import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Label {

    text:
        "待办事项清单"


    font.pixelSize:
        30


    Layout.alignment:
        Qt.AlignHCenter



    opacity:0



    Component.onCompleted:
    {
        appear.start()
    }



    NumberAnimation {

        id:appear

        target:parent

        property:"opacity"

        from:0

        to:1

        duration:400

        easing.type:
            Easing.OutCubic
    }
}