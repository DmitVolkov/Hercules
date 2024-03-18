#include "tcpserver.h"


TcpServer::TcpServer(QObject *parent)
{
    pChecked = new CheckingCorrectFields;
    stateButtonConnect=false;
    pGLayoutTcpServer = new QGridLayout (this);
    this->setLayout (pGLayoutTcpServer);
    TcpServer::setupUIsettings();

}

void TcpServer::setupUIsettings()
{
    //===============SettingsConnect ========
    pGBoxServerSettings = new QGroupBox ("Setting server:", this);
    pGLayoutTcpServer->addWidget (pGBoxServerSettings,0,2,Qt::AlignTop);
    pGBoxServerSettings->setFixedSize (200,80);
    pGLayoutServerSettings = new QGridLayout (pGBoxServerSettings);
    pGBoxServerSettings->setLayout (pGLayoutServerSettings);
    pButtonConnect = new QPushButton ("Connect", pGBoxServerSettings);
    connect(pButtonConnect, &QPushButton::clicked, this, &TcpServer::slot_bindPort);
    pButtonConnect->setFixedSize (70,25);
    pGLayoutServerSettings->addWidget (pButtonConnect,1,2,Qt::AlignCenter);
    pLabelPort = new QLabel ("Port:",pGBoxServerSettings);
    pLabelPort->setFixedSize (60,15);
    pGLayoutServerSettings->addWidget (pLabelPort,0,0,Qt::AlignLeft);
    pLEditPort = new QLineEdit (pGBoxServerSettings);
    //pLEditPort->setInputMask (M);
    pLEditPort->setFixedSize (60,25);
    pGLayoutServerSettings->addWidget (pLEditPort,1,0,Qt::AlignLeft);

    //=================client connection status ============
    pGBoxClientConnectStatuse = new QGroupBox ("Client connection statuse:",this);
    pGLayoutTcpServer->addWidget (pGBoxClientConnectStatuse,1,2,Qt::AlignTop);
    pGBoxClientConnectStatuse->setFixedSize (200,150);
    pGLayoutClientConectStatuse =new QGridLayout (pGBoxClientConnectStatuse);
    pGBoxClientConnectStatuse->setLayout (pGLayoutClientConectStatuse);
    pTEditClientConnectionStatuse = new QTextEdit (pGBoxClientConnectStatuse);
    pTEditClientConnectionStatuse->setFixedSize (180,120);
    pTEditClientConnectionStatuse->setReadOnly (true);
    pGLayoutClientConectStatuse->addWidget (pTEditClientConnectionStatuse,0,0,Qt::AlignCenter);


    //=====================trancive Data  =========
    pGBoxTrancivedData = new QGroupBox ("Trancive data:",this);
    pGLayoutTcpServer->addWidget (pGBoxTrancivedData,0,0,Qt::AlignTop);
    pGBoxTrancivedData->setFixedSize (450,220);
    pGLayoutTranciveData = new QGridLayout (pGBoxTrancivedData);
    pGBoxTrancivedData->setLayout (pGLayoutTranciveData);
    pTeditTranciveData = new QTextEdit (pGBoxTrancivedData);
    pTeditTranciveData->setFixedSize (430,170);
    pGLayoutTranciveData->addWidget (pTeditTranciveData,0,0,Qt::AlignCenter);

    //====================recive data ==========
    pGBoxReciveData = new QGroupBox ("Recive data:",this);
    pGLayoutTcpServer->addWidget (pGBoxReciveData,1,0,Qt::AlignTop);
    pGBoxReciveData->setFixedSize (450,220);
    pGLayoutReciveData = new QGridLayout (pGBoxReciveData);
    pGBoxReciveData->setLayout (pGLayoutReciveData);
    pTEditReciveData = new QTextEdit (pGBoxReciveData);
    pTEditReciveData->setFixedSize (430,170);
    pGLayoutReciveData->addWidget (pTEditReciveData,0,0,Qt::AlignCenter);


    //====================send Data ========
    pGBoxSendData = new QGroupBox ("Send data:",this);
    pGBoxSendData->setFixedSize (450,100);
    pGLayoutTcpServer->addWidget (pGBoxSendData,2,0,Qt::AlignTop);
    pGLayoutSendData = new QGridLayout (pGBoxSendData);
    pGBoxSendData->setLayout (pGLayoutSendData);
    pLEditMesageSend = new QLineEdit (pGBoxSendData);
    pLEditMesageSend->setFixedSize (350,30);
    pGLayoutSendData->addWidget (pLEditMesageSend,0,0,Qt::AlignCenter);
    pButtonSend = new QPushButton ("Send",pGBoxSendData);
    connect (pButtonSend, &QPushButton::clicked, this, &TcpServer::slot_sendClient);
    pButtonSend->setFixedSize (60,30);
    pGLayoutSendData->addWidget (pButtonSend,0,2,Qt::AlignCenter);

    TcpServer::buttonDiactivated();

}

void TcpServer::writeHistoryTx(QString inHistory)
{
    historyTx.append (QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+inHistory+"\n");
    qDebug()<<QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+inHistory;
    pTeditTranciveData->setText (historyTx);
}

void TcpServer::writeHistoryRx(QString inHistory)
{
    historyRx.append (QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+inHistory+"\n");
    pTEditReciveData->setText (historyRx);
    qDebug()<<QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+inHistory;

}

void TcpServer::writeHistoryConnectClientServer(QString inHistory)
{
    historyConnectClient.append (QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+inHistory+"\n");
    pTEditClientConnectionStatuse->setText (historyConnectClient);
    qDebug()<<QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+" connect ip:"+inHistory;

}

void TcpServer::butonActivated()
{
    pButtonSend->setEnabled (true);
}

void TcpServer::buttonDiactivated()
{
    pButtonSend->setEnabled (false);
}


void TcpServer::slot_bindPort()
{
    QString strPort = pLEditPort->text ();
    bool correctPort = pChecked->checkingPortHost (strPort);
    if (!stateButtonConnect&&correctPort){
        //ne nazata
        pLEditPort->setReadOnly (true);
        stateButtonConnect=true;
        pButtonConnect->setText ("Disconnect");
        TcpServer::slot_connectPort();
        TcpServer::butonActivated();
    }
    else{
        //nazata
        pLEditPort->setReadOnly (false);
        stateButtonConnect=false;
        pButtonConnect->setText ("Connect");
        TcpServer::slot_disconectPort();
        TcpServer::buttonDiactivated();
    }

}

void TcpServer::slot_disconectPort()
{
    if(server_status==1){
        foreach(int i,listClientsConnection.keys()){
            QTextStream os(listClientsConnection[i]);
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";
            listClientsConnection[i]->close();
            listClientsConnection.remove(i);
        }
        pServerSocket->close();
        //this->textinfo->append(QString::fromUtf8("Сервер остановлен!"));
        qDebug() << QString::fromUtf8("Сервер остановлен!");
        server_status=0;
    }

}

void TcpServer::slot_connectPort()
{
    int port = pLEditPort->text ().toInt ();
    pServerSocket = new QTcpServer(this);
    connect (pServerSocket, &QTcpServer::newConnection, this, &TcpServer::slot_newConnection);
    if (!pServerSocket->listen(QHostAddress::Any, port) && server_status==0) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(pServerSocket->errorString());
       // this->textinfo->append(pServerSocket->errorString());
    } else {
        server_status=1;
        qDebug() << pServerSocket->isListening() << "TCPSocket listen on port";
       // this->textinfo->append(QString::fromUtf8("Сервер запущен!"));
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }

}

void TcpServer::slot_newConnection()
{
    if(server_status==1){
        qDebug() << QString::fromUtf8("У нас новое соединение!");
        //this->textinfo->append(QString::fromUtf8("У нас новое соединение!"));
         clientSocket=pServerSocket->nextPendingConnection();
        int idusersocs=clientSocket->socketDescriptor();
        listClientsConnection[idusersocs]=clientSocket;
//        QHostAddress temp1 =clientSocket->peerAddress ();
//        qDebug()<<temp1;
        //=====
        QStringList temp=clientSocket->peerAddress ().toString ().split(":");
        qDebug()<<"List:"<<temp;

        //====
        TcpServer::writeHistoryConnectClientServer(" connect ip:"+temp.at (3));
        connect(listClientsConnection[idusersocs],&QTcpSocket::readyRead,this, &TcpServer::slot_redyReadClient);
         connect(listClientsConnection[idusersocs],&QTcpSocket::disconnected ,this, &TcpServer::slot_disconect);
    }

}

void TcpServer::slot_disconect()
{

    QString testr=clientSocket->peerAddress ().toString ();
    qDebug()<<"@@@ clientSocket->peerAddress ().toString ()"<<testr;
    QStringList temp=testr.split(":");
//    QStringList temp=clientSocket->peerAddress ().toString ().split(":");
    qDebug()<<"List:"<<temp;
    TcpServer::writeHistoryConnectClientServer(" disconnect ip:"+temp.at (3));
}

void TcpServer::slot_redyReadClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    int idusersocs=clientSocket->socketDescriptor();
//    QTextStream os(clientSocket);
//    os.setAutoDetectUnicode(true);
//    os << "HTTP/1.0 200 Ok\r\n"
//          "Content-Type: text/html; charset=\"utf-8\"\r\n"
//          "\r\n"
//          "<h1>Nothing to see here</h1>\n"
//          << QDateTime::currentDateTime().toString() << "\n";
    TcpServer::writeHistoryRx("ReadClient"+QString::number (idusersocs)+":"+clientSocket->readAll());
    // Если нужно закрыть сокет
//    clientSocket->close();
//    SClients.remove(idusersocs);

}

void TcpServer::slot_sendClient()
{
    QByteArray mes=pLEditMesageSend->text ().toUtf8 ();
    QMap<int,QTcpSocket *>::iterator it=listClientsConnection.begin ();
    for (;it!=listClientsConnection.end ();++it){
        it.value ()->write (mes);
    }
    TcpServer::writeHistoryTx(pLEditMesageSend->text ());
}
