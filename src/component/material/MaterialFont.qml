import QtQuick 2.9

FontLoader {

    source: "qrc:/font/material"

    readonly property var icons: QtObject {
        objectName: "MaterialIcons"

        property string keyboardArrowLeft:  '\uE314'
        property string menu:               '\uE5D2'
        property string textFields:         '\uE262'
        property string timeline:           '\uE922'
        property string undo:               '\uE166'
        property string redo:               '\uE15A'
        property string autorenew:          '\uE863'
        property string history:            '\uE889'
        property string tune:               '\uE429'
        property string palette:            '\uE40A'
        property string create:             '\uE150'
        property string send:               '\uE163'

    }

}
