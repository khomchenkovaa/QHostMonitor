#include "snmpobject.h"

using namespace KharmonView;

int SnmpObject::DialogTimeout = 10;

SnmpObject::SnmpObject(QObject *parent) : QObject(parent)
{

}

QString SnmpObject::getHost() const
{
    if (host.isValid()) {
        return host.toString();
    }
    if (root && root->host.isValid()) {
        return root->host.toString();
    }
    return "localhost";
}
