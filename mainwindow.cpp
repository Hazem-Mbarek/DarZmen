#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listematriels.h"
#include "listeevents.h"
#include "listesalles.h"
#include "listecontrats.h"
#include "listeartistes.h"
#include "listepersonnels.h"
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->login, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(ui->oublie, &QPushButton::clicked, this, &MainWindow::on_forgotPasswordButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_eventmainButton_2_clicked()
{
    // Start the Python face recognition script as a subprocess
    QProcess process;
    process.start("python", QStringList() << "C:\\Users\\kills\\Desktop\\facial recognition\\main.py");
    if (!process.waitForStarted()) {
        QMessageBox::critical(nullptr, QObject::tr("Error Starting Python Script"),
                              QObject::tr("Failed to start the face recognition script.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        //return 1;
    }


    // Wait for the Python process to finish
       if (!process.waitForFinished()) {
           QMessageBox::critical(nullptr, QObject::tr("Error"),
                                 QObject::tr("Failed to wait for the Python process to finish.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
           //return 1;
       }

       // Read the result from the standard output stream of the Python subprocess
       process.waitForReadyRead();
       QString result = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
       qDebug() << result;

    /*QFile file("C:\\Users\\kills\\Desktop\\facial recognition\\face_recognition_result.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString result = in.readLine().trimmed();
        file.close();
        qDebug() << result;*/
       if (result == "MATCH") {

           ui->MWstackedwidget->setCurrentIndex(3);
       }
       else {
                  QMessageBox::critical(nullptr, QObject::tr("Face Recognition Failed"),
                                        QObject::tr("Face recognition failed.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);

                  ui->MWstackedwidget->setCurrentIndex(0);
              }
}




void MainWindow::on_matmainButton_clicked()
{
    // Create an instance of ListeMatriels
        ListeMatriels *l = new ListeMatriels();

        // Show the ListeMatriels window
        l->show();
        //l->affichageTabMat("","");
        // Close the main window
        this->close();
        l->setMatButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");


}

void MainWindow::on_eventmainButton_clicked()
{

        ListeEvents *l = new ListeEvents();
        l->show();
        this->close();
        l->setEventsButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void MainWindow::on_sallesmainButton_clicked()
{
    ListeSalles *l = new ListeSalles();
    l->show();
    this->close();
    l->setSalleButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void MainWindow::on_contratsmainButton_clicked()
{
    ListeContrats *l = new ListeContrats();
    l->show();
    this->close();
    l->setContratButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void MainWindow::on_artistemainButton_clicked()
{
    ListeArtistes *l = new ListeArtistes();
    l->show();
    this->close();
    l->setArtisteButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void MainWindow::on_employesmainButton_clicked()
{
    ListePersonnels *l = new ListePersonnels();
    l->show();
    this->close();
    l->setPersoButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}


void MainWindow::on_retourOptions_clicked()
{
    ui->MWstackedwidget->setCurrentIndex(0);
}

void MainWindow::on_sallesmainButton_2_clicked()
{
    ui->MWstackedwidget->setCurrentIndex(2);
}

void MainWindow::on_sallesmainButton_3_clicked()
{
    ui->MWstackedwidget->setCurrentIndex(3);
}










#include "passwordresetdialog.h"
#include<QDialog>
#include <QFileDialog>


void MainWindow::on_loginButton_clicked()
{
    // Récupérer le nom d'utilisateur et le mot de passe saisis par l'utilisateur
    QString username = ui->username_2->text();
    QString password = ui->password_2->text();

    // Vérifier les informations d'identification dans la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM LOGIN WHERE USERNAME = :USERNAME AND PASSWORD = :PASSWORD");
    query.bindValue(":USERNAME", username);
    query.bindValue(":PASSWORD", password);

    if (query.exec() && query.next()) {
        // L'utilisateur est authentifié avec succès
        QMessageBox::information(this, "Connexion réussie", "Vous êtes maintenant connecté.");
        // Rediriger vers la page principale de l'application ou effectuer d'autres actions nécessaires
       // ui->Menu_widget->setCurrentWidget(ui->Menu_widget);

         ui->MWstackedwidget->setCurrentIndex(3);
    } else {
        // L'authentification a échoué
        QMessageBox::warning(this, "Échec de la connexion", "Nom d'utilisateur ou mot de passe incorrect.");
    }
}
void MainWindow::on_forgotPasswordButton_clicked()
{
    // Ouvrir la fenêtre de réinitialisation de mot de passe
    PasswordResetDialog resetDialog;
    resetDialog.exec();
}
























