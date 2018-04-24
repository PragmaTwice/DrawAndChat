import QtQuick 2.9
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2

import component.material 1.0
import component.interface 1.0
import component.network 1.0

ApplicationWindow {
    id: app

    visible: true

    width: 800
    height: 500

    Material.theme: Material.Light
    Material.accent: Material.Blue

    Client {
        id: client
        url: "ws://drawandchat.imtwice.cn:2333" //"ws://localhost:2333" | "ws://drawandchat.imtwice.cn:2333"

        onUserLoginRoomResponse: {
            if(state != 0) {
                entrancePage.messageBox("Error",  "0x00" + state.toString(16) + " : " + error)
                uiStack.currentIndex = 0
                return
            }

            uiStack.currentIndex = 2
            mainPage.userName = userName
            mainPage.roomName = roomName
        }

        onUserCreateRoomResponse: {
            if(state != 0) {
                entrancePage.messageBox("Error",  "0x00" + state.toString(16) + " : " + error)
                uiStack.currentIndex = 0
                return
            }

            uiStack.currentIndex = 2
            mainPage.userName = userName
            mainPage.roomName = roomName
        }

        onUserPushPaintResponse: {
            if(state != 0) {
                entrancePage.messageBox("Error",  "0x00" + state.toString(16) + " : " + error)
                return
            }

            mainPage.gotKey(id)
        }

        onOtherPushPaint: {
            mainPage.otherPushPaint(id, inUserName, state, argList)
        }

        onOtherSendMessage: {
            mainPage.otherSendMessage(inUserName, message)
        }
    }

    MaterialFont {
        id: materialFont

    }

    StackLayout {
        anchors.centerIn: parent

        onCurrentIndexChanged: {
            uiStack.anchors.fill = (currentIndex === 2)?
                        parent : null
        }

        id: uiStack

        currentIndex: 0

        EntrancePage {
            id : entrancePage

            anchors.centerIn: parent

            onCreate: {
                if(!client.isConnected()) {
                    messageBox("Error", "Cannot connect to server")
                    return
                }

                client.userCreateRoom(name,room,password)
                parent.currentIndex = 1
            }

            onEnter: {
                if(!client.isConnected()) {
                    messageBox("Error", "Cannot connect to server")
                    return
                }

                client.userLoginRoom(name,room,password)
                parent.currentIndex = 1
            }

        }

        ProgressBar{
            id: entranceProgress

            anchors.centerIn: parent

            indeterminate: true
        }

        MainPage {
            id: mainPage

            anchors.centerIn: parent
            anchors.fill: parent

            onBackToEntrance: {
                client.userLogoutRoom()
                parent.currentIndex = 0
            }
        }

    }
}
