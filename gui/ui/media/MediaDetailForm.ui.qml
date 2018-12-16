import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.4


Item {
    width: 400
    height: 400

    Grid {
        id: grid
        x: 0
        y: 0
        width: 400
        height: 400
        rows: 4
        columns: 2
        visible: true
    }
}
