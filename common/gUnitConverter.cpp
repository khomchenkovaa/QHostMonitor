#include "gUnitConverter.h"

namespace SDPO {

/*****************************************************************/

GUnitConverter::GUnitConverter(const QString& text, QObject *parent) :
    QObject(parent),
    a_Text(text)
{
    convert();
}

/*****************************************************************/

GUnitConverter::GUnitConverter(const int value, const QString ext, QObject *parent) :
    QObject(parent),
    a_Value(value),
    a_Ext(ext)
{
    toString();
    toNumber();
}

/*****************************************************************/

bool GUnitConverter::convert()
{
    QString pattern = "(\\d+)\\s*(\\w\\w|%)";
    QRegExp rx(pattern);
    int pos = 0;
    if ((pos = rx.indexIn(a_Text)) == -1) {
        a_Value = 0;
        a_Ext = QString();
        return false;
    }
    a_Value = rx.cap(1).toInt();
    QString ext = rx.cap(2);
    if (ext.compare("Kb",Qt::CaseInsensitive) == 0) {
        a_Ext = "Kb";
    } else if (ext.compare("Mb",Qt::CaseInsensitive) == 0) {
        a_Ext = "Mb";
    } else if (ext.compare("Gb",Qt::CaseInsensitive) == 0) {
        a_Ext = "Gb";
    } else if (ext.compare("Tb",Qt::CaseInsensitive) == 0) {
        a_Ext = "Tb";
    } else {
        a_Ext = ext;
    }
    toNumber();
    return true;
}

/*****************************************************************/

QString GUnitConverter::toString()
{
    a_Text = QString("%1 %2").arg(a_Value).arg(a_Ext);
    return a_Text;
}

/*****************************************************************/

double GUnitConverter::toNumber()
{
    float result = a_Value;
    if (a_Ext.compare("Kb",Qt::CaseInsensitive) == 0) {
        result *= 1024.0;
    } else if (a_Ext.compare("Mb",Qt::CaseInsensitive) == 0) {
        result *= 1024.0 * 1024.0;
    } else if (a_Ext.compare("Gb",Qt::CaseInsensitive) == 0) {
        result *= 1024.0 * 1024.0 * 1024.0;
    } else if (a_Ext.compare("Tb",Qt::CaseInsensitive) == 0) {
        result *= 1024.0 * 1024.0 * 1024.0 * 1024.0;
    } else if (a_Ext == "%") {
        result /= 100;
    } else if (a_Ext == "ms") {
        result /= 1000;
    }
    a_Number = result;
    return a_Number;
}

/*****************************************************************/

int GUnitConverter::fromNumber()
{
    float result = a_Number;
    if (a_Ext.compare("Kb",Qt::CaseInsensitive) == 0) {
        result /= 1024.0;
    } else if (a_Ext.compare("Mb",Qt::CaseInsensitive) == 0) {
        result /= (1024.0 * 1024.0);
    } else if (a_Ext.compare("Gb",Qt::CaseInsensitive) == 0) {
        result /= (1024.0 * 1024.0 * 1024.0);
    } else if (a_Ext.compare("Tb",Qt::CaseInsensitive) == 0) {
        result /= (1024.0 * 1024.0 * 1024.0 * 1024.0);
    } else if (a_Ext == "%") {
        result *= 100;
    } else if (a_Ext == "ms") {
        result *= 1000;
    }
    a_Value = result;
    toString();
    return a_Value;
}

/*****************************************************************/

} // namespace SDPO
