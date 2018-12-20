import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Window 2.12
import Smart 1.0

Item {
    width: parent.width
    height: parent.height

    ListView {
        id: list

        width: parent.width * 0.9
        height: parent.height

        model: SensorModel {
            manager: sensorManager
        }

        delegate: SensorDelegate {

        }
    }
}
