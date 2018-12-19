import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtQuick.Layouts 1.11
import Smart 1.0

Page {
    id: page

    title: qsTr("News")

    GridView {
        id: grid
        width: parent.width * 0.8
        height: parent.height
        anchors.margins: 20
        anchors.horizontalCenter: parent.horizontalCenter
        cellWidth: Math.max(300,grid.width * 0.2);
        cellHeight : 500

        model: NewsModel{
            manager: newsManager
        }

        delegate: NewsDelegate {
            aWidth: grid.cellWidth
            aHeight: grid.cellHeight
        }
    }
}
