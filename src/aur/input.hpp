#pragma once
#include "variables.hpp"
struct INPUT {
    struct Settings {
        inline static f32 MouseCursorScale       = 1.0f;
        inline static f32 MouseDoubleClickDelay  = 0.30f;
        inline static f32 KeyRepeatDelay         = 0.275f;
        inline static f32 KeyRepeatRate          = 0.050f;
    };
    using Flags = c32;
    enum Flags_ {
        Flags_None                           = 0,
        Flags_Repeat                         = 1 << 0,
        // Flags for Shortcut(), SetNextItemShortcut()
        // - Routing policies: RouteGlobal+OverActive >> RouteActive or RouteFocused (if owner is active item) >> RouteGlobal+OverFocused >> RouteFocused (if in focused window stack) >> RouteGlobal.
        // - Default policy is RouteFocused. Can select only 1 policy among all available.
        Flags_RouteActive                    = 1 << 10,
        Flags_RouteFocused                   = 1 << 11, // Route to windows in the focus stack (DEFAULT). Deep-most focused window takes inputs. Active item takes inputs over deep-most focused window.
        Flags_RouteGlobal                    = 1 << 12, // Global route (unless a focused window or active item registered the route).
        Flags_RouteAlways                    = 1 << 13, // Do not register route, poll keys directly.
        // - Routing options
        Flags_RouteOverFocused               = 1 << 14, // Option: global route: higher priority than focused route (unless active item in focused route).
        Flags_RouteOverActive                = 1 << 15, // Option: global route: higher priority than active item. Unlikely you need to use that: will interfere with every active items, e.g. Ctrl+A registered by InputText will be overridden by this. May not be fully honored as user/internal code is likely to always assume they can access keys when active.
        Flags_RouteUnlessBgFocused           = 1 << 16, // Option: global route: will not be applied if underlying background/void is focused (== no Dear UI windows are focused). Useful for overlay applications.
        Flags_RouteFromRootWindow            = 1 << 17, // Option: route evaluated from the point of view of root window rather than current window.
        // Flags for SetNextItemShortcut()
        Flags_Tooltip                        = 1 << 18,
        // Flags for IsKeyPressed(), IsKeyChordPressed(), IsMouseClicked(), Shortcut()
        Flags_RepeatRateDefault              = 1 << 1,
        Flags_RepeatRateFast                 = 1 << 2,
        Flags_RepeatRateFastest              = 1 << 3,
        // - Repeat mode: Specify when repeating key pressed can be interrupted. In theory uiInputFlags_RepeatUntilOtherKeyPress may be a desirable default, but it would break too many behavior so everything is opt-in.
        Flags_RepeatUntilRelease             = 1 << 4,   // Stop repeating when released (default for all functions except Shortcut). This only exists to allow overriding Shortcut() default behavior.
        Flags_RepeatUntilKeyModsChange       = 1 << 5,   // Stop repeating when released OR if keyboard mods are changed (default for Shortcut)
        Flags_RepeatUntilKeyModsChangeFromNone = 1 << 6,  // Stop repeating when released OR if keyboard mods are leaving the None state. Allows going from Mod+Key to Key by releasing Mod.
        Flags_RepeatUntilOtherKeyPress       = 1 << 7,   // Stop repeating when released OR if any other keyboard key is pressed during the repeat
        // Flags for SetKeyOwner(), SetItemKeyOwner(). Locking key away from non-input aware code. Locking is useful to make input-owner-aware code steal keys from non-input-owner-aware code. If all code is input-owner-aware locking would never be necessary.
        Flags_LockThisFrame                  = 1 << 20,  // Further accesses to key data will require EXPLICIT owner ID (uiKeyOwner_Any/0 will NOT accepted for polling). Cleared at end of frame.
        Flags_LockUntilRelease               = 1 << 21,  // Further accesses to key data will require EXPLICIT owner ID (uiKeyOwner_Any/0 will NOT accepted for polling). Cleared when the key is released or at end of each frame if key is released.
        // - Condition for SetItemKeyOwner()
        Flags_CondHovered                    = 1 << 22,  // Only set if item is hovered (default to both)
        Flags_CondActive                     = 1 << 23,  // Only set if item is active (default to both)
        Flags_CondDefault_                   = Flags_CondHovered            | Flags_CondActive,
        // [Internal] Mask of which function support which flags
        Flags_RepeatRateMask_                = Flags_RepeatRateDefault      | Flags_RepeatRateFast           | Flags_RepeatRateFastest,
        Flags_RepeatUntilMask_               = Flags_RepeatUntilRelease     | Flags_RepeatUntilKeyModsChange | Flags_RepeatUntilKeyModsChangeFromNone | Flags_RepeatUntilOtherKeyPress,
        Flags_RepeatMask_                    = Flags_Repeat                 | Flags_RepeatRateMask_          | Flags_RepeatUntilMask_,
        Flags_CondMask_                      = Flags_CondHovered            | Flags_CondActive,
        Flags_RouteTypeMask_                 = Flags_RouteActive            | Flags_RouteFocused             | Flags_RouteGlobal                      | Flags_RouteAlways,
        Flags_RouteOptionsMask_              = Flags_RouteOverFocused       | Flags_RouteOverActive          | Flags_RouteUnlessBgFocused             | Flags_RouteFromRootWindow,
        Flags_SupportedByIsKeyPressed        = Flags_RepeatMask_,
        Flags_SupportedByIsMouseClicked      = Flags_Repeat,
        Flags_SupportedByShortcut            = Flags_RepeatMask_            | Flags_RouteTypeMask_           | Flags_RouteOptionsMask_,
        Flags_SupportedBySetNextItemShortcut = Flags_RepeatMask_            | Flags_RouteTypeMask_           | Flags_RouteOptionsMask_                | Flags_Tooltip,
        Flags_SupportedBySetKeyOwner         = Flags_LockThisFrame          | Flags_LockUntilRelease,
        Flags_SupportedBySetItemKeyOwner     = Flags_SupportedBySetKeyOwner | Flags_CondMask_,
    };
    using Source = c32;
    enum Source_ {
        Source_None = 0,
        Source_Mouse,
        Source_Keyboard,
        Source_Gamepad,
        Source_COUNT
    };
    using MouseSource = c32;
    enum MouseSource_ {
        MouseSource_Mouse = 0,
        MouseSource_TouchScreen,
        MouseSource_Pen,
        MouseSource_COUNT
    };
    using Mouse = c32;
    enum Mouse_ {
        Mouse_None   = -1,
        Mouse_Left   = 0,
        Mouse_Right  = 1,
        Mouse_Middle = 2,
        Mouse_COUNT  = 5
    };
    struct KeyData {
        c1  Down;
        f32 DownDuration;
        f32 DownDurationPrev;
        f32 AnalogValue;
    };
    using Key = c32;
    enum Key_ {
        // Keyboard
        Key_None = 0,
        Key_NamedKey_BEGIN = 512, // First valid key value (other than 0)
        Key_Tab = 512,            // == uiKey_NamedKey_BEGIN
        Key_LeftArrow,
        Key_RightArrow,
        Key_UpArrow,
        Key_DownArrow,
        Key_PageUp,
        Key_PageDown,
        Key_Home,
        Key_End,
        Key_Insert,
        Key_Delete,
        Key_Backspace,
        Key_Space,
        Key_Enter,
        Key_Escape,
        Key_LeftCtrl,  Key_LeftShift,  Key_LeftAlt,  Key_LeftSuper,
        Key_RightCtrl, Key_RightShift, Key_RightAlt, Key_RightSuper,
        Key_Menu,
        Key_0,   Key_1,   Key_2,   Key_3,   Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,
        Key_A,   Key_B,   Key_C,   Key_D,   Key_E, Key_F, Key_G, Key_H, Key_I, Key_J,
        Key_K,   Key_L,   Key_M,   Key_N,   Key_O, Key_P, Key_Q, Key_R, Key_S, Key_T,
        Key_U,   Key_V,   Key_W,   Key_X,   Key_Y, Key_Z,
        Key_F1,  Key_F2,  Key_F3,  Key_F4,  Key_F5, Key_F6,
        Key_F7,  Key_F8,  Key_F9,  Key_F10, Key_F11, Key_F12,
        Key_F13, Key_F14, Key_F15, Key_F16, Key_F17, Key_F18,
        Key_F19, Key_F20, Key_F21, Key_F22, Key_F23, Key_F24,
        Key_Apostrophe,   // '
        Key_Comma,        // ,
        Key_Minus,        // -
        Key_Period,       // .
        Key_Slash,        // /
        Key_Semicolon,    // ;
        Key_Equal,        // =
        Key_LeftBracket,  // [
        Key_Backslash,    // \ (this text inhibit multiline comment caused by backslash)
        Key_RightBracket, // ]
        Key_GraveAccent,  // `
        Key_CapsLock,
        Key_ScrollLock,
        Key_NumLock,
        Key_PrintScreen,
        Key_Pause,
        Key_Keypad0, Key_Keypad1, Key_Keypad2, Key_Keypad3, Key_Keypad4,
        Key_Keypad5, Key_Keypad6, Key_Keypad7, Key_Keypad8, Key_Keypad9,
        Key_KeypadDecimal,
        Key_KeypadDivide,
        Key_KeypadMultiply,
        Key_KeypadSubtract,
        Key_KeypadAdd,
        Key_KeypadEnter,
        Key_KeypadEqual,
        Key_AppBack,               // Often referred as "Browser Back"
        Key_AppForward,
        Key_Oem102,                // Non-US backslash.
        // Gamepad (0.0f to 1.0f)
        //                      // XBOX        | SWITCH | PS       | -> ACTION
        Key_GamepadStart,       // Menu        | +      | Options  |
        Key_GamepadBack,        // View        | -      | Share    |
        Key_GamepadFaceLeft,    // X           | Y      | Square   | Toggle Menu. Hold for Windowing mode (Focus/Move/Resize windows)
        Key_GamepadFaceRight,   // B           | A      | Circle   | Cancel / Close / Exit
        Key_GamepadFaceUp,      // Y           | X      | Triangle | Open Context Menu
        Key_GamepadFaceDown,    // A           | B      | Cross    | Activate / Open / Toggle. Hold for 0.60f to Activate in Text Input mode (e.g. wired to an on-screen keyboard).
        Key_GamepadDpadLeft,    // D-pad Left  | "      | "        | Move / Tweak / Resize Window (in Windowing mode)
        Key_GamepadDpadRight,   // D-pad Right | "      | "        | Move / Tweak / Resize Window (in Windowing mode)
        Key_GamepadDpadUp,      // D-pad Up    | "      | "        | Move / Tweak / Resize Window (in Windowing mode)
        Key_GamepadDpadDown,    // D-pad Down  | "      | "        | Move / Tweak / Resize Window (in Windowing mode)
        Key_GamepadL1,          // L Bumper    | L      | L1       | Tweak Slower / Focus Previous (in Windowing mode)
        Key_GamepadR1,          // R Bumper    | R      | R1       | Tweak Faster / Focus Next (in Windowing mode)
        Key_GamepadL2,          // L Trigger   | ZL     | L2       | [Analog]
        Key_GamepadR2,          // R Trigger   | ZR     | R2       | [Analog]
        Key_GamepadL3,          // L Stick     | L3     | L3       |
        Key_GamepadR3,          // R Stick     | R3     | R3       |
        Key_GamepadLStickLeft,  //             |        |          | [Analog] Move Window (in Windowing mode)
        Key_GamepadLStickRight, //             |        |          | [Analog] Move Window (in Windowing mode)
        Key_GamepadLStickUp,    //             |        |          | [Analog] Move Window (in Windowing mode)
        Key_GamepadLStickDown,  //             |        |          | [Analog] Move Window (in Windowing mode)
        Key_GamepadRStickLeft,  //             |        |          | [Analog]
        Key_GamepadRStickRight, //             |        |          | [Analog]
        Key_GamepadRStickUp,    //             |        |          | [Analog]
        Key_GamepadRStickDown,  //             |        |          | [Analog]
        // Aliases: Mouse Buttons (auto-submitted from AddMouseButtonEvent() calls)
        // - This is mirroring the data also written to io.MouseDown[], io.MouseWheel, in a format allowing them to be accessed via standard key API.
        Key_MouseLeft, Key_MouseRight, Key_MouseMiddle, Key_MouseX1, Key_MouseX2, Key_MouseWheelX, Key_MouseWheelY,
        // [Internal] Reserved for mod storage
        Key_ReservedForModCtrl, Key_ReservedForModShift, Key_ReservedForModAlt, Key_ReservedForModSuper,
        // [Internal] If you need to iterate all keys (for e.g. an input mapper) you may use uiKey_NamedKey_BEGIN..uiKey_NamedKey_END.
        Key_NamedKey_END,
        Key_NamedKey_COUNT = Key_NamedKey_END - Key_NamedKey_BEGIN,
        // Keyboard Modifiers (explicitly submitted by backend via AddKeyEvent() calls)
        // - Any functions taking a uiKeyChord parameter can binary-or those with regular keys, e.g. Shortcut(uiMod_Ctrl | uiKey_S).
        // - Those are written back into io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper for convenience,
        //   but may be accessed via standard key API such as IsKeyPressed(), IsKeyReleased(), querying duration etc.
        // - Code polling every key (e.g. an interface to detect a key press for input mapping) might want to ignore those
        //   and prefer using the real keys (e.g. uiKey_LeftCtrl, uiKey_RightCtrl instead of uiMod_Ctrl).
        // - In theory the value of keyboard modifiers should be roughly equivalent to a logical or of the equivalent left/right keys.
        //   In practice: it's complicated; mods are often provided from different sources. Keyboard layout, IME, sticky keys and
        //   backends tend to interfere and break that equivalence. The safer decision is to relay that ambiguity down to the end-user...
        // - On macOS, we swap Cmd(Super) and Ctrl keys at the time of the io.AddKeyEvent() call.
        Mode_None  = 0,
        Mode_Ctrl  = 1 << 12,
        Mode_Shift = 1 << 13,
        Mode_Alt   = 1 << 14,
        Mode_Super = 1 << 15,
        Mode_Mask_ = 0xF000, // 4-bits
    };
};
// Those names are provided for debugging purpose and are not meant to be saved persistently nor compared.
static cc8* const INPUT_KeyNames[] = {
    "Tab", "LeftArrow", "RightArrow", "UpArrow", "DownArrow", "PageUp", "PageDown",
    "Home", "End", "Insert", "Del", "Backspace", "Spacebar", "Enter", "Esc",
    "LeftCtrl", "LeftShift", "LeftAlt", "LeftSuper", "RightCtrl", "RightShift", "RightAlt", "RightSuper", "Menu",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H",
    "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
    "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
    "Apostrophe", "Comma", "Minus", "Period", "Slash", "Semicolon", "Equal", "LeftBracket",
    "Backslash", "RightBracket", "GraveAccent", "CapsLock", "ScrollLock", "NumLock", "PrintScreen",
    "Pause", "Keypad0", "Keypad1", "Keypad2", "Keypad3", "Keypad4", "Keypad5", "Keypad6",
    "Keypad7", "Keypad8", "Keypad9", "KeypadDecimal", "KeypadDivide", "KeypadMultiply",
    "KeypadSubtract", "KeypadAdd", "KeypadEnter", "KeypadEqual",
    "AppBack", "AppForward", "Oem102",
    "GamepadStart", "GamepadBack",
    "GamepadFaceLeft", "GamepadFaceRight", "GamepadFaceUp", "GamepadFaceDown",
    "GamepadDpadLeft", "GamepadDpadRight", "GamepadDpadUp", "GamepadDpadDown",
    "GamepadL1", "GamepadR1", "GamepadL2", "GamepadR2", "GamepadL3", "GamepadR3",
    "GamepadLStickLeft", "GamepadLStickRight", "GamepadLStickUp", "GamepadLStickDown",
    "GamepadRStickLeft", "GamepadRStickRight", "GamepadRStickUp", "GamepadRStickDown",
    "MouseLeft", "MouseRight", "MouseMiddle", "MouseX1", "MouseX2", "MouseWheelX", "MouseWheelY",
    "ModCtrl", "ModShift", "ModAlt", "ModSuper", // ReservedForModXXX are showing the ModXXX names.
};
typedef c32 INPUT_KeyChord;
static INPUT_KeyChord GetModForLRModKey(INPUT::Key key) {
    if (key == INPUT::Key_LeftCtrl  || key == INPUT::Key_RightCtrl)  return INPUT::Mode_Ctrl;
    if (key == INPUT::Key_LeftShift || key == INPUT::Key_RightShift) return INPUT::Mode_Shift;
    if (key == INPUT::Key_LeftAlt   || key == INPUT::Key_RightAlt)   return INPUT::Mode_Alt;
    if (key == INPUT::Key_LeftSuper || key == INPUT::Key_RightSuper) return INPUT::Mode_Super;
    return INPUT::Mode_None;
}
inline constexpr INPUT::Flags operator|(INPUT::Flags_ a, INPUT::Flags b) {
    return static_cast<INPUT::Flags>(static_cast<c32>(a) | static_cast<c32>(b));
};
inline constexpr INPUT::Flags operator&(INPUT::Flags_ a, INPUT::Flags b) {
    return static_cast<INPUT::Flags>(static_cast<c32>(a) & static_cast<c32>(b));
};
inline constexpr INPUT::Flags operator~(INPUT::Flags_ a) {
    return static_cast<INPUT::Flags>(~static_cast<c32>(a));
};
inline INPUT::Flags& operator|=(INPUT::Flags& a, INPUT::Flags_ b) {
    return a = a | b;
};
inline INPUT::Flags& operator&=(INPUT::Flags& a, INPUT::Flags_ b) {
    return a = a & b;
};
// key ranges
#define INPUT_LegacyNativeKey_BEGIN 0
#define INPUT_LegacyNativeKey_END   512
#define INPUT_Keyboard_BEGIN        (INPUT::Key_NamedKey_BEGIN)
#define INPUT_Keyboard_END          (INPUT::Key_GamepadStart)
#define INPUT_Gamepad_BEGIN         (INPUT::Key_GamepadStart)
#define INPUT_Gamepad_END           (INPUT::Key_GamepadRStickDown + 1)
#define INPUT_Mouse_BEGIN           (INPUT::Key_MouseLeft)
#define INPUT_Mouse_END             (INPUT::Key_MouseWheelY + 1)
#define INPUT_Aliases_BEGIN         (INPUT_Mouse_BEGIN)
#define INPUT_Aliases_END           (INPUT_Mouse_END)
// navigation shortcuts
#define INPUT_NavKeyboardTweakSlow  INPUT::Mode_Ctrl
#define INPUT_NavKeyboardTweakFast  INPUT::Mode_Shift
#define INPUT_NavGamepadTweakSlow   INPUT::Key_GamepadL1
#define INPUT_NavGamepadTweakFast   INPUT::Key_GamepadR1
#define INPUT_NavGamepadActivate    (g.IO.ConfigNavSwapGamepadButtons ? INPUT::Key_GamepadFaceRight : INPUT::Key_GamepadFaceDown)
#define INPUT_NavGamepadCancel      (g.IO.ConfigNavSwapGamepadButtons ? INPUT::Key_GamepadFaceDown  : INPUT::Key_GamepadFaceRight)
#define INPUT_NavGamepadMenu        INPUT::Key_GamepadFaceLeft // Toggle menu layer. Hold to enable Windowing.
#define INPUT_NavGamepadContextMenu INPUT::Key_GamepadFaceUp   // Open context menu (same as Shift+F10)