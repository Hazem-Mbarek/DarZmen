#ifndef MATERIEL_H
#define MATERIEL_H
#include <QSqlQueryModel>
#include <QString>
#include <QVariant>
#include <QLineEdit>

class Materiel {
public:
    Materiel();

    QString getIdM();
    void setIdM(const QString& nvIdM);

    QString getIdSalle();
    void setIdSalle(const QString& nvIdSalle);

    QString getTypeM();
    void setTypeM(const QString& typeM);

    QString getQuantiteM();
    void setQuantiteM(const QString& nvQuantiteM);

    QString getQuantiteENDOM();
    void setQuantiteENDOM(const QString& nvQuantiteENDOM);

    QString getPrixM();
    void setPrixM(const QString& nvPrixM);

    bool ajouter_materiel();
    bool supprimer_materiel(QVariant id);
    bool modfier_materiel(QVariant idMat);
    QSqlQueryModel * afficher_materiel(const QString& searchQuery, const QString& sortOrder, const QString& sorttype);

    double displayLossAndSumQuantity(QLineEdit *lineEditTotalLoss, QLineEdit *lineEditTotalQuantity);
    void repairDamage(QString idsalle);
    void evaluerDernierContrat(QString evaluerEvent);
    void commanderMateriel();


private:
    QString IdM;
    QString IdSalle;
    QString TypeM;
    QString QuantiteM;
    QString PrixM;
    QString QuantiteENDOM;
};

#endif // MATERIEL_H
