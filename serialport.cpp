#include "serialport.h"


SerialPort::SerialPort()
{    
    SerialPort::initializationVariables();
    SerialPort::initializationUI();
    pGLcentral = new QGridLayout (this);
    this->setLayout (pGLcentral);
    pGLcentral->addWidget (pGBhistoryData, 0 ,0 , Qt::AlignCenter);
    pGLcentral->addWidget (pGBsettingSerial,0,2,Qt::AlignTop);
    pGLcentral->addWidget (pGBtranciveData,2,0,Qt::AlignCenter);
    SerialPort::set_serialPortCBname();

}

void SerialPort::initializationUI()
{
    //=======setting com port ==============
    int sizeHeigth = 20;
    int sizeWidth = 70;
    pGBsettingSerial = new QGroupBox ("Settings",this);
    pGBsettingSerial->setFixedSize (80,370);
    pGLsettingSerial = new QGridLayout (pGBsettingSerial);
    pGBsettingSerial->setLayout (pGLsettingSerial);

    pLnamePort = new QLabel ("Name port:",pGBsettingSerial);
    pLnamePort->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pLnamePort,0,0,Qt::AlignLeft);
    pCBnamePort = new QComboBox(pGBsettingSerial);
    pCBnamePort->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pCBnamePort,1,0,Qt::AlignCenter);

    pLbaud = new QLabel("Speed:",pGBsettingSerial);
    pLbaud->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pLbaud,3,0,Qt::AlignLeft);
    pCBbaud = new QComboBox (pGBsettingSerial);
    pCBbaud->setFixedSize (sizeWidth,sizeHeigth);
    pCBbaud->addItems (strListBaud);
    pCBbaud->setCurrentIndex (9);
    pGLsettingSerial->addWidget (pCBbaud,4,0,Qt::AlignCenter);

    pLdataSize = new QLabel ("Data size:",pGBsettingSerial);
    pLdataSize->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pLdataSize,6,0,Qt::AlignLeft);
    pSBdataSize = new QSpinBox (pGBsettingSerial);
    pSBdataSize->setValue (8);
    pSBdataSize->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pSBdataSize,7,0,Qt::AlignCenter);

    pLmode = new QLabel ("Stop bits:",pGBsettingSerial);
    pLmode->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pLmode,9,0,Qt::AlignLeft);
    pSBmode =  new QSpinBox (pGBsettingSerial);
    pSBmode->setValue (1);
    pSBmode->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pSBmode,10,0,Qt::AlignCenter);

    pLparity = new QLabel ("Parity:", pGBsettingSerial);
    pLparity->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pLparity,12,0,Qt::AlignLeft);
    pCBparity = new QComboBox (pGBsettingSerial);
    pCBparity->setFixedSize (sizeWidth,sizeHeigth);
    pCBparity->addItems (strListParity);
    pGLsettingSerial->addWidget (pCBparity,13,0,Qt::AlignCenter);

    pLhandShake = new QLabel ("Flow control:",pGBsettingSerial);
    pLhandShake->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pLhandShake,15,0,Qt::AlignLeft);
    pCBflowControl = new QComboBox (pGBsettingSerial);
    pCBflowControl->addItems (strListHandshake);
    pCBflowControl->setFixedSize (sizeWidth,sizeHeigth);
    pGLsettingSerial->addWidget (pCBflowControl,16,0,Qt::AlignCenter);

    QLabel *pLspacer = new QLabel(pGBsettingSerial);
    pLspacer->setFixedSize (30,30);
    pGLsettingSerial->addWidget (pLspacer,18,0,Qt::AlignCenter);
    pQPBopen = new QPushButton ("Open",pGBsettingSerial);
    pQPBopen->setFixedSize (sizeWidth,sizeHeigth+5);
    connect (pQPBopen, &QPushButton::clicked, this, &SerialPort::slot_openComPort);
    pGLsettingSerial->addWidget (pQPBopen,19,0,Qt::AlignBottom);

    //========== history data ============
    pGBhistoryData = new QGroupBox("History data", this);
    pGBhistoryData->setFixedSize (550,450);
    pGLhistoryData = new QGridLayout (pGBhistoryData);
    pGBhistoryData->setLayout (pGLhistoryData);
    pTEhistorySerial = new QTextEdit (pGBhistoryData);
    pTEhistorySerial->setFixedSize (530,410);
    pGLhistoryData->addWidget (pTEhistorySerial, 0, 0 ,Qt::AlignCenter);

    //========trancive data======
    pGBtranciveData = new QGroupBox ("Trancive data",this);
    pGBtranciveData->setFixedSize (550,80);
    pGLtransiveData = new QGridLayout (pGBtranciveData);
    pGBtranciveData->setLayout (pGLtransiveData);
    pLEtranciveData = new QLineEdit(pGBtranciveData);
    pLEtranciveData->setFixedSize (450,30);
    pGLtransiveData->addWidget (pLEtranciveData, 0, 0, Qt::AlignLeft);
    pPBtranciveData = new QPushButton ("Send",pGBtranciveData);
    connect (pPBtranciveData, &QPushButton::clicked, this, &SerialPort::slot_writeSerialPort);
    pPBtranciveData->setEnabled (false);
    pPBtranciveData->setFixedSize (60,30);
    pGLtransiveData->addWidget (pPBtranciveData, 0, 2,Qt::AlignCenter);
    connect (pPBtranciveData, &QPushButton::clicked, this, &SerialPort::slot_writeSerialPort);

}

void SerialPort::initializationVariables()
{
    stateButonOpen = true;
    strListName<<"COM 1"<<"COM 2"<<"COM 3"<<"COM 4"<<"COM 5"<<"COM 6"<<"COM 7"<<"COM 8";
    strListBaud<<"50"<<"75"<<"110"<<"150"<<"300"<<"600"<<"1200"<<"2400"<<"4800"<<"9600"<<"19200"<<"38400"<<"57600"<<"115200";
    strListDataSize<<"7"<<"8";
    strListParity<<"No"<<"Even"<<"Odd"<<"Space"<<"Mark";
    strListHandshake<<"OFF"<<"RTS/CTS"<<"XON/XOFF";
    strListMode <<"none"<<"1"<<"2"<<"3"<<"4"<<"5";
}

void SerialPort::addHisoruSerial(QString inHistory)
{
    qDebug()<<QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+" << "+inHistory;
    strHisorySerial+=QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+" << "+inHistory+"\n";
    pTEhistorySerial->setText (strHisorySerial);
}

void SerialPort::set_serialPortCBname()
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        pCBnamePort->addItem(info.portName());
}

void SerialPort::inicializingPortSerial()
{

    strPortName = pCBnamePort->currentText ();
    set_baudRate = pCBbaud->currentText ().toInt ();
    set_DataBits = pSBdataSize->value ();
    set_StopBits = pSBmode->value ();
    set_Control = pCBflowControl->currentText ();
    set_Parity = pCBparity->currentText ();

    qDebug()<<strPortName<<set_baudRate<<set_DataBits<<set_StopBits<<set_Control<<set_Parity;
    pSerial = new QSerialPort (this);
    strPortName=pCBnamePort->currentText ();

    pSerial->setPortName (strPortName);
    pSerial->setBaudRate (set_baudRate);
    pSerial->setDataBits (QSerialPort::DataBits (set_DataBits));
    pSerial->setStopBits (QSerialPort::StopBits (set_StopBits));

    if (set_Control=="RTS/CTS") pSerial->setFlowControl (QSerialPort::HardwareControl);
    if (set_Control=="XON/XOFF") pSerial->setFlowControl (QSerialPort::SoftwareControl);
    if (set_Control=="OFF") pSerial->setFlowControl (QSerialPort::NoFlowControl); //default

    if(set_Parity=="No") pSerial->setParity (QSerialPort::NoParity); //default
    if(set_Parity=="Even") pSerial->setParity (QSerialPort::EvenParity);
    if(set_Parity=="Odd") pSerial->setParity (QSerialPort::OddParity);
    if(set_Parity=="Space") pSerial->setParity (QSerialPort::SpaceParity);
    if(set_Parity=="Mark") pSerial->setParity (QSerialPort::MarkParity);



    connect (pSerial, &QSerialPort::readyRead, this, &SerialPort::slot_readSerialPort);
    connect (pSerial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error), this, &SerialPort::slot_errorSerialPort);
    pSerial->open(QIODevice::ReadWrite);

}

void SerialPort::slot_openComPort()
{
    if (stateButonOpen){
        //ne nezhata
        stateButonOpen = false;
        pQPBopen->setText ("Close");
        pPBtranciveData->setEnabled (true);
        SerialPort::inicializingPortSerial();
    }
    else {
        //nazhata
        stateButonOpen = true;
        pQPBopen->setText ("Open");
        pPBtranciveData->setEnabled (false);
    }

}

void SerialPort::slot_writeSerialPort()
{
    if (!stateButonOpen){
        QByteArray tempByte=pLEtranciveData->text ().toUtf8 ();
        pSerial->write (tempByte);
        SerialPort::addHisoruSerial(pLEtranciveData->text ());
    }
}

void SerialPort::slot_readSerialPort()
{
    SerialPort::addHisoruSerial(pSerial->readAll ());

}

void SerialPort::slot_writeNameport(QString namePort)
{
    strPortName=namePort;
}

void SerialPort::slot_writeBaudPort(QString baudT)
{
   // number_baudRate=baudT.toInt ();
}

void SerialPort::slot_writeStopBits(QString stpBits)
{
    set_StopBits=stpBits.toInt ();
}

void SerialPort::slot_errorSerialPort(QSerialPort::SerialPortError err)
{
    QString strError = "Error "+(
                err==QSerialPort::NoError ? "No error occurred."
              : err==QSerialPort::DeviceNotFoundError ? "An error occurred while attempting to open an non-existing device."
              : err==QSerialPort::PermissionError ? "An error occurred while attempting to open an already opened device by another process or a user not having enough permission and credentials to open."
              : err==QSerialPort::OpenError ? "An error occurred while attempting to open an already opened device in this object."
              : err==QSerialPort::NotOpenError ? "This error occurs when an operation is executed that can only be successfully performed if the device is open."
              : err==QSerialPort::WriteError ? "An I/O error occurred while writing the data."
              : err==QSerialPort::ReadError ? "An I/O error occurred while reading the data."
              : err==QSerialPort::ResourceError ? "An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system."
              : err==QSerialPort::UnsupportedOperationError ? "The requested device operation is not supported or prohibited by the running operating system."
              : err==QSerialPort::TimeoutError ? "A timeout error occurred. "
              : err==QSerialPort::UnknownError ? "An unidentified error occurred."
              :QString(pSerial->errorString ()));
    SerialPort::addHisoruSerial(strError);

}


