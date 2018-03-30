import QtQuick 2.9
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2

Pane {
    id : entrancePane

    leftPadding:    60
    rightPadding:   leftPadding
    topPadding:     30
    bottomPadding:  topPadding

    Material.elevation: 3

    signal enter(string name, string room, string password)
    signal create(string name, string room, string password)

    Column {

        anchors.centerIn: parent

        TextField {
            id: nicknameInput

            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 30

            placeholderText: qsTr("Enter your nickname")

            width: 230

            function checkInput() {
                if(text === '') {
                    Material.accent = Material.Red
                    focus = true

                    return false
                }
                else {
                    Material.accent = Material.Blue
                }

                return true
            }

            onTextChanged: checkInput()
        }

        TextField {
            id: roomnameInput

            anchors.horizontalCenter: parent.horizontalCenter

            placeholderText: qsTr("Enter the room name")

            width: 230

            function checkInput() {
                if(text === '') {
                    Material.accent = Material.Red
                    focus = true

                    return false
                }
                else {
                    Material.accent = Material.Blue
                }

                return true
            }

            onTextChanged: checkInput()
        }

        TextField {
            id: roomPasswordInput

            anchors.horizontalCenter: parent.horizontalCenter

            visible: false

            echoMode: TextInput.Password

            placeholderText: qsTr("Enter the room password")

            width: 230

            function checkInput() {
                if(text === '' && visible) {
                    Material.accent = Material.Red
                    focus = true

                    return false
                }
                else {
                    Material.accent = Material.Blue
                }

                return true
            }

            onTextChanged: checkInput()
        }

        Row{
            anchors.horizontalCenter: parent.horizontalCenter

            Switch {
                id: passwordSwitch

                text: qsTr("passward")

                checked: false

                onClicked: {
                    roomPasswordInput.visible = passwordSwitch.checked
                }
            }

            Switch {
                id: rememberSwitch

                text: qsTr("remember")

                checked: false
            }
        }

        Row {
            id: controlButtons

            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 20

            Button {
                id: enterButton

                highlighted: true

                leftPadding: 20
                rightPadding: 20

                text: qsTr("Enter")

                onClicked: {
                    if(checkInputs()) {
                        enter(nicknameInput.text,
                              roomnameInput.text,
                              passwordSwitch.checked? roomPasswordInput.text:'')
                    }
                }
            }
            Button {
                id: createButton

                leftPadding: 20
                rightPadding: 20

                text: qsTr("Create")

                onClicked: {
                    if(checkInputs()) {
                        create(nicknameInput.text,
                               roomnameInput.text,
                               passwordSwitch.checked? roomPasswordInput.text:'')
                    }
                }
            }

        }

    }

    Dialog {
        id: messageDialog

        title: "Title"
        standardButtons: Dialog.Ok

        width: 250

        Label {
            id: messageDialogLabel

            text: "Text..."

            anchors.fill: parent
            anchors.centerIn: parent

            wrapMode: Text.Wrap
        }

        function setContent(head, content)
        {
            title = head
            messageDialogLabel.text = content
        }

        function openWith(head, content)
        {
            setContent(head, content)
            open()
        }

    }

    function checkInputs()
    {
        return nicknameInput.checkInput()
                && roomnameInput.checkInput()
                && roomPasswordInput.checkInput()
    }

    function messageBox(head, content)
    {
        messageDialog.openWith(head, content)
    }

}
