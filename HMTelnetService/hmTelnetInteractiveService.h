#ifndef HMTELNETINTERACTIVESERVICE_H
#define HMTELNETINTERACTIVESERVICE_H

#include <QWidget>

#include "qtservice.h"
#include "hmTelnetServiceDialog.h"

namespace SDPO {

class HMTelnetInteractiveService : public QtService<QApplication>
{
    HMTelnetServiceDialog *gui;
public:
    HMTelnetInteractiveService(int argc, char **argv);
    ~HMTelnetInteractiveService();

protected:
    void start();
    void stop();
    void pause();
    void resume();
    void processCommand(int code);
};

} // namespace SDPO

#endif // HMTELNETINTERACTIVESERVICE_H
