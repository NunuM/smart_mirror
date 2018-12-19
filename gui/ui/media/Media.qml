import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.3
import Smart 1.0

Page {
    id: page
    title: qsTr("Media")

    GridLayout{
        anchors.fill: parent
        anchors.margins: 20
        rowSpacing: 20
        columnSpacing: 20
        flow:  width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom

        ListView {
            id: list
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10
            model: MediaModel {
                manager: mediaManager
            }
            delegate: Component {
                Item {
                    id: rawItem
                    width: parent.width
                    height: content.implicitHeight

                    Pane {
                        id: content
                        anchors.fill: parent
                        Material.elevation: 5
                        height: page.height * 0.4

                        GridLayout {
                            id: details
                            columns: 2
                            rows: 1
                            width: content.width

                            Image {
                                id: poster
                                fillMode: Image.PreserveAspectFit
                                source: model.poster.length === 0 ? "" : model.poster
                                onStatusChanged: {
                                    console.log(poster.implicitWidth)
                                }
                            }

                            GridLayout {
                                columns: 1
                                rowSpacing: 5
                                columnSpacing: 5
                                width: details.width
                                anchors.margins: 5

                                Text {
                                    id: title
                                    text: model.title
                                    font.pixelSize: 20
                                    color: "white"
                                    Layout.fillWidth: true
                                    wrapMode: Text.WordWrap
                                }

                                GridLayout {
                                    columnSpacing: 5
                                    columns: 2
                                    rows: 5

                                    Text {
                                        id: ratingLabel
                                        text: qsTr("Imdb:");
                                        font.bold: true;
                                        color: "grey"
                                    }

                                    Text {
                                        id: rating
                                        text: model.rating
                                        color: "grey"
                                        wrapMode: Text.WordWrap
                                        Layout.fillWidth: true
                                    }

                                    Text {
                                        id: actorLabel
                                        text: qsTr("Actors:");
                                        font.bold: true;
                                        color: "grey"
                                    }

                                    Text {
                                        id: actor
                                        text: model.actors
                                        color: "grey"
                                        wrapMode: Text.WordWrap
                                        Layout.fillWidth: true
                                    }

                                    Text {
                                        id: plotLabel
                                        text: qsTr("Plot:");
                                        font.bold: true;
                                        color: "grey"
                                        Layout.fillHeight: true
                                    }

                                    Text {
                                        id: plot
                                        text: model.plot
                                        color: "grey"
                                        wrapMode: Text.WordWrap
                                        Layout.fillWidth: true
                                        Layout.fillHeight: true
                                    }
                                }
                                Text {}
                                Button {
                                    text: qsTr("Play Trailer")
                                    highlighted: true
                                    Material.accent: Material.LightBlue
                                }
                            }
                        }
                    }
                }
            }
        }

        MediaDetailForm {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
