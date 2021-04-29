#include "startup.h"
#include "mainwindow.h"
#include "snmpobjectloader.h"
#include "snmpobjectmodel.h"

using namespace KharmonView;

/******************************************************************/

Startup::Startup() :
    QObject(nullptr),
    m_MainForm(*new MainWindow(nullptr)),
    m_ObjectLoader(*new SnmpObjectLoader(nullptr))
{
    load();
}

/******************************************************************/

Startup::~Startup()
{
//    Utils::DestructorMsg(this);
    delete &m_ObjectLoader;
    delete &m_MainForm;
}

/******************************************************************/

void Startup::show() const
{
    m_MainForm.show();
}

/******************************************************************/

void Startup::load()
{
    m_ObjectLoader.create();
    m_MainForm.setModel(new SnmpObjectModel(this));
//    SDPO::IOSnmpCredentialsLoader loader;
//    loader.load();
}



