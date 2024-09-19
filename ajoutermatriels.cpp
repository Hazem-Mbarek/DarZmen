#include "ajoutermatriels.h"
#include "ui_ajoutermatriels.h"
#include "mainwindow.h"
#include "connection.h"
#include "startwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

AjouterMatriels::AjouterMatriels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterMatriels)
{
    ui->setupUi(this);
}

AjouterMatriels::~AjouterMatriels()
{
    delete ui;
}


void AjouterMatriels::FacialRecognition()
{
    MainWindow w;
    AjouterMatriels log;
    Connection c;
    Startwindow splashScreen;
    bool test = c.createconnect();

    log.close();
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
           splashScreen.show();
           splashScreen.start_loading();
           splashScreen.close();
           w.show();

           if(test)
               {
                   QMessageBox::information(nullptr, QObject::tr("database is open"),
                               QObject::tr("connection successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

           }
               else
                   QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                               QObject::tr("connection failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
       } else {
           QMessageBox::critical(nullptr, QObject::tr("Face Recognition Failed"),
                                 QObject::tr("Face recognition failed.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void AjouterMatriels::on_facialrec_clicked()
{
    FacialRecognition();
}
