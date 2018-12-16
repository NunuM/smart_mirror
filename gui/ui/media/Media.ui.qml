import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtQuick.Layouts 1.11
import Smart 1.0

Page {
    width: Screen.width
    height: Screen.height

    title: qsTr("Media")

    ListView {
        id: list
        Layout.minimumWidth: 300
        width: 400
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
}
