#include "listeevents.h"
#include "listecontrats.h"
#include "listeartistes.h"
#include "listepersonnels.h"
#include "listesalles.h"
#include "listematriels.h"
#include "ui_listecontrats.h"
#include "contrats.h"
#include <QMessageBox>
#include <QtDebug>
#include <QModelIndexList>
#include <QSqlError>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QDate>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QTableView>
#include <QtSql>
#include <QByteArray>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "smtp.h"


using namespace QXlsx;

ListeContrats::ListeContrats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListeContrats)
{
    ui->setupUi(this);
    ui->tableView->setModel(c.afficher_contrat("","",""));
}

ListeContrats::~ListeContrats()
{
    delete ui;
}
void ListeContrats::setContratButtonStyle(const QString &style) {
    ui->contrats->setStyleSheet(style);
}
//************************Navigation contrats***************************************
void ListeContrats::on_AjoutCont_clicked()
{
    ui->actionswidgetContrats->setCurrentIndex(2);
    //les informations depuis artistes
    QSqlQuery query;
        if (query.exec("SELECT idartist FROM artiste")) {
            while (query.next()) {

                QString ida = query.value(0).toString();
                ui->lineEdit_9->addItem(ida);
            }
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }

}

void ListeContrats::on_StatsCont_clicked()
{
    ui->actionswidgetContrats->setCurrentIndex(3);
    MakePlot1();
}

void ListeContrats::on_retourcont1_clicked()
{
    ui->actionswidgetContrats->setCurrentIndex(0);
}

void ListeContrats::on_retourcont2_clicked()
{
    ui->actionswidgetContrats->setCurrentIndex(0);
    ui->dateEdit->clear();
    ui->dateEdit_2->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_2->clear();
}

void ListeContrats::on_employes_clicked()
{
    hide();
   ListePersonnels *persopage= new ListePersonnels(this);
   persopage->show();
   persopage->setPersoButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeContrats::on_artistes_clicked()
{
    hide();
    ListeArtistes *artistepage= new ListeArtistes(this);
    artistepage->show();
    artistepage->setArtisteButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeContrats::on_contrats_clicked()
{
    hide();
    ListeContrats *contratpage= new ListeContrats(this);
    contratpage->show();
    contratpage->setContratButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeContrats::on_events_clicked()
{
    hide();
    ListeEvents *eventpage= new ListeEvents(this);
    eventpage->show();
    eventpage->setEventsButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeContrats::on_matariel_clicked()
{
    hide();
    ListeMatriels *matpage= new ListeMatriels(this);
    matpage->show();
    matpage->setMatButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeContrats::on_salles_clicked()
{
    hide();
    ListeSalles *sallepage= new ListeSalles(this);
    sallepage->show();
        sallepage->setSalleButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeContrats::on_pushButton_18_clicked()
{
    bool isIntida;
    bool isvaleur;
    int id=0;
    QDate datedeb = ui->dateEdit->date();
    QDate datefin = ui->dateEdit_2->date();
    int ida = ui->lineEdit_9->currentText().toInt(&isIntida);
    qDebug() << "id artisdte "<<ida;
    int valeur = ui->lineEdit_11->text().toInt(&isvaleur);
    QString description =ui->lineEdit_2->text();
    //controle de saisie
    if( ui->lineEdit_9->currentText().isEmpty() || ui->lineEdit_11->text().isEmpty() || ui->lineEdit_2->text().isEmpty() )
    {
       return;
    }
    if (datedeb >= datefin) {
    QMessageBox::critical(this, "Error", "La date de début doit être antérieure à la date de fin.");
    return;
    }
    if (!isIntida) {
        QMessageBox::critical(this, "Erreur", "ID Artiste doit être un entier.");
        return;
    }
    if (!isvaleur) {
        QMessageBox::critical(this, "Erreur", "Valeur doit être un entier.");
        return;
    }
   // fin controle
   contrats c(id,valeur,datedeb,datefin,description,ida);
   bool test=c.ajouter_contrat();
   if(test)
   {
       ui->tableView->setModel(c.afficher_contrat("","",""));
       ui->dateEdit->clear();
       ui->dateEdit_2->clear();
       ui->lineEdit_9->clear();
       ui->lineEdit_11->clear();
       ui->lineEdit_2->clear();
       qDebug() << "Ajout succ";
        on_retourcont2_clicked();
   }
   else
   {
        qDebug() << "Ajout faild";
   }

}

void ListeContrats::on_pushButton_20_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idContratIndex = selectedIndexes.at(0);
    QVariant idc = idContratIndex .data(Qt::DisplayRole);
    int idContrat = idc.toInt();
    //qDebug() << "Supp succ id est "<<idContrat;
    bool test=c.supprimer_contrat(idContrat);
    if(test)
    {
        ui->tableView->setModel(c.afficher_contrat("","",""));
        qDebug() << "Supp succ";
    }
    else
    {
         qDebug() << "Supp faild";
    }

}


void ListeContrats::on_pushButton_21_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idContratIndex = selectedIndexes.at(0);
    QVariant idc = idContratIndex .data(Qt::DisplayRole);
    ui->actionswidgetContrats->setCurrentIndex(3);
    QSqlQuery query;
    query.prepare("SELECT * FROM contrat WHERE id_contrat = :idc");
    query.bindValue(":idc", idc);
    if (query.exec() && query.next()) {
        qDebug() <<query.value(0);
        qDebug() <<query.value(1);
        qDebug() <<query.value(2);
        qDebug() <<query.value(3);
        qDebug() <<query.value(4);
        qDebug() <<query.value(5);
        ui->lineEdit_id->setText(query.value(0).toString());
        ui->dateEdit_3->setDate(query.value(1).toDate());
        ui->dateEdit_4->setDate(query.value(2).toDate());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_13->setText(query.value(4).toString());
        ui->lineEdit_10->addItem(query.value(5).toString());

    }
   else {
           qDebug() << "Error fetching data:" << query.lastError().text();
       }
    //les informations depuis artistes
    QSqlQuery query1;
        if (query1.exec("SELECT idartist FROM artiste")) {
            while (query1.next()) {

                QString idaa = query1.value(0).toString();
                ui->lineEdit_10->addItem(idaa);
            }
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }

}

void ListeContrats::on_retourcont2_2_clicked()
{
    ui->actionswidgetContrats->setCurrentIndex(0);
    ui->lineEdit_id->clear();
    ui->dateEdit_3->clear();
    ui->dateEdit_4->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_10->clear();
}

void ListeContrats::on_pushButton_25_clicked()
{
    contrats ct;
    bool isIntida;
    bool isvaleur;
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idContratIndex = selectedIndexes.at(0);
    QVariant idc = idContratIndex .data(Qt::DisplayRole);

    ct.setidcontrat(ui->lineEdit_id->text().toInt());
    ct.setdatedeb(ui->dateEdit_3->date());
    ct.setdatefin(ui->dateEdit_4->date());
    ct.setvaleur(ui->lineEdit_13->text().toInt(&isvaleur));
    ct.setdescription(ui->lineEdit_3->text());
    ct.setidacontrat(ui->lineEdit_10->currentText().toInt(&isIntida));

    int id=ct.get_idcontrat();
    QDate datedeb=ct.get_datedeb();
    QDate datefin=ct.get_datefin();
    int valeur=ct.get_valeur();
    QString description=ct.get_description();
    int ida=ct.get_idacontrat();
    //controle de saisie
    if( ui->lineEdit_10->currentText().isEmpty() || ui->lineEdit_13->text().isEmpty() || ui->lineEdit_3->text().isEmpty() )
    {
       return;
    }
    if (datedeb >= datefin) {
    QMessageBox::critical(this, "Error", "La date de début doit être antérieure à la date de fin.");
    return;
    }
    if (!isIntida) {
        QMessageBox::critical(this, "Erreur", "ID Artiste doit être un entier.");
        return;
    }
    if (!isvaleur) {
        QMessageBox::critical(this, "Erreur", "Valeur doit être un entier.");
        return;
    }
   // fin controle
   ct.modfier_contrat(id,datedeb,datefin,valeur,ida,description);
   ui->actionswidgetContrats->setCurrentIndex(0);
   ui->tableView->setModel(c.afficher_contrat("","",""));
   ui->lineEdit_id->clear();
   ui->dateEdit_3->clear();
   ui->dateEdit_4->clear();
   ui->lineEdit_3->clear();
   ui->lineEdit_13->clear();
   ui->lineEdit_10->clear();

}
// tri et recherche
void ListeContrats::on_pushButton_13_clicked()
{
    QString sortOrder;
    if(ui->radioButton->isChecked())
    {
        sortOrder = "ASC";
    }
    else if (ui->radioButton_2->isChecked())
    {
        sortOrder = "DESC";
    }
    QString sorttype = ui->tritext->currentText();
    ui->tableView->setModel(c.afficher_contrat(ui->lineEdit->text(), sortOrder, sorttype));
}

void ListeContrats::on_pushButton_12_clicked()
{
    ui->tableView->setModel(c.afficher_contrat(ui->lineEdit->text(),"",""));
}

void ListeContrats::exportToPdf(const QString& filename, QTableView* tableView) {
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    QPainter painter;
    painter.begin(&printer);

    QImage Logo(":/src/another_logo.png");
      QImage backgroundImage(":/src/Design_sans_titre_2.png");

    // scaling background image
    double scaleX = printer.pageRect().width() / static_cast<double>(backgroundImage.width());
    double scaleY = printer.pageRect().height() / static_cast<double>(backgroundImage.height());
    double scaleFactor = qMax(scaleX, scaleY);
    // taille backg after scaling
    QSize scaledSize(scaleFactor * backgroundImage.width(), scaleFactor * backgroundImage.height());
    // Calculate the position to center the image on the page
    QPoint topLeft((printer.pageRect().width() - scaledSize.width()) / 2,
                   (printer.pageRect().height() - scaledSize.height()) / 2);


    painter.drawImage(QRect(topLeft, scaledSize), backgroundImage);

    //scaling table
    double xscale = printer.pageRect().width() / static_cast<double>(tableView->width());
    double yscale = printer.pageRect().height() / static_cast<double>(tableView->height());
    double scale = qMin(xscale, yscale);


    painter.translate(printer.paperRect().center());
    painter.scale(scale, scale);
    painter.translate(-tableView->width() / 2, -tableView->height() / 2);

    tableView->render(&painter);

    painter.end();
}

void ListeContrats::on_pushButton_16_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save PDF", "", ".pdf");
               if (!filename.isEmpty())
               {
                   exportToPdf(filename, ui->tableView);
               }
}

void ListeContrats::exportToExcel(const QString& filename, QTableView* tableView) {
    QXlsx::Document xlsx;
    QAbstractItemModel* model = tableView->model();

    QStringList headers;
    for (int column = 0; column < model->columnCount(); ++column) {
        QString columnName = model->headerData(column, Qt::Horizontal).toString();

    }
    for (int i = 0; i < headers.size(); ++i) {
        xlsx.write(1, i + 1, headers[i]);
    }

    // Add data rows
    for(int row = 0; row < model->rowCount(); ++row) {
        for(int column = 0; column < model->columnCount(); ++column) {
            QModelIndex index = model->index(row, column);
            QVariant data = model->data(index);

        }
    }

    xlsx.saveAs(filename);
}

void ListeContrats::on_pushButton_19_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Excel", "", ".xlsx");
        if (!filename.isEmpty())
        {

            exportToExcel(filename, ui->tableView);
        }
}

void ListeContrats::on_pushButton_36_clicked()
{
    ui->actionswidgetContrats->setCurrentIndex(1);
}

void ListeContrats::on_annulermail_clicked()
{
    ui->actionswidgetContrats->setCurrentIndex(0);
}

void ListeContrats::sendMail(QString email,QString message)
{
    Smtp* smtp = new Smtp("fatmazahra.boubakri099@gmail.com", "jypu wsje wjms wooh", "smtp.gmail.com", 465);
        smtp->sendMail("fatma.boubakri011@gmail.com", email ,"DarZmen",message);
}


void ListeContrats::on_pbEnvoiMail_2_clicked()
{
    Smtp* mail = new Smtp("fatmazahra.boubakri099@gmail.com", "jypu wsje wjms wooh", "smtp.gmail.com", 465);
     connect(mail,SIGNAL(status(QString)),this,SLOT(mailSent(QString)));
     QString email = ui->mailAdresseEmail_2->text();
     QString sujet = ui->mailSujet_2->text();
     QString message = ui->mailBody_2->text();
     if(email!="" && sujet!=""&& message!="" )
     {
         mail->sendMail("fatma.boubakri011@gmail.com",email,sujet,message);
     }

       QMessageBox::information(this, "DarZmen", "Mail envoyé", QMessageBox::Ok);
}

void ListeContrats::on_pushButton_35_clicked()
{
    QDate dateActuelle = QDate::currentDate();
    QString sqlQuery = "DELETE FROM CONTRAT WHERE DATE_FIN_CONTRAT < :dateActuelle";
    QSqlQuery query;
    query.prepare(sqlQuery);
    query.bindValue(":dateActuelle", dateActuelle);
    if (query.exec()) {
        qDebug() << "Suppression des contrats périmés réussie.";
    } else {
        qDebug() << "Échec de la suppression des contrats périmés:" << query.lastError().text();
    }
        QString searchQuery = "";
        QString sortOrder = "";
        QString sorttype = "";

        QSqlQueryModel *model = c.afficher_contrat(searchQuery, sortOrder, sorttype);

        // Mettre à jour le modèle de vue avec les nouvelles données
        ui->tableView->setModel(model);
}

void ListeContrats::MakePlot1()
{
        // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(255,255,255));
        gradient.setColorAt(0.38, QColor(255, 255, 255));
        gradient.setColorAt(1, QColor(255, 255, 255));
        ui->stats_widget->setBackground(QBrush(gradient));

        // create empty bar chart objects:

        QCPBars *fossil = new QCPBars(ui->stats_widget->xAxis, ui->stats_widget->yAxis);
        fossil->setAntialiased(false);
        fossil->setStackingGap(1);

        // set names and colors:
        fossil->setName("Nombres De Contrats Par Artiste");
        fossil->setPen(QPen(QColor(139, 0, 0).lighter(170)));
        fossil->setBrush(QColor(139, 0, 0));




        // prepare x axis with country labels:
        QVector<double> ticks;
        QVector<QString> labels;
        int i=0;
        QStringList uniqueTypes;
        QVector<double> quantitedata;


        //////////////////////////////////////////////////////////////////AXE DES X//////////////////////////////
            QString  queryStr = "SELECT DISTINCT id_artiste FROM contrat";
             QSqlQuery query(queryStr);
            int count = 0;
            while (query.next()) {
                QString type = query.value(0).toString();
                uniqueTypes << type;
                //qDebug() << type;
                count++;

                if (count == 10) {
                    break;
                }
            }
            for(i=0;i<uniqueTypes.size();i++)
            {
            ticks << i+1;
            }
        //////////////////////////////////////////////////////////////////AXE DES Y//////////////////////////////
            for (int i = 0; i < uniqueTypes.size(); ++i) {
                labels << uniqueTypes[i];
                qDebug() << uniqueTypes[i];

                QSqlQuery query;
                query.prepare("SELECT COUNT(id_contrat) FROM contrat WHERE id_artiste = :id_artiste");
                query.bindValue(":id_artiste", uniqueTypes[i]);

                if (query.exec() && query.next()) {
                    quantitedata << query.value(0).toDouble();
                } else {
                    qDebug() << "Error executing query:" << query.lastError().text();
                    // Handle the case where the query doesn't return any result or fails
                    // You can add a default value or handle it as needed
                    quantitedata << 0.0; // Default value
                }
            }


            /*for (i=0; i < uniqueTypes.size(); ++i) {
                labels << uniqueTypes[i];
                qDebug() << uniqueTypes[i];
                QString  queryStr;
                query.prepare ("SELECT QUANTITEM FROM MATERIELS WHERE TYPE = :type");
                query.bindValue(":type", uniqueTypes[i]);

                QSqlQuery query(queryStr);

                quantitedata<<query.value(0).toDouble();
            }*/

        //labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";


        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        ui->stats_widget->xAxis->setTicker(textTicker);
        ui->stats_widget->xAxis->setTickLabelRotation(60);
        ui->stats_widget->xAxis->setSubTicks(false);
        ui->stats_widget->xAxis->setTickLength(0, 4);
        ui->stats_widget->xAxis->setRange(0, 8);
        ui->stats_widget->xAxis->setBasePen(QPen(Qt::black));
        ui->stats_widget->xAxis->setTickPen(QPen(Qt::black));
        ui->stats_widget->xAxis->grid()->setVisible(true);
        ui->stats_widget->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        ui->stats_widget->xAxis->setTickLabelColor(Qt::black);
        ui->stats_widget->xAxis->setLabelColor(Qt::black);

        // prepare y axis:
        ui->stats_widget->yAxis->setRange(0, 30);
        ui->stats_widget->yAxis->setPadding(5); // a bit more space to the left border
        ui->stats_widget->yAxis->setLabel("Statistiques des contrats");
        ui->stats_widget->yAxis->setBasePen(QPen(Qt::black));
        ui->stats_widget->yAxis->setTickPen(QPen(Qt::black));
        ui->stats_widget->yAxis->setSubTickPen(QPen(Qt::black));
        ui->stats_widget->yAxis->grid()->setSubGridVisible(true);
        ui->stats_widget->yAxis->setTickLabelColor(Qt::black);
        ui->stats_widget->yAxis->setLabelColor(Qt::black);
        ui->stats_widget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        ui->stats_widget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // Add data:

        //quantitedata  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;

        fossil->setData(ticks, quantitedata);

        // setup legend:
        ui->stats_widget->legend->setVisible(true);
        ui->stats_widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        ui->stats_widget->legend->setBrush(QColor(255, 255, 255, 100));
        ui->stats_widget->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        ui->stats_widget->legend->setFont(legendFont);
        ui->stats_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
