import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.1
import com.backend 1.0

Window {
    width: 320
    height: 240
    minimumWidth: 640
    minimumHeight: 480

    visible: true
    title: qsTr("Test Application")

    BackEnd {
        id: backend

        onResultsAreReady: {
            chartView1.model.set(index, { name: wordName + " (" + wordsCount.toString() + ")", size: value })
        }

        onProgressChanged: {
            progressBar1.value = progress
        }

        onParsingCompleted: {
            button1.enabled = true
            messageDialog.text = "File parsing completed in " + parsingTime + " seconds"
            messageDialog.open()
        }
    }

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent
        spacing: 6
        anchors.margins: 6

        ChartView {
            id: chartView1

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 300
            Layout.minimumHeight: 150
        }

        RowLayout {
            Rectangle {
                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.maximumWidth: 50
                Text {
                    anchors.centerIn: parent
                    text: qsTr("Progress")
                }
            }

            ProgressBar {
                id: progressBar1

                Layout.fillWidth: true
                Layout.minimumWidth: 100
            }

            Button {
                id: button1

                Layout.fillWidth: true
                Layout.minimumWidth: 100
                Layout.maximumWidth: 100
                Layout.minimumHeight: 40

                text: qsTr("Open test file")

                onClicked: {
                    fileOpenDialog.open()
                }
            }
        }
    }


    FileDialog {
        id: fileOpenDialog

        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: [ "Text files (*.txt *.txt)" ]

        onAccepted: {
            for (var i = 0; i < 15; i++)
            {
                chartView1.model.set(i, { name: "", size: 0.0 })
            }

            button1.enabled = false

            backend.fileName = fileOpenDialog.fileUrl
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Message"
        icon: StandardIcon.Information
    }

}
