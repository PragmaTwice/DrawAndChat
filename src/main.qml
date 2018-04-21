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
        url: "ws://localhost:2333"

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
                parent.currentIndex = 2
            }

            onEnter: {
                parent.currentIndex = 2
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
                parent.currentIndex = 0
            }
        }

    }
}
