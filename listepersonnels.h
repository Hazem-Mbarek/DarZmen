#ifndef LISTEPERSONNELS_H
#define LISTEPERSONNELS_H

#include <QMainWindow>
#include<QTableView>
#include"Arduino.h"
namespace Ui {
class ListePersonnels;
}

class ListePersonnels : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListePersonnels(QWidget *parent = nullptr);
    ~ListePersonnels();
    void setPersoButtonStyle(const QString &style);

private slots:

//*******************************************Menu********************************************************
    void on_AjoutEmp_clicked();

    void on_StatsEmp_clicked();

    void on_retouremp1_clicked();

    void on_retouremp2_clicked();

    void on_employes_clicked();

    void on_artistes_clicked();

    void on_contrats_clicked();

    void on_events_clicked();

    void on_matariel_clicked();

    void on_salles_clicked();



//******************************************Employe*******************************************************

    void on_retouremp2_3_clicked();

    void on_pbajout_clicked();

    void on_pbsupp_clicked();

    void on_pbmodiffC_2_clicked();
    void on_pbmodiff_clicked();


    void onRadioButtonAddClicked();
    void onRadioButtonModifClicked();


    void on_search_button_2_clicked();


    void on_pb_tri_clicked();

    void on_pdf_export_clicked();

    void on_stat_clicked();
    void on_anuulerStat_clicked();
    void on_stat_export_clicked();


    void sendMail(QString,QString);
    void on_annulermail_clicked();
    void on_pbEnvoiMail_2_clicked();


    void on_pushButton_24_clicked();

    void on_pushButton_26_clicked();
    void on_pushButton_25_clicked();
    void on_notification_button_clicked();

    void on_btnParcourir_clicked();

    void exportToExcel(const QString& filename, QTableView* tableView);
    void on_pdf_button_5_clicked();

    void exportToPdf_Client(const QString& filePath, QTableView* tableView);
    void on_pbPDF_clicked();
    void update_label();

private:
    Ui::ListePersonnels *ui;
    QByteArray imageData;
    QByteArray data;
   // QByteArray data2;
    Arduino A;
   // Arduino b;
    QString Mat;
};

#endif // LISTEPERSONNELS_H
