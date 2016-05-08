import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem
import QtQuick.Controls 1.3 as QuickControls
import Material.Extras 0.1

import FinanceManager 0.1

import "qrc:assets/scripts/formChecks.js" as FormChecks


ColumnLayout {
    property var budgetList: [];
    spacing: 0

    ListItem.Standard {
        action: Item {}

        content: RowLayout {
            anchors.centerIn: parent
            width: parent.width

            TextField {
                id: nameTextField
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.4 * parent.width

                floatingLabel: true
                placeholderText: "Name"

                onTextChanged: {
                    nameTextField.helperText = ""
                    nameTextField.hasError = false
                }
            }

            MenuField {
                id: nameModifier
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["is equal", "contains", "does not contain"]
            }

            MenuField {
                id: nameLinker
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["AND", "OR"]
            }
        }
    }

    ListItem.Standard {
        action: Item {}

        content: RowLayout {
            anchors.centerIn: parent
            width: parent.width

            TextField {
                id: descriptionTextField
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.4 * parent.width

                floatingLabel: true
                placeholderText: "Description"

                onTextChanged: {
                    descriptionTextField.helperText = ""
                    descriptionTextField.hasError = false
                }
            }

            MenuField {
                id: descriptionModifier
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["is equal", "contains", "does not contain"]
            }

            MenuField {
                id: descriptionLinker
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["AND", "OR"]
            }
        }
    }

    Dialog {
        id: creationDatePickerDialog
        hasActions: true
        contentMargins: 0
        floatingActions: true

        DatePicker {
            id: creationDatePicker
            frameVisible: false
            dayAreaBottomMargin : Units.dp(48)
        }

        onAccepted: {
            creationTextField.text = Qt.formatDate(creationDatePicker.selectedDate, "ddd MMMM yyyy")
        }
    }

    ListItem.Standard {
        action: Item {}

        content: RowLayout {
            anchors.centerIn: parent
            width: parent.width

            TextField {
                id: creationTextField
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.4 * parent.width

                floatingLabel: true
                placeholderText: "Created at"

                MouseArea {
                    anchors.fill: parent
                    onClicked: creationDatePickerDialog.show()
                }
            }

            MenuField {
                id: creationTimeModifier
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["before", "after"]
            }

            MenuField {
                id: creationTimeLinker
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["AND", "OR"]
            }
        }
    }

    Dialog {
        id: expiresFromDatePickerDialog
        hasActions: true
        contentMargins: 0
        floatingActions: true

        DatePicker {
            id: expiresFromDatePicker
            frameVisible: false
            dayAreaBottomMargin : Units.dp(48)
        }

        onAccepted: {
            expiresFromTextField.text = Qt.formatDate(expiresFromDatePicker.selectedDate, "ddd MMMM yyyy")
        }
    }

    Dialog {
        id: expiresToDatePickerDialog
        hasActions: true
        contentMargins: 0
        floatingActions: true

        DatePicker {
            id: expiresToDatePicker
            frameVisible: false
            dayAreaBottomMargin : Units.dp(48)
        }

        onAccepted: {
            expiresToTextField.text = Qt.formatDate(expiresToDatePicker.selectedDate, "ddd MMMM yyyy")
        }
    }

    ListItem.Standard {
        action: Item {}

        content: RowLayout {
            anchors.centerIn: parent
            width: parent.width

            TextField {
                id: expiresFromTextField
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.4 * parent.width

                floatingLabel: true
                placeholderText: "Expires from"

                MouseArea {
                    anchors.fill: parent
                    onClicked: expiresFromDatePickerDialog.show()
                }
            }

            TextField {
                id: expiresToTextField
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.4 * parent.width

                floatingLabel: true
                placeholderText: "Expires to"

                MouseArea {
                    anchors.fill: parent
                    onClicked: expiresToDatePickerDialog.show()
                }
            }

            MenuField {
                id: expireTimeLinker
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["AND", "OR"]
            }
        }
    }

    ListItem.Standard {
        action: Item {}

        content: RowLayout {
            anchors.centerIn: parent
            width: parent.width

            QuickControls.ExclusiveGroup { id: expiredOptionGroup }

            Label {
                Layout.alignment : Qt.AlignHCenter
                text: "Expired"
            }

            RadioButton {
                checked: true
                text: "No"
                canToggle: true
                exclusiveGroup: expiredOptionGroup
            }

            RadioButton {
                checked: false
                text: "Yes"
                canToggle: true
                exclusiveGroup: expiredOptionGroup
            }

            RadioButton {
                checked: false
                text: "N/A"
                canToggle: true
                exclusiveGroup: expiredOptionGroup
            }

            MenuField {
                id: expiredLinker
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["AND", "OR"]
            }
        }
    }

    ListItem.Standard {
        action: Item {}

        content: RowLayout {
            anchors.centerIn: parent
            width: parent.width

            TextField {
                id: valueTextField
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.4 * parent.width

                floatingLabel: true
                placeholderText: "Value"

                onTextChanged: {
                    valueTextField.helperText = ""
                    valueTextField.hasError = false
                }
            }

            MenuField {
                id: valueModifier
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 0.2 * parent.width

                model: ["is equal", "bigger", "smaller"]
            }
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignRight
        spacing: Units.dp(8)

        anchors {
            right: parent.right
            margins: Units.dp(16)
        }

        Button {
            id: registerButton
            text: "Search"
            textColor: Theme.primaryColor
            enabled: true
            onClicked: FormChecks.getBudgetList(false)
        }
    }

    ListView {
        id: budgetListView
        model: budgetList.length
        delegate: ListItem.Subtitled {
            text: name
            subText: description
            valueText: value
            maximumLineCount: 3
        }
    }

    Repeater {
        id: budgetRepeater
        model: budgetList.length
        ListItem.Subtitled {
            text: budgetList[index].name
            subText: budgetList[index].description +
                     "\n Created at: " + Qt.formatDateTime(budgetList[index].creationDate, "dd/MM/yyyy") +
                     " - Expires at: " + Qt.formatDateTime(budgetList[index].expirationDate, "dd/MM/yyyy")
            valueText: budgetList[index].value
            maximumLineCount: 3
        }
    }

    Component.onCompleted: FormChecks.getBudgetList(true);
}
