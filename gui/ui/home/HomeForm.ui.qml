import QtQuick 2.9
import QtQuick.Controls 2.2
import "../sensor"
import Smart 1.0

Page {
    property int modelSize: 1

    width: 800
    height: 600

    title: qsTr("Home" + newsManager.last.title)

    ListView {
        id: sensorViews
        width: parent.width * 0.3
        height: parent.height
        antialiasing: false

        model: SensorModel {
            manager: sensorManager
        }

        delegate: SensorDelegate {

        }
    }

}
