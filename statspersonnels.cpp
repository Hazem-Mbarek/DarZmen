#include "statspersonnels.h"
#include "ui_statspersonnels.h"

StatsPersonnels::StatsPersonnels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatsPersonnels)
{
    ui->setupUi(this);
}

StatsPersonnels::~StatsPersonnels()
{
    delete ui;
}
