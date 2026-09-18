import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true

    width: 500
    height: 700

    title: "Todo List"

    // 列视图  主要布局
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        spacing: 15

        // 标记 软件名字
        Label {
            text: "待办事项清单"

            font.pixelSize: 30

            Layout.alignment:
                Qt.AlignHCenter
        }

        // 行分布    功能布局
        RowLayout {

            Layout.fillWidth: true

            // 输入todo 条目
            TextField {
                id: todoInput

                placeholderText:
                    "输入 待办事项"

                Layout.fillWidth: true

                onAccepted: {
                    addTodo()
                }
            }

            // 点击添加条目
            Button {
                text: "添加"

                onClicked: {
                    addTodo()
                }
            }
        }

        // 关键 Listview使用我们定制model
        ListView {
            id: todoList

            Layout.fillWidth: true
            Layout.fillHeight: true

            spacing: 8

            model: todoModel

            // 每一个条目的样子
            delegate: Rectangle {

                width: todoList.width
                height: 55

                border.width: 1
                radius: 12

                RowLayout {

                    anchors.fill: parent

                    anchors.leftMargin: 10
                    anchors.rightMargin: 10

                    CheckBox {

                        checked: model.completed

                        onClicked: {
                            todoManager.toggleTodo(index)
                        }
                    }

                    Label {

                        text: model.title

                        Layout.fillWidth: true

                        elide:
                            Text.ElideRight

                        font.pixelSize: 16

                        opacity:
                            model.completed
                            ? 0.5
                            : 1.0
                    }

                    Button {

                        text: "删除"

                        onClicked: {
                            todoManager.removeTodo(index)
                        }
                    }
                }
            }
        }

        // 清空待办事项按钮
        Button {

            text: "清空所有待办事项"

            Layout.fillWidth: true

            onClicked: {
                todoManager.clearCompleted()
            }
        }
    }

    // 一些需要使用的函数
    //    添加待办事项条目
    function addTodo()
    {
        const text =
            todoInput.text.trim()

        if (text.length === 0)
            return

        todoManager.addTodo(text)

        todoInput.clear()

        todoInput.forceActiveFocus()
    }
}