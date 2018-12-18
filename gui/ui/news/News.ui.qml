import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtQuick.Layouts 1.11
import Smart 1.0

Page {
    width: Screen.width
    height: Screen.height

    title: qsTr("News")

    GridLayout{
        anchors.fill: parent
        columns: 1

        ListView {
            id: list
            width: parent.width * 0.3;
            height: parent.height
            spacing: 10
            maximumFlickVelocity: 2499
            antialiasing: true
            model:  NewsModel {
                manager: newsManager
            }
            focus: true
            delegate: NewsDelegate {
                width: parent.width
                height: 300
            }
        }
    }

}
