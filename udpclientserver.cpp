#include "udpclientserver.h"

    UdpClientServer::UdpClientServer()
{
        pCheckCorrectFields = new CheckingCorrectFields;
        UdpClientServer::inicializationUI();
        stateButtonConnect=false;
        pUdpSocket = new QUdpSocket (this);


}

    void UdpClientServer::inicializationUI()
    {
        pGLayoutFirst = new QGridLayout (this);
        this->setLayout (pGLayoutFirst);


        //=======Gr Box History message  ==========
        pGBoxMesageTxRx = new QGroupBox ("Recive and send data",this);
        pGLayoutFirst->addWidget (pGBoxMesageTxRx,0,0,Qt::AlignLeft);
        pGBoxMesageTxRx->setFixedSize (450,400);
        pVBlayoutHistoryMess = new QVBoxLayout (pGBoxMesageTxRx);
        pGBoxMesageTxRx->setLayout (pVBlayoutHistoryMess);
        pTEditHistoryMessage = new QTextEdit (pGBoxMesageTxRx);
        //pTEditHistoryMessage->setFixedSize (450,400);
        pVBlayoutHistoryMess->addWidget (pTEditHistoryMessage);


        //======= Gr Box  setting connection=====
        pGBoxSettingsConnect = new QGroupBox ("Settings connect UDP",this);
        pGLayoutFirst->addWidget (pGBoxSettingsConnect,0,2,Qt::AlignTop);
        pGBoxSettingsConnect->setFixedSize (200,130);
        pGLayoutSettingsConnect = new QGridLayout (pGBoxSettingsConnect);
        pGBoxSettingsConnect->setLayout (pGLayoutSettingsConnect);
        pButtonConnect = new QPushButton (pGBoxSettingsConnect);
        pButtonConnect->setFixedSize (100,20);
        pButtonConnect->setText ("Connect");
        pLEditPortListen = new QLineEdit (pGBoxSettingsConnect);
        pLEditPortListen->setFixedSize (60,20);
        pLEditPortSend = new QLineEdit (pGBoxSettingsConnect);
        pLEditPortSend->setFixedSize (60,20);
        pLEditIpHost = new QLineEdit (pGBoxSettingsConnect);
        pLEditIpHost->setFixedSize (100,20);
        pLEditIpHost->setInputMask ("000.000.000.000;_");
        pLabelPortListen = new QLabel("Listen Port:",pGBoxSettingsConnect);
        pLabelPortListen->setFixedSize (120,20);
        pLabelPortSend = new QLabel ("Send Port:",pGBoxSettingsConnect);
        pLabelPortSend->setFixedSize (60,20);
        pLabelIpHost = new QLabel("Ip addr host:",pGBoxSettingsConnect);
        pLabelIpHost->setFixedSize (60,20);
        pGLayoutSettingsConnect->addWidget (pLabelIpHost,0,0,Qt::AlignLeft);
        pGLayoutSettingsConnect->addWidget (pLEditIpHost,1,0,Qt::AlignLeft);
        QLabel *pLabelOtstup = new QLabel (pGBoxSettingsConnect);
        pLabelOtstup->setFixedSize (30,10);
        pGLayoutSettingsConnect->addWidget (pLabelOtstup,1,1,Qt::AlignLeft);
        pGLayoutSettingsConnect->addWidget (pLabelPortListen,0,3,Qt::AlignLeft);
        pGLayoutSettingsConnect->addWidget (pLEditPortListen,1,3,Qt::AlignLeft);
        pGLayoutSettingsConnect->addWidget (pLabelPortSend,2,3,Qt::AlignLeft);
        pGLayoutSettingsConnect->addWidget (pLEditPortSend,3,3,Qt::AlignLeft);
        pGLayoutSettingsConnect->addWidget (pButtonConnect,3,0,Qt::AlignLeft);

        connect (pButtonConnect, &QPushButton::clicked, this,[this](){
            if (stateButtonConnect){
                //кнопка коннект нажата
                UdpClientServer::slot_diactivativeButtonSend();
                pButtonConnect->setText ("Connect");
                stateButtonConnect=false;
            }
            else{
                //кнопка коннект не нажата
                UdpClientServer::slot_conectUDP();
                //stateButtonConnect=true;
            }
        });



        //===== Gr Box send message  =========

        pGBoxMesageSend = new QGroupBox ("Send data",this);
        pGLayoutFirst->addWidget (pGBoxMesageSend,2,0,Qt::AlignLeft);
        pGBoxMesageSend->setFixedSize (450,130);
        pGlAyoutMesageSend = new QGridLayout (pGBoxMesageSend);
        pGBoxMesageSend->setLayout (pGlAyoutMesageSend);
        pButtonSendMes1 = new QPushButton ("Send",pGBoxMesageSend);
        pButtonSendMes1->setFixedSize (60,30);
        connect (pButtonSendMes1,&QPushButton::clicked,this,&UdpClientServer::slot_sendMess1);
        pButtonSendMes2 = new QPushButton ("Send",pGBoxMesageSend);
        pButtonSendMes2->setFixedSize (60,30);
        connect (pButtonSendMes2,&QPushButton::clicked,this,&UdpClientServer::slot_sendMess2);
        pButtonSendMes3 = new QPushButton ("Send",pGBoxMesageSend);
        pButtonSendMes3->setFixedSize (60,30);
        connect (pButtonSendMes3,&QPushButton::clicked,this,&UdpClientServer::slot_sendMess3);
        pLEditMesSend1 = new QLineEdit (pGBoxMesageSend);
        pLEditMesSend1->setFixedSize (360,30);
        pLEditMesSend2 = new QLineEdit (pGBoxMesageSend);
        pLEditMesSend2->setFixedSize (360,30);
        pLEditMesSend3 = new QLineEdit (pGBoxMesageSend);
        pLEditMesSend3->setFixedSize (360,30);
        pGlAyoutMesageSend->addWidget (pLEditMesSend1,0,0,Qt::AlignCenter);
        pGlAyoutMesageSend->addWidget (pLEditMesSend2,2,0,Qt::AlignCenter);
        pGlAyoutMesageSend->addWidget (pLEditMesSend3,4,0,Qt::AlignCenter);
        pGlAyoutMesageSend->addWidget (pButtonSendMes1,0,2,Qt::AlignCenter);
        pGlAyoutMesageSend->addWidget (pButtonSendMes2,2,2,Qt::AlignCenter);
        pGlAyoutMesageSend->addWidget (pButtonSendMes3,4,2,Qt::AlignCenter);
        UdpClientServer::slot_diactivativeButtonSend();
    }

    QString UdpClientServer::getDatetTimeString()
    {
        return QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
    }

    void UdpClientServer::slot_activativeButtonSend()
    {
        pButtonSendMes1->setEnabled (true);
        pButtonSendMes2->setEnabled (true);
        pButtonSendMes3->setEnabled (true);


    }

    void UdpClientServer::slot_diactivativeButtonSend()
    {
        pButtonSendMes1->setEnabled (false);
        pButtonSendMes2->setEnabled (false);
        pButtonSendMes3->setEnabled (false);
    }

    bool UdpClientServer::slot_checkingCorrectFieldsSettingsConnectUDP()
    {
        QString temp1=pLEditIpHost->text ();
        QString temp2=pLEditPortListen->text();
        QString temp3=pLEditPortSend->text ();
        return (pCheckCorrectFields->checkinIpHost (temp1) && pCheckCorrectFields->checkingPortHost (temp2)
                && pCheckCorrectFields->checkingPortHost (temp3)) ? true : false ;
    }

    void UdpClientServer::setHisroryFields(QString historyMessages)
    {
        historyMessage+=historyMessages;
        pTEditHistoryMessage->setText (historyMessage);
    }

    void UdpClientServer::slot_conectUDP()
    {
        if (UdpClientServer::slot_checkingCorrectFieldsSettingsConnectUDP()){
            //поля заполнены верно можно конектиться
            UdpClientServer::slot_connectUdp();
            pButtonConnect->setText ("Disconnect");
            UdpClientServer::slot_activativeButtonSend();
            stateButtonConnect=true;
            qDebug()<<UdpClientServer::getDatetTimeString()+"| Correct fields for settings connect.\n";
            UdpClientServer::setHisroryFields(UdpClientServer::getDatetTimeString()+"| Correct fields for settings connect.\n");
        }
        else {
            //поля заполнены не верно
            pButtonConnect->setText ("Connect");
            stateButtonConnect=false;
            qDebug()<<UdpClientServer::getDatetTimeString()+"| Incorrect fields for settings connect.\n";
            UdpClientServer::setHisroryFields(UdpClientServer::getDatetTimeString()+"| Incorrect fields for settings connect.\n");
        }
    }

    void UdpClientServer::slot_sendMess1()
    {
        QByteArray mesSend = pLEditMesSend1->text ().toUtf8 ();
        QString strIPhost=pLEditIpHost->text ();
        int portSend=(pLEditPortSend->text ()).toInt ();
        int envio = pUdpSocket->writeDatagram (mesSend,QHostAddress(strIPhost),portSend);
        UdpClientServer::setHisroryFields(UdpClientServer::getDatetTimeString()+"<< "+mesSend.data()+"Send bytes: " + envio +"\n");

    }

    void UdpClientServer::slot_sendMess2()
    {
        QByteArray mesSend = pLEditMesSend2->text ().toUtf8 ();
        QString strIPhost=pLEditIpHost->text ();
        int portSend=(pLEditPortSend->text ()).toInt ();
        int envio = pUdpSocket->writeDatagram (mesSend,QHostAddress(strIPhost),portSend);
        UdpClientServer::setHisroryFields(UdpClientServer::getDatetTimeString()+"<< "+mesSend.data()+"Send bytes: " + envio +"\n");

    }

    void UdpClientServer::slot_sendMess3()
    {
        QByteArray mesSend = pLEditMesSend3->text ().toUtf8 ();
        QString strIPhost=pLEditIpHost->text ();
        int portSend=(pLEditPortSend->text ()).toInt ();
        int envio = pUdpSocket->writeDatagram (mesSend,QHostAddress(strIPhost),portSend);
        UdpClientServer::setHisroryFields(UdpClientServer::getDatetTimeString()+"<< "+mesSend.data()+"Send bytes: " + envio +"\n");

    }

    void UdpClientServer::slot_connectUdp()
    {
        QString strIPhost=pLEditIpHost->text ();
        int portListen=(pLEditPortListen->text ()).toInt ();
        int portSend=(pLEditPortSend->text ()).toInt ();
        pUdpSocket->bind(portListen);
        connect(pUdpSocket, &QUdpSocket::readyRead,
                    this, &UdpClientServer::slotReadPendingDatagrams);
        pUdpSocket->connectToHost (strIPhost,portSend);

    }

    void UdpClientServer::slotReadPendingDatagrams()
    {
        QByteArray baDatagram;
        do {
        baDatagram.resize(pUdpSocket->pendingDatagramSize());
        pUdpSocket->readDatagram(baDatagram.data(), baDatagram.size());
        } while(pUdpSocket->hasPendingDatagrams());
        QDateTime dateTime;
        QDataStream in(&baDatagram, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_3);
        in >> dateTime;
        UdpClientServer::setHisroryFields(UdpClientServer::getDatetTimeString()+">> "+baDatagram.data()+"\n");
       // pLEditReciveData->setText (historyRc+=QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+" << "+baDatagram.data()+"\n");
        //append("Received:" + dateTime.toString());
    }

