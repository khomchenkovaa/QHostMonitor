#ifndef QTESTLISTPROPERTIES_H
#define QTESTLISTPROPERTIES_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QUuid;
QT_END_NAMESPACE

namespace Ui {
class TestListProperties;
}

namespace SDPO {

class TestListProperties : public QDialog
{
    Q_OBJECT

public:
    explicit TestListProperties(QWidget *parent = nullptr);
    ~TestListProperties();

    void setFileName(const QString fileName);
    void setGuid(const QUuid guid);
    void setFileSize(const quint64 bytes);
    void setFoldersCnt(const int foldersCnt);
    void setViewsCnt(const int viewsCnt);
    void setTestsCnt(const int testsCnt);
    void setTotalRecords(const int totalCnt);
    bool storeHistory() const;
    void setStoreHistory(const bool value);

private:
    Ui::TestListProperties *ui;
};

} // namespace SDPO

#endif // QTESTLISTPROPERTIES_H
