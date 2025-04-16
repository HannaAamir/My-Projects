import os
import json
import random
import logging
import requests
from flask import Flask, render_template, request, jsonify

# Initialize Flask application
app = Flask(__name__)
app.secret_key = os.environ.get("SESSION_SECRET", "default_secret_key")

# Load quotes from JSON file
def load_quotes():
    try:
        with open('quotes.json', 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        logging.error("quotes.json not found, creating empty quote database")
        return {"happy": [], "sad": [], "motivating": [], "inspiring": [], 
                "calm": [], "funny": [], "love": [], "wisdom": []}
    except json.JSONDecodeError:
        logging.error("Error parsing quotes.json, returning empty database")
        return {"happy": [], "sad": [], "motivating": [], "inspiring": [], 
                "calm": [], "funny": [], "love": [], "wisdom": []}

# Fetch quotes from QuoteGarden API
def fetch_quotes_from_api(mood, limit=10):
    moods_map = {
        "happy": "happiness",
        "sad": "sadness",
        "motivating": "motivational",
        "inspiring": "inspirational",
        "calm": "peace",
        "funny": "humor",
        "love": "love",
        "wisdom": "wisdom"
    }
    
    search_term = moods_map.get(mood.lower(), mood.lower())
    
    try:
        response = requests.get(f"https://quote-garden.onrender.com/api/v3/quotes?genre={search_term}&limit={limit}")
        if response.status_code == 200:
            data = response.json()
            if data.get('data'):
                return [{"text": quote["quoteText"], "author": quote["quoteAuthor"]} 
                        for quote in data["data"]]
        return []
    except Exception as e:
        logging.error(f"Error fetching quotes from API: {e}")
        return []

# Routes
@app.route('/')
def index():
    quotes = load_quotes()
    moods = list(quotes.keys())
    return render_template('index.html', moods=moods)

@app.route('/quotes', methods=['POST'])
def get_quotes():
    data = request.get_json()
    mood = data.get('mood', '').lower()
    
    if not mood:
        return jsonify({"error": "Mood is required"}), 400
    
    quotes = load_quotes()
    
    # If the mood doesn't exist in our database or has no quotes, create it
    if mood not in quotes:
        quotes[mood] = []
    
    # If we have fewer than 5 quotes for this mood, try to fetch more from the API
    if len(quotes[mood]) < 5:
        api_quotes = fetch_quotes_from_api(mood)
        
        # Add any new quotes to our database
        if api_quotes:
            for quote in api_quotes:
                if quote not in quotes[mood]:
                    quotes[mood].append(quote)
            
            # Save updated quotes back to the file
            try:
                with open('quotes.json', 'w') as f:
                    json.dump(quotes, f, indent=4)
            except Exception as e:
                logging.error(f"Error saving quotes to file: {e}")
    
    # If we still have no quotes for this mood after API call
    if not quotes[mood]:
        return jsonify({
            "quote": "No quotes found for this mood. Try another mood?",
            "author": "Quote Bot"
        })
    
    # Return a random quote for the given mood
    random_quote = random.choice(quotes[mood])
    return jsonify(random_quote)

# Error handlers
@app.errorhandler(404)
def page_not_found(e):
    return render_template('index.html', error="Page not found"), 404

@app.errorhandler(500)
def server_error(e):
    return render_template('index.html', error="Server error. Please try again later."), 500
