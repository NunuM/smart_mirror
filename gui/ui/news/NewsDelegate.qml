import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.4

Item {
    id: item
    Pane {
        id: content
        anchors.fill: parent
        Material.elevation: 5

        Image {
            id: img
            width: content.width
            anchors.left: parent.left
            fillMode: Image.PreserveAspectFit
            source: model.image
        }

        Text {
            id: name
            width: content.width - img.width - 20
            text: model.title
            font.pointSize: 12
            font.family: "ubuntu"
            color: "black"
            Layout.fillWidth: true
            anchors.top: img.bottom
            anchors.leftMargin: 10
            wrapMode: Text.Wrap
        }

        Text {
            id: plot
            width: content.width - img.width - 20
            anchors.top: name.bottom
            anchors.leftMargin: 10
            anchors.topMargin: 10
            wrapMode: Text.Wrap
            text: model.description
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("ola" + model.index)
        }
    }
}
