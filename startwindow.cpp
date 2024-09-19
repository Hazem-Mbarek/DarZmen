#include "startwindow.h"
#include "ui_startwindow.h"

Startwindow::Startwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Startwindow)
{
    ui->setupUi(this);

    setMaximumWidth(800);
    setMaximumHeight(400);
    ui->progressBar->setMinimum(1);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setRange(1,100);
}

Startwindow::~Startwindow()
{
    delete ui;
}

void Startwindow::start_loading()
{
    for(int value= ui->progressBar->minimum() ; value < ui->progressBar->maximum(); value++)
    {
        QThread::msleep(30);
        ui->progressBar->setValue(value);
        ui->label_Value->setText(QString::number(value) + " %");
        qApp->processEvents(QEventLoop::AllEvents);
    }

}
