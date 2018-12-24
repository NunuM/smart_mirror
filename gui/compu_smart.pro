QT += quick dbus
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/smart/sensor.cpp \
    src/smart/softwarecenter.cpp \
    src/main.cpp \
    src/smart/radialbar.cpp \
    src/smart/sensormanager.cpp \
    src/smart/sensormodel.cpp \
    src/smart/mediamanager.cpp \
    src/smart/mediamodel.cpp \
    src/smart/newsmanager.cpp \
    src/smart/newsmodel.cpp \
    src/smart/notesmanager.cpp \
    src/smart/notesmodel.cpp \
    src/smart/weathermanager.cpp \
    src/smart/weathermodel.cpp \
    src/smart/navigationmanager.cpp \
    src/smart/weathersortproxymodel.cpp \
    src/smart/trafficmanager.cpp \
    src/smart/trafficmodel.cpp \
    src/smart/notificationmanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ui/sensor/SensorDelegate.qml \
    ui/main.qml \
    ui/media/MediaDelegate.qml \
    ui/news/News.qml \
    ui/news/NewsDelegate.qml \
    ui/notes/NotesDelegate.qml \
    ui/application/Application.qml \
    ui/home/HomeForm.qml \
    ui/media/Media.qml \
    ui/media/MediaDetailForm.qml \
    ui/weather/Weather.qml \
    ui/notes/Notes.qml \
    js/weather.js \
    ui/sensor/Sensor.qml \
    ui/sensor/SensorComponent.qml \
    js/ago.js \
    ui/traffic/Traffic.qml

HEADERS += \
    src/smart/sensor.h \
    src/smart/softwarecenter.h \
    src/smart/radialbar.h \
    src/smart/sensormanager.h \
    src/smart/sensormodel.h \
    src/smart/mediamanager.h \
    src/smart/mediamodel.h \
    src/smart/newsmanager.h \
    src/smart/newsmodel.h \
    src/smart/notesmanager.h \
    src/smart/notesmodel.h \
    src/smart/weathermanager.h \
    src/smart/weathermodel.h \
    src/smart/navigationmanager.h \
    src/smart/weathersortproxymodel.h \
    src/smart/trafficmanager.h \
    src/smart/trafficmodel.h \
    src/smart/notificationmanager.h
