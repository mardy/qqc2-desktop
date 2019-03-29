include("../common-config.pri")
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
    ComboBoxDelegate.qml \
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
    Layouts/ColumnLayout.qml \
    Layouts/GridLayout.qml \
    Layouts/RowLayout.qml \
    Layouts/qmldir \
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
    TabView.qml \
    TextArea.qml \
    TextField.qml \
    ToolBar.qml \
    ToolButton.qml \
    ToolSeparator.qml \
    ToolTip.qml

OTHER_FILES += \
    $$QML_FILES

DESTDIR = $$OUT_PWD/$$TARGETPATH

include("../qml_module.pri")
include("../qml_preprocessor.pri")
