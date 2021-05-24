#include "startup.h"
#include "mainwindow.h"
#include "snmpobjectloader.h"
#include "snmpobjectmodel.h"
#include "snmpclient.h"

#include <QFileDialog>

using namespace KharmonView;

/******************************************************************/

Startup::Startup()
    : QObject(nullptr)
    , m_MainForm    (*new MainWindow())
    , m_ObjectLoader(*new SnmpObjectLoader())
    , m_ObjectModel (*new SnmpObjectModel())
    , m_SnmpClient  (*new SnmpClient())
{
    setup();
}

/******************************************************************/

Startup::~Startup()
{
//    Utils::DestructorMsg(this);
    delete &m_SnmpClient;
    delete &m_ObjectLoader;
    delete &m_MainForm;
}

/******************************************************************/

void Startup::cfgNew()
{
    if (SnmpObject::root != nullptr) {
        SnmpObject::root->stopView();
        disconnect(SnmpObject::root, &SnmpObject::snmpUpdate, &m_SnmpClient, &SnmpClient::snmpRun);
    }
    m_ObjectModel.beginResetModel();
    m_ObjectLoader.create();
    m_ObjectModel.endResetModel();
    connect(SnmpObject::root, &SnmpObject::snmpUpdate, &m_SnmpClient, &SnmpClient::snmpRun);
    SnmpObject::root->startView();
}

/******************************************************************/

void Startup::cfgOpen()
{
    QString fileName = QFileDialog::getOpenFileName(&m_MainForm,tr("Load configuration file"),QString(),"KharmonConf(*.conf)");
    if (!fileName.isEmpty()) {
        if (SnmpObject::root != nullptr) {
            SnmpObject::root->stopView();
            disconnect(SnmpObject::root, &SnmpObject::snmpUpdate, &m_SnmpClient, &SnmpClient::snmpRun);
        }
        m_ObjectModel.beginResetModel();
        m_ObjectLoader.load(fileName);
        m_ObjectModel.endResetModel();
        connect(SnmpObject::root, &SnmpObject::snmpUpdate, &m_SnmpClient, &SnmpClient::snmpRun);
        SnmpObject::root->updateWithChilds();
        SnmpObject::root->startView();
    }
}

/******************************************************************/

void Startup::show() const
{
    m_MainForm.show();
}

/******************************************************************/

void Startup::setup()
{
    m_ObjectLoader.create();
    m_MainForm.setModel(&m_ObjectModel);

    connect(&m_MainForm, &MainWindow::cmdNew, this, &Startup::cfgNew);
    connect(&m_MainForm, &MainWindow::cmdOpen, this, &Startup::cfgOpen);

    connect(&m_MainForm, &MainWindow::cmdSave, this, [this](){
        QString fileName = m_ObjectLoader.fileName();
        if (fileName.isEmpty()) {
            fileName = QFileDialog::getSaveFileName(&m_MainForm,tr("Save As..."),QString(),"KharmonConf(*.conf)");
        }
        if (!fileName.isEmpty()) {
            m_ObjectLoader.save(fileName);
        }
    });

    connect(&m_MainForm, &MainWindow::cmdSaveAs, this, [this](){
        QString fileName = QFileDialog::getSaveFileName(&m_MainForm,tr("Save As..."),QString(),"KharmonConf(*.conf)");
        if (!fileName.isEmpty()) {
            m_ObjectLoader.save(fileName);
        }
    });

//    SDPO::IOSnmpCredentialsLoader loader;
//    loader.load();
}



