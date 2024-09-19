#ifndef LISTEEVENTS_H
#define LISTEEVENTS_H
#include "evenements.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QImage>
#include "QZXing.h"
#include "Arduino.h"
namespace Ui {
class ListeEvents;
}

class ListeEvents : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListeEvents(QWidget *parent = nullptr);
    ~ListeEvents();
    void setEventsButtonStyle(const QString &style);
    void exportToPdf(const QString& filename, QTableView* tableView);
    void exportToExcel(const QString& filename, QTableView* tableView);
    QImage generateQRCode(QString data);
    void MakePlot1();
    void printWidget(QWidget* widget);
    int getEventsWithDeadlineOver();
    int getEventsDuringCurrentWeek();
    int getEventsDuringCurrentMonth();
    QString getEventWithMostEmployees();
    void createPieChart();
    bool isRoomAvailable(int roomId, const QDate &startDate, const QDate &endDate);
    void showRoomInfoDialog(QWidget *p,QDate dated,QDate datef);
    QDate findNextAvailableDate(int roomId, const QDate &startDate, const QDate &endDate);
    //void affichageTabEvent(bool testsearch,bool testtri);
    //stream

private slots:
    void on_stats_events_4_clicked();

    void on_add_events_4_clicked();

    //void on_retourevents1_clicked();

    void on_retourevents2_clicked();

    void on_employes_clicked();

    void on_artistes_clicked();

    void on_contrats_clicked();

    void on_events_clicked();

    void on_matariel_clicked();

    void on_salles_clicked();

    void on_pushButton_36_clicked();

    void on_delete_button_4_clicked();

    void on_pushButton_38_clicked();

    void on_update_button_4_clicked();

    //void on_pushButton_46_clicked();

    void on_retourevents2_2_clicked();

    void on_pushButton_45_clicked();

    void on_pdf_button_4_clicked();

    void on_filtrer_button_4_clicked();

    void on_search_button_4_clicked();

    void on_pdf_button_5_clicked();

    void on_pushButton_39_clicked();

    void on_qrcode_button_4_clicked();

    void on_retourevents1_2_clicked();

    void on_retourevents1_3_clicked();

    void on_retourevents1_4_clicked();

    void on_pushButton_44_clicked();




    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void updateLabell();

    void on_pdf_button_8_clicked();

private:
    Ui::ListeEvents *ui;
    Evenements E;
    Arduino A;
    QThread *esp32Thread;
    QByteArray data;
};

#endif // LISTEEVENTS_H
