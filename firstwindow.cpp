#include "firstwindow.h"
#include "ui_firstwindow.h"

FirstWindow::FirstWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FirstWindow)
{
    ui->setupUi(this);
    this->setFixedSize (700,600);
    pGLayoutFirstWindow = new QGridLayout (this);
    this->setLayout (pGLayoutFirstWindow);
    pTab = new QTabWidget (this);
    pGLayoutFirstWindow->addWidget (pTab);
    pUDP = new UdpClientServer;
    pTab->addTab (pUDP, "UDP");
    pTcpClient = new TcpClient;
    pTab->addTab (pTcpClient,"TCP client");
    pTcpServer = new TcpServer (this);
    pTab->addTab (pTcpServer,"TCP server");
    pSerial = new SerialPort;
    pTab->addTab (pSerial,"Serial port");

}

FirstWindow::~FirstWindow()
{
    delete ui;
}


