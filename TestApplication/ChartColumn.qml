import QtQuick 2.0

Item
{
    property string title: "default"
    property double columnSize: 1.0

    Rectangle
    {
        id: theRect

        color: "red"

        Text
        {
            text: title
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            rotation : 270
        }

        width: chartListView1.width / (columnsCount + 1)
        height: chartListView1.height * columnSize
        y: chartListView1.height - height

    }
}
