#include "startup.h"
#include "mainwindow.h"
#include "ioSnmpCredentialsLoader.h"

using namespace MibBrowser;

/******************************************************************/

Startup::Startup() :
    QObject(nullptr),
    m_mainForm(*new MainWindow(nullptr))
{
    load();
}

/******************************************************************/

Startup::~Startup()
{
//    Utils::DestructorMsg(this);
    delete &m_mainForm;
}

/******************************************************************/

void Startup::show() const
{
    m_mainForm.show();
}

/******************************************************************/

void Startup::load()
{
    SDPO::IOSnmpCredentialsLoader loader;
    loader.load();
}



