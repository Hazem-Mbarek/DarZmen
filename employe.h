#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include "string"
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QPdfWriter>
#include <QPainter>

#include <QTextDocument>
#include <QSqlError>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSlice>

#include <QDate>


class employe
{
public:
    employe();


    int getMatricule();
    void setMatricule(int nvMatricule);

    QString getNomE();
    void setNomE(QString nvNomE);


    QString getPrenomE();
    void setPrenomE(QString nvPrenomE);

    QString getMailE();
    void setMailE(QString nvMailE);

    QString getServiceE();
    void setServiceE(QString nvServiceE);

    int getSalaireE();
    void setSalaireE(int nvSalaireE);

    QString getExperienceE();
    void setExperienceE(QString nvExperienceE);

    int getIdEventE();
    void setIdEventE(int nvIdEventE);


    QDate getDateGardeE();
    void setDateGardeE(QDate nvDateGardeE);




//*************************************************LES FONCTIONALITES***************************************************

    bool ajouter_Emp(const QString &ExperienceE, const QByteArray &imageData);
    bool supprimer_Emp(int Matricule);
    QSqlQueryModel* afficher();
    bool modifier_Emp(QVariant MatE,const QString &ExperienceE);
    QSqlQueryModel*  rechercherParIdd(QString Matricule);
    void pdfgenrateur();
    QChartView *capacite();

    QSqlQueryModel*  rechercherParDate(const QDate& date);
    bool rechercher(int Matricule);
  //  bool rechercherE(int Matricule);


private:

    int Matricule;
    QString NomE;
    QString PrenomE;
    QString MailE;
    QString ServiceE;
    int SalaireE;
    QString ExperienceE;
    int IdEventE;
    QDate DateGardeE;
    QByteArray img;





};

#endif // EMPLOYE_H

