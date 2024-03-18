#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpacerItem>
#include <QDateTime>
#include <QDebug>
#include <QSerialPortInfo>
#include <QWaitCondition>
#include <QSerialPort>
#include <QSpinBox>




class SerialPort : public QDialog
{
    Q_OBJECT
public:
    SerialPort();
    void initializationUI ();
    void initializationVariables ();
    void addHisoruSerial (QString inHistory);

private:
    QGridLayout *pGLcentral, *pGLsettingSerial, *pGLtransiveData, *pGLhistoryData;
    QComboBox *pCBnamePort, *pCBbaud, *pCBparity, *pCBflowControl;
    QSpinBox *pSBdataSize, *pSBmode;
    QLabel *pLnamePort, *pLbaud, *pLdataSize, *pLparity, *pLhandShake, *pLmode;
    QGroupBox *pGBsettingSerial, *pGBtranciveData, *pGBhistoryData;
    QPushButton *pQPBopen, *pPBtranciveData;
    QTextEdit *pTEhistorySerial;
    QLineEdit *pLEtranciveData;

    QSerialPort *pSerial;

    QStringList strListName, strListBaud, strListDataSize, strListParity, strListHandshake, strListMode;
    bool stateButonOpen;
    QString strHisorySerial;
    //===settings serial
    QString strPortName;  //name
    int set_baudRate; //speed
    int set_DataBits; //data
    int set_StopBits; //stop bit
    QString set_Control; //флоу контроль
                     //0-No flow control.,
                     //1-Hardware flow control (RTS/CTS).
                     //2-Software flow control (XON/XOFF).
                     //-1 -Unknown flow control. This value is obsolete. It is provided to keep old source code working. We strongly advise against using it in new code.
    QString set_Parity; //проверка четности
//    QSerialPort::NoParity          0   No parity bit it sent.       This is the most common parity setting. Error detection is handled by the communication protocol.
//    QSerialPort::EvenParity        2   even                         The number of 1 bits in each character, including the parity bit, is always even.
//    QSerialPort::OddParity         3   odd                          The number of 1 bits in each character, including the parity bit, is always odd. It ensures that at least one state transition occurs in each character.
//    QSerialPort::SpaceParity       4   Space                        Space parity. The parity bit is sent in the space signal condition. It does not provide error detection information.
//    QSerialPort::MarkParity        5   Mark                         Mark parity. The parity bit is always set to the mark signal condition (logical 1). It does not provide error detection information.
//    QSerialPort::UnknownParity    -1   Unknown        Unknown parity. This value is obsolete. It is provided to keep old source code working. We strongly advise against using it in new code.



    void set_serialPortCBname();
    void inicializingPortSerial ();

private slots:
    void slot_openComPort ();
    void slot_writeSerialPort ();
    void slot_readSerialPort ();
    void slot_writeNameport (QString namePort);
    void slot_writeBaudPort (QString baudT);
    void slot_writeStopBits (QString stpBits);
    void slot_errorSerialPort(QSerialPort::SerialPortError err);

};

#endif // SERIALPORT_H
