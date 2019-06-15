#include "root.h"
#include "pmcountercli/reader.h"

#include <QString>
#include <QSerialPort>
#include <QDebug>

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
    qDebug() << "Root constructor";
    mReader = new Pms7003Reader(mPortName, this);
    if (mReader->isPortOpen()) {
        mReader->setAverageResults(true);
    } else {
        delete mReader;
    }
}

Root::~Root()
{
    qDebug() << "Root destructor";    
}

void Root::index(Context *c, const QString &buttonName)
{
    bool ok = false;
    const Pms7003Reader::CommandType commandType = Pms7003Reader::CommandType(
        QMetaEnum::fromType<Pms7003Reader::CommandType>()
            .keyToValue(buttonName.toLatin1().constData(), &ok)
        );

    qDebug() << "Index called with argument:" << buttonName
             << commandType;

    const quint16 pm1 = mReader? mReader->pmData().stdPm1 : 0;
    const quint16 pm25 = mReader? mReader->pmData().stdPm25 : 0;
    const quint16 pm10 = mReader? mReader->pmData().stdPm10 : 0;

    const bool isError = (mReader->isPortOpen() == false
                          or mReader->portError() != QSerialPort::NoError);
    const QString errorString(isError?
        mReader->portErrorString() : tr("Serial port open. %1").arg(mPortName));

    c->setStash("template", "src/root.html");

    c->setStash("stdPm1", QString::number(pm1));
    c->setStash("stdPm25", QString::number(pm25));
    c->setStash("stdPm10", QString::number(pm10));

    c->setStash("status", mReader? mReader->status() : "");

    c->setStash("error", errorString);
    c->setStash("isError", QString::number(isError));

    if (mReader && ok && (int(commandType) >= 0)) {
        // TODO: invoke method asynchronously!
        mReader->executeCommand(commandType);
    }
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

