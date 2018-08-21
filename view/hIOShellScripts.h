#ifndef HIOSHELLSCRIPTS_H
#define HIOSHELLSCRIPTS_H

#include <QObject>

namespace SDPO {

class ShellScript;

class IOShellScripts : public QObject
{
    Q_OBJECT
public:
    explicit IOShellScripts(QObject *parent = 0);

    QList<ShellScript*> load(const QString dirName);
    ShellScript *loadFromFile(const QString fileName);
    void saveToFile(const QString fileName, const ShellScript *script);

signals:

public slots:

};

} // namespace SDPO

#endif // HIOSHELLSCRIPTS_H
