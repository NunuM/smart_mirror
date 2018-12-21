import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Window 2.12
import Smart 1.0

Page {

    title: qsTr("Notes")

    GridView {
        width: parent.width * 0.9
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        cellWidth: 300;
        cellHeight : 300;

        model: NotesModel {
            manager: notesManager
        }

        delegate: NotesDelegate {

        }
    }
}
