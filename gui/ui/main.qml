import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.20
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Applications")
                width: parent.width
                onClicked: {
                    stackView.push("application/Application.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Media")
                width: parent.width
                onClicked: {
                    stackView.push("media/Media.ui.qml")
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("News")
                width: parent.width
                onClicked: {
                    stackView.push("news/News.ui.qml")
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Notes")
                width: parent.width
                onClicked: {
                    stackView.push("notes/Notes.ui.qml")
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Weather")
                width: parent.width
                onClicked: {
                    stackView.push("weather/Weather.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "home/HomeForm.ui.qml"
        anchors.fill: parent
    }

    Connections{
        target: navigatorManager
        onChangeViewTo: {
            if(stackView.depth > 1){
                stackView.pop();
                if(view !== stackView.initialItem){
                    stackView.push(view);
                }
            } else {
                if(view !== stackView.initialItem){
                    stackView.push(view);
                }
            }
        }
    }
}
