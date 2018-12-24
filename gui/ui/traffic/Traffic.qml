import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Window 2.12
import Smart 1.0

Page {
    id: page
    title: qsTr("Traffic")

    ListView {
        anchors.fill: parent
        model: TrafficModel {
            manager: trafficManager
        }

        delegate: Text {
            id: ds
            text: model.uid
        }
    }
}

