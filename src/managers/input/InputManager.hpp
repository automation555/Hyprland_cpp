#pragma once

#include "../../defines.hpp"
#include <list>
#include "../../helpers/WLClasses.hpp"
#include "../../Window.hpp"
#include "../../helpers/Timer.hpp"

class CInputManager {
public:

    void            onMouseMoved(wlr_pointer_motion_event*);
    void            onMouseWarp(wlr_pointer_motion_absolute_event*);
    void            onMouseButton(wlr_pointer_button_event*);
    void            onKeyboardKey(wlr_keyboard_key_event*, SKeyboard*);
    void            onKeyboardMod(void*, SKeyboard*);

    void            newKeyboard(wlr_input_device*);
    void            newMouse(wlr_input_device*);
    void            destroyKeyboard(SKeyboard*);
    void            destroyMouse(wlr_input_device*);

    void            constrainMouse(SMouse*, wlr_pointer_constraint_v1*);
    void            recheckConstraint(SMouse*);

    Vector2D        getMouseCoordsInternal();
    void            refocus();

    void            setKeyboardLayout();

    void            updateDragIcon();
    void            updateCapabilities(wlr_input_device*);


    // for dragging floating windows
    CWindow*        currentlyDraggedWindow = nullptr;
    int             dragButton = -1;

    SDrag           m_sDrag;

    std::list<SConstraint>  m_lConstraints;
    std::list<SKeyboard>    m_lKeyboards;
    std::list<SMouse>       m_lMice;

    // tablets
    std::list<STablet>      m_lTablets;
    std::list<STabletTool>  m_lTabletTools;
    std::list<STabletPad>   m_lTabletPads;

    void            newTabletTool(wlr_input_device*);
    void            newTabletPad(wlr_input_device*);
    void            focusTablet(STablet*, wlr_tablet_tool*, bool motion = false);

    SKeyboard*      m_pActiveKeyboard = nullptr;

    CTimer          m_tmrLastCursorMovement;

private:

    uint32_t        m_uiCapabilities = 0;

    void            mouseMoveUnified(uint32_t, bool refocus = false);

    STabletTool*    ensureTabletToolPresent(wlr_tablet_tool*);

    void            applyConfigToKeyboard(SKeyboard*);
};

inline std::unique_ptr<CInputManager> g_pInputManager;