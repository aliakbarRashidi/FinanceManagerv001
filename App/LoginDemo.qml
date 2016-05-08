import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.Extras 0.1

import FinanceManager 0.1

import "qrc:assets/scripts/formChecks.js" as FormChecks


Item {
    id: loginView

    View {
        id: loginDialog
        anchors.centerIn: parent
        width: Units.dp(240)
        height: Units.dp(310)
        radius: Units.dp(2)
        elevation: 2

        CircleImage {
            id: userImage

            //source: currentUser.faceIconUrl
            visible: status == Image.Ready
            width: Units.dp(80)
            height: width
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: Units.dp(45)
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(0,0,0,0.3)
                radius: width/2
            }
        }

        Item {
            anchors.fill: userImage
            visible: !userImage.visible

            Icon {
                anchors.centerIn: parent
                name: "action/account_circle"
                size: Units.dp(95)
            }
        }

        Label {
            id: usernameLabel

            text: "Username"
            style: "title"

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: userImage.bottom
                topMargin: Units.dp(20)
            }
        }

        TextField {
            id: emailTextField
            anchors {
                left: parent.left
                right: parent.right
                bottom: passwordTextField.top
                margins: Units.dp(20)
            }

            floatingLabel: true
            placeholderText: "Email"

            onTextChanged: {
                emailTextField.helperText = ""
                emailTextField.hasError = false
            }

            onAccepted: FormChecks.doLogin()
        }

        TextField {
            id: passwordTextField
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: Units.dp(20)
            }

            floatingLabel: true
            placeholderText: "Password"

            echoMode: TextInput.Password

            onTextChanged: {
                passwordTextField.helperText = ""
                passwordTextField.hasError = false
            }

            onAccepted: FormChecks.doLogin()
        }
    }

    Connections {
        target: SessionManager

        onAuthenticationSucceeded: {
            print("OK!")
        }
        onAuthenticationFailed: {
            print("FAILURE!")
        }
    }
}
