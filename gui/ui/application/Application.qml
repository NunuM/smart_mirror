import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.3

Page {
    id: page

    title: qsTr("Application")

    GridLayout {
        anchors.fill: parent
        anchors.margins: 20
        rowSpacing: 20
        columnSpacing: 20
        flow:  width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom

        ListView {
            id: list
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10
            model: programsModel
            delegate: Component {
                Item {
                    width: parent.width
                    height: content.implicitHeight

                    Pane {
                        id: content
                        anchors.fill: parent
                        Material.elevation: 5
                        width: parent.width
                        height: 200
                        Text {
                            id: title
                            width: parent.width
                            color: model.index === list.currentIndex ? "grey" : "white"
                            font.pointSize: 20
                            text:  modelData.title
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    list.currentIndex = model.index
                                    console.log(list.currentIndex);
                                }
                            }
                        }
                    }
                }
            }
            focus: true
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Pane {
                id: content
                anchors.fill: parent
                Material.elevation: 5
                GridLayout {
                    anchors.fill: parent
                    columns: 2
                    rows: 2
                    anchors.margins: 20
                    rowSpacing: 5
                    columnSpacing: 5

                    Text {
                        text: qsTr("Summary:")
                        color: "Grey"
                        font.pointSize: 12
                        font.bold: true
                    }

                    Text {
                        text: {
                            return list.model[list.currentIndex].summary;
                        }
                        font.pointSize: 12
                        color: "Grey"
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                    }

                    Text {
                        id: desc
                        text: qsTr("Description:")
                        color: "Grey"
                        font.pointSize: 12
                        wrapMode: Text.NoWrap
                        Layout.fillHeight: true
                        font.bold: true
                    }
                    ScrollView {
                        id: scroll
                        clip: true
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        Text {
                            width: scroll.width
                            height: scroll.height
                            text: {
                                return list.model[list.currentIndex].description;
                            }
                            font.pointSize: 12
                            color: "Grey"
                            wrapMode: Text.WordWrap
                        }
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}
