import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6


MapQuickItem {
    property real lat: 0
    property real lng: 0

    id: incident
    sourceItem: Rectangle {
        width: 14;
        height: 14;
        color: "#e41e25";
        border.width: 2;
        border.color: "white";
        smooth: true;
        radius: 7
    }

    coordinate {
        latitude: lat
        longitude: lng
    }
    opacity: 1.0
    anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
}
