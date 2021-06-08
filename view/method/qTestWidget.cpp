#include "qTestWidget.h"

namespace SDPO {

/******************************************************************/

TestWidget::TestWidget(QWidget *parent)
    : QWidget(parent)
{
}

/******************************************************************/

TestWidget::~TestWidget()
{

}

/******************************************************************/

QVariantMap TestWidget::setTemplateVars(const QStringList &params) const
{
    QVariantMap result;
    foreach (const QString &key, params) {
        result.insert(key, getTemplateValue(key));
    }
    return result;
}

/******************************************************************/

} // namespace SDPO
