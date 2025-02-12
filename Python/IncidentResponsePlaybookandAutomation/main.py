from siem_integration import fetch_siem_alerts_test_mode
from incident_analysis import analyze_alerts, trigger_playbook
from automated_actions import execute_actions
from log_to_db import log_incident
from notification import send_email


def main():
    # Fetch SIEM alerts
    alerts = fetch_siem_alerts_test_mode(use_mock=True)

    if alerts is None:
        print("No alerts to analyze.")
        return
    # Analyze and classify alerts
    analyze_alerts(alerts)

    # Example: Log an incident after automatic action
    log_incident("DDoS", "high", ["Block IP", "Alert team"])

    # Send a notification (example)
    send_email("it_team@company.com", "Incident Report", "DDoS attack mitigated.")


if __name__ == "__main__":
    main()
