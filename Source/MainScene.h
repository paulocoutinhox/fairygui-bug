#pragma once

#include "axmol.h"
#include "FairyGUI.h"
#include "gui/DemoDialogWindow.h"

class MainScene : public ax::Scene
{
private:
    DemoDialogWindow* demoDialog;
    fairygui::GRoot* groot;

public:
    bool init() override;
    void update(float delta) override;
    void menuCloseCallback(ax::Ref* sender);
};
