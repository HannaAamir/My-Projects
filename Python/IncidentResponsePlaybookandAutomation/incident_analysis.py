from automated_actions import execute_actions


def analyze_alerts(alerts):
    for alert in alerts:
        severity = alert.get('severity', 'low')
        incident_type = alert.get('incident_type', 'Unknown')
        print(f"Alert: {incident_type} | Severity: {severity}")
        trigger_playbook(incident_type, severity)


def trigger_playbook(incident_type, severity):
    print(f"Processing {incident_type} with severity {severity}")
    if severity == "high":
        actions = playbook.get(incident_type, {}).get("high", [])
    elif severity == "medium":
        actions = playbook.get(incident_type, {}).get("medium", [])
    else:
        actions = playbook.get(incident_type, {}).get("low", [])

    execute_actions(actions)
