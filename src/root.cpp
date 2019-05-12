#include "root.h"
#include "pmcountercli/reader.h"

#include <QString>
#include <QSerialPort>
#include <QDebug>

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
    qDebug() << "Root constructor";
    mPort.setPortName(mPortName);
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
    //QString body = QString::number(mReader->pmData().stdPm1)
    //    + " | " + QString::number(mReader->pmData().stdPm25)
    //    + " | " + QString::number(mReader->pmData().stdPm10);

    //if (mPort.isOpen()) {
    //    body += br + "Port is open. Refresh the page to see updated values";
    //} else {
    //    body += br +"Port is not open, displaying old data. New data will be "
    //            "read soon";
    //    if (mPort.open(QSerialPort::ReadOnly)) {
    //        mReader->restart();
    //    } else {
    //        body += br + "Failed to restart serial port reader";
    //    }
    //}

    //if (mPort.error() == QSerialPort::NoError) {
    //    body += br + "ERROR: " + mPort.errorString();
    //}

    const quint16 pm1 = mReader? mReader->pmData().stdPm1 : 0;
    const quint16 pm25 = mReader? mReader->pmData().stdPm25 : 0;
    const quint16 pm10 = mReader? mReader->pmData().stdPm10 : 0;

    const QString errorString(mPort.isOpen()? mPort.errorString()
        : tr("Serial port is not open. Is port \"%1\" correct? Is the device "
             "connected?").arg(mPortName));
    const bool isError = (mPort.isOpen() == false
                          || mPort.error() != QSerialPort::NoError);

    c->setStash("template", "src/root.html");
    c->setStash("stdPm1", QString::number(pm1));
    c->setStash("stdPm25", QString::number(pm25));
    c->setStash("stdPm10", QString::number(pm10));
    c->setStash("error", errorString);
    c->setStash("isError", QString::number(isError));
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

