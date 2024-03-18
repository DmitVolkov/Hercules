#ifndef UDPCLIENTSERVER_H
#define UDPCLIENTSERVER_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QUdpSocket>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QTextEdit>
#include <QSpacerItem>
#include <QDateTime>
#include "checkingcorrectfields.h"

class UdpClientServer : public QDialog
{
    Q_OBJECT
public:
    explicit UdpClientServer();
    void inicializationUI ();
    QString getDatetTimeString();

    QString historyMessage;
    bool stateButtonConnect;

public slots:
    void slot_activativeButtonSend ();
    void slot_diactivativeButtonSend ();
    bool slot_checkingCorrectFieldsSettingsConnectUDP();
    void setHisroryFields (QString historyMessages);
    void slot_conectUDP ();
    void slot_sendMess1 ();
    void slot_sendMess2 ();
    void slot_sendMess3 ();
    void slot_connectUdp ();

private:
    CheckingCorrectFields *pCheckCorrectFields;
    QGridLayout *pGLayoutFirst;
    QVBoxLayout  *pVBlayoutHistoryMess;
    QHBoxLayout *pHBLayoutAddSetConnectAddMess;
    QGroupBox *pGBoxSettingsConnect, *pGBoxMesageTxRx, *pGBoxMesageSend;
    QLabel *pLabelPortListen, *pLabelPortSend, *pLabelIpHost;
    QLineEdit *pLEditPortListen, *pLEditPortSend, *pLEditIpHost, *pLEditMesSend1, *pLEditMesSend2, *pLEditMesSend3;
    QPushButton *pButtonConnect, *pButtonSendMes1,*pButtonSendMes2,*pButtonSendMes3;
    QGridLayout *pGLayoutSettingsConnect, *pGlAyoutMesageSend;
    QTextEdit *pTEditHistoryMessage;
    QUdpSocket *pUdpSocket;

private slots:
    void slotReadPendingDatagrams();

};



#endif // UDPCLIENTSERVER_H
