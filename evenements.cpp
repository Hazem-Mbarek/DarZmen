#include "evenements.h"
#include <QDate>
#include <QImage>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QBuffer>
#include <QDebug>
#include <QSqlError>

Evenements::Evenements()
{

    id=0;
    idc=0;
    dated = QDate::currentDate();
    datef = QDate::currentDate();
}
Evenements::Evenements(int id,QDate dated,QDate datef,int idc,int ids,int nbremp,QImage qrcode,QString nomevent)
{
    this->id=id;
    this->dated=dated;
    this->datef=datef;
    this->idc=idc;
    this->ids=ids;
    this->nbremp=nbremp;
    this->qrcode=qrcode;
    this->nomevent=nomevent;

}
void Evenements::setIdevent(int nvid){id=nvid;}
void Evenements::setNomevent(QString nvnomevent){nomevent=nvnomevent;}
void Evenements::setContratid(int nvidc){idc=nvidc;}
void Evenements::setSalletid(int nvids){ids=nvids;}
void Evenements::setDatedebutevent(const QDate &nvdated){dated=nvdated;}
void Evenements::setDatefinevent(const QDate &nvdatef){datef=nvdatef;}
void Evenements::setNbrEmployes(int nvnbremp){nbremp=nvnbremp;}
void Evenements::setQrcode(QImage nvqrcode){qrcode=nvqrcode;}
int Evenements::getIdevent(){return id;}
QString Evenements::getNomevent(){return nomevent;}
int Evenements::getContratid(){return idc;}
int Evenements::getSalleid(){return ids;}
int Evenements::getNbrEmployes(){return nbremp;}
QDate Evenements::getDatefinevent(){return datef;}
QDate Evenements::getDatedebutevent(){return dated;}
QImage Evenements::getQrcode(){return qrcode;}
//ajout CRUD
bool Evenements::ajouter_event()
{
    QSqlQuery query;
    /*query.prepare("INSERT INTO evenement (id_event, date_debut_event, date_fin_event, id_contrat, id_salle, nbr_emp, qrcode) "
                  "VALUES (:id, TO_DATE(:dated, 'YYYY-MM-DD'), TO_DATE(:datef, 'YYYY-MM-DD'), :idc, :ids, :nbremp, :qrcode)");*/
    query.prepare("INSERT INTO evenement ( date_debut_event, date_fin_event, id_contrat, id_salle, nbr_inv, qrcode,nomevent) "
                  "VALUES ( TO_DATE(:dated, 'YYYY-MM-DD'), TO_DATE(:datef, 'YYYY-MM-DD'), :idc, :ids, :nbremp, :qrcode, :nomevent)");
    //query.bindValue(":id", id);
    query.bindValue(":dated", dated.toString("yyyy-MM-dd"));
    query.bindValue(":datef", datef.toString("yyyy-MM-dd"));
    query.bindValue(":idc", idc);
    query.bindValue(":ids", ids);
    query.bindValue(":nbremp", nbremp);
    query.bindValue(":nomevent", nomevent);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    qrcode.save(&buffer, "PNG");
    query.bindValue(":qrcode", byteArray);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    return true;
}
/*int Evenements::ajouter_event()
{
    QSqlQuery query;
    query.prepare("INSERT INTO evenement ( date_debut_event, date_fin_event, id_contrat, id_salle, nbr_inv, qrcode,nomevent) "
                  "VALUES ( TO_DATE(:dated, 'YYYY-MM-DD'), TO_DATE(:datef, 'YYYY-MM-DD'), :idc, :ids, :nbremp, :qrcode, :nomevent)");

    query.bindValue(":dated", dated.toString("yyyy-MM-dd"));
    query.bindValue(":datef", datef.toString("yyyy-MM-dd"));
    query.bindValue(":idc", idc);
    query.bindValue(":ids", ids);
    query.bindValue(":nbremp", nbremp);
    query.bindValue(":nomevent", nomevent);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    qrcode.save(&buffer, "PNG");
    query.bindValue(":qrcode", byteArray);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return -1; // Return -1 to indicate failure
    }

    // Retrieve the last inserted ID
    QSqlQuery idQuery("SELECT EVENEMENT_SEQ.CURRVAL FROM dual");
    if (idQuery.exec() && idQuery.next()) {
        return idQuery.value(0).toInt(); // Return the last inserted ID
    } else {
        qDebug() << "Failed to retrieve last inserted ID.";
        return -1; // Return -1 if ID retrieval fails
    }
}*/

//Supp CRUD
bool Evenements::supprimer_event(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from evenement where id_event= :id");
    query.bindValue(":id",res);

    return query.exec();
}
//Afficher CRUD
class CustomQueryModel : public QSqlQueryModel
{
public:
    QVariant data(const QModelIndex &index, int role) const override
    {
        if (role == Qt::DecorationRole && index.column() == 6)
        {
            QByteArray byteArray = QSqlQueryModel::data(index, Qt::DisplayRole).toByteArray();
            QImage image;
            image.loadFromData(byteArray);
            return QPixmap::fromImage(image);
        }

        return QSqlQueryModel::data(index, role);
    }
};

/*QSqlQueryModel * Evenements::afficher_events()
{
    CustomQueryModel *model = new CustomQueryModel();
    model->setQuery("select * from evenement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Debut"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID Contrat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID Salle"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr employe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Qr code"));

    return model;
}*/

QSqlQueryModel *Evenements::afficher_events(const QString& searchQuery, const QString& sortOrder, const QString& sorttype)
{
    CustomQueryModel *model = new CustomQueryModel();
    QString queryStr = "SELECT * FROM evenement";

    if (!searchQuery.isEmpty()) {
        queryStr += " WHERE id_event LIKE '%" + searchQuery + "%' OR " +
                    "date_debut_event LIKE '%" + searchQuery + "%' OR " +
                    "date_fin_event LIKE '%" + searchQuery + "%' OR " +
                    "id_contrat LIKE '%" + searchQuery + "%' OR " +
                    "id_salle LIKE '%" + searchQuery + "%' OR " +
                    "nbr_inv LIKE '%" + searchQuery + "%' OR " +
                    "nomevent LIKE '%" + searchQuery + "%'";
     }


    if (!sortOrder.isEmpty() && !sorttype.isEmpty()) {
        queryStr += " ORDER BY "+ sorttype +" " + sortOrder;
        //qDebug() <<queryStr;
    }

    model->setQuery(queryStr);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Nom Event"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Debut"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID Contrat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID Salle"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr invités"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Qr code"));

    return model;
}

void Evenements::modfier_event(int id,QDate dated,QDate datef,int idc,int ids,int nbremp,QImage qrcode,QString nomevent)
{
    QSqlQuery query;
    query.prepare("UPDATE evenement SET date_debut_event = :dated, date_fin_event = :datef, id_contrat = :idc, id_salle = :ids, nbr_inv = :nbremp,nomevent =:nomevent,qrcode = :qrcode WHERE id_event = :id");
    query.bindValue(":dated",dated);
    query.bindValue(":datef",datef);
    query.bindValue(":idc",idc);
    query.bindValue(":ids",ids);
    query.bindValue(":nbremp",nbremp);
    query.bindValue(":nomevent", nomevent);
    query.bindValue(":id",id);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    qrcode.save(&buffer, "PNG");
    query.bindValue(":qrcode", byteArray);
    if (!query.exec()) {
                qDebug() << "Error executing query:" << query.lastError().text();
                return;
            }
    qDebug() << "Data inserted successfully!";
}
