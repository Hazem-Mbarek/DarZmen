#ifndef LISTEMATRIELS_H
#define LISTEMATRIELS_H
#include "materiel.h"
#include <QMainWindow>
#include <QTableView>

namespace Ui {
class ListeMatriels;
}

class ListeMatriels : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListeMatriels(QWidget *parent = nullptr);
    ~ListeMatriels();
    void setMatButtonStyle(const QString &style);
    void affichageTabMat(bool testsearch,bool testtri);
    void exportToPdf(const QString& filename, QTableView* tableView);
    void exportToExcel(const QString& filename, QTableView* tableView);
    void MakePlot1();
    void MakePlot2();
    void generalstats();
    void printWidget(QWidget* widget);



private slots:
    void on_salles_clicked();

    void on_AjoutMat_clicked();

    void on_StatsMat_clicked();

    void on_retourmat1_clicked();

    void on_retourmat2_clicked();



    void on_confirmajoutmat_clicked();



    void on_suppressionmateriel_clicked();

    void on_retourmat3_clicked();

    void on_confirmmodifmat_clicked();

    void on_ModifMat_clicked();

    void on_employes_clicked();

    void on_artistes_clicked();

    void on_contrats_clicked();

    void on_events_clicked();

    void on_matariel_clicked();

    void on_confirmfilterMAT_clicked();

    void on_filtrerMat_clicked();

    void on_rechercheMat_clicked();

    void on_pdfMatExp_clicked();

    void on_ExcelmAT_clicked();

    void on_retour5_clicked();

    void on_barcodeMat_clicked();

    void on_genererBarcode_clicked();

    void on_nextGraphMat_clicked();

    void on_prevGraphMat_clicked();

    void on_nextGraphMat_2_clicked();

    void on_retour5_2_clicked();

    void on_imprimerQR_clicked();

    void on_damageMat_clicked();

    void on_retourdamage_clicked();

    void on_pushButton_49_clicked();

    void on_cleardamage_clicked();

    void on_evaluercontrat_clicked();

    void on_decoderMat_clicked();

    void on_retour5_3_clicked();

    void on_retour5_4_clicked();

    void on_decoderMat_2_clicked();

    void on_pushButton_clicked();

    void on_commanderMat_clicked();

private:
    Ui::ListeMatriels *ui;
    Materiel M;
};

#endif // LISTEMATRIELS_H
