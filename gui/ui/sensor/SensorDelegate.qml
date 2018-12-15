import QtQuick 2.4
import QtQuick.Controls 2.4
import CustomControls 1.0

Item {
    id: container
    height: 110
    width: container.ListView.view ? container.ListView.view.width : 0

    RadialBar {
        width: parent.width - 10
        height: 100
        anchors.centerIn: parent
        penStyle: Qt.FlatCap
        dialType: model.index % 2 == 0 ? RadialBar.MinToMax : RadialBar.NoDial
        progressColor: "#e2801d"
        backgroundColor: "#34495e"
        dialWidth: 2
        startAngle: 0
        spanAngle: 320
        minValue: 0
        maxValue: 100
        value: model.reading
        textFont {
            family: "Consolas"
            italic: false
            pointSize: 12
        }
        suffixText: model.unit
        textColor: "#FFFFFF"
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.OpenHandCursor
    }

}
