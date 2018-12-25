import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Window 2.12
import Smart 1.0
import QtLocation 5.6
import QtPositioning 5.6

Page {
    id: page
    title: qsTr("Traffic")

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    TrafficModel {
        id: incidents
        manager: trafficManager
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(41.157, -8.62) // Porto
        zoomLevel: 14

        property variant markers
        property variant mapItems

        function addIncident(description, lat, lng)
        {
            var incidentMarker = Qt.createQmlObject ('Marker {}', map)
            incidentMarker.lat = lat
            incidentMarker.lng = lng

            map.addMapItem(incidentMarker)

            var incidentMarkerDes = Qt.createQmlObject ('MarkerDescription {}', map)
            incidentMarkerDes.rel = incidentMarker
            incidentMarkerDes.description = description

            map.addMapItem(incidentMarkerDes)
        }

        Component.onCompleted: {
            console.debug("Inserting " + incidents.rowCount() + " new incidents")
            updateMarkers()
        }

        function updateMarkers(){
            for(var i=0; i<incidents.rowCount(); i++){

                var index = incidents.index(i,0)
                var lat = incidents.data(index, 1)
                var lng = incidents.data(index, 2)
                var des = incidents.data(index, 3)

                map.addIncident(des,lat,lng)
            }
        }
    }

    Connections {
        target: incidents
        onRowsInserted:{
            map.updateMarkers()
        }
    }

}

