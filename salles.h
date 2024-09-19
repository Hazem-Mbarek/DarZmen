#ifndef SALLES_H
#define SALLES_H

#include <QObject>
#include <QString>
#include <QSqlQueryModel>

class salles
{
private:
    QString id;
    QString taille;
    QString prix;

    void recordHistory(const QString& action, int id);

public:
    salles();
    salles(const QString& id, const QString& taille, const QString& prix);

    QString getIdSalles() const;
    void setIdSalles(const QString& id);

    QString getTaille() const;
    void setTaille(const QString& taille);

    QString getPrix() const;
    void setPrix(const QString& prix);

    bool ajouter();
    bool modifier(QString id, QString taille, QString prix);
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    QSqlQueryModel* rechercher(const QString& searchString);
    QSqlQueryModel* trier(const QString& critere);

    void enregistrerTraitement(QString id, QString taille, QString prix, const QString &type_traitement, const QString &emailResponsable);
};

#endif // SALLES_H
