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
#include "smart/newsmanager.h"
#include "smart/newsmodel.h"
#include "smart/notesmanager.h"
#include "smart/notesmodel.h"
#include "smart/weathermanager.h"
#include "smart/weathermodel.h"
#include "smart/navigationmanager.h"
#include <unistd.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    smart::SoftwareCenter center("/run/snapd.socket");
    auto model = center.loadInstalledPrograms();

    smart::SensorManager sensorManager;
    smart::MediaManager mediaManager;
    smart::NewsManager newsManager;
    smart::NotesManager notesManager;
    smart::WeatherManager weatherManager;
    smart::NavigationManager navigatorManager;

    // Init default navigation routes
    navigatorManager.init();
    navigatorManager.appendView(QStringLiteral("notes"),QStringLiteral("notes/Notes.ui.qml"));
    navigatorManager.appendView(QStringLiteral("applications"),QStringLiteral("application/Application.ui.qml"));
    navigatorManager.appendView(QStringLiteral("home"),QStringLiteral("home/HomeForm.ui.qml"));
    navigatorManager.appendView(QStringLiteral("media"),QStringLiteral("media/Media.ui.qml"));
    navigatorManager.appendView(QStringLiteral("news"),QStringLiteral("news/News.ui.qml"));
    navigatorManager.appendView(QStringLiteral("notes"),QStringLiteral("notes/Notes.ui.qml"));
    navigatorManager.appendView(QStringLiteral("weather"),QStringLiteral("weather/Weather.ui.qml"));

    notesManager.appendNote(QStringLiteral("Nova"), false, QStringLiteral("2019-08-08 11:15"));

    sensorManager.appendSensor("name", "º", QVector<qreal>() << 2.2);

    weatherManager.appendWeather("2019-09-09", 0,0,0,0,0,"ola","",0,0);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<smart::RadialBar>("CustomControls", 1, 0, "RadialBar");

    qmlRegisterType<smart::SensorModel>("Smart", 1, 0, "SensorModel");
    qmlRegisterUncreatableType<smart::SensorManager>("Smart", 1, 0, "SensorManager",
                                                     QStringLiteral("SensorManager should not be created in QML"));

    qmlRegisterType<smart::MediaModel>("Smart", 1, 0, "MediaModel");
    qmlRegisterUncreatableType<smart::MediaManager>("Smart", 1, 0, "MediaManager",
                                                    QStringLiteral("MediaManager should not be created in QML"));

    qmlRegisterType<smart::NewsModel>("Smart", 1, 0, "NewsModel");
    qmlRegisterUncreatableType<smart::NewsManager>("Smart", 1, 0, "NewsManager",
                                                   QStringLiteral("MediaManager should not be created in QML"));

    qmlRegisterType<smart::NotesModel>("Smart", 1, 0, "NotesModel");
    qmlRegisterUncreatableType<smart::NotesManager>("Smart", 1, 0, "NotesManager",
                                                    QStringLiteral("NotesManager should not be created in QML"));

    qmlRegisterType<smart::WeatherModel>("Smart", 1, 0, "WeatherModel");
    qmlRegisterUncreatableType<smart::WeatherManager>("Smart", 1, 0, "WeatherManager",
                                                      QStringLiteral("NotesManager should not be created in QML"));

    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();

    ctxt->setContextProperty("programsModel", model);
    ctxt->setContextProperty("sensorManager",  &sensorManager);
    ctxt->setContextProperty("mediaManager",  &mediaManager);
    ctxt->setContextProperty("newsManager",  &newsManager);
    ctxt->setContextProperty("notesManager",  &notesManager);
    ctxt->setContextProperty("weatherManager",  &weatherManager);
    ctxt->setContextProperty("navigatorManager",  &navigatorManager);

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
