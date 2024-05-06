#pragma once

#include <string>

#include "axmol.h"
#include "FairyGUI.h"

class DemoDialogWindow : public fairygui::Window
{
public:
    CREATE_FUNC(DemoDialogWindow);
    void showMessage(std::string message);
    std::function<void(fairygui::EventContext*)> btUpdateClickCallback;

protected:
    virtual void onInit() override;
    virtual void onShown() override;
    void onBtUpdateClick(fairygui::EventContext* context);
};
