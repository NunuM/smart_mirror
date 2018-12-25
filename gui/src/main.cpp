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
#include "smart/weathersortproxymodel.h"
#include "smart/trafficmanager.h"
#include "smart/trafficmodel.h"
#include "smart/notificationmanager.h"
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
    smart::TrafficManager trafficManager;
    smart::NotificationManager notificationManager;

    mediaManager.appendMovie(QStringLiteral("{\"type\": \"movie\", \"genre\": \"Action, Adventure, Fantasy\", \"actors\": \"Johnny Depp, Javier Bardem, Geoffrey Rush, Brenton Thwaites\", \"inserted\": \"2018-12-17 16:18:27.949416\", \"imdbid\": \"tt1790809\", \"country\": \"USA\", \"released\": \"26 May 2017\", \"title\": \"Pirates of the Caribbean Dead Men Tell No Tales\", \"quality\": \"HDRip XviD\", \"boxoffice\": \"$172,537,139\", \"plot\": \"Captain Jack Sparrow searches for the trident of Poseidon while being pursued by an undead sea captain and his crew.\", \"year\": 2017, \"imdbvotes\": \"211,949\", \"language\": \"English, Spanish\", \"metascore\": \"39\", \"writer\": \"Jeff Nathanson (screenplay by), Jeff Nathanson (story by), Terry Rossio (story by), Ted Elliott (based on characters created by), Terry Rossio (based on characters created by), Stuart Beattie (based on characters created by), Jay Wolpert (based on characters created by)\", \"dvd\": \"03 Oct 2017\", \"runtime\": \"129 min\", \"production\": \"Walt Disney Pictures\", \"imdbrating\": 6.6, \"website\": \"http://pirates.disney.com/pirates-of-the-caribbean-dead-men-tell-no-tales\", \"awards\": \"9 nominations.\", \"magnet\": \"magnet:?xt=urn:btih:CA548AA95DEADD1681C4826E61AD122A5E57B0D7&dn=Pirates.of.the.Caribbean.Dead.Men.Tell.No.Tales.2017.HDRip.XviD.\", \"poster\": \"https://m.media-amazon.com/images/M/MV5BMTYyMTcxNzc5M15BMl5BanBnXkFtZTgwOTg2ODE2MTI@._V1_SX300.jpg\", \"originaltitle\": \"Pirates.of.the.Caribbean.Dead.Men.Tell.No.Tales.2017.HDRip.XviD.\", \"rated\": \"PG-13\", \"director\": \"Joachim R\u00f8nning, Espen Sandberg\"}"));


    newsManager.appendNews(QStringLiteral("[{\"author\": \"\",\"title\": \"Antigo edíficio dos CTT vai ser o  - Sol\",\"description\": \"'Lisboa é um dos destinos mais badalados do mundo e mal podemos esperar para que a Clink esteja presente', disse Niall O’Hanlon, diretor de aquisições da Clink Hostels.\",\"url\": \"https://sol.sapo.pt/artigo/638843/antigo-edificio-dos-ctt-vai-ser-o-maior-hostel-de-portugal\",\"urlToImage\": \"https://cdn1.newsplex.pt/fotos/2018/12/17/670495.png?type=Artigo\",\"publishedAt\": \"2018-12-17T14:23:43Z\",\"content\": \"A antiga loja dos CTT - Correios de Portugal na Rua da Palma, um edíficio com cerca de 4.500 metros quadrados, vai agora tornar-se no “maior hostel de Portugal”, segundo afirmou a Worx Real Estate Consultants, empresa que representou a Clink Hostels, comprado… [+823 chars]\"}]"));

    newsManager.appendNews(QStringLiteral("[{\"author\": \"\",\"title\": \"1 milhão de vacinas contra a gripe administradas desde início da campanha - SIC Notícias\",\"description\": \"Desde o início da campanha de vacinação contra a gripe, já foram administradas mais de um milhão de vacinas. No entanto, a Direção Geral de Saúde reforça, e recomenda, a necessidade de mais portugueses serem vacinados até ao final do ano, especialmente pessoa…\",\"url\": \"https://sicnoticias.sapo.pt/pais/2018-12-19-1-milhao-de-vacinas-contra-a-gripe-administradas-desde-inicio-da-campanha\",\"urlToImage\": \"https://images.impresa.pt/sicnot/2018-12-19-gripe.BMP/fb/wm\",\"publishedAt\": \"2018-12-19T08:14:00Z\",\"content\": \"Chinelos são vistos perto de uma escola em Dapchi, na Nigéria, de onde dezenas de alunas desapareceram após um ataque do Boko Haram. Afolabi Sotunde\"}]"));

    newsManager.appendNews(QStringLiteral("[{\"author\": \"\",\"title\": \"1 milhão de vacinas contra a gripe administradas desde início da campanha - SIC Notícias\",\"description\": \"Desde o início da campanha de vacinação contra a gripe, já foram administradas mais de um milhão de vacinas. No entanto, a Direção Geral de Saúde reforça, e recomenda, a necessidade de mais portugueses serem vacinados até ao final do ano, especialmente pessoa…\",\"url\": \"https://sicnoticias.sapo.pt/pais/2018-12-19-1-milhao-de-vacinas-contra-a-gripe-administradas-desde-inicio-da-campanha\",\"urlToImage\": \"https://images.impresa.pt/sicnot/2018-12-19-gripe.BMP/fb/wm\",\"publishedAt\": \"2018-12-19T08:14:00Z\",\"content\": \"Chinelos são vistos perto de uma escola em Dapchi, na Nigéria, de onde dezenas de alunas desapareceram após um ataque do Boko Haram. Afolabi Sotunde\"}]"));

    // Init default navigation routes
    navigatorManager.init();
    navigatorManager.appendView(QStringLiteral("notes"),QStringLiteral("notes/Notes.qml"));
    navigatorManager.appendView(QStringLiteral("applications"),QStringLiteral("application/Application.qml"));
    navigatorManager.appendView(QStringLiteral("home"),QStringLiteral("home/HomeForm.qml"));
    navigatorManager.appendView(QStringLiteral("media"),QStringLiteral("media/Media.qml"));
    navigatorManager.appendView(QStringLiteral("news"),QStringLiteral("news/News.qml"));
    navigatorManager.appendView(QStringLiteral("notes"),QStringLiteral("notes/Notes.qml"));
    navigatorManager.appendView(QStringLiteral("weather"),QStringLiteral("weather/Weather.qml"));
    navigatorManager.appendView(QStringLiteral("traffic"),QStringLiteral("traffic/Traffic.qml"));

    notesManager.appendNote(QStringLiteral("Nova"), false, QStringLiteral("2019-08-08 11:15"));

    notesManager.appendNote(QStringLiteral("Nova 2"), false, QStringLiteral("2011-08-08 11:15"));

    notesManager.appendNote(QStringLiteral("Nasdva 2"), false, QStringLiteral("2015-08-08 11:15"));

    sensorManager.appendSensor("name", "º", QVector<qreal>() << 52);

    weatherManager.appendWeather("2018-12-22", 2.2,20.0,12.0,22.0,10.0,"broken clouds","09d",10,20);
    weatherManager.appendWeather("2018-12-19", 22,22.0,22.0,22.0,22.0,"broken clouds","09d",22,22);
    weatherManager.appendWeather("2018-12-23", 33,33.0,33.0,33.0,33.0,"broken clouds","09d",33,33);

    trafficManager.appendTraffic("1",41.1575628,-8.6208863,"Meu carro ardeu",false);

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

    qmlRegisterType<smart::WeatherSortProxyModel>("Smart", 1, 0, "WeatherSortProxyModel");

    qmlRegisterType<smart::TrafficModel>("Smart", 1, 0, "TrafficModel");
    qmlRegisterUncreatableType<smart::TrafficManager>("Smart", 1, 0, "TrafficManager",
                                                      QStringLiteral("TrafficManager should not be created in QML"));

    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();

    ctxt->setContextProperty("programsModel", model);
    ctxt->setContextProperty("sensorManager",  &sensorManager);
    ctxt->setContextProperty("mediaManager",  &mediaManager);
    ctxt->setContextProperty("newsManager",  &newsManager);
    ctxt->setContextProperty("notesManager",  &notesManager);
    ctxt->setContextProperty("weatherManager",  &weatherManager);
    ctxt->setContextProperty("navigatorManager",  &navigatorManager);
    ctxt->setContextProperty("trafficManager",  &trafficManager);
    ctxt->setContextProperty("notificationManager",  &notificationManager);

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
