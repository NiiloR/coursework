import QtQuick
import QtQuick.Controls

Item {
    id: root

    width: 350
    height: 350

    property date visibleDate: new Date()

    property date startDate: new Date(0)
    property date endDate: new Date(0)

    property date minimumDate: new Date(1900,0,1)
    property date maximumDate: new Date(2999,11,31)

    signal clicked(date date)
    property date selectedDate: new Date()
    signal rangeChanged(date startDate, date endDate)

    Column {
        anchors.fill: parent
        spacing: 0

        //
        // Header
        //
        Rectangle {
            width: parent.width
            height: 40
            color: "#16141f"

            Row {
                anchors.fill: parent
                anchors.margins: 5

                Button {
                    text: "<"

                    onClicked: {
                        let d = new Date(root.visibleDate)
                        d.setMonth(d.getMonth() - 1)
                        root.visibleDate = d
                    }
                }

                Label {
                    width: parent.width - 80
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    text: Qt.formatDate(
                              root.visibleDate,
                              "MMMM yyyy")
                    color: "white"
                }

                Button {
                    text: ">"

                    onClicked: {
                        let d = new Date(root.visibleDate)
                        d.setMonth(d.getMonth() + 1)
                        root.visibleDate = d
                    }
                }
            }

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 2
                color: "orange"
            }
        }

        //
        // Weekdays
        //
        Row {
            width: parent.width
            height: 30

            Repeater {
                model: ["Mon","Tue","Wed","Thu","Fri","Sat","Sun"]

                Rectangle {
                    width: parent.width / 7
                    height: parent.height
                    color: "#ffffff"

                    Text {
                        anchors.centerIn: parent
                        color: "#333333"
                        text: modelData
                    }
                }
            }
        }

        //
        // Calendar Grid
        //
        MonthGrid {
            id: monthGrid

            width: parent.width
            height: parent.height - 70

            month: root.visibleDate.getMonth()
            year: root.visibleDate.getFullYear()

            delegate: Rectangle {
                required property var model
                property bool validDate:
                model.date >= root.minimumDate &&
                model.date <= root.maximumDate
                border.color: "orange"
                border.width: 1

                property bool isSelected:
                    sameDate(model.date, root.startDate) ||
                    sameDate(model.date, root.endDate)

                property bool inRange:
                    root.startDate.getTime() > 0 &&
                    root.endDate.getTime() > 0 &&
                    model.date >= root.startDate &&
                    model.date <= root.endDate

                color: isSelected
                       ? "orange"
                       : inRange
                         ? "#ffdd99"
                         : "white"

                Text {
                    anchors.centerIn: parent

                    text: model.day

                    color: isSelected
                           ? "black"
                           : model.month === monthGrid.month
                             ? "#111111"
                             : "#888888"

                    font.bold: isSelected
                }

                MouseArea {
                    anchors.fill: parent
                    enabled: validDate
                    onClicked: {
                        root.selectedDate = model.date
                        root.clicked(model.date)
                        if (root.startDate.getTime() === 0 ||
                                (root.startDate.getTime() > 0 &&
                                 root.endDate.getTime() > 0)) {

                            root.startDate = model.date
                            root.endDate = new Date(0)

                        } else {

                            if (model.date < root.startDate) {
                                root.endDate = root.startDate
                                root.startDate = model.date
                            } else {
                                root.endDate = model.date
                            }

                            root.rangeChanged(
                                        root.startDate,
                                        root.endDate)
                        }
                    }
                }
            }
        }
    }

    function sameDate(a, b) {

        if (!a || !b)
            return false

        return a.getDate() === b.getDate() &&
               a.getMonth() === b.getMonth() &&
               a.getFullYear() === b.getFullYear()
    }
}
