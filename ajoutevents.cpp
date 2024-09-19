#include "ajoutevents.h"
#include "ui_ajoutevents.h"

AjoutEvents::AjoutEvents(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjoutEvents)
{
    ui->setupUi(this);
}

AjoutEvents::~AjoutEvents()
{
    delete ui;
}
