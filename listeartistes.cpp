#include "listeevents.h"
#include "listecontrats.h"
#include "listeartistes.h"
#include "listepersonnels.h"
#include "listesalles.h"
#include "listematriels.h"
#include "ui_listeartistes.h"

#include"artiste.h"
#include <QtSql>
#include<QSqlQuery>
#include <QVariant>
#include<QMessageBox>
#include <QFileDialog>
#include "QMessageBox"
#include <QVBoxLayout>
#include <QtCharts>
#include <QPainter>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSlice>
#include <QChartView>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QWidget>
ListeArtistes::ListeArtistes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListeArtistes)
{
    artiste A;
    ui->setupUi(this);
    ui->tableView_2->setModel(A.afficher_Arti());
    connect(ui->exportToPdfButton, &QPushButton::clicked, this, &ListeArtistes::on_exportToPdfButton_clicked);


   /* // Initialisation de l'icône de plateau système
       QSystemTrayIcon trayIcon(this);
       trayIcon.setIcon(QIcon(":/src/articon.jpg"));
       trayIcon.setVisible(true);

       // Création du menu contextuel pour l'icône de plateau système
       trayMenu = new QMenu(this);
      QAction* showAction = new QAction("Show", this);
       connect(showAction, &QAction::triggered, this, &ListeArtistes::show);
       QAction* exitAction = new QAction("Exit", this);
       connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
       trayMenu->addAction(showAction);
       trayMenu->addAction(exitAction);
       trayIcon.setContextMenu(trayMenu);

       // Autres initialisations de l'interface utilisateur
       connect(ui->StatsArtis, &QPushButton::clicked, this, &ListeArtistes::on_stat_cl_clicked);*/


}

ListeArtistes::~ListeArtistes()
{
    delete ui;
    delete trayMenu;
   // delete trayIcon;
}
void ListeArtistes::setArtisteButtonStyle(const QString &style) {
    ui->artistes->setStyleSheet(style);
}

//************************Navigation Artistes menu***************************************

void ListeArtistes::on_AjoutA_clicked()
{
    ui->actionswidgetArt->setCurrentIndex(1);
}

void ListeArtistes::on_StatsA_clicked()
{
    ui->actionswidgetArt->setCurrentIndex(3);
}

void ListeArtistes::on_retourartiste2_clicked()
{
    ui->actionswidgetArt->setCurrentIndex(0);
}

void ListeArtistes::on_retourartiste2_2_clicked()
{
    ui->actionswidgetArt->setCurrentIndex(0);
}


void ListeArtistes::on_retourartiste1_clicked()
{
    ui->actionswidgetArt->setCurrentIndex(0);
}

void ListeArtistes::on_employes_clicked()
{
    hide();
    ListePersonnels *persopage= new ListePersonnels(this);
    persopage->show();
    persopage->setPersoButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeArtistes::on_artistes_clicked()
{
    hide();
    ListeArtistes *artistepage= new ListeArtistes(this);
    artistepage->show();
    artistepage->setArtisteButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");

}

void ListeArtistes::on_contrats_clicked()
{
    hide();
    ListeContrats *contratpage= new ListeContrats(this);
    contratpage->show();
    contratpage->setContratButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeArtistes::on_events_clicked()
{
    hide();
    ListeEvents *eventpage= new ListeEvents(this);
    eventpage->show();
    eventpage->setEventsButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeArtistes::on_matariel_clicked()
{
    hide();
    ListeMatriels *matpage= new ListeMatriels(this);
    matpage->show();
    matpage->setMatButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeArtistes::on_salles_clicked()
{
    hide();
    ListeSalles *sallepage= new ListeSalles(this);
    sallepage->show();
        sallepage->setSalleButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}
//**************************************************************CRUD***************************************************************************






void ListeArtistes::on_b_confajout_arti_clicked()
{
 artiste A ;
 A.setIdartist(ui->Idartist->text().toInt());
 A.setNomA(ui->NomA->text());
 A.setPrenomA(ui->PrenomA->text());
 A.setMailA(ui->MailA->text());
 A.setNtlfnA(ui->NtlfnA->text().toInt());
 A.setNblocA(ui->NblocA->text().toInt());

bool test=A.ajouter_Arti();
    if(test){


        ui->Idartist->clear();
        ui->NomA->clear();
        ui->PrenomA->clear();
        ui->MailA->clear();
        ui->NtlfnA->clear();
        ui->NblocA->clear();

         ui->tableView_2->setModel(A.afficher_Arti());

         qDebug()<<"add success";
         //trayIcon.showMessage("Artist Added", "The artist has been successfully added.", QSystemTrayIcon::Information, 50);



    }
    else{
         qDebug()<<"add failed";
    }
}







void ListeArtistes::on_pushButton_26_clicked(){

     artiste A;
    QModelIndexList selectedIndexes = ui->tableView_2->selectionModel()->selectedIndexes();
        if (selectedIndexes.isEmpty()) {
            qDebug() << "No row selected.";
            return;
        }
        QModelIndex Idartist = selectedIndexes.at(0);
        QVariant idA = Idartist.data(Qt::DisplayRole);
        int Idarti = idA.toInt();
        bool test=A.supprimer_Arti(Idarti);

    if(test){
        qDebug()<<"supp success";
        ui->tableView_2->setModel(A.afficher_Arti());
    }
    else{
         qDebug()<<"supp failed";
    }
}
















void ListeArtistes::on_pbmodifA_clicked()
{

    QModelIndexList selectedIndexes = ui->tableView_2->selectionModel()->selectedIndexes();
        if (selectedIndexes.isEmpty()) {
            qDebug() << "No row selected.";
            return;
        }
        QModelIndex idAIndex = selectedIndexes.at(0);
        QVariant Idartist = idAIndex.data(Qt::DisplayRole);
        ui->actionswidgetArt->setCurrentIndex(2);

QSqlQuery query;
    query.prepare("SELECT * FROM ARTISTE WHERE IDARTIST= :Idartist");
    query.bindValue(":Idartist",Idartist);
    if (query.exec() && query.next()) {

        qDebug() <<query.value(0);
        qDebug() <<query.value(1);
        qDebug() <<query.value(2);
        qDebug() <<query.value(3);
        qDebug() <<query.value(4);
        qDebug() <<query.value(5);




        ui->Idartist_2->setText(QString::number(query.value(0).toInt()));
         ui->NomA_2->setText(query.value(1).toString());
          ui->PrenomA_2->setText(query.value(2).toString());
           ui->MailA_2->setText(query.value(3).toString());
          ui->NtlfnA_2->setText(QString::number(query.value(4).toInt()));
            //ui->NtlfnA_2->setText(query.value(4).toString());
           ui->NblocA_2->setText(QString::number(query.value(5).toInt()));


    } else {
        qDebug() << "Error fetching data:" << query.lastError().text();
    }
}














void ListeArtistes::on_pbmodifCA_clicked(){
    artiste A;


    QModelIndexList selectedIndexes = ui->tableView_2->selectionModel()->selectedIndexes();

        if (selectedIndexes.isEmpty()) {
            qDebug() << "No row selected.";
            return;
        }
        QModelIndex idAIndex = selectedIndexes.at(0);
        QVariant Idartist = idAIndex.data(Qt::DisplayRole);

    A.setIdartist(ui->Idartist_2->text().toInt());
    A.setNomA(ui->NomA_2->text());
    A.setPrenomA(ui->PrenomA_2->text());
    A.setMailA(ui->MailA_2->text());

     A.setNtlfnA(ui->NtlfnA_2->text().toInt());
    A.setNblocA(ui->NblocA_2->text().toInt());




if(A.modifier_Arti(Idartist)){


                  ui->tableView_2->setModel(A.afficher_Arti());
                  qDebug()<<"update success";
}
else{
qDebug()<<"update failed";
}
}








void ListeArtistes::on_pb_trier_clicked()
{
    QString critere;

    if (ui->a->isChecked())
        critere = "ASC";
    else if (ui->d->isChecked())
        critere = "DESC";
    else
    {
        qDebug() << "Please select a sorting order.";
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString query = "SELECT * FROM ARTISTE ORDER BY NOMARTIST " + critere;

    // Execute
    model->setQuery(query);


    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDARTIST"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMARTIST"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMARTIST"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAILARTIST"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NTLFARTIST"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NLOC"));


    // Configure
    ui->tableView_2->setModel(model);
}






void ListeArtistes::on_search_buttonn_clicked()
{
    artiste a;
    int MatToSearch = ui->lineEdit_4->text().toInt();

    qDebug()<<"MatToSearch"<<MatToSearch;
    QSqlQueryModel* model = a.rechercher(ui->lineEdit_4->text());
    qDebug()<<"MatToSearch"<<MatToSearch;

        if (model->rowCount() > 0)
        {    qDebug()<<"MatToSearch"<<model;

            ui->tableView_2->setModel(model);
        }
        else
        {
            QMessageBox::information(this, "No Records", "No records found for the entered Matricule.");
        }

}


//pdf
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>

void ListeArtistes::drawModel(QPainter& painter, QSqlQueryModel* model) {
    QTextDocument doc;
    QString html = "<html><body><table border='1'>";

    // Header
    html += "<tr>";
    for (int col = 0; col < model->columnCount(); ++col) {
        html += QString("<th>%1</th>").arg(model->headerData(col, Qt::Horizontal).toString());
    }
    html += "</tr>";

    // Data
    for (int row = 0; row < model->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            html += QString("<td>%1</td>").arg(data);
        }
        html += "</tr>";
    }

    html += "</table></body></html>";
    doc.setHtml(html);
    doc.drawContents(&painter);
}

void ListeArtistes::exportToPDF(const QString& filePath, QSqlQueryModel* model) {
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter;
    painter.begin(&printer);

    drawModel(painter, model);

    painter.end();
}
void ListeArtistes::on_exportToPdfButton_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", "PDF Files (*.pdf)");
    if (!filePath.isEmpty()) {
        QSqlQueryModel *queryModel = qobject_cast<QSqlQueryModel*>(ui->tableView_2->model());
        if (queryModel) {
            exportToPDF(filePath, queryModel);
            QMessageBox::information(this, tr("Export PDF"), tr("PDF exported successfully."));
        } else {
            QMessageBox::warning(this, tr("Export PDF"), tr("Unable to export PDF: Invalid model type."));
        }
    }
}


void ListeArtistes::on_stat_cl_clicked()
{
    // Fetch data from the database
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT NOMARTIST, NLOC FROM ARTISTE");

    // Create a bar series and populate it with data
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    for (int i = 0; i < model->rowCount(); ++i) {
        QString Name = model->data(model->index(i, 0)).toString();
        int Nloc = model->data(model->index(i, 1)).toInt();

        QtCharts::QBarSet *set = new QtCharts::QBarSet(Name);
        *set << Nloc;
        series->append(set);
    }

    // Create a bar chart and add the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics on Number of Locations per artist");
    chart->setAnimationOptions(QtCharts::QChart::AllAnimations);

    // Create and configure the axes
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);

    // Create a chart view to display the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set up a new window to display the chart
    QDialog *chartDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    chartDialog->setLayout(layout);

    // Show the chart window
    chartDialog->exec();
}














/*


void ListeArtistes::notif()
{
    // Requête pour récupérer tous les équipements disponibles
    QSqlQuery query("SELECT NOMARTIST FROM ARTISTE WHERE NLOC = 0");

    QStringList equipementsEpuises; // Liste pour stocker les noms des équipements épuisés

    // Vérification de chaque équipement
    while (query.next()) {
        QString NomA = query.value(0).toString();
        equipementsEpuises.append(NomA);
    }

    // Vérification s'il y a des équipements épuisés
    if (!equipementsEpuises.isEmpty()) {
        // Construction du message de notification
        QString messageNotification = "Les équipements suivants sont épuisés :\n";
        messageNotification += equipementsEpuises.join(", ");

        // Envoyer la notification (par exemple, afficher dans une boîte de dialogue)
        QMessageBox::information(this, "nouveau artiste", messageNotification);
    }
}*/

void ListeArtistes::notif()
{
    qDebug() << "Notification called!"; // Affiche un message dans la console de débogage

    // Requête pour récupérer tous les artistes épuisés
    QSqlQuery query("SELECT NOMARTIST FROM ARTISTE WHERE NLOC = 0");

    QStringList artistesEpuises; // Liste pour stocker les noms des artistes épuisés

    // Vérification de chaque artiste
    while (query.next()) {
        QString NomA = query.value(0).toString();
        artistesEpuises.append(NomA);
    }

    // Vérification s'il y a des artistes épuisés
    if (!artistesEpuises.isEmpty()) {
        // Construction du message de notification
        QString messageNotification = "Les nouveaux artistes sont :\n";
        messageNotification += artistesEpuises.join(", ");

        // Afficher le message de notification dans la console de débogage
        qDebug() << messageNotification;

        // Envoyer la notification (par exemple, afficher dans une boîte de dialogue)
        QMessageBox::information(this, "Nouveaux artistes", messageNotification);
    }
}







void ListeArtistes::on_exportToPdfButton_2_clicked()
{
   notif();

}
