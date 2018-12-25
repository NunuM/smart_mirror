import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

MapQuickItem {
    property var rel
    property string description: ""

    sourceItem: Text{
        text: description
        color:"#242424"
        font.bold: true
        styleColor: "#ECECEC"
        style: Text.Outline
    }
    coordinate: rel.coordinate
    anchorPoint: Qt.point(-rel.sourceItem.width * 0.5,rel.sourceItem.height * 1.5)
}
