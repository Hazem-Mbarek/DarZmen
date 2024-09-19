#include "materiel.h"
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <chrono>
#include <ctime>
#include <QFile>
#include <QTextStream>
#include <QDesktopServices>


Materiel::Materiel() {}

QString Materiel::getIdM() {
    return IdM;
}

void Materiel::setIdM(const QString& nvIdM) {
    IdM = nvIdM;
}

QString Materiel::getIdSalle() {
    return IdSalle;
}

void Materiel::setIdSalle(const QString& nvIdSalle) {
    IdSalle = nvIdSalle;
}

QString Materiel::getTypeM() {
    return TypeM;
}

void Materiel::setTypeM(const QString& typeM) {
    TypeM = typeM;
}


QString Materiel::getQuantiteM() {
    return QuantiteM;
}

void Materiel::setQuantiteM(const QString& nvQuantiteM) {
    QuantiteM = nvQuantiteM;
}

QString Materiel::getQuantiteENDOM() {
    return QuantiteENDOM;
}

void Materiel::setQuantiteENDOM(const QString& nvQuantiteENDOM) {
    QuantiteENDOM = nvQuantiteENDOM;
}

QString Materiel::getPrixM() {
    return PrixM;
}

void Materiel::setPrixM(const QString& nvPrixM) {
    PrixM = nvPrixM;
}

bool Materiel::ajouter_materiel()
{

    QString type = getTypeM();
     QString prix = getPrixM();
    QString quantite = getQuantiteM();
    QString idSalle = getIdSalle();


    QSqlQuery query;
    query.prepare("INSERT INTO Materiels (TYPE, PRIX, QUANTITEM, IDSALLE, QUANTITEENDOM) VALUES (:type, :prix, :quantite, :idSalle, 0)");


    query.bindValue(":type", type);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":idSalle", idSalle);


    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return true;
    }

    else
    {
        return true;
    qDebug() << "Data inserted successfully!";
    }

}

bool Materiel::supprimer_materiel(QVariant idMat)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Materiels WHERE ID_MAT = :id");
    query.bindValue(":id", idMat);

    if (!query.exec()) {
        qDebug() << "Error executing delete query:" << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    qDebug() << "Entry with ID_MAT =" << idMat.toInt() << "deleted successfully!";
    }


}
bool Materiel::modfier_materiel(QVariant idMat)
{
    QString type = getTypeM();
     QString prix = getPrixM();
    QString quantite = getQuantiteM();
    QString idSalle = getIdSalle();
    QString quantiteEnd = getQuantiteENDOM();

    QSqlQuery query;
    query.prepare("UPDATE MATERIELS SET PRIX = :prix, TYPE = :type, QUANTITEM = :quantite, IDSALLE = :idSalle, QUANTITEENDOM = :quantiteEnd WHERE ID_MAT = :idMat");


    query.bindValue(":type", type);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":idSalle", idSalle);
    query.bindValue(":idMat", idMat);
    query.bindValue(":quantiteEnd", quantiteEnd);



    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }
    else
    {
    qDebug() << "Data inserted successfully!";
    return true;
    }
}
QSqlQueryModel * Materiel::afficher_materiel(const QString& searchQuery, const QString& sortOrder, const QString& sorttype)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QString queryStr = "select * from Materiels";

        if (!searchQuery.isEmpty()) {
            queryStr += " WHERE ID_MAT LIKE '%" + searchQuery + "%' OR "
                                 "TYPE LIKE '%" + searchQuery + "%' OR "
                                 "PRIX LIKE '%" + searchQuery + "%' OR "
                                 "QUANTITEM LIKE '%" + searchQuery + "%' OR "
                                 "IDSALLE LIKE '%" + searchQuery + "%' OR "
                                    "QUANTITEENDOM LIKE '%" + searchQuery + "%'";

        }


        if (!sortOrder.isEmpty() && !sorttype.isEmpty()) {
            queryStr += " ORDER BY "+ sorttype +" " + sortOrder;
            //qDebug() <<queryStr;
        }

        model->setQuery(queryStr);

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MAT"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDSALLE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("QUANTITEENDOM"));
        return model;
}












double Materiel::displayLossAndSumQuantity(QLineEdit *lineEditTotalLoss, QLineEdit *lineEditTotalQuantity)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    double totalLoss = 0.0;
    double totalQuantityEndom = 0.0;

    QString queryStr = "SELECT PRIX, QUANTITEENDOM FROM Materiels";
    model->setQuery(queryStr);

    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);
        double price = record.value("PRIX").toDouble();
        double quantityEndom = record.value("QUANTITEENDOM").toDouble();

        double lossForRow = price * quantityEndom;
        totalLoss += lossForRow;

        totalQuantityEndom += quantityEndom;
    }

    lineEditTotalLoss->setText(QString::number(totalLoss));
    lineEditTotalQuantity->setText(QString::number(totalQuantityEndom));

    delete model;
    qDebug() <<  totalLoss;
    return totalLoss;
}

void Materiel::commanderMateriel()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile("MatREMP.txt"));
    QUrl url("https://www.amazon.com");
            QDesktopServices::openUrl(url);
}

void Materiel::repairDamage(QString idsalle)
{
    QSqlQuery selectQuery;



        if (!idsalle.isEmpty()) {
            selectQuery.prepare("SELECT TYPE, QUANTITEENDOM FROM MATERIELS WHERE QUANTITEENDOM != 0 AND IDSALLE = :idsalle");
            selectQuery.bindValue(":idsalle", idsalle);
        }
        else {
           selectQuery.prepare("SELECT TYPE, QUANTITEENDOM FROM MATERIELS WHERE QUANTITEENDOM != 0");
       }
       /* if (selectQuery.exec()) {
            while (selectQuery.next()) {
                QString type = selectQuery.value(0).toString();
                int quantity = selectQuery.value(1).toInt();
                qDebug() << "Type:" << type << ", Quantity:" << quantity;
            }
        }*/
        QFile file("MatREMP.txt");

            // Open the file in write mode
            if (!file.open(QIODevice::Append | QIODevice::Text))
            {
                qDebug() << "Could not open file for writing";

            }

            // Create a QTextStream object with QFile as the device
            QTextStream out(&file);

       if (selectQuery.exec()) {
        while (selectQuery.next()) {
            qDebug() << selectQuery.value(0).toString()<<selectQuery.value(1).toString();
            out << selectQuery.value(0).toString() << " / ";
            out << selectQuery.value(1).toString() << "\n";
        }
       }
        // Close the file
        file.close();





    QSqlQuery updateQuery;

    if (idsalle.isEmpty()) {
        updateQuery.prepare("UPDATE MATERIELS SET QUANTITEM = QUANTITEM - QUANTITEENDOM, QUANTITEENDOM = 0 WHERE QUANTITEENDOM != 0");
    } else {
        updateQuery.prepare("UPDATE MATERIELS SET QUANTITEM = QUANTITEM - QUANTITEENDOM, QUANTITEENDOM = 0 WHERE IDSALLE = :idsalle");
        updateQuery.bindValue(":idsalle", idsalle);
    }

    if (!updateQuery.exec()) {
        qDebug() << "Error executing repairDamage query:" << updateQuery.lastError().text();
        return;
    }

    int affectedRows = updateQuery.numRowsAffected();
    qDebug() << "repairDamage: Successfully repaired" << affectedRows << "rows.";
}


void Materiel::evaluerDernierContrat(QString evaluerEvent)
{
    QSqlQuery query;
    double totalLoss = 0.0;

    query.prepare("SELECT ID_CONTRAT, ID_SALLE FROM EVENEMENT WHERE ID_EVENT = :idevent");
    query.bindValue(":idevent", evaluerEvent);

    if (!query.exec()) {
        qDebug() << "Error executing table events query:" << query.lastError().text();
        return;
    }

    if (query.first()) {
        QString contrat = query.value(0).toString();
        QString salle = query.value(1).toString();

        qDebug() << "ID_CONTRAT:" << contrat << ", ID_SALLE:" << salle;
//////////////////////////////////////////////EXTRACTION OF DECRIPTION
        QSqlQuery queryDescription;
        QSqlQuery queryValue;
        queryDescription.prepare("SELECT DESCRIPTION FROM CONTRAT WHERE ID_CONTRAT = :contrat");
        queryDescription.bindValue(":contrat", contrat);

////////////////////////////////////////////////////////////CALCUL VALEUR A PAYER
        queryValue.prepare("SELECT SUM(PRIX * QUANTITEENDOM) AS totalLoss FROM Materiels WHERE IDSALLE = :SALLE");
        queryValue.bindValue(":SALLE", salle);

        if (!queryValue.exec()) {
            qDebug() << "Error executing query to calculate total loss:" << queryValue.lastError().text();
            return;
        }

        if (queryValue.first()) {
            totalLoss = queryValue.value("totalLoss").toDouble();
            qDebug() << "Total Loss:" << totalLoss;
        } else {
            qDebug() << "No data found to calculate total loss.";
        }

        if (!queryDescription.exec()) {
            qDebug() << "Error executing description query:" << queryDescription.lastError().text();
            return;
        }

////////////////////////////repair damage for selected salle
        Materiel m;
        m.repairDamage(salle);


//////////////////////////////////////////////creation du nouvelle description
        while (queryDescription.next()) {
            QString description = queryDescription.value(0).toString();
            qDebug() << "Description:" << description;
            QString newDescription = " ";
            QString addedDescription = " Valeur a payer: " + QString::number(totalLoss);
            newDescription = description + addedDescription;
            qDebug() << "newDescription:" << newDescription;

/////////////////////////////////////////////////insertion du nouvelle description
            QSqlQuery queryUpdateDescription;
            queryUpdateDescription.prepare("UPDATE CONTRAT SET DESCRIPTION = :newDescription WHERE ID_CONTRAT = :contrat");
            queryUpdateDescription.bindValue(":newDescription", newDescription);
            queryUpdateDescription.bindValue(":contrat", contrat);

            if (!queryUpdateDescription.exec()) {
                qDebug() << "Error updating description in CONTRAT table:" << queryUpdateDescription.lastError().text();
                return;
            } else {
                qDebug() << "Description updated successfully in CONTRAT table.";
            }
        }
    } else {
        qDebug() << "No records found.";
    }



}
