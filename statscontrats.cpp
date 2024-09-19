#include "statscontrats.h"
#include "ui_statscontrats.h"

StatsContrats::StatsContrats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatsContrats)
{
    ui->setupUi(this);
}

StatsContrats::~StatsContrats()
{
    delete ui;
}
