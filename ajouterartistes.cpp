#include "ajouterartistes.h"
#include "ui_ajouterartistes.h"

AjouterArtistes::AjouterArtistes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterArtistes)
{
    ui->setupUi(this);
}

AjouterArtistes::~AjouterArtistes()
{
    delete ui;
}
