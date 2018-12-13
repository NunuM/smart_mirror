#ifndef SOFTWARECENTER_H
#define SOFTWARECENTER_H

#include <QVariantList>
#include <QString>

namespace smart {

class SoftwareCenter
{

public:
    SoftwareCenter(QString serverSocket);
    QVariantList loadInstalledPrograms();

signals:

public slots:

private:

    QString mServerSocket;
};

}

#endif // SOFTWARECENTER_H
