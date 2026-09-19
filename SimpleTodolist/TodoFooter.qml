import QtQuick


Rectangle {

    id: root


    width:
        parent.width


    height:
        45



    radius:
        height / 2



    property bool hovered:
        mouseArea.containsMouse



    color:

        mouseArea.pressed

        ? "#ffd6d6"

        : hovered

          ? "#ffe8e8"

          : "#fff5f5"



    border.width:
        1


    border.color:
        "#ffcccc"



    scale:

        mouseArea.pressed

        ? 0.96

        : 1



    Behavior on color {

        ColorAnimation {

            duration:150

        }

    }



    Behavior on scale {

        NumberAnimation {

            duration:100

            easing.type:
                Easing.OutCubic

        }

    }



    Text {

        anchors.fill:
            parent


        text:
            "清空已完成事项"



        color:
            "#e74c3c"



        font.pixelSize:
            15



        horizontalAlignment:
            Text.AlignHCenter



        verticalAlignment:
            Text.AlignVCenter

    }



    MouseArea {

        id: mouseArea


        anchors.fill:
            parent



        hoverEnabled:
            true



        cursorShape:
            Qt.PointingHandCursor



        onClicked:
        {
            todoManager.clearCompleted()
        }

    }

}