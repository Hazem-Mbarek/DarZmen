#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include <QDate>
#include <QImage>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCalendarWidget>
class Evenements
{
public:
    Evenements();
    Evenements(int,QDate,QDate,int,int,int,QImage,QString);
    void setIdevent(int id);
    void setNomevent(QString nomevent);
    void setDatedebutevent(const QDate& dated);
    void setDatefinevent(const QDate& datef);
    void setContratid(int idc);
    void setSalletid(int ids);
    void setNbrEmployes(int nbremp);
    void setQrcode(QImage qrcode);
    //
    int getIdevent();
    QString getNomevent();
    int getContratid();
    int getSalleid();
    int getNbrEmployes();
    QDate getDatedebutevent();
    QDate getDatefinevent();
    QImage getQrcode();
    //
    bool ajouter_event();
    //int ajouter_event();
    //QSqlQueryModel * afficher_events();
    QSqlQueryModel * afficher_events(const QString& searchQuery, const QString& sortOrder, const QString &sorttype);
    bool supprimer_event(int id);
    bool update_event(int id);
    void modfier_event(int id,QDate dated,QDate datef,int idc,int ids,int nbremp,QImage qrcode,QString nomevent);

private:
    int id;
    QString nomevent;
    int idc;
    int ids;
    int nbremp;
    QDate dated;
    QDate datef;
    QImage qrcode;

};

#endif // EVENEMENTS_H
