TEMPLATE = aux
TARGETPATH = QtQuick/Controls.2/Desktop

QML_FILES += \
    ApplicationWindow.qml \
# TODO    BusyIndicator.qml \
    Button.qml \
    CheckBox.qml \
    CheckDelegate.qml \
    CheckIndicator.qml \
    ComboBox.qml \
    Container.qml \
    Control.qml \
    DelayButton.qml \
    DialogButtonBox.qml \
    Dialog.qml \
    Dial.qml \
    Drawer.qml \
    Frame.qml \
    GroupBox.qml \
    ItemDelegate.qml \
    Label.qml \
#    MenuBarItem.qml \
    MenuItem.qml \
    Menu.qml \
    Popup.qml \
    ProgressBar.qml \
    RadioButton.qml \
    RadioDelegate.qml \
    RangeSlider.qml \
    RoundButton.qml \
    ScrollBar.qml \
    ScrollView.qml \
    Slider.qml \
    SpinBox.qml \
    SwitchDelegate.qml \
    SwitchIndicator.qml \
    Switch.qml \
    TabBar.qml \
    TabButton.qml \
    TextArea.qml \
    TextField.qml \
    ToolBar.qml \
    ToolButton.qml \
    ToolTip.qml

OTHER_FILES += \
    $$QML_FILES

target.files = \
    $$QML_FILES
target.path = $$[QT_INSTALL_QML]/$${TARGETPATH}
INSTALLS += target

load(qml_module)

#!static: CONFIG += qmlcache
