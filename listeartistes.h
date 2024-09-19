#ifndef LISTEARTISTES_H
#define LISTEARTISTES_H

#include <QMainWindow>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QSqlQueryModel>

#include <QSystemTrayIcon>
#include <QMenu>
#include<QDialog>
#include <QFileDialog>



namespace Ui {
class ListeArtistes;
}

class ListeArtistes : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListeArtistes(QWidget *parent = nullptr);
    ~ListeArtistes();
    void setArtisteButtonStyle(const QString &style);
private slots:



    void on_AjoutA_clicked();

    void on_StatsA_clicked();

    void on_retourartiste2_clicked();

    void on_retourartiste1_clicked();

    void on_employes_clicked();

    void on_artistes_clicked();

    void on_contrats_clicked();

    void on_events_clicked();

    void on_matariel_clicked();

    void on_salles_clicked();

    void on_retourartiste2_2_clicked();

    void on_b_confajout_arti_clicked();

    void on_pushButton_26_clicked();

    void on_pbmodifA_clicked();

    void on_pbmodifCA_clicked();


     void on_stat_cl_clicked();
    void on_pb_trier_clicked();
    void on_search_buttonn_clicked();
    // Fonction pour exporter la liste d'équipements vers un fichier PDF
            void exportToPDF(const QString& filePath, QSqlQueryModel* model);

            // Fonction utilitaire pour dessiner le contenu du modèle sur une page PDF
            void drawModel(QPainter& painter, QSqlQueryModel* model);
            void on_exportToPdfButton_clicked();

          //  void on_verifierQuantiteEquipements_clicked();
            void notif();

            void on_exportToPdfButton_2_clicked();

private:

    QSystemTrayIcon trayIcon;
    QMenu* trayMenu;
    Ui::ListeArtistes *ui;

};

#endif // LISTEARTISTES_H
