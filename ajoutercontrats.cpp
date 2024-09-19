#include "ajoutercontrats.h"
#include "ui_ajoutercontrats.h"

AjouterContrats::AjouterContrats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterContrats)
{
    ui->setupUi(this);
}

AjouterContrats::~AjouterContrats()
{
    delete ui;
}
