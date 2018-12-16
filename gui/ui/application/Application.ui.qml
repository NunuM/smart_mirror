import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    property int modelSize: 1
    width: 800
    height: 600

    title: qsTr("Application")

    ListView {
        width: parent.width * 0.5
        height: parent.height

        model: programsModel
        delegate: Rectangle {
            height: 25
            width: parent.width * 0.5
            Text { text:  modelData.title }
        }
    }
}
