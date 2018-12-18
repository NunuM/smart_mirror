import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Window 2.12
import Smart 1.0

Page {
    property int modelSize: 1
    width: Screen.width
    height: Screen.height

    title: qsTr("Notes")

    ListView {
        width: parent.width
        height: parent.height
        model: NotesModel {
            manager: notesManager
        }

        delegate: NotesDelegate {
            width: 300
            height: 300
        }
    }
}
