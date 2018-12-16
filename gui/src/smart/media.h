#ifndef MEDIA_H
#define MEDIA_H

#include <QObject>
#include <QJsonArray>

namespace smart {

class Media : public QObject
{
    Q_OBJECT
public:
    explicit Media(QObject *parent = nullptr);

signals:


public slots:

private:
    QJsonArray mItems;
};

}

#endif // MEDIA_H
