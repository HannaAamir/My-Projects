import requests
from config import siem_url, siem_api_key
import requests
import json

import requests

# Mock function for testing
def fetch_siem_alerts_test_mode(use_mock=False):
    if use_mock:
        # Return mock data for testing
        return {
            "alerts": [
                {"id": 1, "severity": "High", "message": "Suspicious login attempt detected."},
                {"id": 2, "severity": "Medium", "message": "Multiple failed login attempts."}
            ]
        }
    else:
        # Replace with your actual code to fetch alerts from SIEM system
        try:
            siem_url = 'https://siem.company.com/api/alerts'  # Replace with real URL
            headers = {'Authorization': 'Bearer your_api_key'}  # Replace with your actual API key
            response = requests.get(siem_url, headers=headers)
            response.raise_for_status()  # Raise error if request failed
            return response.json()  # Return the actual JSON response from the SIEM
        except requests.exceptions.RequestException as e:
            print(f"Error fetching SIEM alerts: {e}")
            return None

# Mocked response for testing
def fetch_siem_alerts_mocked():
    mock_response = {
        "alerts": [
            {"id": 1, "severity": "high", "message": "Suspicious login detected"},
            {"id": 2, "severity": "low", "message": "User password changed"}
        ]
    }
    return mock_response

# Real function to fetch SIEM alerts (requires a valid SIEM system URL and API key)
def fetch_siem_alerts():
    siem_url = 'https://siem.company.com/api/alerts'  # Replace with actual SIEM endpoint
    api_key = 'your_api_key_here'  # Replace with your API key or token

    headers = {
        'Authorization': f'Bearer {api_key}',
        'Content-Type': 'application/json'
    }

    try:
        # Making a GET request to fetch SIEM alerts
        response = requests.get(siem_url, headers=headers)
        response.raise_for_status()  # Raise an exception for any HTTP error responses

        # If the response is successful, return the JSON data
        return response.json()
    except requests.exceptions.RequestException as e:
        print(f"Error fetching SIEM alerts: {e}")
        return None

# Switch between mocked and real functions for testing purposes
def fetch_siem_alerts_test_mode(use_mock=True):
    if use_mock:
        return fetch_siem_alerts_mocked()
    else:
        return fetch_siem_alerts()

