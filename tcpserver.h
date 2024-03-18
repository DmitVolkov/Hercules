#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDateTime>
#include "checkingcorrectfields.h"

class TcpServer : public QDialog
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    void setupUIsettings ();


private:
    QGridLayout *pGLayoutTcpServer,*pGLayoutServerSettings, *pGLayoutClientConectStatuse, *pGLayoutTranciveData, *pGLayoutReciveData, *pGLayoutSendData;
    QGroupBox *pGBoxServerSettings, *pGBoxClientConnectStatuse, *pGBoxTrancivedData, *pGBoxReciveData, *pGBoxSendData;
    QPushButton *pButtonConnect, *pButtonSend;
    QLabel *pLabelPort;
    QLineEdit *pLEditPort, *pLEditMesageSend;
    QTextEdit *pTEditClientConnectionStatuse, *pTEditReciveData, *pTeditTranciveData;
    QTcpServer *pServerSocket;
    QTcpSocket* clientSocket;
    CheckingCorrectFields *pChecked;
    QMap<int,QTcpSocket *> listClientsConnection;
    int server_status;
    bool stateButtonConnect;
    QString historyTx, historyRx , historyConnectClient;

    void writeHistoryTx (QString inHistory);
    void writeHistoryRx (QString inHistory);
    void writeHistoryConnectClientServer (QString inHistory);
    void butonActivated ();
    void buttonDiactivated ();



private slots:
    void slot_bindPort ();
    void slot_disconectPort ();
    void slot_connectPort ();
    void slot_newConnection ();
    void slot_disconect ();
    void slot_redyReadClient ();
    void slot_sendClient ();
};

#endif // TCPSERVER_H
