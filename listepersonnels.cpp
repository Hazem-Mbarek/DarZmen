#include "listeevents.h"
#include "listeevents.h"
#include "listecontrats.h"
#include "listeartistes.h"
#include "listepersonnels.h"
#include "listesalles.h"
#include "listematriels.h"
#include "ui_listepersonnels.h"
#include <QSqlRecord>
#include"employe.h"
#include <QtSql>
#include<QSqlQuery>
#include <QVariant>
#include<QMessageBox>
#include<Sms.h>
#include"smtp.h"
#include<QDate>
#include "imagedelegate.h"
#include <QIntValidator>
#include<QMessageBox>
#include <QIntValidator>
#include<QValidator>
#include <QRegularExpression>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

ListePersonnels::ListePersonnels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListePersonnels)
{
    employe E;
     ui->setupUi(this);
     ui->TabE->setModel(E.afficher());
     //QSqlQueryModel* model = E->afficher();
     //ui->TabE->setModel(model);
     ImageDelegate *imageDelegate = new ImageDelegate(this);
     ui->TabE->setItemDelegateForColumn(9, imageDelegate);


     int ret=A.connect_arduino(); //cnx à ard
     switch(ret)
     {
     case(0):
         qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
         break;
     case(1):
         qDebug() << "arduino is available but not connected to :"<<A.getarduino_port_name();
         break;
     case(-1):
         qDebug() << "arduino is not available";
         break;
     }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));



//****************************************************BOUTON RADIO "ADD"********************************************************************

     connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(onRadioButtonAddClicked()));
     connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(onRadioButtonAddClicked()));
     connect(ui->radioButton_3, SIGNAL(clicked()), this, SLOT(onRadioButtonAddClicked()));

//****************************************************BOUTON RADIO "UPDATE"******************************************************************

     connect(ui->radioButton_7, SIGNAL(clicked()), this, SLOT(onRadioButtonModifClicked()));
     connect(ui->radioButton_9, SIGNAL(clicked()), this, SLOT(onRadioButtonModifClicked()));
     connect(ui->radioButton_8, SIGNAL(clicked()), this, SLOT(onRadioButtonModifClicked()));
}



void ListePersonnels::update_label()
{
    employe e;
    data=A.read_from_arduino();
    if(data=="D")
        {

            if(e.rechercher(Mat.toInt()))
            {
                A.write_to_arduino("1");
            }
            else
            {
                A.write_to_arduino("0");
            }
            Mat.clear();
        }
        else
        {
            Mat=Mat+data;//acrementat
        }
        qDebug() << "Mat=" << Mat ;


       /* data2=b.read_from_arduino();
        if(e.rechercherE(Mat.toInt()))
        {
             b.write_to_arduino("1");
        }
        else
        {
            b.write_to_arduino("0");
        }*/
}
ListePersonnels::~ListePersonnels()
{
    delete ui;
}
void ListePersonnels::setPersoButtonStyle(const QString &style) {
    ui->employes->setStyleSheet(style);
}
//***************************************************************Navigation  menu**********************************************************************

void ListePersonnels::on_AjoutEmp_clicked() {ui->actionswidgetPers->setCurrentIndex(4);}
void ListePersonnels::on_StatsEmp_clicked() {ui->actionswidgetPers->setCurrentIndex(1);}
void ListePersonnels::on_retouremp1_clicked() {ui->actionswidgetPers->setCurrentIndex(0);}
void ListePersonnels::on_retouremp2_clicked() {ui->actionswidgetPers->setCurrentIndex(0);}
void ListePersonnels::on_retouremp2_3_clicked() {ui->actionswidgetPers->setCurrentIndex(0);}

void ListePersonnels::on_employes_clicked()
{
    hide();
    ListePersonnels *persopage= new ListePersonnels(this);
    persopage->show();
    persopage->setPersoButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListePersonnels::on_artistes_clicked()
{
    hide();
    ListeArtistes *artistepage= new ListeArtistes(this);
    artistepage->show();
    artistepage->setArtisteButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListePersonnels::on_contrats_clicked()
{
    hide();
    ListeContrats *contratpage= new ListeContrats(this);
    contratpage->show();
    contratpage->setContratButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListePersonnels::on_events_clicked()
{
    hide();
    ListeEvents *eventpage= new ListeEvents(this);
    eventpage->show();
    eventpage->setEventsButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListePersonnels::on_matariel_clicked()
{
    hide();
    ListeMatriels *matpage= new ListeMatriels(this);
    matpage->show();
    matpage->setMatButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListePersonnels::on_salles_clicked()
{
    hide();
    ListeSalles *sallepage= new ListeSalles(this);
    sallepage->show();
        sallepage->setSalleButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}











//**************************************************************CRUD***************************************************************************

QString ExperienceE ;
void ListePersonnels::onRadioButtonAddClicked()
{   if (ui->radioButton->isChecked())
       ExperienceE = "Debutant";
    else if (ui->radioButton_2->isChecked())
        ExperienceE = "Intermediaire";
    else if (ui->radioButton_3->isChecked())
      ExperienceE = "Expert";   }





void ListePersonnels::on_pbajout_clicked()
{
    employe E ;



    if (ui->matEa->text().isEmpty() || ui->le_nomEaj->text().isEmpty() || ui->le_prenE_aj->text().isEmpty() ||
    ui->le_mailE_aj->text().isEmpty() || ui->le_salE_aj->text().isEmpty()) {
    qDebug() << "Veuillez remplir tous les champs.";
    return;}


    QString MatriculeStr = ui->matEa->text();
    bool isInt;
    int Matricule = MatriculeStr.toInt(&isInt);
    if (!isInt || MatriculeStr.length() != 5) {qDebug() << "La matricule doit être composée uniquement de chiffres et doit etre 5 chiffres.";
    return;}


    QString NomE = ui->le_nomEaj->text();
    QString PrenomE = ui->le_prenE_aj->text();
    if (NomE.length() > 10 || PrenomE.length() > 10 || !NomE.contains(QRegExp("[a-zA-Z]+")) || !PrenomE.contains(QRegExp("[a-zA-Z]+"))) {
    qDebug() << "Le nom et le prénom doivent être des chaînes de caractères et ne doivent pas dépasser 10 caractères.";
    return;}


    QString MailE = ui->le_mailE_aj->text();
    if (!MailE.contains("@") || !MailE.contains(".") || MailE.indexOf("@") > MailE.lastIndexOf(".")) {qDebug() << "Le format de l'adresse email est incorrect.";
    return;}


    QString SalaireEStr = ui->le_salE_aj->text();
    int SalaireE = SalaireEStr.toInt(&isInt);
    if (!isInt || SalaireEStr.length() != 4) {qDebug() << "Le salaire doit être un entier et  doit etre 4 chiffres.";
    return;}


 E.setMatricule(ui->matEa->text().toInt());
 E.setNomE(ui->le_nomEaj->text());
 E.setPrenomE(ui->le_prenE_aj->text());
 E.setMailE(ui->le_mailE_aj->text());
 E.setServiceE(ui->le_serE_aj->currentText());
 E.setSalaireE(ui->le_salE_aj->text().toInt());
 E.setIdEventE(ui->le_salE_aj_2->text().toInt());
 E.setDateGardeE(ui->calendarWidget->selectedDate());
 E.setExperienceE(ExperienceE);
 //on_btnParcourir_clicked();

bool test=E.ajouter_Emp(ExperienceE,imageData);
    if(test){

        ui->matEa->clear();
        ui->le_nomEaj->clear();
        ui->le_prenE_aj->clear();
        ui->le_mailE_aj->clear();
        ui->le_serE_aj->clear();
        ui->le_salE_aj->clear();
        ui->le_salE_aj_2->clear();
        ui->TabE->setModel(E.afficher());
         qDebug()<<"add success";
        /* SMS sms;
                         QString to="+21655457575";
                         QString message="vous etes un client maintenant chez nous ! bienvenue";
                         sms.sendSms(to,message);*/
            }

    else{qDebug()<<"add failed";}




  // ui->TabE->setModel(E.afficher());



}







void ListePersonnels::on_pbsupp_clicked(){

    employe E;
    QModelIndexList selectedIndexes = ui->TabE->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
    qDebug() << "No row selected.";
    return; }

        QModelIndex idEmpIndex = selectedIndexes.at(0);
        QVariant idE = idEmpIndex.data(Qt::DisplayRole);
        int Matricule = idE.toInt();
        bool test=E.supprimer_Emp(Matricule);

    if(test){
        qDebug()<<"delete success";
        ui->TabE->setModel(E.afficher());
    }

    else{ qDebug()<<"delete failed"; }
}





void ListePersonnels::on_pbmodiff_clicked()
{

    QModelIndexList selectedIndexes = ui->TabE->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
            qDebug() << "No row selected.";
            return;
        }
        QModelIndex idEmpIndex = selectedIndexes.at(0);
        QVariant Matricule = idEmpIndex.data(Qt::DisplayRole);
        ui->actionswidgetPers->setCurrentIndex(5);

QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE MATRICULE= :Matricule");
    query.bindValue(":Matricule",Matricule);
    if (query.exec() && query.next()) {

        qDebug() <<query.value(0);
        qDebug() <<query.value(1);
        qDebug() <<query.value(2);
        qDebug() <<query.value(3);
        qDebug() <<query.value(4);
        qDebug() <<query.value(5);
        qDebug() <<query.value(6);
        qDebug() <<query.value(7);
        //qDebug() <<query.value(8);


       // QDate DateGardeE = ui->calendarWidget->selectedDate();


        ui->matEModif_2->setText(QString::number(query.value(0).toInt()));
        ui->nomEModif_2->setText(query.value(1).toString());
        ui->prenEModif_2->setText(query.value(2).toString());
        ui->mailEModif_2->setText(query.value(3).toString());
        ui->serEModif_2->setCurrentIndex(ui->serEModif_2->findText(query.value(4).toString()));
        ui->salEModif_2->setText(QString::number(query.value(5).toInt()));
        ui->le_salE_aj_3->setText(QString::number(query.value(7).toInt()));
        QDate date = query.value(8).toDate();
        ui->calendarWidget_3->setSelectedDate(date);





        QString ExperienceE = query.value(6).toString();
               if (ExperienceE == "Débutant")
                   ui->radioButton_7->setChecked(true);
               else if (ExperienceE == "Intermédiaire")
                   ui->radioButton_9->setChecked(true);
               else if (ExperienceE == "Expérimenté")
                   ui->radioButton_8->setChecked(true);


    } else { qDebug() << "Error fetching data:" << query.lastError().text(); }
}





void ListePersonnels::onRadioButtonModifClicked() {
    if (ui->radioButton_7->isChecked())
       ExperienceE = "Debutant";
    else if (ui->radioButton_9->isChecked())
        ExperienceE = "Intermediaire";
    else if (ui->radioButton_8->isChecked())
       ExperienceE = "Expert";
}




void ListePersonnels::on_pbmodiffC_2_clicked(){
    employe E;


    QModelIndexList selectedIndexes = ui->TabE->selectionModel()->selectedIndexes();

        if (selectedIndexes.isEmpty()) {
            qDebug() << "No row selected.";
            return;  }
        QModelIndex idEmpIndex = selectedIndexes.at(0);
        QVariant Matricule = idEmpIndex.data(Qt::DisplayRole);


       if (ui->matEModif_2->text().isEmpty() || ui->nomEModif_2->text().isEmpty() || ui->prenEModif_2->text().isEmpty() ||
               ui->mailEModif_2->text().isEmpty() || ui->salEModif_2->text().isEmpty())
        {qDebug() << "Veuillez remplir tous les champs.";
         return;  }

        QString NomE = ui->nomEModif_2->text();
        QString PrenomE = ui->prenEModif_2->text();
        if (NomE.length() > 10 || PrenomE.length() > 10 || !NomE.contains(QRegExp("[a-zA-Z]+")) || !PrenomE.contains(QRegExp("[a-zA-Z]+"))) {
            qDebug() << "Le nom et le prénom doivent être des chaînes de caractères et ne doivent pas dépasser 10 caractères.";
            return; }


        QString MailE = ui->mailEModif_2->text();
        if (!MailE.contains("@") || !MailE.contains(".") || MailE.indexOf("@") > MailE.lastIndexOf(".")) {
            qDebug() << "Le format de l'adresse email est incorrect.";
            return; }


        bool isInt;
        QString SalaireEStr = ui->salEModif_2->text();
        int SalaireE = SalaireEStr.toInt(&isInt);
        if (!isInt || SalaireEStr.length() != 4) {
            qDebug() << "Le salaire doit être un entier et  doit etre 4 chiffres.";
            return; }


    E.setNomE(ui->nomEModif_2->text());
    E.setPrenomE(ui->prenEModif_2->text());
    E.setMailE(ui->mailEModif_2->text());
    E.setServiceE(ui->serEModif_2->currentText());
    E.setSalaireE(ui->salEModif_2->text().toInt());
    E.setIdEventE(ui->le_salE_aj_3->text().toInt());
    E.setDateGardeE(ui->calendarWidget_3->selectedDate());
    E.setExperienceE(ExperienceE);



if(E.modifier_Emp(Matricule,ExperienceE)){


                  ui->matEModif_2->clear();
                  ui->nomEModif_2->clear();
                  ui->prenEModif_2->clear();
                  ui->mailEModif_2->clear();
                  ui->serEModif_2->clear();
                  ui->salEModif_2->clear();
                  ui->le_salE_aj_3->clear();
                  ui->TabE->setModel(E.afficher());
                  qDebug()<<"update success";
}
else{
qDebug()<<"update failed";
}
}














//********************************************************* LES METIERS ***********************************************




void ListePersonnels::on_search_button_2_clicked()
{
    employe E;
    int MatToSearch = ui->lineEdit_3->text().toInt();

    qDebug()<<"MatToSearch"<<MatToSearch;
    QSqlQueryModel* model = E.rechercherParIdd(ui->lineEdit_3->text());
    qDebug()<<"MatToSearch"<<MatToSearch;

        if (model->rowCount() > 0)
        {    qDebug()<<"MatToSearch"<<model;

            ui->TabE->setModel(model);
        }
        else
        {
            QMessageBox::information(this, "No Records", "No records found for the entered Matricule.");
        }

}



void ListePersonnels::on_pb_tri_clicked()
{
    QString critere;

    if (ui->tri_c->isChecked())
        critere = "ASC";
    else if (ui->tri_d->isChecked())
        critere = "DESC";
    else
    {
        qDebug() << "Please select a sorting order.";
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString query = "SELECT * FROM EMPLOYE ORDER BY NOM_E " + critere;

    // Execute
    model->setQuery(query);


    model->setHeaderData(0,Qt::Horizontal,QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_E"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_E"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL_E"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("SERVICE_E"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SALAIRE_E"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("EXPERIENCE_E"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EVENT"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_GARDE"));

    // Configure
    ui->TabE->setModel(model);
}






//pdf
void ListePersonnels::on_pdf_export_clicked(){
    employe E;
    E.pdfgenrateur();
}



//Stat

void ListePersonnels::on_anuulerStat_clicked(){ui->actionswidgetPers->setCurrentIndex(0);}
void ListePersonnels::on_stat_clicked(){ui->actionswidgetPers->setCurrentIndex(3);}
void ListePersonnels::on_stat_export_clicked()
{
    employe E;
    QChartView *chartView = E.capacite();
        chartView->show();
}




//Mailing

void ListePersonnels::on_pushButton_24_clicked() {ui->actionswidgetPers->setCurrentIndex(2);}
void ListePersonnels::on_annulermail_clicked() {ui->actionswidgetPers->setCurrentIndex(0);}
void ListePersonnels::sendMail(QString email,QString message)
{
 Smtp* smtp = new Smtp("fatmazahra.boubakri099@gmail.com", "jypu wsje wjms wooh", "smtp.gmail.com", 465);
    smtp->sendMail("fatma.boubakri011@gmail.com", email ,"DarZmen",message);
}

void ListePersonnels::on_pbEnvoiMail_2_clicked()
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








void ListePersonnels::on_pushButton_26_clicked() {ui->actionswidgetPers->setCurrentIndex(0);}

void ListePersonnels::on_pushButton_25_clicked() {ui->actionswidgetPers->setCurrentIndex(1);}

void ListePersonnels::on_notification_button_clicked()
{
    employe E;
    QDate selectedDate = ui->calendarWidget_2->selectedDate();

    QSqlQueryModel* model = E.rechercherParDate(selectedDate);

    if (model && model->rowCount() > 0)
    {
        QString employeN;
        for (int row = 0; row < model->rowCount(); ++row)
        {
            employeN += model->record(row).value("NOM_E").toString() + "\n";
        }

        QMessageBox::information(this, "employe ex "  + selectedDate.toString("yyyy-MM-dd"), employeN);



        /*SMS*/

     /* SMS sms;
                         QString to="+21695174074";
       //QString to="+21655457575";
                         QString message="vous avez un garde ! bienvenue";
                         sms.sendSms(to,message);*/

    }
    else
    {
        QMessageBox::information(this, "No emp", "No resources found for the selected date.");
    }
    delete model;
}










void ListePersonnels::on_btnParcourir_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir une image"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        QImage image(fileName);

        // Vous pouvez afficher l'image si nécessaire
        // ui->labelImage->setPixmap(QPixmap::fromImage(image));

        QByteArray byteArray;
        QBuffer buffer(&byteArray); // Correction ici
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG"); // Vous pouvez choisir un format différent si nécessaire


 imageData = byteArray;
    }
}






void ListePersonnels::exportToExcel(const QString& filename, QTableView* tableView) {

    QXlsx::Document xlsx;
    QAbstractItemModel* model = tableView->model();


    QStringList headers;
    int writeColumn = 1;
    for (int column = 0; column < model->columnCount(); ++column) {
        QString columnName = model->headerData(column, Qt::Horizontal).toString();
        if (columnName != "Qr code") {
            headers << columnName;
            xlsx.write(1, writeColumn++, columnName);
        }
    }


    for(int row = 0; row < model->rowCount(); ++row) {
        writeColumn = 1;
        for(int column = 0; column < model->columnCount(); ++column) {
            QString columnName = model->headerData(column, Qt::Horizontal).toString();

            QModelIndex index = model->index(row, column);
            QVariant data = model->data(index);

            if (data.type() == QVariant::ByteArray) {
                continue;
            }

            if (data.type() == QVariant::Date) {
                QDate date = data.toDate();
                QString dateString = date.toString("dd/MM/yyyy");
                xlsx.write(row + 2, writeColumn++, dateString);
            } else {
                xlsx.write(row + 2, writeColumn++, data.toString());
            }
        }
    }

    xlsx.saveAs(filename);
}



void ListePersonnels::on_pdf_button_5_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Excel", "", "*.xlsx");
        if (!filename.isEmpty())
        {
         exportToExcel(filename, ui->TabE);
        }
}




#include <QImage>
#include <QPainter>
#include <QPrinter>
#include <QDebug> // Si vous utilisez qDebug() pour le débogage


void ListePersonnels::exportToPdf_Client(const QString& filePath, QTableView* tableView)
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter;
    if (!painter.begin(&printer)) {
        // Gérer l'erreur de démarrage du QPainter
        return;
    }

    // Définir la couleur rouge bordeaux pour le texte et la bordure
    QColor bordoColor("#800020");

    // Créer un pinceau et une plume pour la décoration
    QBrush brush(Qt::lightGray);
    QPen pen(bordoColor);
    pen.setWidth(2);
    painter.setBrush(brush);
    painter.setPen(pen);

    // Dessiner un rectangle pour la décoration de fond
    QRect backgroundRect(0, 0, printer.width(), 100); // Hauteur de la décoration: 100 pixels
    painter.drawRect(backgroundRect);

    // Dessiner une ligne de bordure autour de la page
    QPen borderPen(bordoColor);
    borderPen.setWidth(5);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, printer.width(), printer.height());

    // Définir une police plus grande et artistique pour le titre
    QFont titleFont("Arial", 30, QFont::Bold); // Modifier la police et la taille selon votre préférence
    titleFont.setItalic(true); // Ajouter une italique à la police
    painter.setFont(titleFont);

    // Mesurer la largeur du texte du titre pour le centrer
    QString titleText = "DarZmen";
    QFontMetrics fm(titleFont);
    int titleWidth = fm.width(titleText);
    int titleX = (printer.width() - titleWidth) / 2; // Calculer la position horizontale pour centrer le titre
    int titleY = 150; // Position verticale du titre (ajustez selon vos besoins)

    painter.setPen(bordoColor); // Utiliser la couleur bordeaux pour le texte du titre
    painter.drawText(titleX, titleY, titleText);

    // Calculer la position pour dessiner le TableView au milieu de la page
    int tableWidth = tableView->width();
    int tableHeight = tableView->height();
    int x = (printer.width() - tableWidth) / 2;
    int y = (printer.height() - tableHeight) / 2;

    // Déplacer l'origine du QPainter pour dessiner le TableView au milieu de la page
    painter.translate(x, y);

    // Dessiner le TableView sur le QPainter
    tableView->render(&painter);
    qDebug() << "Reached exportToPdf() function.";

    painter.end();
}


void ListePersonnels::on_pbPDF_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");

        if (!filePath.isEmpty()) {
            exportToPdf_Client(filePath, ui->TabE);
        }
}






