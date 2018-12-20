import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.3
import Smart 1.0

Page {

    property var model: WeatherModel {
        manager: weatherManager
    }

    title: qsTr("Weather")

    GridView {
        width: parent.width * 0.9
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        cellWidth: 300;
        cellHeight : 300;

        model: WeatherSortProxyModel {
            sourceModel: model
        }

        delegate: Item {
            width: 290
            height: 290

            Pane {
                anchors.fill: parent
                Material.elevation: 5

                Column {
                    anchors.fill: parent
                    Text {
                        id: title
                        text: {
                            var longDayName = Qt.formatDate(model.date, "ddd");
                            return longDayName.charAt(0).toUpperCase() + longDayName.slice(1) + ": " + model.temp + "ºC";
                        }
                        color: "white"
                        font.pointSize: 28
                        wrapMode: Text.WordWrap
                    }
                    Item {
                        id: details
                        width: parent.width
                        height: 290 - title.height

                        GridLayout {
                            rows: 5
                            columns: 2
                            anchors.verticalCenter: details.verticalCenter

                            Text {
                                text: qsTr("Max: ")
                                color: "grey"
                                font.bold: true
                            }

                            Text {
                                text: model.tempMax + "ºC"
                                color: "grey"
                            }

                            Text {
                                text: qsTr("Min: ")
                                color: "grey"
                                font.bold: true
                            }

                            Text {
                                text: model.tempMin + "ºC"
                                color: "grey"
                            }

                            Text {
                                text: qsTr("Wind Speed: ")
                                color: "grey"
                                font.bold: true
                            }

                            Text {
                                text: model.winSpeed
                                color: "grey"
                            }

                            Text {
                                text: qsTr("Humidity: ")
                                color: "grey"
                                font.bold: true
                            }

                            Text {
                                text: model.humidity + "%"
                                color: "grey"
                            }

                            Text {
                                text: qsTr("Pressure: ")
                                color: "grey"
                                font.bold: true
                            }

                            Text {
                                text: model.pressure + "%"
                                color: "grey"
                            }
                        }
                    }
                }
            }
        }
    }
}
