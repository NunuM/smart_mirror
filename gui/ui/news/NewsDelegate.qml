import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.4

Item {
    id: item
    property int aWidth: 0
    property int aHeight: 0

    width: aWidth
    height: aHeight

    GridLayout {
        anchors.fill: parent
        anchors.margins: 20
        rowSpacing: 20
        columnSpacing: 20

        Pane {
            id: content
            Layout.fillWidth: true
            height: details.implicitHeight
            Material.elevation: 5

            GridLayout {
                id: details
                rows: 2
                columns: 1
                width: content.width - 20

                Text {
                    id: name
                    text: model.title
                    font.pointSize: 16
                    color: "white"
                    wrapMode: Text.Wrap
                    Layout.fillWidth: true
                }

                Image {
                    id: image
                    source: model.image
                    width: details.width
                    sourceSize.width: details.width
                    fillMode: Image.PreserveAspectCrop
                }

                Text {
                    id: description
                    wrapMode: Text.Wrap
                    text: model.description
                    color: "grey"
                    Layout.fillWidth: true
                }
            }
        }
    }
}
