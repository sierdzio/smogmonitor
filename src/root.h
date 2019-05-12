#ifndef ROOT_H
#define ROOT_H

#include <Cutelyst/Controller>
#include <QSerialPort>

#include "pmcountercli/reader.h"

using namespace Cutelyst;

class Root : public Controller
{
    Q_OBJECT
    C_NAMESPACE("")
public:
    explicit Root(QObject *parent = nullptr);
    ~Root();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);

    C_ATTR(defaultPage, :Path)
    void defaultPage(Context *c);

private:
    C_ATTR(End, :ActionClass("RenderView"))
    void End(Context *c) { Q_UNUSED(c); }

    QSerialPort mPort;
    Reader *mReader = nullptr;
    const QString br = QStringLiteral("<br/><br/>");
    const QString mPortName = QStringLiteral("/dev/ttyUSB0");
};

#endif //ROOT_H

