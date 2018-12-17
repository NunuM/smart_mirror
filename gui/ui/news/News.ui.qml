import QtQuick 2.9
import QtQuick.Controls 2.2
import Smart 1.0

Page {
    width: 800
    height: 600

    title: qsTr("News")

    ListView {
        id: list

        width: 400
        height: parent.height
        spacing: 10
        maximumFlickVelocity: 2499
        antialiasing: true
        model: NewsModel{
            manager: newsManager
        }
        focus: true
        delegate: NewsDelegate {
            width: parent.width
        }
    }
}
