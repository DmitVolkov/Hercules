#ifndef CHECKINGCORRECTFIELDS_H
#define CHECKINGCORRECTFIELDS_H

#include <QObject>
#include <QIntValidator>
#include <QRegExpValidator>



class CheckingCorrectFields : public QObject
{
    Q_OBJECT
public:
    explicit CheckingCorrectFields(QObject *parent = nullptr);

    bool checkingPortHost(QString &strPortHost);
    bool checkinIpHost (QString &strIpHost);

signals:

private:
    QIntValidator *pIntValidator;
    QRegExpValidator *ipValidator;

};

#endif // CHECKINGCORRECTFIELDS_H
