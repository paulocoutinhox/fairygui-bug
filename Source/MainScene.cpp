#include "MainScene.h"

USING_NS_AX;

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    // native label
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }

    // fairy gui
    fairygui::UIConfig::registerFont("Pulang", "fonts/Pulang.ttf");
    fairygui::UIConfig::registerFont("MF", "fonts/Marker Felt.ttf");

    groot = fairygui::GRoot::create(this);
    groot->retain();

    fairygui::UIPackage::addPackage("ui/fairy-gui/Main");

    demoDialog = DemoDialogWindow::create();
    demoDialog->retain();
    demoDialog->initWindow();
    demoDialog->show();
    
    demoDialog->btUpdateClickCallback = [=](fairygui::EventContext * context) {
        demoDialog->showMessage("UPDATED MESSAGE: XYZ");
        label->setString("UPDATED MESSAGE: XYZ");
    };

    // update
    scheduleUpdate();

    return true;
}

void MainScene::update(float delta)
{
    //
}
