#ifndef LISTESALLES_H
#define LISTESALLES_H
#include "salles.h"
#include <QMainWindow>
#include "dialog.h"

namespace Ui {
class ListeSalles;
}

class ListeSalles : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListeSalles(QWidget *parent = nullptr);
    ~ListeSalles();
    void setSalleButtonStyle(const QString &style);
private slots:
    void on_AjoutSalles_clicked();

    void on_StatsSalles_clicked();

    void on_retoursalles1_clicked();

    void on_retoursalles2_clicked();

    void on_employes_clicked();

    void on_artistes_clicked();

    void on_contrats_clicked();

    void on_events_clicked();

    void on_matariel_clicked();

    void on_salles_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_20_clicked();


    void on_pushButton_21_clicked();

   // void on_pushButton_25_clicked();

    void on_pushButton_search_clicked();

  //  void on_pushButton_13_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_24_clicked();

   // void on_retoursalles2_4_clicked();

   // void on_pushButton_33_clicked();

   // void on_retoursalles1_2_clicked();

    //void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    //void on_pushButton_8_clicked();

    /*void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_15_clicked();*/

    void on_retoursalles2_7_clicked();

    void on_AjoutSalles_2_clicked();

    void on_AjoutSalles_3_clicked();

    void on_starttest_clicked();

private:
    Ui::ListeSalles *ui;
   // Déclaration de ctmp comme membre de classe
    salles stmp;
    Dialog dialog;


};

#endif // LISTESALLES_H
