import QtQuick 2.14
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    width: 1130
    height: 900

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    visible: true
    color: "transparent"
    title: qsTr("Saagia - application for weather and energy analyzing")


    menuBar: Window_bar_menu{}

    Rectangle {
        id: main_container

        width: parent.width
        height: parent.height
        opacity: 0.9
        color: "#1d1b29"

        Rectangle {
            id: container
            x: 26
            y: 100
            width: main_container.width - 50
            height: main_container.height - 150
            opacity: 0.9
            color: "#3a3749"

            Column {

                id: right_column
                anchors.right: parent.right
                leftPadding: -10
                y: 75
                spacing: 20
                width: 575
                height: parent.height - 85

                Rectangle {
                    id: right_column_background
                    y: 80
                    width: parent.width
                    height: parent.height
                    opacity: 0.9
                    color: "#1d1b29"

                    Text {

                        text: qsTr("TITLE for the chart below")
                        color: "white"
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.bottomMargin: 10
                        anchors.bottom: chart_base_test_real.top

                    }

                    Chart_base_test {
                        id: chart_base_test_real
                        width: parent.width - 20
                        height: 400
                        anchors.right: parent.right
                        anchors.left: parent.left
                        anchors.top: parent.top

                        anchors.rightMargin: 10
                        anchors.leftMargin: 10
                        anchors.topMargin: 50
                    }

                    Energy_type_button_row{
                        id: button_row
                        width: right_column.width
                        anchors.top: chart_base_test_real.bottom
                        anchors.right: parent.right
                        anchors.left: parent.left

                        anchors.margins: 10

                    }
                }


                }


            Rectangle {
                id: left_column_background
                anchors.top: show_case.bottom
                anchors.topMargin: 15
                anchors.bottomMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: container.bottom
                width: right_column.width - 100
                color: "#1d1b29"

                New_data_load_popup {
                    id: new_data_load_popup
                    x: 211
                    y: 49

                }


                Text {

                    text: qsTr("TITLE for the chart below")
                    color: "white"
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 10
                    anchors.bottom: wind_background_1.top
                    font.family: "Arial"
                    font.bold: false


                }

                Rectangle {

                    id: wind_background_1

                    width: 400
                    height: 250
                    color: "#060317"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    anchors.topMargin: 50



                    Wind_chart_base {
                        id: wind_chart_base

                        anchors.leftMargin: -2
                        anchors.rightMargin: -2
                        anchors.topMargin: -2
                        anchors.bottomMargin: -2

                    }

                }

                Text {

                    text: qsTr("TITLE for the chart below")
                    color: "white"
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 10
                    anchors.bottom: wind_background_2.top


                }

                Rectangle {

                    id: wind_background_2

                    width: 400
                    height: 250
                    color: "#060317"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.top: wind_background_1.bottom
                    anchors.topMargin: 50
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    anchors.bottomMargin: 10

                    Wind_chart_base {
                        id: wind_chart_base_2
                        anchors.leftMargin: -2
                        anchors.rightMargin: -2
                        anchors.topMargin: -2
                        anchors.bottomMargin: -2



                    }
                }

            }

            Currently_showing_box{
                id: show_case

                y: 10
                x: 10
                width: parent.width - 20

                }

            }


        }

        Rectangle {
            id: top_bar
            width: parent.width
            height: 92
            color: "transparent"


            Title_text{

                anchors.left: parent.left
                anchors.leftMargin: 25
                anchors.top: parent.top
                anchors.topMargin: 25
            }

            Text {
                id: city
                property string location: "Tampere"
                objectName: "city"
                text: qsTr("<b>Location: </b>" + location)
                font.pixelSize: 15
                color: "#ffffff"
                anchors.right: text_input_bar.right
                anchors.top: top_bar.top
                anchors.topMargin: 10

                Connections{
                    target: saagia_view
                    onLocationChanged: city.location = s

                }

            }

            Text_input_bar {
                id: text_input_bar

                anchors.right: parent.right
                anchors.rightMargin: 25

                anchors.top: city.bottom
                anchors.topMargin: 10

            }



    }

    Rectangle {

        height: 25
        width: parent.width
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        color: "#16141f"

        Output_area {
            id: output_area
            width: parent.width
            height: parent.width

        }


        Rectangle {

            height: 1
            width: parent.width
            color: "orange"
            anchors.top: parent.top

        }

    }


}




