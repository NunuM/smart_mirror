import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.4
Item {

    Pane{
        anchors.fill: parent
        Material.elevation: 5

        Column {

            Row{
                Text {
                    id: year
                    color: "white"
                    text: model.alarm
                    font.pointSize: 28
                }
            }

            Text {
                text: qsTr(model.title)
            }

            CheckBox {
                checked: model.notifiable
                onClicked: model.notifiable = checked
                text: "Notify"
            }
        }
    }
}
