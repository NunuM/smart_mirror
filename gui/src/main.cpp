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
#include <thread>
#include <unistd.h>
#include <chrono>
#include <QDebug>


int main(int argc, char *argv[])
{

    smart::SoftwareCenter center("/run/snapd.socket");
    auto model = center.loadInstalledPrograms();

    smart::SensorManager sensorManager;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<smart::RadialBar>("CustomControls", 1, 0, "RadialBar");
    qmlRegisterType<smart::SensorModel>("Sensors", 1, 0, "SensorModel");
    qmlRegisterUncreatableType<smart::SensorManager>("Sensors", 1, 0, "SensorManager",
           QStringLiteral("ToDoList should not be created in QML"));

    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();

    ctxt->setContextProperty("programsModel", model);
    ctxt->setContextProperty("sensorManager",  &sensorManager);

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
