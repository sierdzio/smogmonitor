#include "root.h"
#include "pmcountercli/reader.h"

#include <QString>
#include <QSerialPort>
#include <QDebug>

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::index(Context *c)
{
    QString body;

    QSerialPort port("/dev/ttyUSB0");
    port.setBaudRate(QSerialPort::Baud9600);
    port.setStopBits(QSerialPort::OneStop);

    if (!port.open(QSerialPort::ReadOnly)) {
        body = "Serial port could not be opened";
        qDebug() << body;
    } else {
        Reader reader(&port);
        body = "Hello Cutelyst & Qt! " + QString::number(reader.pmData().stdPm25);
    }

    c->response()->body() = body.toUtf8();
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

