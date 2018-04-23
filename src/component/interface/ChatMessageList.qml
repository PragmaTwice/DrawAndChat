import QtQuick 2.9
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ScrollView {
    id: chatView

    clip: true

    height: parent.height * 0.7
    width: chatToolbar.width

    Column {
        id: chatMessageList

        width: chatToolbar.width - 24

        spacing: 20

        onChildrenChanged: {
            chatMessageBar.position = 1
        }

    }

    ScrollBar.vertical: ScrollBar {
        id: chatMessageBar

        height: chatView.height
        anchors.right: chatView.right
    }

    function pushMessage(name, content, align){
        var component = Qt.createComponent("qrc:/component/interface/ChatMessageItem.qml")

        if (component.status === Component.Ready) {
            if(name && content) {
                component.createObject(chatMessageList, {
                    "name": name,
                    "content": content,
                    "align": align
                })
            }
        }
    }

    function pushOthersMessage(name, content){
        pushMessage(name, content, 1)
    }

    function pushMyMessage(name, content){
        pushMessage(name, content, 2)

        client.userSendMessage(content)
    }

}
