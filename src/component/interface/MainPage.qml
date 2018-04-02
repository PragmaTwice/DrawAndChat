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

                        onClicked: drawBoard.undo()

                    }

                    ToolButton {
                        id: redoButton

                        enabled: false

                        text: materialFont.icons.redo
                        font: materialFont.name

                        onClicked: drawBoard.redo()
                    }

                    ToolSeparator {}

                    ToolButton {
                        id: moveBoardButton

                        text: materialFont.icons.panTool
                        font: materialFont.name

                        highlighted: true

                        onClicked: {
                            drawBoard.paintState = DrawBoard.None
                            itemRow.paintToolButtonsHighlighted(this)
                        }
                    }

                    ToolButton {
                        id: penButton

                        text: materialFont.icons.create
                        font: materialFont.name

                        onClicked: {
                            drawBoard.paintState = DrawBoard.Pen
                            itemRow.paintToolButtonsHighlighted(this)
                        }
                    }

                    ToolButton {
                        id: lineButton

                        text: materialFont.icons.timeline
                        font: materialFont.name

                        onClicked: {
                            drawBoard.paintState = DrawBoard.Lines
                            itemRow.paintToolButtonsHighlighted(this)
                        }
                    }

                    ToolButton {
                        id: textButton

                        text: materialFont.icons.textFields
                        font: materialFont.name

                        onClicked: {
                            drawBoard.paintState = DrawBoard.Text

                            itemRow.paintToolButtonsHighlighted(this)
                        }
                    }

                    function paintToolButtonsHighlighted(obj){
                        var paintToolButtons = [moveBoardButton, penButton, lineButton, textButton]
                        for(var index in paintToolButtons) {
                            paintToolButtons[index].highlighted = false
                        }
                        obj.highlighted = true
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

        Pane {

            width: drawToolbar.width
            height: app.height - drawToolbar.height

            Flickable {
                id: drawScroll

                width: drawToolbar.width
                height: app.height - drawToolbar.height

                clip: true

                interactive: drawBoard.paintState == DrawBoard.None

                Pane {
                    id: drawPane

                    Material.elevation: 4

                    transformOrigin: Item.TopLeft
                    x: 10; y: 10

                    DrawBoard {
                        id: drawBoard

                        height: 600
                        width: 600

                        MouseArea {
                            id: drawArea

                            anchors.fill: parent

                            cursorShape: Qt.OpenHandCursor

                            enabled: false
                        }

                        onItemBackChanged: {
                            undoButton.enabled = undoable()
                            redoButton.enabled = redoable()
                        }

                        onPaintStateChanged: {
                            drawArea.cursorShape = (paintState == DrawBoard.None)?
                                        Qt.OpenHandCursor:Qt.CrossCursor
                        }

                    }

                    height: drawBoard.height + 24
                    width: drawBoard.width + 24
                }

                onMovementStarted: {
                    if(drawArea.cursorShape == Qt.OpenHandCursor) {
                        drawArea.cursorShape = Qt.ClosedHandCursor
                    }
                }

                onMovementEnded: {
                    if(drawArea.cursorShape == Qt.ClosedHandCursor) {
                        drawArea.cursorShape = Qt.OpenHandCursor
                    }
                }

                contentHeight: drawPane.height + 2*drawPane.y
                contentWidth: drawPane.width + 2*drawPane.x

            }

            RoundButton {
                id: colorPickButton

                anchors.bottom: parent.bottom
                anchors.right: parent.right

                text: materialFont.icons.palette

                font: materialFont.name

                Material.background: Material.Indigo
                highlighted: true

                width: 53
                height: width

                onClicked: {
                    highlighted = false
                    colorPickPopup.open()
                }

            }

            Popup {
                id: colorPickPopup

                width: 200
                height: 300

                x: colorPickButton.x + colorPickButton.width/2 - width/2
                y: colorPickButton.y - height

                focus: true

                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
                onClosed: colorPickButton.highlighted = true
            }

            RoundButton {
                id: paintSizeButton

                anchors.bottom: parent.bottom
                anchors.right: colorPickButton.left

                text: materialFont.icons.lineWeight

                font: materialFont.name

                Material.background: Material.Indigo
                highlighted: true

                width: colorPickButton.width
                height: width

                onClicked: {
                    highlighted = false
                    paintSizePopup.open()
                }

            }

            Popup {
                id: paintSizePopup

                width: 200
                height: 300

                x: paintSizeButton.x + paintSizeButton.width/2 - width/2
                y: paintSizeButton.y - height

                focus: true

                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
                onClosed: paintSizeButton.highlighted = true
            }

            RoundButton {
                id: textSizeButton

                anchors.bottom: parent.bottom
                anchors.right: paintSizeButton.left

                text: materialFont.icons.textFormat

                font: materialFont.name

                Material.background: Material.Indigo
                highlighted: true

                width: colorPickButton.width
                height: width

                onClicked: {
                    highlighted = false
                    textSizePopup.open()
                }

            }

            Popup {
                id: textSizePopup

                width: 200
                height: 300

                x: textSizeButton.x + textSizeButton.width/2 - width/2
                y: textSizeButton.y - height

                focus: true

                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
                onClosed: textSizeButton.highlighted = true
            }

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

                Material.background: Material.Blue
                highlighted: true

                width: app.width * 0.035 + 25
                height: width

                text: materialFont.icons.send

                font {
                    family : materialFont.name
                    pixelSize: width * 0.3
                }

                onClicked: {
                    chatView.pushMyMessage("twice", chatInput.text)

                    chatInput.text = ''

                }

            }
        }

    }


}
