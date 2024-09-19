#include "listeevents.h"
#include "listecontrats.h"
#include "listeartistes.h"
#include "listepersonnels.h"
#include "listesalles.h"
#include "listematriels.h"
#include "ui_listematriels.h"
#include "materiel.h"
#include <QtSql>
#include <QMessageBox>
#include <QtDebug>
#include <QModelIndexList>
#include <QSqlError>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QTableView>
#include <QByteArray>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "QZXing.h"
#include <QDesktopServices>
//#include "barcodeprinter.h"
using namespace QXlsx;


ListeMatriels::ListeMatriels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListeMatriels)
{
    ui->setupUi(this);
    ui->TabaffichageMat->setModel(M.afficher_materiel("","",""));

}

ListeMatriels::~ListeMatriels()
{
    delete ui;
}

void ListeMatriels::setMatButtonStyle(const QString &style) {
    ui->matariel->setStyleSheet(style);
}


//************************Navigation mat ***************************************

void ListeMatriels::on_AjoutMat_clicked()
{

        ui->actionswidgetMat->setCurrentIndex(1);
        //need to clear or combobox will repeat
        ui->idSallemodifmat->clear();

        // combobox data
        QSqlQuery query1;
        if (query1.exec("SELECT idSalle FROM salle")) { // Assuming idSalle is the primary key
            while (query1.next()) {
                QString idSalle = query1.value(0).toString();

                // Check if idSalle is not already present in the uniqueIds set


                    QString item =idSalle;
                    ui->idSalleajoutmat->addItem(item); // Add idSalle to the combo box

            }
        } else {
            qDebug() << "Failed to execute query:" << query1.lastError().text();
        }
        ui->idSalleajoutmat->setCurrentIndex(-1);

}

void ListeMatriels::on_StatsMat_clicked()
{

        ui->actionswidgetMat->setCurrentIndex(2);
        generalstats();
        MakePlot1();
        //MakePlot2();


}

void ListeMatriels::on_ModifMat_clicked()
{



QModelIndexList selectedIndexes = ui->TabaffichageMat->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idMatIndex = selectedIndexes.at(0);
    QVariant idMat = idMatIndex.data(Qt::DisplayRole);
    QModelIndex idMatSALLEindex = selectedIndexes.at(4);
    QVariant defaultIdSalle = idMatSALLEindex.data(Qt::DisplayRole);
    qDebug() <<defaultIdSalle;

    //need to clear or combobox will repeat
    ui->idSallemodifmat->clear();

    // combobox data
    QSqlQuery query1;
    if (query1.exec("SELECT idSalle FROM salle")) {
        while (query1.next()) {
            QString idSalle = query1.value(0).toString();

            // Check if idSalle is not already present in the uniqueIds set


                QString item =idSalle;
                ui->idSallemodifmat->addItem(item); // Add idSalle to the combo box

        }
    } else {
        qDebug() << "Failed to execute query:" << query1.lastError().text();
    }
     ui->idSallemodifmat->setCurrentIndex(ui->idSallemodifmat->findText(QString::number(defaultIdSalle.toInt())));


    ui->actionswidgetMat->setCurrentIndex(3);


QSqlQuery query;
    query.prepare("SELECT * FROM MATERIELS WHERE ID_MAT = :idMat");

    query.bindValue(":idMat", idMat);
    if (query.exec() && query.next()) {

        qDebug() <<query.value(0);
        qDebug() <<query.value(1);
        qDebug() <<query.value(2);
        qDebug() <<query.value(3);
        qDebug() <<query.value(5);

        ui->idMatmodif->setText(query.value(0).toString());
        ui->typematmodif->setText(query.value(1).toString());
        ui->nbrmatmodif->setText(query.value(3).toString());
        ui->prixmatmodif->setText(query.value(2).toString());
        ui->nbrmatendmodif->setText(query.value(5).toString());

    } else {
        qDebug() << "Error fetching data:" << query.lastError().text();
    }
}

void ListeMatriels::on_barcodeMat_clicked()
{

    QModelIndexList selectedIndexes = ui->TabaffichageMat->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    ui->actionswidgetMat->setCurrentIndex(4);
    QModelIndex idMatIndex = selectedIndexes.at(0);
    QVariant idMat = idMatIndex.data(Qt::DisplayRole).toString(); // Convert to string

    QSqlQuery query;
    query.prepare("SELECT ID_MAT, TYPE, IDSALLE FROM MATERIELS WHERE ID_MAT = :idMat");
    query.bindValue(":idMat", idMat);

    if (query.exec() && query.next()) {
        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();
        qDebug() << query.value(2).toString();

        ui->ID_MAT_barcode->setText(query.value(0).toString());
        ui->Type_barcode->setText(query.value(1).toString());
        ui->idsalle_barcode->setText(query.value(2).toString());
    } else {
        qDebug() << "Error fetching data:" << query.lastError().text();
    }
}



void ListeMatriels::on_retourmat1_clicked()
{

        ui->actionswidgetMat->setCurrentIndex(0);
        ui->typeMatadd->clear();
        ui->nbrMatadd->clear();
        ui->prixMatadd->clear();
        ui->idSalleajoutmat->clear();

}

void ListeMatriels::on_retourmat2_clicked()
{
    ui->actionswidgetMat->setCurrentIndex(0);

}


void ListeMatriels::on_retourmat3_clicked()
{
    ui->actionswidgetMat->setCurrentIndex(0);
    ui->typeMatadd->clear();
    ui->nbrMatadd->clear();
    ui->prixMatadd->clear();
    ui->idSallemodifmat->clear();

}



void ListeMatriels::on_filtrerMat_clicked()
{

    QString sortOrder;
        if(ui->CroissantMat->isChecked())
        {
            sortOrder = "ASC";
        }
        else if (ui->DecrMat->isChecked())
        {
            sortOrder = "DESC";
        }
        QString sorttype = ui->tritext->currentText();
        ui->TabaffichageMat->setModel(M.afficher_materiel(ui->searchMat->text(), sortOrder, sorttype));

    qDebug() << "Filter pressed";
}

void ListeMatriels::on_rechercheMat_clicked()
{

    QString searchText = ui->searchMat->text();
    ui->TabaffichageMat->setModel(M.afficher_materiel(searchText,"",""));


}

//*******************************************************navigation stats**************
void ListeMatriels::on_prevGraphMat_clicked()
{
    ui->graphswidgetMat->setCurrentIndex(0);
}
void ListeMatriels::on_nextGraphMat_clicked()
{
    ui->graphswidgetMat->setCurrentIndex(1);
}
void ListeMatriels::on_nextGraphMat_2_clicked()
{
    //ui->graphswidgetMat->setCurrentIndex(2);
}
//*****************************************************CRUD**************************************************





void ListeMatriels::on_confirmajoutmat_clicked()
{
    Materiel m;

    m.setPrixM(ui->prixMatadd->text());
    m.setQuantiteM(ui->nbrMatadd->text());
    m.setIdSalle(ui->idSalleajoutmat->currentText());
    m.setTypeM(ui->typeMatadd->text());

//////////////////////////////////////////////////////////////////////////////////////CSAISIE
    if (m.getPrixM().isEmpty() || m.getTypeM().isEmpty() || m.getQuantiteM().isEmpty() || m.getIdSalle().isEmpty()) {
           QMessageBox::warning(this, "Information manquante", "Merci de saisir tous les elements.");
           return;
       }
    QRegExp re("\\d*");
        if (!re.exactMatch(m.getQuantiteM())) {
            QMessageBox::warning(this, "Quantité non valable", "Merci de saisir une valeur numerique pour Nombre.");
            return;
       }
    QRegExp priceRe("\\d+\\.\\d+|\\d+");
            if (!priceRe.exactMatch(m.getPrixM())) {
                QMessageBox::warning(this, "Prix non valable", "Merci de saisir une valeur numerique pour Prix.");
                return;
            }
/////////////////////////////////////////////////////////////////////////////////////
    bool test=m.ajouter_materiel();
        if(test)
        {


            ui->typeMatadd->clear();
            ui->nbrMatadd->clear();
            ui->prixMatadd->clear();
            ui->idSalleajoutmat->setCurrentIndex(-1);
        }



    //update display after ajout
    ui->TabaffichageMat->setModel(M.afficher_materiel("","",""));
}

void ListeMatriels::on_suppressionmateriel_clicked()
{
    Materiel m;
    QModelIndexList selectedIndexes = ui->TabaffichageMat->selectionModel()->selectedIndexes();

        if (selectedIndexes.isEmpty()) {
            qDebug() << "No row selected.";
            return;
        }

        //Id of selected row
        QModelIndex idMatIndex = selectedIndexes.at(0);
        QVariant idMat = idMatIndex.data(Qt::DisplayRole);

        m.supprimer_materiel(idMat);
       ui->TabaffichageMat->setModel(M.afficher_materiel("","",""));
}


void ListeMatriels::on_confirmmodifmat_clicked()
{

        Materiel m;


        QModelIndexList selectedIndexes = ui->TabaffichageMat->selectionModel()->selectedIndexes();

            if (selectedIndexes.isEmpty()) {
                qDebug() << "No row selected.";
                return;
            }
            QModelIndex idMatIndex = selectedIndexes.at(0);
            QVariant idMat = idMatIndex.data(Qt::DisplayRole);

        m.setPrixM(ui->prixmatmodif->text());
        m.setQuantiteM(ui->nbrmatmodif->text());
        m.setIdSalle(ui->idSallemodifmat->currentText());
        m.setTypeM(ui->typematmodif->text());
        m.setQuantiteENDOM(ui->nbrmatendmodif->text());

        //////////////////////////////////////////////////////////////////////////////////////CSAISIE
            if (m.getPrixM().isEmpty() || m.getTypeM().isEmpty() || m.getQuantiteM().isEmpty() || m.getIdSalle().isEmpty()|| m.getQuantiteENDOM().isEmpty()) {
                   QMessageBox::warning(this, "Information manquante", "Merci de saisir tous les elements.");
                   return;
               }
            QRegExp re("\\d*");
                if (!re.exactMatch(m.getQuantiteM())||!re.exactMatch(m.getQuantiteENDOM())) {
                    QMessageBox::warning(this, "Quantité non valable", "Merci de saisir une valeur numerique pour les Nombres.");
                    return;
                }
            QRegExp priceRe("\\d+\\.\\d+|\\d+");
                    if (!priceRe.exactMatch(m.getPrixM())) {
                        QMessageBox::warning(this, "Prix non valable", "Merci de saisir une valeur numerique pour Prix.");
                        return;
                    }

                    if(m.getQuantiteENDOM().toInt()>m.getQuantiteM().toInt())
                    {
                        QMessageBox::warning(this, "Quantité non valable", "Nombre Materiel endomagé doit etre inferieur ou egal au nombre total.");
                        return;
                    }
        /////////////////////////////////////////////////////////////////////////////////////

        if(m.modfier_materiel(idMat))
        {
            ui->typematmodif->clear();
            ui->nbrmatmodif->clear();
            ui->prixmatmodif->clear();
            ui->idSallemodifmat->setCurrentIndex(-1);
            ui->idMatmodif->clear();
            ui->nbrmatendmodif->clear();
            //update display after modif
            ui->TabaffichageMat->setModel(M.afficher_materiel("","",""));
        }


}
//***************************************************PDF/EXCEL*******************************************************
void ListeMatriels::exportToExcel(const QString& filename, QTableView* tableView) {
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
void ListeMatriels::on_ExcelmAT_clicked()
{

       QString filename = QFileDialog::getSaveFileName(this, "Save Excel", "", ".xlsx");
           if (!filename.isEmpty())
           {

               exportToExcel(filename, ui->TabaffichageMat);
           }
}

void ListeMatriels::exportToPdf(const QString& filename, QTableView* tableView) {
    QPdfWriter writer(filename);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Portrait);

    QPainter painter(&writer);

    // Load the background image
    QImage backgroundImage(":/src/Design_sans_titre_3.png");
    if (!backgroundImage.isNull()) {
        // Define the target rectangle for the background image
        QRectF targetRect(0, 0, writer.width(), writer.height() + 100); // Increase height by 100 units
        painter.drawImage(targetRect, backgroundImage);
    } else {
        qDebug() << "Failed to load background image";
    }

    // Set stylesheet for the table view header to make it transparent with black text
    QString headerStyleSheet = "QHeaderView::section { background-color: transparent; color: black; }";
    tableView->horizontalHeader()->setStyleSheet(headerStyleSheet);
    tableView->verticalHeader()->setStyleSheet(headerStyleSheet);

    // Set the background color of the table view to be transparent
    tableView->setStyleSheet("background-color: transparent; color: black;");

    // Calculate scale to fit the table view content to the page
    double xscale = writer.width() / double(tableView->width());
    double yscale = writer.height() / double(tableView->height());
    double scale = qMin(xscale, yscale);

    painter.save(); // Save the painter state before applying scale
    painter.scale(scale, scale);

    // Adjust the position of the table view to lower it
    double tableX = 0; // Adjust as needed
    double tableY = backgroundImage.height() + 20; // Adjust as needed
    painter.translate(tableX, tableY);

    // Render the scaled table view content
    tableView->render(&painter);

    painter.restore(); // Restore the painter state to revert the scale and translation transformations

    // Add text title at a lower position on the page
    QFont titleFont("Arial", 20, QFont::Bold); // Adjust font size and style as needed
    painter.setFont(titleFont);
    painter.setPen(Qt::black); // Set text color

    QString titleText = "Your Title Here"; // Adjust title text as needed

    // Calculate the height of the title text
    QFontMetrics fontMetrics(titleFont);
    int textHeight = fontMetrics.height();

    // Adjust the position of the title text to ensure visibility
    QRectF titleRect(50, backgroundImage.height() + 20, writer.width() - 100, textHeight+1000); // Adjust position and size of the title
    painter.drawText(titleRect, Qt::AlignCenter, titleText);
}




void ListeMatriels::on_pdfMatExp_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save PDF", "", ".pdf");
       //QString filename = QFileDialog::getSaveFileName(this, "Save Excel", "", ".xlsx");
           if (!filename.isEmpty())
           {
               exportToPdf(filename, ui->TabaffichageMat);
               //exportToExcel(filename, ui->tableView_4);
           }
}

//*****************************************************STATS*******************************************************
void ListeMatriels::MakePlot1()
{
// set dark background gradient:
QLinearGradient gradient(0, 0, 0, 400);
gradient.setColorAt(0, QColor(255,255,255));
gradient.setColorAt(0.38, QColor(255, 255, 255));
gradient.setColorAt(1, QColor(255, 255, 255));
ui->graphMat2->setBackground(QBrush(gradient));

// create empty bar chart objects:

QCPBars *fossil = new QCPBars(ui->graphMat2->xAxis, ui->graphMat2->yAxis);
QCPBars *nuclear = new QCPBars(ui->graphMat2->xAxis, ui->graphMat2->yAxis);
fossil->setAntialiased(false);
fossil->setStackingGap(1);
nuclear->setAntialiased(false);
nuclear->setStackingGap(1);

// set names and colors:
nuclear->setName("Endommagé");
nuclear->setPen(QPen(QColor(215, 157, 27).lighter(150)));
nuclear->setBrush(QColor(215, 157, 27));

fossil->setName("Nombre");
fossil->setPen(QPen(QColor(139, 0, 0).lighter(170)));
fossil->setBrush(QColor(139, 0, 0));
nuclear->moveAbove(fossil);



// prepare x axis with country labels:
QVector<double> ticks;
QVector<QString> labels;
int i=0;
QStringList uniqueTypes;
QVector<double> quantitedata;
QVector<double> quantitedata2;


//////////////////////////////////////////////////////////////////AXE DES X//////////////////////////////
    QString  queryStr = "SELECT DISTINCT TYPE FROM MATERIELS";
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
        query.prepare("SELECT QUANTITEM,QUANTITEENDOM FROM MATERIELS WHERE TYPE = :type");
        query.bindValue(":type", uniqueTypes[i]);

        if (query.exec() && query.next()) {
            quantitedata << query.value(0).toDouble();
            quantitedata2 << query.value(1).toDouble();
            //qDebug() << "quantitedata:" << quantitedata;
            //qDebug() << "quantitedata2:" << quantitedata2;
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();

            quantitedata << 0.0; // Default value
            quantitedata2 << 0.0;
        }
    }






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
ui->graphMat2->yAxis->setLabel("Nombre en fct type mat");
ui->graphMat2->yAxis->setBasePen(QPen(Qt::black));
ui->graphMat2->yAxis->setTickPen(QPen(Qt::black));
ui->graphMat2->yAxis->setSubTickPen(QPen(Qt::black));
ui->graphMat2->yAxis->grid()->setSubGridVisible(true);
ui->graphMat2->yAxis->setTickLabelColor(Qt::black);
ui->graphMat2->yAxis->setLabelColor(Qt::black);
ui->graphMat2->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
ui->graphMat2->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

// Add data:
fossil->setData(ticks, quantitedata);
nuclear->setData(ticks, quantitedata2);

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




/*void ListeMatriels::MakePlot2()
{
    ui->graphMat->legend->setVisible(true);
    ui->graphMat->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QStringList lineNames;
    lineNames << "lsNone" << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";
    // add graphs with different line styles:
    for (int i=QCPGraph::lsNone; i<=QCPGraph::lsImpulse; ++i)
    {
      ui->graphMat->addGraph();
      pen.setColor(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80));
      ui->graphMat->graph()->setPen(pen);
      ui->graphMat->graph()->setName(lineNames.at(i-QCPGraph::lsNone));
      ui->graphMat->graph()->setLineStyle((QCPGraph::LineStyle)i);
      ui->graphMat->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
      // generate data:
      QVector<double> x(15), y(15);
      for (int j=0; j<15; ++j)
      {
        x[j] = j/15.0 * 5*3.14 + 0.01;
        y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
      }
      ui->graphMat->graph()->setData(x, y);
      ui->graphMat->graph()->rescaleAxes(true);
    }
    // zoom out a bit:
    ui->graphMat->yAxis->scaleRange(1.1, ui->graphMat->yAxis->range().center());
    ui->graphMat->xAxis->scaleRange(1.1, ui->graphMat->xAxis->range().center());
    // set blank axis lines:
    ui->graphMat->xAxis->setTicks(false);
    ui->graphMat->yAxis->setTicks(true);
    ui->graphMat->xAxis->setTickLabels(false);
    ui->graphMat->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    ui->graphMat->axisRect()->setupFullAxesBox();
}*/

//*****************************************************MENU********************************************************


void ListeMatriels::on_employes_clicked()
{
    hide();
    ListePersonnels *persopage= new ListePersonnels(this);
    persopage->show();
    persopage->setPersoButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeMatriels::on_artistes_clicked()
{
    hide();
    ListeArtistes *artistepage= new ListeArtistes(this);
    artistepage->show();
    artistepage->setArtisteButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeMatriels::on_contrats_clicked()
{
    hide();
    ListeContrats *contratpage= new ListeContrats(this);
    contratpage->show();
    contratpage->setContratButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeMatriels::on_events_clicked()
{
    hide();
    ListeEvents *eventpage= new ListeEvents(this);
    eventpage->show();
    eventpage->setEventsButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeMatriels::on_matariel_clicked()
{
    hide();
   ListeMatriels *matpage= new ListeMatriels(this);
   matpage->show();
   matpage->setMatButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}
void ListeMatriels::on_salles_clicked()
{
    hide();
    ListeSalles *sallepage= new ListeSalles(this);
    sallepage->show();
        sallepage->setSalleButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}


//*******************************************************************limbo*************************************************************

/*void ListeMatriels::affichageTabMat(bool testsearch,bool testtri) {

    QString queryString = "SELECT * FROM Materiels";
    QSqlQuery query;

    qDebug() << "********";
    qDebug() << "Filter text:" << ui->filterMat->text();
    qDebug() << "search text:" << ui->searchMat->text();


 if (!ui->searchMat->text().isEmpty() || !ui->filterMat->text().isEmpty()){

    if (!ui->searchMat->text().isEmpty() && testsearch==true)
    {
        QString searchText = ui->searchMat->text();
        queryString += QString(" WHERE ID_MAT LIKE %1 OR TYPE LIKE %1 OR PRIX LIKE %1 OR QUANTITEM LIKE %1 OR IDSALLE LIKE %1").arg(searchText);
        qDebug() << "inside ifff 1";
     query.prepare(queryString);

     if (!query.exec()) {
         qDebug() << "Error executing query:" << query.lastError().text();
         return;
     }
    }

    if (!ui->filterMat->text().isEmpty()) {

        if (ui->DecrMat->isChecked()&& testtri==true) {
        QString filterText = ui->filterMat->text();
        queryString += QString(" ORDER BY %1 DESC").arg(filterText);
        }

        else if(ui->CroissantMat->isChecked()&& testtri==true)
        {
            QString filterText = ui->filterMat->text();
            queryString += QString(" ORDER BY %1 ASC").arg(filterText);
        }
           qDebug() << "inside ifff 2";
        query.prepare(queryString);

        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
            return;
        }
      }
}


    else{
        query.prepare("SELECT * FROM Materiels");
            qDebug() << "inside else";

            if (!query.exec()) {
                qDebug() << "Error executing query:" << query.lastError().text();
                return;
            }

     }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(query);

    ui->TabaffichageMat->setModel(model);
}*/

//matmeshach
void ListeMatriels::on_confirmfilterMAT_clicked()
{

}








////////////////////////////////////////////////////////////////////////QR CODE
/*


void ListeEvents::on_qrcode_button_4_clicked()
{
       QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (.png.jpg *.bmp)");
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

//save code
QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Save QR Code Image"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directoryPath.isEmpty()) {
        QString filePath = QDir(directoryPath).filePath(nomevent + ".png");
        if (qrcode.save(filePath)) {
            qDebug() << "QR Code image saved successfully.";
        } else {
            qDebug() << "Failed to save QR Code image.";
        }
*/


void ListeMatriels::on_retour5_clicked()
{

    /*BarcodePrinter printer;
        QString barcodeText = "hazemhazem";
 qDebug() <<printer.getAvailablePrinters();
        if (printer.configurePrinter("Microsoft Print to PDF")) {
           qDebug() << printer.encodeBarcode(barcodeText);
           // printer.printBarcode(barcodeText);
        } else {
            qDebug() << "Failed to configure printer. Generating PDF instead.";
            // Do something else, like save the barcode to a PDF file
        }*/

    QString matInfo = QString("ID_MAT %1 / Type %2 / IDSALLE %3 ")
                                     .arg(ui->ID_MAT_barcode->text())
                                     .arg(ui->Type_barcode->text())
                                     .arg(ui->idsalle_barcode->text());
           qDebug() << matInfo;

           QZXing encoder;
           QZXingEncoderConfig config;
           QImage img = encoder.encodeData(matInfo, config);
           ui->barcode->setPixmap(QPixmap::fromImage(img));



           QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Save QR Code Image"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
               if (!directoryPath.isEmpty()) {
                   QString filePath = QDir(directoryPath).filePath(ui->ID_MAT_barcode->text() + "Mat.png");
                   if (img.save(filePath)) {
                       qDebug() << "QR Code image saved successfully.";
                   } else {
                       qDebug() << "Failed to save QR Code image.";
                   }
    }

}
////////////////////////////////////////////////////////////////////////////////impression qr
void ListeMatriels::on_imprimerQR_clicked()
{
    if (ui->barcode->pixmap() == nullptr || ui->barcode->pixmap()->isNull()) {
        QMessageBox::warning(this, "Aucun QR code", "Merci de generer le QR code.");
        return;
    }
    printWidget(ui->barcode);
}

void ListeMatriels::printWidget(QWidget* widget) {
    QPrinter printer;

    QPrintDialog printDialog(&printer, widget);

    if (printDialog.exec() == QDialog::Rejected) {
        return;
    }

    QPainter painter(&printer);
    widget->render(&painter);
}
/////////////////////////////////////////////////////////////////////////////////////////
void ListeMatriels::on_genererBarcode_clicked()
{
    //ui->actionswidgetMat->setCurrentIndex(0);
}

void ListeMatriels::on_retour5_2_clicked()
{
     ui->actionswidgetMat->setCurrentIndex(0);
      ui->barcode->clear();
}

void ListeMatriels::generalstats()
{
    QSqlQuery query;
    QVariant quantitetot = 0, prixtot = 0;
    QSet<QString> uniqueTypes; // Set to store unique types

    query.prepare("SELECT TYPE, PRIX, QUANTITEM, QUANTITEENDOM FROM Materiels");

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
    else
    {
        while (query.next()) {
            QString type = query.value(0).toString();

            quantitetot = quantitetot.toInt() + query.value(2).toInt() + query.value(3).toInt();

            prixtot = prixtot.toDouble() + query.value(1).toDouble() * (query.value(2).toDouble() + query.value(3).toDouble());

            if (uniqueTypes.contains(type)) {
                qDebug() << "Duplicate type detected:" << type;

            } else {

                uniqueTypes.insert(type);


            }
        }

        int numUniqueTypes = uniqueTypes.size();
        QString uniqueTypesText = QString::number(numUniqueTypes);
        QString quantitetotText = QString::number(quantitetot.toInt());
        QString prixtotText = QString::number(prixtot.toDouble());
        ui->statsmat1->setText(uniqueTypesText);
        ui->statsmat2->setText(quantitetotText);
        ui->statsmat3->setText(prixtotText);
        qDebug() << "Total Unique Types:" << numUniqueTypes;
        qDebug() << "Total Quantity:" << quantitetot.toInt();
        qDebug() << "Total Price:" << prixtot.toDouble();
    }
}

void ListeMatriels::on_damageMat_clicked()
{
Materiel m;


// Clear ComboBox to prevent repetition
ui->ideventdamage->clear();

// Populate ComboBox with event IDs
QSqlQuery query1;
if (query1.exec("SELECT ID_EVENT FROM EVENEMENT")) {
    while (query1.next()) {
        QString idevent = query1.value(0).toString();
        qDebug() << "Event ID:" << idevent; // Print the event ID for debugging
        ui->ideventdamage->addItem(idevent); // Add idevent to the combo box
    }
} else {
    qDebug() << "Failed to execute query:" << query1.lastError().text();
}

    m.displayLossAndSumQuantity(ui->lineEditTotalLoss, ui->lineEditTotalQuantity);
    ui->actionswidgetMat->setCurrentIndex(5);
}

void ListeMatriels::on_retourdamage_clicked()
{
    ui->actionswidgetMat->setCurrentIndex(0);
}

void ListeMatriels::on_cleardamage_clicked()
{
    Materiel materiel;

    materiel.repairDamage("");
    ui->TabaffichageMat->setModel(M.afficher_materiel("","",""));
}


void ListeMatriels::on_evaluercontrat_clicked()
{
    Materiel materiel;


    QString evaluerEvent = ui->ideventdamage->currentText();


    materiel.evaluerDernierContrat(evaluerEvent);

    ui->TabaffichageMat->setModel(M.afficher_materiel("","",""));
}

void ListeMatriels::on_decoderMat_clicked()
{

            QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (.png.jpg *.bmp)");
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

void ListeMatriels::on_retour5_3_clicked()
{

}

void ListeMatriels::on_retour5_4_clicked()
{

}

void ListeMatriels::on_decoderMat_2_clicked()
{

}

void ListeMatriels::on_pushButton_clicked()
{
    QUrl url("https://barcode.tec-it.com/en");
            QDesktopServices::openUrl(url);

            QString text1 = ui->ID_MAT_barcode->text();
               QString text2 = ui->Type_barcode->text();
               QString text3 = ui->idsalle_barcode->text();


               QString concatenatedText ="IDMAT " + text1 + " TYPE " + text2 + " IDSALLE " + text3;


               if (!concatenatedText.isEmpty()) {
                   QClipboard *clipboard = QApplication::clipboard();
                   clipboard->setText(concatenatedText);
               }
}

void ListeMatriels::on_commanderMat_clicked()
{
    Materiel materiel;
    materiel.commanderMateriel();
}
