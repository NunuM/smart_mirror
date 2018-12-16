#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QJsonDocument>
#include <QVariant>
#include <QProcess>
#include "smart/softwarecenter.h"
#include "smart/radialbar.h"
#include "smart/sensormanager.h"
#include "smart/sensormodel.h"
#include "smart/sensor.h"
#include "smart/mediamanager.h"
#include "smart/mediamodel.h"
#include <thread>
#include <unistd.h>
#include <chrono>
#include <QDebug>


int main(int argc, char *argv[])
{

    smart::SoftwareCenter center("/run/snapd.socket");
    auto model = center.loadInstalledPrograms();

    smart::SensorManager sensorManager;
    smart::MediaManager mediaManager;

    auto g = QVector<qreal>();
    g.append(2.2);

    sensorManager.appendSensor("name", "º", g);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<smart::RadialBar>("CustomControls", 1, 0, "RadialBar");

    qmlRegisterType<smart::SensorModel>("Smart", 1, 0, "SensorModel");
    qmlRegisterUncreatableType<smart::SensorManager>("Smart", 1, 0, "SensorManager",
           QStringLiteral("SensorManager should not be created in QML"));

    qmlRegisterType<smart::MediaModel>("Smart", 1, 0, "MediaModel");
    qmlRegisterUncreatableType<smart::MediaManager>("Smart", 1, 0, "MediaManager",
           QStringLiteral("MediaManager should not be created in QML"));

    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();

    ctxt->setContextProperty("programsModel", model);
    ctxt->setContextProperty("sensorManager",  &sensorManager);
    ctxt->setContextProperty("mediaManager",  &mediaManager);

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
