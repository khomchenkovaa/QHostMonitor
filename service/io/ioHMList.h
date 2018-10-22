#ifndef IOHMLIST_H
#define IOHMLIST_H

#include "tEnums.h"
#include "method/sdpoTestMethodConverters.h"

namespace SDPO {

class HMListService;

class IOHMList : public QObject
{
    Q_OBJECT

    HMListService *m_HML;

    QString m_fileName;
    IOTestMethodConverter *m_curMethodConverter;
public:
    explicit IOHMList(HMListService *hml, QString fileName, QObject *parent = 0);
    ~IOHMList();

signals:

public slots:

};

} // namespace SDPO

#endif // IOHMLIST_H
