#include "connwindow.h"
#include "ui_connwindow.h"


#include <QSerialPortInfo>
#include <QList>
#include <QDateTime>

ConnWindow::ConnWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ConnWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this); //using '(this)' I don't have to delete heap object in destructor below (child <- parent relation)
}

ConnWindow::~ConnWindow()
{
    delete ui;
    //delete device; //I would have to use it if I didn't use "this"
}


void ConnWindow::on_pushButton_search_clicked()
{
    this->addToLogs("Looking for devices...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    for(int i = 0; i < devices.count(); i++){
        this->addToLogs(devices.at(i).portName() + " " + devices.at(i).description());
        ui->comboBox_devices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }

}

void ConnWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textLogs->append(currentDateTime + "\t" + message);
}


void ConnWindow::on_pushButton_connect_clicked()
{
    if(ui->comboBox_devices->count() == 0){  //checks if there are any devices to connect
        this->addToLogs("No devices were found");
        return;
    }

    QString portName = ui->comboBox_devices->currentText().split("\t").first();
    this->device->setPortName(portName);

    if(!device->isOpen()){
        if(device->open(QSerialPort::ReadWrite)){ //opening a serial port with read and write communications || returns true if success
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            this->addToLogs("Opened serial port");
        } else {
            this->addToLogs("Error opening serial port");
        }
    } else {
        this->addToLogs("Port is already open");
    }
}

void ConnWindow::on_pushButton_close_clicked()
{
    if(this->device->isOpen()){
        this->device->close(); //
        this->addToLogs("Closed connection");
    } else {
        this->addToLogs("Port was not opened");
        return;
    }
}

