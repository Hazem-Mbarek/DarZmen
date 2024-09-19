#include "listesalles.h"
#include "ui_listesalles.h"
#include "listeevents.h"
#include "listecontrats.h"
#include "listeartistes.h"
#include "listepersonnels.h"
#include "listematriels.h"
#include "salles.h" // Assurez-vous que le fichier salles.h est inclus

#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

ListeSalles::ListeSalles(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListeSalles)
{
    ui->setupUi(this);
    ui->tableView->setModel(stmp.afficher());
}

ListeSalles::~ListeSalles()
{
    delete ui;
}

void ListeSalles::setSalleButtonStyle(const QString &style) {
    ui->salles->setStyleSheet(style);
}

void ListeSalles::on_AjoutSalles_clicked()
{
    ui->actionswidgetSalles->setCurrentIndex(1);
}

void ListeSalles::on_retoursalles1_clicked()
{
    ui->actionswidgetSalles->setCurrentIndex(0);
}

void ListeSalles::on_retoursalles2_clicked()
{
    ui->actionswidgetSalles->setCurrentIndex(0);
}

void ListeSalles::on_employes_clicked()
{
    hide();
    ListePersonnels *persopage = new ListePersonnels(this);
    persopage->show();
    persopage->setPersoButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeSalles::on_artistes_clicked()
{
    hide();
    ListeArtistes *artistepage = new ListeArtistes(this);
    artistepage->show();
    artistepage->setArtisteButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeSalles::on_contrats_clicked()
{
    hide();
    ListeContrats *contratpage = new ListeContrats(this);
    contratpage->show();
    contratpage->setContratButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeSalles::on_events_clicked()
{
    hide();
    ListeEvents *eventpage = new ListeEvents(this);
    eventpage->show();
    eventpage->setEventsButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeSalles::on_matariel_clicked()
{
    hide();
    ListeMatriels *matpage = new ListeMatriels(this);
    matpage->show();
    matpage->setMatButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}

void ListeSalles::on_salles_clicked()
{
    hide();
    ListeSalles *sallepage = new ListeSalles(this);
    sallepage->show();
    sallepage->setSalleButtonStyle("background-color: rgb(215, 157, 27); color: white; border: 4px solid rgb(215, 157, 27); border-radius: 20px; outline: none;");
}



void ListeSalles::on_pushButton_23_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString taille = ui->lineEdit_taille->text();
    QString prix = ui->lineEdit_prix->text();

    salles s(id, taille, prix);

    bool test = s.ajouter();

    if (test) {
        QString emailResponsable = ui->lineEdit_email->text();
        stmp.enregistrerTraitement(id,taille,prix, "Ajout", emailResponsable);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\nClick Cancel to exit"), QMessageBox::Cancel);
        ui->actionswidgetSalles->setCurrentIndex(0);
        ui->tableView->setModel(stmp.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Ajout non effectué."), QMessageBox::Cancel);
    }
}

void ListeSalles::on_pushButton_20_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }

    QModelIndex idIndex = selectedIndexes.at(0);
    int id = idIndex.data(Qt::DisplayRole).toInt(); // Assuming the id is stored as an integer
    salles s;

    bool deleted = s.supprimer(id);


    if (deleted) {
        qDebug() << "Entry with ID =" << id << " deleted successfully!";
        ui->tableView->setModel(stmp.afficher());
    } else {
        qDebug() << "Failed to delete entry with ID =" << id;
    }
}





void ListeSalles::on_pushButton_21_clicked()
{
    ui->actionswidgetSalles->setCurrentIndex(2);
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        qDebug() << "No row selected.";
        return;
    }
    QModelIndex idIndex = selectedIndexes.at(0);
    int id = idIndex.data(Qt::DisplayRole).toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM salle WHERE idsalle = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        qDebug() << query.value(0);
        qDebug() << query.value(1);
        qDebug() << query.value(2);
        ui->lineEdit_idmodif->setText(query.value(0).toString());
        ui->lineEdit_taillemodif->setText(query.value(1).toString());
        ui->lineEdit_prixmodif->setText(query.value(2).toString());
    }
}

void ListeSalles::on_pushButton_24_clicked()
{
    QString id = ui->lineEdit_idmodif->text();
    QString taille = ui->lineEdit_taillemodif->text();
    QString prix = ui->lineEdit_prixmodif->text();

    salles s;
    s.setIdSalles(id);
    s.setTaille(taille);
    s.setPrix(prix);

    bool test = s.modifier(id, taille, prix);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\nClick Cancel to exit"), QMessageBox::Cancel);
        ui->actionswidgetSalles->setCurrentIndex(0);
        ui->tableView->setModel(stmp.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Modification non effectuée."), QMessageBox::Cancel);
    }
}



void ListeSalles::on_pushButton_search_clicked()
{
    QString searchString = ui->lineEdit_search->text();
    QSqlQueryModel* searchResult = stmp.rechercher(searchString);
    ui->tableView->setModel(searchResult);
}

void ListeSalles::on_pushButton_tri_clicked()
{
    QString critere = ui->lineEdit_critere->text();
    ui->tableView->setModel(stmp.trier(critere));
}


void ListeSalles::on_StatsSalles_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM salle");

        ui->tableView->setModel(model);
}


void ListeSalles::on_pushButton_7_clicked()
{
    QString emailartist = ui->lineEdit_email->text();


        if (emailartist == "root@root.com")
        {
            QMessageBox::information(this, "Succès", "Connexion avec succès");
            ui->actionswidgetSalles->setCurrentIndex(0);
        }
        else
        {QSqlQuery query;
            //QSqlQuery QueryGetUser(DBConnection);
            query.prepare("SELECT * FROM artiste WHERE emailartist = :emailartist");
            query.bindValue(":emailartist", emailartist);


            if (query.exec() && query.next())
            {
                QMessageBox::information(this, "Succès", "Connexion avec succès");
                ui->actionswidgetSalles->setCurrentIndex(0);
            }
            else
            {
                QMessageBox::information(this, "Erreur", "Vérifiez l'adresse et le mot de passe");
            }
        }
}

/*void ListeSalles::on_pushButton_8_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();
      model->setQuery("SELECT FROM historique");

            // Configurez le QTableView pour afficher les données
       ui->tableView_2->setModel(model);

}*/


/*void ListeSalles::on_pushButton_11_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();
      model->setQuery("SELECT FROM historique");

            // Configurez le QTableView pour afficher les données
       ui->tableView_3->setModel(model);
}*/


void ListeSalles::on_retoursalles2_7_clicked()
{
    ui->actionswidgetSalles->setCurrentIndex(0);
}

void ListeSalles::on_AjoutSalles_2_clicked()
{
    ui->actionswidgetSalles->setCurrentIndex(4);
}

void ListeSalles::on_AjoutSalles_3_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();
      model->setQuery("SELECT* FROM historique");

            // Configurez le QTableView pour afficher les données
       ui->tableView_3->setModel(model);
}

void ListeSalles::on_starttest_clicked()
{
    dialog.exec();
}
