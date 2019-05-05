#include "smogmonitor.h"

#include "root.h"

using namespace Cutelyst;

smogmonitor::smogmonitor(QObject *parent) : Application(parent)
{
}

smogmonitor::~smogmonitor()
{
}

bool smogmonitor::init()
{
    new Root(this);

    return true;
}

