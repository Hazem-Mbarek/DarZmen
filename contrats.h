#ifndef CONTRATS_H
#define CONTRATS_H
#include <iostream>
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class contrats
{
public:
    contrats();
    contrats(int,int,QDate,QDate,QString,int);
    void setidcontrat(int n);
    void setidacontrat(int n);
    void setdatedeb(QDate n);
    void setdatefin(QDate n);
    void setdescription(QString n);
    void setvaleur(int n);
    int get_idcontrat();
    int get_idacontrat();
    QDate get_datedeb();
    QDate get_datefin();
    QString get_description();
    int get_valeur();

    //crud
    bool ajouter_contrat();
    QSqlQueryModel * afficher_contrat(const QString& searchQuery, const QString& sortOrder, const QString &sorttype);
    bool supprimer_contrat(int id);
    void modfier_contrat(int id,QDate datedeb,QDate datefin,int valeur,int ida,QString description);

private:
    int id,valeur,ida;
    QDate datedeb,datefin;
    QString description;

};

#endif // CONTRATS_H
