#ifndef TELNETCLIENT_H
#define TELNETCLIENT_H

#include <QObject>
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>

class TelnetClient : public QDialog
{
    Q_OBJECT
public:
    TelnetClient();

    void initializationUI ();

signals:

};

#endif // TELNETCLIENT_H
