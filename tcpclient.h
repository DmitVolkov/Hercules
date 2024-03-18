#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QDateTime>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QProcess>
#include <QTextCodec>
#include "checkingcorrectfields.h"


class TcpClient : public QDialog
{
    Q_OBJECT
public:
    explicit TcpClient();
    void inicializationUI ();
    QString getDatetTimeString();
    void historyMesageWrite (QString str);

    bool stateButtonConnect;
    QString strHistoryMesage;

private:
    QLineEdit *pLEditMesage1, *pLEditMesage2, *pLEditMesage3,  *pLEditIpHost, *pLEditPortHost;
    QTextEdit *pTEditHistoryMesage;
    QPushButton *pButtonMesSend1, *pButtonMesSend2, *pButtonMesSend3, *pButtonConnect, *pButtonPingHost;
    QGroupBox *pGBoxMesSend, *pGBoxSettingsConnect, *pGBoxHistoryMes;
    QLabel *pLabelIpHost, *pLabelPortHost;
    QGridLayout *pGLatoutTcpClient,*pGLatoutSettingsConnect, *pGLatoutMessageSend;
    CheckingCorrectFields *pCheckCorrectFields;
    QTcpSocket *pTcpSocket;
    QProcess *pProcessPing;



private slots:
    void slot_activativeButtonSend ();
    void slot_diactivativeButtonSend ();
    bool slot_checkingCorrectFieldsSettingsTcp ();
    void slot_pingHost ();
    void slot_connect ();
    void slot_disconect ();
    void slot_error(QAbstractSocket::SocketError err);
    void slot_readyRead ();
    void slot_sendMessage(QString mes);
    void slot_sendMes1();
    void slot_sendMes2();
    void slot_sendMes3();
    void slot_dataOnStdOutPing();
    //void slot_dataOnStdOutErrorPing();
    //void slot_dataOnStdInputPing();

};

#endif // TCPCLIENT_H
