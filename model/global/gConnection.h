#ifndef GCONNECTION_H
#define GCONNECTION_H

#include "tMethod.h"

#include <QString>
#include <QList>

namespace SDPO {

enum class GConnectionMethod { cmKeepActive, cmReconnect };

typedef QList<TMethodID> TMethodIdList;

struct GConnection {
    QString           resource; // Resource (UNC)
    QString           server;   // Server or Domain
    QString           login;
    QString           password;
    GConnectionMethod type;
    TMethodIdList     methods;

    GConnection() {
        clear();
    }

    void clear() {
        resource.clear();
        server.clear();
        login.clear();
        password.clear();
        type = GConnectionMethod::cmKeepActive;
        methods.clear();
    }
};

/*****************************************************************/
}


#endif // GCONNECTION_H
