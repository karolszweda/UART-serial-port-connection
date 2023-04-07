#ifndef CONNWINDOW_H
#define CONNWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class ConnWindow; }
QT_END_NAMESPACE

class ConnWindow : public QMainWindow
{
    Q_OBJECT

public:
    ConnWindow(QWidget *parent = nullptr);
    ~ConnWindow();

private slots:
    void on_pushButton_search_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_close_clicked();
    void readFromPort();

    void on_pushButton_diode_on_clicked();

    void on_pushButton_diode_off_clicked();

private:
    Ui::ConnWindow *ui;
    QSerialPort *device; // object's pointer
    void addToLogs(QString message);
    void sendMessageToDevice(QString message);
};
#endif // CONNWINDOW_H
