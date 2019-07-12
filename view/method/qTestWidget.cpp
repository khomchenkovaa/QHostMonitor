#include "qTestWidget.h"

namespace SDPO {

/******************************************************************/

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent)
{
}

/******************************************************************/

TestWidget::~TestWidget()
{

}

/******************************************************************/

QMap<QString, QString> TestWidget::setTemplateVars(const QStringList &params) const
{
    QMap<QString, QString> result;
    foreach (const QString &key, params) {
        result.insert(key, getTemplateValue(key));
    }
    return result;
}

/******************************************************************/

} // namespace SDPO
