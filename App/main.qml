/**
    Personal Finance App Test 1
    main.qml
    Purpose: A container to hold and display various ui tests for the project.

    @author raldi
    @version 0.0.1 27/02/16
*/

import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem
import QtQuick.Window 2.1
import Qt.labs.settings 1.0


ApplicationWindow {
    // Main configuration section for the application window
    id: mainwindow
    title: "Initial tests for personal finance manager"
    visible: true // Needed if loading from c++.

    property string primaryChosen: "blue"
    property string accentChosen: "red"
    property string tabHighlightChosen: "white"

    // Settings wont work with Units.dp
    height: Units.dp(600)
    //minimumHeight: Units.dp(500)
    //maximumHeight: Units.dp(1200)
    width: Units.dp(800)
    //minimumWidth: Units.dp(300)
    //maximumWidth: Units.dp(1080)

    // Theme colors.
    theme {
        primaryColor: Palette.colors[primaryChosen]["500"]
        accentColor: Palette.colors[accentChosen]["500"]
        tabHighlightColor: Palette.colors[tabHighlightChosen]["500"]
    }

    // Persistent application settings.
    Settings {
        id: settings
        property alias x: mainwindow.x
        property alias y: mainwindow.y
        property alias width: mainwindow.width
        property alias height: mainwindow.height
        property alias primaryChosen: mainwindow.primaryChosen
        property alias accentChosen: mainwindow.accentChosen
        property alias tabHighlightChosen: mainwindow.tabHighlightChosen
    }

    // Application structure.
    property var appLoginViews: [
            "Login", "Register"
    ]

    property var appChartViews: [
            "ToDo"
    ]

    property var appLandingViews: [
            "ToDo"
    ]

    property var appFormViews: [
            "Budget", "ListBudget"
    ]

    property var appDashboardViews: [
            "ToDo"
    ]

    property var appProfileViews: [
            "ToDo"
    ]

    property var sections: [ appLoginViews, appChartViews, appLandingViews, appFormViews,
        appDashboardViews, appProfileViews ]

    property var sectionTitles: [ "Login Views", "Chart Views", "Landing Views", "Form Views",
        "Dashboard Views", "Profile Views"]

    property string selectedComponent: sections[0][0]

    initialPage: TabbedPage {
        id: page

        title: "GlFinance Demo v0.0.1"

        actionBar.maxActionCount: navDrawer.enabled ? 3 : 4

        actions: [
            Action {
                iconName: "alert/warning"
                name: "Dummy error"
                onTriggered: mainwindow.showError("Something went wrong", "Do you want to retry?", "Close", true)
            },

            Action {
                iconName: "image/color_lens"
                name: "Colors"
                onTriggered: colorPicker.show()
            },

            Action {
                iconName: "action/settings"
                name: "Settings"
                hoverAnimation: true
            },

            Action {
                iconName: "alert/warning"
                name: "THIS SHOULD BE HIDDEN!"
                visible: false
            },

            Action {
                iconName: "action/language"
                name: "Language"
                enabled: false
            },

            Action {
                iconName: "action/account_circle"
                name: "Accounts"
            }
        ]

        backAction: navDrawer.action

        NavigationDrawer {
            id: navDrawer

            enabled: page.width < Units.dp(500)

            onEnabledChanged: smallLoader.active = enabled

            Flickable {
                anchors.fill: parent

                contentHeight: Math.max(content.implicitHeight, height)

                Column {
                    id: content
                    anchors.fill: parent

                    Repeater {
                        model: sections

                        delegate: Column {
                            width: parent.width

                            ListItem.Subheader {
                                text: sectionTitles[index]
                            }

                            Repeater {
                                model: modelData
                                delegate: ListItem.Standard {
                                    text: modelData
                                    selected: modelData == mainwindow.selectedComponent
                                    onClicked: {
                                        mainwindow.selectedComponent = modelData
                                        navDrawer.close()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Repeater {
            model: !navDrawer.enabled ? sections : 0

            delegate: Tab {
                title: sectionTitles[index]

                property string selectedComponent: modelData[0]
                property var section: modelData

                sourceComponent: tabDelegate
            }
        }

        Loader {
            id: smallLoader
            anchors.fill: parent
            sourceComponent: tabDelegate

            property var section: []
            visible: active
            active: false
        }
    }

    Dialog {
        id: colorPicker
        title: "Pick color"

        positiveButtonText: "Done"

        MenuField {
            id: selection
            model: ["Primary color", "Accent color", "Background color"]
            width: Units.dp(160)
        }

        Grid {
            columns: 7
            spacing: Units.dp(8)

            Repeater {
                model: [
                    "red", "pink", "purple", "deepPurple", "indigo",
                    "blue", "lightBlue", "cyan", "teal", "green",
                    "lightGreen", "lime", "yellow", "amber", "orange",
                    "deepOrange", "grey", "blueGrey", "brown", "black",
                    "white"
                ]

                Rectangle {
                    width: Units.dp(30)
                    height: Units.dp(30)
                    radius: Units.dp(2)
                    color: Palette.colors[modelData]["500"]
                    border.width: modelData === "white" ? Units.dp(2) : 0
                    border.color: Theme.alpha("#000", 0.26)

                    Ink {
                        anchors.fill: parent

                        onPressed: {
                            switch(selection.selectedIndex) {
                                case 0:
                                    theme.primaryColor = parent.color
                                    break;
                                case 1:
                                    theme.accentColor = parent.color
                                    break;
                                case 2:
                                    theme.backgroundColor = parent.color
                                    break;
                            }
                        }
                    }
                }
            }
        }

        onRejected: {
            // TODO set default colors again but we currently don't know what that is
        }
    }

    Component {
        id: tabDelegate

        Item {

            Sidebar {
                id: sidebar

                expanded: !navDrawer.enabled

                Column {
                    width: parent.width

                    Repeater {
                        model: section
                        delegate: ListItem.Standard {
                            text: modelData
                            selected: modelData == selectedComponent
                            onClicked: selectedComponent = modelData
                        }
                    }
                }
            }
            Flickable {
                id: flickable
                anchors {
                    left: sidebar.right
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                clip: true
                contentHeight: Math.max(example.implicitHeight + 40, height)
                Loader {
                    id: example
                    anchors.fill: parent
                    asynchronous: true
                    visible: status == Loader.Ready
                    // selectedComponent will always be valid, as it defaults to the first component
                    source: {
                        if (navDrawer.enabled) {
                            return Qt.resolvedUrl("%1Demo.qml").arg(mainwindow.selectedComponent.replace(" ", ""))
                        } else {
                            return Qt.resolvedUrl("%1Demo.qml").arg(selectedComponent.replace(" ", ""))
                        }
                    }
                }

                ProgressCircle {
                    anchors.centerIn: parent
                    visible: example.status == Loader.Loading
                }
            }
            Scrollbar {
                flickableItem: flickable
            }
        }
    }

    Component.onDestruction: {
        settings.x = mainwindow.x
        settings.y = mainwindow.y
        settings.width = mainwindow.width
        settings.height = mainwindow.height
        settings.accentchosen = mainwindow.accentchosen
    }
}
