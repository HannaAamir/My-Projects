import smtplib
from email.mime.text import MIMEText

def send_email(to, subject, body):
    msg = MIMEText(body)
    msg["Subject"] = subject
    msg["From"] = "no-reply@company.com"
    msg["To"] = to

    with smtplib.SMTP("smtp.company.com") as server:
        server.sendmail(msg["From"], [msg["To"]], msg.as_string())
