#include "listeevents.h"
#include "listecontrats.h"
#include "listeartistes.h"
#include "listepersonnels.h"
#include "listesalles.h"
#include "listematriels.h"
#include "ui_listeevents.h"
#include "evenements.h"
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
#include <QByteArray>
#include "QZXing.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QFile>
#include <QIODevice>
#include <QAbstractItemModel>
#include <QTableView>
#include <QtCharts>
#include <QPainter>
#include <QPrinter>
#include <QFileInfo>
#include <QImageReader>
#include <QPdfWriter>
#include <QProcess>
using namespace QXlsx;
QT_CHARTS_USE_NAMESPACE
ListeEvents::ListeEvents(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListeEvents)
{
    ui->setupUi(this);
    ui->tableView_4->setModel(E.afficher_events("","",""));
    // Start connection to Arduino
    int ret = A.connect_arduino();
    switch (ret) {
        case 0: qDebug() << "Arduino is available and connected to: " << A.getarduino_port_name();
            break;
        case 1: qDebug() << "Arduino is available but not connected to: " << A.getarduino_port_name();
            break;
        case -1: qDebug() << "Arduino is not available";
            break;
    }
    //updateLabell();
    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(updateLabell()));
    //QObject::connect(A.getserial(), &QSerialPort::readyRead, this, &ListeEvents::updateLabell());


}

ListeEvents::~ListeEvents()
{
    delete ui;
}
void ListeEvents::setEventsButtonStyle(const QString &style) {
    ui->events->setStyleSheet(style);
}
//************************Navigation events menu***************************************
void ListeEvents::on_stats_events_4_clicked()
{
    ui->actionswidgetEvents->setCurrentIndex(1);
    int i1=getEventsWithDeadlineOver();
    QString i11=QString::number(i1);
    int i2=getEventsDuringCurrentWeek();
    QString i12=QString::number(i2);
    int i3=getEventsDuringCurrentMonth();
    QString i13=QString::number(i3);
    ui->lineEdit_20->setText(i11);
    ui->lineEdit_19->setText(i12);
    ui->lineEdit_21->setText(i13);
    MakePlot1();
    createPieChart();
}
void ListeEvents::on_add_events_4_clicked()
{
    ui->actionswidgetEvents->setCurrentIndex(3);
    //les informations depuis contrats
    QSqlQuery query;
    if (query.exec("SELECT id_contrat, id_artiste FROM contrat")) {
        while (query.next()) {

            QString idContrat = query.value(0).toString();
            QString idArtiste = query.value(1).toString();
            QString item = "Id contrat est "+idContrat + " - " +"Id Artiste est "+idArtiste;
            ui->lineEdit_9->addItem(item);
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
    //les informations depuis Salles
   /* QSqlQuery query1;
    if (query1.exec("SELECT * FROM salle")) {
        while (query1.next()) {

            QString idSalle = query1.value(0).toString();
            QString taillesalle = query1.value(1).toString();
            QString prixsalle = query1.value(2).toString();//+" - "+"Le prix est "+prixsalle
            QString item = "Id salle est "+idSalle + " - " +"La taille est "+taillesalle;
            ui->lineEdit_12->addItem(item);
        }
    } else {
        qDebug() << "Failed to execute query:" << query1.lastError().text();
    }*/
}
void ListeEvents::on_retourevents2_clicked()
{
    ui->actionswidgetEvents->setCurrentIndex(0);
    ui->dateTimeEdit_5->clear();
    ui->dateTimeEdit_6->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_12->clear();
    //ui->lineEdit_11->clear();
    ui->label_21->clear();
    ui->lineEdit_18->clear();
}
//************************menu nav****************************************
void ListeEvents::on_employes_clicked()
{
    hide();
    ListePersonnels *persopage= new ListePersonnels(this);
    persopage->show();
    persopage->setPersoButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeEvents::on_artistes_clicked()
{
    hide();
    ListeArtistes *artistepage= new ListeArtistes(this);
    artistepage->show();
    artistepage->setArtisteButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeEvents::on_contrats_clicked()
{
    hide();
    ListeContrats *contratpage= new ListeContrats(this);
    contratpage->show();
    contratpage->setContratButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeEvents::on_events_clicked()
{
    hide();
    ListeEvents *eventpage= new ListeEvents(this);
    eventpage->show();
    eventpage->setEventsButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeEvents::on_matariel_clicked()
{
    hide();
    ListeMatriels *matpage= new ListeMatriels(this);
    matpage->show();
    matpage->setMatButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeEvents::on_salles_clicked()
{
    hide();
    ListeSalles *sallepage= new ListeSalles(this);
    sallepage->show();
    sallepage->setSalleButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}




void ListeEvents::on_pushButton_36_clicked()
{
    bool isIntidc;
    bool isIntids;
    bool isIntnbr;
    int id = 0;
    //int newEventID = 0;
    QDate dated = ui->dateTimeEdit_5->date();
    QDate datef = ui->dateTimeEdit_6->date();
    QString currentText = ui->lineEdit_9->currentText();
    QStringList parts = currentText.split("Id contrat est ");
    QString idContratText = parts[1].split(" - ")[0];
    int idc = idContratText.toInt(&isIntidc);
    QString currentText2 = ui->lineEdit_12->currentText();
    QStringList parts2 = currentText2.split("Id salle est ");
    if (parts2.size() < 2) {
        QMessageBox::critical(this, "Error", "ID salle introuvable.");
        return;
    }
    QString idsalleText = parts2[1].split(" - ")[0];
    int ids = idsalleText.toInt(&isIntids);
    int nbremp = ui->lineEdit_11->text().toInt(&isIntnbr);
    QString nomevent = ui->lineEdit_18->text();

    //controle de saisie
    if (nomevent.isEmpty() || ui->lineEdit_11->text().isEmpty())
    {
        return;
    }
    if (dated >= datef) {
        QMessageBox::critical(this, "Error", "La date de début doit être antérieure à la date de fin.");
        return;
    }
    if (nomevent.isEmpty() || !nomevent.at(0).isUpper() || !nomevent.contains(QRegExp("^[A-Za-z]+$"))) {
        QMessageBox::critical(this, "Error", "Nomevent doit commencer par une lettre majuscule et contenir uniquement des caractères alphabétiques");
        return;
    }
    if (!isIntidc) {
        QMessageBox::critical(this, "Erreur", "ID Contrat doit être un entier.");
        return;
    }
    if (!isIntids) {
        QMessageBox::critical(this, "Erreur", "ID Salle doit être un entier.");
        return;
    }
    if (!isIntnbr) {
        QMessageBox::critical(this, "Erreur", "Nombre des employes doit être un entier.");
        return;
    }
    const QPixmap *pixmapPtr = ui->label_21->pixmap();
    if (!pixmapPtr) {
        QMessageBox::critical(this, "Error", "No Qrcode found ");
        return;
    }
    // fin controle
    /*QSqlQuery query;
    query.prepare("SELECT id_event FROM (SELECT id_event FROM evenement ORDER BY id_event DESC) WHERE ROWNUM = 1");
    if (query.exec() && query.next()) {
        int lastEventID = query.value(0).toInt();
        qDebug() << "the last id est " << lastEventID;
        newEventID = lastEventID + 1;
    }*/
    QString eventInfo = QString("Bonjour monsieur,madame,\nVous êtes invité à participer à l'événement %1 du %2 jusqu'au %3 dans la salle %4.\nMerci, nous attendons votre présence.")
            .arg(ui->lineEdit_18->text())
            .arg(ui->dateTimeEdit_5->date().toString("dd/MM/yyyy"))
            .arg(ui->dateTimeEdit_6->date().toString("dd/MM/yyyy"))
            .arg(ids);

    QZXing encoder;
    QZXingEncoderConfig config;
    QImage qrcode = encoder.encodeData(eventInfo, config);


    int whiteBackgroundSize = qrcode.width() + 40;


    QImage whiteBackground(whiteBackgroundSize, whiteBackgroundSize, QImage::Format_RGB32);
    whiteBackground.fill(Qt::white);


    int qrCodeX = (whiteBackground.width() - qrcode.width()) / 2;
    int qrCodeY = (whiteBackground.height() - qrcode.height()) / 2;


    QPainter painter(&whiteBackground);
    painter.drawImage(qrCodeX, qrCodeY, qrcode);


    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Save QR Code Image"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directoryPath.isEmpty()) {
        QString filePath = QDir(directoryPath).filePath(nomevent + ".png");
        if (whiteBackground.save(filePath)) {
            qDebug() << "QR Code image saved successfully with white space border.";
        } else {
            qDebug() << "Failed to save QR Code image with white space border.";
        }
    } else {
        qDebug() << "Directory path is empty. QR Code image not saved.";
    }

    ui->label_21->setPixmap(QPixmap::fromImage(whiteBackground));

    Evenements E(id, dated, datef, idc, ids, nbremp, qrcode, nomevent);
    bool test = E.ajouter_event();
    if (test)
    {
        ui->tableView_4->setModel(E.afficher_events("","",""));
        //ui->lineEdit_10->clear();
        ui->dateTimeEdit_5->clear();
        ui->dateTimeEdit_6->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_11->clear();
        ui->label_21->clear();
        ui->lineEdit_18->clear();
        qDebug() << "Ajout succ";
    }
    else
    {
        qDebug() << "Ajout faild";
    }
    on_retourevents2_clicked();
}



void ListeEvents::on_delete_button_4_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_4->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idEventIndex = selectedIndexes.at(0);
    QVariant idE = idEventIndex.data(Qt::DisplayRole);
    int idEvent = idE.toInt();
    bool test=E.supprimer_event(idEvent);
    if(test)
    {
        ui->tableView_4->setModel(E.afficher_events("","",""));
        qDebug() << "Supp succ";
    }
    else
    {
         qDebug() << "Supp faild";
    }
    on_retourevents2_clicked();

}

void ListeEvents::on_pushButton_38_clicked()
{
    ui->dateTimeEdit_5->clear();
    ui->dateTimeEdit_6->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_11->clear();
    ui->label_21->clear();
    ui->lineEdit_18->clear();
}


void ListeEvents::on_update_button_4_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_4->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idEventIndex = selectedIndexes.at(0);
    QVariant idE = idEventIndex.data(Qt::DisplayRole);
    ui->actionswidgetEvents->setCurrentIndex(2);

    QSqlQuery query;
    query.prepare("SELECT * FROM evenement WHERE id_event = :idE");
    query.bindValue(":idE", idE);
    if (query.exec() && query.next()) {
          qDebug() << "id_contrat:" << query.value(3).toString();
          qDebug() << "id_salle:" << query.value(4).toString();
            qDebug() <<query.value(0);
            qDebug() <<query.value(1);
            qDebug() <<query.value(2);
            qDebug() <<query.value(3);
            qDebug() <<query.value(4);
            qDebug() <<query.value(5);
            qDebug() <<query.value(6);
            ui->lineEdit_14->setText(query.value(0).toString());
            ui->dateTimeEdit_7->setDate(query.value(1).toDate());
            ui->dateTimeEdit_8->setDate(query.value(2).toDate());
            ui->lineEdit_13->addItem(query.value(3).toString());
            ui->lineEdit_16->addItem(query.value(4).toString());
            ui->lineEdit_15->setText(query.value(5).toString());
            ui->lineEdit_17->setText(query.value(7).toString());
            QByteArray imageData = query.value(6).toByteArray();
            QImage qrCodeImage;
            qrCodeImage.loadFromData(imageData);
            ui->label_28->setPixmap(QPixmap::fromImage(qrCodeImage));
        } else {
            qDebug() << "Error fetching data:" << query.lastError().text();
        }
    //les informations depuis contrats
    QSqlQuery query2;
    if (query2.exec("SELECT id_contrat, id_artiste FROM contrat")) {
        while (query2.next()) {

            QString idContrat = query2.value(0).toString();
            QString idArtiste = query2.value(1).toString();
            QString item = "Id contrat est "+idContrat + " - " +"Id Artiste est "+idArtiste;
            ui->lineEdit_13->addItem(item);
        }
    } else {
        qDebug() << "Failed to execute query:" << query2.lastError().text();
    }
    //les informations depuis Salles
    /*QSqlQuery query1;
    if (query1.exec("SELECT * FROM salle")) {
        while (query1.next()) {

            QString idSalle = query1.value(0).toString();
            QString taillesalle = query1.value(1).toString();
            //QString prixsalle = query1.value(2).toString();//+" - "+"Le prix est "+prixsalle
            QString item = "Id salle est "+idSalle + " - " +"La taille est "+taillesalle;
            ui->lineEdit_16->addItem(item);
        }
    } else {
        qDebug() << "Failed to execute query:" << query1.lastError().text();
    }*/
    //

}


void ListeEvents::on_retourevents2_2_clicked()
{
    ui->actionswidgetEvents->setCurrentIndex(0);
    ui->lineEdit_14->clear();
    ui->dateTimeEdit_7->clear();
    ui->dateTimeEdit_8->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_17->clear();
    ui->label_28->clear();

}

void ListeEvents::on_pushButton_45_clicked()
{
    Evenements e;
    bool isIntidc;
    bool isIntids;
    bool isIntnbr;
    QModelIndexList selectedIndexes = ui->tableView_4->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idEventIndex = selectedIndexes.at(0);
    QVariant idE = idEventIndex.data(Qt::DisplayRole);

    e.setIdevent(ui->lineEdit_14->text().toInt());
    e.setDatedebutevent(ui->dateTimeEdit_7->date());
    e.setDatefinevent(ui->dateTimeEdit_8->date());
    if (!ui->lineEdit_13->currentText().toInt())
    {
        QString currentText = ui->lineEdit_13->currentText();
        QStringList parts = currentText.split("Id contrat est ");
        QString idContratText = parts[1].split(" - ")[0];
        e.setContratid(idContratText.toInt(&isIntidc));
    }
    else
    {
      e.setContratid(ui->lineEdit_13->currentText().toInt(&isIntidc));
    }

    if (!ui->lineEdit_16->currentText().toInt())
    {
        QString currentText2 = ui->lineEdit_16->currentText();
        QStringList parts2 = currentText2.split("Id salle est ");
        QString idsalleText = parts2[1].split(" - ")[0];
        e.setSalletid(idsalleText.toInt(&isIntids));
    }
    else
    {
       e.setSalletid(ui->lineEdit_16->currentText().toInt(&isIntids));
    }

    e.setNbrEmployes(ui->lineEdit_15->text().toInt(&isIntnbr));
    e.setNomevent(ui->lineEdit_17->text());

    QString newEventInfo = QString("Bonjour monsieur,madame,\nVous êtes invité à participer à l'événement %1 du %2 jusqu'au %3 dans la salle %4.\nMerci, nous attendons votre présence.")
                              .arg(e.getNomevent())
                              .arg(e.getDatedebutevent().toString("dd/MM/yyyy"))
                              .arg(e.getDatefinevent().toString("dd/MM/yyyy"))
                              .arg(e.getSalleid());

    QZXing encoder;
    QZXingEncoderConfig config;
    QImage newQRCodeImage = encoder.encodeData(newEventInfo, config);
    e.setQrcode(newQRCodeImage);

    int id = e.getIdevent();
    QDate dated = e.getDatedebutevent();
    QDate datef = e.getDatefinevent();
    int idc = e.getContratid();
    int ids = e.getSalleid();
    int nbremp = e.getNbrEmployes();
    QString nomevent = e.getNomevent();
    QImage qrcode = e.getQrcode();

    //controle de saisie
    if (dated >= datef) {
        QMessageBox::critical(this, "Error", "La date de début doit être antérieure à la date de fin.");
        return;
    }
    if (nomevent.isEmpty() || !nomevent.at(0).isUpper() || !nomevent.contains(QRegExp("^[A-Za-z]+$"))) {
        QMessageBox::critical(this, "Error", "Nomevent doit commencer par une lettre majuscule et contenir uniquement des caractères alphabétiques");
        return;
    }
    if (!isIntidc) {
        QMessageBox::critical(this, "Erreur", "ID Contrat doit être un entier.");
        return;
    }
    if (!isIntids) {
        QMessageBox::critical(this, "Erreur", "ID Salle doit être un entier.");
        return;
    }
    if (!isIntnbr) {
        QMessageBox::critical(this, "Erreur", "Nombre des employes doit être un entier.");
        return;
    }

    const QPixmap *pixmapPtr = ui->label_28->pixmap();
    if (!pixmapPtr) {
        QMessageBox::critical(this, "Error", "No Qrcode found ");
        return;
    }


    int whiteBackgroundSize = qrcode.width() + 40;
    QImage whiteBackground(whiteBackgroundSize, whiteBackgroundSize, QImage::Format_RGB32);
    whiteBackground.fill(Qt::white);


    int qrCodeX = (whiteBackground.width() - qrcode.width()) / 2;
    int qrCodeY = (whiteBackground.height() - qrcode.height()) / 2;


    QPainter painter(&whiteBackground);
    painter.drawImage(qrCodeX, qrCodeY, qrcode);


    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Save QR Code Image"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directoryPath.isEmpty()) {
        QString filePath = QDir(directoryPath).filePath(nomevent + ".png");
        if (whiteBackground.save(filePath)) {
            qDebug() << "QR Code image saved successfully with white space border.";
        } else {
            qDebug() << "Failed to save QR Code image with white space border.";
        }
    } else {
        qDebug() << "Directory path is empty. QR Code image not saved.";
    }

    // Update the UI and database
    E.modfier_event(id, dated, datef, idc, ids, nbremp, qrcode, nomevent);
    ui->lineEdit_14->clear();
    ui->dateTimeEdit_7->clear();
    ui->dateTimeEdit_8->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_17->clear();
    ui->label_28->clear();
    ui->actionswidgetEvents->setCurrentIndex(0);
    ui->tableView_4->setModel(E.afficher_events("","",""));
}


//Metiers PDF/Excel
void ListeEvents::exportToPdf(const QString& filename, QTableView* tableView) {

    QImage templateImage("C:/Users/USER/Downloads/100-1.png"); // Replace with the path to your template image
    if (templateImage.isNull()) {
        qDebug() << "Failed to load template image. Aborting export to PDF.";
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    if (!printer.isValid()) {
        qDebug() << "Printer is not valid. Aborting export to PDF.";
        return;
    }

    QPainter painter(&printer);

    if (!painter.isActive()) {
        qDebug() << "Painter is not active. Aborting export to PDF.";
        return;
    }

    double xscale = printer.pageRect().width() / double(templateImage.width());
    double yscale = printer.pageRect().height() / double(templateImage.height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect().center());
    painter.scale(scale, scale);
    painter.translate(-templateImage.width()/2, -templateImage.height()/2);


    painter.drawImage(0, 0, templateImage);


    double tableScaleFactor = 1.5; // Increase the table size by 50%
    int tableWidth = tableView->width() * tableScaleFactor;
    int tableHeight = tableView->height() * tableScaleFactor;
    int tableX = (templateImage.width() - tableWidth) / 2;
    int tableY = (templateImage.height() - tableHeight) / 2;


    painter.translate(tableX, tableY);
    painter.scale(tableScaleFactor, tableScaleFactor);
    tableView->render(&painter);

    painter.end();
}
void ListeEvents::exportToExcel(const QString& filename,QTableView* tableView) {
    // Load the template file
    QString templateFilename = "C:/Users/USER/Desktop/Projet C++/DarZmenInteg5/event.xlsx";
    QFile templateFile(templateFilename);
    if (!templateFile.open(QIODevice::ReadOnly)) {
        // Handle error when template file cannot be opened
        qDebug() << "Failed to open template file";
        return;
    }

    // Read template contents
    QByteArray templateData = templateFile.readAll();
    templateFile.close();

    QTemporaryFile tempFile;
        if (!tempFile.open()) {
            qDebug() << "Error: Failed to create temporary file";
            return;
        }
        tempFile.write(templateData);
        tempFile.close();

        // Create a new QXlsx document using the template file
        QXlsx::Document xlsx(tempFile.fileName());

    QAbstractItemModel* model = tableView->model();

    // Set document properties
    xlsx.setDocumentProperty("title", "Liste des Evenements");
    xlsx.setDocumentProperty("creator", "DAR ZMEN");
    xlsx.setDocumentProperty("company", "DAR ZMEN");

    // Add current date
    QString currentDate = QDateTime::currentDateTime().toString("dd/MM/yyyy");
    xlsx.write("H1", "Date: " + currentDate);

    for(int row = 0; row < model->rowCount(); ++row) {
        int writeColumn = 2;
        for(int column = 0; column < model->columnCount(); ++column) {
            QString columnName = model->headerData(column, Qt::Horizontal).toString();
            if (columnName == "Qr code")
                continue;

            QModelIndex index = model->index(row, column);
            QVariant data = model->data(index);

            if (data.type() == QVariant::ByteArray) {
                continue;
            }

            if (data.type() == QVariant::Date) {
                QDate date = data.toDate();
                QString dateString = date.toString("dd/MM/yyyy");
                xlsx.write(row + 4, writeColumn++, dateString); // Adjusted row to accommodate title, date, and header
            } else {
                xlsx.write(row + 4, writeColumn++, data.toString()); // Adjusted row to accommodate title, date, and header
            }
        }
    }



    // Save the file
    xlsx.saveAs(filename);
}

void ListeEvents::on_pdf_button_4_clicked()
{
        /*QString filename = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
        if (!filename.isEmpty())
        {
            exportToPdf(filename, ui->tableView_4);
        }*/
        QTableView* tableViewc = ui->tableView_4;

        if (!tableViewc)
        {
            QMessageBox::critical(nullptr, "ERREUR", "Table view not found.");
            return;
        }

        QAbstractItemModel* model = tableViewc->model();

        if (!model)
        {
            QMessageBox::critical(nullptr, "ERREUR", "Model not found.");
            return;
        }

        int rowCount = model->rowCount();
        int columnCount = model->columnCount();

        QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "Evnets.pdf", "PDF files (*.pdf)");
        if (filePath.isEmpty())
        {
            return;
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);

        QTextDocument document;
        QTextCursor cursor(&document);

        // Concatenate the entire HTML content in a QString
        QString htmlContent = "<html>\n"
                                  "<head>\n"
                                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                  "<title>Liste de Clients</title>\n"
                                  "<style>"
                                  "table {"
                                  "   border-collapse: collapse;"
                                  "   width: 100%;"
                                  "}"
                                  "th, td {"
                                  "   border: 1px solid #dddddd;"
                                  "   text-align: left;"
                                  "   padding: 8px;"
                                  "}"
                                  "th {"
                                  "   background-color: #F5B7B1;"
                                  "}"
                                  "</style>"
                                  "</head>\n"
                                  "<body bgcolor=#FDFEFE link=#5000A0>\n"
                                  "<img src='C:/Users/USER/Desktop/Projet C++/projet/src/logo__2_-removebg-preview.png' alt='Logo' style='float: right; width: 50px; height: auto;'>"
                                  "<h1>Liste de Events</h1>"
                                  "<table>\\n";   // Removed border, cellspacing, and cellpadding attributes

        htmlContent += "<thead><tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!tableViewc->isColumnHidden(column)) {
                htmlContent += QString("<th>%1</th>").arg(model->headerData(column, Qt::Horizontal).toString());
            }
        }
        htmlContent += "</tr></thead>\n";

        for (int row = 0; row < rowCount; row++) {
                htmlContent += "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!tableViewc->isColumnHidden(column)) {
                        QString data = model->data(model->index(row, column)).toString().simplified();
                        // Check if the cell contains a QR code (replace "QR_CODE" with your actual representation)
                        if (data != "QR_CODE") {
                            htmlContent += QString("<td>%1</td>").arg((!data.isEmpty()) ? data : "&nbsp;");
                        }
                    }
                }
                htmlContent += "</tr>\n";
            }
        htmlContent += "</table>\n"
                       "</body>\n"
                       "</html>\n";

        // Insert the entire HTML content at once
        cursor.insertHtml(htmlContent);

        document.print(&printer);
}
void ListeEvents::on_pdf_button_5_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Excel", "", "*.xlsx");
        if (!filename.isEmpty())
        {
         exportToExcel(filename, ui->tableView_4);
        }
}
//metier rech et tri
void ListeEvents::on_filtrer_button_4_clicked()
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
    //qDebug() <<sorttype;
    ui->tableView_4->setModel(E.afficher_events(ui->search_line_4->text(), sortOrder, sorttype));
    //ui->tableView_4->setModel(E.afficher_events("", sortOrder, sorttype));
}


void ListeEvents::on_search_button_4_clicked()
{
    ui->tableView_4->setModel(E.afficher_events(ui->search_line_4->text(),"",""));
}
//Qr code
void ListeEvents::on_pushButton_39_clicked()
{
    if (!ui->lineEdit_18->text().isEmpty() && !ui->lineEdit_12->currentText().isEmpty() && !ui->dateTimeEdit_5->text().isEmpty() && !ui->dateTimeEdit_6->text().isEmpty())
    {
    int newEventID=0;
    QSqlQuery query;
    query.prepare("SELECT id_event FROM (SELECT id_event FROM evenement ORDER BY id_event DESC) WHERE ROWNUM = 1");

    if (query.exec() && query.next()) {
        int lastEventID = query.value(0).toInt();
        qDebug() << "The last id is:" << lastEventID;
        newEventID = lastEventID + 1;
    }
    QString currentText2 = ui->lineEdit_12->currentText();
    QStringList parts2 = currentText2.split("Id salle est ");
    QString idsalleText = parts2[1].split(" - ")[0];
    int ids =idsalleText.toInt();
    QString eventInfo = QString("Bonjour monsieur,madame,\nVous êtes invité à participer à l'événement %1 du %2 jusqu'au %3 dans la salle %4.\nMerci, nous attendons votre présence.")
                              .arg(ui->lineEdit_18->text())
                              .arg(ui->dateTimeEdit_5->date().toString("dd/MM/yyyy"))
                              .arg(ui->dateTimeEdit_6->date().toString("dd/MM/yyyy"))
                              .arg(ids);

    QZXing encoder;
    QZXingEncoderConfig config;
    QImage img = encoder.encodeData(eventInfo, config);
    ui->label_21->setPixmap(QPixmap::fromImage(img));
    }
}

void ListeEvents::on_qrcode_button_4_clicked()
{
       QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (*.png *.jpg *.bmp)");
       if (filePath.isEmpty()) {
           qDebug() << "No file selected.";
           return;
       }
       QImage image(filePath);
       if (image.isNull()) {
           qDebug() << "Failed to load image:" << filePath;
           return;
       }
       QZXing decoder;
       QString result = decoder.decodeImage(image);

       if (!result.isEmpty()) {
           qDebug() << "Decoded text:" << result;
           QMessageBox::information(nullptr, "QR Code Decoded", "\n" + result);
       } else {
           qDebug() << "Failed to decode QR code from the image.";
           QMessageBox::critical(nullptr, "Error", "Failed to decode QR code from the image.");
       }
}
//Stats
void ListeEvents::MakePlot1()
{
        // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(255,255,255));
        gradient.setColorAt(0.38, QColor(255, 255, 255));
        gradient.setColorAt(1, QColor(255, 255, 255));
        ui->graphMat2->setBackground(QBrush(gradient));

        // create empty bar chart objects:

        QCPBars *fossil = new QCPBars(ui->graphMat2->xAxis, ui->graphMat2->yAxis);
        fossil->setAntialiased(false);
        fossil->setStackingGap(1);

        // set names and colors:
        fossil->setName("Nombres Des Invités Par Evenements");
        fossil->setPen(QPen(QColor(139, 0, 0).lighter(170)));
        fossil->setBrush(QColor(139, 0, 0));




        // prepare x axis with country labels:
        QVector<double> ticks;
        QVector<QString> labels;
        int i=0;
        QStringList uniqueTypes;
        QVector<double> quantitedata;


        //////////////////////////////////////////////////////////////////AXE DES X//////////////////////////////
            QString  queryStr = "SELECT  id_event FROM evenement";
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
                query.prepare("SELECT nbr_inv FROM evenement WHERE id_event = :id_event");
                query.bindValue(":id_event", uniqueTypes[i]);

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
        ui->graphMat2->xAxis->setTicker(textTicker);
        ui->graphMat2->xAxis->setTickLabelRotation(60);
        ui->graphMat2->xAxis->setSubTicks(false);
        ui->graphMat2->xAxis->setTickLength(0, 4);
        ui->graphMat2->xAxis->setRange(0, 8);
        ui->graphMat2->xAxis->setBasePen(QPen(Qt::black));
        ui->graphMat2->xAxis->setTickPen(QPen(Qt::black));
        ui->graphMat2->xAxis->grid()->setVisible(true);
        ui->graphMat2->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        ui->graphMat2->xAxis->setTickLabelColor(Qt::black);
        ui->graphMat2->xAxis->setLabelColor(Qt::black);

        // prepare y axis:
        ui->graphMat2->yAxis->setRange(0, 30);
        ui->graphMat2->yAxis->setPadding(5); // a bit more space to the left border
        ui->graphMat2->yAxis->setLabel("Statistiques des évenements");
        ui->graphMat2->yAxis->setBasePen(QPen(Qt::black));
        ui->graphMat2->yAxis->setTickPen(QPen(Qt::black));
        ui->graphMat2->yAxis->setSubTickPen(QPen(Qt::black));
        ui->graphMat2->yAxis->grid()->setSubGridVisible(true);
        ui->graphMat2->yAxis->setTickLabelColor(Qt::black);
        ui->graphMat2->yAxis->setLabelColor(Qt::black);
        ui->graphMat2->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        ui->graphMat2->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // Add data:

        //quantitedata  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;

        fossil->setData(ticks, quantitedata);

        // setup legend:
        ui->graphMat2->legend->setVisible(true);
        ui->graphMat2->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        ui->graphMat2->legend->setBrush(QColor(255, 255, 255, 100));
        ui->graphMat2->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        ui->graphMat2->legend->setFont(legendFont);
        ui->graphMat2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void ListeEvents::on_retourevents1_2_clicked()
{
    ui->stackedWidgetstats->setCurrentIndex(1);
}

void ListeEvents::on_retourevents1_3_clicked()
{
    //ui->stackedWidgetstats->setCurrentIndex(0);
    ui->actionswidgetEvents->setCurrentIndex(0);
    ui->lineEdit_20->clear();
    ui->lineEdit_19->clear();
    ui->lineEdit_21->clear();

    QLayout *layout = ui->statspie->layout();
        if (layout) {
            QLayoutItem *child;
            while ((child = layout->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }
        }

}

void ListeEvents::on_retourevents1_4_clicked()
{
    ui->stackedWidgetstats->setCurrentIndex(0);
    //createPieChart();
}

int ListeEvents::getEventsWithDeadlineOver() {
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM evenement WHERE date_fin_event < CURRENT_DATE")) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    }
    return 0;
}


int ListeEvents::getEventsDuringCurrentWeek() {
    QDate currentDate = QDate::currentDate();
    QDate startDate = currentDate.addDays(-currentDate.dayOfWeek() + 1);
    QDate endDate = startDate.addDays(6);

    /*qDebug() << "Start Date:" << startDate.toString("yyyy-MM-dd");
    qDebug() << "End Date:" << endDate.toString("yyyy-MM-dd");*/

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM evenement WHERE date_debut_event BETWEEN ? AND ?");
    query.addBindValue(startDate);
    query.addBindValue(endDate);

    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
    return 0;
}



int ListeEvents::getEventsDuringCurrentMonth() {
    QDate currentDate = QDate::currentDate();
    QDate startDate = currentDate.addDays(-currentDate.day() + 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);

    /*qDebug() << "Start Date:" << startDate.toString("yyyy-MM-dd");
    qDebug() << "End Date:" << endDate.toString("yyyy-MM-dd");*/

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM evenement WHERE date_debut_event BETWEEN ? AND ?");
    query.addBindValue(startDate);
    query.addBindValue(endDate);

    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
    return 0;
}

void ListeEvents::createPieChart() {
    QSqlQuery query("SELECT id_contrat, COUNT(*) AS num_events FROM evenement GROUP BY id_contrat");

    QMap<QString, int> contractEventCounts;
    while (query.next()) {
        contractEventCounts.insert(query.value(0).toString(), query.value(1).toInt());
    }

    QPieSeries *series = new QPieSeries();
    QMapIterator<QString, int> it(contractEventCounts);
    while (it.hasNext()) {
        it.next();
        QPieSlice *slice = series->append(it.key(), it.value());
        // Set custom colors for pie slices
        if (slice) {
            if (series->slices().count() == 1)
                slice->setBrush(QColor("#D8C412"));
            else if (series->slices().count() == 2)
                slice->setBrush(QColor("#8B0000"));
            else if (series->slices().count() == 3)
                slice->setBrush(QColor("#FFD700"));
            // Add more conditions for additional slices if needed
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);

    QFont font;
    font.setPointSize(16);
    chart->setTitleFont(font);

    // Set title color to dark red
    chart->setTitleBrush(QColor("#8B0000"));

    chart->setTitle("Nombre des Evénements Par Contract ");

    QChart::AnimationOptions options = QChart::AllAnimations;
    chart->setAnimationOptions(options);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    chartView->setFixedSize(1200, 1200);

    if (!ui->statspie->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->statspie);
        ui->statspie->setLayout(layout);
    }

    ui->statspie->layout()->addWidget(chartView);
}

//Impression Qrcode
void ListeEvents::printWidget(QWidget* widget) {
    QPrinter printer;

    QPrintDialog printDialog(&printer, widget);

    if (printDialog.exec() == QDialog::Rejected) {
        return;
    }

    QPainter painter(&printer);
    widget->render(&painter);
}

void ListeEvents::on_pushButton_44_clicked()
{
    if (ui->label_21->pixmap() == nullptr || ui->label_21->pixmap()->isNull()) {
        QMessageBox::warning(this, "Aucun QR code", "Merci de generer le QR code.");
        return;
    }
    printWidget(ui->label_21);
}

//metier2/////////////////////////
bool ListeEvents::isRoomAvailable(int roomId, const QDate &startDate, const QDate &endDate) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM evenement "
                      "WHERE id_salle = :roomId "
                      "AND ((date_debut_event <= :start AND date_fin_event >= :start) "
                      "OR (date_debut_event <= :end AND date_fin_event >= :end) "
                      "OR (date_debut_event >= :start AND date_fin_event <= :end))");
    query.bindValue(":roomId", roomId);
    query.bindValue(":start", startDate);
    query.bindValue(":end", endDate);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return false;
    }
    if (query.next()) {
        int count = query.value(0).toInt();
        return count == 0;
    }
    return false;
}


QDate ListeEvents::findNextAvailableDate(int roomId, const QDate &startDate, const QDate &endDate) {
    QSqlQuery query;
    query.prepare("SELECT date_fin_event FROM evenement "
                  "WHERE id_salle = :roomId "
                  "AND date_debut_event <= :endDate AND date_fin_event >= :startDate "
                  "ORDER BY date_debut_event ASC");
    query.bindValue(":roomId", roomId);
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return QDate();
    }
    QDate nextAvailableDate = endDate.addDays(1);
    while (query.next()) {
        QDate eventEndDate = query.value(0).toDate();
        if (eventEndDate.isValid() && eventEndDate >= startDate) {
            nextAvailableDate = eventEndDate.addDays(1);
        }
    }

    return nextAvailableDate;
}


void ListeEvents::showRoomInfoDialog(QWidget *p,QDate dated,QDate datef) {
    QDialog dialog(p);
       dialog.setWindowTitle("Room Information");
       dialog.setWindowIcon(QIcon("C:/Users/USER/Desktop/Projet C++/DarZmenInteg5/src/logo__2_-removebg-preview.png"));
       dialog.setStyleSheet("background-color: white;");

       QGridLayout *layout = new QGridLayout(&dialog);
       int row = 0;
       int col = 0;

       QSqlQuery query;
       query.prepare("SELECT * FROM salle");
       if (!query.exec()) {
           qDebug() << "Query failed:" << query.lastError().text();
           return;
       }

       while (query.next()) {
           int roomId = query.value(0).toInt();
           QString roomSize = query.value(1).toString();
           QString roomPrice = query.value(2).toString();
           bool isAvailable = isRoomAvailable(roomId, dated, datef);
           QString availableText = "Disponible";
           if (!isAvailable) {
                   //QDate availableDate = findAvailableDate(roomId,dated,datef);
                   QDate availableDate = findNextAvailableDate(roomId,dated,datef);
                   availableText = "Disponible à partir de :\n" + availableDate.toString("dd/MM/yyyy");
           }

           QPushButton *roomButton = new QPushButton(&dialog);
           roomButton->setIcon(QIcon("C:/Users/USER/Desktop/Projet C++/DarZmenInteg5/src/salle.png"));
           roomButton->setIconSize(QSize(80, 80));
           roomButton->setFixedSize(250, 200);
           roomButton->setText("Salle ID: " + QString::number(roomId) + "\n"
                               + "Taille: " + roomSize + "\n"
                               + "Prix: " + roomPrice + "\n"
                               +availableText);
           roomButton->setToolTip("Salle ID: " + QString::number(roomId) + "\n"
                                  + "Taille: " + roomSize + "\n"
                                  + "Prix: " + roomPrice + "\n"
                                  +availableText);
           if (isAvailable) {
               roomButton->setStyleSheet("QPushButton { border: 1px solid black; background-color: lightgreen; }"
                                              "QPushButton:hover { background-color: green; }"
                                              "QPushButton:pressed { background-color: darkgreen; }");
               roomButton->setEnabled(true);
           } else {
               roomButton->setStyleSheet("QPushButton { border: 1px solid black; background-color: lightcoral; }");
               roomButton->setEnabled(false);
           }
           if (ui->actionswidgetEvents->currentIndex() == 3) {
           connect(roomButton, &QPushButton::clicked, this, [&dialog, roomId, roomSize, this]() {
               QString item = "Id salle est "+ QString::number(roomId) + " - " +"La taille est "+ roomSize;
               if (ui->lineEdit_12->count() == 0) {
                      ui->lineEdit_12->addItem(item);
              }
              else
              {
                  ui->lineEdit_12->clear();
                  ui->lineEdit_12->addItem(item);
              }
               dialog.close();
           });
           }

           if (ui->actionswidgetEvents->currentIndex() == 2) {
           connect(roomButton, &QPushButton::clicked, this, [&dialog, roomId, roomSize, this]() {
               QString item = "Id salle est "+ QString::number(roomId) + " - " +"La taille est "+ roomSize;
               if (ui->lineEdit_16->count() == 0) {
                      ui->lineEdit_16->addItem(item);
              }
              else
              {
                  ui->lineEdit_16->clear();
                  ui->lineEdit_16->addItem(item);
              }
               dialog.close();
           });
           }

           layout->addWidget(roomButton, row, col);
           col++;
           if (col == 3) {
               col = 0;
               row++;
           }
       }

       dialog.exec();
}

void ListeEvents::on_pushButton_46_clicked()
{
    QWidget *parentWidget = nullptr;
    QDate dated = ui->dateTimeEdit_5->date();
    QDate datef = ui->dateTimeEdit_6->date();
    if (dated >= datef) {
    QMessageBox::critical(this, "Error", "La date de début doit être antérieure à la date de fin.");
    return;
    }
    else
    {
        showRoomInfoDialog(parentWidget,dated,datef);
    }
}

void ListeEvents::on_pushButton_47_clicked()
{
    QWidget *parentWidget = nullptr;
    QDate dated = ui->dateTimeEdit_7->date();
    QDate datef = ui->dateTimeEdit_8->date();
    if (dated >= datef) {
    QMessageBox::critical(this, "Error", "La date de début doit être antérieure à la date de fin.");
    return;
    }
    else
    {
        showRoomInfoDialog(parentWidget,dated,datef);
    }
}

//***********************************************************************************************************************
void ListeEvents::on_pushButton_clicked() {

    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, [=]() {
        QDate selectedDate = calendarWidget->selectedDate();
        ui->dateTimeEdit_5->setDate(selectedDate);
        calendarWidget->close();
    });
      calendarWidget->setWindowModality(Qt::WindowModal);
      calendarWidget->setStyleSheet("QCalendarWidget QToolButton {"
                                        "   background-color: #f0f0f0;"
                                        "   border: 1px solid #d8d8d8;"
                                        "   border-radius: 5px;"
                                        "   padding: 5px;"
                                        "}"
                                        "QCalendarWidget QWidget {"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView {"
                                        "   background-color: #ffffff;"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView:selected {"
                                        "   background-color: #007bff;"
                                        "   color: #ffffff;"
                                        "}");
      calendarWidget->resize(391, 301);
      QPoint buttonPos = ui->pushButton->mapToGlobal(QPoint(0, ui->pushButton->height()));
      int x = 850;
      int y = buttonPos.y() - 270;
      calendarWidget->move(x, y);
      calendarWidget->show();
}




void ListeEvents::on_pushButton_2_clicked()
{
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, [=]() {
        QDate selectedDate = calendarWidget->selectedDate();
        ui->dateTimeEdit_6->setDate(selectedDate);
        calendarWidget->close();
    });
      calendarWidget->setWindowModality(Qt::WindowModal);
      calendarWidget->setStyleSheet("QCalendarWidget QToolButton {"
                                        "   background-color: #f0f0f0;"
                                        "   border: 1px solid #d8d8d8;"
                                        "   border-radius: 5px;"
                                        "   padding: 5px;"
                                        "}"
                                        "QCalendarWidget QWidget {"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView {"
                                        "   background-color: #ffffff;"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView:selected {"
                                        "   background-color: #007bff;"
                                        "   color: #ffffff;"
                                        "}");
      calendarWidget->resize(391, 301);
      QPoint buttonPos = ui->pushButton_2->mapToGlobal(QPoint(0, ui->pushButton_2->height()));
      int x = 850;
      int y = buttonPos.y() - 270;
      calendarWidget->move(x, y);
      calendarWidget->show();
}

void ListeEvents::on_pushButton_3_clicked()
{
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, [=]() {
        QDate selectedDate = calendarWidget->selectedDate();
        ui->dateTimeEdit_7->setDate(selectedDate);
        calendarWidget->close();
    });
      calendarWidget->setWindowModality(Qt::WindowModal);
      calendarWidget->setStyleSheet("QCalendarWidget QToolButton {"
                                        "   background-color: #f0f0f0;"
                                        "   border: 1px solid #d8d8d8;"
                                        "   border-radius: 5px;"
                                        "   padding: 5px;"
                                        "}"
                                        "QCalendarWidget QWidget {"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView {"
                                        "   background-color: #ffffff;"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView:selected {"
                                        "   background-color: #007bff;"
                                        "   color: #ffffff;"
                                        "}");
      calendarWidget->resize(391, 301);
      QPoint buttonPos = ui->pushButton_3->mapToGlobal(QPoint(0, ui->pushButton_3->height()));
      int x = 850;
      int y = buttonPos.y() - 270;
      calendarWidget->move(x, y);
      calendarWidget->show();
}

void ListeEvents::on_pushButton_4_clicked()
{
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, [=]() {
        QDate selectedDate = calendarWidget->selectedDate();
        ui->dateTimeEdit_8->setDate(selectedDate);
        calendarWidget->close();
    });
      calendarWidget->setWindowModality(Qt::WindowModal);
      calendarWidget->setStyleSheet("QCalendarWidget QToolButton {"
                                        "   background-color: #f0f0f0;"
                                        "   border: 1px solid #d8d8d8;"
                                        "   border-radius: 5px;"
                                        "   padding: 5px;"
                                        "}"
                                        "QCalendarWidget QWidget {"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView {"
                                        "   background-color: #ffffff;"
                                        "   color: #333333;"
                                        "}"
                                        "QCalendarWidget QAbstractItemView:selected {"
                                        "   background-color: #007bff;"
                                        "   color: #ffffff;"
                                        "}");
      calendarWidget->resize(391, 301);
      QPoint buttonPos = ui->pushButton_4->mapToGlobal(QPoint(0, ui->pushButton_4->height()));
      int x = 850;
      int y = buttonPos.y() - 270;
      calendarWidget->move(x, y);
      calendarWidget->show();
}

void ListeEvents::updateLabell()
{
    data = A.read_from_arduino();

    QString dataAsString = QString::fromUtf8(data);
    qDebug() << "dataAsString:" << dataAsString;

    int eventNameIndex = dataAsString.indexOf("Event Name:");
    if(eventNameIndex != -1) {
        QString eventName = dataAsString.mid(eventNameIndex + QString("Event Name:").length()).trimmed();
        qDebug() << "Event Name:" << eventName;

        QSqlQuery query;
        query.prepare("SELECT nbr_inv, date_debut_event, date_fin_event FROM evenement WHERE NOMEVENT = :eventName");
        query.bindValue(":eventName", eventName);

        if (query.exec() && query.next()) {
            int nbrInv = query.value(0).toInt();
            QDateTime startDate = query.value(1).toDateTime();
            QDateTime endDate = query.value(2).toDateTime();
            QDateTime currentDate = QDateTime::currentDateTime();

            if (startDate <= currentDate && currentDate <= endDate) {
                if (nbrInv > 0) {
                    query.prepare("UPDATE evenement SET nbr_inv = nbr_inv - 1 WHERE NOMEVENT = :eventName");
                    query.bindValue(":eventName", eventName);

                    // Execute the query
                    if (query.exec()) {
                        qDebug() << "nbr_inv decremented successfully.";
                        ui->tableView_4->setModel(E.afficher_events("","",""));
                     //
                    } else {
                        qDebug() << "Error decrementing nbr_inv:" << query.lastError().text();
                    }
                } else {
                    qDebug() << "nbr_inv is already 0. Cannot decrement further.";
                }
            } else {
                qDebug() << "Event is not active (current date is not between start and end dates).";
            }
        } else {
            qDebug() << "Failed to fetch event details:" << query.lastError().text();
        }
    } else {
        qDebug() << "Event Name not found in data.";
    }
}

void ListeEvents::on_pdf_button_8_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_4->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idEventIndex = selectedIndexes.at(0);
    QVariant idE = idEventIndex.data(Qt::DisplayRole);
    QSqlQuery query;
    query.prepare("SELECT nbr_inv FROM evenement WHERE id_event = :idE");
    query.bindValue(":idE", idE);
    if (query.exec() && query.next()) {
        // Retrieve nbr_inv from the query result
        QVariant nbrInvVariant = query.value(0);

        // Convert nbr_inv to a QByteArray
        QByteArray data = nbrInvVariant.toByteArray();

        // Send data to Arduino
        A.write_to_arduino(data);
    }
    else {
        qDebug() << "Error executing query or no data found.";
    }
}
