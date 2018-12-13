import QtQuick 2.4
import QtQuick.Controls 2.4

Item {
    id: container
    height: 110
    width: container.ListView.view ? container.ListView.view.width : 0
    Rectangle {
        width: parent.width - 10
        height: 100
        anchors.rightMargin: 5
        color: "orange"
        Column{
            anchors.centerIn: parent
            Text {
                id: title
                text: model.name
                x: 10;
                font.pixelSize: 12
                font.bold: true
                color: "white"
                linkColor: "white"
            }

            Text {
                id: last
                text: model.lastReading
                x: 10;
                font.pixelSize: 34
                font.bold: true
                color: "white"
                linkColor: "white"
            }
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.OpenHandCursor
        }

        Connections
        {
            target: model
            nameChanged: {
                console.log("Got signal from SerialCom in QML. passed bool value is: ");
            }
        }

    }

}
