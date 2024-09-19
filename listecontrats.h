#ifndef LISTECONTRATS_H
#define LISTECONTRATS_H
#include "contrats.h"
#include <QMainWindow>
#include <QTableView>

namespace Ui {
class ListeContrats;
}

class ListeContrats : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListeContrats(QWidget *parent = nullptr);
    ~ListeContrats();
    void setContratButtonStyle(const QString &style);
private slots:
    void on_AjoutCont_clicked();


    void on_StatsCont_clicked();


    void on_retourcont1_clicked();

    void on_retourcont2_clicked();




    void on_employes_clicked();

    void on_artistes_clicked();

    void on_contrats_clicked();

    void on_events_clicked();

    void on_matariel_clicked();

    void on_salles_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_retourcont2_2_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void exportToPdf(const QString& filename, QTableView* tableView);
    void exportToExcel(const QString& filename, QTableView* tableView);

    void on_pushButton_16_clicked();

    void on_pushButton_19_clicked();
    void on_pushButton_36_clicked();

    void on_annulermail_clicked();
    void sendMail(QString email,QString message);

    void on_pbEnvoiMail_2_clicked();


    void on_pushButton_35_clicked();
    void MakePlot1();

private:
    Ui::ListeContrats *ui;
    contrats c;
};

#endif // LISTECONTRATS_H
