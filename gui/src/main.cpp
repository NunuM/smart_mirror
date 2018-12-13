#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QJsonDocument>
#include <QVariant>
#include <QProcess>
#include "smart/softwarecenter.h"
#include "smart/sensor.h"
#include <thread>
#include <unistd.h>
#include <chrono>


int main(int argc, char *argv[])
{
    smart::SoftwareCenter center("/run/snapd.socket");
    auto model = center.loadInstalledPrograms();

    auto faked = QJsonDocument::fromJson(QString("[{\"name\":\"outside\",\"value\":32.2}]").toUtf8());

    auto s1 = new smart::Sensor("sensor 1", faked.array());

    s1->lastReading();

    QList<QObject*> dataList;
    dataList.append(new smart::Sensor("sensor 1", faked.array()));
    dataList.append(new smart::Sensor("sensor 2", faked.array()));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();

    ctxt->setContextProperty("programsModel", model);
    ctxt->setContextProperty("sensorModel",  QVariant::fromValue(dataList));

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    std::thread t([s1](){
         std::this_thread::sleep_for(std::chrono::seconds(5));
        auto dd = QJsonDocument::fromJson(QString("{\"name\":\"outside\",\"value\":54}").toUtf8());
        s1->newReading(dd.object());
    });

    return app.exec();
}
