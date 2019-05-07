#include "root.h"
#include "pmcountercli/reader.h"

#include <QString>
#include <QSerialPort>
#include <QDebug>

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
    qDebug() << "Root constructor";
    mPort.setPortName(QStringLiteral("/dev/ttyUSB0"));
    mPort.setBaudRate(QSerialPort::Baud9600);
    mPort.setStopBits(QSerialPort::OneStop);
    if (mPort.open(QSerialPort::ReadOnly)) {
        mReader = new Reader(&mPort);
        qDebug() << "Serial port is set up";
    } else {
        qDebug() << "Serial port could not be opened!" << mPort.portName()
                 << mPort.baudRate() << mPort.stopBits() << mPort.errorString();
    }
}

Root::~Root()
{
    qDebug() << "Root destructor";
    mPort.close();
}

void Root::index(Context *c)
{
    QString body;
    if (mPort.isOpen()) {
        body = "Hello Cutelyst & Qt!\n"
            + QString::number(mReader->pmData().stdPm1)
            + " | " + QString::number(mReader->pmData().stdPm25)
            + " | " + QString::number(mReader->pmData().stdPm10);
    } else {
        body = "Serial port is not open. " + mPort.errorString();
        qDebug() << body;
    }

    c->response()->body() = body.toUtf8();
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

