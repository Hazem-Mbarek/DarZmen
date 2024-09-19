#ifndef PASSWORDRESETDIALOG_H
#define PASSWORDRESETDIALOG_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class PasswordResetDialog;
}

class PasswordResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordResetDialog(QWidget *parent = nullptr);
    ~PasswordResetDialog();
private slots:
    void on_resetButton_clicked();
private:
    Ui::PasswordResetDialog *ui;
    QSqlDatabase db;

    // Méthode pour vérifier si la réponse à la question de sécurité est correcte
    bool verifySecurityAnswer(const QString &answer);

    // Méthode pour mettre à jour le mot de passe dans la base de données
    bool updatePassword(const QString &username, const QString &newPassword);
};

#endif // PASSWORDRESETDIALOG_H











