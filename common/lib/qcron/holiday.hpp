#ifndef HOLIDAY_HPP
#define HOLIDAY_HPP

#include <QDate>

namespace SDPO {

class Holiday
{
public:
    static QList<QDate> yearsHolidays(int year);
    static bool isHoliday(const QDate & date);
    static QDate easter(int year);
    static QDate next(const QDate & date);
};

}
#endif // HOLIDAY_HPP
