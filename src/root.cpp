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
        mReader->setAverageResults(true);
        qDebug() << "Serial port is set up with timeout:" << mReader->timeout()
                 << "[ms]";
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
    QString body = QString::number(mReader->pmData().stdPm1)
        + " | " + QString::number(mReader->pmData().stdPm25)
        + " | " + QString::number(mReader->pmData().stdPm10);

    if (mPort.isOpen()) {
        body += br + "Port is open. Refresh the page to see updated values";
    } else {
        body += br +"Port is not open, displaying old data. New data will be "
                "read soon";
        if (mPort.open(QSerialPort::ReadOnly)) {
            mReader->restart();
        } else {
            body += br + "Failed to restart serial port reader";
        }
    }

    if (mPort.errorString().isEmpty() == false) {
        body += br + "ERROR: " + mPort.errorString();
    }

    c->response()->body() = body.toUtf8();
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

