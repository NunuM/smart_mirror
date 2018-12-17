import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtQuick.Layouts 1.11
import Smart 1.0

Page {

    width: Screen.width
    height: Screen.height

    title: qsTr("Media")

    GridLayout{
        anchors.fill: parent
        columns: 2

        ListView {
            id: list
            width: parent.width * 0.3;
            height: parent.height
            spacing: 10
            maximumFlickVelocity: 2499
            antialiasing: true
            model: MediaModel {
                manager: mediaManager
            }
            focus: true
            delegate: MediaDelegate {
                width: parent.width
                height: 300
            }
        }

        MediaDetailForm {
            width: parent.width * 0.7;
            height: parent.height
        }

    }

}
