import QtQuick 2.9
import QtQuick.Controls 2.2
import Smart 1.0

Page {
    property int modelSize: 1
    width: 800
    height: 600

    title: qsTr("Weather")

    ListView {
        width: parent.width
        height: parent.height

        model: WeatherModel{
            manager: weatherManager
        }

        delegate: Rectangle {
            width: 100
            height: 100
            Text {
                id: name
                text: model.description
            }
        }
    }
}
