import QtCore
import QtQuick
import QtQuick.Dialogs
import QtQuick.Window

FileDialog {
    id: saveDialog

    property int dialog_type: 0

    title: "Save as"

    currentFolder: StandardPaths.writableLocation(
                       StandardPaths.DocumentsLocation)

    fileMode: FileDialog.SaveFile

    onAccepted: send_request_forward()

    function send_request_forward() {

        if (dialog_type === 0) {
            saagia_controller.save_to_file(selectedFile)
        } else {
            console.log("Save preferences file")
        }
    }
}
