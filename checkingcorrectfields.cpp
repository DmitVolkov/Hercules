#include "checkingcorrectfields.h"

CheckingCorrectFields::CheckingCorrectFields(QObject *parent)
    : QObject{parent}
{
    pIntValidator = new QIntValidator (this);
    pIntValidator->setRange (1,65535);


    /* Создаем строку для регулярного выражения */
       QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
       /* Создаем регулярное выражение с применением строки, как
        * повторяющегося элемента
        */
       QRegExp ipRegex ("^" + ipRange
                        + "\\." + ipRange
                        + "\\." + ipRange
                        + "\\." + ipRange + "$");
       /* Создаем Валидатор регулярного выражения с применением
        * созданного регулярного выражения
        */
       ipValidator = new QRegExpValidator(ipRegex, this);
       /* Устанавливаем Валидатор на QLineEdit */
       //ui->lineEdit->setValidator(ipValidator);

}

bool CheckingCorrectFields::checkingPortHost(QString &strPortHost)
{
    bool strPortHostIsEmpty = !strPortHost.isEmpty ();
    bool convertPortHost = false;
    int porthost =strPortHost.toInt (&convertPortHost);
    bool isNull=(porthost>0);
    bool max=(porthost<65536);
    int temp1231r4=strPortHostIsEmpty+convertPortHost+isNull+max;
    return (temp1231r4>3 )? true  : false;

}

bool CheckingCorrectFields::checkinIpHost(QString &strIpHost)
{
    bool strIpHostEmpty = !strIpHost.isEmpty ();
    int temp=0;
    bool currentIpHost = ipValidator->validate (strIpHost,temp);
    return (strIpHostEmpty && currentIpHost) ? true : false ;
}
