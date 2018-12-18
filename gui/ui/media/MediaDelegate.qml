import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.4


Item {
    id: media

    Pane {
        id: content
        anchors.fill: parent
        Material.elevation: 5

        Image {
            id: img
            anchors.left: parent.left
            height: parent.height
            fillMode: Image.PreserveAspectFit
            source: model.poster
        }

        Text {
            id: name
            width: content.width - img.width - 20
            text: qsTr(model.title)
            font.pointSize: 18
            font.family: "ubuntu"
            color: "black"
            Layout.fillWidth: true
            anchors.left: img.right
            anchors.leftMargin: 10
            wrapMode: Text.Wrap
        }

        Text {
            id: plot
            width: content.width - img.width - 20
            anchors.top: name.bottom
            anchors.left: img.right
            anchors.leftMargin: 10
            anchors.topMargin: 10
            wrapMode: Text.Wrap
            text: qsTr(model.plot)
        }

        Text {
            id: rating
            width: content.width - img.width - 20
            anchors.top: plot.bottom
            anchors.left: img.right
            anchors.leftMargin: 10
            anchors.topMargin: 10
            wrapMode: Text.Wrap
            text: "Rating: " + model.rating
        }

        Button {
            anchors.left: img.right
            anchors.leftMargin: 10
            anchors.bottom: img.bottom
            text: qsTr("Watch Trailer")
            highlighted: true
            Material.accent: Material.LightBlue
            onClicked: {
                console.log("");
            }
        }
    }
}

