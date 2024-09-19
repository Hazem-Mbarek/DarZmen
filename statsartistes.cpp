#include "statsartistes.h"
#include "ui_statsartistes.h"

StatsArtistes::StatsArtistes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatsArtistes)
{
    ui->setupUi(this);
}

StatsArtistes::~StatsArtistes()
{
    delete ui;
}
