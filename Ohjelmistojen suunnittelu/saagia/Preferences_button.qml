import QtQuick
import QtQuick.Controls

Button {
    id: button

    text: "<font color='#cccccc'>Preferences</font>"
    font.pixelSize: 13

    icon.source: "images/heart_outline.png"
    icon.color: "#ff6666"
    icon.width: 15
    icon.height: 15

    property string chosen_start_date: "test"
    property string testeri: ""

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: button
                text: "<font color='#ffffff'>Preferences</font>"
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: button
                text: "<font color='#ffffff'><b>Preferences</b></font>"
            }
        }
    ]

    onClicked: {
        console.log(testeri)
    }

    Connections {
        target: popup

        function onForwardParameters(txt) {
            testeri = txt
        }
    }
}
