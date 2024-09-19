#include "ajoutersalles.h"
#include "ui_ajoutersalles.h"

AjouterSalles::AjouterSalles(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterSalles)
{
    ui->setupUi(this);
}

AjouterSalles::~AjouterSalles()
{
    delete ui;
}
