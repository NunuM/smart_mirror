import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.4
Item {

    Pane {
        id: content
        width: 290
        height: 290
        Material.elevation: 5
        Layout.fillWidth: true
        Layout.fillHeight: true

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20

            Component.onCompleted: {
                console.log(width);
            }

            Text {
                id: year
                color: "white"
                text: {
                    var date = new Date(model.alarm)
                    return date.getFullYear();
                }
                font.pointSize: 28
                wrapMode: Text.WrapAnywhere
                Layout.fillWidth: true
            }

            Text {
                text: "model.title"
                color: "grey"
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            CheckBox {
                checked: model.notifiable
                onClicked: model.notifiable = checked
                text: "Notify"
                Layout.fillWidth: true
            }
        }
    }
}
