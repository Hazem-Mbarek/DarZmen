#include "statsmatriels.h"
#include "ui_statsmatriels.h"

StatsMatriels::StatsMatriels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatsMatriels)
{
    ui->setupUi(this);
}

StatsMatriels::~StatsMatriels()
{
    delete ui;
}
