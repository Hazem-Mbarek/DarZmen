#include "statsevents.h"
#include "ui_statsevents.h"

StatsEvents::StatsEvents(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatsEvents)
{
    ui->setupUi(this);
}

StatsEvents::~StatsEvents()
{
    delete ui;
}
