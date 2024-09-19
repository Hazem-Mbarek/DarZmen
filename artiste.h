#ifndef ARTISTE_H
#define ARTISTE_H
#include<QString>
#include <QDate>
#include "string"
#include <QSqlQueryModel>
#include <QPainter>
using namespace std ;


class artiste
{
public:
    artiste();
    int getIdartist();
    void setIdartist( int nvIdartist);

    QString getNomA();
    void setNomA( QString nvNomA);

    QString getPrenomA();
    void setPrenomA( QString nvPrenomA);

    QString getMailA();
    void setMailA(QString nvMailA);

    int getNtlfnA();
    void setNtlfnA( int nvNtlfnA);

    int getNblocA();
    void setNblocA(int nvNblocA);
    bool ajouter_Arti();
    bool supprimer_Arti(int Idartist);
    QSqlQueryModel* afficher_Arti();
    bool modifier_Arti(QVariant Idartist);

    QSqlQueryModel*  rechercher(QString Idartist);

   /* // Fonction pour exporter la liste d'équipements vers un fichier PDF
            void exportToPDF(const QString& filePath, QSqlQueryModel* model);

            // Fonction utilitaire pour dessiner le contenu du modèle sur une page PDF

            void on_exportToPdfButton_clicked();
               void drawModel(QPainter& painter, QSqlQueryModel* model);*/
private:
private:
    int Idartist;
    QString NomA;
    QString PrenomA;
    QString MailA;
   int NtlfnA;
    int NblocA;


};

#endif // ARTISTE_H
