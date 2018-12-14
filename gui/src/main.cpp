#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QJsonDocument>
#include <QVariant>
#include <QProcess>
#include "smart/softwarecenter.h"
#include "smart/sensor.h"
#include "smart/radialbar.h"
#include "smart/sensormanager.h"
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
    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();

    qmlRegisterType<smart::RadialBar>("CustomControls", 1, 0, "RadialBar");

    ctxt->setContextProperty("programsModel", model);
    ctxt->setContextProperty("sensorModel",  QVariant::fromValue(sensorManager.sensors()));

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    std::thread t([s1](){
//        while (true) {
//            std::this_thread::sleep_for(std::chrono::seconds(5));
//            auto dd = QJsonDocument::fromJson(QString("{\"name\":\"outside\",\"value\":54}").toUtf8());
//            s1->newReading(dd.object());
//        }
//    });

    return app.exec();
}
