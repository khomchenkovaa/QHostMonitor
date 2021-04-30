#include "startup.h"
#include "mainwindow.h"
#include "snmpobjectloader.h"
#include "snmpobjectmodel.h"

#include <QFileDialog>

using namespace KharmonView;

/******************************************************************/

Startup::Startup() :
    QObject(nullptr),
    m_MainForm    (*new MainWindow(nullptr)),
    m_ObjectLoader(*new SnmpObjectLoader(nullptr)),
    m_ObjectModel (*new SnmpObjectModel(nullptr))
{
    setup();
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

void Startup::setup()
{
    m_ObjectLoader.create();
    m_MainForm.setModel(&m_ObjectModel);

    connect(&m_MainForm, &MainWindow::cmdNew, this, [this](){
        m_ObjectModel.beginResetModel();
        m_ObjectLoader.create();
        m_ObjectModel.endResetModel();
    });

    connect(&m_MainForm, &MainWindow::cmdOpen, this, [this](){
        QString fileName = QFileDialog::getOpenFileName(&m_MainForm,tr("Load configuration file"),QString(),"KharmonConf(*.conf)");
        if (!fileName.isEmpty()) {
            m_ObjectModel.beginResetModel();
            m_ObjectLoader.load(fileName);
            m_ObjectModel.endResetModel();
            SnmpObject::root->startView();
        }
    });

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



