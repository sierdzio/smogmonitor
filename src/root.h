#pragma once

#include <Cutelyst/Controller>
#include <QSerialPort>
#include <QPointer>

using namespace Cutelyst;

class Pms7003Reader;

class Root : public Controller
{
    Q_OBJECT
    C_NAMESPACE("")

public:
    explicit Root(QObject *parent = nullptr);
    ~Root();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c, const QString &buttonName);

    C_ATTR(defaultPage, :Path)
    void defaultPage(Context *c);

private:
    C_ATTR(End, :ActionClass("RenderView"))
    void End(Context *c) { Q_UNUSED(c); }

    QPointer<Pms7003Reader> mReader;
    const QString br = QStringLiteral("<br/><br/>");
    const QString mPortName = QStringLiteral("/dev/ttyUSB0");
};
