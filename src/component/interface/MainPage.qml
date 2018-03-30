import QtQuick 2.9
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2

import component.interface 1.0

Row {
    id: mainRow

    signal backToEntrance

    Column {
        id: drawCloumn

        Layout.fillHeight: true

        ToolBar {
            id: drawToolbar

            width: app.width * 0.666

            anchors.left: parent.left

            Flickable {

                clip: true

                width: drawToolbar.width
                height: parent.height

                contentWidth: itemRow.width
                contentHeight: parent.height

                RowLayout {
                    id: itemRow

                    anchors.top: parent.top

                    ToolButton {
                        id: backButton

                        text: materialFont.icons.keyboardArrowLeft
                        font: materialFont.name

                        onClicked: backToEntrance()
                    }

                    ToolSeparator {}

                    ToolButton {
                        id: undoButton

                        enabled: false

                        text: materialFont.icons.undo
                        font: materialFont.name

                    }

                    ToolButton {
                        id: redoButton

                        enabled: false

                        text: materialFont.icons.redo
                        font: materialFont.name
                    }

                    ToolSeparator {}

                    ToolButton {
                        id: penButton

                        text: materialFont.icons.create
                        font: materialFont.name

                        onClicked: drawBoard.paintState = (drawBoard.paintState==DrawBoard.Pen)?
                                       DrawBoard.None : DrawBoard.Pen
                    }

                    ToolButton {
                        id: lineButton

                        text: materialFont.icons.timeline
                        font: materialFont.name

                        onClicked: drawBoard.paintState = (drawBoard.paintState==DrawBoard.Lines)?
                                       DrawBoard.None : DrawBoard.Lines
                    }

                    ToolButton {
                        id: textButton

                        text: materialFont.icons.textFields
                        font: materialFont.name
                    }

                    ToolSeparator {}

                    ToolButton {
                        id: historyButton

                        text: materialFont.icons.history
                        font: materialFont.name
                    }

                    ToolButton {
                        id: controlButton

                        text: materialFont.icons.tune
                        font: materialFont.name
                    }
                }
            }
        }

        Flickable {
            id: drawScroll

            width: drawToolbar.width
            height: app.height - drawToolbar.height

            clip: true

            interactive: drawBoard.paintState == DrawBoard.None

            Pane {
                id: drawPane

                Material.elevation: 3

                transformOrigin: Item.TopLeft
                x: 10; y: 10

                DrawBoard {
                    id: drawBoard

                    height: 500
                    width: 500

                }

                height: drawBoard.height + 24
                width: drawBoard.width + 24
            }

            contentHeight: drawPane.height + 2*drawPane.y
            contentWidth: drawPane.width + 2*drawPane.x

        }

    }

    Column {
        id: chatColumn

        anchors.right: parent.right

        Layout.fillHeight: true

        ToolBar {
            id: chatToolbar

            width: app.width * 0.333

            Material.background: Material.Blue

            Flickable {

                clip: true

                width: chatToolbar.width
                height: parent.height

                contentWidth: itemRow.width
                contentHeight: parent.height

                RowLayout {

                    anchors.top: parent.top

                    Label {
                        id: roomNameLabel

                        text: "room name"

                        leftPadding: chatToolbar.width * 0.3

                    }

                    ToolButton {
                        id: menuButton

                        text: materialFont.icons.menu
                        font: materialFont.name
                    }

                }
            }
        }

        Pane {
            id: chatPane

            height: app.height - chatToolbar.height
            width: chatToolbar.width

            Material.elevation: 3

            Column {

                anchors.fill: parent

                ChatMessageList {
                    id: chatView

                }

                ScrollView {
                    id: chatInputView

                    clip: true

                    height: parent.height * 0.3
                    width: chatToolbar.width - 12

                    TextArea {
                        id: chatInput

                        width: parent.width

                        wrapMode: Text.Wrap

                        selectByMouse: true

                        placeholderText: qsTr("What you want to say...")


                    }

                }

            }

            RoundButton {
                id: sendButton

                anchors.bottom: parent.bottom
                anchors.right: parent.right

                anchors.bottomMargin: 10

                text: materialFont.icons.send

                font: materialFont.name

                Material.background: Material.Blue
                highlighted: true

                width: app.width * 0.035 + 25
                height: width

                onClicked: {
                    chatView.pushMyMessage("twice", chatInput.text)

                    chatInput.text = ''

                }

            }
        }

    }


}
