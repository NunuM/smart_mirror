import QtQuick 2.9
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
        Column{
            Image {
                id: img
                width: content.width
                height: content.height - name.height - description.height - 20
                fillMode: Image.PreserveAspectFit
                source: model.image
            }

            Text {
                id: name
                width: content.width
                text: model.title
                font.pointSize: 12
                font.family: "ubuntu"
                color: "black"
                wrapMode: Text.Wrap
            }

            Text {
                id: description
                width: content.width
                wrapMode: Text.Wrap
                text: model.description
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("ola" + model.index)
        }
    }
}
