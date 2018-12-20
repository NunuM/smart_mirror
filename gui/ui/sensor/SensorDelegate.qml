import QtQuick 2.4
import QtQuick.Controls 2.4
import CustomControls 1.0

Item {
    id: container
    width: parent.width
    height: 110

    RadialBar {
        width: parent.width - 10
        height: 100
        anchors.centerIn: parent
        penStyle: Qt.FlatCap
        dialType: model.index % 2 == 0 ? RadialBar.MinToMax : RadialBar.NoDial
        progressColor: "white"
        backgroundColor: "black"
        dialWidth: 10
        startAngle: 0
        spanAngle: 320
        minValue: 0
        maxValue: 100
        value: model.reading
        textFont {
            italic: false
            pointSize: 12
        }
        suffixText: model.unit
        textColor: "grey"
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.OpenHandCursor
    }

}
