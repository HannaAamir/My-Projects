import os
import logging
from app import app

# Set up logging for easier debugging
logging.basicConfig(level=logging.DEBUG)

if __name__ == "__main__":
    # Run the Flask application
    app.run(host="0.0.0.0", port=5000, debug=True)
