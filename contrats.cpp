#include "contrats.h"
#include <QDate>
#include <QDebug>
#include <QSqlError>

contrats::contrats()
{
id=0000;
valeur=0000;
datedeb= QDate::currentDate();
datefin= QDate::currentDate();
description="";
}
void contrats::setidcontrat(int n){id=n;}
void contrats::setidacontrat(int n){ida=n;}
void contrats::setdatedeb(QDate n){datedeb=n;}
void contrats::setdatefin(QDate n){datefin=n;}
void contrats::setdescription(QString n){description=n;}
void contrats::setvaleur(int n){valeur=n;}

int  contrats::get_idcontrat(){return id;}
int  contrats::get_idacontrat(){return ida;}
QDate contrats::get_datedeb(){return datedeb;}
QDate contrats::get_datefin(){return datefin;}
QString contrats::get_description(){return description;}
int contrats::get_valeur(){return valeur;}


contrats::contrats(int id,int valeur,QDate datedeb,QDate datefin,QString description,int ida)
{
    this->id=id;
    this->datedeb=datedeb;
    this->datefin=datefin;
    this->valeur=valeur;
    this->description=description;
    this->ida=ida;
}

//crud ajout
bool contrats::ajouter_contrat()
{
    QSqlQuery query;
    query.prepare("INSERT INTO contrat (date_debut_contrat, date_fin_contrat, description, valeur, id_artiste) "
                  "VALUES (TO_DATE(:date_debut_contrat, 'YYYY-MM-DD'), TO_DATE(:date_fin_contrat, 'YYYY-MM-DD'), :description, :valeur, :id_artiste)");
    query.bindValue(":date_debut_contrat", datedeb.toString("yyyy-MM-dd"));
    query.bindValue(":date_fin_contrat", datefin.toString("yyyy-MM-dd"));
    query.bindValue(":description", description);
    query.bindValue(":valeur", valeur);
    query.bindValue(":id_artiste", ida);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    return true;
}

//Supp CRUD
bool contrats::supprimer_contrat(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from contrat where id_contrat= :id");
    query.bindValue(":id",res);

    return query.exec();
}
//afficher crud
QSqlQueryModel *contrats::afficher_contrat(const QString &searchQuery, const QString &sortOrder, const QString &sorttype)
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QString queryStr = "SELECT * FROM contrat";

    if (!searchQuery.isEmpty()) {
        queryStr += " WHERE id_contrat LIKE '%" + searchQuery + "%' OR " +
                    "date_debut_contrat LIKE '%" + searchQuery + "%' OR " +
                    "date_fin_contrat LIKE '%" + searchQuery + "%' OR " +
                    "description LIKE '%" + searchQuery + "%' OR " +
                    "valeur LIKE '%" + searchQuery + "%' OR " +
                    "id_artiste LIKE '%" + searchQuery + "%'";
     }


    if (!sortOrder.isEmpty() && !sorttype.isEmpty()) {
        queryStr += " ORDER BY "+ sorttype +" " + sortOrder;
        //qDebug() <<queryStr;
    }

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Debut"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("valeur"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_artiste"));

    return model;
}
//modifier crud
void contrats::modfier_contrat(int id,QDate datedeb,QDate datefin,int valeur,int ida,QString description)
{
    QSqlQuery query;
    query.prepare("UPDATE contrat SET date_debut_contrat = :datedeb, date_fin_contrat = :datefin, description = :description, valeur = :valeur, id_artiste = :ida WHERE id_contrat = :id");
    query.bindValue(":datedeb",datedeb);
    query.bindValue(":datefin",datefin);
    query.bindValue(":description",description);
    query.bindValue(":valeur",valeur);
    query.bindValue(":ida",ida);
    query.bindValue(":id",id);
    if (!query.exec()) {
                qDebug() << "Error executing query:" << query.lastError().text();
                return;
            }
    qDebug() << "Data inserted successfully!";
}
