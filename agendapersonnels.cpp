#include "agendapersonnels.h"
#include "ui_agendapersonnels.h"




AgendaPersonnels::AgendaPersonnels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AgendaPersonnels)
{
    ui->setupUi(this);
}

AgendaPersonnels::~AgendaPersonnels()
{
    delete ui;
}
