import QtQuick 2.9
import QtQuick.Controls 2.2
import "../sensor"

Page {
    property int modelSize: 1

    width: 800
    height: 600

    title: qsTr("Home")

    ListView {
        id: sensorViews
        width: parent.width * 0.3
        height: parent.height

        model: sensorModel
        delegate: SensorDelegate {

        }
    }

}
