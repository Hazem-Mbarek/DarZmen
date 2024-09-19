#include "artiste.h"
#include"QSqlQuery"
#include <QDebug>
#include<QtSql>
#include <QSqlQueryModel>
artiste::artiste() {
    // Constructor implementation
}

int artiste::getIdartist () {
    return Idartist;
}

void artiste::setIdartist(int nvIdartist) {
    Idartist= nvIdartist;
}


QString artiste::getNomA() {
    return NomA;
}

void artiste::setNomA(QString nvNomA) {
    NomA = nvNomA;
}
QString artiste::getPrenomA() {
    return PrenomA;
}

void artiste::setPrenomA(QString nvPrenomA) {
    PrenomA = nvPrenomA;
}
QString artiste::getMailA() {
    return MailA;
}

void artiste::setMailA(QString nvMailA) {
    MailA = nvMailA;
}
int artiste::getNtlfnA() {
    return NtlfnA;
}

void artiste::setNtlfnA(int nvNtlfnA) {
    NtlfnA = nvNtlfnA;
}
int artiste::getNblocA() {
    return NblocA;
}

void artiste::setNblocA(int nvNblocA) {
    NblocA=nvNblocA;
}
bool artiste::ajouter_Arti(){
    int Idartist= getIdartist();
    QString NomA= getNomA();
    QString PrenomA= getPrenomA();
    QString MailA= getMailA();
    int NtlfnA= getNtlfnA();
    int NblocA= getNblocA();
QSqlQuery query;

query.prepare("INSERT INTO ARTISTE (IDARTIST,NOMARTIST,PRENOMARTIST,EMAILARTIST,NTLFARTIST,NLOC)" " VALUES (:Idartist, :NomA, :PrenomA, :MailA, :NtlfnA, :NblocA)");

                query.bindValue(":Idartist", Idartist);
                query.bindValue(":NomA", NomA);
                query.bindValue(":PrenomA", PrenomA);
                query.bindValue(":MailA", MailA);
                query.bindValue(":NtlfnA", NtlfnA);
                query.bindValue(":NblocA", NblocA);

return query.exec();
}


bool artiste::supprimer_Arti(int Idartist)
{
    QSqlQuery query;
    QString res = QString::number(Idartist);
    query.prepare("Delete from ARTISTE WHERE IDARTIST=:Idartist");
    query.bindValue(":Idartist", res);
    return query.exec();
}

#include <QMessageBox>
QSqlQueryModel* artiste::afficher_Arti(){
//QMessageBox::information(nullptr, "Artist", "YOMNA has the biggest number of LOCATIONS:25.");
QSqlQueryModel *model = new QSqlQueryModel();
QString queryStr = "select * from ARTISTE";
model->setQuery(queryStr);


model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDARTIST"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMARTIST"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMARTIST"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAILARTIST"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("NTLFARTIST"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NLOC"));


return model;

}













bool artiste::modifier_Arti(QVariant Idartist){

QString PrenomA= getPrenomA();
QString NomA= getNomA();
QString MailA= getMailA();
int NtlfnA= getNtlfnA();
int NblocA= getNblocA();

QSqlQuery query;
query.prepare("UPDATE ARTISTE SET NOMARTIST= :NomA,PRENOMARTIST= :PrenomA,EMAILARTIST= :MailA,NTLFARTIST= :NtlfnA,NLOC= :NblocA   WHERE IDARTIST= :Idartist");

              query.bindValue(":Idartist", Idartist);
              query.bindValue(":NomA", NomA);
              query.bindValue(":PrenomA", PrenomA);
              query.bindValue(":MailA", MailA);
              query.bindValue(":NtlfnA", NtlfnA);
              query.bindValue(":NblocA", NblocA);


 return query.exec();
}







QSqlQueryModel*  artiste::rechercher(QString Idartist){
    QSqlQueryModel* modal = new QSqlQueryModel();

    QString queryString = "SELECT * FROM ARTISTE WHERE IDARTIST = '" + Idartist + "'";

    qDebug() << "Query string: " << queryString;

    modal->setQuery(queryString);
    if (modal->lastError().isValid()) {
        qDebug() << "Query error: " << modal->lastError().text();
    } else {
        qDebug() << "Query successful.";

        for (int row = 0; row < modal->rowCount(); ++row) {
            QString resultString; //cont val tt lign
            for (int col = 0; col < modal->columnCount(); ++col) {
                resultString += modal->data(modal->index(row, col)).toString() + " | ";
            }
            qDebug() << "Result " << row + 1 << ": " << resultString;
        }
    }

    return modal;
}



