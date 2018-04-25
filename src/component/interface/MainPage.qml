import QtQuick 2.9
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import component.interface 1.0

Row {
    id: mainRow

    signal backToEntrance

    property string userName: "UserName"
    property string roomName: "RoomName"

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
                            textDialog.open()

                            drawBoard.paintState = DrawBoard.Text

                            itemRow.paintToolButtonsHighlighted(this)
                        }

                        Dialog {
                            id: textDialog

                            title: qsTr("input text to draw...")

                            standardButtons: Dialog.Ok

                            modal: true

                            width: 300

                            x: -100
                            y: 100

                            TextField {
                                id: textDialogField

                                anchors.fill: parent
                                anchors.centerIn: parent
                            }

                            onClosed: {
                                drawBoard.nowText = textDialogField.text
                            }
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

                        onDeletePaint: {
                            client.userRemovePaint(key)
                        }

                        onNewPaint: {
                            client.userPushPaint(state, argMap)
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

                Material.background: "black"
                highlighted: true

                width: 53
                height: width

                onClicked: {
                    if(!colorPickPopup.opened) {
                        if(Material.background != "#000000") {
                            highlighted = false
                        }
                        else {
                            highlighted = true
                        }

                        colorPickPopup.open()
                    }
                    else {
                        colorPickPopup.close()
                    }
                }

                Popup {
                    id: colorPickPopup

                    width: 150
                    height: 300

                    x: parent.width/2-width/2
                    y: -height

                    focus: true

                    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                    onClosed: {
                        if(colorPickButton.Material.background != "#ffffff") {
                            colorPickButton.highlighted = true
                        }
                        else {
                            colorPickButton.highlighted = false
                        }
                    }

                    ScrollView {

                        height: parent.height
                        anchors.fill: parent

                        clip: true

                        ScrollBar.vertical.interactive: false

                        ColorPicker {
                            onChangePaintColor: {
                                drawBoard.paintColor = nowColor
                                colorPickButton.Material.background = nowColor
                            }
                        }
                    }
                }

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
                    if(!paintSizePopup.opened) {
                        highlighted = false
                        paintSizePopup.open()
                    }
                    else {
                        paintSizePopup.close()
                    }
                }

                Popup {
                    id: paintSizePopup

                    width: 80
                    height: 300

                    x: parent.width/2-width/2
                    y: -height

                    focus: true

                    closePolicy: Popup.CloseOnEscap | Popup.CloseOnPressOutsideParent
                    onClosed: paintSizeButton.highlighted = true

                    ColumnLayout {

                        anchors.fill: parent

                        Slider {
                            orientation: Qt.Vertical

                            from: 1
                            to: 10

                            value: 1
                            stepSize: 1

                            anchors.horizontalCenter: parent.horizontalCenter

                            onValueChanged: {
                                paintSizePopupNumberLabel.text = value
                                drawBoard.paintSize = value
                            }
                        }
                        Label {
                            id: paintSizePopupNumberLabel

                            anchors.horizontalCenter: parent.horizontalCenter

                            text: "1"
                        }
                    }

                }

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
                    if(!textSizePopup.opened) {
                        highlighted = false
                        textSizePopup.open()
                    }
                    else {
                        textSizePopup.close()
                    }
                }

                Popup {
                    id: textSizePopup

                    width: 80
                    height: 300

                    x: parent.width/2-width/2
                    y: -height

                    focus: true

                    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                    onClosed: textSizeButton.highlighted = true

                    ColumnLayout {

                        anchors.fill: parent

                        Slider {
                            orientation: Qt.Vertical

                            from: 12
                            to: 36

                            value: 12
                            stepSize: 1

                            anchors.horizontalCenter: parent.horizontalCenter

                            onValueChanged: {
                                textSizePopupNumberLabel.text = value
                                drawBoard.textSize = value
                            }
                        }
                        Label {
                            id: textSizePopupNumberLabel

                            anchors.horizontalCenter: parent.horizontalCenter

                            text: "12"
                        }
                    }
                }

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

                        text: roomName

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

                    ScrollBar.vertical.interactive: false

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
                    chatView.pushMyMessage(userName, chatInput.text)

                    chatInput.text = ''

                }

            }
        }

    }

    function otherSendMessage(name, message) {
        chatView.pushOthersMessage(name, message)
    }

    function otherPushPaint(key, author, state, argument) {
        drawBoard.drawShape(key, author, state, argument)
    }

    function gotPaintKey(key) {
        drawBoard.gotKey(key)
    }

    function dropPaintKey(key) {
        drawBoard.dropKey(key)
    }

    function clearBoard() {
        drawBoard.clear()
    }

}
