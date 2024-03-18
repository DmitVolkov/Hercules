#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QGridLayout>
#include "udpclientserver.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "serialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FirstWindow; }
QT_END_NAMESPACE

class FirstWindow : public QDialog
{
    Q_OBJECT

public:
    FirstWindow(QWidget *parent = nullptr);
    ~FirstWindow();

private:
    Ui::FirstWindow *ui;
    QTabWidget *pTab;
    QGridLayout *pGLayoutFirstWindow;
    UdpClientServer *pUDP;
    TcpClient *pTcpClient;
    TcpServer *pTcpServer;
    SerialPort *pSerial;


};
#endif // FIRSTWINDOW_H
