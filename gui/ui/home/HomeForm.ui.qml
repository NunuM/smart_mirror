import QtQuick 2.9
import QtQuick.Controls 2.2
import "../sensor"
import Sensors 1.0

Page {
    property int modelSize: 1

    width: 800
    height: 600

    title: qsTr("Home")

    ListView {
        id: sensorViews
        width: parent.width * 0.3
        height: parent.height

        model: SensorModel {
            manager: sensorManager
        }

        delegate: SensorDelegate {

        }
    }

}
