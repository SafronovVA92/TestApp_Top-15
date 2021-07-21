import QtQuick 2.0

ListView {
    id: chartListView1

    readonly property int columnsCount: 15

    interactive: false
    orientation:  Qt.Horizontal
    spacing: (chartView1.width / columnsCount) // for each column

    delegate: Item
    {
        id: myRectComp

        ChartColumn
        {
            title: name
            columnSize: size
        }

    }

    model: ListModel {
        id:  myModel

        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
        ListElement { name: ""; size: 0.0 }
    }
}
