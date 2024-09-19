#include "passwordresetdialog.h"
#include "ui_passwordresetdialog.h"


PasswordResetDialog::PasswordResetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordResetDialog)
{
    ui->setupUi(this);
}

PasswordResetDialog::~PasswordResetDialog()
{
    delete ui;
}

void PasswordResetDialog::on_resetButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString answer = ui->securityAnswerLineEdit->text();
    QString newPassword = ui->newPasswordLineEdit->text();

    if (verifySecurityAnswer(answer)) {
        if (updatePassword(username, newPassword)) {
            QMessageBox::information(this, "Success", "Password reset successfully.");
            close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to reset password. Please try again.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Incorrect security answer.");
    }
}

bool PasswordResetDialog::verifySecurityAnswer(const QString &answer)
{
    // Vérifier si la réponse à la question de sécurité est correcte
    QSqlQuery query(db);
    query.prepare("SELECT ANSWER FROM security_questions");
    if (query.exec() && query.next()) {
        QString correctAnswer = query.value("ANSWER").toString();
        return (answer == correctAnswer);
    } else {
        return false;
    }
}


bool PasswordResetDialog::updatePassword(const QString &username, const QString &newPassword)
{
    // Mettre à jour le mot de passe dans la base de données
    QSqlQuery query(db);
    query.prepare("UPDATE LOGIN SET password = :password WHERE username = :username");
    query.bindValue(":password", newPassword);
    query.bindValue(":username", username);
    return query.exec();
}

