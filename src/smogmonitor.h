#ifndef SMOGMONITOR_H
#define SMOGMONITOR_H

#include <Cutelyst/Application>

using namespace Cutelyst;

class smogmonitor : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "smogmonitor")
public:
    Q_INVOKABLE explicit smogmonitor(QObject *parent = nullptr);
    ~smogmonitor();

    bool init();
};

#endif //SMOGMONITOR_H

