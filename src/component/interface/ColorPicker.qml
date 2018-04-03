import QtQuick 2.9
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ColumnLayout {

    signal changePaintColor(color nowColor)

    RadioButton {
        checked: true

        text: qsTr("Black")

        property color paintColor: "black"

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Red")

        property color paintColor: Material.color(Material.Red)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Pink")

        property color paintColor: Material.color(Material.Pink)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Purple")

        property color paintColor: Material.color(Material.Purple)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("DeepPurple")

        property color paintColor: Material.color(Material.DeepPurple)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Indigo")

        property color paintColor: Material.color(Material.Indigo)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Blue")

        property color paintColor: Material.color(Material.Blue)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Cyan")

        property color paintColor: Material.color(Material.Cyan)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Teal")

        property color paintColor: Material.color(Material.Teal)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Green")

        property color paintColor: Material.color(Material.Green)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("LightGreen")

        property color paintColor: Material.color(Material.LightGreen)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Lime")

        property color paintColor: Material.color(Material.Lime)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Yellow")

        property color paintColor: Material.color(Material.Yellow)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Amber")

        property color paintColor: Material.color(Material.Amber)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Orange")

        property color paintColor: Material.color(Material.Orange)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("DeepOrange")

        property color paintColor: Material.color(Material.DeepOrange)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Brown")

        property color paintColor: Material.color(Material.Brown)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("Grey")

        property color paintColor: Material.color(Material.Grey)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("BlueGrey")

        property color paintColor: Material.color(Material.BlueGrey)

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
    RadioButton {
        text: qsTr("White")

        property color paintColor: "white"

        Material.accent: paintColor

        onClicked: changePaintColor(paintColor)
    }
}
