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

    GridLayout {
        anchors.fill: parent
        anchors.margins: 20
        rowSpacing: 20
        columnSpacing: 20
        flow:  width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom

        GridView {
            id: list
            Layout.fillWidth: true
            Layout.fillHeight: true
            cellWidth: 210
            cellHeight: 352

            model: MediaModel {
                manager: mediaManager
            }
            delegate: Item {

                id: rawItem
                width: 210
                height: 352


                Pane {
                    id: content
                    width: rawItem.width - 10
                    height: rawItem.height - 10
                    Material.elevation: 5

                    Column {
                        anchors.fill: parent
                        Layout.fillHeight: true
                        Image {
                            id: poster
                            width: parent.width
                            sourceSize.width: parent.width
                            fillMode: Image.PreserveAspectFit
                            source: model.poster.length === 0 ? "" : model.poster
                            onStatusChanged: {
                                console.log(poster.implicitWidth)
                            }
                            asynchronous:true
                        }

                        Text {
                            id: genre
                            text: model.genre
                            font.pointSize: 9
                            wrapMode: Text.WordWrap
                        }

                        Text {
                            width: parent.width
                            id: title
                            text: model.title
                            wrapMode: Text.WordWrap
                            color: "white"
                        }
                    }
                }
            }
        }
    }
}

