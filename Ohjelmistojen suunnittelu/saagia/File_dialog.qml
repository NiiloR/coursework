import QtQuick
import QtQuick.Dialogs

FileDialog {
    id: loadDialog

    nameFilters: ["CSV files (*.csv)", "Text files (*.txt)"]

    onAccepted: {
        console.log(selectedFile)
        saagia_controller.load_from_file(selectedFile)
    }
}
