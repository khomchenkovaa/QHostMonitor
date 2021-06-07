/*!
 * \class SDPO::TDriveSpace
 * \brief Check for low disk space
 *
 * To create a task to check for low disk space, choose "Drive Free Space" as the test type, select the drive to check, and specify the minimum free space value.
 * To check available space on a drive elsewhere on the network, use a UNC test, or mount the drive on the local PC that is running HostMonitor.
 */
#ifndef TDRIVESPACE_H
#define TDRIVESPACE_H

#include "testmethod.h"

namespace SDPO {

class TDriveSpace : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString HostAddr READ getHostAddr)
    Q_PROPERTY(QString Path READ getDrive)
    Q_PROPERTY(QString Object READ getDriveObject)

    QString m_Drive;
    int m_MinFreeSpace;
    QString m_Dimension; // KB, MB, GB, TB, %

public:
    explicit TDriveSpace(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }
    QString getDriveObject() const;

    // getters and setters
    QString getDrive() const { return m_Drive; }
    void setDrive(const QString value) { m_Drive = value; }
    int getMinFreeSpace() const { return m_MinFreeSpace; }
    void setMinFreeSpace(const int value) { m_MinFreeSpace = value; }
    QString getDimension() const { return m_Dimension; }
    void setDimension(const QString value) { m_Dimension = value; }

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;
};

} // namespace SDPO

#endif // TDRIVESPACE_H
