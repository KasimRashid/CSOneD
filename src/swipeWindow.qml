import QtQuick 2.0

import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
Window {
    visible: true
    width: 200
    height: 400
    title: qsTr("Hello World")

    id: page

    swipView {
        id: swipeView
        anchors.fill: parent
        currentIndex: 0
        page {
                    Label {
                        text: qsTr("First page")
                        anchors.centerIn: parent
                    }
                }
        page {
                    Label {
                        text: qsTr("Second page")
                        anchors.centerIn: parent
                    }
                }
        page {
                    Label {
                        text: qsTr("Third page")
                        anchors.centerIn: parent
                    }
                }
        page {
                    Label {
                        text: qsTr("Fourth page")
                        anchors.centerIn: parent
                    }
                }
        page {
                    Label {
                        text: qsTr("Fifth page")
                        anchors.centerIn: parent
                    }
                }
    }



    Rectangle
    {
        id:minus
        width:parent.width/2
        height:100
        anchors.left:parent.left
        anchors.bottom:parent.bottom
        color:"red"
        MouseArea
        {
            anchors.fill:parent
            onClicked:{
                if(swipeView.currentIndex>0)
                    swipeView.currentIndex--
            }
        }
    }
    Rectangle
    {
        id:plus
        width:parent.width/2
        height:100
        anchors.right:parent.right
        anchors.bottom:parent.bottom
        color:"green"
        MouseArea
        {
            anchors.fill:parent
            onClicked:{
                if(swipeView.currentIndex<4)
                    swipeView.currentIndex++
            }
        }
    }
}
