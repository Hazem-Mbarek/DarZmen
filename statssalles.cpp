#include "statssalles.h"
#include "ui_statssalles.h"

StatsSalles::StatsSalles(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatsSalles)
{
    ui->setupUi(this);
}

StatsSalles::~StatsSalles()
{
    delete ui;
}
