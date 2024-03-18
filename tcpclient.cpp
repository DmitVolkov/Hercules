#include "tcpclient.h"



TcpClient::TcpClient()
{
    pCheckCorrectFields = new CheckingCorrectFields ;
    pTcpSocket = new QTcpSocket (this);
    stateButtonConnect = false;
    pGLatoutTcpClient = new QGridLayout (this);
    this->setLayout (pGLatoutTcpClient);
    TcpClient::inicializationUI();

}

void TcpClient::inicializationUI()
{
    //===============SettingsConnect ========
    pGBoxSettingsConnect = new QGroupBox ("Settings connect",this);
    pGLatoutTcpClient->addWidget (pGBoxSettingsConnect,0,2,Qt::AlignCenter);
    pGBoxSettingsConnect->setFixedSize (200,110);
    pGLatoutSettingsConnect = new QGridLayout (pGBoxSettingsConnect);
    pGBoxSettingsConnect->setLayout (pGLatoutSettingsConnect);
    pLEditIpHost = new QLineEdit (pGBoxSettingsConnect);
    pLEditIpHost->setInputMask ("000.000.000.000;_");
    pLEditIpHost->setFixedSize (100,20);
    pLEditPortHost = new QLineEdit (pGBoxSettingsConnect);
    pLEditPortHost->setFixedSize (60,20);
    pButtonConnect = new QPushButton ("Connect",pGBoxSettingsConnect);
    pButtonConnect->setFixedSize (70,20);
    connect (pButtonConnect, &QPushButton::clicked, this, [this](){
        if(stateButtonConnect){
            //nazhata
            stateButtonConnect=false;
            pButtonConnect->setText ("Conect");
            TcpClient::slot_disconect();
        }
        else{
            //ne nazhata
            stateButtonConnect=true;
            pButtonConnect->setText ("Disconect");
            TcpClient::slot_connect();
        }
    });
    pButtonPingHost = new QPushButton ("Ping", pGBoxSettingsConnect);
    pButtonPingHost->setFixedSize (70,22);
    connect (pButtonPingHost, &QPushButton::clicked, this, &TcpClient::slot_pingHost);
    pLabelIpHost = new QLabel ("Ip host:",pGBoxSettingsConnect);
    pLabelIpHost->setFixedSize (100,20);
    pLabelPortHost = new QLabel ("Port host:",pGBoxSettingsConnect);
    pLabelPortHost->setFixedSize (60,20);
    pGLatoutSettingsConnect->addWidget (pLabelIpHost,0,0,Qt::AlignLeft);
    pGLatoutSettingsConnect->addWidget (pLEditIpHost,1,0,Qt::AlignLeft);
    pGLatoutSettingsConnect->addWidget (pLabelPortHost,3,0,Qt::AlignLeft);
    pGLatoutSettingsConnect->addWidget (pLEditPortHost,4,0,Qt::AlignLeft);
    pGLatoutSettingsConnect->addWidget (pButtonConnect,1,2,Qt::AlignCenter);
    pGLatoutSettingsConnect->addWidget (pButtonPingHost,4,2,Qt::AlignCenter);

    //=========== Message Send ========================
    pGBoxMesSend = new QGroupBox ("Message",this);
    pGLatoutTcpClient->addWidget (pGBoxMesSend,2,0,Qt::AlignCenter);
    pGBoxMesSend->setFixedSize (500,130);
    pGLatoutMessageSend = new QGridLayout (pGBoxMesSend);
    pGBoxMesSend->setLayout (pGLatoutMessageSend);
    pLEditMesage1 = new QLineEdit (pGBoxMesSend);
    pLEditMesage1->setFixedSize (410,20);
    pLEditMesage2 = new QLineEdit (pGBoxMesSend);
    pLEditMesage2->setFixedSize (410,20);
    pLEditMesage3 = new QLineEdit (pGBoxMesSend);
    pLEditMesage3->setFixedSize (410,20);
    pButtonMesSend1 = new QPushButton ("Send",pGBoxMesSend);
    pButtonMesSend1->setFixedSize (60,20);
    connect (pButtonMesSend1, &QPushButton::clicked, this,&TcpClient::slot_sendMes1);
    pButtonMesSend2 = new QPushButton ("Send",pGBoxMesSend);
    pButtonMesSend2->setFixedSize (60,20);
    connect (pButtonMesSend2, &QPushButton::clicked, this,&TcpClient::slot_sendMes2);
    pButtonMesSend3 = new QPushButton ("Send",pGBoxMesSend);
    pButtonMesSend3->setFixedSize (60,20);
    connect (pButtonMesSend3, &QPushButton::clicked, this,&TcpClient::slot_sendMes3);
    pGLatoutMessageSend->addWidget (pLEditMesage1,0,0,Qt::AlignLeft);
    pGLatoutMessageSend->addWidget (pLEditMesage2,2,0,Qt::AlignLeft);
    pGLatoutMessageSend->addWidget (pLEditMesage3,4,0,Qt::AlignLeft);
    pGLatoutMessageSend->addWidget (pButtonMesSend1,0,2,Qt::AlignRight);
    pGLatoutMessageSend->addWidget (pButtonMesSend2,2,2,Qt::AlignRight);
    pGLatoutMessageSend->addWidget (pButtonMesSend3,4,2,Qt::AlignRight);

    //================History message ====================
    pGBoxHistoryMes = new QGroupBox ("Recive\\Trancive data",this);
    pGLatoutTcpClient->addWidget (pGBoxHistoryMes,0,0,Qt::AlignCenter);
    pGBoxHistoryMes->setFixedSize (450,400);
    pTEditHistoryMesage = new QTextEdit (pGBoxHistoryMes);
    pTEditHistoryMesage->setFixedSize (440,390);

    TcpClient::slot_diactivativeButtonSend();
}

QString TcpClient::getDatetTimeString()
{
    return QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
}

void TcpClient::historyMesageWrite(QString str)
{
    strHistoryMesage +=QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+" << "+str+"\n";
    pTEditHistoryMesage->setText (strHistoryMesage);
    qDebug()<<QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+"| "+str+"\n";

}


void TcpClient::slot_activativeButtonSend()
{
    pButtonMesSend1->setEnabled (true);
    pButtonMesSend2->setEnabled (true);
    pButtonMesSend3->setEnabled (true);

}

void TcpClient::slot_diactivativeButtonSend()
{
    pButtonMesSend1->setEnabled (false);
    pButtonMesSend2->setEnabled (false);
    pButtonMesSend3->setEnabled (false);
}

bool TcpClient::slot_checkingCorrectFieldsSettingsTcp()
{
    QString temp1=pLEditIpHost->text ();
    QString temp2=pLEditPortHost->text();
    return (pCheckCorrectFields->checkinIpHost (temp1) && pCheckCorrectFields->checkingPortHost (temp2)) ? true : false ;
}

void TcpClient::slot_pingHost()
{
    QString temp = pLEditIpHost->text ();
    if (pCheckCorrectFields->checkinIpHost (temp)){
        //если поля соответствуют
        pProcessPing = new QProcess (this);
        connect (pProcessPing, &QProcess::readyReadStandardOutput, this, &TcpClient::slot_dataOnStdOutPing);

#ifdef Q_OS_UNIX

    // rabotaet na linux
        QString strCommand="ping -c 3 "+pLEditIpHost->text ();


#endif
#ifdef Q_OS_WINDOWS
    //rabotatet na windows
        QString strCommand="ping "+pLEditIpHost->text ();
#endif
        pProcessPing->start ();
//        pProcessPing->start (strCommand);
    }
    else{
        //если поля не соответствуют
        TcpClient::historyMesageWrite("Incorrect write fields settings connect.");
    }

}

void TcpClient::slot_connect()
{
    if (TcpClient::slot_checkingCorrectFieldsSettingsTcp()){
        //если поля соответствуют
        TcpClient::slot_activativeButtonSend();
        QString ipHostTemp=pLEditIpHost->text ();
        int portHostTemp=pLEditPortHost->text ().toInt ();
        pTcpSocket->connectToHost (ipHostTemp, portHostTemp);
        connect (pTcpSocket, &QTcpSocket::readyRead, this, &TcpClient::slot_readyRead);
        connect (pTcpSocket, QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error), this, &TcpClient::slot_error);
    }
    else{
        //если поля не соответствуют
        TcpClient::historyMesageWrite("Incorrect write fields settings connect.");
    }

}

void TcpClient::slot_disconect()
{
    TcpClient::slot_diactivativeButtonSend();
    pTcpSocket->close ();
    TcpClient::historyMesageWrite("Disconect signal from host");
}

void TcpClient::slot_error(QAbstractSocket::SocketError err)
{
    QString strError = "Error" + (
                err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused by the peer (or timed out)."
              : err == QAbstractSocket::RemoteHostClosedError ? "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent."
              : err == QAbstractSocket::HostNotFoundError ? "The host address was not found."
              : err == QAbstractSocket::SocketAccessError ? "The socket operation failed because the application lacked the required privileges."
              : err == QAbstractSocket::SocketResourceError ? "The local system ran out of resources (e.g., too many sockets)."
              : err == QAbstractSocket::SocketTimeoutError ? "The socket operation timed out."
              : err == QAbstractSocket::DatagramTooLargeError ? "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes)."
              : err == QAbstractSocket::NetworkError ? "An error occurred with the network (e.g., the network cable was accidentally plugged out)."
              : err == QAbstractSocket::AddressInUseError ? "The address specified to QAbstractSocket::bind() is already in use and was set to be exclusive."
              : err == QAbstractSocket::SocketAddressNotAvailableError ? "The address specified to QAbstractSocket::bind() does not belong to the host."
              : err == QAbstractSocket::UnsupportedSocketOperationError ? "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support)."
              : err == QAbstractSocket::ProxyAuthenticationRequiredError ? "The socket is using a proxy, and the proxy requires authentication."
              : err == QAbstractSocket::SslHandshakeFailedError ? "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)"
              : err == QAbstractSocket::UnfinishedSocketOperationError ? "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background)."
              : err == QAbstractSocket::ProxyConnectionRefusedError ? "Could not contact the proxy server because the connection to that server was denied."
              : err == QAbstractSocket::ProxyConnectionClosedError ? "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)."
              : err == QAbstractSocket::ProxyConnectionTimeoutError ? "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase."
              : err == QAbstractSocket::ProxyNotFoundError ? "The proxy address set with setProxy() (or the application proxy) was not found."
              : err == QAbstractSocket::ProxyProtocolError ? "The connection negotiation with the proxy server failed, because the response from the proxy server could not be understood."
              : err == QAbstractSocket::OperationError ? "An operation was attempted while the socket was in a state that did not permit it."
              : err == QAbstractSocket::SslInternalError ? "The SSL library being used reported an internal error. This is probably the result of a bad installation or misconfiguration of the library."
              : err == QAbstractSocket::SslInvalidUserDataError ? "Invalid data (certificate, key, cypher, etc.) was provided and its use resulted in an error in the SSL library."
              : err == QAbstractSocket::TemporaryError ? "A temporary error occurred (e.g., operation would block and socket is non-blocking)."
              : err == QAbstractSocket::UnknownSocketError ? "An unidentified error occurred."
                                                           : QString(pTcpSocket->errorString()));
    TcpClient::historyMesageWrite(strError);
}

void TcpClient::slot_readyRead()
{
    QByteArray arrayRx=pTcpSocket->readAll ();
    TcpClient::historyMesageWrite(QString(arrayRx).simplified());

}

void TcpClient::slot_sendMessage(QString mes)
{
    QByteArray mesageTx = mes.toUtf8 ();
    pTcpSocket->write (mesageTx);
    TcpClient::historyMesageWrite(mes);

}

void TcpClient::slot_sendMes1()
{
    TcpClient::slot_sendMessage(pLEditMesage1->text ());
}

void TcpClient::slot_sendMes2()
{
    TcpClient::slot_sendMessage(pLEditMesage2->text ());
}

void TcpClient::slot_sendMes3()
{
    TcpClient::slot_sendMessage(pLEditMesage3->text ());
}

void TcpClient::slot_dataOnStdOutPing()
{
    QByteArray temp=pProcessPing->readAllStandardOutput();
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    TcpClient::slot_sendMessage(codec->toUnicode(temp));
}

