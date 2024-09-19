#include "calendrierevents.h"
#include "ui_calendrierevents.h"

CalendrierEvents::CalendrierEvents(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalendrierEvents)
{
    ui->setupUi(this);
}

CalendrierEvents::~CalendrierEvents()
{
    delete ui;
}
