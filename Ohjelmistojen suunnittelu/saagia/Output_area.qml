import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {
    id: text_output

    color: "transparent"

        Flickable {
            id: flickable
            anchors.fill: parent
            TextArea.flickable: TextArea {
                text: saagia_view ? saagia_view.print_data : ""
                color: "#fff"
                wrapMode: TextArea.Wrap
                placeholderTextColor: "#ffffff"
                font.family: "consolas"
                font.pixelSize: 13
            }
            ScrollBar.vertical: ScrollBar {
                width: 40
            }
        }
        }
