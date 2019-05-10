#include "smogmonitor.h"

#include <Cutelyst/Plugins/StaticSimple/staticsimple.h>
#include <Cutelyst/Plugins/View/Grantlee/grantleeview.h>

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
    new StaticSimple(this);
    auto view = new GrantleeView(this);
    view->setIncludePaths({ pathTo("root"), pathTo("root/static") });
    //view->setWrapper("root.html");
    return true;
}

