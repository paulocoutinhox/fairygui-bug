#include "gui/DemoDialogWindow.h"
#include "DemoDialogWindow.h"


using namespace fairygui;

void DemoDialogWindow::onInit() {
    setContentPane(UIPackage::createObject("Main", "Dialog")->as<GComponent>());
    center();
    
    getContentPane()->getChild("btUpdate")->addClickListener(
        CC_CALLBACK_1(DemoDialogWindow::onBtUpdateClick, this)
    );
}

void DemoDialogWindow::onShown() {
    //
}

void DemoDialogWindow::showMessage(std::string message) {
    auto lbMessage1 = dynamic_cast<fairygui::GTextField *>(getContentPane()->getChild("lbMessage1"));
    lbMessage1->setText(message);
    
    auto lbMessage2 = dynamic_cast<fairygui::GTextField *>(getContentPane()->getChild("lbMessage2"));
    lbMessage2->setText(message);
}

void DemoDialogWindow::onBtUpdateClick(fairygui::EventContext * context) {
    btUpdateClickCallback(context);
}
