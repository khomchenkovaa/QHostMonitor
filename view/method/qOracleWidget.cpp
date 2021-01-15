#include "qOracleWidget.h"
#include "ui_qOracleWidget.h"
#include "method/tOracle.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

namespace SDPO {

/*****************************************************************/

OracleWidget::OracleWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::OracleWidget)
{
    ui->setupUi(this);
    connect(ui->cmbDatabase, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

OracleWidget::~OracleWidget()
{
    delete ui;
}

/*****************************************************************/

void OracleWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Oracle) ) {
        reset();
        return;
    }
    TOracle* test = qobject_cast<TOracle*>(item);
    ui->cmbDatabase->setCurrentText(test->getDatabase());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->editPassword->setText(test->getPassword());

}

/*****************************************************************/

TTestMethod *OracleWidget::save(TTestMethod *item)
{
    TOracle* test;
    if (item && (item->getTMethodID() == TMethodID::Oracle)) {
        test = qobject_cast<TOracle*>(item);
    } else {
        test = new TOracle();
    }
    test->setDatabase(ui->cmbDatabase->currentText());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->editPassword->text());

    return test;
}

/*****************************************************************/

void OracleWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::Oracle);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbDatabase->clear();
    ui->cmbLogin->clear();
    ui->editPassword->clear();
}

/*****************************************************************/

QStringList OracleWidget::validate()
{
    QStringList errors;
    if(ui->cmbDatabase->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Oracle SID"));
    }
    return errors;
}

/*****************************************************************/

QString OracleWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Oracle);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::Oracle);
    case Macro::Host : return ui->cmbDatabase->currentText();
    case Macro::Object : return ui->cmbDatabase->currentText();
    default: return QString();
    }
}

/*****************************************************************/

void OracleWidget::on_btnTest_clicked()
{
    if (!QSqlDatabase::isDriverAvailable("QOCI")) {
        QMessageBox::warning(this,tr("Driver error"),
              tr("Driver QOCI is unavailable"));
        return;
    }
    QSqlDatabase db = QSqlDatabase::database("testOracle");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QOCI", "testOracle");
    }
    db.setDatabaseName(ui->cmbDatabase->currentText());
    db.setUserName(ui->cmbLogin->currentText());
    db.setPassword(ui->editPassword->text());
    bool ok = db.open();
    if (!ok) {
        QMessageBox::warning(this,tr("Connection error"),
              tr("Error code: %1\n%2").arg(db.lastError().nativeErrorCode(), db.lastError().text()));
    } else {
        QMessageBox::information(this,tr("Information"),tr("Test completed successfully"));
        db.close();
    }
}

/*****************************************************************/

} // namespace SDPO


