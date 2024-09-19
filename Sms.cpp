#include "Sms.h"
#include <QDebug>
void SMS::setTwilioCredentials(const QString &accountSid, const QString &authToken, const QString &twilioPhoneNumber)
{
    this->accountSid = accountSid;
    this->authToken = authToken;
    this->twilioPhoneNumber = twilioPhoneNumber;
}
SMS::SMS(QObject *parent) : QObject(parent)
{
   /* // Initialize your Twilio credentials and phone number
    accountSid = "AC86baf0c06f3b4c1b67835c7f78ac35d3";
    authToken = "243eca000615c2effd55fb16ee46cf6c";
    twilioPhoneNumber = "+14405445319";*/

   accountSid = "AC8f0db31af14a7952bb17994367f7856e";
    authToken = "3a7495f1a11dfa793406372162909817";
    twilioPhoneNumber = "+13342343409";

    connect(&curlProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &SMS::handleSmsResponse);
}

void SMS::sendSms(const QString &to, const QString &message)
{

        qDebug() << "Before sending SMS...";

        QStringList arguments;
        arguments << "-X" << "POST"
                  << "https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json"
                  << "--data-urlencode" << "To=" + to
                  << "--data-urlencode" << "From=" + twilioPhoneNumber
                  << "--data-urlencode" << "Body=" + message
                  << "-u" << accountSid + ":" + authToken;

        // Start the curl process
        curlProcess.start("curl", arguments);

        // Wait for the process to finish (with a timeout to prevent infinite waiting)
        if (!curlProcess.waitForFinished(30000)) {
            // If the process didn't finish within the timeout, handle the error
            qDebug() << "Error: Timed out waiting for curl process to finish.";
        }

        // Check the exit code of the process
        int exitCode = curlProcess.exitCode();
        qDebug() << "Curl process finished with exit code:" << exitCode;

        // Handle the response based on the exit code (you might need to adjust this part)
        if (exitCode == 0) {
            qDebug() << "SMS sent successfully!";
        } else {
            qDebug() << "Error sending SMS. Exit code:" << exitCode;
            qDebug() << "Error details:" << curlProcess.errorString();
        }

        qDebug() << "Sending SMS completed.";
    }


void SMS::handleSmsResponse()
{
    qDebug() << "Handling SMS response...";

    if (curlProcess.exitCode() == 0) {
        qDebug() << "SMS sent successfully!";
    } else {
        qDebug() << "Error sending SMS. Exit code:" << curlProcess.exitCode();
        qDebug() << "Error details:" << curlProcess.readAllStandardError();
    }

    // Emit the signal to indicate that SMS sending is finished
    emit finishedSending();

}
