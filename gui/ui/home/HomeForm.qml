import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.3
import "../../js/weather.js" as Weather
import "../../js/ago.js" as Ago
import "../sensor"
Page {
    property var todayWeather: weatherManager.today
    property var weatherAnimation : new Weather.Skycons({"color": "white"})

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 3

        Rectangle {
            color: 'transparent'
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150

            ListView {
                id: notificationList
                anchors.fill: parent

                spacing: 5

                ListModel {
                    id: notificationModel
                }

                Component.onCompleted: {
                    notificationModel.append({notification:"Just Go Paid", inserted:new Date()});
                }

                model: notificationModel
                delegate: Pane {
                    width: parent.width
                    Material.elevation: 5
                    Column{
                        anchors.fill: parent
                        Text {
                            width: parent.width
                            text: model.notification
                            font.pointSize: 14
                            color: "grey"
                            wrapMode: Text.WordWrap
                        }
                        Text {
                            font.pointSize: 9
                            color: "grey"
                            text: Ago.time_ago(model.inserted)
                        }
                    }
                }
            }
        }

        Rectangle {
            color: 'transparent'
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 100

            Column {
                anchors.centerIn: parent

                Text {
                    id: currentTime
                    text: Qt.formatTime(new Date(),"H:mm:ss a")
                    color: "white"
                    font.pointSize: 20
                    function set(){
                        currentTime.text = Qt.formatTime(new Date(), "H:mm:ss a");
                    }
                }

                Text {
                    text: todayWeather.temp + "ºC";
                    color: "white"
                    font.pointSize: 44
                }

                Grid {
                    Layout.fillWidth: true
                    rows: 4
                    columns: 2
                    rowSpacing: 5

                    Text {
                        text: todayWeather.tempMin + "ºC";
                        color: "white"
                        font.bold: true
                    }

                    Text {
                        text: todayWeather.tempMax + "ºC";
                        color: "white"
                        font.bold: true
                    }


                    Text {
                        text: qsTr("Wind Speed: ")
                        color: "grey"
                        font.bold: true
                    }

                    Text {
                        text: todayWeather.windSpeed
                        color: "grey"
                    }

                    Text {
                        text: qsTr("Humidity: ")
                        color: "grey"
                        font.bold: true
                    }

                    Text {
                        text: todayWeather.humidity
                        color: "grey"
                    }

                    Text {
                        text: qsTr("Pressure: ")
                        color: "grey"
                        font.bold: true
                    }

                    Text {
                        text: todayWeather.pressure
                        color: "grey"
                    }
                }

                Canvas {
                    id: mycanvas
                    width: parent.width
                    height: 400
                    onPaint: {
                        var ctx = getContext("2d");
                        weatherAnimation.add(Weather.iconToFunction(todayWeather.icon), ctx);
                    }
                }

                Text {
                    text: todayWeather.description
                    color: "grey"
                    font.pointSize: 20
                }
            }
        }

        Rectangle {
            color: 'transparent'
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.fillHeight: true
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150

            SensorComponent {
                anchors.centerIn: parent
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    Timer {
        interval: 60
        running: true
        repeat: true
        onTriggered: {
            mycanvas.requestAnimationFrame(function(){
                weatherAnimation.play();
            });
        }
    }

    Timer {
        id: textTimer
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: currentTime.set()
    }


    Connections {
        target: mediaManager
        onNotifiy: {
            notificationModel.append({notification:name, inserted: Date.now()});
        }
    }
}
