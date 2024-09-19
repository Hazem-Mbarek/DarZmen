#include"employe.h"
#include"QSqlQuery"
#include <QDebug>
#include<QtSql>
#include <QSqlQueryModel>
#include <QMessageBox>

#include <QPainter>
#include <QPdfWriter>
#include <QStandardPaths>
#include <QDebug>
#include <QSqlRecord>
#include <QRegularExpression>
#include<QPageSize>

#include<QDate>
#include <QImage>
#include <QSqlQueryModel>
#include <QVariant>
#include <QSqlQuery>
#include <QPixmap>







employe::employe(){

}

int employe::getMatricule(){return Matricule;}
void employe::setMatricule(int nvMatricule){Matricule=nvMatricule;}

QString employe::getNomE(){return NomE;}
void employe::setNomE(QString nvNomE){NomE=nvNomE;}

QString employe::getPrenomE(){return PrenomE;}
void employe::setPrenomE(QString nvPrenomE){PrenomE=nvPrenomE;}

QString employe::getMailE(){return MailE;}
void employe::setMailE(QString nvMailE){MailE=nvMailE;}

QString employe::getServiceE(){return ServiceE;}
void employe::setServiceE(QString nvServiceE){ServiceE=nvServiceE;}

int employe::getSalaireE(){return SalaireE;}
void employe::setSalaireE(int nvSalaireE){SalaireE=nvSalaireE;}

QString employe::getExperienceE(){return ExperienceE;}
void employe::setExperienceE(QString nvExperienceE){ExperienceE=nvExperienceE;}

int employe::getIdEventE(){return IdEventE;}
void employe::setIdEventE(int nvIdEventE){IdEventE=nvIdEventE;}

QDate employe::getDateGardeE(){return DateGardeE;}
void employe::setDateGardeE(QDate nvDateGardeE){DateGardeE=nvDateGardeE;}

//***************************************************************CRUD*********************************************************************



bool employe::ajouter_Emp(const QString &ExperienceE, const QByteArray &imageData)
{
    int Matricule= getMatricule();
    QString NomE= getNomE();
    QString PrenomE= getPrenomE();
    QString MailE= getMailE();
    QString ServiceE= getServiceE();
    int SalaireE= getSalaireE();
    int IdEventE=getIdEventE();
    QDate DateGardeE=getDateGardeE();

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (MATRICULE,NOM_E,PRENOM_E,MAIL_E,SERVICE_E,SALAIRE_E,EXPERIENCE_E,ID_EVENT,DATE_GARDE,IMG)" " VALUES (:Matricule, :NomE, :PrenomE, :MailE, :ServiceE, :SalaireE, :ExperienceE, :IdEventE, :DateGardeE, :img)");

    query.bindValue(":Matricule", Matricule);
    query.bindValue(":NomE", NomE);
    query.bindValue(":PrenomE", PrenomE);
    query.bindValue(":MailE", MailE);
    query.bindValue(":ServiceE", ServiceE);
    query.bindValue(":SalaireE", SalaireE);
    query.bindValue(":ExperienceE", ExperienceE);
    query.bindValue(":IdEventE", IdEventE);
    query.bindValue(":DateGardeE", DateGardeE);
    query.bindValue(":img", imageData);



    return query.exec();
}





bool employe::supprimer_Emp(int Matricule)
{
        QSqlQuery query;
        QString res = QString::number(Matricule);
        query.prepare("Delete from EMPLOYE WHERE MATRICULE=:Matricule");
        query.bindValue(":Matricule", res);
        return query.exec();
}






bool employe::rechercher(int Matricule)
{
    QSqlQuery query;
    query.prepare("SELECT MATRICULE FROM EMPLOYE WHERE MATRICULE = :Matricule");
    query.bindValue(":Matricule", Matricule);
    if (query.exec() && query.next())
    {
        return true;
    }
    return false;// L'ID est unique
}




/*bool employe::rechercherE(int Matricule)
    {
        QSqlQuery query;
        query.prepare("SELECT experience FROM EMPLOYE WHERE MATRICULE = :Matricule AND EXPERIENCE_E LIKE '%expert%'");
        query.bindValue(":Matricule", Matricule);

        if (query.exec() && query.next())
        {
            return true;
        }
        return false;
    }*/



QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr = "select * from EMPLOYE";
    model->setQuery(queryStr);





    model->setHeaderData(0,Qt::Horizontal,QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_E"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_E"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL_E"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("SERVICE_E"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SALAIRE_E"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("EXPERIENCE_E"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EVENT"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_GARDE"));



    return model;

}





bool employe::modifier_Emp(QVariant Matricule,const QString &ExperienceE)
{

     QString PrenomE= getPrenomE();
     QString NomE= getNomE();
     QString MailE= getMailE();
     QString ServiceE= getServiceE();
     int SalaireE= getSalaireE();
     int IdEventE=getIdEventE();
     QDate DateGardeE=getDateGardeE();

     QSqlQuery query;
     query.prepare("UPDATE EMPLOYE SET NOM_E= :NomE,PRENOM_E= :PrenomE,MAIL_E= :MailE,SERVICE_E= :ServiceE,SALAIRE_E= :SalaireE,EXPERIENCE_E= :ExperienceE,ID_EVENT= :IdEventE,DATE_GARDE= :DateGardeE  WHERE MATRICULE= :Matricule");

     query.bindValue(":Matricule", Matricule);
     query.bindValue(":NomE", NomE);
     query.bindValue(":PrenomE", PrenomE);
     query.bindValue(":MailE", MailE);
     query.bindValue(":ServiceE", ServiceE);
     query.bindValue(":SalaireE", SalaireE);
     query.bindValue(":ExperienceE", ExperienceE);
     query.bindValue(":IdEventE", IdEventE);
     query.bindValue(":DateGardeE", DateGardeE);

     return query.exec();
}












//*******************************************************LES METIERS***********************************************************************




QSqlQueryModel* employe::rechercherParIdd(QString Matricule) {
    QSqlQueryModel* modal = new QSqlQueryModel();

    QString queryString = "SELECT * FROM EMPLOYE WHERE MATRICULE = '" + Matricule + "'";



    qDebug() << "Query string: " << queryString;

    // Execute
    modal->setQuery(queryString);

    // Check for errors
    if (modal->lastError().isValid()) {
        qDebug() << "Query error: " << modal->lastError().text();
    } else {
        qDebug() << "Query successful.";

        for (int row = 0; row < modal->rowCount(); ++row) {
            QString resultString; //cont val tt lign
            for (int col = 0; col < modal->columnCount(); ++col) {
                resultString += modal->data(modal->index(row, col)).toString() + " | ";//récupère la valeur
            }
            qDebug() << "Result " << row + 1 << ": " << resultString;
        }
    }

    return modal;
}







/*void employe::pdfgenrateur()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE");

    if (query.exec())
    {
        QPdfWriter pdfWriter("employes.pdf");
        QPainter painter(&pdfWriter);
        QTextDocument doc;
        QTextOption option(Qt::AlignLeft);

        QFont font("Arial", 100);
        doc.setDefaultFont(font);

        doc.setDocumentMargin(90);

        QString employesHtml;

        while (query.next())
        {
            QString nomEmploye = query.value("NOM_E").toString();
            QString prenomEmploye = query.value("PRENOM_E").toString();
            QString mailEmploye = query.value("MAIL_E").toString();
            QString serviceEmploye = query.value("SERVICE_E").toString();
            QString salaireEmploye = query.value("SALAIRE_E").toString();
            QString experienceEmploye = query.value("EXPERIENCE_E").toString();
            QString idEventEmploye = query.value("ID_EVENT").toString();
            QString DateGardeEmploye = query.value("DATE_GARDE").toString();

            QString employeHtml = "<h1>Employe: " + nomEmploye + " " + prenomEmploye + "</h1>";
            employeHtml += "<p><strong>Nom: </strong>" + nomEmploye + "</p>";
            employeHtml += "<p><strong>Prénom: </strong>" + prenomEmploye + "</p>";
            employeHtml += "<p><strong>Mail: </strong>" + mailEmploye + "</p>";
            employeHtml += "<p><strong>Service: </strong>" + serviceEmploye + "</p>";
            employeHtml += "<p><strong>Salaire: </strong>" + salaireEmploye + "</p>";
            employeHtml += "<p><strong>Experience: </strong>" + experienceEmploye + "</p>";
            employeHtml += "<p><strong>IdEvent: </strong>" + idEventEmploye + "</p>";
            employeHtml += "<p><strong>Dategarde: </strong>" + DateGardeEmploye + "</p>";

            employesHtml += employeHtml;
        }

        doc.setHtml(employesHtml);
        doc.setDefaultTextOption(option);


        QRectF rect(0, 0, pdfWriter.width(), pdfWriter.height());
        doc.drawContents(&painter, rect);
    }
    else
    {
        qDebug() << "Error generating report: " << query.lastError();
    }
}*/


void employe::pdfgenrateur()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE");

    if (query.exec())
    {
        QPdfWriter pdfWriter("employes.pdf");
        QPainter painter(&pdfWriter);
        QTextDocument doc;
        QTextOption option(Qt::AlignLeft);

        QFont font("Arial", 100);
        doc.setDefaultFont(font);

        doc.setDocumentMargin(90);

        QString employesHtml;

        while (query.next())
        {
            QString nomEmploye = query.value("NOM_E").toString();
            QString prenomEmploye = query.value("PRENOM_E").toString();
            QString mailEmploye = query.value("MAIL_E").toString();
            QString serviceEmploye = query.value("SERVICE_E").toString();
            QString salaireEmploye = query.value("SALAIRE_E").toString();
            QString experienceEmploye = query.value("EXPERIENCE_E").toString();
            QString idEventEmploye = query.value("ID_EVENT").toString();
            QString DateGardeEmploye = query.value("DATE_GARDE").toString();

            // Style du nom de l'employé en rouge bordeaux
            QString employeHtml = "<h1><font color=\"#800020\">Employe: " + nomEmploye + " " + prenomEmploye + "</font></h1>";
            employeHtml += "<p><strong>Nom: </strong>" + nomEmploye + "</p>";
            employeHtml += "<p><strong>Prénom: </strong>" + prenomEmploye + "</p>";
            employeHtml += "<p><strong>Mail: </strong>" + mailEmploye + "</p>";
            employeHtml += "<p><strong>Service: </strong>" + serviceEmploye + "</p>";
            employeHtml += "<p><strong>Salaire: </strong>" + salaireEmploye + "</p>";
            employeHtml += "<p><strong>Experience: </strong>" + experienceEmploye + "</p>";
            employeHtml += "<p><strong>IdEvent: </strong>" + idEventEmploye + "</p>";
            employeHtml += "<p><strong>Dategarde: </strong>" + DateGardeEmploye + "</p>";

            // Ajouter un espace supplémentaire entre les sections d'employé
            employeHtml += "<br><br>";

            employesHtml += employeHtml;
        }

        doc.setHtml(employesHtml);
        doc.setDefaultTextOption(option);

        // Dessiner une bordure plus large en rouge bordeaux
        painter.setPen(QPen(QColor("#800020"), 10)); // Largeur de bordure de 10 pixels
        painter.drawRect(0, 0, pdfWriter.width(), pdfWriter.height());

        QRectF rect(0, 0, pdfWriter.width(), pdfWriter.height());
        doc.drawContents(&painter, rect);
    }
    else
    {
        qDebug() << "Error generating report: " << query.lastError();
    }
}



/*void employe::pdfgenrateur()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE");

    if (query.exec())
    {
        QPdfWriter pdfWriter("employes.pdf");
        QPainter painter(&pdfWriter);
        QTextDocument doc;
        QTextOption option(Qt::AlignLeft);

        QFont font("Arial", 100);
        doc.setDefaultFont(font);

        doc.setDocumentMargin(90);

        QString employesHtml;

        while (query.next())
        {
            QString nomEmploye = query.value("NOM_E").toString();
            QString prenomEmploye = query.value("PRENOM_E").toString();
            QString mailEmploye = query.value("MAIL_E").toString();
            QString serviceEmploye = query.value("SERVICE_E").toString();
            QString salaireEmploye = query.value("SALAIRE_E").toString();
            QString experienceEmploye = query.value("EXPERIENCE_E").toString();
            QString idEventEmploye = query.value("ID_EVENT").toString();
            QString DateGardeEmploye = query.value("DATE_GARDE").toString();

            QString employeHtml = "<h1>Employe: " + nomEmploye + " " + prenomEmploye + "</h1>";
            employeHtml += "<p><strong>Nom: </strong>" + nomEmploye + "</p>";
            employeHtml += "<p><strong>Prénom: </strong>" + prenomEmploye + "</p>";
            employeHtml += "<p><strong>Mail: </strong>" + mailEmploye + "</p>";
            employeHtml += "<p><strong>Service: </strong>" + serviceEmploye + "</p>";
            employeHtml += "<p><strong>Salaire: </strong>" + salaireEmploye + "</p>";
            employeHtml += "<p><strong>Experience: </strong>" + experienceEmploye + "</p>";
            employeHtml += "<p><strong>IdEvent: </strong>" + idEventEmploye + "</p>";
            employeHtml += "<p><strong>Dategarde: </strong>" + DateGardeEmploye + "</p>";

            employesHtml += employeHtml;
        }

        doc.setHtml(employesHtml);
        doc.setDefaultTextOption(option);

        // Dessiner la décoration de fond
        painter.save();
        painter.setBrush(Qt::lightGray);
        painter.drawRect(0, 0, pdfWriter.width(), pdfWriter.height());
        painter.restore();

        // Dessiner le titre "Darzmen" au milieu en haut avec une écriture artistique
        painter.save();
        painter.setFont(QFont("Garamond", 40, QFont::Bold));
        painter.setPen(Qt::black); // Couleur du texte
        QRect titleRect = QRect(0, 100, pdfWriter.width(), 30); // Rectangle pour le titre
        painter.drawText(titleRect, Qt::AlignCenter, "Darzmen");
        painter.restore();

        QRectF rect(0, 0, pdfWriter.width(), pdfWriter.height());
        doc.drawContents(&painter, rect);
    }
    else
    {
        qDebug() << "Error generating report: " << query.lastError();
    }
}
*/






QChartView* employe::capacite()
{
    int Debutant = 0;
    int Intermediaire = 0;
    int Expert = 0;

    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE EXPERIENCE_E = 'Debutant'");
    query.exec();

    while (query.next())
        Debutant++;

    query.prepare("SELECT * FROM EMPLOYE WHERE EXPERIENCE_E = 'Intermediaire'");
    query.exec();

    while (query.next())
        Intermediaire++;

    query.prepare("SELECT * FROM EMPLOYE WHERE EXPERIENCE_E = 'Expert'");
    query.exec();

    while (query.next())
        Expert++;

    qDebug() << "Debutant:" << Debutant << ", Intermediaire:" << Intermediaire << ", Expert:" << Expert;

    QPieSeries *series = new QPieSeries();
    series->append("Debutant", Debutant);
    series->append("Intermediaire", Intermediaire);
    series->append("Expert", Expert);

    series->slices().at(0)->setColor("#f37b78");
    series->slices().at(1)->setColor("#663333");
    series->slices().at(2)->setColor("#cccccc");

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique de l'experience des employes");

    series->setLabelsVisible();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    chartView->resize(1000, 500);

    return chartView;
}







QSqlQueryModel* employe::rechercherParDate(const QDate& date)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE DATE_GARDE = :DATE_GARDE");
    query.bindValue(":DATE_GARDE", date);

    if (query.exec())
    {
        // Set the query model with the result
        model->setQuery(query);
        return model;
    }
    else
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        delete model;
        return nullptr;
    }
}

























