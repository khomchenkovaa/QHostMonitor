#include "qMibBrowser.h"
#include "ui_qMibBrowser.h"
#include <QtWidgets>
#include <QProcess>

namespace SDPO {

/******************************************************************/

MibBrowser::MibBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MibBrowser)
{
    ui->setupUi(this);
    m_model = modelFromFile(":/resources/mibs.txt");
    ui->treeMibs->setModel(m_model);
    ui->treeMibs->setHeaderHidden(true);
    QObject::connect(ui->treeMibs,
        SIGNAL(clicked(const QModelIndex&)),
        this, SLOT(updateFields(const QModelIndex&)));
}

/******************************************************************/

MibBrowser::~MibBrowser()
{
    delete ui;
}

/******************************************************************/

QString MibBrowser::getOid() const
{
    return ui->editOid->text();
}

/******************************************************************/

void MibBrowser::setOid(const QString oid)
{
    QString strOid = oid;
    ui->editOid->setText(oid);
    // select index
    QModelIndex idx = m_model->index(0,0); // iso.org.dod.internet(1.3.6.1)
    int index1 = strOid.indexOf("1.3.6.1");
    if (index1 != -1) {
        strOid = strOid.mid(index1 + 7);
        QStringList lstOid = strOid.split(".");
        foreach(QString oidNum, lstOid ) {
            if (oidNum.isEmpty()) continue;
            int childCount = m_model->rowCount(idx);
            if (!childCount) break;
            bool found = false;
            for (int i=0; i< childCount; i++) {
                QModelIndex tmpIdx = m_model->index(i,0,idx);
                QString name = m_model->data(tmpIdx).toString();
                if (name.contains(QString("(%1)").arg(oidNum))) {
                    idx = tmpIdx;
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }
    }
    ui->treeMibs->setCurrentIndex(idx);
    updateFields(idx);
}

/******************************************************************/

void MibBrowser::updateFields(const QModelIndex &index)
{
    if (!index.isValid()) return;
    bool has_children = index.child(0, 0).isValid();
    ui->editSyntax->clear();
    ui->editAccess->clear();
    ui->editStatus->clear();
    ui->txtDescription->clear();

    // build name, oid
    QString origname = m_model->data(index).toString();
    QString name = m_model->data(index).toString();
    name.truncate(name.indexOf("("));
    int index1 = origname.indexOf("(");
    int index2 = origname.indexOf(")");
    QString oid = origname.mid(index1 + 1, index2 - index1 - 1);
    QModelIndex mindex = index;

    while (mindex.parent().isValid()) {
        mindex = mindex.parent();
        QString current = m_model->data(mindex).toString();
        index1 = current.indexOf("(");
        index2 = current.indexOf(")");
        QString left = current;
        QString right = current;
        left.truncate(index1);
        right = right.mid(index1 + 1, index2 - index1 - 1);

        name = left + "." + name;
        oid = right + "." + oid;
    }
    name = "." + name;
    oid = "." + oid;
    if (!has_children) {
        oid += ".0";
    }
    ui->editOid->setText(oid);
    ui->editMib->setText(name);

    QString command = QString("snmptranslate -Td %1").arg(name);
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        process.close();
        ui->txtDescription->setPlainText("ERROR: Can no start " + command);
        return;
    }
    if(!process.waitForFinished()) {
        ui->txtDescription->setPlainText("ERROR: Terminated " + command);
        process.close();
        return;
    }
    if( process.exitStatus() == QProcess::NormalExit ) {
        QString description = process.readAll();
        QStringList list = description.split("\n");
        foreach(const QString& str, list ) {
            int idxSyntax = str.indexOf("SYNTAX");
            if ( idxSyntax > 0) {
                ui->editSyntax->setText(str.mid(idxSyntax + 6).trimmed());
            }
            int idxAccess = str.indexOf("MAX-ACCESS");
            if ( idxAccess > 0) {
                ui->editAccess->setText(str.mid(idxAccess + 10).trimmed());
            }
            int idxStatus = str.indexOf("STATUS");
            if ( idxStatus > 0) {
                ui->editStatus->setText(str.mid(idxStatus + 6).trimmed());
            }
        }
        QString pattern = "DESCRIPTION\\s*\"(.*)\"";
        QRegExp rx(pattern);
        if (rx.indexIn(description) != -1) {
            QRegExp sp("\\s+");
            ui->txtDescription->setPlainText(rx.cap(1).replace(sp," "));
        }
    } else {
        ui->txtDescription->setPlainText("ERROR: " + process.errorString());
    }
}

/******************************************************************/

static QVector<QStandardItem *> parents(10);
QAbstractItemModel *MibBrowser::modelFromFile(const QString &fileName)
{
    //*************************
    // load global mibs
    //*************************
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox msgBox;
        msgBox.setText("Cannot read the MIB tree.");
        msgBox.exec();
        return new QStringListModel(this);
    }

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QStandardItemModel *model = new QStandardItemModel(this);
    parents[0] = model->invisibleRootItem();

    m_topitem = 0;

    while (!file.atEnd()) {
        QString line = file.readLine();
        QString trimmedLine = line.trimmed();
        if (line.isEmpty() || trimmedLine.isEmpty()) {
            continue;
        }
        QRegExp re("^\\s+");
        int nonws = re.indexIn(line);
        int level = 0;
        if (nonws != -1) {
            if (line.startsWith("\t")) {
                level = re.cap(0).length();
            }
            else {
                level = re.cap(0).length()/4;
            }
        }

        if (level+1 >= parents.size()) {
            parents.resize(parents.size()*2);
        }
        QStandardItem *item = new QStandardItem;
        if (!m_topitem) {
            m_topitem = item;
        }
        item->setEditable(false);
        item->setText(trimmedLine);
//        int index1 = trimmedLine.indexOf("(");
//        int index2 = trimmedLine.indexOf(")");
//        //QString left = trimmedLine;
//        QString right = trimmedLine.mid(index1 + 1, index2 - index1 - 1);
//        //left.truncate(index1);
//        //right = right.mid(index1 + 1, index2 - index1 - 1);
//        item->setData(right);
        parents[level]->appendRow(item);
        parents[level+1] = item;
    }
    QApplication::restoreOverrideCursor();
    return model;
}

/******************************************************************/

} // namespace SDPO
