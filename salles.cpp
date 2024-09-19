#include "salles.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDateTime>

salles::salles() {}

salles::salles(const QString& id, const QString& taille, const QString& prix)
    : id(id), taille(taille), prix(prix) {}

QString salles::getIdSalles() const {
    return id;
}

void salles::setIdSalles(const QString& id) {
    this->id = id;
}

QString salles::getTaille() const {
    return taille;
}

void salles::setTaille(const QString& taille) {
    this->taille = taille;
}

QString salles::getPrix() const {
    return prix;
}

void salles::setPrix(const QString& prix) {
    this->prix = prix;
}

void salles::enregistrerTraitement(QString id, QString taille, QString prix, const QString &type_traitement, const QString &emailResponsable)
{
    QSqlQuery query;

    // Enregistrer le traitement dans la table des traitements
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeStr = dateTime.toString("yyyy-MM-dd HH:mm:ss");

    query.prepare("INSERT INTO historique (id, taille, prix,type_traitement,date_heure_traitement, emailResponsable) "
                  "VALUES (:id, :taille, :prix, :type_traitement, :date_heure_traitement, :emailResponsable)");
    query.bindValue(":id", id);
    query.bindValue(":taille", taille);
    query.bindValue(":prix", prix);
    query.bindValue(":type_traitement", type_traitement);
    query.bindValue(":date_heure_traitement", dateTimeStr);
    query.bindValue(":email_responsable", emailResponsable);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'enregistrement du traitement:" << query.lastError().text();
        return;
    }
}

bool salles::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO salle (idsalle, taille, prix) VALUES (:id, :taille, :prix)");
    query.bindValue(":id", id);
    query.bindValue(":taille", taille);
    query.bindValue(":prix", prix);

    return query.exec();
}

bool salles::modifier(QString id, QString taille, QString prix) {
    QSqlQuery query;
    query.prepare("UPDATE salle SET taille = :taille, prix = :prix WHERE idsalle = :id");
    query.bindValue(":id", id);
    query.bindValue(":taille", taille);
    query.bindValue(":prix", prix);
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false; // Retourner false en cas d'erreur d'exécution de la requête
    } else {
        qDebug() << "Data updated successfully!";
        return true; // Retourner true si la requête s'exécute avec succès
    }
}


QSqlQueryModel* salles::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT idsalle, taille, prix, "
                       "CASE "
                       "  WHEN prix >= 0 AND prix < 100 THEN '1 Star' "
                       "  WHEN prix >= 100 AND prix < 200 THEN '2 Stars' "
                       "  WHEN prix >= 200 AND prix < 300 THEN '3 Stars' "
                       "  WHEN prix >= 300 AND prix < 400 THEN '4 Stars' "
                       "  WHEN prix >= 400 THEN '5 Stars' "

                       "END AS Rating "
                       "FROM salle";
    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Rating"));
    return model;
}

bool salles::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM salle WHERE idsalle = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error executing delete query:";
        return false;
    } else {
        qDebug() << "Entry with ID =" << id << " deleted successfully!";
        return true;
    }
}

QSqlQueryModel* salles::rechercher(const QString& searchString) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM salle WHERE idsalle LIKE :search";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":search", "%" + searchString + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* salles::trier(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM salle ORDER BY " + critere;
    model->setQuery(queryStr);
    return model;
}
