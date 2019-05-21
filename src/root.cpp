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

void Root::index(Context *c, const QString &buttonName)
{
    bool ok = false;
    const Reader::CommandType commandType = Reader::CommandType(
        QMetaEnum::fromType<Reader::CommandType>()
            .keyToValue(buttonName.toLatin1().constData(), &ok)
        );

    qDebug() << "Index called with argument:" << buttonName
             << commandType;

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

    c->setStash("status", mReader? mReader->status() : "");

    c->setStash("error", errorString);
    c->setStash("isError", QString::number(isError));

    if (mReader && ok && commandType) {
        // TODO: invoke method asynchronously!
        mReader->executeCommand(commandType);
    }
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

