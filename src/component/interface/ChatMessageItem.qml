import QtQuick 2.9
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Column {
    property string name
    property string content

    property int align: alignTypes.left

    property double maxMessageWidthRate: 0.8

    readonly property var alignTypes: QtObject {
        objectName: "AlignTypes"

        property int left: 1
        property int right: 2

    }

    spacing: 5

    width: parent.width

    Label {
        text: name

        font.pixelSize: 15

        Layout.maximumWidth: 20

        color: Material.color(Material.Grey)

        onWidthChanged: {
            if(width > parent.width) width = parent.width
        }

        wrapMode: Text.Wrap

        anchors.right: (align === alignTypes.right)? parent.right : undefined
        anchors.left: (align === alignTypes.left)? parent.left : undefined
    }

    Label {
        text: content

        font.pixelSize: 16

        onWidthChanged: {
            if(width > parent.width * maxMessageWidthRate)
                width = parent.width * maxMessageWidthRate
        }

        color: "white"

        wrapMode: Text.Wrap

        anchors.right: (align === alignTypes.right)? parent.right : undefined
        anchors.left: (align === alignTypes.left)? parent.left : undefined

        leftPadding: 10
        rightPadding: leftPadding
        topPadding: 5
        bottomPadding: topPadding

        background: Rectangle {

            color: Material.color(Material.Blue)

            radius: 6
        }
    }

}
