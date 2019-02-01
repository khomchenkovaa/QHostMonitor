/*!
 * \class SDPO::QCron
 * \brief a cron-like scheduler based on Qt
 *
 * Using a pattern following cron syntax, a QCron object will emit signals
 * when the system time (given by QDateTime) enters a valid time table or when it leaves such time table.
 *
 * \b Example
 *
 * From monday to friday, every minutes from 8:00 to 11:59 and from 14:00 to 17:59.
 *
 * \code
 * QCron cron("* 8-11,14-17 * * 1-5 *");
 * connect(&cron, SIGNAL(activated()),   this, SLOT(onActivation()));
 * connect(&cron, SIGNAL(deactivated()), this, SLOT(onDeactivation()));
 * \endcode
 *
 * The 'activated' signal will be emitted every weekday at 8.00 and 14.00, and the 'deactivated' signal will be emitted every weekday at 12.00 and 18.00.
 *
 * \todo
 *
 * The following is greatly inspired by python-crontab (https://pypi.python.org/pypi/python-crontab), Wikipedia (https://en.wikipedia.org/wiki/Cron#CRON_expression).
 *
 * \verbatim
   Field Name    Mandatory Allowed Values  Special Characters Extra Values
   Minutes       Yes       0-59            * / , -            < >
   Hours         Yes 	   0-23            * / , -            < >
   Day of month  Yes 	   1-31            * / , -            < >
   Month         Yes 	   1-12 or JAN-DEC * / , -            < >
   Day of week   Yes 	   0-6 or SUN-SAT  * / , -            < >
   Year          No        2015-2100       * , -
   \endverbatim
 *
 * Extra Values are < for minimum value, such as 0 for minutes or 1 for months.
 * And > for maximum value, such as 23 for hours or 12 for months.
 *
 * Supported special cases allow crontab lines to not use fields. Theseare the supported aliases which are not available in SystemV mode:
 * \verbatim
   Case            Meaning
   @reboot         Every boot
   @hourly         0 * * * *
   @daily          0 0 * * *
   @weekly         0 0 * * 0
   @monthly        0 0 1 * *
   @yearly         0 0 1 1 *
   @annually       0 0 1 1 *
   @midnight       0 0 * * *
   \endverbatim
 *
 * <b>Comma ( , )</b> Commas are used to separate items of a list.
 * For example, using "MON,WED,FRI" in the 5th field (day of week) means Mondays, Wednesdays and Fridays.
 *
 * <b>Hyphen ( - )</b> Hyphens define ranges. For example, 2000-2010 indicates every year between 2000 and 2010 AD, inclusive.
 *
 * <b>Percent ( % )</b> Percent-signs (%) in the command, unless escaped with backslash (\), are changed into newline characters,
 * and all data after the first % are sent to the command as standard input.
 *
 * <b>L 'L'</b> stands for "last".
 * When used in the day-of-week field, it allows you to specify constructs such as "the last Friday" ("5L") of a given month.
 * In the day-of-month field, it specifies the last day of the month.
 *
 * \b W The 'W' character is allowed for the day-of-month field.
 * This character is used to specify the weekday (Monday-Friday) nearest the given day.
 * As an example, if you were to specify "15W" as the value for the day-of-month field, the meaning is: "the nearest weekday to the 15th of the month."
 * So, if the 15th is a Saturday, the trigger fires on Friday the 14th.
 * If the 15th is a Sunday, the trigger fires on Monday the 16th.
 * If the 15th is a Tuesday, then it fires on Tuesday the 15th.
 * However, if you specify "1W" as the value for day-of-month, and the 1st is a Saturday, the trigger fires on Monday the 3rd, as it does not 'jump' over the boundary of a month's days.
 * The 'W' character can be specified only when the day-of-month is a single day, not a range or list of days.
 *
 * <b>Hash ( # )</b> '#' is allowed for the day-of-week field, and must be followed by a number between one and five.
 * It allows you to specify constructs such as "the second Friday" of a given month.
 *
 * <b>Question mark ( ? )</b> In some implementations, used instead of '*' for leaving either day-of-month or day-of-week blank.
 * Other cron implementations substitute "?" with the start-up time of the cron daemon, so that ? ? * * * * would be updated to 25 8 * * * *
 * if cron started-up on 8:25am, and would run at this time every day until restarted again. (WON'T BE IMPLEMENTED)
 *
 * <b>Slash ( / )</b> In vixie-cron, slashes can be combined with ranges to specify step values.
 * For example, * / 5 in the minutes field indicates every 5 minutes (see note).
 * It is shorthand for the more verbose POSIX form 5,10,15,20,25,30,35,40,45,50,55,00.
 * POSIX does not define a use for slashes; its rationale (commenting on a BSD extension) notes that the definition is based on System V format but does not exclude the possibility of extensions.
 */
#ifndef _QCRON_HPP
#define _QCRON_HPP

#include <QObject>
#include <QDateTime>
#include "qcronfield.hpp"

namespace SDPO {

class QCron : public QObject
{
    Q_OBJECT

public:
    QCron();
    QCron(const QString & pattern);
    ~QCron();

    // Accessors.
    bool isValid() const
        { return _is_valid; }

    const QString & error() const
        { return _error; }

    // Features.
    QDateTime next();
    QDateTime next(QDateTime dt);
    void catchUp(QDateTime & dt, EField field, int value);
    bool match(const QDateTime & dt) const;
    void add(QDateTime & dt, EField field, int value);

signals:
    void activated();
    void deactivated();

private:
    bool _is_valid;
    bool _is_active;
    QString _error;
    QCronField _fields[6];

    void _init();
    void _setError(const QString & error);
    void _parsePattern(const QString & pattern);
    void _parseField(QString & field_str,
                     EField field);
    QString _validCharacters(EField field);
    void _process(QDateTime & dt, EField field);

public slots:
    void checkState();
};

}

#endif
