#include "ajouterpersonnels.h"
#include "ui_ajouterpersonnels.h"

AjouterPersonnels::AjouterPersonnels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterPersonnels)
{
    ui->setupUi(this);
}

AjouterPersonnels::~AjouterPersonnels()
{
    delete ui;
}
