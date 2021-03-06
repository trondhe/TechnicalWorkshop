//import QtQuick 2.9
//import QtQuick.Window 2.2

//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Hello World")
//}

import QtQuick 2.9
import QtQuick.Controls 2.0
import tw.ImageManager 1.0

ApplicationWindow {
    id: root
    width: 300
    height: 480
    visible: true

    ImageManagerQML {
        id: manager
    }

    Text {
        id: name
        text: manager.image_data_length
        anchors.centerIn: parent

    }
}
