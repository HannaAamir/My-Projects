import sqlite3
from datetime import datetime

conn = sqlite3.connect('incident_response.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS incidents
                  (id INTEGER PRIMARY KEY, timestamp TEXT, type TEXT, severity TEXT, actions TEXT, status TEXT)''')

def log_incident(incident_type, severity, actions):
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    cursor.execute("INSERT INTO incidents (timestamp, type, severity, actions, status) VALUES (?, ?, ?, ?, ?)",
                   (timestamp, incident_type, severity, ",".join(actions), "Resolved"))
    conn.commit()
