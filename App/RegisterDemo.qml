import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

import FinanceManager 0.1

import "qrc:assets/scripts/formChecks.js" as FormChecks


Item {
    id: registerView

    View {
        anchors.centerIn: parent

        width: Units.dp(350)
        height: column.implicitHeight + Units.dp(32)

        elevation: 1
        radius: Units.dp(2)

        ColumnLayout {
            id: column

            anchors {
                fill: parent
                topMargin: Units.dp(16)
                bottomMargin: Units.dp(16)
            }

            Label {
                id: titleLabel

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Units.dp(16)
                }

                style: "title"
                text: "Register New User"
            }

            ListItem.Standard {
                action: Icon {
                    anchors.centerIn: parent
                    name: "action/account_circle"
                }

                content: TextField {
                    id: nameField
                    characterLimit: 50
                    anchors.centerIn: parent
                    width: parent.width
                    floatingLabel: true
                    placeholderText: "Name"
                    validator: RegExpValidator{ regExp: FormChecks.namePattern }

                    onTextChanged: {
                        if (nameField.text.length > nameField.characterLimit) {
                            nameField.helperText = "Name is too long."
                            nameField.hasError = true
                        } else if (nameField.text.length === 0) {
                            nameField.helperText = "Name cannot be empty."
                            nameField.hasError = true
                        } else {
                            nameField.helperText = ""
                            nameField.hasError = false
                        }
                    }
                }
            }

            ListItem.Standard {
                action: Icon {
                    anchors.centerIn: parent
                    name: "communication/email"
                }

                content: TextField {
                    id: emailField
                    characterLimit: 100
                    anchors.centerIn: parent
                    width: parent.width
                    floatingLabel: false
                    placeholderText: "Email"
                    validator: RegExpValidator{ regExp: FormChecks.emailPattern }

                    onTextChanged: {
                        if (emailField.text.length > emailField.characterLimit) {
                            emailField.helperText = "Email is too long."
                            emailField.hasError = true
                        } else if (emailField.text.length === 0) {
                            emailField.helperText = "Email cannot be empty."
                            emailField.hasError = true
                        } else {
                            emailField.helperText = ""
                            emailField.hasError = false
                        }
                    }
                }
            }

            ListItem.Standard {
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/lock"
                }

                content: TextField {
                    id: passwordField
                    characterLimit: 100
                    anchors.centerIn: parent
                    width: parent.width
                    echoMode: TextInput.Password
                    floatingLabel: false
                    placeholderText: "Password"

                    onTextChanged: {
                        if (passwordField.text.length > passwordField.characterLimit) {
                            passwordField.helperText = "Password is too long."
                            passwordField.hasError = true
                        } else if (passwordField.text.length === 0) {
                            passwordField.helperText = "Password cannot be empty."
                            passwordField.hasError = true
                        } else {
                            passwordField.helperText = ""
                            passwordField.hasError = false
                        }
                    }
                }
            }

            ListItem.Standard {
                action: Icon {
                    id: passwordRetypeFieldIcon
                    anchors.centerIn: parent
                    name: "awesome/lock"
                }

                content: TextField {
                    id: passwordRetypeField
                    characterLimit: 100
                    anchors.centerIn: parent
                    width: parent.width
                    echoMode: TextInput.Password
                    floatingLabel: false
                    placeholderText: "Retype Password"

                    onTextChanged: {
                        if (passwordField.text === passwordRetypeField.text) {
                            passwordRetypeFieldIcon.name = "action/check_circle"
                            passwordField.helperText = "Passwords match."
                            passwordRetypeField.hasError = false
                        } else {
                            passwordRetypeFieldIcon.name = "action/info"
                            passwordField.helperText = "Passwords do not match."
                            passwordRetypeField.hasError = true
                        }
                    }
                }
            }

            Dialog {
                id: birthdayDatePickerDialog
                hasActions: true
                contentMargins: 0
                floatingActions: true

                DatePicker {
                    id: birthdayDatePicker
                    frameVisible: false
                    dayAreaBottomMargin : Units.dp(48)
                }

                onAccepted: {
                    birthdateField.text = Qt.formatDate(birthdayDatePicker.selectedDate, "ddd MMMM yyyy")
                    //birthdateField.text = new Date(birthdayDatePicker.selectedDate).toLocaleDateString("en-US")
                }
            }

            ListItem.Standard {
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/calendar"
                }

                content: TextField {
                    id: birthdateField
                    characterLimit: 10
                    anchors.centerIn: parent
                    width: parent.width
                    floatingLabel: false
                    placeholderText: "Birthdate"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: birthdayDatePickerDialog.show()
                    }
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: Units.dp(8)
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: Units.dp(8)

                anchors {
                    right: parent.right
                    margins: Units.dp(16)
                }

                Button {
                    id: cancelButton
                    text: "Cancel"
                    textColor: Theme.primaryColor
                }

                Button {
                    id: registerButton
                    text: "Done"
                    textColor: Theme.primaryColor
                    enabled: true
                    onClicked: FormChecks.doRegister()
                }
            }
        }
    }

    Connections {
        target: SessionManager

        onAccountCreationSucceeded: {
            print("OK!")
        }
        onAccountCreationFailed: {
            print("FAILURE!")
        }
    }
}
