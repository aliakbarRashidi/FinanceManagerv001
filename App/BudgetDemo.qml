import QtQuick 2.4
import QtQuick.Controls 1.4
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
                text: "Register New Budget"
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
                    name: "action/account_circle"
                }

                content: TextField {
                    id: descriptionField
                    characterLimit: 255
                    anchors.centerIn: parent
                    width: parent.width
                    floatingLabel: false
                    placeholderText: "Description"

                    onTextChanged: {
                        if (descriptionField.text.length > descriptionField.characterLimit) {
                            descriptionField.helperText = "Description is too long."
                            descriptionField.hasError = true
                        } else {
                            descriptionField.helperText = ""
                            descriptionField.hasError = false
                        }
                    }
                }
            }

            Dialog {
                id: expiryDatePickerDialog
                hasActions: true
                contentMargins: 0
                floatingActions: true

                DatePicker {
                    id: expiryDatePicker
                    frameVisible: false
                    dayAreaBottomMargin : Units.dp(48)
                }

                onAccepted: {
                    expiryField.text = Qt.formatDate(expiryDatePicker.selectedDate, "ddd MMMM yyyy")
                }
            }

            ListItem.Standard {
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/calendar"
                }

                content: TextField {
                    id: expiryField
                    characterLimit: 10
                    anchors.centerIn: parent
                    width: parent.width
                    floatingLabel: false
                    placeholderText: "Expires at..."

                    MouseArea {
                        anchors.fill: parent
                        onClicked: expiryDatePickerDialog.show()
                    }
                }
            }

            ListItem.Standard {
                action: Icon {
                    anchors.centerIn: parent
                    name: "action/account_circle"
                }

                content: TextField {
                    id: valueField
                    characterLimit: 100
                    anchors.centerIn: parent
                    width: parent.width
                    floatingLabel: false
                    placeholderText: "Value"
                    validator: RegExpValidator{ regExp: FormChecks.numberPattern }

                    onTextChanged: {
                        if (valueField.text.length > valueField.characterLimit) {
                            valueField.helperText = "Value is too big."
                            valueField.hasError = true
                        } else if (valueField.text.length === 0) {
                            valueField.helperText = "Value cannot be empty."
                            valueField.text = 0
                            valueField.hasError = true
                        } else {
                            valueField.helperText = ""
                            valueField.hasError = false
                        }
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
                    onClicked: FormChecks.createBudget()
                }
            }
        }
    }

    Connections {
        target: SessionManager

        onBudgetCreationSucceeded: {
            print("OK!")
        }
        onBudgetCreationFailed: {
            print("FAILURE!")
        }
    }
}
