#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->templcdnumber->display("-----");
    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";
    temperature_value = 0.0;



     //   Identify the port the arduino uno is on.

    bool arduino_is_available = false;
    QString arduino_uno_port_name;
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the arduino uno
            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available){
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::readSerial()
{
    QSqlQuery query;
    serialData += arduino->readAll(); // Append newly received data to serialData

    // Check if serialData contains at least one complete temperature reading
    while (serialData.contains(',')) {
        // Find the position of the first comma
        int commaIndex = serialData.indexOf(',');

        // Extract the temperature reading from serialData
        QString temperatureString = serialData.left(commaIndex);
        serialData = serialData.mid(commaIndex + 1); // Remove the processed data including comma

        // Convert the temperature reading to double
        bool conversionOk;
        double temperature = temperatureString.toDouble(&conversionOk);
        int id=2025;
        query.prepare("SELECT temp from SALLE WHERE idsalle = :id");
        query.bindValue(":id", id);
        if(query.exec() && query.next() && conversionOk)
        {
            qDebug()<<"querry is up";
            qDebug()<<"TEMP BASE = "<<query.value(0).toDouble();
            updateTemperature(QString::number(temperature, 'f', 2)); // Display temperature with 2 decimal places
            if (temperature > query.value(0).toDouble())
            {
                qDebug()<<"Statuus = "<<1;
            }
            else
            {
                qDebug()<<"Statuus = "<<0;
            }
        }
        else
        {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        // Check if conversion was successful
        /*if (conversionOk && query.exec()) {
            // Update the temperature display
            updateTemperature(QString::number(temperature, 'f', 2)); // Display temperature with 2 decimal places
            if (temperature > query.value(0).toDouble())
            {
                qDebug()<<"Statuus = "<<1;
            }
            else
            {
                qDebug()<<"Statuus = "<<0;
            }

        }*/
    }
}

    void Dialog::updateTemperature(QString sensor_reading)
    {
        //  update the value displayed on the lcdNumber
        ui->templcdnumber->display(sensor_reading);
    }

