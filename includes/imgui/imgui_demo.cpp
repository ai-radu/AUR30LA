// [SECTION] Forward Declarations
// [SECTION] Helpers
// [SECTION] Demo Window / ShowDemoWindow()
// [SECTION] DemoWindowMenuBar()
// [SECTION] Helpers: ExampleTreeNode, ExampleMemberInfo (for use by Property Editor & Multi-Select demos)
// [SECTION] Helpers: ExampleImageViewer
// [SECTION] DemoWindowWidgetsComboBoxes()
// [SECTION] DemoWindowWidgetsColorAndPickers()
// [SECTION] DemoWindowWidgetsDataTypes()
// [SECTION] DemoWindowWidgetsDragAndDrop()
// [SECTION] DemoWindowWidgetsDragsAndSliders()
// [SECTION] DemoWindowWidgetsFonts()
// [SECTION] DemoWindowWidgetsImages()
// [SECTION] DemoWindowWidgetsListBoxes()
// [SECTION] DemoWindowWidgetsMultiComponents()
// [SECTION] DemoWindowWidgetsPlotting()
// [SECTION] DemoWindowWidgetsProgressBars()
// [SECTION] DemoWindowWidgetsQueryingStatuses()
// [SECTION] DemoWindowWidgetsSelectables()
// [SECTION] DemoWindowWidgetsSelectionAndMultiSelect()
// [SECTION] DemoWindowWidgetsTabs()
// [SECTION] DemoWindowWidgetsText()
// [SECTION] DemoWindowWidgetsTextFilter()
// [SECTION] DemoWindowWidgetsTextInput()
// [SECTION] DemoWindowWidgetsTreeNodes()
// [SECTION] DemoWindowWidgetsVerticalSliders()
// [SECTION] DemoWindowWidgets()
// [SECTION] DemoWindowLayout()
// [SECTION] DemoWindowPopups()
// [SECTION] DemoWindowTables()
// [SECTION] DemoWindowInputs()
// [SECTION] About Window / ShowAboutWindow()
// [SECTION] Style Editor / ShowStyleEditor()
// [SECTION] User Guide / ShowUserGuide()
// [SECTION] Example App: Main Menu Bar / ShowExampleAppMainMenuBar()
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
// [SECTION] Example App: Image Viewer / ShowExampleAppImageViewer()
// [SECTION] Example App: Debug Log / ShowExampleAppLog()
// [SECTION] Example App: Simple Layout / ShowExampleAppLayout()
// [SECTION] Example App: Property Editor / ShowExampleAppPropertyEditor()
// [SECTION] Example App: Long Text / ShowExampleAppLongText()
// [SECTION] Example App: Auto Resize / ShowExampleAppAutoResize()
// [SECTION] Example App: Constrained Resize / ShowExampleAppConstrainedResize()
// [SECTION] Example App: Simple overlay / ShowExampleAppSimpleOverlay()
// [SECTION] Example App: Manipulating window titles / ShowExampleAppWindowTitles()
// [SECTION] Example App: Custom Rendering using ImDrawList API / ShowExampleAppCustomRendering()
// [SECTION] Example App: Docking, DockSpace / ShowExampleAppDockSpace()
// [SECTION] Example App: Documents Handling / ShowExampleAppDocuments()
// [SECTION] Example App: Assets Browser / ShowExampleAppAssetsBrowser()
#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "aur.h"
#ifndef IMGUI_DISABLE
// System includes
#include <ctype.h>          // toupper
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#include <stdint.h>         // intptr_t
#if !defined(_MSC_VER) || _MSC_VER >= 1800
#include <inttypes.h>       // PRId64/PRIu64, not avail in some MinGW headers.
#endif
#ifdef __EMSCRIPTEN__
#include <emscripten/version.h>     // __EMSCRIPTEN_MAJOR__ etc.
#endif
// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (disable: 4127)     // condition expression is constant
#pragma warning (disable: 4996)     // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#pragma warning (disable: 26451)    // [Static Analyzer] Arithmetic overflow : Using operator 'xxx' on a 4 byte value and then casting the result to an 8 byte value. Cast the value to the wider type before calling operator 'xxx' to avoid overflow(io.2).
#endif
// Clang/GCC warnings with -Weverything
#if defined(__clang__)
#if __has_warning("-Wunknown-warning-option")
#pragma clang diagnostic ignored "-Wunknown-warning-option"        // warning: unknown warning group 'xxx'                     // not all warnings are known by all Clang versions and they tend to be rename-happy.. so ignoring warnings triggers new warnings on some configuration. Great!
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"               // warning: unknown warning group 'xxx'
#pragma clang diagnostic ignored "-Wold-style-cast"                // warning: use of old-style cast                           // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"       // warning: 'xx' is deprecated: The POSIX name for this..   // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"      // warning: cast to 'void *' from smaller integer type
#pragma clang diagnostic ignored "-Wformat"                        // warning: format specifies type 'int' but the argument has type 'unsigned int'
#pragma clang diagnostic ignored "-Wformat-security"               // warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"         // warning: declaration requires an exit-time destructor    // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#pragma clang diagnostic ignored "-Wunused-macros"                 // warning: macro is not used                               // we define snprintf/vsnprintf on Windows so they are available, but not always used.
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant" // warning: zero as null pointer constant                   // some standard header variations use #define NULL 0
#pragma clang diagnostic ignored "-Wdouble-promotion"              // warning: implicit conversion from 'float' to 'double' when passing argument to function  // using printf() is a misery with this as C++ va_arg ellipsis changes float to double.
#pragma clang diagnostic ignored "-Wreserved-id-macro"             // warning: macro name is a reserved identifier
#pragma clang diagnostic ignored "-Wimplicit-int-float-conversion" // warning: implicit conversion from 'xxx' to 'float' may lose precision
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"           // warning: 'xxx' is an unsafe pointer used for buffer access
#pragma clang diagnostic ignored "-Wswitch-default"                // warning: 'switch' missing 'default' label
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpragmas"                // warning: unknown option after '#pragma GCC diagnostic' kind
#pragma GCC diagnostic ignored "-Wfloat-equal"            // warning: comparing floating-point with '==' or '!=' is unsafe
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"    // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat"                 // warning: format '%p' expects argument of type 'int'/'void*', but argument X has type 'unsigned int'/'uiWindow*'
#pragma GCC diagnostic ignored "-Wformat-security"        // warning: format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"       // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"             // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wmisleading-indentation" // [__GNUC__ >= 6] warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on GitHub.
#pragma GCC diagnostic ignored "-Wstrict-overflow"        // warning: assuming signed overflow does not occur when simplifying division / ..when changing X +- C1 cmp C2 to X cmp C2 -+ C1
#pragma GCC diagnostic ignored "-Wcast-qual"              // warning: cast from type 'const xxxx *' to type 'xxxx *' casts away qualifiers
#endif
// Play it nice with Windows users (Update: May 2018, Notepad now supports Unix-style carriage returns!)
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#else
#define IM_NEWLINE  "\n"
#endif
// Helpers
#if defined(_MSC_VER) && !defined(snprintf)
#define snprintf    _snprintf
#endif
#if defined(_MSC_VER) && !defined(vsnprintf)
#define vsnprintf   _vsnprintf
#endif
// Format specifiers for 64-bit values (hasn't been decently standardized before VS2013)
#if !defined(PRId64) && defined(_MSC_VER)
#define PRId64 "I64d"
#define PRIu64 "I64u"
#elif !defined(PRId64)
#define PRId64 "lld"
#define PRIu64 "llu"
#endif
// Helpers macros
// We normally try to not use many helpers in imgui_demo.cpp in order to make code easier to copy and paste,
// but making an exception here as those are largely simplifying code...
// In other imgui sources we can use nicer internal functions from imgui_internal.h (ImMin/ImMax) but not in the demo.
#define IM_MIN(A, B)        (((A) < (B)) ? (A) : (B))
#define IM_MAX(A, B)        (((A) >= (B)) ? (A) : (B))
#define IM_CLAMP(V, MN, MX) ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))
// Enforce cdecl calling convention for functions called by the standard library,
// in case compilation settings changed the default to e.g. __vectorcall
#ifndef IMGUI_CDECL
#ifdef _MSC_VER
#define IMGUI_CDECL __cdecl
#else
#define IMGUI_CDECL
#endif
#endif
//-----------------------------------------------------------------------------
// [SECTION] Forward Declarations
//-----------------------------------------------------------------------------
#if !defined(IMGUI_DISABLE_DEMO_WINDOWS)
// Forward Declarations
struct uiDemoWindowData;
static void ShowExampleAppMainMenuBar();
static void ShowExampleAppAssetsBrowser(bool* p_open);
static void ShowExampleAppConsole(bool* p_open);
static void ShowExampleAppCustomRendering(bool* p_open);
static void ShowExampleAppDockSpace(bool* p_open);
static void ShowExampleAppDocuments(bool* p_open);
static void ShowExampleAppImageViewer(bool* p_open);
static void ShowExampleAppLog(bool* p_open);
static void ShowExampleAppLayout(bool* p_open);
static void ShowExampleAppPropertyEditor(bool* p_open, uiDemoWindowData* demo_data);
static void ShowExampleAppSimpleOverlay(bool* p_open);
static void ShowExampleAppAutoResize(bool* p_open);
static void ShowExampleAppConstrainedResize(bool* p_open);
static void ShowExampleAppLongText(bool* p_open);
static void ShowExampleAppWindowTitles(bool* p_open);
static void ShowExampleMenuFile();
// We split the contents of the big ShowDemoWindow() function into smaller functions
// (because the link time of very large functions tends to grow non-linearly)
static void DemoWindowMenuBar(uiDemoWindowData* demo_data);
static void DemoWindowWidgets(uiDemoWindowData* demo_data);
static void DemoWindowLayout();
static void DemoWindowPopups();
static void DemoWindowTables();
static void DemoWindowColumns();
static void DemoWindowInputs();
// Helper tree functions used by Property Editor & Multi-Select demos
struct ExampleTreeNode;
static ExampleTreeNode* ExampleTree_CreateNode(const char* name, int uid, ExampleTreeNode* parent);
static void             ExampleTree_DestroyNode(ExampleTreeNode* node);
//-----------------------------------------------------------------------------
// [SECTION] Helpers
//-----------------------------------------------------------------------------
// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(const char* desc) {
    UI::TextDisabled("(?)");
    if (UI::BeginItemTooltip()) {
        UI::PushTextWrapPos(UI::GetFontSize() * 35.0f);
        UI::TextUnformatted(desc);
        UI::PopTextWrapPos();
        UI::EndTooltip();
    }
}
static void ShowDockingDisabledMessage() {
    uiIO& io = UI::GetIO();
    UI::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
    UI::Text("Set io.ConfigFlags |= uiConfigFlags_DockingEnable in your code, or ");
    UI::SameLine(0.0f, 0.0f);
    if (UI::SmallButton("click here")) io.ConfigFlags |= uiConfigFlags_DockingEnable;
}
// Helper to wire demo markers located in code to an interactive browser (e.g. https://pthom.github.io/imgui_explorer)
#if IMGUI_VERSION_NUM >= 19263
namespace UI { extern IMGUI_API void DemoMarker(const char* file, int line, const char* section); }
#define IMGUI_DEMO_MARKER(section)  do { UI::DemoMarker("imgui_demo.cpp", __LINE__, section); } while (0)
#endif
// Sneakily forward declare functions which aren't worth putting in public API yet
namespace UI {
    IMGUI_API void ShowFontAtlas(ImFontAtlas* atlas);
    IMGUI_API void TreeNodeSetOpen(uiID storage_id, bool is_open);
}
//-----------------------------------------------------------------------------
// [SECTION] Demo Window / ShowDemoWindow()
//-----------------------------------------------------------------------------
// Data to be shared across different functions of the demo.
struct uiDemoWindowData {
    // Examples Apps (accessible from the "Examples" menu)
    bool ShowMainMenuBar = false;
    bool ShowAppAssetsBrowser = false;
    bool ShowAppConsole = false;
    bool ShowAppCustomRendering = false;
    bool ShowAppDocuments = false;
    bool ShowAppDockSpace = false;
    bool ShowAppImageViewer = false;
    bool ShowAppLog = false;
    bool ShowAppLayout = false;
    bool ShowAppPropertyEditor = false;
    bool ShowAppSimpleOverlay = false;
    bool ShowAppAutoResize = false;
    bool ShowAppConstrainedResize = false;
    bool ShowAppFullscreen = false;
    bool ShowAppLongText = false;
    bool ShowAppWindowTitles = false;
    // Dear ImGui Tools (accessible from the "Tools" menu)
    bool ShowMetrics = false;
    bool ShowDebugLog = false;
    bool ShowIDStackTool = false;
    bool ShowStyleEditor = false;
    bool ShowAbout = false;
    // Other data
    bool DisableSections = false;
    ExampleTreeNode* DemoTree = NULL;
    ~uiDemoWindowData() { if (DemoTree) ExampleTree_DestroyNode(DemoTree); }
};
// Demonstrate most Dear ImGui features (this is big function!)
// You may execute this function to experiment with the UI and understand what it does.
// You may then search for keywords in the code when you are interested by a specific feature.
void UI::ShowDemoWindow(bool* p_open) {
    // Exceptionally add an extra assert here for people confused about initial Dear ImGui setup
    // Most functions would normally just assert/crash if the context is missing.
    IM_ASSERT(UI::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");
    // Verify ABI compatibility between caller code and compiled version of Dear ImGui. This helps detects some build issues.
    IMGUI_CHECKVERSION();
    // Stored data
    static uiDemoWindowData demo_data;
    // Examples Apps (accessible from the "Examples" menu)
    if (demo_data.ShowMainMenuBar)          { ShowExampleAppMainMenuBar(); }
    if (demo_data.ShowAppDockSpace)         { ShowExampleAppDockSpace(&demo_data.ShowAppDockSpace); } // Important: Process the Docking app first, as explicit DockSpace() nodes needs to be submitted early (read comments near the DockSpace function)
    if (demo_data.ShowAppDocuments)         { ShowExampleAppDocuments(&demo_data.ShowAppDocuments); } // ...process the Document app next, as it may also use a DockSpace()
    if (demo_data.ShowAppAssetsBrowser)     { ShowExampleAppAssetsBrowser(&demo_data.ShowAppAssetsBrowser); }
    if (demo_data.ShowAppConsole)           { ShowExampleAppConsole(&demo_data.ShowAppConsole); }
    if (demo_data.ShowAppCustomRendering)   { ShowExampleAppCustomRendering(&demo_data.ShowAppCustomRendering); }
    if (demo_data.ShowAppImageViewer)       { ShowExampleAppImageViewer(&demo_data.ShowAppImageViewer); }
    if (demo_data.ShowAppLog)               { ShowExampleAppLog(&demo_data.ShowAppLog); }
    if (demo_data.ShowAppLayout)            { ShowExampleAppLayout(&demo_data.ShowAppLayout); }
    if (demo_data.ShowAppPropertyEditor)    { ShowExampleAppPropertyEditor(&demo_data.ShowAppPropertyEditor, &demo_data); }
    if (demo_data.ShowAppSimpleOverlay)     { ShowExampleAppSimpleOverlay(&demo_data.ShowAppSimpleOverlay); }
    if (demo_data.ShowAppAutoResize)        { ShowExampleAppAutoResize(&demo_data.ShowAppAutoResize); }
    if (demo_data.ShowAppConstrainedResize) { ShowExampleAppConstrainedResize(&demo_data.ShowAppConstrainedResize); }
    if (demo_data.ShowAppLongText)          { ShowExampleAppLongText(&demo_data.ShowAppLongText); }
    if (demo_data.ShowAppWindowTitles)      { ShowExampleAppWindowTitles(&demo_data.ShowAppWindowTitles); }
    // Dear ImGui Tools (accessible from the "Tools" menu)
    if (demo_data.ShowMetrics)              { UI::ShowMetricsWindow(&demo_data.ShowMetrics); }
    if (demo_data.ShowDebugLog)             { UI::ShowDebugLogWindow(&demo_data.ShowDebugLog); }
    if (demo_data.ShowIDStackTool)          { UI::ShowIDStackToolWindow(&demo_data.ShowIDStackTool); }
    if (demo_data.ShowAbout)                { UI::ShowAboutWindow(&demo_data.ShowAbout); }
    if (demo_data.ShowStyleEditor) {
        UI::Begin("Dear ImGui Style Editor", &demo_data.ShowStyleEditor);
        UI::ShowStyleEditor();
        UI::End();
    }
    // We specify a default position/size in case there's no data in the .ini file.
    // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
    const uiViewport* main_viewport = UI::GetMainViewport();
    UI::SetNextWindowPos(vec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), uiCond_FirstUseEver);
    UI::SetNextWindowSize(vec2(550, 680), uiCond_FirstUseEver);

    // Main body of the Demo window starts here.
    if (!UI::Begin("Dear ImGui Demo", p_open))
    {
        // Early out if the window is collapsed, as an optimization.
        UI::End();
        return;
    }

    // Most framed widgets share a common width settings. Remaining width is used for the label.
    // The width of the frame may be changed with PushItemWidth() or SetNextItemWidth().
    // - Positive value for absolute size, negative value for right-alignment.
    // - The default value is about GetWindowWidth() * 0.65f.
    // - See 'Demo->Layout->Widgets Width' for details.
    // Here we change the frame width based on how much width we want to give to the label.
    const float label_width_base = UI::GetFontSize() * 12;               // Some amount of width for label, based on font size.
    const float label_width_max = UI::GetContentRegionAvail().x * 0.40f; // ...but always leave some room for framed widgets.
    const float label_width = IM_MIN(label_width_base, label_width_max);
    UI::PushItemWidth(-label_width);                                     // Right-align: framed items will leave 'label_width' available for the label.
    //UI::PushItemWidth(UI::GetContentRegionAvail().x * 0.40f);       // e.g. Use 40% width for framed widgets, leaving 60% width for labels.
    //UI::PushItemWidth(-UI::GetContentRegionAvail().x * 0.40f);      // e.g. Use 40% width for labels, leaving 60% width for framed widgets.
    //UI::PushItemWidth(UI::GetFontSize() * -12);                     // e.g. Use XXX width for labels, leaving the rest for framed widgets.

    // Menu Bar
    DemoWindowMenuBar(&demo_data);

    UI::Text("(%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    UI::Spacing();

    if (UI::CollapsingHeader("Configuration"))
    {
        uiIO& io = UI::GetIO();

        if (UI::TreeNode("Configuration##2"))
        {
            IMGUI_DEMO_MARKER("Configuration");
            UI::BarrierText("General");
            UI::CheckboxFlags("io.ConfigFlags: NavEnableKeyboard",    &io.ConfigFlags, uiConfigFlags_NavEnableKeyboard);
            UI::SameLine(); HelpMarker("Enable keyboard controls.");
            UI::CheckboxFlags("io.ConfigFlags: NavEnableGamepad",     &io.ConfigFlags, uiConfigFlags_NavEnableGamepad);
            UI::SameLine(); HelpMarker("Enable gamepad controls. Require backend to set io.BackendFlags |= uiBackendFlags_HasGamepad.\n\nRead instructions in imgui.cpp for details.");
            UI::CheckboxFlags("io.ConfigFlags: NoMouse",              &io.ConfigFlags, uiConfigFlags_NoMouse);
            UI::SameLine(); HelpMarker("Instruct dear imgui to disable mouse inputs and interactions.");

            // The "NoMouse" option can get us stuck with a disabled mouse! Let's provide an alternative way to fix it:
            if (io.ConfigFlags & uiConfigFlags_NoMouse)
            {
                if (fmodf((float)UI::GetTime(), 0.40f) < 0.20f)
                {
                    UI::SameLine();
                    UI::Text("<<PRESS SPACE TO DISABLE>>");
                }
                // Prevent both being checked
                if (UI::IsKeyPressed(uiKey_Space) || (io.ConfigFlags & uiConfigFlags_NoKeyboard))
                    io.ConfigFlags &= ~uiConfigFlags_NoMouse;
            }

            UI::CheckboxFlags("io.ConfigFlags: NoMouseCursorChange",  &io.ConfigFlags, uiConfigFlags_NoMouseCursorChange);
            UI::SameLine(); HelpMarker("Instruct backend to not alter mouse cursor shape and visibility.");
            UI::CheckboxFlags("io.ConfigFlags: NoKeyboard", &io.ConfigFlags, uiConfigFlags_NoKeyboard);
            UI::SameLine(); HelpMarker("Instruct dear imgui to disable keyboard inputs and interactions.");

            UI::Checkbox("io.ConfigInputTrickleEventQueue", &io.ConfigInputTrickleEventQueue);
            UI::SameLine(); HelpMarker("Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up) will be spread over multiple frames, improving interactions with low framerates.");
            UI::Checkbox("io.MouseDrawCursor", &io.MouseDrawCursor);
            UI::SameLine(); HelpMarker("Instruct Dear ImGui to render a mouse cursor itself. Note that a mouse cursor rendered via your application GPU rendering path will feel more laggy than hardware cursor, but will be more in sync with your other visuals.\n\nSome desktop applications may use both kinds of cursors (e.g. enable software cursor only when resizing/dragging something).");

            UI::BarrierText("Keyboard/Gamepad Navigation");
            UI::Checkbox("io.ConfigNavSwapGamepadButtons", &io.ConfigNavSwapGamepadButtons);
            UI::Checkbox("io.ConfigNavMoveSetMousePos", &io.ConfigNavMoveSetMousePos);
            UI::SameLine(); HelpMarker("Directional/tabbing navigation teleports the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is difficult");
            UI::Checkbox("io.ConfigNavCaptureKeyboard", &io.ConfigNavCaptureKeyboard);
            UI::Checkbox("io.ConfigNavEscapeClearFocusItem", &io.ConfigNavEscapeClearFocusItem);
            UI::SameLine(); HelpMarker("Pressing Escape clears focused item.");
            UI::Checkbox("io.ConfigNavEscapeClearFocusWindow", &io.ConfigNavEscapeClearFocusWindow);
            UI::SameLine(); HelpMarker("Pressing Escape clears focused window.");
            UI::Checkbox("io.ConfigNavCursorVisibleAuto", &io.ConfigNavCursorVisibleAuto);
            UI::SameLine(); HelpMarker("Using directional navigation key makes the cursor visible. Mouse click hides the cursor.");
            UI::Checkbox("io.ConfigNavCursorVisibleAlways", &io.ConfigNavCursorVisibleAlways);
            UI::SameLine(); HelpMarker("Navigation cursor is always visible.");

            UI::BarrierText("Docking");
            UI::CheckboxFlags("io.ConfigFlags: DockingEnable", &io.ConfigFlags, uiConfigFlags_DockingEnable);
            UI::SameLine();
            if (io.ConfigDockingWithShift)
                HelpMarker("Drag from window title bar or their tab to dock/undock. Hold SHIFT to enable docking.\n\nDrag from window menu button (upper-left button) to undock an entire node (all windows).");
            else
                HelpMarker("Drag from window title bar or their tab to dock/undock. Hold SHIFT to disable docking.\n\nDrag from window menu button (upper-left button) to undock an entire node (all windows).");
            if (io.ConfigFlags & uiConfigFlags_DockingEnable)
            {
                UI::Indent();
                UI::Checkbox("io.ConfigDockingNoSplit", &io.ConfigDockingNoSplit);
                UI::SameLine(); HelpMarker("Simplified docking mode: disable window splitting, so docking is limited to merging multiple windows together into tab-bars.");
                UI::Checkbox("io.ConfigDockingNoDockingOver", &io.ConfigDockingNoDockingOver);
                UI::SameLine(); HelpMarker("Simplified docking mode: disable window merging into a same tab-bar, so docking is limited to splitting windows.");
                UI::Checkbox("io.ConfigDockingWithShift", &io.ConfigDockingWithShift);
                UI::SameLine(); HelpMarker("Enable docking when holding Shift only (allow to drop in wider space, reduce visual noise)");
                UI::Checkbox("io.ConfigDockingAlwaysTabBar", &io.ConfigDockingAlwaysTabBar);
                UI::SameLine(); HelpMarker("Create a docking node and tab-bar on single floating windows.");
                UI::Checkbox("io.ConfigDockingTransparentPayload", &io.ConfigDockingTransparentPayload);
                UI::SameLine(); HelpMarker("Make window or viewport transparent when docking and only display docking boxes on the target viewport. Useful if rendering of multiple viewport cannot be synced. Best used with ConfigViewportsNoAutoMerge.");
                UI::Unindent();
            }

            UI::BarrierText("Multi-viewports");
            UI::CheckboxFlags("io.ConfigFlags: ViewportsEnable", &io.ConfigFlags, uiConfigFlags_ViewportsEnable);
            UI::SameLine(); HelpMarker("[beta] Enable beta multi-viewports support. See uiPlatformIO for details.");
            if (io.ConfigFlags & uiConfigFlags_ViewportsEnable)
            {
                UI::Indent();
                UI::Checkbox("io.ConfigViewportsNoAutoMerge", &io.ConfigViewportsNoAutoMerge);
                UI::SameLine(); HelpMarker("Set to make all floating imgui windows always create their own viewport. Otherwise, they are merged into the main host viewports when overlapping it.");
                UI::Checkbox("io.ConfigViewportsNoTaskBarIcon", &io.ConfigViewportsNoTaskBarIcon);
                UI::SameLine(); HelpMarker("(note: some platform backends may not reflect a change of this value for existing viewports, and may need the viewport to be recreated)");
                UI::Checkbox("io.ConfigViewportsNoDecoration", &io.ConfigViewportsNoDecoration);
                UI::SameLine(); HelpMarker("(note: some platform backends may not reflect a change of this value for existing viewports, and may need the viewport to be recreated)");
                UI::Checkbox("io.ConfigViewportsNoDefaultParent", &io.ConfigViewportsNoDefaultParent);
                UI::SameLine(); HelpMarker("(note: some platform backends may not reflect a change of this value for existing viewports, and may need the viewport to be recreated)");
                UI::Checkbox("io.ConfigViewportsPlatformFocusSetsuiFocus", &io.ConfigViewportsPlatformFocusSetsuiFocus);
                UI::SameLine(); HelpMarker("When a platform window is focused (e.g. using Alt+Tab, clicking Platform Title Bar), apply corresponding focus on imgui windows (may clear focus/active id from imgui windows location in other platform windows). In principle this is better enabled but we provide an opt-out, because some Linux window managers tend to eagerly focus windows (e.g. on mouse hover, or even a simple window pos/size change).");
                UI::Unindent();
            }

            //UI::BarrierText("DPI/Scaling");
            //UI::Checkbox("io.ConfigDpiScaleFonts", &io.ConfigDpiScaleFonts);
            //UI::SameLine(); HelpMarker("Experimental: Automatically update style.FontScaleDpi when Monitor DPI changes. This will scale fonts but NOT style sizes/padding for now.");
            //UI::Checkbox("io.ConfigDpiScaleViewports", &io.ConfigDpiScaleViewports);
            //UI::SameLine(); HelpMarker("Experimental: Scale Dear ImGui and Platform Windows when Monitor DPI changes.");

            UI::BarrierText("Windows");
            UI::Checkbox("io.ConfigWindowsResizeFromEdges", &io.ConfigWindowsResizeFromEdges);
            UI::SameLine(); HelpMarker("Enable resizing of windows from their edges and from the lower-left corner.\nThis requires uiBackendFlags_HasMouseCursors for better mouse cursor feedback.");
            UI::Checkbox("io.ConfigWindowsMoveFromTitleBarOnly", &io.ConfigWindowsMoveFromTitleBarOnly);
            UI::Checkbox("io.ConfigWindowsCopyContentsWithCtrlC", &io.ConfigWindowsCopyContentsWithCtrlC); // [EXPERIMENTAL]
            UI::SameLine(); HelpMarker("*EXPERIMENTAL* Ctrl+C copy the contents of focused window into the clipboard.\n\nExperimental because:\n- (1) has known issues with nested Begin/End pairs.\n- (2) text output quality varies.\n- (3) text output is in submission order rather than spatial order.");
            UI::Checkbox("io.ConfigScrollbarScrollByPage", &io.ConfigScrollbarScrollByPage);
            UI::SameLine(); HelpMarker("Enable scrolling page by page when clicking outside the scrollbar grab.\nWhen disabled, always scroll to clicked location.\nWhen enabled, Shift+Click scrolls to clicked location.");

            UI::BarrierText("Widgets");
            UI::Checkbox("io.ConfigInputTextCursorBlink", &io.ConfigInputTextCursorBlink);
            UI::SameLine(); HelpMarker("Enable blinking cursor (optional as some users consider it to be distracting).");
            UI::Checkbox("io.ConfigInputTextEnterKeepActive", &io.ConfigInputTextEnterKeepActive);
            UI::SameLine(); HelpMarker("Pressing Enter will reactivate item and select all text (single-line only).");
            UI::Checkbox("io.ConfigDragClickToInputText", &io.ConfigDragClickToInputText);
            UI::SameLine(); HelpMarker("Enable turning DragXXX widgets into text input with a simple mouse click-release (without moving).");
            UI::Checkbox("io.ConfigMacOSXBehaviors", &io.ConfigMacOSXBehaviors);
            UI::SameLine(); HelpMarker("Swap Cmd<>Ctrl keys, enable various MacOS style behaviors.");
            UI::Text("Also see Style->Rendering for rendering options.");

            // Also read: https://github.com/ocornut/imgui/wiki/Error-Handling
            UI::BarrierText("Error Handling");

            UI::Checkbox("io.ConfigErrorRecovery", &io.ConfigErrorRecovery);
            UI::SameLine(); HelpMarker(
                "Options to configure how we handle recoverable errors.\n"
                "- Error recovery is not perfect nor guaranteed! It is a feature to ease development.\n"
                "- You not are not supposed to rely on it in the course of a normal application run.\n"
                "- Possible usage: facilitate recovery from errors triggered from a scripting language or after specific exceptions handlers.\n"
                "- Always ensure that on programmers seat you have at minimum Asserts or Tooltips enabled when making direct imgui API call! "
                "Otherwise it would severely hinder your ability to catch and correct mistakes!");
            UI::Checkbox("io.ConfigErrorRecoveryEnableAssert", &io.ConfigErrorRecoveryEnableAssert);
            UI::Checkbox("io.ConfigErrorRecoveryEnableDebugLog", &io.ConfigErrorRecoveryEnableDebugLog);
            UI::Checkbox("io.ConfigErrorRecoveryEnableTooltip", &io.ConfigErrorRecoveryEnableTooltip);
            if (!io.ConfigErrorRecoveryEnableAssert && !io.ConfigErrorRecoveryEnableDebugLog && !io.ConfigErrorRecoveryEnableTooltip)
                io.ConfigErrorRecoveryEnableAssert = io.ConfigErrorRecoveryEnableDebugLog = io.ConfigErrorRecoveryEnableTooltip = true;

            // Also read: https://github.com/ocornut/imgui/wiki/Debug-Tools
            UI::BarrierText("Debug");
            UI::Checkbox("io.ConfigDebugIsDebuggerPresent", &io.ConfigDebugIsDebuggerPresent);
            UI::SameLine(); HelpMarker("Enable various tools calling IM_DEBUG_BREAK().\n\nRequires a debugger being attached, otherwise IM_DEBUG_BREAK() options will appear to crash your application.");
            UI::Checkbox("io.ConfigDebugHighlightIdConflicts", &io.ConfigDebugHighlightIdConflicts);
            UI::SameLine(); HelpMarker("Highlight and show an error message when multiple items have conflicting identifiers.");
            UI::BeginDisabled();
            UI::Checkbox("io.ConfigDebugBeginReturnValueOnce", &io.ConfigDebugBeginReturnValueOnce);
            UI::EndDisabled();
            UI::SameLine(); HelpMarker("First calls to Begin()/BeginChild() will return false.\n\nTHIS OPTION IS DISABLED because it needs to be set at application boot-time to make sense. Showing the disabled option is a way to make this feature easier to discover.");
            UI::Checkbox("io.ConfigDebugBeginReturnValueLoop", &io.ConfigDebugBeginReturnValueLoop);
            UI::SameLine(); HelpMarker("Some calls to Begin()/BeginChild() will return false.\n\nWill cycle through window depths then repeat. Windows should be flickering while running.");
            UI::Checkbox("io.ConfigDebugIgnoreFocusLoss", &io.ConfigDebugIgnoreFocusLoss);
            UI::SameLine(); HelpMarker("Option to deactivate io.AddFocusEvent(false) handling. May facilitate interactions with a debugger when focus loss leads to clearing inputs data.");
            UI::Checkbox("io.ConfigDebugIniSettings", &io.ConfigDebugIniSettings);
            UI::SameLine(); HelpMarker("Option to save .ini data with extra comments (particularly helpful for Docking, but makes saving slower).");

            UI::TreePop();
            UI::Spacing();
        }

        if (UI::TreeNode("Backend Flags"))
        {
            IMGUI_DEMO_MARKER("Configuration/Backend Flags");
            HelpMarker(
                "Those flags are set by the backends (imgui_impl_xxx files) to specify their capabilities.\n"
                "Here we expose them as read-only fields to avoid breaking interactions with your backend.");

            // Make a local copy to avoid modifying actual backend flags.
            // FIXME: Maybe we need a BeginReadonly() equivalent to keep label bright?
            UI::BeginDisabled();
            UI::CheckboxFlags("io.BackendFlags: HasGamepad",             &io.BackendFlags, uiBackendFlags_HasGamepad);
            UI::CheckboxFlags("io.BackendFlags: HasMouseCursors",        &io.BackendFlags, uiBackendFlags_HasMouseCursors);
            UI::CheckboxFlags("io.BackendFlags: HasSetMousePos",         &io.BackendFlags, uiBackendFlags_HasSetMousePos);
            UI::CheckboxFlags("io.BackendFlags: PlatformHasViewports",   &io.BackendFlags, uiBackendFlags_PlatformHasViewports);
            UI::CheckboxFlags("io.BackendFlags: HasMouseHoveredViewport",&io.BackendFlags, uiBackendFlags_HasMouseHoveredViewport);
            UI::CheckboxFlags("io.BackendFlags: HasParentViewport",      &io.BackendFlags, uiBackendFlags_HasParentViewport);
            UI::CheckboxFlags("io.BackendFlags: RendererHasVtxOffset",   &io.BackendFlags, uiBackendFlags_RendererHasVtxOffset);
            UI::CheckboxFlags("io.BackendFlags: RendererHasTextures",    &io.BackendFlags, uiBackendFlags_RendererHasTextures);
            UI::CheckboxFlags("io.BackendFlags: RendererHasViewports",   &io.BackendFlags, uiBackendFlags_RendererHasViewports);
            UI::EndDisabled();

            UI::TreePop();
            UI::Spacing();
        }

        if (UI::TreeNode("Style, Fonts"))
        {
            IMGUI_DEMO_MARKER("Configuration/Style, Fonts");
            UI::Checkbox("Style Editor", &demo_data.ShowStyleEditor);
            UI::SameLine();
            HelpMarker("The same contents can be accessed in 'Tools->Style Editor' or by calling the ShowStyleEditor() function.");
            UI::TreePop();
            UI::Spacing();
        }

        if (UI::TreeNode("Capture/Logging"))
        {
            IMGUI_DEMO_MARKER("Configuration/Capture, Logging");
            HelpMarker(
                "The logging API redirects all text output so you can easily capture the content of "
                "a window or a block. Tree nodes can be automatically expanded.\n"
                "Try opening any of the contents below in this window and then click one of the \"Log To\" button.");
            UI::LogButtons();

            HelpMarker("You can also call UI::LogText() to output directly to the log without a visual output.");
            if (UI::Button("Copy \"Hello, world!\" to clipboard"))
            {
                UI::LogToClipboard();
                UI::LogText("Hello, world!");
                UI::LogFinish();
            }
            UI::TreePop();
        }
    }
    // All demo contents
    DemoWindowWidgets(&demo_data);
    DemoWindowLayout();
    DemoWindowPopups();
    DemoWindowTables();
    DemoWindowInputs();
    // End of ShowDemoWindow()
    UI::PopItemWidth();
    UI::End();
}
//-----------------------------------------------------------------------------
// [SECTION] DemoWindowMenuBar()
//-----------------------------------------------------------------------------

static void DemoWindowMenuBar(uiDemoWindowData* demo_data)
{
    if (UI::BeginMenuBar())
    {
        if (UI::BeginMenu("Menu"))
        {
            IMGUI_DEMO_MARKER("Menu/File");
            ShowExampleMenuFile();
            UI::EndMenu();
        }
        if (UI::BeginMenu("Examples"))
        {
            IMGUI_DEMO_MARKER("Menu/Examples");
            UI::MenuItem("Main menu bar", NULL, &demo_data->ShowMainMenuBar);

            UI::BarrierText("Mini apps");
            UI::MenuItem("Assets Browser", NULL, &demo_data->ShowAppAssetsBrowser);
            UI::MenuItem("Console", NULL, &demo_data->ShowAppConsole);
            UI::MenuItem("Custom rendering", NULL, &demo_data->ShowAppCustomRendering);
            UI::MenuItem("Documents", NULL, &demo_data->ShowAppDocuments);
            UI::MenuItem("Dockspace", NULL, &demo_data->ShowAppDockSpace);
            UI::MenuItem("Image Viewer", NULL, &demo_data->ShowAppImageViewer);
            UI::MenuItem("Log", NULL, &demo_data->ShowAppLog);
            UI::MenuItem("Property editor", NULL, &demo_data->ShowAppPropertyEditor);
            UI::MenuItem("Simple layout", NULL, &demo_data->ShowAppLayout);
            UI::MenuItem("Simple overlay", NULL, &demo_data->ShowAppSimpleOverlay);

            UI::BarrierText("Concepts");
            UI::MenuItem("Auto-resizing window", NULL, &demo_data->ShowAppAutoResize);
            UI::MenuItem("Constrained-resizing window", NULL, &demo_data->ShowAppConstrainedResize);
            UI::MenuItem("Fullscreen window", NULL, &demo_data->ShowAppFullscreen);
            UI::MenuItem("Long text display", NULL, &demo_data->ShowAppLongText);
            UI::MenuItem("Manipulating window titles", NULL, &demo_data->ShowAppWindowTitles);

            UI::EndMenu();
        }
        if (UI::BeginMenu("Tools"))
        {
            IMGUI_DEMO_MARKER("Menu/Tools");
            uiIO& io = UI::GetIO();
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
            const bool has_debug_tools = true;
#else
            const bool has_debug_tools = false;
#endif
            UI::MenuItem("Metrics/Debugger", NULL, &demo_data->ShowMetrics, has_debug_tools);
            if (UI::BeginMenu("Debug Options"))
            {
                UI::BeginDisabled(!has_debug_tools);
                UI::Checkbox("Highlight ID Conflicts", &io.ConfigDebugHighlightIdConflicts);
                UI::EndDisabled();
                UI::Checkbox("Assert on error recovery", &io.ConfigErrorRecoveryEnableAssert);
                UI::TextDisabled("(see Demo->Configuration for more)");
                UI::EndMenu();
            }
            UI::MenuItem("Debug Log", NULL, &demo_data->ShowDebugLog, has_debug_tools);
            UI::MenuItem("ID Stack Tool", NULL, &demo_data->ShowIDStackTool, has_debug_tools);
            bool is_debugger_present = io.ConfigDebugIsDebuggerPresent;
            if (UI::MenuItem("Item Picker", NULL, false, has_debug_tools))// && is_debugger_present))
                UI::DebugStartItemPicker();
            if (!is_debugger_present)
                UI::SetItemTooltip("Requires io.ConfigDebugIsDebuggerPresent=true to be set.\n\nWe otherwise disable some extra features to avoid casual users crashing the application.");
            UI::MenuItem("Style Editor", NULL, &demo_data->ShowStyleEditor);
            UI::MenuItem("About Dear ImGui", NULL, &demo_data->ShowAbout);

            UI::EndMenu();
        }
        UI::EndMenuBar();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] Helpers: ExampleTreeNode, ExampleMemberInfo (for use by Property Editor & Multi-Select demos)
//-----------------------------------------------------------------------------

// Simple representation for a tree
// (this is designed to be simple to understand for our demos, not to be fancy or efficient etc.)
struct ExampleTreeNode
{
    // Tree structure
    char                        Name[28] = "";
    int                         UID = 0;
    ExampleTreeNode*            Parent = NULL;
    ImVector<ExampleTreeNode*>  Childs;
    int                         IndexInParent = 0;  // Maintaining this allows us to implement linear traversal more easily

    // Leaf Data
    bool                        HasData = false;    // All leaves have data
    bool                        DataMyBool = true;
    int                         DataMyInt = 128;
    vec2                        DataMyVec2 = vec2(0.0f, 3.141592f);
};

// Simple representation of struct metadata/serialization data.
// (this is a minimal version of what a typical advanced application may provide)
struct ExampleMemberInfo
{
    const char*     Name;       // Member name
    uiDataType   DataType;   // Member type
    int             DataCount;  // Member count (1 when scalar)
    int             Offset;     // Offset inside parent structure
};

// Metadata description of ExampleTreeNode struct.
static const ExampleMemberInfo ExampleTreeNodeMemberInfos[]
{
    { "MyName",     uiDataType_String,  1, offsetof(ExampleTreeNode, Name) },
    { "MyBool",     uiDataType_Bool,    1, offsetof(ExampleTreeNode, DataMyBool) },
    { "MyInt",      uiDataType_S32,     1, offsetof(ExampleTreeNode, DataMyInt) },
    { "MyVec2",     uiDataType_Float,   2, offsetof(ExampleTreeNode, DataMyVec2) },
};

static ExampleTreeNode* ExampleTree_CreateNode(const char* name, int uid, ExampleTreeNode* parent)
{
    ExampleTreeNode* node = IM_NEW(ExampleTreeNode);
    snprintf(node->Name, IM_COUNTOF(node->Name), "%s", name);
    node->UID = uid;
    node->Parent = parent;
    node->IndexInParent = parent ? parent->Childs.Size : 0;
    if (parent)
        parent->Childs.push_back(node);
    return node;
}

static void ExampleTree_DestroyNode(ExampleTreeNode* node)
{
    for (ExampleTreeNode* child_node : node->Childs)
        ExampleTree_DestroyNode(child_node);
    IM_DELETE(node);
}

// Create example tree data
// (warning: this can allocates MANY MANY more times than other code in all of Dear ImGui + demo combined)
// (a real application managing one million nodes would likely store its tree data differently)
static ExampleTreeNode* ExampleTree_CreateDemoTree()
{
    //     20 root nodes ->    211 total nodes,   ~261 allocs.
    //   1000 root nodes ->   ~11K total nodes,   ~14K allocs.
    //  10000 root nodes ->  ~123K total nodes,  ~154K allocs.
    // 100000 root nodes -> ~1338K total nodes, ~1666K allocs.
    const int ROOT_ITEMS_COUNT = 20;

    static const char* category_names[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pear", "Pineapple", "Strawberry", "Watermelon" };
    const int category_count = IM_COUNTOF(category_names);
    const size_t NAME_MAX_LEN = sizeof(ExampleTreeNode::Name);
    char name_buf[NAME_MAX_LEN];
    int uid = 0;
    ExampleTreeNode* node_L0 = ExampleTree_CreateNode("<ROOT>", ++uid, NULL);
    for (int idx_L0 = 0; idx_L0 < ROOT_ITEMS_COUNT; idx_L0++)
    {
        snprintf(name_buf, IM_COUNTOF(name_buf), "%s %d", category_names[idx_L0 / (ROOT_ITEMS_COUNT / category_count)], idx_L0 % (ROOT_ITEMS_COUNT / category_count));
        ExampleTreeNode* node_L1 = ExampleTree_CreateNode(name_buf, ++uid, node_L0);
        const int number_of_childs = (int)strlen(node_L1->Name);
        for (int idx_L1 = 0; idx_L1 < number_of_childs; idx_L1++)
        {
            snprintf(name_buf, IM_COUNTOF(name_buf), "Child %d", idx_L1);
            ExampleTreeNode* node_L2 = ExampleTree_CreateNode(name_buf, ++uid, node_L1);
            node_L2->HasData = true;
            if (idx_L1 == 0)
            {
                snprintf(name_buf, IM_COUNTOF(name_buf), "Sub-child %d", 0);
                ExampleTreeNode* node_L3 = ExampleTree_CreateNode(name_buf, ++uid, node_L2);
                node_L3->HasData = true;
            }
        }
    }
    return node_L0;
}

//-----------------------------------------------------------------------------
// [SECTION] Helpers: ExampleImageViewer
//-----------------------------------------------------------------------------
struct ExampleImageViewerData {
    ImU32 ImageBgColor = IM_COL32(100, 100, 100, 255);
    ImU32 GridColor = IM_COL32(255, 255, 255, 100);
    bool  GridEnabled = true;
    bool  ViewReset = true;
    vec2  ViewOffset; // in image space
    float Zoom = 10.0f;
    float ZoomMin = 1.0f;
    float ZoomMax = 10000.0f;
};
static void ExampleImageViewer_DrawOptions(ExampleImageViewerData* data) {
    UI::SetNextItemShortcut(uiKey_G, uiInputFlags_Tooltip); // | uiInputFlags_RouteGlobal
    UI::Checkbox("Grid", &data->GridEnabled);
    UI::SameLine();
    UI::SetNextItemWidth(UI::GetFontSize() * 10.0f);
    float zoom_100 = data->Zoom * 100.0f;
    if (UI::DragFloat("##Zoom", &zoom_100, 5.0f, data->ZoomMin * 100.0f, data->ZoomMax * 100.0f, "%.0f%%", uiSliderFlags_AlwaysClamp))
        data->Zoom = zoom_100 / 100.0f;
}
static void ExampleImageViewer_DrawCanvas(ExampleImageViewerData* data, vec2 canvas_size, ImTextureRef image_tex_ref, int image_w, int image_h) {
    uiIO& io = UI::GetIO();
    uiPlatformIO& platform_io = UI::GetPlatformIO();
    ImDrawList* draw_list = UI::GetWindowDrawList();
    IM_ASSERT(canvas_size.x >= 0.0f && canvas_size.y >= 0.0f);
    // Layout canvas
    UI::InvisibleButton("##Canvas", canvas_size);
    vec2 canvas_min = UI::GetItemRectMin();
    vec2 canvas_max = UI::GetItemRectMax();
    if (data->ViewReset)
        data->ViewOffset = vec2((canvas_size.x * 0.5f / data->Zoom) - 0.5f, (canvas_size.y * 0.5f / data->Zoom) - 0.5f); // Add half a pixel padding
    data->ViewReset = false;
    // Handle inputs
    if (UI::SetItemKeyOwner(uiKey_MouseWheelY))
        if (io.MouseWheel != 0.0f)
            data->Zoom = IM_CLAMP(data->Zoom * (1.0f + io.MouseWheel * 0.10f), data->ZoomMin, data->ZoomMax);
    float zoom = data->Zoom; // (float)(int)ViewZoom;
    if (UI::IsItemActive() && UI::IsMouseDragging(0)) {
        data->ViewOffset.x -= io.MouseDelta.x / zoom;
        data->ViewOffset.y -= io.MouseDelta.y / zoom;
    }
    // Display image
    vec2 image_min, image_max;
    image_min.x = (float)(int)((canvas_min.x - (data->ViewOffset.x * zoom)) + (canvas_size.x * 0.5f));
    image_min.y = (float)(int)((canvas_min.y - (data->ViewOffset.y * zoom)) + (canvas_size.y * 0.5f));
    image_max.x = (float)(int)(image_min.x + image_w * zoom);
    image_max.y = (float)(int)(image_min.y + image_h * zoom);
    draw_list->AddRect(vec2(canvas_min.x - 1.0f, canvas_min.y - 1.0f), vec2(canvas_max.x + 1.0f, canvas_max.y + 1.0f), IM_COL32(255, 255, 255, 255));
    draw_list->PushClipRect(canvas_min, canvas_max, true);
    draw_list->AddRectFilled(image_min, image_max, data->ImageBgColor);
    if (platform_io.DrawCallback_SetSamplerNearest != NULL)
        draw_list->AddCallback(platform_io.DrawCallback_SetSamplerNearest);
    draw_list->AddImage(image_tex_ref, image_min, image_max);
    if (platform_io.DrawCallback_SetSamplerLinear != NULL)
        draw_list->AddCallback(UI::GetPlatformIO().DrawCallback_SetSamplerLinear);
    // Display grid lines for visible pixels
    if (data->GridEnabled && zoom > 6.0f) {
        const float step = (float)zoom;
        for (int px = (int)((canvas_min.x - image_min.x) / step); px <= (int)((canvas_max.x - image_min.x) / step); px++)
            draw_list->AddLineV(image_min.x + px * step, canvas_min.y, canvas_max.y, data->GridColor, 1.0f);
        for (int py = (int)((canvas_min.y - image_min.y) / step); py <= (int)((canvas_max.y - image_min.y) / step); py++)
            draw_list->AddLineH(canvas_min.x, canvas_max.x, image_min.y + py * step, data->GridColor, 1.0f);
    }
    draw_list->PopClipRect();
}
//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsColorAndPickers()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsColorAndPickers()
{
    if (UI::TreeNode("Color/Picker Widgets"))
    {
        IMGUI_DEMO_MARKER("Widgets/Color");
        static vec4 color = vec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
        static uiColorEditFlags base_flags = uiColorEditFlags_None;

        UI::BarrierText("Options");
        UI::CheckboxFlags("uiColorEditFlags_NoAlpha", &base_flags, uiColorEditFlags_NoAlpha);
        UI::CheckboxFlags("uiColorEditFlags_AlphaOpaque", &base_flags, uiColorEditFlags_AlphaOpaque);
        UI::CheckboxFlags("uiColorEditFlags_AlphaNoBg", &base_flags, uiColorEditFlags_AlphaNoBg);
        UI::CheckboxFlags("uiColorEditFlags_AlphaPreviewHalf", &base_flags, uiColorEditFlags_AlphaPreviewHalf);
        UI::CheckboxFlags("uiColorEditFlags_NoOptions", &base_flags, uiColorEditFlags_NoOptions); UI::SameLine(); HelpMarker("Right-click on the individual color widget to show options.");
        UI::CheckboxFlags("uiColorEditFlags_NoDragDrop", &base_flags, uiColorEditFlags_NoDragDrop);
        UI::CheckboxFlags("uiColorEditFlags_NoColorMarkers", &base_flags, uiColorEditFlags_NoColorMarkers);
        UI::CheckboxFlags("uiColorEditFlags_HDR", &base_flags, uiColorEditFlags_HDR); UI::SameLine(); HelpMarker("Currently all this does is to lift the 0..1 limits on dragging widgets.");

        IMGUI_DEMO_MARKER("Widgets/Color/ColorEdit");
        UI::BarrierText("Inline color editor");
        UI::Text("Color widget:");
        UI::SameLine(); HelpMarker(
            "Click on the color square to open a color picker.\n"
            "Ctrl+Click on individual component to input value.\n");
        UI::ColorEdit3("MyColor##1", (float*)&color, base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorEdit (HSV, with Alpha)");
        UI::Text("Color widget HSV with Alpha:");
        UI::ColorEdit4("MyColor##2", (float*)&color, uiColorEditFlags_DisplayHSV | base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorEdit (float display)");
        UI::Text("Color widget with Float Display:");
        UI::ColorEdit4("MyColor##2f", (float*)&color, uiColorEditFlags_Float | base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorButton (with Picker)");
        UI::Text("Color button with Picker:");
        UI::SameLine(); HelpMarker(
            "With the uiColorEditFlags_NoInputs flag you can hide all the slider/text inputs.\n"
            "With the uiColorEditFlags_NoLabel flag you can pass a non-empty label which will only "
            "be used for the tooltip and picker popup.");
        UI::ColorEdit4("MyColor##3", (float*)&color, uiColorEditFlags_NoInputs | uiColorEditFlags_NoLabel | base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorButton (with custom Picker popup)");
        UI::Text("Color button with Custom Picker Popup:");

        // Generate a default palette. The palette will persist and can be edited.
        static bool saved_palette_init = true;
        static vec4 saved_palette[32] = {};
        if (saved_palette_init)
        {
            for (int n = 0; n < IM_COUNTOF(saved_palette); n++)
            {
                UI::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f,
                    saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
                saved_palette[n].w = 1.0f; // Alpha
            }
            saved_palette_init = false;
        }

        static vec4 backup_color;
        bool open_popup = UI::ColorButton("MyColor##3b", color, base_flags);
        UI::SameLine(0, UI::GetStyle().ItemInnerSpacing.x);
        open_popup |= UI::Button("Palette");
        if (open_popup)
        {
            UI::OpenPopup("mypicker");
            backup_color = color;
        }
        if (UI::BeginPopup("mypicker"))
        {
            UI::Text("MY CUSTOM COLOR PICKER WITH AN AMAZING PALETTE!");
            UI::Barrier();
            UI::ColorPicker4("##picker", (float*)&color, base_flags | uiColorEditFlags_NoSidePreview | uiColorEditFlags_NoSmallPreview);
            UI::SameLine();

            UI::BeginGroup(); // Lock X position
            UI::Text("Current");
            UI::ColorButton("##current", color, uiColorEditFlags_NoPicker | uiColorEditFlags_AlphaPreviewHalf, vec2(60, 40));
            UI::Text("Previous");
            if (UI::ColorButton("##previous", backup_color, uiColorEditFlags_NoPicker | uiColorEditFlags_AlphaPreviewHalf, vec2(60, 40)))
                color = backup_color;
            UI::Barrier();
            UI::Text("Palette");
            for (int n = 0; n < IM_COUNTOF(saved_palette); n++)
            {
                UI::PushID(n);
                if ((n % 8) != 0)
                    UI::SameLine(0.0f, UI::GetStyle().ItemSpacing.y);

                uiColorEditFlags palette_button_flags = uiColorEditFlags_NoAlpha | uiColorEditFlags_NoPicker | uiColorEditFlags_NoTooltip;
                if (UI::ColorButton("##palette", saved_palette[n], palette_button_flags, vec2(20, 20)))
                    color = vec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!

                // Allow user to drop colors into each palette entry. Note that ColorButton() is already a
                // drag source by default, unless specifying the uiColorEditFlags_NoDragDrop flag.
                if (UI::BeginDragDropTarget())
                {
                    if (const uiPayload* payload = UI::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                        memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
                    if (const uiPayload* payload = UI::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                        memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
                    UI::EndDragDropTarget();
                }

                UI::PopID();
            }
            UI::EndGroup();
            UI::EndPopup();
        }

        IMGUI_DEMO_MARKER("Widgets/Color/ColorButton (simple)");
        UI::Text("Color button only:");
        static bool no_border = false;
        UI::Checkbox("uiColorEditFlags_NoBorder", &no_border);
        UI::ColorButton("MyColor##3c", *(vec4*)&color, base_flags | (no_border ? uiColorEditFlags_NoBorder : 0), vec2(80, 80));

        IMGUI_DEMO_MARKER("Widgets/Color/ColorPicker");
        UI::BarrierText("Color picker");

        static bool ref_color = false;
        static vec4 ref_color_v(1.0f, 0.0f, 1.0f, 0.5f);
        static int picker_mode = 0;
        static int display_mode = 0;
        static uiColorEditFlags color_picker_flags = uiColorEditFlags_AlphaBar;

        UI::PushID("Color picker");
        UI::CheckboxFlags("uiColorEditFlags_NoAlpha", &color_picker_flags, uiColorEditFlags_NoAlpha);
        UI::CheckboxFlags("uiColorEditFlags_AlphaBar", &color_picker_flags, uiColorEditFlags_AlphaBar);
        UI::CheckboxFlags("uiColorEditFlags_NoSidePreview", &color_picker_flags, uiColorEditFlags_NoSidePreview);
        if (color_picker_flags & uiColorEditFlags_NoSidePreview)
        {
            UI::SameLine();
            UI::Checkbox("With Ref Color", &ref_color);
            if (ref_color)
            {
                UI::SameLine();
                UI::ColorEdit4("##RefColor", &ref_color_v.x, uiColorEditFlags_NoInputs | base_flags);
            }
        }

        UI::Combo("Picker Mode", &picker_mode, "Auto/Current\0uiColorEditFlags_PickerHueBar\0uiColorEditFlags_PickerHueWheel\0");
        UI::SameLine(); HelpMarker("When not specified explicitly, user can right-click the picker to change mode.");

        UI::Combo("Display Mode", &display_mode, "Auto/Current\0uiColorEditFlags_NoInputs\0uiColorEditFlags_DisplayRGB\0uiColorEditFlags_DisplayHSV\0uiColorEditFlags_DisplayHex\0");
        UI::SameLine(); HelpMarker(
            "ColorEdit defaults to displaying RGB inputs if you don't specify a display mode, "
            "but the user can change it with a right-click on those inputs.\n\nColorPicker defaults to displaying RGB+HSV+Hex "
            "if you don't specify a display mode.\n\nYou can change the defaults using SetColorEditOptions().");

        uiColorEditFlags flags = base_flags | color_picker_flags;
        if (picker_mode == 1)  flags |= uiColorEditFlags_PickerHueBar;
        if (picker_mode == 2)  flags |= uiColorEditFlags_PickerHueWheel;
        if (display_mode == 1) flags |= uiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
        if (display_mode == 2) flags |= uiColorEditFlags_DisplayRGB;     // Override display mode
        if (display_mode == 3) flags |= uiColorEditFlags_DisplayHSV;
        if (display_mode == 4) flags |= uiColorEditFlags_DisplayHex;
        UI::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);

        UI::Text("Set defaults in code:");
        UI::SameLine(); HelpMarker(
            "SetColorEditOptions() is designed to allow you to set boot-time default.\n"
            "We don't have Push/Pop functions because you can force options on a per-widget basis if needed, "
            "and the user can change non-forced ones with the options menu.\nWe don't have a getter to avoid "
            "encouraging you to persistently save values that aren't forward-compatible.");
        if (UI::Button("Default: Uint8 + HSV + Hue Bar"))
            UI::SetColorEditOptions(uiColorEditFlags_Uint8 | uiColorEditFlags_DisplayHSV | uiColorEditFlags_PickerHueBar);
        if (UI::Button("Default: Float + HDR + Hue Wheel"))
            UI::SetColorEditOptions(uiColorEditFlags_Float | uiColorEditFlags_HDR | uiColorEditFlags_PickerHueWheel);

        // Always display a small version of both types of pickers
        // (that's in order to make it more visible in the demo to people who are skimming quickly through it)
        UI::Text("Both types:");
        float w = (UI::GetContentRegionAvail().x - UI::GetStyle().ItemSpacing.y) * 0.40f;
        UI::SetNextItemWidth(w);
        UI::ColorPicker3("##MyColor##5", (float*)&color, uiColorEditFlags_PickerHueBar | uiColorEditFlags_NoSidePreview | uiColorEditFlags_NoInputs | uiColorEditFlags_NoAlpha);
        UI::SameLine();
        UI::SetNextItemWidth(w);
        UI::ColorPicker3("##MyColor##6", (float*)&color, uiColorEditFlags_PickerHueWheel | uiColorEditFlags_NoSidePreview | uiColorEditFlags_NoInputs | uiColorEditFlags_NoAlpha);
        UI::PopID();

        // HSV encoded support (to avoid RGB<>HSV round trips and singularities when S==0 or V==0)
        static vec4 color_hsv(0.23f, 1.0f, 1.0f, 1.0f); // Stored as HSV!
        UI::Spacing();
        UI::Text("HSV encoded colors");
        UI::SameLine(); HelpMarker(
            "By default, colors are given to ColorEdit and ColorPicker in RGB, but uiColorEditFlags_InputHSV "
            "allows you to store colors as HSV and pass them to ColorEdit and ColorPicker as HSV. This comes with the "
            "added benefit that you can manipulate hue values with the picker even when saturation or value are zero.");
        UI::Text("Color widget with InputHSV:");
        UI::ColorEdit4("HSV shown as RGB##1", (float*)&color_hsv, uiColorEditFlags_DisplayRGB | uiColorEditFlags_InputHSV | uiColorEditFlags_Float);
        UI::ColorEdit4("HSV shown as HSV##1", (float*)&color_hsv, uiColorEditFlags_DisplayHSV | uiColorEditFlags_InputHSV | uiColorEditFlags_Float);
        UI::DragFloat4("Raw HSV values", (float*)&color_hsv, 0.01f, 0.0f, 1.0f);

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsComboBoxes()
//-----------------------------------------------------------------------------
static void DemoWindowWidgetsComboBoxes() {
    if (UI::TreeNode("Combo")) {
        // Combo Boxes are also called "Dropdown" in other systems
        // Expose flags as checkbox for the demo
        static uiComboFlags flags = 0;
        UI::CheckboxFlags("uiComboFlags_PopupAlignLeft", &flags, uiComboFlags_PopupAlignLeft);
        UI::SameLine(); HelpMarker("Only makes a difference if the popup is larger than the combo");
        if (UI::CheckboxFlags("uiComboFlags_NoArrowButton", &flags, uiComboFlags_NoArrowButton))
            flags &= ~uiComboFlags_NoPreview;     // Clear incompatible flags
        if (UI::CheckboxFlags("uiComboFlags_NoPreview", &flags, uiComboFlags_NoPreview))
            flags &= ~(uiComboFlags_NoArrowButton | uiComboFlags_WidthFitPreview); // Clear incompatible flags
        if (UI::CheckboxFlags("uiComboFlags_WidthFitPreview", &flags, uiComboFlags_WidthFitPreview))
            flags &= ~uiComboFlags_NoPreview;
        // Override default popup height
        if (UI::CheckboxFlags("uiComboFlags_Small", &flags, uiComboFlags_Small))
            flags &= ~(uiComboFlags_HeightMask_ & ~uiComboFlags_Small);
        if (UI::CheckboxFlags("uiComboFlags_Regular", &flags, uiComboFlags_Regular))
            flags &= ~(uiComboFlags_HeightMask_ & ~uiComboFlags_Regular);
        if (UI::CheckboxFlags("uiComboFlags_Largest", &flags, uiComboFlags_Largest))
            flags &= ~(uiComboFlags_HeightMask_ & ~uiComboFlags_Largest);
        // Using the generic BeginCombo() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        static int item_selected_idx = 0; // Here we store our selection data as an index.
        const char* combo_preview_value = items[item_selected_idx];
        if (UI::BeginCombo("combo 1", combo_preview_value, flags)) {
            for (int n = 0; n < IM_COUNTOF(items); n++) {
                const bool is_selected = (item_selected_idx == n);
                if (UI::Selectable(items[n], is_selected)) item_selected_idx = n;
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) UI::SetItemDefaultFocus();
            }
            UI::EndCombo();
        }
        // Show case embedding a filter using a simple trick: displaying the filter inside combo contents.
        // See https://github.com/ocornut/imgui/issues/718 for advanced/esoteric alternatives.
        if (UI::BeginCombo("combo 2 (w/ filter)", combo_preview_value, flags)) {
            static uiTextFilter filter;
            if (UI::IsWindowAppearing()) { UI::SetKeyboardFocusHere(); filter.Clear(); }
            UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_F);
            filter.Draw("##Filter", -FLT_MIN);
            for (int n = 0; n < IM_COUNTOF(items); n++) {
                const bool is_selected = (item_selected_idx == n);
                if (filter.PassFilter(items[n]))
                    if (UI::Selectable(items[n], is_selected)) item_selected_idx = n;
            }
            UI::EndCombo();
        }
        UI::Spacing();
        UI::BarrierText("One-liner variants");
        HelpMarker("The Combo() function is not greatly useful apart from cases were you want to embed all options in a single strings.\nFlags above don't apply to this section.");
        // Simplified one-liner Combo() API, using values packed in a single constant string
        // This is a convenience for when the selection set is small and known at compile-time.
        static int item_current_2 = 0;
        UI::Combo("combo 3 (one-liner)", &item_current_2, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
        // Simplified one-liner Combo() using an array of const char*
        // This is not very useful (may obsolete): prefer using BeginCombo()/EndCombo() for full control.
        static int item_current_3 = -1; // If the selection isn't within 0..count, Combo won't display a preview
        UI::Combo("combo 4 (array)", &item_current_3, items, IM_COUNTOF(items));
        // Simplified one-liner Combo() using an accessor function
        static int item_current_4 = 0;
        UI::Combo("combo 5 (function)", &item_current_4, [](void* data, int n) { return ((const char**)data)[n]; }, items, IM_COUNTOF(items));
        UI::TreePop();
    }
}
//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDataTypes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDataTypes()
{
    if (UI::TreeNode("Data Types"))
    {
        IMGUI_DEMO_MARKER("Widgets/Data Types");
        // DragScalar/InputScalar/SliderScalar functions allow various data types
        // - signed/unsigned
        // - 8/16/32/64-bits
        // - integer/float/double
        // To avoid polluting the public API with all possible combinations, we use the uiDataType enum
        // to pass the type, and passing all arguments by pointer.
        // This is the reason the test code below creates local variables to hold "zero" "one" etc. for each type.
        // In practice, if you frequently use a given type that is not covered by the normal API entry points,
        // you can wrap it yourself inside a 1 line function which can take typed argument as value instead of void*,
        // and then pass their address to the generic function. For example:
        //   bool MySliderU64(const char *label, u64* value, u64 min = 0, u64 max = 0, const char* format = "%lld")
        //   {
        //      return SliderScalar(label, uiDataType_U64, value, &min, &max, format);
        //   }

        // Setup limits (as helper variables so we can take their address, as explained above)
        // Note: SliderScalar() functions have a maximum usable range of half the natural type maximum, hence the /2.
        #ifndef LLONG_MIN
        ImS64 LLONG_MIN = -9223372036854775807LL - 1;
        ImS64 LLONG_MAX = 9223372036854775807LL;
        ImU64 ULLONG_MAX = (2ULL * 9223372036854775807LL + 1);
        #endif
        const char    s8_zero  = 0,   s8_one  = 1,   s8_fifty  = 50, s8_min  = -128,        s8_max = 127;
        const ImU8    u8_zero  = 0,   u8_one  = 1,   u8_fifty  = 50, u8_min  = 0,           u8_max = 255;
        const short   s16_zero = 0,   s16_one = 1,   s16_fifty = 50, s16_min = -32768,      s16_max = 32767;
        const ImU16   u16_zero = 0,   u16_one = 1,   u16_fifty = 50, u16_min = 0,           u16_max = 65535;
        const ImS32   s32_zero = 0,   s32_one = 1,   s32_fifty = 50, s32_min = INT_MIN/2,   s32_max = INT_MAX/2,    s32_hi_a = INT_MAX/2 - 100,    s32_hi_b = INT_MAX/2;
        const ImU32   u32_zero = 0,   u32_one = 1,   u32_fifty = 50, u32_min = 0,           u32_max = UINT_MAX/2,   u32_hi_a = UINT_MAX/2 - 100,   u32_hi_b = UINT_MAX/2;
        const ImS64   s64_zero = 0,   s64_one = 1,   s64_fifty = 50, s64_min = LLONG_MIN/2, s64_max = LLONG_MAX/2,  s64_hi_a = LLONG_MAX/2 - 100,  s64_hi_b = LLONG_MAX/2;
        const ImU64   u64_zero = 0,   u64_one = 1,   u64_fifty = 50, u64_min = 0,           u64_max = ULLONG_MAX/2, u64_hi_a = ULLONG_MAX/2 - 100, u64_hi_b = ULLONG_MAX/2;
        const float   f32_zero = 0.f, f32_one = 1.f, f32_lo_a = -10000000000.0f, f32_hi_a = +10000000000.0f;
        const double  f64_zero = 0.,  f64_one = 1.,  f64_lo_a = -1000000000000000.0, f64_hi_a = +1000000000000000.0;

        // State
        static char   s8_v  = 127;
        static ImU8   u8_v  = 255;
        static short  s16_v = 32767;
        static ImU16  u16_v = 65535;
        static ImS32  s32_v = -1;
        static ImU32  u32_v = (ImU32)-1;
        static ImS64  s64_v = -1;
        static ImU64  u64_v = (ImU64)-1;
        static float  f32_v = 0.123f;
        static double f64_v = 90000.01234567890123456789;

        const float drag_speed = 0.2f;
        static bool drag_clamp = false;
        IMGUI_DEMO_MARKER("Widgets/Data Types/Drags");
        UI::BarrierText("Drags");
        UI::Checkbox("Clamp integers to 0..50", &drag_clamp);
        UI::SameLine(); HelpMarker(
            "As with every widget in dear imgui, we never modify values unless there is a user interaction.\n"
            "You can override the clamping limits by using Ctrl+Click to input a value.");
        UI::DragScalar("drag s8",        uiDataType_S8,     &s8_v,  drag_speed, drag_clamp ? &s8_zero  : NULL, drag_clamp ? &s8_fifty  : NULL);
        UI::DragScalar("drag u8",        uiDataType_U8,     &u8_v,  drag_speed, drag_clamp ? &u8_zero  : NULL, drag_clamp ? &u8_fifty  : NULL, "%u ms");
        UI::DragScalar("drag s16",       uiDataType_S16,    &s16_v, drag_speed, drag_clamp ? &s16_zero : NULL, drag_clamp ? &s16_fifty : NULL);
        UI::DragScalar("drag u16",       uiDataType_U16,    &u16_v, drag_speed, drag_clamp ? &u16_zero : NULL, drag_clamp ? &u16_fifty : NULL, "%u ms");
        UI::DragScalar("drag s32",       uiDataType_S32,    &s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL);
        UI::DragScalar("drag s32 hex",   uiDataType_S32,    &s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL, "0x%08X");
        UI::DragScalar("drag u32",       uiDataType_U32,    &u32_v, drag_speed, drag_clamp ? &u32_zero : NULL, drag_clamp ? &u32_fifty : NULL, "%u ms");
        UI::DragScalar("drag s64",       uiDataType_S64,    &s64_v, drag_speed, drag_clamp ? &s64_zero : NULL, drag_clamp ? &s64_fifty : NULL);
        UI::DragScalar("drag u64",       uiDataType_U64,    &u64_v, drag_speed, drag_clamp ? &u64_zero : NULL, drag_clamp ? &u64_fifty : NULL);
        UI::DragScalar("drag float",     uiDataType_Float,  &f32_v, 0.005f,  &f32_zero, &f32_one, "%f");
        UI::DragScalar("drag float log", uiDataType_Float,  &f32_v, 0.005f,  &f32_zero, &f32_one, "%f", uiSliderFlags_Logarithmic);
        UI::DragScalar("drag double",    uiDataType_Double, &f64_v, 0.0005f, &f64_zero, NULL,     "%.10f grams");
        UI::DragScalar("drag double log",uiDataType_Double, &f64_v, 0.0005f, &f64_zero, &f64_one, "0 < %.10f < 1", uiSliderFlags_Logarithmic);

        IMGUI_DEMO_MARKER("Widgets/Data Types/Sliders");
        UI::BarrierText("Sliders");
        UI::SliderScalar("slider s8 full",       uiDataType_S8,     &s8_v,  &s8_min,   &s8_max,   "%d");
        UI::SliderScalar("slider u8 full",       uiDataType_U8,     &u8_v,  &u8_min,   &u8_max,   "%u");
        UI::SliderScalar("slider s16 full",      uiDataType_S16,    &s16_v, &s16_min,  &s16_max,  "%d");
        UI::SliderScalar("slider u16 full",      uiDataType_U16,    &u16_v, &u16_min,  &u16_max,  "%u");
        UI::SliderScalar("slider s32 low",       uiDataType_S32,    &s32_v, &s32_zero, &s32_fifty,"%d");
        UI::SliderScalar("slider s32 high",      uiDataType_S32,    &s32_v, &s32_hi_a, &s32_hi_b, "%d");
        UI::SliderScalar("slider s32 full",      uiDataType_S32,    &s32_v, &s32_min,  &s32_max,  "%d");
        UI::SliderScalar("slider s32 hex",       uiDataType_S32,    &s32_v, &s32_zero, &s32_fifty, "0x%04X");
        UI::SliderScalar("slider u32 low",       uiDataType_U32,    &u32_v, &u32_zero, &u32_fifty,"%u");
        UI::SliderScalar("slider u32 high",      uiDataType_U32,    &u32_v, &u32_hi_a, &u32_hi_b, "%u");
        UI::SliderScalar("slider u32 full",      uiDataType_U32,    &u32_v, &u32_min,  &u32_max,  "%u");
        UI::SliderScalar("slider s64 low",       uiDataType_S64,    &s64_v, &s64_zero, &s64_fifty,"%" PRId64);
        UI::SliderScalar("slider s64 high",      uiDataType_S64,    &s64_v, &s64_hi_a, &s64_hi_b, "%" PRId64);
        UI::SliderScalar("slider s64 full",      uiDataType_S64,    &s64_v, &s64_min,  &s64_max,  "%" PRId64);
        UI::SliderScalar("slider u64 low",       uiDataType_U64,    &u64_v, &u64_zero, &u64_fifty,"%" PRIu64 " ms");
        UI::SliderScalar("slider u64 high",      uiDataType_U64,    &u64_v, &u64_hi_a, &u64_hi_b, "%" PRIu64 " ms");
        UI::SliderScalar("slider u64 full",      uiDataType_U64,    &u64_v, &u64_min,  &u64_max,  "%" PRIu64 " ms");
        UI::SliderScalar("slider float low",     uiDataType_Float,  &f32_v, &f32_zero, &f32_one);
        UI::SliderScalar("slider float low log", uiDataType_Float,  &f32_v, &f32_zero, &f32_one,  "%.10f", uiSliderFlags_Logarithmic);
        UI::SliderScalar("slider float high",    uiDataType_Float,  &f32_v, &f32_lo_a, &f32_hi_a, "%e");
        UI::SliderScalar("slider double low",    uiDataType_Double, &f64_v, &f64_zero, &f64_one,  "%.10f grams");
        UI::SliderScalar("slider double low log",uiDataType_Double, &f64_v, &f64_zero, &f64_one,  "%.10f", uiSliderFlags_Logarithmic);
        UI::SliderScalar("slider double high",   uiDataType_Double, &f64_v, &f64_lo_a, &f64_hi_a, "%e grams");

        UI::BarrierText("Sliders (reverse)");
        UI::SliderScalar("slider s8 reverse",    uiDataType_S8,   &s8_v,  &s8_max,    &s8_min,   "%d");
        UI::SliderScalar("slider u8 reverse",    uiDataType_U8,   &u8_v,  &u8_max,    &u8_min,   "%u");
        UI::SliderScalar("slider s32 reverse",   uiDataType_S32,  &s32_v, &s32_fifty, &s32_zero, "%d");
        UI::SliderScalar("slider u32 reverse",   uiDataType_U32,  &u32_v, &u32_fifty, &u32_zero, "%u");
        UI::SliderScalar("slider s64 reverse",   uiDataType_S64,  &s64_v, &s64_fifty, &s64_zero, "%" PRId64);
        UI::SliderScalar("slider u64 reverse",   uiDataType_U64,  &u64_v, &u64_fifty, &u64_zero, "%" PRIu64 " ms");

        IMGUI_DEMO_MARKER("Widgets/Data Types/Inputs");
        static bool inputs_step = true;
        static uiInputTextFlags flags = uiInputTextFlags_None;
        UI::BarrierText("Inputs");
        UI::Checkbox("Show step buttons", &inputs_step);
        UI::CheckboxFlags("uiInputTextFlags_ReadOnly", &flags, uiInputTextFlags_ReadOnly);
        UI::CheckboxFlags("uiInputTextFlags_ParseEmptyRefVal", &flags, uiInputTextFlags_ParseEmptyRefVal);
        UI::CheckboxFlags("uiInputTextFlags_DisplayEmptyRefVal", &flags, uiInputTextFlags_DisplayEmptyRefVal);
        UI::InputScalar("input s8",      uiDataType_S8,     &s8_v,  inputs_step ? &s8_one  : NULL, NULL, "%d", flags);
        UI::InputScalar("input u8",      uiDataType_U8,     &u8_v,  inputs_step ? &u8_one  : NULL, NULL, "%u", flags);
        UI::InputScalar("input s16",     uiDataType_S16,    &s16_v, inputs_step ? &s16_one : NULL, NULL, "%d", flags);
        UI::InputScalar("input u16",     uiDataType_U16,    &u16_v, inputs_step ? &u16_one : NULL, NULL, "%u", flags);
        UI::InputScalar("input s32",     uiDataType_S32,    &s32_v, inputs_step ? &s32_one : NULL, NULL, "%d", flags);
        UI::InputScalar("input s32 hex", uiDataType_S32,    &s32_v, inputs_step ? &s32_one : NULL, NULL, "%04X", flags);
        UI::InputScalar("input u32",     uiDataType_U32,    &u32_v, inputs_step ? &u32_one : NULL, NULL, "%u", flags);
        UI::InputScalar("input u32 hex", uiDataType_U32,    &u32_v, inputs_step ? &u32_one : NULL, NULL, "%08X", flags);
        UI::InputScalar("input s64",     uiDataType_S64,    &s64_v, inputs_step ? &s64_one : NULL, NULL, NULL, flags);
        UI::InputScalar("input u64",     uiDataType_U64,    &u64_v, inputs_step ? &u64_one : NULL, NULL, NULL, flags);
        UI::InputScalar("input float",   uiDataType_Float,  &f32_v, inputs_step ? &f32_one : NULL, NULL, NULL, flags);
        UI::InputScalar("input double",  uiDataType_Double, &f64_v, inputs_step ? &f64_one : NULL, NULL, NULL, flags);

        UI::TreePop();
    }
}
//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDragAndDrop()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDragAndDrop()
{
    if (UI::TreeNode("Drag and Drop"))
    {
        IMGUI_DEMO_MARKER("Widgets/Drag and drop");
        if (UI::TreeNode("Drag and drop in standard widgets"))
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and drop/Standard widgets");
            // ColorEdit widgets automatically act as drag source and drag target.
            // They are using standardized payload strings IMGUI_PAYLOAD_TYPE_COLOR_3F and IMGUI_PAYLOAD_TYPE_COLOR_4F
            // to allow your own widgets to use colors in their drag and drop interaction.
            // Also see 'Demo->Widgets->Color/Picker Widgets->Palette' demo.
            HelpMarker("You can drag from the color squares.");
            static float col1[3] = { 1.0f, 0.0f, 0.2f };
            static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            UI::ColorEdit3("color 1", col1);
            UI::ColorEdit4("color 2", col2);
            UI::TreePop();
        }

        if (UI::TreeNode("Drag and drop to copy/swap items"))
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and drop/Copy-swap items");
            enum Mode
            {
                Mode_Copy,
                Mode_Move,
                Mode_Swap
            };
            static int mode = 0;
            if (UI::RadioButton("Copy", mode == Mode_Copy)) { mode = Mode_Copy; } UI::SameLine();
            if (UI::RadioButton("Move", mode == Mode_Move)) { mode = Mode_Move; } UI::SameLine();
            if (UI::RadioButton("Swap", mode == Mode_Swap)) { mode = Mode_Swap; }
            static const char* names[9] =
            {
                "Bobby", "Beatrice", "Betty",
                "Brianna", "Barry", "Bernard",
                "Bibi", "Blaine", "Bryn"
            };
            for (int n = 0; n < IM_COUNTOF(names); n++)
            {
                UI::PushID(n);
                if ((n % 3) != 0)
                    UI::SameLine();
                UI::Button(names[n], vec2(60, 60));

                // Our buttons are both drag sources and drag targets here!
                if (UI::BeginDragDropSource(uiDragDropFlags_None))
                {
                    // Set payload to carry the index of our item (could be anything)
                    UI::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));

                    // Display preview (could be anything, e.g. when dragging an image we could decide to display
                    // the filename and a small preview of the image, etc.)
                    if (mode == Mode_Copy) { UI::Text("Copy %s", names[n]); }
                    if (mode == Mode_Move) { UI::Text("Move %s", names[n]); }
                    if (mode == Mode_Swap) { UI::Text("Swap %s", names[n]); }
                    UI::EndDragDropSource();
                }
                if (UI::BeginDragDropTarget())
                {
                    if (const uiPayload* payload = UI::AcceptDragDropPayload("DND_DEMO_CELL"))
                    {
                        IM_ASSERT(payload->DataSize == sizeof(int));
                        int payload_n = *(const int*)payload->Data;
                        if (mode == Mode_Copy)
                        {
                            names[n] = names[payload_n];
                        }
                        if (mode == Mode_Move)
                        {
                            names[n] = names[payload_n];
                            names[payload_n] = "";
                        }
                        if (mode == Mode_Swap)
                        {
                            const char* tmp = names[n];
                            names[n] = names[payload_n];
                            names[payload_n] = tmp;
                        }
                    }
                    UI::EndDragDropTarget();
                }
                UI::PopID();
            }
            UI::TreePop();
        }

        if (UI::TreeNode("Drag to reorder items (simple)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and Drop/Drag to reorder items (simple)");
            // FIXME: there is temporary (usually single-frame) ID Conflict during reordering as a same item may be submitting twice.
            // This code was always slightly faulty but in a way which was not easily noticeable.
            // Until we fix this, enable uiItemFlags_AllowDuplicateId to disable detecting the issue.
            UI::PushItemFlag(uiItemFlags_AllowDuplicateId, true);

            // Simple reordering
            HelpMarker(
                "We don't use the drag and drop api at all here! "
                "Instead we query when the item is held but not hovered, and order items accordingly.");
            static const char* item_names[] = { "Item One", "Item Two", "Item Three", "Item Four", "Item Five" };
            for (int n = 0; n < IM_COUNTOF(item_names); n++)
            {
                const char* item = item_names[n];
                UI::Selectable(item);

                if (UI::IsItemActive() && !UI::IsItemHovered())
                {
                    int n_next = n + (UI::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (n_next >= 0 && n_next < IM_COUNTOF(item_names))
                    {
                        item_names[n] = item_names[n_next];
                        item_names[n_next] = item;
                        UI::ResetMouseDragDelta();
                    }
                }
            }

            UI::PopItemFlag();
            UI::TreePop();
        }

        if (UI::TreeNode("Tooltip at target location"))
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and Drop/Tooltip at target location");
            for (int n = 0; n < 2; n++)
            {
                // Drop targets
                UI::Button(n ? "drop here##1" : "drop here##0");
                if (UI::BeginDragDropTarget())
                {
                    uiDragDropFlags drop_target_flags = uiDragDropFlags_AcceptBeforeDelivery | uiDragDropFlags_AcceptNoPreviewTooltip;
                    if (const uiPayload* payload = UI::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F, drop_target_flags))
                    {
                        IM_UNUSED(payload);
                        UI::SetMouseCursor(uiMouseCursor_NotAllowed);
                        UI::SetTooltip("Cannot drop here!");
                    }
                    UI::EndDragDropTarget();
                }

                // Drop source
                static vec4 col4 = { 1.0f, 0.0f, 0.2f, 1.0f };
                if (n == 0)
                    UI::ColorButton("drag me", col4);

            }
            UI::TreePop();
        }

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDragsAndSliders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDragsAndSliders()
{
    if (UI::TreeNode("Drag/Slider Flags"))
    {
        IMGUI_DEMO_MARKER("Widgets/Drag and Slider Flags");
        // Demonstrate using advanced flags for DragXXX and SliderXXX functions. Note that the flags are the same!
        static uiSliderFlags flags = uiSliderFlags_None;
        UI::CheckboxFlags("uiSliderFlags_AlwaysClamp", &flags, uiSliderFlags_AlwaysClamp);
        UI::CheckboxFlags("uiSliderFlags_ClampOnInput", &flags, uiSliderFlags_ClampOnInput);
        UI::SameLine(); HelpMarker("Clamp value to min/max bounds when input manually with Ctrl+Click. By default Ctrl+Click allows going out of bounds.");
        UI::CheckboxFlags("uiSliderFlags_ClampZeroRange", &flags, uiSliderFlags_ClampZeroRange);
        UI::SameLine(); HelpMarker("Clamp even if min==max==0.0f. Otherwise DragXXX functions don't clamp.");
        UI::CheckboxFlags("uiSliderFlags_Logarithmic", &flags, uiSliderFlags_Logarithmic);
        UI::SameLine(); HelpMarker("Enable logarithmic editing (more precision for small values).");
        UI::CheckboxFlags("uiSliderFlags_NoRoundToFormat", &flags, uiSliderFlags_NoRoundToFormat);
        UI::SameLine(); HelpMarker("Disable rounding underlying value to match precision of the format string (e.g. %.3f values are rounded to those 3 digits).");
        UI::CheckboxFlags("uiSliderFlags_NoInput", &flags, uiSliderFlags_NoInput);
        UI::SameLine(); HelpMarker("Disable Ctrl+Click or Enter key allowing to input text directly into the widget.");
        UI::CheckboxFlags("uiSliderFlags_NoSpeedTweaks", &flags, uiSliderFlags_NoSpeedTweaks);
        UI::SameLine(); HelpMarker("Disable keyboard modifiers altering tweak speed. Useful if you want to alter tweak speed yourself based on your own logic.");
        UI::CheckboxFlags("uiSliderFlags_WrapAround", &flags, uiSliderFlags_WrapAround);
        UI::SameLine(); HelpMarker("Enable wrapping around from max to min and from min to max (only supported by DragXXX() functions)");
        UI::CheckboxFlags("uiSliderFlags_ColorMarkers", &flags, uiSliderFlags_ColorMarkers);

        // Drags
        static float drag_f = 0.5f;
        static float drag_f4[4];
        static int drag_i = 50;
        UI::Text("Underlying float value: %f", drag_f);
        UI::DragFloat("DragFloat (0 -> 1)", &drag_f, 0.005f, 0.0f, 1.0f, "%.3f", flags);
        UI::DragFloat("DragFloat (0 -> +inf)", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
        UI::DragFloat("DragFloat (-inf -> 1)", &drag_f, 0.005f, -FLT_MAX, 1.0f, "%.3f", flags);
        UI::DragFloat("DragFloat (-inf -> +inf)", &drag_f, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flags);
        //UI::DragFloat("DragFloat (0 -> 0)", &drag_f, 0.005f, 0.0f, 0.0f, "%.3f", flags);           // To test ClampZeroRange
        //UI::DragFloat("DragFloat (100 -> 100)", &drag_f, 0.005f, 100.0f, 100.0f, "%.3f", flags);
        UI::DragInt("DragInt (0 -> 100)", &drag_i, 0.5f, 0, 100, "%d", flags);
        UI::DragFloat4("DragFloat4 (0 -> 1)", drag_f4, 0.005f, 0.0f, 1.0f, "%.3f", flags); // Multi-component item, mostly here to document the effect of uiSliderFlags_ColorMarkers.

        // Sliders
        static float slider_f = 0.5f;
        static float slider_f4[4];
        static int slider_i = 50;
        const uiSliderFlags flags_for_sliders = (flags & ~uiSliderFlags_WrapAround);
        UI::Text("Underlying float value: %f", slider_f);
        UI::SliderFloat("SliderFloat (0 -> 1)", &slider_f, 0.0f, 1.0f, "%.3f", flags_for_sliders);
        UI::SliderInt("SliderInt (0 -> 100)", &slider_i, 0, 100, "%d", flags_for_sliders);
        UI::SliderFloat4("SliderFloat4 (0 -> 1)", slider_f4, 0.0f, 1.0f, "%.3f", flags); // Multi-component item, mostly here to document the effect of uiSliderFlags_ColorMarkers.

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsFonts()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsFonts()
{
    if (UI::TreeNode("Fonts"))
    {
        IMGUI_DEMO_MARKER("Widgets/Fonts");
        ImFontAtlas* atlas = UI::GetIO().Fonts;
        UI::ShowFontAtlas(atlas);
        // FIXME-NEWATLAS: Provide a demo to add/create a procedural font?
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsImages()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsImages()
{
    if (UI::TreeNode("Images"))
    {
        IMGUI_DEMO_MARKER("Widgets/Images");
        uiIO& io = UI::GetIO();
        UI::TextWrapped(
            "Below we are displaying the font texture (which is the only texture we have access to in this demo). "
            "Use the 'ImTextureID' type as storage to pass pointers or identifier to your own texture data. "
            "Hover the texture for a zoomed view!");

        // Below we are displaying the font texture because it is the only texture we have access to inside the demo!
        // Read description about ImTextureID/ImTextureRef and FAQ for details about texture identifiers.
        // If you use one of the default imgui_impl_XXXX.cpp rendering backend, they all have comments at the top
        // of their respective source file to specify what they are using as texture identifier, for example:
        // - The imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer.
        // - The imgui_impl_opengl3.cpp renderer expect a GLuint OpenGL texture identifier, etc.
        // So with the DirectX11 backend, you call UI::Image() with a 'ID3D11ShaderResourceView*' cast to ImTextureID.
        // - If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers
        //   to UI::Image(), and gather width/height through your own functions, etc.
        // - You can use ShowMetricsWindow() to inspect the draw data that are being passed to your renderer,
        //   it will help you debug issues if you are confused about it.
        // - Consider using the lower-level ImDrawList::AddImage() API, via UI::GetWindowDrawList()->AddImage().
        // - Read https://github.com/ocornut/imgui/blob/master/docs/FAQ.md
        // - Read https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples

        // Grab the current texture identifier used by the font atlas.
        ImFontAtlas* atlas = io.Fonts;
        ImTextureRef my_tex_id = atlas->TexRef;
        float my_tex_w = (float)atlas->TexData->Width; // Regular user code should never have to care about TexData-> fields, but since we want to display the entire texture here, we pull Width/Height from it.
        float my_tex_h = (float)atlas->TexData->Height;
        UI::Text("%.0fx%.0f", my_tex_w, my_tex_h);

        // Basic drawing
        UI::BarrierText("Image()/ImageWithBg() function");
        vec2 uv_min = vec2(0.0f, 0.0f); // Top-left
        vec2 uv_max = vec2(1.0f, 1.0f); // Lower-right
        UI::PushStyleVar(uiStyleVar_ImageBorderSize, IM_MAX(1.0f, UI::GetStyle().ImageBorderSize));
        UI::ImageWithBg(my_tex_id, vec2(my_tex_w, my_tex_h), uv_min, uv_max, vec4(0.0f, 0.0f, 0.0f, 1.0f));
        UI::PopStyleVar();

        // Fancy widget
        UI::BarrierText("Interactive Image Viewer");
        static ExampleImageViewerData image_viewer;
        vec2 canvas_size(UI::GetContentRegionAvail().x, my_tex_h * 2.0f);
        ExampleImageViewer_DrawOptions(&image_viewer);
        ExampleImageViewer_DrawCanvas(&image_viewer, canvas_size, my_tex_id, (int)my_tex_w, (int)my_tex_h);

        IMGUI_DEMO_MARKER("Widgets/Images/Textured buttons");
        UI::BarrierText("Textured Buttons");
        UI::TextWrapped("And now some textured buttons..");
        static int pressed_count = 0;
        for (int i = 0; i < 8; i++)
        {
            // UV coordinates are often (0.0f, 0.0f) and (1.0f, 1.0f) to display an entire textures.
            // Here are trying to display only a 32x32 pixels area of the texture, hence the UV computation.
            // Read about UV coordinates here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
            UI::PushID(i);
            if (i > 0)
                UI::PushStyleVar(uiStyleVar_FramePadding, vec2(i - 1.0f, i - 1.0f));
            vec2 size = vec2(32.0f, 32.0f);                         // Size of the image we want to make visible
            vec2 uv0 = vec2(0.0f, 0.0f);                            // UV coordinates for lower-left
            vec2 uv1 = vec2(32.0f / my_tex_w, 32.0f / my_tex_h);    // UV coordinates for (32,32) in our texture
            vec4 bg_col = vec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
            vec4 tint_col = vec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
            if (UI::ImageButton("", my_tex_id, size, uv0, uv1, bg_col, tint_col))
                pressed_count += 1;
            if (i > 0)
                UI::PopStyleVar();
            UI::PopID();
            UI::SameLine();
        }
        UI::NewLine();
        UI::Text("Pressed %d times.", pressed_count);
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsListBoxes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsListBoxes()
{
    if (UI::TreeNode("List Boxes"))
    {
        IMGUI_DEMO_MARKER("Widgets/List Boxes");
        // BeginListBox() is essentially a thin wrapper to using BeginChild()/EndChild()
        // using the uiChildFlags_FrameStyle flag for stylistic changes + displaying a label.
        // You may be tempted to simply use BeginChild() directly. However note that BeginChild() requires EndChild()
        // to always be called (inconsistent with BeginListBox()/EndListBox()).

        // Using the generic BeginListBox() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        static int item_selected_idx = 0; // Here we store our selected data as an index.

        static bool item_highlight = false;
        int item_highlighted_idx = -1; // Here we store our highlighted data as an index.
        UI::Checkbox("Highlight hovered item in second listbox", &item_highlight);

        if (UI::BeginListBox("listbox 1"))
        {
            for (int n = 0; n < IM_COUNTOF(items); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                if (UI::Selectable(items[n], is_selected))
                    item_selected_idx = n;

                if (item_highlight && UI::IsItemHovered())
                    item_highlighted_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    UI::SetItemDefaultFocus();
            }
            UI::EndListBox();
        }
        UI::SameLine(); HelpMarker("Here we are sharing selection state between both boxes.");

        // Custom size: use all width, 5 items tall
        UI::Text("Full-width:");
        if (UI::BeginListBox("##listbox 2", vec2(-FLT_MIN, 5 * UI::GetTextLineHeightWithSpacing())))
        {
            for (int n = 0; n < IM_COUNTOF(items); n++)
            {
                bool is_selected = (item_selected_idx == n);
                uiSelectFlags flags = (item_highlighted_idx == n) ? uiSelectFlags_Highlight : 0;
                if (UI::Selectable(items[n], is_selected, flags))
                    item_selected_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    UI::SetItemDefaultFocus();
            }
            UI::EndListBox();
        }

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsMultiComponents()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsMultiComponents()
{
    if (UI::TreeNode("Multi-component Widgets"))
    {
        IMGUI_DEMO_MARKER("Widgets/Multi-component Widgets");
        static float vec4f[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
        static int vec4i[4] = { 1, 5, 100, 255 };

        static uiSliderFlags flags = 0;
        UI::CheckboxFlags("uiSliderFlags_ColorMarkers", &flags, uiSliderFlags_ColorMarkers); // Only passing this to Drag/Sliders

        UI::BarrierText("2-wide");
        UI::InputFloat2("input float2", vec4f);
        UI::InputInt2("input int2", vec4i);
        UI::DragFloat2("drag float2", vec4f, 0.01f, 0.0f, 1.0f, NULL, flags);
        UI::DragInt2("drag int2", vec4i, 1, 0, 255, NULL, flags);
        UI::SliderFloat2("slider float2", vec4f, 0.0f, 1.0f, NULL, flags);
        UI::SliderInt2("slider int2", vec4i, 0, 255, NULL, flags);

        UI::BarrierText("3-wide");
        UI::InputFloat3("input float3", vec4f);
        UI::InputInt3("input int3", vec4i);
        UI::DragFloat3("drag float3", vec4f, 0.01f, 0.0f, 1.0f, NULL, flags);
        UI::DragInt3("drag int3", vec4i, 1, 0, 255, NULL, flags);
        UI::SliderFloat3("slider float3", vec4f, 0.0f, 1.0f, NULL, flags);
        UI::SliderInt3("slider int3", vec4i, 0, 255, NULL, flags);

        UI::BarrierText("4-wide");
        UI::InputFloat4("input float4", vec4f);
        UI::InputInt4("input int4", vec4i);
        UI::DragFloat4("drag float4", vec4f, 0.01f, 0.0f, 1.0f, NULL, flags);
        UI::DragInt4("drag int4", vec4i, 1, 0, 255, NULL, flags);
        UI::SliderFloat4("slider float4", vec4f, 0.0f, 1.0f, NULL, flags);
        UI::SliderInt4("slider int4", vec4i, 0, 255, NULL, flags);

        UI::BarrierText("Ranges");
        static float begin = 10, end = 90;
        static int begin_i = 100, end_i = 1000;
        UI::DragFloatRange2("range float", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%", uiSliderFlags_AlwaysClamp);
        UI::DragIntRange2("range int", &begin_i, &end_i, 5, 0, 1000, "Min: %d units", "Max: %d units");
        UI::DragIntRange2("range int (no bounds)", &begin_i, &end_i, 5, 0, 0, "Min: %d units", "Max: %d units");

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsPlotting()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsPlotting()
{
    // Plot/Graph widgets are not very good.
// Consider using a third-party library such as ImPlot: https://github.com/epezent/implot
// (see others https://github.com/ocornut/imgui/wiki/Useful-Extensions)
    if (UI::TreeNode("Plotting"))
    {
        IMGUI_DEMO_MARKER("Widgets/Plotting");
        UI::Text("Need better plotting and graphing? Consider using ImPlot:");
        UI::TextLinkOpenURL("https://github.com/epezent/implot");
        UI::Barrier();

        static bool animate = true;
        UI::Checkbox("Animate", &animate);

        // Plot as lines and plot as histogram
        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        UI::PlotLines("Frame Times", arr, IM_COUNTOF(arr));
        UI::PlotHistogram("Histogram", arr, IM_COUNTOF(arr), 0, NULL, 0.0f, 1.0f, vec2(0, 80.0f));
        //UI::SameLine(); HelpMarker("Consider using ImPlot instead!");

        // Fill an array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
        // and the sizeof() of your structure in the "stride" parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = UI::GetTime();
        while (refresh_time < UI::GetTime()) // Create data at fixed 60 Hz rate for the demo
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset + 1) % IM_COUNTOF(values);
            phase += 0.10f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int n = 0; n < IM_COUNTOF(values); n++)
                average += values[n];
            average /= (float)IM_COUNTOF(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            UI::PlotLines("Lines", values, IM_COUNTOF(values), values_offset, overlay, -1.0f, 1.0f, vec2(0, 80.0f));
        }

        // Use functions to generate output
        // FIXME: This is actually VERY awkward because current plot API only pass in indices.
        // We probably want an API passing floats and user provide sample rate/count.
        struct Funcs
        {
            static float Sin(void*, int i) { return sinf(i * 0.1f); }
            static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
        };
        static int func_type = 0, display_count = 70;
        UI::BarrierText("Functions");
        UI::SetNextItemWidth(UI::GetFontSize() * 8);
        UI::Combo("func", &func_type, "Sin\0Saw\0");
        UI::SameLine();
        UI::SliderInt("Sample count", &display_count, 1, 400);
        float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
        UI::PlotLines("Lines##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, vec2(0, 80));
        UI::PlotHistogram("Histogram##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, vec2(0, 80));

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsProgressBars()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsProgressBars()
{
    if (UI::TreeNode("Progress Bars"))
    {
        // Animate a simple progress bar
        static float progress_accum = 0.0f, progress_dir = 1.0f;
        progress_accum += progress_dir * 0.4f * UI::GetIO().DeltaTime;
        if (progress_accum >= +1.1f) { progress_accum = +1.1f; progress_dir *= -1.0f; }
        if (progress_accum <= -0.1f) { progress_accum = -0.1f; progress_dir *= -1.0f; }

        const float progress = IM_CLAMP(progress_accum, 0.0f, 1.0f);

        // Typically we would use vec2(-1.0f,0.0f) or vec2(-FLT_MIN,0.0f) to use all available width,
        // or vec2(width,0.0f) for a specified width. vec2(0.0f,0.0f) uses ItemWidth.
        UI::ProgressBar(progress, vec2(0.0f, 0.0f));
        UI::SameLine(0.0f, UI::GetStyle().ItemInnerSpacing.x);
        UI::Text("Progress Bar");

        char buf[32];
        sprintf(buf, "%d/%d", (int)(progress * 1753), 1753);
        UI::ProgressBar(progress, vec2(0.f, 0.f), buf);

        // Pass an animated negative value, e.g. -1.0f * (float)UI::GetTime() is the recommended value.
        // Adjust the factor if you want to adjust the animation speed.
        UI::ProgressBar(-1.0f * (float)UI::GetTime(), vec2(0.0f, 0.0f), "Searching..");
        UI::SameLine(0.0f, UI::GetStyle().ItemInnerSpacing.x);
        UI::Text("Indeterminate");

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsQueryingStatuses()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsQueryingStatuses()
{
    if (UI::TreeNode("Querying Item Status (Edited/Active/Hovered etc.)"))
    {
        IMGUI_DEMO_MARKER("Widgets/Querying Item Status (Edited,Active,Hovered etc.)");
        // Select an item type
        const char* item_names[] =
        {
            "Text", "Button", "Button (w/ repeat)", "Checkbox", "SliderFloat", "InputText", "InputTextMultiline", "InputFloat",
            "InputFloat3", "ColorEdit4", "Selectable", "MenuItem", "TreeNode", "TreeNode (w/ double-click)", "Combo", "ListBox"
        };
        static int item_type = 4;
        static bool item_disabled = false;
        UI::Combo("Item Type", &item_type, item_names, IM_COUNTOF(item_names), IM_COUNTOF(item_names));
        UI::SameLine();
        HelpMarker("Testing how various types of items are interacting with the IsItemXXX functions. Note that the bool return value of most ImGui function is generally equivalent to calling UI::IsItemHovered().");
        UI::Checkbox("Item Disabled", &item_disabled);

        // Submit selected items so we can query their status in the code following it.
        bool ret = false;
        static bool b = false;
        static float col4f[4] = { 1.0f, 0.5, 0.0f, 1.0f };
        static char str[16] = {};
        if (item_disabled)
            UI::BeginDisabled(true);
        if (item_type == 0) { UI::Text("ITEM: Text"); }                                              // Testing text items with no identifier/interaction
        if (item_type == 1) { ret = UI::Button("ITEM: Button"); }                                    // Testing button
        if (item_type == 2) { UI::PushItemFlag(uiItemFlags_ButtonRepeat, true); ret = UI::Button("ITEM: Button"); UI::PopItemFlag(); } // Testing button (with repeater)
        if (item_type == 3) { ret = UI::Checkbox("ITEM: Checkbox", &b); }                            // Testing checkbox
        if (item_type == 4) { ret = UI::SliderFloat("ITEM: SliderFloat", &col4f[0], 0.0f, 1.0f); }   // Testing basic item
        if (item_type == 5) { ret = UI::InputText("ITEM: InputText", &str[0], IM_COUNTOF(str)); }  // Testing input text (which handles tabbing)
        if (item_type == 6) { ret = UI::InputTextMultiline("ITEM: InputTextMultiline", &str[0], IM_COUNTOF(str)); } // Testing input text (which uses a child window)
        if (item_type == 7) { ret = UI::InputFloat("ITEM: InputFloat", col4f, 1.0f); }               // Testing +/- buttons on scalar input
        if (item_type == 8) { ret = UI::InputFloat3("ITEM: InputFloat3", col4f); }                   // Testing multi-component items (IsItemXXX flags are reported merged)
        if (item_type == 9) { ret = UI::ColorEdit4("ITEM: ColorEdit4", col4f); }                     // Testing multi-component items (IsItemXXX flags are reported merged)
        if (item_type == 10) { ret = UI::Selectable("ITEM: Selectable"); }                            // Testing selectable item
        if (item_type == 11) { ret = UI::MenuItem("ITEM: MenuItem"); }                                // Testing menu item (they use uiButtonFlags_PressedOnRelease button policy)
        if (item_type == 12) { ret = UI::TreeNode("ITEM: TreeNode"); if (ret) UI::TreePop(); }     // Testing tree node
        if (item_type == 13) { ret = UI::TreeNodeEx("ITEM: TreeNode w/ uiTreeFlags_OpenOnDoubleClick", uiTreeFlags_OpenOnDoubleClick | uiTreeFlags_NoTreePushOnOpen); } // Testing tree node with uiButtonFlags_PressedOnDoubleClick button policy.
        if (item_type == 14) { const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi" }; static int current = 1; ret = UI::Combo("ITEM: Combo", &current, items, IM_COUNTOF(items)); }
        if (item_type == 15) { const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi" }; static int current = 1; ret = UI::ListBox("ITEM: ListBox", &current, items, IM_COUNTOF(items), IM_COUNTOF(items)); }

        bool hovered_delay_none = UI::IsItemHovered();
        bool hovered_delay_stationary = UI::IsItemHovered(uiHoverFlags_Stationary);
        bool hovered_delay_short = UI::IsItemHovered(uiHoverFlags_Delay);
        bool hovered_delay_tooltip = UI::IsItemHovered(uiHoverFlags_ForTooltip); // = Normal + Stationary

        // Display the values of IsItemHovered() and other common item state functions.
        // Note that the uiHoverFlags_XXX flags can be combined.
        // Because BulletText is an item itself and that would affect the output of IsItemXXX functions,
        // we query every state in a single call to avoid storing them and to simplify the code.
        UI::BulletText(
            "Return value = %d\n"
            "IsItemFocused() = %d\n"
            "IsItemHovered() = %d\n"
            "IsItemHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsItemHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsItemHovered(_AllowWhenOverlappedByItem) = %d\n"
            "IsItemHovered(_AllowWhenOverlappedByWindow) = %d\n"
            "IsItemHovered(_AllowWhenDisabled) = %d\n"
            "IsItemHovered(_RectOnly) = %d\n"
            "IsItemActive() = %d\n"
            "IsItemEdited() = %d\n"
            "IsItemActivated() = %d\n"
            "IsItemDeactivated() = %d\n"
            "IsItemDeactivatedAfterEdit() = %d\n"
            "IsItemVisible() = %d\n"
            "IsItemClicked() = %d\n"
            "IsItemToggledOpen() = %d\n"
            "GetItemRectMin() = (%.1f, %.1f)\n"
            "GetItemRectMax() = (%.1f, %.1f)\n"
            "GetItemRectSize() = (%.1f, %.1f)",
            ret,
            UI::IsItemFocused(),
            UI::IsItemHovered(),
            UI::IsItemHovered(uiHoverFlags_AllowWhenBlockedByPopup),
            UI::IsItemHovered(uiHoverFlags_AllowWhenBlockedByActiveItem),
            UI::IsItemHovered(uiHoverFlags_AllowWhenOverlappedByItem),
            UI::IsItemHovered(uiHoverFlags_AllowWhenOverlappedByWindow),
            UI::IsItemHovered(uiHoverFlags_AllowWhenDisabled),
            UI::IsItemHovered(uiHoverFlags_RectOnly),
            UI::IsItemActive(),
            UI::IsItemEdited(),
            UI::IsItemActivated(),
            UI::IsItemDeactivated(),
            UI::IsItemDeactivatedAfterEdit(),
            UI::IsItemVisible(),
            UI::IsItemClicked(),
            UI::IsItemToggledOpen(),
            UI::GetItemRectMin().x, UI::GetItemRectMin().y,
            UI::GetItemRectMax().x, UI::GetItemRectMax().y,
            UI::GetItemRectSize().x, UI::GetItemRectSize().y
        );
        UI::BulletText(
            "with Hovering Delay or Stationary test:\n"
            "IsItemHovered() = %d\n"
            "IsItemHovered(_Stationary) = %d\n"
            "IsItemHovered(_DelayShort) = %d\n"
            "IsItemHovered(_DelayNormal) = %d\n"
            "IsItemHovered(_Tooltip) = %d",
            hovered_delay_none, hovered_delay_stationary, hovered_delay_short, hovered_delay_tooltip);

        if (item_disabled)
            UI::EndDisabled();

        char buf[1] = "";
        UI::InputText("unused", buf, IM_COUNTOF(buf), uiInputTextFlags_ReadOnly);
        UI::SameLine();
        HelpMarker("This widget is only here to be able to tab-out of the widgets above and see e.g. Deactivated() status.");

        UI::TreePop();
    }

    if (UI::TreeNode("Querying Window Status (Focused/Hovered etc.)"))
    {
        IMGUI_DEMO_MARKER("Widgets/Querying Window Status (Focused,Hovered etc.)");
        static bool embed_all_inside_a_child_window = false;
        UI::Checkbox("Embed everything inside a child window for testing _RootWindow flag.", &embed_all_inside_a_child_window);
        if (embed_all_inside_a_child_window)
            UI::BeginChild("outer_child", vec2(0, UI::GetFontSize() * 20.0f), uiChildFlags_Borders);

        // Testing IsWindowFocused() function with its various flags.
        UI::BulletText(
            "IsWindowFocused() = %d\n"
            "IsWindowFocused(_ChildWindows) = %d\n"
            "IsWindowFocused(_ChildWindows|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_ChildWindows|_DockHierarchy) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowFocused(_RootWindow) = %d\n"
            "IsWindowFocused(_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowFocused(_AnyWindow) = %d\n",
            UI::IsWindowFocused(),
            UI::IsWindowFocused(uiFocusFlags_ChildWindows),
            UI::IsWindowFocused(uiFocusFlags_ChildWindows | uiFocusFlags_NoPopupHierarchy),
            UI::IsWindowFocused(uiFocusFlags_ChildWindows | uiFocusFlags_DockHierarchy),
            UI::IsWindowFocused(uiFocusFlags_ChildWindows | uiFocusFlags_RootWindow),
            UI::IsWindowFocused(uiFocusFlags_ChildWindows | uiFocusFlags_RootWindow | uiFocusFlags_NoPopupHierarchy),
            UI::IsWindowFocused(uiFocusFlags_ChildWindows | uiFocusFlags_RootWindow | uiFocusFlags_DockHierarchy),
            UI::IsWindowFocused(uiFocusFlags_RootWindow),
            UI::IsWindowFocused(uiFocusFlags_RootWindow | uiFocusFlags_NoPopupHierarchy),
            UI::IsWindowFocused(uiFocusFlags_RootWindow | uiFocusFlags_DockHierarchy),
            UI::IsWindowFocused(uiFocusFlags_AnyWindow));

        // Testing IsWindowHovered() function with its various flags.
        UI::BulletText(
            "IsWindowHovered() = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsWindowHovered(_ChildWindows) = %d\n"
            "IsWindowHovered(_ChildWindows|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_DockHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowHovered(_RootWindow) = %d\n"
            "IsWindowHovered(_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_AnyWindow) = %d\n"
            "IsWindowHovered(_Stationary) = %d\n",
            UI::IsWindowHovered(),
            UI::IsWindowHovered(uiHoverFlags_AllowWhenBlockedByPopup),
            UI::IsWindowHovered(uiHoverFlags_AllowWhenBlockedByActiveItem),
            UI::IsWindowHovered(uiHoverFlags_ChildWindows),
            UI::IsWindowHovered(uiHoverFlags_ChildWindows | uiHoverFlags_NoPopupHierarchy),
            UI::IsWindowHovered(uiHoverFlags_ChildWindows | uiHoverFlags_DockHierarchy),
            UI::IsWindowHovered(uiHoverFlags_ChildWindows | uiHoverFlags_RootWindow),
            UI::IsWindowHovered(uiHoverFlags_ChildWindows | uiHoverFlags_RootWindow | uiHoverFlags_NoPopupHierarchy),
            UI::IsWindowHovered(uiHoverFlags_ChildWindows | uiHoverFlags_RootWindow | uiHoverFlags_DockHierarchy),
            UI::IsWindowHovered(uiHoverFlags_RootWindow),
            UI::IsWindowHovered(uiHoverFlags_RootWindow | uiHoverFlags_NoPopupHierarchy),
            UI::IsWindowHovered(uiHoverFlags_RootWindow | uiHoverFlags_DockHierarchy),
            UI::IsWindowHovered(uiHoverFlags_ChildWindows | uiHoverFlags_AllowWhenBlockedByPopup),
            UI::IsWindowHovered(uiHoverFlags_AnyWindow),
            UI::IsWindowHovered(uiHoverFlags_Stationary));

        UI::BeginChild("child", vec2(0, 50), uiChildFlags_Borders);
        UI::Text("This is another child window for testing the _ChildWindows flag.");
        UI::EndChild();
        if (embed_all_inside_a_child_window)
            UI::EndChild();

        // Calling IsItemHovered() after begin returns the hovered status of the title bar.
        // This is useful in particular if you want to create a context menu associated to the title bar of a window.
        // This will also work when docked into a Tab (the Tab replace the Title Bar and guarantee the same properties).
        static bool test_window = false;
        UI::Checkbox("Hovered/Active tests after Begin() for title bar testing", &test_window);
        if (test_window)
        {
            // FIXME-DOCK: This window cannot be docked within the ImGui Demo window, this will cause a feedback loop and get them stuck.
            // Could we fix this through an uiWindowClass feature? Or an API call to tag our parent as "don't skip items"?
            UI::Begin("Title bar Hovered/Active tests", &test_window);
            if (UI::BeginPopupContextItem()) // <-- This is using IsItemHovered()
            {
                if (UI::MenuItem("Close")) { test_window = false; }
                UI::EndPopup();
            }
            UI::Text(
                "IsItemHovered() after begin = %d (== is title bar hovered)\n"
                "IsItemActive() after begin = %d (== is window being clicked/moved)\n",
                UI::IsItemHovered(), UI::IsItemActive());
            UI::End();
        }

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsSelectables()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsSelectables()
{
    //UI::SetNextItemOpen(true, uiCond_Once);
    if (UI::TreeNode("Selectables"))
    {
        IMGUI_DEMO_MARKER("Widgets/Selectables");
        // Selectable() has 2 overloads:
        // - The one taking "bool selected" as a read-only selection information.
        //   When Selectable() has been clicked it returns true and you can alter selection state accordingly.
        // - The one taking "bool* p_selected" as a read-write selection information (convenient in some cases)
        // The earlier is more flexible, as in real application your selection may be stored in many different ways
        // and not necessarily inside a bool value (e.g. in flags within objects, as an external list, etc).
        IMGUI_DEMO_MARKER("Widgets/Selectables/Basic");
        if (UI::TreeNode("Basic"))
        {
            static bool selection[5] = { false, true, false, false };
            UI::Selectable("1. I am selectable", &selection[0]);
            UI::Selectable("2. I am selectable", &selection[1]);
            UI::Selectable("3. I am selectable", &selection[2]);
            if (UI::Selectable("4. I am double clickable", selection[3], uiSelectFlags_AllowDoubleClick))
                if (UI::IsMouseDoubleClicked(0))
                    selection[3] = !selection[3];
            UI::TreePop();
        }

        IMGUI_DEMO_MARKER("Widgets/Selectables/Rendering more items on the same line");
        if (UI::TreeNode("Multiple items on the same line"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/Multiple items on the same line");
            // - Using SetNextItemAllowOverlap()
            // - Using the Selectable() override that takes "bool* p_selected" parameter, the bool value is toggled automatically.
            {
                static bool selected[3] = {};
                UI::SetNextItemAllowOverlap(); UI::Selectable("main.c", &selected[0]); UI::SameLine(); UI::SmallButton("Link 1");
                UI::SetNextItemAllowOverlap(); UI::Selectable("hello.cpp", &selected[1]); UI::SameLine(); UI::SmallButton("Link 2");
                UI::SetNextItemAllowOverlap(); UI::Selectable("hello.h", &selected[2]); UI::SameLine(); UI::SmallButton("Link 3");
            }

            // (2)
            // - Using uiSelectFlags_AllowOverlap is a shortcut for calling SetNextItemAllowOverlap()
            // - No visible label, display contents inside the selectable bounds.
            // - We don't maintain actual selection in this example to keep things simple.
            UI::Spacing();
            {
                static bool checked[5] = {};
                static int selected_n = 0;
                const float color_marker_w = UI::CalcTextSize("x").x;
                for (int n = 0; n < 5; n++)
                {
                    UI::PushID(n);
                    UI::AlignTextToFramePadding();
                    if (UI::Selectable("##selectable", selected_n == n, uiSelectFlags_AllowOverlap))
                        selected_n = n;
                    UI::SameLine(0, 0);
                    UI::Checkbox("##check", &checked[n]);
                    UI::SameLine();
                    vec4 color((n & 1) ? 1.0f : 0.2f, (n & 2) ? 1.0f : 0.2f, 0.2f, 1.0f);
                    UI::ColorButton("##color", color, uiColorEditFlags_NoTooltip, vec2(color_marker_w, 0));
                    UI::SameLine();
                    UI::Text("Some label");
                    UI::PopID();
                }
            }

            UI::TreePop();
        }

        if (UI::TreeNode("In Tables"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/In Tables");
            static bool selected[10] = {};

            if (UI::BeginTable("split1", 3, uiTableFlags_Resizable | uiTableFlags_NoSavedSettings | uiTableFlags_Borders))
            {
                for (int i = 0; i < 10; i++)
                {
                    char label[32];
                    sprintf(label, "Item %d", i);
                    UI::TableNextColumn();
                    UI::Selectable(label, &selected[i]); // FIXME-TABLE: Selection overlap
                }
                UI::EndTable();
            }
            UI::Spacing();
            if (UI::BeginTable("split2", 3, uiTableFlags_Resizable | uiTableFlags_NoSavedSettings | uiTableFlags_Borders))
            {
                for (int i = 0; i < 10; i++)
                {
                    char label[32];
                    sprintf(label, "Item %d", i);
                    UI::TableNextRow();
                    UI::TableNextColumn();
                    UI::Selectable(label, &selected[i], uiSelectFlags_SpanAllColumns);
                    UI::TableNextColumn();
                    UI::Text("Some other contents");
                    UI::TableNextColumn();
                    UI::Text("123456");
                }
                UI::EndTable();
            }
            UI::TreePop();
        }

        if (UI::TreeNode("Grid"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/Grid");
            static char selected[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

            // Add in a bit of silly fun...
            const float time = (float)UI::GetTime();
            const bool winning_state = memchr(selected, 0, sizeof(selected)) == NULL; // If all cells are selected...
            if (winning_state)
                UI::PushStyleVar(uiStyleVar_SelectableTextAlign, vec2(0.5f + 0.5f * cosf(time * 2.0f), 0.5f + 0.5f * sinf(time * 3.0f)));

            const float size = UI::CalcTextSize("Sailor").x;
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++)
                {
                    if (x > 0)
                        UI::SameLine();
                    UI::PushID(y * 4 + x);
                    if (UI::Selectable("Sailor", selected[y][x] != 0, 0, vec2(size, size)))
                    {
                        // Toggle clicked cell + toggle neighbors
                        selected[y][x] ^= 1;
                        if (x > 0) { selected[y][x - 1] ^= 1; }
                        if (x < 3) { selected[y][x + 1] ^= 1; }
                        if (y > 0) { selected[y - 1][x] ^= 1; }
                        if (y < 3) { selected[y + 1][x] ^= 1; }
                    }
                    UI::PopID();
                }

            if (winning_state)
                UI::PopStyleVar();
            UI::TreePop();
        }
        if (UI::TreeNode("Alignment"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/Alignment");
            HelpMarker(
                "By default, Selectables uses style.SelectableTextAlign but it can be overridden on a per-item "
                "basis using PushStyleVar(). You'll probably want to always keep your default situation to "
                "left-align otherwise it becomes difficult to layout multiple items on a same line");

            static bool selected[3 * 3] = { true, false, true, false, true, false, true, false, true };
            const float size = UI::CalcTextSize("(1.0,1.0)").x;
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    vec2 alignment = vec2((float)x / 2.0f, (float)y / 2.0f);
                    char name[32];
                    sprintf(name, "(%.1f,%.1f)", alignment.x, alignment.y);
                    if (x > 0) UI::SameLine();
                    UI::PushStyleVar(uiStyleVar_SelectableTextAlign, alignment);
                    UI::Selectable(name, &selected[3 * y + x], uiSelectFlags_None, vec2(size, size));
                    UI::PopStyleVar();
                }
            }
            UI::TreePop();
        }
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsSelectionAndMultiSelect()
//-----------------------------------------------------------------------------
// Multi-selection demos
// Also read: https://github.com/ocornut/imgui/wiki/Multi-Select
//-----------------------------------------------------------------------------

static const char* ExampleNames[] =
{
    "Artichoke", "Arugula", "Asparagus", "Avocado", "Bamboo Shoots", "Bean Sprouts", "Beans", "Beet", "Belgian Endive", "Bell Pepper",
    "Bitter Gourd", "Bok Choy", "Broccoli", "Brussels Sprouts", "Burdock Root", "Cabbage", "Calabash", "Capers", "Carrot", "Cassava",
    "Cauliflower", "Celery", "Celery Root", "Celcuce", "Chayote", "Chinese Broccoli", "Corn", "Cucumber"
};

// Extra functions to add deletion support to uiSelectionBasicStorage
struct ExampleSelectionWithDeletion : uiSelectionBasicStorage
{
    // Find which item should be Focused after deletion.
    // Call _before_ item submission. Return an index in the before-deletion item list, your item loop should call SetKeyboardFocusHere() on it.
    // The subsequent ApplyDeletionPostLoop() code will use it to apply Selection.
    // - We cannot provide this logic in core Dear ImGui because we don't have access to selection data.
    // - We don't actually manipulate the ImVector<> here, only in ApplyDeletionPostLoop(), but using similar API for consistency and flexibility.
    // - Important: Deletion only works if the underlying uiID for your items are stable: aka not depend on their index, but on e.g. item id/ptr.
    // FIXME-MULTISELECT: Doesn't take account of the possibility focus target will be moved during deletion. Need refocus or scroll offset.
    int ApplyDeletionPreLoop(uiMultiSelectIO* ms_io, int items_count)
    {
        if (Size == 0)
            return -1;

        // If focused item is not selected...
        const int focused_idx = (int)ms_io->NavIdItem;  // Index of currently focused item
        if (ms_io->NavIdSelected == false)  // This is merely a shortcut, == Contains(adapter->IndexToStorage(items, focused_idx))
        {
            ms_io->RangeSrcReset = true;    // Request to recover RangeSrc from NavId next frame. Would be ok to reset even when NavIdSelected==true, but it would take an extra frame to recover RangeSrc when deleting a selected item.
            return focused_idx;             // Request to focus same item after deletion.
        }

        // If focused item is selected: land on first unselected item after focused item.
        for (int idx = focused_idx + 1; idx < items_count; idx++)
            if (!Contains(GetStorageIdFromIndex(idx)))
                return idx;

        // If focused item is selected: otherwise return last unselected item before focused item.
        for (int idx = IM_MIN(focused_idx, items_count) - 1; idx >= 0; idx--)
            if (!Contains(GetStorageIdFromIndex(idx)))
                return idx;

        return -1;
    }

    // Rewrite item list (delete items) + update selection.
    // - Call after EndMultiSelect()
    // - We cannot provide this logic in core Dear ImGui because we don't have access to your items, nor to selection data.
    template<typename ITEM_TYPE>
    void ApplyDeletionPostLoop(uiMultiSelectIO* ms_io, ImVector<ITEM_TYPE>& items, int item_curr_idx_to_select)
    {
        // Rewrite item list (delete items) + convert old selection index (before deletion) to new selection index (after selection).
        // If NavId was not part of selection, we will stay on same item.
        ImVector<ITEM_TYPE> new_items;
        new_items.reserve(items.Size - Size);
        int item_next_idx_to_select = -1;
        for (int idx = 0; idx < items.Size; idx++)
        {
            if (!Contains(GetStorageIdFromIndex(idx)))
                new_items.push_back(items[idx]);
            if (item_curr_idx_to_select == idx)
                item_next_idx_to_select = new_items.Size - 1;
        }
        items.swap(new_items);

        // Update selection
        Clear();
        if (item_next_idx_to_select != -1 && ms_io->NavIdSelected)
            SetItemSelected(GetStorageIdFromIndex(item_next_idx_to_select), true);
    }
};

// Example: Implement dual list box storage and interface
struct ExampleDualListBox
{
    ImVector<uiID>           Items[2];               // ID is index into ExampleName[]
    uiSelectionBasicStorage  Selections[2];          // Store ExampleItemId into selection
    bool                        OptKeepSorted = true;

    void MoveAll(int src, int dst)
    {
        IM_ASSERT((src == 0 && dst == 1) || (src == 1 && dst == 0));
        for (uiID item_id : Items[src])
            Items[dst].push_back(item_id);
        Items[src].clear();
        SortItems(dst);
        Selections[src].Swap(Selections[dst]);
        Selections[src].Clear();
    }
    void MoveSelected(int src, int dst)
    {
        for (int src_n = 0; src_n < Items[src].Size; src_n++)
        {
            uiID item_id = Items[src][src_n];
            if (!Selections[src].Contains(item_id))
                continue;
            Items[src].erase(&Items[src][src_n]); // FIXME-OPT: Could be implemented more optimally (rebuild src items and swap)
            Items[dst].push_back(item_id);
            src_n--;
        }
        if (OptKeepSorted)
            SortItems(dst);
        Selections[src].Swap(Selections[dst]);
        Selections[src].Clear();
    }
    void ApplySelectionRequests(uiMultiSelectIO* ms_io, int side)
    {
        // In this example we store item id in selection (instead of item index)
        Selections[side].UserData = Items[side].Data;
        Selections[side].AdapterIndexToStorageId = [](uiSelectionBasicStorage* self, int idx) { uiID* items = (uiID*)self->UserData; return items[idx]; };
        Selections[side].ApplyRequests(ms_io);
    }
    static int IMGUI_CDECL CompareItemsByValue(const void* lhs, const void* rhs)
    {
        const int* a = (const int*)lhs;
        const int* b = (const int*)rhs;
        return *a - *b;
    }
    void SortItems(int n)
    {
        qsort(Items[n].Data, (size_t)Items[n].Size, sizeof(Items[n][0]), CompareItemsByValue);
    }
    void Show()
    {
        //if (UI::Checkbox("Sorted", &OptKeepSorted) && OptKeepSorted) { SortItems(0); SortItems(1); }
        if (UI::BeginTable("split", 3, uiTableFlags_None))
        {
            UI::TableSetupColumn("", uiTableColumnFlags_WidthStretch);    // Left side
            UI::TableSetupColumn("", uiTableColumnFlags_WidthFixed);      // Buttons
            UI::TableSetupColumn("", uiTableColumnFlags_WidthStretch);    // Right side
            UI::TableNextRow();

            int request_move_selected = -1;
            int request_move_all = -1;
            float child_height_0 = 0.0f;
            for (int side = 0; side < 2; side++)
            {
                // FIXME-MULTISELECT: Dual List Box: Add context menus
                // FIXME-NAV: Using uiWindowFlags_NavFlattened exhibit many issues.
                ImVector<uiID>& items = Items[side];
                uiSelectionBasicStorage& selection = Selections[side];

                UI::TableSetColumnIndex((side == 0) ? 0 : 2);
                UI::Text("%s (%d)", (side == 0) ? "Available" : "Basket", items.Size);

                // Submit scrolling range to avoid glitches on moving/deletion
                const float items_height = UI::GetTextLineHeightWithSpacing();
                UI::SetNextWindowContentSize(vec2(0.0f, items.Size * items_height));

                bool child_visible;
                if (side == 0)
                {
                    // Left child is resizable
                    UI::SetNextWindowSizeConstraints(vec2(0.0f, UI::GetFrameHeightWithSpacing() * 4), vec2(FLT_MAX, FLT_MAX));
                    child_visible = UI::BeginChild("0", vec2(-FLT_MIN, UI::GetFontSize() * 20), uiChildFlags_FrameStyle | uiChildFlags_ResizeY);
                    child_height_0 = UI::GetWindowSize().y;
                }
                else
                {
                    // Right child use same height as left one
                    child_visible = UI::BeginChild("1", vec2(-FLT_MIN, child_height_0), uiChildFlags_FrameStyle);
                }
                if (child_visible)
                {
                    uiMultiSelectFlags flags = uiMultiSelectFlags_BoxSelect1d;
                    uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, selection.Size, items.Size);
                    ApplySelectionRequests(ms_io, side);

                    for (int item_n = 0; item_n < items.Size; item_n++)
                    {
                        uiID item_id = items[item_n];
                        bool item_is_selected = selection.Contains(item_id);
                        UI::SetNextItemSelectionUserData(item_n);
                        UI::Selectable(ExampleNames[item_id], item_is_selected, uiSelectFlags_AllowDoubleClick);
                        if (UI::IsItemFocused())
                        {
                            // FIXME-MULTISELECT: Dual List Box: Transfer focus
                            if (UI::IsKeyPressed(uiKey_Enter) || UI::IsKeyPressed(uiKey_KeypadEnter))
                                request_move_selected = side;
                            if (UI::IsMouseDoubleClicked(0)) // FIXME-MULTISELECT: Double-click on multi-selection?
                                request_move_selected = side;
                        }
                    }

                    ms_io = UI::EndMultiSelect();
                    ApplySelectionRequests(ms_io, side);
                }
                UI::EndChild();
            }

            // Buttons columns
            UI::TableSetColumnIndex(1);
            UI::NewLine();
            //vec2 button_sz = { UI::CalcTextSize(">>").x + UI::GetStyle().FramePadding.x * 2.0f, UI::GetFrameHeight() + padding.y * 2.0f };
            vec2 button_sz = { UI::GetFrameHeight(), UI::GetFrameHeight() };

            // (Using BeginDisabled()/EndDisabled() works but feels distracting given how it is currently visualized)
            if (UI::Button(">>", button_sz))
                request_move_all = 0;
            if (UI::Button(">", button_sz))
                request_move_selected = 0;
            if (UI::Button("<", button_sz))
                request_move_selected = 1;
            if (UI::Button("<<", button_sz))
                request_move_all = 1;

            // Process requests
            if (request_move_all != -1)
                MoveAll(request_move_all, request_move_all ^ 1);
            if (request_move_selected != -1)
                MoveSelected(request_move_selected, request_move_selected ^ 1);

            // FIXME-MULTISELECT: Support action from outside
            /*
            if (OptKeepSorted == false)
            {
                UI::NewLine();
                if (UI::ArrowButton("MoveUp", Var::Dir::Up)) {}
                if (UI::ArrowButton("MoveDown", Var::Dir::Down)) {}
            }
            */

            UI::EndTable();
        }
    }
};

static void DemoWindowWidgetsSelectionAndMultiSelect(uiDemoWindowData* demo_data)
{
    if (UI::TreeNode("Selection State & Multi-Select"))
    {
        IMGUI_DEMO_MARKER("Widgets/Selection State & Multi-Select");
        HelpMarker("Selections can be built using Selectable(), TreeNode() or other widgets. Selection state is owned by application code/data.");

        UI::BulletText("Wiki page:");
        UI::SameLine();
        UI::TextLinkOpenURL("imgui/wiki/Multi-Select", "https://github.com/ocornut/imgui/wiki/Multi-Select");

        // Without any fancy API: manage single-selection yourself.
        if (UI::TreeNode("Single-Select"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Single-Select");
            static int selected = -1;
            for (int n = 0; n < 5; n++)
            {
                char buf[32];
                sprintf(buf, "Object %d", n);
                if (UI::Selectable(buf, selected == n))
                    selected = n;
            }
            UI::TreePop();
        }

        // Demonstrate implementation a most-basic form of multi-selection manually
        // This doesn't support the Shift modifier which requires BeginMultiSelect()!
        if (UI::TreeNode("Multi-Select (manual/simplified, without BeginMultiSelect)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (manual/simplified, without BeginMultiSelect)");
            HelpMarker("Hold Ctrl and Click to select multiple items.");
            static bool selection[5] = { false, false, false, false, false };
            for (int n = 0; n < 5; n++)
            {
                char buf[32];
                sprintf(buf, "Object %d", n);
                if (UI::Selectable(buf, selection[n]))
                {
                    if (!UI::GetIO().KeyCtrl) // Clear selection when Ctrl is not held
                        memset(selection, 0, sizeof(selection));
                    selection[n] ^= 1; // Toggle current item
                }
            }
            UI::TreePop();
        }

        // Demonstrate handling proper multi-selection using the BeginMultiSelect/EndMultiSelect API.
        // Shift+Click w/ Ctrl and other standard features are supported.
        // We use the uiSelectionBasicStorage helper which you may freely reimplement.
        if (UI::TreeNode("Multi-Select"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select");
            UI::Text("Supported features:");
            UI::BulletText("Keyboard navigation (arrows, page up/down, home/end, space).");
            UI::BulletText("Ctrl modifier to preserve and toggle selection.");
            UI::BulletText("Shift modifier for range selection.");
            UI::BulletText("Ctrl+A to select all.");
            UI::BulletText("Escape to clear selection.");
            UI::BulletText("Click and drag to box-select.");
            UI::Text("Tip: Use 'Demo->Tools->Debug Log->Selection' to see selection requests as they happen.");

            // Use default selection.Adapter: Pass index to SetNextItemSelectionUserData(), store index in Selection
            const int ITEMS_COUNT = 50;
            static uiSelectionBasicStorage selection;
            UI::Text("Selection: %d/%d", selection.Size, ITEMS_COUNT);

            // The BeginChild() has no purpose for selection logic, other that offering a scrolling region.
            if (UI::BeginChild("##Basket", vec2(-FLT_MIN, UI::GetFontSize() * 20), uiChildFlags_FrameStyle | uiChildFlags_ResizeY))
            {
                uiMultiSelectFlags flags = uiMultiSelectFlags_ClearOnEscape | uiMultiSelectFlags_BoxSelect1d;
                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                for (int n = 0; n < ITEMS_COUNT; n++)
                {
                    char label[64];
                    sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                    bool item_is_selected = selection.Contains((uiID)n);
                    UI::SetNextItemSelectionUserData(n);
                    UI::Selectable(label, item_is_selected);
                }

                ms_io = UI::EndMultiSelect();
                selection.ApplyRequests(ms_io);
            }
            UI::EndChild();
            UI::TreePop();
        }

        // Demonstrate using the clipper with BeginMultiSelect()/EndMultiSelect()
        if (UI::TreeNode("Multi-Select (with clipper)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (with clipper)");
            // Use default selection.Adapter: Pass index to SetNextItemSelectionUserData(), store index in Selection
            static uiSelectionBasicStorage selection;

            UI::Text("Added features:");
            UI::BulletText("Using uiListClipper.");

            const int ITEMS_COUNT = 10000;
            UI::Text("Selection: %d/%d", selection.Size, ITEMS_COUNT);
            if (UI::BeginChild("##Basket", vec2(-FLT_MIN, UI::GetFontSize() * 20), uiChildFlags_FrameStyle | uiChildFlags_ResizeY))
            {
                uiMultiSelectFlags flags = uiMultiSelectFlags_ClearOnEscape | uiMultiSelectFlags_BoxSelect1d;
                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                uiListClipper clipper;
                clipper.Begin(ITEMS_COUNT);
                if (ms_io->RangeSrcItem != -1)
                    clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // Ensure RangeSrc item is not clipped.
                while (clipper.Step())
                {
                    for (int n = clipper.DisplayStart; n < clipper.DisplayEnd; n++)
                    {
                        char label[64];
                        sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                        bool item_is_selected = selection.Contains((uiID)n);
                        UI::SetNextItemSelectionUserData(n);
                        UI::Selectable(label, item_is_selected);
                    }
                }

                ms_io = UI::EndMultiSelect();
                selection.ApplyRequests(ms_io);
            }
            UI::EndChild();
            UI::TreePop();
        }

        // Demonstrate dynamic item list + deletion support using the BeginMultiSelect/EndMultiSelect API.
        // In order to support Deletion without any glitches you need to:
        // - (1) If items are submitted in their own scrolling area, submit contents size SetNextWindowContentSize() ahead of time to prevent one-frame readjustment of scrolling.
        // - (2) Items needs to have persistent ID Stack identifier = ID needs to not depends on their index. PushID(index) = KO. PushID(item_id) = OK. This is in order to focus items reliably after a selection.
        // - (3) BeginXXXX process
        // - (4) Focus process
        // - (5) EndXXXX process
        if (UI::TreeNode("Multi-Select (with deletion)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (with deletion)");
            // Storing items data separately from selection data.
            // (you may decide to store selection data inside your item (aka intrusive storage) if you don't need multiple views over same items)
            // Use a custom selection.Adapter: store item identifier in Selection (instead of index)
            static ImVector<uiID> items;
            static ExampleSelectionWithDeletion selection;
            selection.UserData = (void*)&items;
            selection.AdapterIndexToStorageId = [](uiSelectionBasicStorage* self, int idx) { ImVector<uiID>* p_items = (ImVector<uiID>*)self->UserData; return (*p_items)[idx]; }; // Index -> ID

            UI::Text("Added features:");
            UI::BulletText("Dynamic list with Delete key support.");
            UI::Text("Selection size: %d/%d", selection.Size, items.Size);

            // Initialize default list with 50 items + button to add/remove items.
            static uiID items_next_id = 0;
            if (items_next_id == 0)
                for (uiID n = 0; n < 50; n++)
                    items.push_back(items_next_id++);
            if (UI::SmallButton("Add 20 items"))     { for (int n = 0; n < 20; n++) { items.push_back(items_next_id++); } }
            UI::SameLine();
            if (UI::SmallButton("Remove 20 items"))  { for (int n = IM_MIN(20, items.Size); n > 0; n--) { selection.SetItemSelected(items.back(), false); items.pop_back(); } }

            // (1) Extra to support deletion: Submit scrolling range to avoid glitches on deletion
            const float items_height = UI::GetTextLineHeightWithSpacing();
            UI::SetNextWindowContentSize(vec2(0.0f, items.Size * items_height));

            if (UI::BeginChild("##Basket", vec2(-FLT_MIN, UI::GetFontSize() * 20), uiChildFlags_FrameStyle | uiChildFlags_ResizeY))
            {
                uiMultiSelectFlags flags = uiMultiSelectFlags_ClearOnEscape | uiMultiSelectFlags_BoxSelect1d;
                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, selection.Size, items.Size);
                selection.ApplyRequests(ms_io);

                const bool want_delete = UI::Shortcut(uiKey_Delete, uiInputFlags_Repeat) && (selection.Size > 0);
                const int item_curr_idx_to_focus = want_delete ? selection.ApplyDeletionPreLoop(ms_io, items.Size) : -1;

                for (int n = 0; n < items.Size; n++)
                {
                    const uiID item_id = items[n];
                    char label[64];
                    sprintf(label, "Object %05u: %s", item_id, ExampleNames[item_id % IM_COUNTOF(ExampleNames)]);

                    bool item_is_selected = selection.Contains(item_id);
                    UI::SetNextItemSelectionUserData(n);
                    UI::Selectable(label, item_is_selected);
                    if (item_curr_idx_to_focus == n)
                        UI::SetKeyboardFocusHere(-1);
                }

                // Apply multi-select requests
                ms_io = UI::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                if (want_delete)
                    selection.ApplyDeletionPostLoop(ms_io, items, item_curr_idx_to_focus);
            }
            UI::EndChild();
            UI::TreePop();
        }

        // Implement a Dual List Box (#6648)
        if (UI::TreeNode("Multi-Select (dual list box)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (dual list box)");
            // Init default state
            static ExampleDualListBox dlb;
            if (dlb.Items[0].Size == 0 && dlb.Items[1].Size == 0)
                for (int item_id = 0; item_id < IM_COUNTOF(ExampleNames); item_id++)
                    dlb.Items[0].push_back((uiID)item_id);

            // Show
            dlb.Show();

            UI::TreePop();
        }

        // Demonstrate using the clipper with BeginMultiSelect()/EndMultiSelect()
        if (UI::TreeNode("Multi-Select (in a table)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (in a table)");
            static uiSelectionBasicStorage selection;

            const int ITEMS_COUNT = 10000;
            UI::Text("Selection: %d/%d", selection.Size, ITEMS_COUNT);
            if (UI::BeginTable("##Basket", 2, uiTableFlags_ScrollY | uiTableFlags_RowBg | uiTableFlags_BordersOuter, vec2(0.0f, UI::GetFontSize() * 20)))
            {
                UI::TableSetupColumn("Object");
                UI::TableSetupColumn("Action");
                UI::TableSetupScrollFreeze(0, 1);
                UI::TableHeadersRow();

                uiMultiSelectFlags flags = uiMultiSelectFlags_ClearOnEscape | uiMultiSelectFlags_BoxSelect1d;
                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                uiListClipper clipper;
                clipper.Begin(ITEMS_COUNT);
                if (ms_io->RangeSrcItem != -1)
                    clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // Ensure RangeSrc item is not clipped.
                while (clipper.Step())
                {
                    for (int n = clipper.DisplayStart; n < clipper.DisplayEnd; n++)
                    {
                        UI::TableNextRow();
                        UI::TableNextColumn();
                        UI::PushID(n);
                        char label[64];
                        sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                        bool item_is_selected = selection.Contains((uiID)n);
                        UI::SetNextItemSelectionUserData(n);
                        UI::Selectable(label, item_is_selected, uiSelectFlags_SpanAllColumns | uiSelectFlags_AllowOverlap);
                        UI::TableNextColumn();
                        UI::SmallButton("hello");
                        UI::PopID();
                    }
                }

                ms_io = UI::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                UI::EndTable();
            }
            UI::TreePop();
        }

        if (UI::TreeNode("Multi-Select (checkboxes)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (checkboxes)");
            UI::Text("In a list of checkboxes (not selectable):");
            UI::BulletText("Using _NoAutoSelect + _NoAutoClear flags.");
            UI::BulletText("Shift+Click to check multiple boxes.");
            UI::BulletText("Shift+Keyboard to copy current value to other boxes.");

            // If you have an array of checkboxes, you may want to use NoAutoSelect + NoAutoClear and the uiSelectionExternalStorage helper.
            static bool items[20] = {};
            static uiMultiSelectFlags flags = uiMultiSelectFlags_NoAutoSelect | uiMultiSelectFlags_NoAutoClear | uiMultiSelectFlags_ClearOnEscape;
            UI::CheckboxFlags("uiMultiSelectFlags_NoAutoSelect", &flags, uiMultiSelectFlags_NoAutoSelect);
            UI::CheckboxFlags("uiMultiSelectFlags_NoAutoClear", &flags, uiMultiSelectFlags_NoAutoClear);
            UI::CheckboxFlags("uiMultiSelectFlags_BoxSelect2d", &flags, uiMultiSelectFlags_BoxSelect2d); // Cannot use uiMultiSelectFlags_BoxSelect1d as checkboxes are varying width.

            if (UI::BeginChild("##Basket", vec2(-FLT_MIN, UI::GetFontSize() * 20), uiChildFlags_Borders | uiChildFlags_ResizeY))
            {
                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, -1, IM_COUNTOF(items));
                uiSelectionExternalStorage storage_wrapper;
                storage_wrapper.UserData = (void*)items;
                storage_wrapper.AdapterSetItemSelected = [](uiSelectionExternalStorage* self, int n, bool selected) { bool* array = (bool*)self->UserData; array[n] = selected; };
                storage_wrapper.ApplyRequests(ms_io);
                for (int n = 0; n < 20; n++)
                {
                    char label[32];
                    sprintf(label, "Item %d", n);
                    UI::SetNextItemSelectionUserData(n);
                    UI::Checkbox(label, &items[n]);
                }
                ms_io = UI::EndMultiSelect();
                storage_wrapper.ApplyRequests(ms_io);
            }
            UI::EndChild();

            UI::TreePop();
        }

        // Demonstrate individual selection scopes in same window
        if (UI::TreeNode("Multi-Select (multiple scopes)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (multiple scopes)");
            // Use default select: Pass index to SetNextItemSelectionUserData(), store index in Selection
            const int SCOPES_COUNT = 3;
            const int ITEMS_COUNT = 8; // Per scope
            static uiSelectionBasicStorage selections_data[SCOPES_COUNT];

            // Use uiMultiSelectFlags_ScopeRect to not affect other selections in same window.
            static uiMultiSelectFlags flags = uiMultiSelectFlags_ScopeRect | uiMultiSelectFlags_ClearOnEscape;// | uiMultiSelectFlags_ClearOnClickVoid;
            if (UI::CheckboxFlags("uiMultiSelectFlags_ScopeWindow", &flags, uiMultiSelectFlags_ScopeWindow) && (flags & uiMultiSelectFlags_ScopeWindow))
                flags &= ~uiMultiSelectFlags_ScopeRect;
            if (UI::CheckboxFlags("uiMultiSelectFlags_ScopeRect", &flags, uiMultiSelectFlags_ScopeRect) && (flags & uiMultiSelectFlags_ScopeRect))
                flags &= ~uiMultiSelectFlags_ScopeWindow;
            UI::CheckboxFlags("uiMultiSelectFlags_ClearOnClickVoid", &flags, uiMultiSelectFlags_ClearOnClickVoid);
            UI::CheckboxFlags("uiMultiSelectFlags_BoxSelect1d", &flags, uiMultiSelectFlags_BoxSelect1d);

            for (int selection_scope_n = 0; selection_scope_n < SCOPES_COUNT; selection_scope_n++)
            {
                UI::PushID(selection_scope_n);
                uiSelectionBasicStorage* selection = &selections_data[selection_scope_n];
                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, selection->Size, ITEMS_COUNT);
                selection->ApplyRequests(ms_io);

                UI::BarrierText("Selection scope");
                UI::Text("Selection size: %d/%d", selection->Size, ITEMS_COUNT);

                for (int n = 0; n < ITEMS_COUNT; n++)
                {
                    char label[64];
                    sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                    bool item_is_selected = selection->Contains((uiID)n);
                    UI::SetNextItemSelectionUserData(n);
                    UI::Selectable(label, item_is_selected);
                }

                // Apply multi-select requests
                ms_io = UI::EndMultiSelect();
                selection->ApplyRequests(ms_io);
                UI::PopID();
            }
            UI::TreePop();
        }

        // See ShowExampleAppAssetsBrowser()
        if (UI::TreeNode("Multi-Select (tiled assets browser)"))
        {
            UI::Checkbox("Assets Browser", &demo_data->ShowAppAssetsBrowser);
            UI::Text("(also access from 'Examples->Assets Browser' in menu)");
            UI::TreePop();
        }

        // Demonstrate supporting multiple-selection in a tree.
        // - We don't use linear indices for selection user data, but our ExampleTreeNode* pointer directly!
        //   This showcase how SetNextItemSelectionUserData() never assume indices!
        // - The difficulty here is to "interpolate" from RangeSrcItem to RangeDstItem in the SetAll/SetRange request.
        //   We want this interpolation to match what the user sees: in visible order, skipping closed nodes.
        //   This is implemented by our TreeGetNextNodeInVisibleOrder() user-space helper.
        // - Important: In a real codebase aiming to implement full-featured selectable tree with custom filtering, you
        //   are more likely to build an array mapping sequential indices to visible tree nodes, since your
        //   filtering/search + clipping process will benefit from it. Having this will make this interpolation much easier.
        // - Consider this a prototype: we are working toward simplifying some of it.
        if (UI::TreeNode("Multi-Select (trees)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (trees)");
            HelpMarker(
                "This is rather advanced and experimental. If you are getting started with multi-select, "
                "please don't start by looking at how to use it for a tree!\n\n"
                "Future versions will try to simplify and formalize some of this.");

            struct ExampleTreeFuncs
            {
                static void DrawNode(ExampleTreeNode* node, uiSelectionBasicStorage* selection)
                {
                    uiTreeFlags tree_node_flags = uiTreeFlags_SpanAvailWidth | uiTreeFlags_OpenOnArrow | uiTreeFlags_OpenOnDoubleClick;
                    tree_node_flags |= uiTreeFlags_NavLeftJumpsToParent; // Enable pressing left to jump to parent
                    if (node->Childs.Size == 0)
                        tree_node_flags |= uiTreeFlags_Bullet | uiTreeFlags_Leaf;
                    if (selection->Contains((uiID)node->UID))
                        tree_node_flags |= uiTreeFlags_Selected;

                    // Using SetNextItemStorageID() to specify storage id, so we can easily peek into
                    // the storage holding open/close stage, using our TreeNodeGetOpen/TreeNodeSetOpen() functions.
                    UI::SetNextItemSelectionUserData((uiSelectionUserData)(intptr_t)node);
                    UI::SetNextItemStorageID((uiID)node->UID);
                    if (UI::TreeNodeEx(node->Name, tree_node_flags))
                    {
                        for (ExampleTreeNode* child : node->Childs)
                            DrawNode(child, selection);
                        UI::TreePop();
                    }
                    else if (UI::IsItemToggledOpen())
                    {
                        TreeCloseAndUnselectChildNodes(node, selection);
                    }
                }

                // When closing a node: 1) close and unselect all child nodes, 2) select parent if any child was selected.
                // FIXME: This is currently handled by user logic but I'm hoping to eventually provide tree node
                // features to do this automatically, e.g. a uiTreeFlags_AutoCloseChildNodes etc.
                static int TreeCloseAndUnselectChildNodes(ExampleTreeNode* node, uiSelectionBasicStorage* selection, int depth = 0)
                {
                    // Recursive close (the test for depth == 0 is because we call this on a node that was just closed!)
                    int unselected_count = selection->Contains((uiID)node->UID) ? 1 : 0;
                    if (depth == 0 || UI::TreeNodeGetOpen((uiID)node->UID))
                    {
                        for (ExampleTreeNode* child : node->Childs)
                            unselected_count += TreeCloseAndUnselectChildNodes(child, selection, depth + 1);
                        UI::TreeNodeSetOpen((uiID)node->UID, false);
                    }

                    // Select root node if any of its child was selected, otherwise unselect
                    selection->SetItemSelected((uiID)node->UID, (depth == 0 && unselected_count > 0));
                    return unselected_count;
                }

                // Apply multi-selection requests
                static void ApplySelectionRequests(uiMultiSelectIO* ms_io, ExampleTreeNode* tree, uiSelectionBasicStorage* selection)
                {
                    for (uiSelectionRequest& req : ms_io->Requests)
                    {
                        if (req.Type == uiSelectionRequestType_SetAll)
                        {
                            if (req.Selected)
                                TreeSetAllInOpenNodes(tree, selection, req.Selected);
                            else
                                selection->Clear();
                        }
                        else if (req.Type == uiSelectionRequestType_SetRange)
                        {
                            ExampleTreeNode* first_node = (ExampleTreeNode*)(intptr_t)req.RangeFirstItem;
                            ExampleTreeNode* last_node = (ExampleTreeNode*)(intptr_t)req.RangeLastItem;
                            for (ExampleTreeNode* node = first_node; node != NULL; node = TreeGetNextNodeInVisibleOrder(node, last_node))
                                selection->SetItemSelected((uiID)node->UID, req.Selected);
                        }
                    }
                }

                static void TreeSetAllInOpenNodes(ExampleTreeNode* node, uiSelectionBasicStorage* selection, bool selected)
                {
                    if (node->Parent != NULL) // Root node isn't visible nor selectable in our scheme
                        selection->SetItemSelected((uiID)node->UID, selected);
                    if (node->Parent == NULL || UI::TreeNodeGetOpen((uiID)node->UID))
                        for (ExampleTreeNode* child : node->Childs)
                            TreeSetAllInOpenNodes(child, selection, selected);
                }

                // Interpolate in *user-visible order* AND only *over opened nodes*.
                // If you have a sequential mapping tables (e.g. generated after a filter/search pass) this would be simpler.
                // Here the tricks are that:
                // - we store/maintain ExampleTreeNode::IndexInParent which allows implementing a linear iterator easily, without searches, without recursion.
                //   this could be replaced by a search in parent, aka 'int index_in_parent = curr_node->Parent->Childs.find_index(curr_node)'
                //   which would only be called when crossing from child to a parent, aka not too much.
                // - we call SetNextItemStorageID() before our TreeNode() calls with an ID which doesn't relate to UI stack,
                //   making it easier to call TreeNodeGetOpen()/TreeNodeSetOpen() from any location.
                static ExampleTreeNode* TreeGetNextNodeInVisibleOrder(ExampleTreeNode* curr_node, ExampleTreeNode* last_node)
                {
                    // Reached last node
                    if (curr_node == last_node)
                        return NULL;

                    // Recurse into childs. Query storage to tell if the node is open.
                    if (curr_node->Childs.Size > 0 && UI::TreeNodeGetOpen((uiID)curr_node->UID))
                        return curr_node->Childs[0];

                    // Next sibling, then into our own parent
                    while (curr_node->Parent != NULL)
                    {
                        if (curr_node->IndexInParent + 1 < curr_node->Parent->Childs.Size)
                            return curr_node->Parent->Childs[curr_node->IndexInParent + 1];
                        curr_node = curr_node->Parent;
                    }
                    return NULL;
                }

            }; // ExampleTreeFuncs

            static uiSelectionBasicStorage selection;
            if (demo_data->DemoTree == NULL)
                demo_data->DemoTree = ExampleTree_CreateDemoTree(); // Create tree once
            UI::Text("Selection size: %d", selection.Size);

            if (UI::BeginChild("##Tree", vec2(-FLT_MIN, UI::GetFontSize() * 20), uiChildFlags_FrameStyle | uiChildFlags_ResizeY))
            {
                ExampleTreeNode* tree = demo_data->DemoTree;
                uiMultiSelectFlags ms_flags = uiMultiSelectFlags_ClearOnEscape | uiMultiSelectFlags_BoxSelect2d;
                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(ms_flags, selection.Size, -1);
                ExampleTreeFuncs::ApplySelectionRequests(ms_io, tree, &selection);
                for (ExampleTreeNode* node : tree->Childs)
                    ExampleTreeFuncs::DrawNode(node, &selection);
                ms_io = UI::EndMultiSelect();
                ExampleTreeFuncs::ApplySelectionRequests(ms_io, tree, &selection);
            }
            UI::EndChild();

            UI::TreePop();
        }

        // Advanced demonstration of BeginMultiSelect()
        // - Showcase clipping.
        // - Showcase deletion.
        // - Showcase basic drag and drop.
        // - Showcase TreeNode variant (note that tree node don't expand in the demo: supporting expanding tree nodes + clipping a separate thing).
        // - Showcase using inside a table.
        //UI::SetNextItemOpen(true, uiCond_Once);
        if (UI::TreeNode("Multi-Select (advanced)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (advanced)");
            // Options
            enum WidgetType { WidgetType_Selectable, WidgetType_TreeNode };
            static bool use_clipper = true;
            static bool use_deletion = true;
            static bool use_drag_drop = true;
            static bool show_in_table = false;
            static bool show_color_button = true;
            static uiMultiSelectFlags flags = uiMultiSelectFlags_ClearOnEscape | uiMultiSelectFlags_BoxSelect1d;
            static WidgetType widget_type = WidgetType_Selectable;

            if (UI::TreeNode("Options"))
            {
                if (UI::RadioButton("Selectables", widget_type == WidgetType_Selectable)) { widget_type = WidgetType_Selectable; }
                UI::SameLine();
                if (UI::RadioButton("Tree nodes", widget_type == WidgetType_TreeNode)) { widget_type = WidgetType_TreeNode; }
                UI::SameLine();
                HelpMarker("TreeNode() is technically supported but... using this correctly is more complicated (you need some sort of linear/random access to your tree, which is suited to advanced trees setups already implementing filters and clipper. We will work toward simplifying and demoing this.\n\nFor now the tree demo is actually a little bit meaningless because it is an empty tree with only root nodes.");
                UI::Checkbox("Enable clipper", &use_clipper);
                UI::Checkbox("Enable deletion", &use_deletion);
                UI::Checkbox("Enable drag & drop", &use_drag_drop);
                UI::Checkbox("Show in a table", &show_in_table);
                UI::Checkbox("Show color button", &show_color_button);
                UI::CheckboxFlags("uiMultiSelectFlags_SingleSelect", &flags, uiMultiSelectFlags_SingleSelect);
                UI::CheckboxFlags("uiMultiSelectFlags_NoSelectAll", &flags, uiMultiSelectFlags_NoSelectAll);
                UI::CheckboxFlags("uiMultiSelectFlags_NoRangeSelect", &flags, uiMultiSelectFlags_NoRangeSelect);
                UI::CheckboxFlags("uiMultiSelectFlags_NoAutoSelect", &flags, uiMultiSelectFlags_NoAutoSelect);
                UI::CheckboxFlags("uiMultiSelectFlags_NoAutoClear", &flags, uiMultiSelectFlags_NoAutoClear);
                UI::CheckboxFlags("uiMultiSelectFlags_NoAutoClearOnReselect", &flags, uiMultiSelectFlags_NoAutoClearOnReselect);
                UI::CheckboxFlags("uiMultiSelectFlags_NoSelectOnRightClick", &flags, uiMultiSelectFlags_NoSelectOnRightClick);
                UI::CheckboxFlags("uiMultiSelectFlags_BoxSelect1d", &flags, uiMultiSelectFlags_BoxSelect1d);
                UI::CheckboxFlags("uiMultiSelectFlags_BoxSelect2d", &flags, uiMultiSelectFlags_BoxSelect2d);
                UI::CheckboxFlags("uiMultiSelectFlags_BoxSelectNoScroll", &flags, uiMultiSelectFlags_BoxSelectNoScroll);
                UI::CheckboxFlags("uiMultiSelectFlags_ClearOnEscape", &flags, uiMultiSelectFlags_ClearOnEscape);
                UI::CheckboxFlags("uiMultiSelectFlags_ClearOnClickVoid", &flags, uiMultiSelectFlags_ClearOnClickVoid);
                if (UI::CheckboxFlags("uiMultiSelectFlags_ScopeWindow", &flags, uiMultiSelectFlags_ScopeWindow) && (flags & uiMultiSelectFlags_ScopeWindow))
                    flags &= ~uiMultiSelectFlags_ScopeRect;
                if (UI::CheckboxFlags("uiMultiSelectFlags_ScopeRect", &flags, uiMultiSelectFlags_ScopeRect) && (flags & uiMultiSelectFlags_ScopeRect))
                    flags &= ~uiMultiSelectFlags_ScopeWindow;
                if (UI::CheckboxFlags("uiMultiSelectFlags_SelectOnAuto", &flags, uiMultiSelectFlags_SelectOnAuto))
                    flags &= ~(uiMultiSelectFlags_SelectOnMask_ ^ uiMultiSelectFlags_SelectOnAuto);
                UI::SameLine(); HelpMarker("Apply selection on mouse down when clicking on unselected item, on mouse up when clicking on selected item. (Default)");
                if (UI::CheckboxFlags("uiMultiSelectFlags_SelectOnClickAlways", &flags, uiMultiSelectFlags_SelectOnClickAlways))
                    flags &= ~(uiMultiSelectFlags_SelectOnMask_ ^ uiMultiSelectFlags_SelectOnClickAlways);
                UI::SameLine(); HelpMarker("Prevents Drag and Drop from being used on multi-selection, but allows e.g. BoxSelect to always reselect even when clicking inside an existing selection. (Excel style behavior)");
                if (UI::CheckboxFlags("uiMultiSelectFlags_SelectOnClickRelease", &flags, uiMultiSelectFlags_SelectOnClickRelease))
                    flags &= ~(uiMultiSelectFlags_SelectOnMask_ ^ uiMultiSelectFlags_SelectOnClickRelease);
                UI::SameLine(); HelpMarker("Allow dragging an unselected item without altering selection.");
                UI::TreePop();
            }

            // Initialize default list with 1000 items.
            // Use default selection.Adapter: Pass index to SetNextItemSelectionUserData(), store index in Selection
            static ImVector<int> items;
            static int items_next_id = 0;
            if (items_next_id == 0) { for (int n = 0; n < 1000; n++) { items.push_back(items_next_id++); } }
            static ExampleSelectionWithDeletion selection;
            static bool request_deletion_from_menu = false; // Queue deletion triggered from context menu

            UI::Text("Selection size: %d/%d", selection.Size, items.Size);

            const float items_height = (widget_type == WidgetType_TreeNode) ? UI::GetTextLineHeight() : UI::GetTextLineHeightWithSpacing();
            UI::SetNextWindowContentSize(vec2(0.0f, items.Size * items_height));
            if (UI::BeginChild("##Basket", vec2(-FLT_MIN, UI::GetFontSize() * 20), uiChildFlags_FrameStyle | uiChildFlags_ResizeY))
            {
                vec2 color_button_sz(UI::GetFontSize(), UI::GetFontSize());
                if (widget_type == WidgetType_TreeNode)
                    UI::PushStyleVarY(uiStyleVar_ItemSpacing, 0.0f);

                uiMultiSelectIO* ms_io = UI::BeginMultiSelect(flags, selection.Size, items.Size);
                selection.ApplyRequests(ms_io);

                const bool want_delete = (UI::Shortcut(uiKey_Delete, uiInputFlags_Repeat) && (selection.Size > 0)) || request_deletion_from_menu;
                const int item_curr_idx_to_focus = want_delete ? selection.ApplyDeletionPreLoop(ms_io, items.Size) : -1;
                request_deletion_from_menu = false;

                if (show_in_table)
                {
                    if (widget_type == WidgetType_TreeNode)
                        UI::PushStyleVar(uiStyleVar_CellPadding, vec2(0.0f, 0.0f));
                    UI::BeginTable("##Split", 2, uiTableFlags_Resizable | uiTableFlags_NoSavedSettings | uiTableFlags_NoPadOuterX);
                    UI::TableSetupColumn("", uiTableColumnFlags_WidthStretch, 0.70f);
                    UI::TableSetupColumn("", uiTableColumnFlags_WidthStretch, 0.30f);
                    //UI::PushStyleVarY(uiStyleVar_ItemSpacing, 0.0f);
                }

                uiListClipper clipper;
                if (use_clipper)
                {
                    clipper.Begin(items.Size);
                    if (item_curr_idx_to_focus != -1)
                        clipper.IncludeItemByIndex(item_curr_idx_to_focus); // Ensure focused item is not clipped.
                    if (ms_io->RangeSrcItem != -1)
                        clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // Ensure RangeSrc item is not clipped.
                }

                while (!use_clipper || clipper.Step())
                {
                    const int item_begin = use_clipper ? clipper.DisplayStart : 0;
                    const int item_end = use_clipper ? clipper.DisplayEnd : items.Size;
                    for (int n = item_begin; n < item_end; n++)
                    {
                        if (show_in_table)
                            UI::TableNextColumn();

                        const int item_id = items[n];
                        const char* item_category = ExampleNames[item_id % IM_COUNTOF(ExampleNames)];
                        char label[64];
                        sprintf(label, "Object %05d: %s", item_id, item_category);

                        // IMPORTANT: for deletion refocus to work we need object ID to be stable,
                        // aka not depend on their index in the list. Here we use our persistent item_id
                        // instead of index to build a unique ID that will persist.
                        // (If we used PushID(index) instead, focus wouldn't be restored correctly after deletion).
                        UI::PushID(item_id);

                        // Emit a color button, to test that Shift+LeftArrow landing on an item that is not part
                        // of the selection scope doesn't erroneously alter our selection.
                        if (show_color_button)
                        {
                            ImU32 dummy_col = (ImU32)((unsigned int)n * 0xC250B74B) | IM_COL32_A_MASK;
                            UI::ColorButton("##", ImColor(dummy_col), uiColorEditFlags_NoTooltip, color_button_sz);
                            UI::SameLine();
                        }

                        // Submit item
                        bool item_is_selected = selection.Contains((uiID)n);
                        bool item_is_open = false;
                        UI::SetNextItemSelectionUserData(n);
                        if (widget_type == WidgetType_Selectable)
                        {
                            UI::Selectable(label, item_is_selected, uiSelectFlags_None);
                        }
                        else if (widget_type == WidgetType_TreeNode)
                        {
                            uiTreeFlags tree_node_flags = uiTreeFlags_SpanAvailWidth | uiTreeFlags_OpenOnArrow | uiTreeFlags_OpenOnDoubleClick;
                            if (item_is_selected)
                                tree_node_flags |= uiTreeFlags_Selected;
                            item_is_open = UI::TreeNodeEx(label, tree_node_flags);
                        }

                        // Focus (for after deletion)
                        if (item_curr_idx_to_focus == n)
                            UI::SetKeyboardFocusHere(-1);

                        // Drag and Drop
                        if (use_drag_drop && UI::BeginDragDropSource())
                        {
                            // Create payload with full selection OR single unselected item.
                            // (the later is only possible when using uiMultiSelectFlags_SelectOnClickRelease)
                            if (UI::GetDragDropPayload() == NULL)
                            {
                                ImVector<int> payload_items;
                                void* it = NULL;
                                uiID id = 0;
                                if (!item_is_selected)
                                    payload_items.push_back(item_id);
                                else
                                    while (selection.GetNextSelectedItem(&it, &id))
                                        payload_items.push_back((int)id);
                                UI::SetDragDropPayload("MULTISELECT_DEMO_ITEMS", payload_items.Data, (size_t)payload_items.size_in_bytes());
                            }

                            // Display payload content in tooltip
                            const uiPayload* payload = UI::GetDragDropPayload();
                            const int* payload_items = (int*)payload->Data;
                            const int payload_count = (int)payload->DataSize / (int)sizeof(int);
                            if (payload_count == 1)
                                UI::Text("Object %05d: %s", payload_items[0], ExampleNames[payload_items[0] % IM_COUNTOF(ExampleNames)]);
                            else
                                UI::Text("Dragging %d objects", payload_count);

                            UI::EndDragDropSource();
                        }

                        if (widget_type == WidgetType_TreeNode && item_is_open)
                            UI::TreePop();

                        // Right-click: context menu
                        if (UI::BeginPopupContextItem())
                        {
                            UI::BeginDisabled(!use_deletion || selection.Size == 0);
                            sprintf(label, "Delete %d item(s)###DeleteSelected", selection.Size);
                            if (UI::Selectable(label))
                                request_deletion_from_menu = true;
                            UI::EndDisabled();
                            UI::Selectable("Close");
                            UI::EndPopup();
                        }

                        // Demo content within a table
                        if (show_in_table)
                        {
                            UI::TableNextColumn();
                            UI::SetNextItemWidth(-FLT_MIN);
                            UI::PushStyleVar(uiStyleVar_FramePadding, vec2(0, 0));
                            UI::InputText("##NoLabel", (char*)(void*)item_category, strlen(item_category), uiInputTextFlags_ReadOnly);
                            UI::PopStyleVar();
                        }

                        UI::PopID();
                    }
                    if (!use_clipper)
                        break;
                }

                if (show_in_table)
                {
                    UI::EndTable();
                    if (widget_type == WidgetType_TreeNode)
                        UI::PopStyleVar();
                }

                // Apply multi-select requests
                ms_io = UI::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                if (want_delete)
                    selection.ApplyDeletionPostLoop(ms_io, items, item_curr_idx_to_focus);

                if (widget_type == WidgetType_TreeNode)
                    UI::PopStyleVar();
            }
            UI::EndChild();
            UI::TreePop();
        }
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTabs()
//-----------------------------------------------------------------------------

static void EditTabBarFittingPolicyFlags(uiTabBarFlags* p_flags)
{
    if ((*p_flags & uiTabBarFlags_FitMask_) == 0)
        *p_flags |= uiTabBarFlags_FitDefault_;
    if (UI::CheckboxFlags("uiTabBarFlags_FitMixed", p_flags, uiTabBarFlags_FitMixed))
        *p_flags &= ~(uiTabBarFlags_FitMask_ ^ uiTabBarFlags_FitMixed);
    if (UI::CheckboxFlags("uiTabBarFlags_FitShrink", p_flags, uiTabBarFlags_FitShrink))
        *p_flags &= ~(uiTabBarFlags_FitMask_ ^ uiTabBarFlags_FitShrink);
    if (UI::CheckboxFlags("uiTabBarFlags_FitScroll", p_flags, uiTabBarFlags_FitScroll))
        *p_flags &= ~(uiTabBarFlags_FitMask_ ^ uiTabBarFlags_FitScroll);
}

static void DemoWindowWidgetsTabs()
{
    if (UI::TreeNode("Tabs"))
    {
        IMGUI_DEMO_MARKER("Widgets/Tabs");
        if (UI::TreeNode("Basic"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tabs/Basic");
            uiTabBarFlags tab_bar_flags = uiTabBarFlags_None;
            if (UI::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                if (UI::BeginTabItem("Avocado"))
                {
                    UI::Text("This is the Avocado tab!\nblah blah blah blah blah");
                    UI::EndTabItem();
                }
                if (UI::BeginTabItem("Broccoli"))
                {
                    UI::Text("This is the Broccoli tab!\nblah blah blah blah blah");
                    UI::EndTabItem();
                }
                if (UI::BeginTabItem("Cucumber"))
                {
                    UI::Text("This is the Cucumber tab!\nblah blah blah blah blah");
                    UI::EndTabItem();
                }
                UI::EndTabBar();
            }
            UI::Barrier();
            UI::TreePop();
        }

        if (UI::TreeNode("Advanced & Close Button"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tabs/Advanced & Close Button");
            // Expose a couple of the available flags. In most cases you may just call BeginTabBar() with no flags (0).
            static uiTabBarFlags tab_bar_flags = uiTabBarFlags_Reorderable;
            UI::CheckboxFlags("uiTabBarFlags_Reorderable", &tab_bar_flags, uiTabBarFlags_Reorderable);
            UI::CheckboxFlags("uiTabBarFlags_AutoSelectNewTabs", &tab_bar_flags, uiTabBarFlags_AutoSelectNewTabs);
            UI::CheckboxFlags("uiTabBarFlags_TabListPopupButton", &tab_bar_flags, uiTabBarFlags_TabListPopupButton);
            UI::CheckboxFlags("uiTabBarFlags_NoCloseWithMiddleMouseButton", &tab_bar_flags, uiTabBarFlags_NoCloseWithMiddleMouseButton);
            UI::CheckboxFlags("uiTabBarFlags_DrawSelectedOverline", &tab_bar_flags, uiTabBarFlags_DrawSelectedOverline);
            EditTabBarFittingPolicyFlags(&tab_bar_flags);

            // Tab Bar
            UI::AlignTextToFramePadding();
            UI::Text("Opened:");
            const char* names[4] = { "Artichoke", "Beetroot", "Celery", "Daikon" };
            static bool opened[4] = { true, true, true, true }; // Persistent user state
            for (int n = 0; n < IM_COUNTOF(opened); n++)
            {
                UI::SameLine();
                UI::Checkbox(names[n], &opened[n]);
            }

            // Passing a bool* to BeginTabItem() is similar to passing one to Begin():
            // the underlying bool will be set to false when the tab is closed.
            if (UI::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                for (int n = 0; n < IM_COUNTOF(opened); n++)
                    if (opened[n] && UI::BeginTabItem(names[n], &opened[n], uiTabItemFlags_None))
                    {
                        UI::Text("This is the %s tab!", names[n]);
                        if (n & 1)
                            UI::Text("I am an odd tab.");
                        UI::EndTabItem();
                    }
                UI::EndTabBar();
            }
            UI::Barrier();
            UI::TreePop();
        }

        if (UI::TreeNode("TabItemButton & Leading/Trailing flags"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tabs/TabItemButton & Leading-Trailing flags");
            static ImVector<int> active_tabs;
            static int next_tab_id = 0;
            if (next_tab_id == 0) // Initialize with some default tabs
                for (int i = 0; i < 3; i++)
                    active_tabs.push_back(next_tab_id++);

            // TabItemButton() and Leading/Trailing flags are distinct features which we will demo together.
            // (It is possible to submit regular tabs with Leading/Trailing flags, or TabItemButton tabs without Leading/Trailing flags...
            // but they tend to make more sense together)
            static bool show_leading_button = true;
            static bool show_trailing_button = true;
            UI::Checkbox("Show Leading TabItemButton()", &show_leading_button);
            UI::Checkbox("Show Trailing TabItemButton()", &show_trailing_button);

            // Expose some other flags which are useful to showcase how they interact with Leading/Trailing tabs
            static uiTabBarFlags tab_bar_flags = uiTabBarFlags_AutoSelectNewTabs | uiTabBarFlags_Reorderable | uiTabBarFlags_FitShrink;
            EditTabBarFittingPolicyFlags(&tab_bar_flags);

            if (UI::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                // Demo a Leading TabItemButton(): click the "?" button to open a menu
                if (show_leading_button)
                    if (UI::TabItemButton("?", uiTabItemFlags_Leading | uiTabItemFlags_NoTooltip))
                        UI::OpenPopup("MyHelpMenu");
                if (UI::BeginPopup("MyHelpMenu"))
                {
                    UI::Selectable("Hello!");
                    UI::EndPopup();
                }

                // Demo Trailing Tabs: click the "+" button to add a new tab.
                // (In your app you may want to use a font icon instead of the "+")
                // We submit it before the regular tabs, but thanks to the uiTabItemFlags_Trailing flag it will always appear at the end.
                if (show_trailing_button)
                    if (UI::TabItemButton("+", uiTabItemFlags_Trailing | uiTabItemFlags_NoTooltip))
                        active_tabs.push_back(next_tab_id++); // Add new tab

                // Submit our regular tabs
                for (int n = 0; n < active_tabs.Size; )
                {
                    bool open = true;
                    char name[16];
                    snprintf(name, IM_COUNTOF(name), "%04d", active_tabs[n]);
                    if (UI::BeginTabItem(name, &open, uiTabItemFlags_None))
                    {
                        UI::Text("This is the %s tab!", name);
                        UI::EndTabItem();
                    }

                    if (!open)
                        active_tabs.erase(active_tabs.Data + n);
                    else
                        n++;
                }

                UI::EndTabBar();
            }
            UI::Barrier();
            UI::TreePop();
        }
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsText()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsText()
{
    if (UI::TreeNode("Text"))
    {
        IMGUI_DEMO_MARKER("Widgets/Text");
        if (UI::TreeNode("Colorful Text"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text/Colored Text");
            // Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
            UI::TextColored(vec4(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
            UI::TextColored(vec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
            UI::TextDisabled("Disabled");
            UI::SameLine(); HelpMarker("The TextDisabled color is stored in uiStyle.");
            UI::TreePop();
        }

        if (UI::TreeNode("Font Size"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text/Font Size");
            uiStyle& style = UI::GetStyle();
            const float global_scale = style.FontScaleMain * style.FontScaleDpi;
            UI::Text("style.FontScaleMain = %0.2f", style.FontScaleMain);
            UI::Text("style.FontScaleDpi = %0.2f", style.FontScaleDpi);
            UI::Text("global_scale = ~%0.2f", global_scale); // This is not technically accurate as internal scales may apply, but conceptually let's pretend it is.
            UI::Text("FontSize = %0.2f", UI::GetFontSize());

            UI::BarrierText("");
            static float custom_size = 16.0f;
            UI::SliderFloat("custom_size", &custom_size, 10.0f, 100.0f, "%.0f");
            UI::Text("UI::PushFont(nullptr, custom_size);");
            UI::PushFont(NULL, custom_size);
            UI::Text("FontSize = %.2f (== %.2f * global_scale)", UI::GetFontSize(), custom_size);
            UI::PopFont();

            UI::BarrierText("");
            static float custom_scale = 1.0f;
            UI::SliderFloat("custom_scale", &custom_scale, 0.5f, 4.0f, "%.2f");
            UI::Text("UI::PushFont(nullptr, style.FontSizeBase * custom_scale);");
            UI::PushFont(NULL, style.FontSizeBase * custom_scale);
            UI::Text("FontSize = %.2f (== style.FontSizeBase * %.2f * global_scale)", UI::GetFontSize(), custom_scale);
            UI::PopFont();

            UI::BarrierText("");
            for (float scaling = 0.5f; scaling <= 4.0f; scaling += 0.5f)
            {
                UI::PushFont(NULL, style.FontSizeBase * scaling);
                UI::Text("FontSize = %.2f (== style.FontSizeBase * %.2f * global_scale)", UI::GetFontSize(), scaling);
                UI::PopFont();
            }

            UI::TreePop();
        }

        if (UI::TreeNode("Word Wrapping"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text/Word Wrapping");
            // Using shortcut. You can use PushTextWrapPos()/PopTextWrapPos() for more flexibility.
            UI::TextWrapped(
                "This text should automatically wrap on the edge of the window. The current implementation "
                "for text wrapping follows simple rules suitable for English and possibly other languages.");
            UI::Spacing();

            static float wrap_width = 200.0f;
            UI::SliderFloat("Wrap width", &wrap_width, -20, 600, "%.0f");

            ImDrawList* draw_list = UI::GetWindowDrawList();
            for (int n = 0; n < 2; n++)
            {
                UI::Text("Test paragraph %d:", n);
                vec2 pos = UI::GetCursorScreenPos();
                vec2 marker_min = vec2(pos.x + wrap_width, pos.y);
                vec2 marker_max = vec2(pos.x + wrap_width + 10, pos.y + UI::GetTextLineHeight());
                UI::PushTextWrapPos(UI::GetCursorPos().x + wrap_width);
                if (n == 0)
                    UI::Text("The lazy dog is a good dog. This paragraph should fit within %.0f pixels. Testing a 1 character word. The quick brown fox jumps over the lazy dog.", wrap_width);
                else
                    UI::Text("aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");

                // Draw actual text bounding box, following by marker of our expected limit (should not overlap!)
                draw_list->AddRect(UI::GetItemRectMin(), UI::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
                draw_list->AddRectFilled(marker_min, marker_max, IM_COL32(255, 0, 255, 255));
                UI::PopTextWrapPos();
            }

            UI::TreePop();
        }

        if (UI::TreeNode("UTF-8 Text"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text/UTF-8 Text");
            // UTF-8 test with Japanese characters
            // (Needs a suitable font? Try "Google Noto" or "Arial Unicode". See docs/FONTS.md for details.)
            // - From C++11 you can use the u8"my text" syntax to encode literal strings as UTF-8
            // - For earlier compiler, you may be able to encode your sources as UTF-8 (e.g. in Visual Studio, you
            //   can save your source files as 'UTF-8 without signature').
            // - FOR THIS DEMO FILE ONLY, BECAUSE WE WANT TO SUPPORT OLD COMPILERS, WE ARE *NOT* INCLUDING RAW UTF-8
            //   CHARACTERS IN THIS SOURCE FILE. Instead we are encoding a few strings with hexadecimal constants.
            //   Don't do this in your application! Please use u8"text in any language" in your application!
            // Note that characters values are preserved even by InputText() if the font cannot be displayed,
            // so you can safely copy & paste garbled characters into another application.
            UI::TextWrapped(
                "CJK text will only appear if the font was loaded with the appropriate CJK character ranges. "
                "Call io.Fonts->AddFontFromFileTTF() manually to load extra character ranges. "
                "Read docs/FONTS.md for details.");
            UI::Text("Hiragana: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)");
            UI::Text("Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
            static char buf[32] = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";
            //static char buf[32] = u8"NIHONGO"; // <- this is how you would write it with C++11, using real kanjis
            UI::InputText("UTF-8 input", buf, IM_COUNTOF(buf));
            UI::TreePop();
        }
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTextFilter()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTextFilter()
{
    if (UI::TreeNode("Text Filter"))
    {
        IMGUI_DEMO_MARKER("Widgets/Text Filter");
        // Helper class to easy setup a text filter.
        // You may want to implement a more feature-full filtering scheme in your own application.
        HelpMarker("Not a widget per-se, but uiTextFilter is a helper to perform simple filtering on text strings.");
        static uiTextFilter filter;
        UI::Text("Filter usage:\n"
            "  \"\"         display all lines\n"
            "  \"xxx\"      display lines containing \"xxx\"\n"
            "  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
            "  \"-xxx\"     hide lines containing \"xxx\"");
        filter.Draw();
        const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
        for (int i = 0; i < IM_COUNTOF(lines); i++)
            if (filter.PassFilter(lines[i]))
                UI::BulletText("%s", lines[i]);
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTextInput()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTextInput()
{
    // To wire InputText() with std::string or any other custom string type,
    // see the "Text Input > Resize Callback" section of this demo, and the misc/cpp/imgui_stdlib.h file.
    if (UI::TreeNode("Text Input"))
    {
        IMGUI_DEMO_MARKER("Widgets/Text Input");
        if (UI::TreeNode("Multi-line Text Input"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Multi-line Text Input");
            // WE ARE USING A FIXED-SIZE BUFFER FOR SIMPLICITY HERE.
            // If you want to use InputText() with std::string or any custom dynamic string type:
            // - For std::string: use the wrapper in misc/cpp/imgui_stdlib.h/.cpp
            // - Otherwise, see the 'Dear ImGui Demo->Widgets->Text Input->Resize Callback' for using uiInputTextFlags_CallbackResize.
            static char text[1024 * 16] =
                "/*\n"
                " The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
                " the hexadecimal encoding of one offending instruction,\n"
                " more formally, the invalid operand with locked CMPXCHG8B\n"
                " instruction bug, is a design flaw in the majority of\n"
                " Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
                " processors (all in the P5 microarchitecture).\n"
                "*/\n\n"
                "label:\n"
                "\tlock cmpxchg8b eax\n";

            static uiInputTextFlags flags = uiInputTextFlags_AllowTabInput;
            HelpMarker("You can use the uiInputTextFlags_CallbackResize facility if you need to wire InputTextMultiline() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example. (This is not demonstrated in imgui_demo.cpp because we don't want to include <string> in here)");
            UI::CheckboxFlags("uiInputTextFlags_ReadOnly", &flags, uiInputTextFlags_ReadOnly);
            UI::CheckboxFlags("uiInputTextFlags_WordWrap", &flags, uiInputTextFlags_WordWrap);
            UI::SameLine(); HelpMarker("Feature is currently in Beta. Please read comments in imgui.h");
            UI::CheckboxFlags("uiInputTextFlags_AllowTabInput", &flags, uiInputTextFlags_AllowTabInput);
            UI::SameLine(); HelpMarker("When _AllowTabInput is set, passing through the widget with Tabbing doesn't automatically activate it, in order to also cycling through subsequent widgets.");
            UI::CheckboxFlags("uiInputTextFlags_CtrlEnterForNewLine", &flags, uiInputTextFlags_CtrlEnterForNewLine);
            UI::InputTextMultiline("##source", text, IM_COUNTOF(text), vec2(-FLT_MIN, UI::GetTextLineHeight() * 16), flags);
            UI::TreePop();
        }

        if (UI::TreeNode("Filtered Text Input"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Filtered Text Input");
            struct TextFilters
            {
                // Modify character input by altering 'data->Eventchar' (uiInputTextFlags_CallbackCharFilter callback)
                static int FilterCasingSwap(uiInputTextCallbackData* data)
                {
                    if (data->EventChar >= 'a' && data->EventChar <= 'z') { data->EventChar -= 'a' - 'A'; } // Lowercase becomes uppercase
                    else if (data->EventChar >= 'A' && data->EventChar <= 'Z') { data->EventChar += 'a' - 'A'; } // Uppercase becomes lowercase
                    return 0;
                }

                // Return 0 (pass) if the character is 'i' or 'm' or 'g' or 'u' or 'i', otherwise return 1 (filter out)
                static int FilteruiLetters(uiInputTextCallbackData* data)
                {
                    if (data->EventChar < 256 && strchr("imgui", (char)data->EventChar))
                        return 0;
                    return 1;
                }
            };

            static char buf1[32] = ""; UI::InputText("default", buf1, IM_COUNTOF(buf1));
            static char buf2[32] = ""; UI::InputText("decimal", buf2, IM_COUNTOF(buf2), uiInputTextFlags_CharsDecimal);
            static char buf3[32] = ""; UI::InputText("hexadecimal", buf3, IM_COUNTOF(buf3), uiInputTextFlags_CharsHexadecimal | uiInputTextFlags_CharsUppercase);
            static char buf4[32] = ""; UI::InputText("uppercase", buf4, IM_COUNTOF(buf4), uiInputTextFlags_CharsUppercase);
            static char buf5[32] = ""; UI::InputText("no blank", buf5, IM_COUNTOF(buf5), uiInputTextFlags_CharsNoBlank);
            static char buf6[32] = ""; UI::InputText("casing swap", buf6, IM_COUNTOF(buf6), uiInputTextFlags_CallbackCharFilter, TextFilters::FilterCasingSwap); // Use CharFilter callback to replace characters.
            static char buf7[32] = ""; UI::InputText("\"imgui\"", buf7, IM_COUNTOF(buf7), uiInputTextFlags_CallbackCharFilter, TextFilters::FilteruiLetters); // Use CharFilter callback to disable some characters.
            UI::TreePop();
        }

        if (UI::TreeNode("Password Input"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Password input");
            static char password[64] = "password123";
            UI::InputText("password", password, IM_COUNTOF(password), uiInputTextFlags_Password);
            UI::SameLine(); HelpMarker("Display all characters as '*'.\nDisable clipboard cut and copy.\nDisable logging.\n");
            UI::InputTextWithHint("password (w/ hint)", "<password>", password, IM_COUNTOF(password), uiInputTextFlags_Password);
            UI::InputText("password (clear)", password, IM_COUNTOF(password));
            UI::TreePop();
        }

        if (UI::TreeNode("Completion, History, Edit Callbacks"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Completion, History, Edit Callbacks");
            struct Funcs
            {
                static int MyCallback(uiInputTextCallbackData* data)
                {
                    if (data->EventFlag == uiInputTextFlags_CallbackCompletion)
                    {
                        data->InsertChars(data->CursorPos, "..");
                    }
                    else if (data->EventFlag == uiInputTextFlags_CallbackHistory)
                    {
                        if (data->EventKey == uiKey_UpArrow)
                        {
                            data->DeleteChars(0, data->BufTextLen);
                            data->InsertChars(0, "Pressed Up!");
                            data->SelectAll();
                        }
                        else if (data->EventKey == uiKey_DownArrow)
                        {
                            data->DeleteChars(0, data->BufTextLen);
                            data->InsertChars(0, "Pressed Down!");
                            data->SelectAll();
                        }
                    }
                    else if (data->EventFlag == uiInputTextFlags_CallbackEdit)
                    {
                        // Toggle casing of first character
                        char c = data->Buf[0];
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) data->Buf[0] ^= 32;
                        data->BufDirty = true;

                        // Increment a counter
                        int* p_int = (int*)data->UserData;
                        *p_int = *p_int + 1;
                    }
                    return 0;
                }
            };
            static char buf1[64];
            UI::InputText("Completion", buf1, IM_COUNTOF(buf1), uiInputTextFlags_CallbackCompletion, Funcs::MyCallback);
            UI::SameLine(); HelpMarker(
                "Here we append \"..\" each time Tab is pressed. "
                "See 'Examples>Console' for a more meaningful demonstration of using this callback.");

            static char buf2[64];
            UI::InputText("History", buf2, IM_COUNTOF(buf2), uiInputTextFlags_CallbackHistory, Funcs::MyCallback);
            UI::SameLine(); HelpMarker(
                "Here we replace and select text each time Up/Down are pressed. "
                "See 'Examples>Console' for a more meaningful demonstration of using this callback.");

            static char buf3[64];
            static int edit_count = 0;
            UI::InputText("Edit", buf3, IM_COUNTOF(buf3), uiInputTextFlags_CallbackEdit, Funcs::MyCallback, (void*)&edit_count);
            UI::SameLine(); HelpMarker(
                "Here we toggle the casing of the first character on every edit + count edits.");
            UI::SameLine(); UI::Text("(%d)", edit_count);

            UI::TreePop();
        }

        if (UI::TreeNode("Resize Callback"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Resize Callback");
            // To wire InputText() with std::string or any other custom string type,
            // you can use the uiInputTextFlags_CallbackResize flag + create a custom UI::InputText() wrapper
            // using your preferred type. See misc/cpp/imgui_stdlib.h for an implementation of this using std::string.
            HelpMarker(
                "Using uiInputTextFlags_CallbackResize to wire your custom string type to InputText().\n\n"
                "See misc/cpp/imgui_stdlib.h for an implementation of this for std::string.");
            struct Funcs
            {
                static int MyResizeCallback(uiInputTextCallbackData* data)
                {
                    if (data->EventFlag == uiInputTextFlags_CallbackResize)
                    {
                        ImVector<char>* my_str = (ImVector<char>*)data->UserData;
                        IM_ASSERT(my_str->begin() == data->Buf);
                        my_str->resize(data->BufSize); // NB: On resizing calls, generally data->BufSize == data->BufTextLen + 1
                        data->Buf = my_str->begin();
                    }
                    return 0;
                }

                // Note: Because UI:: is a namespace you would typically add your own function into the namespace.
                // For example, you code may declare a function 'UI::InputText(const char* label, MyString* my_str)'
                static bool MyInputTextMultiline(const char* label, ImVector<char>* my_str, const vec2& size = vec2(0, 0), uiInputTextFlags flags = 0)
                {
                    IM_ASSERT((flags & uiInputTextFlags_CallbackResize) == 0);
                    return UI::InputTextMultiline(label, my_str->begin(), (size_t)my_str->size(), size, flags | uiInputTextFlags_CallbackResize, Funcs::MyResizeCallback, (void*)my_str);
                }
            };

            // For this demo we are using ImVector as a string container.
            // Note that because we need to store a terminating zero character, our size/capacity are 1 more
            // than usually reported by a typical string class.
            static uiInputTextFlags flags = uiInputTextFlags_None;
            UI::CheckboxFlags("uiInputTextFlags_WordWrap", &flags, uiInputTextFlags_WordWrap);

            static ImVector<char> my_str;
            if (my_str.empty())
                my_str.push_back(0);
            Funcs::MyInputTextMultiline("##MyStr", &my_str, vec2(-FLT_MIN, UI::GetTextLineHeight() * 16), flags);
            UI::Text("Data: %p\nSize: %d\nCapacity: %d", (void*)my_str.begin(), my_str.size(), my_str.capacity());
            UI::TreePop();
        }

        if (UI::TreeNode("Eliding, Alignment"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Eliding, Alignment");
            static char buf1[128] = "/path/to/some/folder/with/long/filename.cpp";
            static uiInputTextFlags flags = uiInputTextFlags_ElideLeft;
            UI::CheckboxFlags("uiInputTextFlags_ElideLeft", &flags, uiInputTextFlags_ElideLeft);
            UI::InputText("Path", buf1, IM_COUNTOF(buf1), flags);
            UI::TreePop();
        }

        if (UI::TreeNode("Miscellaneous"))
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Miscellaneous");
            static char buf1[16];
            static uiInputTextFlags flags = uiInputTextFlags_EscapeClearsAll;
            UI::CheckboxFlags("uiInputTextFlags_EscapeClearsAll", &flags, uiInputTextFlags_EscapeClearsAll);
            UI::CheckboxFlags("uiInputTextFlags_ReadOnly", &flags, uiInputTextFlags_ReadOnly);
            UI::CheckboxFlags("uiInputTextFlags_NoUndoRedo", &flags, uiInputTextFlags_NoUndoRedo);
            UI::InputText("Hello", buf1, IM_COUNTOF(buf1), flags);
            UI::TreePop();
        }

        UI::TreePop();
    }

}
//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTreeNodes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTreeNodes()
{
    if (UI::TreeNode("Tree Nodes"))
    {
        IMGUI_DEMO_MARKER("Widgets/Tree Nodes");
        // See see "Examples -> Property Editor" (ShowExampleAppPropertyEditor() function) for a fancier, data-driven tree.
        if (UI::TreeNode("Basic Trees"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Basic Trees");
            for (int i = 0; i < 5; i++)
            {
                // Use SetNextItemOpen() so set the default state of a node to be open. We could
                // also use TreeNodeEx() with the uiTreeFlags_DefaultOpen flag to achieve the same thing!
                if (i == 0)
                    UI::SetNextItemOpen(true, uiCond_Once);

                // Here we use PushID() to generate a unique base ID, and then the "" used as TreeNode id won't conflict.
                // An alternative to using 'PushID() + TreeNode("", ...)' to generate a unique ID is to use 'TreeNode((void*)(intptr_t)i, ...)',
                // aka generate a dummy pointer-sized value to be hashed. The demo below uses that technique. Both are fine.
                UI::PushID(i);
                if (UI::TreeNode("", "Child %d", i))
                {
                    UI::Text("blah blah");
                    UI::SameLine();
                    if (UI::SmallButton("button")) {}
                    UI::TreePop();
                }
                UI::PopID();
            }
            UI::TreePop();
        }

        if (UI::TreeNode("Hierarchy Lines"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Hierarchy Lines");
            static uiTreeFlags base_flags = uiTreeFlags_DrawLinesFull | uiTreeFlags_DefaultOpen;
            HelpMarker("Default option for DrawLinesXXX is stored in style.TreeLinesFlags");
            UI::CheckboxFlags("uiTreeFlags_DrawLinesNone", &base_flags, uiTreeFlags_DrawLinesNone);
            UI::CheckboxFlags("uiTreeFlags_DrawLinesFull", &base_flags, uiTreeFlags_DrawLinesFull);
            UI::CheckboxFlags("uiTreeFlags_DrawLinesToNodes", &base_flags, uiTreeFlags_DrawLinesToNodes);

            if (UI::TreeNodeEx("Parent", base_flags))
            {
                if (UI::TreeNodeEx("Child 1", base_flags))
                {
                    UI::Button("Button for Child 1");
                    UI::TreePop();
                }
                if (UI::TreeNodeEx("Child 2", base_flags))
                {
                    UI::Button("Button for Child 2");
                    UI::TreePop();
                }
                UI::Text("Remaining contents");
                UI::Text("Remaining contents");
                UI::TreePop();
            }

            UI::TreePop();
        }

        if (UI::TreeNode("Clipping Large Trees"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Clipping Large Trees");
            UI::TextWrapped(
                "- Using uiListClipper with trees is a less easy than on arrays or grids.\n"
                "- Refer to 'Demo->Examples->Property Editor' for an example of how to do that.\n"
                "- Discuss in #3823");
            UI::TreePop();
        }

        if (UI::TreeNode("Selectable Nodes"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Selectable Nodes");
            HelpMarker(
                "Manually implemented selectable nodes.\n"
                "Click to select, Ctrl+Click to toggle, click on arrows or double-click to open.\n\n"
                "You may also use the multi-select API (see 'Demo->Widgets->Selection State & Multi-Select') for more advanced multi-selection features.");

            // Hold in 'selection_mask' a simple representation of what may be user-side selection state.
            // - You may retain selection state inside or outside your objects in whatever format you see fit.
            //   You may use uiSelectionBasicStorage which is conceptually close to a set<> of identifiers.
            // - We record which node was clicked and then apply selection at the end of the loop.
            // - This is a manual and simplified reimplementation of multi-selection, which the full
            //   BeginMultiSelect() API implements better, but which is not trivial to wire for trees.
            static int selection_mask = 0x00;
            int node_clicked_idx = -1;
            for (int node_n = 0; node_n < 6; node_n++)
            {
                // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                // To alter selection we use if 'IsItemClicked() && !IsItemToggledOpen()', so clicking on an arrow doesn't alter selection.
                // In a BeginMultiSelect()/EndMultiSelect() we could use IsItemToggledSelection() but here we reimplement and use our own logic.
                uiTreeFlags flags = uiTreeFlags_OpenOnArrow | uiTreeFlags_OpenOnDoubleClick | uiTreeFlags_SpanAvailWidth;
                if (selection_mask & (1 << node_n))
                    flags |= uiTreeFlags_Selected;

                bool is_open = UI::TreeNodeEx((void*)(intptr_t)node_n, flags, "Selectable Node %d", node_n);
                if (UI::IsItemClicked() && !UI::IsItemToggledOpen())
                    node_clicked_idx = node_n;
                if (is_open)
                {
                    UI::BulletText("<Node contents here>");
                    UI::TreePop();
                }
            }
            if (node_clicked_idx != -1)
            {
                // Update selection state (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
                if (UI::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked_idx);          // Ctrl+Click to toggle
                else //if (!(selection_mask & (1 << node_clicked_idx))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked_idx);           // Click to single-select
            }
            UI::TreePop();
        }

        if (UI::TreeNode("Advanced"))
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Advanced");
            static uiTreeFlags base_flags = uiTreeFlags_OpenOnArrow | uiTreeFlags_OpenOnDoubleClick | uiTreeFlags_SpanAvailWidth;
            static bool align_label_with_current_x_position = false;
            static bool use_drag_and_drop = false;
            UI::CheckboxFlags("uiTreeFlags_OpenOnArrow", &base_flags, uiTreeFlags_OpenOnArrow);
            UI::CheckboxFlags("uiTreeFlags_OpenOnDoubleClick", &base_flags, uiTreeFlags_OpenOnDoubleClick);
            UI::CheckboxFlags("uiTreeFlags_SpanAvailWidth", &base_flags, uiTreeFlags_SpanAvailWidth); UI::SameLine(); HelpMarker("Extend hit area to all available width instead of allowing more items to be laid out after the node.");
            UI::CheckboxFlags("uiTreeFlags_SpanFullWidth", &base_flags, uiTreeFlags_SpanFullWidth);
            UI::CheckboxFlags("uiTreeFlags_SpanLabelWidth", &base_flags, uiTreeFlags_SpanLabelWidth); UI::SameLine(); HelpMarker("Reduce hit area to the text label and a bit of margin.");
            UI::CheckboxFlags("uiTreeFlags_SpanAllColumns", &base_flags, uiTreeFlags_SpanAllColumns); UI::SameLine(); HelpMarker("For use in Tables only.");
            UI::CheckboxFlags("uiTreeFlags_AllowOverlap", &base_flags, uiTreeFlags_AllowOverlap);
            UI::CheckboxFlags("uiTreeFlags_Framed", &base_flags, uiTreeFlags_Framed); UI::SameLine(); HelpMarker("Draw frame with background (e.g. for CollapsingHeader)");
            UI::CheckboxFlags("uiTreeFlags_FramePadding", &base_flags, uiTreeFlags_FramePadding);
            UI::CheckboxFlags("uiTreeFlags_NavLeftJumpsToParent", &base_flags, uiTreeFlags_NavLeftJumpsToParent);

            HelpMarker("Default option for DrawLinesXXX is stored in style.TreeLinesFlags");
            UI::CheckboxFlags("uiTreeFlags_DrawLinesNone", &base_flags, uiTreeFlags_DrawLinesNone);
            UI::CheckboxFlags("uiTreeFlags_DrawLinesFull", &base_flags, uiTreeFlags_DrawLinesFull);
            UI::CheckboxFlags("uiTreeFlags_DrawLinesToNodes", &base_flags, uiTreeFlags_DrawLinesToNodes);

            UI::Checkbox("Align label with current X position", &align_label_with_current_x_position);
            UI::Checkbox("Make Tree Nodes as drag & drop sources", &use_drag_and_drop);
            if (align_label_with_current_x_position)
                UI::Unindent(UI::GetTreeNodeToLabelSpacing());

            for (int node_n = 0; node_n < 6; node_n++)
            {
                uiTreeFlags node_flags = base_flags;
                if (node_n < 3)
                {
                    // Items 0..2 are Tree Node
                    bool is_open = UI::TreeNodeEx((void*)(intptr_t)node_n, node_flags, "Selectable Node %d", node_n);
                    if (use_drag_and_drop && UI::BeginDragDropSource())
                    {
                        UI::SetDragDropPayload("MY_TREENODE_PAYLOAD_TYPE", NULL, 0);
                        UI::Text("This is a drag and drop source");
                        UI::EndDragDropSource();
                    }
                    if (node_n == 2 && (base_flags & uiTreeFlags_SpanLabelWidth))
                    {
                        // Item 2 has an additional inline button to help demonstrate SpanLabelWidth.
                        UI::SameLine();
                        if (UI::SmallButton("button")) {}
                    }
                    if (is_open)
                    {
                        UI::BulletText("Blah blah\nBlah Blah");
                        UI::SameLine();
                        UI::SmallButton("Button");
                        UI::TreePop();
                    }
                }
                else
                {
                    // Items 3..5 are Tree Leaves
                    // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                    // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                    node_flags |= uiTreeFlags_Leaf | uiTreeFlags_NoTreePushOnOpen; // uiTreeFlags_Bullet
                    UI::TreeNodeEx((void*)(intptr_t)node_n, node_flags, "Selectable Leaf %d", node_n);
                    if (use_drag_and_drop && UI::BeginDragDropSource())
                    {
                        UI::SetDragDropPayload("MY_TREENODE_PAYLOAD_TYPE", NULL, 0);
                        UI::Text("This is a drag and drop source");
                        UI::EndDragDropSource();
                    }
                }
            }
            if (align_label_with_current_x_position)
                UI::Indent(UI::GetTreeNodeToLabelSpacing());
            UI::TreePop();
        }
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsVerticalSliders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsVerticalSliders()
{
    if (UI::TreeNode("Vertical Sliders"))
    {
        IMGUI_DEMO_MARKER("Widgets/Vertical Sliders");
        const float spacing = 4;
        UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(spacing, spacing));

        static int int_value = 0;
        UI::VSliderInt("##int", vec2(18, 160), &int_value, 0, 5);
        UI::SameLine();

        static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
        UI::PushID("set1");
        for (int i = 0; i < 7; i++)
        {
            if (i > 0) UI::SameLine();
            UI::PushID(i);
            UI::PushStyleColor(uiCol_FrameBg, (vec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
            UI::PushStyleColor(uiCol_FrameBgHovered, (vec4)ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
            UI::PushStyleColor(uiCol_FrameBgActive, (vec4)ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
            UI::PushStyleColor(uiCol_SliderGrab, (vec4)ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
            UI::VSliderFloat("##v", vec2(18, 160), &values[i], 0.0f, 1.0f, "");
            if (UI::IsItemActive() || UI::IsItemHovered())
                UI::SetTooltip("%.3f", values[i]);
            UI::PopStyleColor(4);
            UI::PopID();
        }
        UI::PopID();

        UI::SameLine();
        UI::PushID("set2");
        static float values2[4] = { 0.20f, 0.80f, 0.40f, 0.25f };
        const int rows = 3;
        const vec2 small_slider_size(18, (float)(int)((160.0f - (rows - 1) * spacing) / rows));
        for (int nx = 0; nx < 4; nx++)
        {
            if (nx > 0) UI::SameLine();
            UI::BeginGroup();
            for (int ny = 0; ny < rows; ny++)
            {
                UI::PushID(nx * rows + ny);
                UI::VSliderFloat("##v", small_slider_size, &values2[nx], 0.0f, 1.0f, "");
                if (UI::IsItemActive() || UI::IsItemHovered())
                    UI::SetTooltip("%.3f", values2[nx]);
                UI::PopID();
            }
            UI::EndGroup();
        }
        UI::PopID();

        UI::SameLine();
        UI::PushID("set3");
        for (int i = 0; i < 4; i++)
        {
            if (i > 0) UI::SameLine();
            UI::PushID(i);
            UI::PushStyleVar(uiStyleVar_GrabMinSize, 40);
            UI::VSliderFloat("##v", vec2(40, 160), &values[i], 0.0f, 1.0f, "%.2f\nsec");
            UI::PopStyleVar();
            UI::PopID();
        }
        UI::PopID();
        UI::PopStyleVar();
        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgets()
//-----------------------------------------------------------------------------

static void DemoWindowWidgets(uiDemoWindowData* demo_data)
{
    //UI::SetNextItemOpen(true, uiCond_Once);
    if (!UI::CollapsingHeader("Widgets"))
        return;
    // IMGUI_DEMO_MARKER("Widgets");

    const bool disable_all = demo_data->DisableSections; // The Checkbox for that is inside the "Disabled" section at the bottom
    if (disable_all)
        UI::BeginDisabled();

    DemoWindowWidgetsComboBoxes();
    DemoWindowWidgetsColorAndPickers();
    DemoWindowWidgetsDataTypes();

    DemoWindowWidgetsDragAndDrop();
    DemoWindowWidgetsDragsAndSliders();
    DemoWindowWidgetsFonts();
    DemoWindowWidgetsImages();
    DemoWindowWidgetsListBoxes();
    DemoWindowWidgetsMultiComponents();
    DemoWindowWidgetsPlotting();
    DemoWindowWidgetsProgressBars();
    DemoWindowWidgetsQueryingStatuses();
    DemoWindowWidgetsSelectables();
    DemoWindowWidgetsSelectionAndMultiSelect(demo_data);
    DemoWindowWidgetsTabs();
    DemoWindowWidgetsText();
    DemoWindowWidgetsTextFilter();
    DemoWindowWidgetsTextInput();
    DemoWindowWidgetsTreeNodes();
    DemoWindowWidgetsVerticalSliders();

    if (disable_all)
        UI::EndDisabled();
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowLayout()
//-----------------------------------------------------------------------------

static void DemoWindowLayout()
{
    if (!UI::CollapsingHeader("Layout & Scrolling"))
        return;

    if (UI::TreeNode("Child windows"))
    {
        IMGUI_DEMO_MARKER("Layout/Child windows");
        UI::BarrierText("Child windows");

        HelpMarker("Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window.");
        static bool disable_mouse_wheel = false;
        static bool disable_menu = false;
        UI::Checkbox("Disable Mouse Wheel", &disable_mouse_wheel);
        UI::Checkbox("Disable Menu", &disable_menu);

        // Child 1: no border, enable horizontal scrollbar
        {
            uiWindowFlags window_flags = uiWindowFlags_HorizontalScrollbar;
            if (disable_mouse_wheel)
                window_flags |= uiWindowFlags_NoScrollWithMouse;
            UI::BeginChild("ChildL", vec2(UI::GetContentRegionAvail().x * 0.5f, 260), uiChildFlags_None, window_flags);
            for (int i = 0; i < 100; i++)
                UI::Text("%04d: scrollable region", i);
            UI::EndChild();
        }

        UI::SameLine();

        // Child 2: rounded border
        {
            uiWindowFlags window_flags = uiWindowFlags_None;
            if (disable_mouse_wheel)
                window_flags |= uiWindowFlags_NoScrollWithMouse;
            if (!disable_menu)
                window_flags |= uiWindowFlags_MenuBar;
            UI::PushStyleVar(uiStyleVar_ChildRounding, 5.0f);
            UI::BeginChild("ChildR", vec2(0, 260), uiChildFlags_Borders, window_flags);
            if (!disable_menu && UI::BeginMenuBar())
            {
                if (UI::BeginMenu("Menu"))
                {
                    ShowExampleMenuFile();
                    UI::EndMenu();
                }
                UI::EndMenuBar();
            }
            if (UI::BeginTable("split", 2, uiTableFlags_Resizable | uiTableFlags_NoSavedSettings))
            {
                for (int i = 0; i < 100; i++)
                {
                    char buf[32];
                    sprintf(buf, "%03d", i);
                    UI::TableNextColumn();
                    UI::Button(buf, vec2(-FLT_MIN, 0.0f));
                }
                UI::EndTable();
            }
            UI::EndChild();
            UI::PopStyleVar();
        }

        // Child 3: manual-resize
        UI::BarrierText("Manual-resize");
        {
            HelpMarker("Drag bottom border to resize. Double-click bottom border to auto-fit to vertical contents.");
            //if (UI::Button("Set Height to 200"))
            //    UI::SetNextWindowSize(vec2(-FLT_MIN, 200.0f));

            UI::PushStyleColor(uiCol_ChildBg, UI::GetStyleColorVec4(uiCol_FrameBg));
            if (UI::BeginChild("ResizableChild", vec2(-FLT_MIN, UI::GetTextLineHeightWithSpacing() * 8), uiChildFlags_Borders | uiChildFlags_ResizeY))
                for (int n = 0; n < 10; n++)
                    UI::Text("Line %04d", n);
            UI::PopStyleColor();
            UI::EndChild();
        }

        // Child 4: auto-resizing height with a limit
        UI::BarrierText("Auto-resize with constraints");
        {
            static int draw_lines = 3;
            static int max_height_in_lines = 10;
            UI::SetNextItemWidth(UI::GetFontSize() * 8);
            UI::DragInt("Lines Count", &draw_lines, 0.2f);
            UI::SetNextItemWidth(UI::GetFontSize() * 8);
            UI::DragInt("Max Height (in Lines)", &max_height_in_lines, 0.2f);

            UI::SetNextWindowSizeConstraints(vec2(0.0f, UI::GetTextLineHeightWithSpacing() * 1), vec2(FLT_MAX, UI::GetTextLineHeightWithSpacing() * max_height_in_lines));
            if (UI::BeginChild("ConstrainedChild", vec2(-FLT_MIN, 0.0f), uiChildFlags_Borders | uiChildFlags_AutoResizeY))
                for (int n = 0; n < draw_lines; n++)
                    UI::Text("Line %04d", n);
            UI::EndChild();
        }

        UI::BarrierText("Misc/Advanced");

        // Demonstrate a few extra things
        // - Changing uiCol_ChildBg (which is transparent black in default styles)
        // - Using SetCursorPos() to position child window (the child window is an item from the POV of parent window)
        //   You can also call SetNextWindowPos() to position the child window. The parent window will effectively
        //   layout from this position.
        // - Using UI::GetItemRectMin/Max() to query the "item" state (because the child window is an item from
        //   the POV of the parent window). See 'Demo->Querying Status (Edited/Active/Hovered etc.)' for details.
        {
            static int offset_x = 0;
            static bool override_bg_color = true;
            static uiChildFlags child_flags = uiChildFlags_Borders | uiChildFlags_ResizeX | uiChildFlags_ResizeY;
            UI::SetNextItemWidth(UI::GetFontSize() * 8);
            UI::DragInt("Offset X", &offset_x, 1.0f, -1000, 1000);
            UI::Checkbox("Override ChildBg color", &override_bg_color);
            UI::CheckboxFlags("uiChildFlags_Borders", &child_flags, uiChildFlags_Borders);
            UI::CheckboxFlags("uiChildFlags_AlwaysUseWindowPadding", &child_flags, uiChildFlags_AlwaysUseWindowPadding);
            UI::CheckboxFlags("uiChildFlags_ResizeX", &child_flags, uiChildFlags_ResizeX);
            UI::CheckboxFlags("uiChildFlags_ResizeY", &child_flags, uiChildFlags_ResizeY);
            UI::CheckboxFlags("uiChildFlags_FrameStyle", &child_flags, uiChildFlags_FrameStyle);
            UI::SameLine(); HelpMarker("Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding.");
            if (child_flags & uiChildFlags_FrameStyle)
                override_bg_color = false;

            UI::SetCursorPosX(UI::GetCursorPosX() + (float)offset_x);
            if (override_bg_color)
                UI::PushStyleColor(uiCol_ChildBg, IM_COL32(255, 0, 0, 100));
            UI::BeginChild("Red", vec2(200, 100), child_flags, uiWindowFlags_None);
            if (override_bg_color)
                UI::PopStyleColor();

            for (int n = 0; n < 50; n++)
                UI::Text("Some test %d", n);
            UI::EndChild();
            bool child_is_hovered = UI::IsItemHovered();
            vec2 child_rect_min = UI::GetItemRectMin();
            vec2 child_rect_max = UI::GetItemRectMax();
            UI::Text("Hovered: %d", child_is_hovered);
            UI::Text("Rect of child window is: (%.0f,%.0f) (%.0f,%.0f)", child_rect_min.x, child_rect_min.y, child_rect_max.x, child_rect_max.y);
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Widgets Width"))
    {
        IMGUI_DEMO_MARKER("Layout/Widgets Width");
        static float f = 0.0f;
        static bool show_indented_items = true;
        UI::Checkbox("Show indented items", &show_indented_items);

        // Use SetNextItemWidth() to set the width of a single upcoming item.
        // Use PushItemWidth()/PopItemWidth() to set the width of a group of items.
        // In real code use you'll probably want to choose width values that are proportional to your font size
        // e.g. Using '20.0f * GetFontSize()' as width instead of '200.0f', etc.

        UI::Text("SetNextItemWidth/PushItemWidth(100)");
        UI::SameLine(); HelpMarker("Fixed width.");
        UI::PushItemWidth(100);
        UI::DragFloat("float##1b", &f);
        if (show_indented_items)
        {
            UI::Indent();
            UI::DragFloat("float (indented)##1b", &f);
            UI::Unindent();
        }
        UI::PopItemWidth();

        UI::Text("SetNextItemWidth/PushItemWidth(-100)");
        UI::SameLine(); HelpMarker("Align to right edge minus 100");
        UI::PushItemWidth(-100);
        UI::DragFloat("float##2a", &f);
        if (show_indented_items)
        {
            UI::Indent();
            UI::DragFloat("float (indented)##2b", &f);
            UI::Unindent();
        }
        UI::PopItemWidth();

        UI::Text("SetNextItemWidth/PushItemWidth(GetContentRegionAvail().x * 0.5f)");
        UI::SameLine(); HelpMarker("Half of available width.\n(~ right-cursor_pos)\n(works within a column set)");
        UI::PushItemWidth(UI::GetContentRegionAvail().x * 0.5f);
        UI::DragFloat("float##3a", &f);
        if (show_indented_items)
        {
            UI::Indent();
            UI::DragFloat("float (indented)##3b", &f);
            UI::Unindent();
        }
        UI::PopItemWidth();

        UI::Text("SetNextItemWidth/PushItemWidth(-GetContentRegionAvail().x * 0.5f)");
        UI::SameLine(); HelpMarker("Align to right edge minus half");
        UI::PushItemWidth(-UI::GetContentRegionAvail().x * 0.5f);
        UI::DragFloat("float##4a", &f);
        if (show_indented_items)
        {
            UI::Indent();
            UI::DragFloat("float (indented)##4b", &f);
            UI::Unindent();
        }
        UI::PopItemWidth();

        UI::Text("SetNextItemWidth/PushItemWidth(-Min(GetContentRegionAvail().x * 0.40f, GetFontSize() * 12))");
        UI::PushItemWidth(-IM_MIN(UI::GetFontSize() * 12, UI::GetContentRegionAvail().x * 0.40f));
        UI::DragFloat("float##5a", &f);
        if (show_indented_items)
        {
            UI::Indent();
            UI::DragFloat("float (indented)##5b", &f);
            UI::Unindent();
        }
        UI::PopItemWidth();

        // Demonstrate using PushItemWidth to surround three items.
        // Calling SetNextItemWidth() before each of them would have the same effect.
        UI::Text("SetNextItemWidth/PushItemWidth(-FLT_MIN)");
        UI::SameLine(); HelpMarker("Align to right edge");
        UI::PushItemWidth(-FLT_MIN);
        UI::DragFloat("##float6a", &f);
        if (show_indented_items)
        {
            UI::Indent();
            UI::DragFloat("float (indented)##6b", &f);
            UI::Unindent();
        }
        UI::PopItemWidth();

        UI::TreePop();
    }

    if (UI::TreeNode("Basic Horizontal Layout"))
    {
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout");
        UI::TextWrapped("(Use UI::SameLine() to keep adding items to the right of the preceding item)");

        // Text
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/SameLine");
        UI::Text("Two items: Hello"); UI::SameLine();
        UI::TextColored(vec4(1, 1, 0, 1), "Sailor");

        // Adjust spacing
        UI::Text("More spacing: Hello"); UI::SameLine(0, 20);
        UI::TextColored(vec4(1, 1, 0, 1), "Sailor");

        // Button
        UI::AlignTextToFramePadding();
        UI::Text("Normal buttons"); UI::SameLine();
        UI::Button("Banana"); UI::SameLine();
        UI::Button("Apple"); UI::SameLine();
        UI::Button("Corniflower");

        // Button
        UI::Text("Small buttons"); UI::SameLine();
        UI::SmallButton("Like this one"); UI::SameLine();
        UI::Text("can fit within a text block.");

        // Aligned to arbitrary position. Easy/cheap column.
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/SameLine (with offset)");
        UI::Text("Aligned");
        UI::SameLine(150); UI::Text("x=150");
        UI::SameLine(300); UI::Text("x=300");
        UI::Text("Aligned");
        UI::SameLine(150); UI::SmallButton("x=150");
        UI::SameLine(300); UI::SmallButton("x=300");

        // Checkbox
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/SameLine (more)");
        static bool c1 = false, c2 = false, c3 = false, c4 = false;
        UI::Checkbox("My", &c1); UI::SameLine();
        UI::Checkbox("Tailor", &c2); UI::SameLine();
        UI::Checkbox("Is", &c3); UI::SameLine();
        UI::Checkbox("Rich", &c4);

        // Various
        static float f0 = 1.0f, f1 = 2.0f, f2 = 3.0f;
        UI::PushItemWidth(UI::CalcTextSize("AAAAAAA").x);
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD" };
        static int item = -1;
        UI::Combo("Combo", &item, items, IM_COUNTOF(items)); UI::SameLine();
        UI::SliderFloat("X", &f0, 0.0f, 5.0f); UI::SameLine();
        UI::SliderFloat("Y", &f1, 0.0f, 5.0f); UI::SameLine();
        UI::SliderFloat("Z", &f2, 0.0f, 5.0f);

        UI::Text("Lists:");
        static int selection[4] = { 0, 1, 2, 3 };
        for (int i = 0; i < 4; i++)
        {
            if (i > 0) UI::SameLine();
            UI::PushID(i);
            UI::ListBox("", &selection[i], items, IM_COUNTOF(items));
            UI::PopID();
            //UI::SetItemTooltip("ListBox %d hovered", i);
        }
        UI::PopItemWidth();

        // Dummy
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/Dummy");
        vec2 button_sz(40, 40);
        UI::Button("A", button_sz); UI::SameLine();
        UI::Dummy(button_sz); UI::SameLine();
        UI::Button("B", button_sz);

        // Manually wrapping
        // (we should eventually provide this as an automatic layout feature, but for now you can do it manually)
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/Manual wrapping");
        UI::Text("Manual wrapping:");
        uiStyle& style = UI::GetStyle();
        int buttons_count = 20;
        float window_visible_x2 = UI::GetCursorScreenPos().x + UI::GetContentRegionAvail().x;
        for (int n = 0; n < buttons_count; n++)
        {
            UI::PushID(n);
            UI::Button("Box", button_sz);
            float last_button_x2 = UI::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
            if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
                UI::SameLine();
            UI::PopID();
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Groups"))
    {
        IMGUI_DEMO_MARKER("Layout/Groups");
        HelpMarker(
            "BeginGroup() basically locks the horizontal position for new line. "
            "EndGroup() bundles the whole group so that you can use \"item\" functions such as "
            "IsItemHovered()/IsItemActive() or SameLine() etc. on the whole group.");
        UI::BeginGroup();
        {
            UI::BeginGroup();
            UI::Button("AAA");
            UI::SameLine();
            UI::Button("BBB");
            UI::SameLine();
            UI::BeginGroup();
            UI::Button("CCC");
            UI::Button("DDD");
            UI::EndGroup();
            UI::SameLine();
            UI::Button("EEE");
            UI::EndGroup();
            UI::SetItemTooltip("First group hovered");
        }
        // Capture the group size and create widgets using the same size
        vec2 size = UI::GetItemRectSize();
        const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
        UI::PlotHistogram("##values", values, IM_COUNTOF(values), 0, NULL, 0.0f, 1.0f, size);

        UI::Button("ACTION", vec2((size.x - UI::GetStyle().ItemSpacing.x) * 0.5f, size.y));
        UI::SameLine();
        UI::Button("REACTION", vec2((size.x - UI::GetStyle().ItemSpacing.x) * 0.5f, size.y));
        UI::EndGroup();
        UI::SameLine();

        UI::Button("LEVERAGE\nBUZZWORD", size);
        UI::SameLine();

        if (UI::BeginListBox("List", size))
        {
            UI::Selectable("Selected", true);
            UI::Selectable("Not Selected", false);
            UI::EndListBox();
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Text Baseline Alignment"))
    {
        IMGUI_DEMO_MARKER("Layout/Text Baseline Alignment");
        {
            UI::BulletText("Text baseline:");
            UI::SameLine(); HelpMarker(
                "This is testing the vertical alignment that gets applied on text to keep it aligned with widgets. "
                "Lines only composed of text or \"small\" widgets use less vertical space than lines with framed widgets.");
            UI::Indent();

            UI::Text("KO Blahblah"); UI::SameLine();
            UI::Button("Some framed item"); UI::SameLine();
            HelpMarker("Baseline of button will look misaligned with text..");

            // If your line starts with text, call AlignTextToFramePadding() to align text to upcoming widgets.
            // (because we don't know what's coming after the Text() statement, we need to move the text baseline
            // down by FramePadding.y ahead of time)
            UI::AlignTextToFramePadding();
            UI::Text("OK Blahblah"); UI::SameLine();
            UI::Button("Some framed item##2"); UI::SameLine();
            HelpMarker("We call AlignTextToFramePadding() to vertically align the text baseline by +FramePadding.y");

            // SmallButton() uses the same vertical padding as Text
            UI::Button("TEST##1"); UI::SameLine();
            UI::Text("TEST"); UI::SameLine();
            UI::SmallButton("TEST##2");

            // If your line starts with text, call AlignTextToFramePadding() to align text to upcoming widgets.
            UI::AlignTextToFramePadding();
            UI::Text("Text aligned to framed item"); UI::SameLine();
            UI::Button("Item##1"); UI::SameLine();
            UI::Text("Item"); UI::SameLine();
            UI::SmallButton("Item##2"); UI::SameLine();
            UI::Button("Item##3");

            UI::Unindent();
        }

        UI::Spacing();

        {
            UI::BulletText("Multi-line text:");
            UI::Indent();
            UI::Text("One\nTwo\nThree"); UI::SameLine();
            UI::Text("Hello\nWorld"); UI::SameLine();
            UI::Text("Banana");

            UI::Text("Banana"); UI::SameLine();
            UI::Text("Hello\nWorld"); UI::SameLine();
            UI::Text("One\nTwo\nThree");

            UI::Button("HOP##1"); UI::SameLine();
            UI::Text("Banana"); UI::SameLine();
            UI::Text("Hello\nWorld"); UI::SameLine();
            UI::Text("Banana");

            UI::Button("HOP##2"); UI::SameLine();
            UI::Text("Hello\nWorld"); UI::SameLine();
            UI::Text("Banana");
            UI::Unindent();
        }

        UI::Spacing();

        {
            UI::BulletText("Misc items:");
            UI::Indent();

            // SmallButton() sets FramePadding to zero. Text baseline is aligned to match baseline of previous Button.
            UI::Button("80x80", vec2(80, 80));
            UI::SameLine();
            UI::Button("50x50", vec2(50, 50));
            UI::SameLine();
            UI::Button("Button()");
            UI::SameLine();
            UI::SmallButton("SmallButton()");

            // Tree
            // (here the node appears after a button and has odd intent, so we use uiTreeFlags_DrawLinesNone to disable hierarchy outline)
            const float spacing = UI::GetStyle().ItemInnerSpacing.x;
            UI::Button("Button##1"); // Will make line higher
            UI::SameLine(0.0f, spacing);
            if (UI::TreeNodeEx("Node##1", uiTreeFlags_DrawLinesNone))
            {
                // Placeholder tree data
                for (int i = 0; i < 6; i++)
                    UI::BulletText("Item %d..", i);
                UI::TreePop();
            }

            const float padding = (float)(int)(UI::GetFontSize() * 1.20f); // Large padding
            UI::PushStyleVarY(uiStyleVar_FramePadding, padding);
            UI::Button("Button##2");
            UI::PopStyleVar();
            UI::SameLine(0.0f, spacing);
            if (UI::TreeNodeEx("Node##2", uiTreeFlags_DrawLinesNone))
                UI::TreePop();

            // Vertically align text node a bit lower so it'll be vertically centered with upcoming widget.
            // Otherwise you can use SmallButton() (smaller fit).
            UI::AlignTextToFramePadding();

            // Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add
            // other contents "inside" the node.
            bool node_open = UI::TreeNode("Node##3");
            UI::SameLine(0.0f, spacing); UI::Button("Button##3");
            if (node_open)
            {
                // Placeholder tree data
                for (int i = 0; i < 6; i++)
                    UI::BulletText("Item %d..", i);
                UI::TreePop();
            }

            // Bullet
            UI::Button("Button##4");
            UI::SameLine(0.0f, spacing);
            UI::BulletText("Bullet text");

            UI::AlignTextToFramePadding();
            UI::BulletText("Node");
            UI::SameLine(0.0f, spacing); UI::Button("Button##5");
            UI::Unindent();
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Scrolling"))
    {
        IMGUI_DEMO_MARKER("Layout/Scrolling/Vertical");
        // Vertical scroll functions
        HelpMarker("Use SetScrollHereY() or SetScrollFromPosY() to scroll to a given vertical position.");

        static int track_item = 50;
        static bool enable_track = true;
        static bool enable_extra_decorations = false;
        static float scroll_to_off_px = 0.0f;
        static float scroll_to_pos_px = 200.0f;

        UI::Checkbox("Decoration", &enable_extra_decorations);

        UI::PushItemWidth(UI::GetFontSize() * 10);
        enable_track |= UI::DragInt("##item", &track_item, 0.25f, 0, 99, "Item = %d");
        UI::SameLine();
        UI::Checkbox("Track", &enable_track);

        bool scroll_to_off = UI::DragFloat("##off", &scroll_to_off_px, 1.00f, 0, FLT_MAX, "+%.0f px");
        UI::SameLine();
        scroll_to_off |= UI::Button("Scroll Offset");

        bool scroll_to_pos = UI::DragFloat("##pos", &scroll_to_pos_px, 1.00f, -10, FLT_MAX, "X/Y = %.0f px");
        UI::SameLine();
        scroll_to_pos |= UI::Button("Scroll To Pos");
        UI::PopItemWidth();

        if (scroll_to_off || scroll_to_pos)
            enable_track = false;

        uiStyle& style = UI::GetStyle();
        float child_w = (UI::GetContentRegionAvail().x - 4 * style.ItemSpacing.x) / 5;
        if (child_w < 1.0f)
            child_w = 1.0f;
        UI::PushID("##VerticalScrolling");
        for (int i = 0; i < 5; i++)
        {
            if (i > 0) UI::SameLine();
            UI::BeginGroup();
            const char* names[] = { "Top", "25%", "Center", "75%", "Bottom" };
            UI::TextUnformatted(names[i]);

            const uiWindowFlags child_flags = enable_extra_decorations ? uiWindowFlags_MenuBar : 0;
            const uiID child_id = UI::GetID((void*)(intptr_t)i);
            const bool child_is_visible = UI::BeginChild(child_id, vec2(child_w, 200.0f), uiChildFlags_Borders, child_flags);
            if (UI::BeginMenuBar())
            {
                UI::TextUnformatted("abc");
                UI::EndMenuBar();
            }
            if (scroll_to_off)
                UI::SetScrollY(scroll_to_off_px);
            if (scroll_to_pos)
                UI::SetScrollFromPosY(UI::GetCursorStartPos().y + scroll_to_pos_px, i * 0.25f);
            if (child_is_visible) // Avoid calling SetScrollHereY when running with culled items
            {
                for (int item = 0; item < 100; item++)
                {
                    if (enable_track && item == track_item)
                    {
                        UI::TextColored(vec4(1, 1, 0, 1), "Item %d", item);
                        UI::SetScrollHereY(i * 0.25f); // 0.0f:top, 0.5f:center, 1.0f:bottom
                    }
                    else
                    {
                        UI::Text("Item %d", item);
                    }
                }
            }
            float scroll_y = UI::GetScrollY();
            float scroll_max_y = UI::GetScrollMaxY();
            UI::EndChild();
            UI::Text("%.0f/%.0f", scroll_y, scroll_max_y);
            UI::EndGroup();
        }
        UI::PopID();

        // Horizontal scroll functions
        IMGUI_DEMO_MARKER("Layout/Scrolling/Horizontal");
        UI::Spacing();
        HelpMarker(
            "Use SetScrollHereX() or SetScrollFromPosX() to scroll to a given horizontal position.\n\n"
            "Because the clipping rectangle of most window hides half worth of WindowPadding on the "
            "left/right, using SetScrollFromPosX(+1) will usually result in clipped text whereas the "
            "equivalent SetScrollFromPosY(+1) wouldn't.");
        UI::PushID("##HorizontalScrolling");
        for (int i = 0; i < 5; i++)
        {
            float child_height = UI::GetTextLineHeight() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
            uiWindowFlags child_flags = uiWindowFlags_HorizontalScrollbar | (enable_extra_decorations ? uiWindowFlags_AlwaysVerticalScrollbar : 0);
            uiID child_id = UI::GetID((void*)(intptr_t)i);
            bool child_is_visible = UI::BeginChild(child_id, vec2(-100, child_height), uiChildFlags_Borders, child_flags);
            if (scroll_to_off)
                UI::SetScrollX(scroll_to_off_px);
            if (scroll_to_pos)
                UI::SetScrollFromPosX(UI::GetCursorStartPos().x + scroll_to_pos_px, i * 0.25f);
            if (child_is_visible) // Avoid calling SetScrollHereY when running with culled items
            {
                for (int item = 0; item < 100; item++)
                {
                    if (item > 0)
                        UI::SameLine();
                    if (enable_track && item == track_item)
                    {
                        UI::TextColored(vec4(1, 1, 0, 1), "Item %d", item);
                        UI::SetScrollHereX(i * 0.25f); // 0.0f:left, 0.5f:center, 1.0f:right
                    }
                    else
                    {
                        UI::Text("Item %d", item);
                    }
                }
            }
            float scroll_x = UI::GetScrollX();
            float scroll_max_x = UI::GetScrollMaxX();
            UI::EndChild();
            UI::SameLine();
            const char* names[] = { "Left", "25%", "Center", "75%", "Right" };
            UI::Text("%s\n%.0f/%.0f", names[i], scroll_x, scroll_max_x);
            UI::Spacing();
        }
        UI::PopID();

        // Miscellaneous Horizontal Scrolling Demo
        IMGUI_DEMO_MARKER("Layout/Scrolling/Horizontal (more)");
        HelpMarker(
            "Horizontal scrolling for a window is enabled via the uiWindowFlags_HorizontalScrollbar flag.\n\n"
            "You may want to also explicitly specify content width by using SetNextWindowContentWidth() before Begin().");
        static int lines = 7;
        UI::SliderInt("Lines", &lines, 1, 15);
        UI::PushStyleVar(uiStyleVar_FrameRounding, 3.0f);
        UI::PushStyleVar(uiStyleVar_FramePadding, vec2(2.0f, 1.0f));
        vec2 scrolling_child_size = vec2(0, UI::GetFrameHeightWithSpacing() * 7 + 30);
        UI::BeginChild("scrolling", scrolling_child_size, uiChildFlags_Borders, uiWindowFlags_HorizontalScrollbar);
        for (int line = 0; line < lines; line++)
        {
            // Display random stuff. For the sake of this trivial demo we are using basic Button() + SameLine()
            // If you want to create your own time line for a real application you may be better off manipulating
            // the cursor position yourself, aka using SetCursorPos/SetCursorScreenPos to position the widgets
            // yourself. You may also want to use the lower-level ImDrawList API.
            int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
            for (int n = 0; n < num_buttons; n++)
            {
                if (n > 0) UI::SameLine();
                UI::PushID(n + line * 1000);
                char num_buf[16];
                sprintf(num_buf, "%d", n);
                const char* label = (!(n % 15)) ? "FizzBuzz" : (!(n % 3)) ? "Fizz" : (!(n % 5)) ? "Buzz" : num_buf;
                float hue = n * 0.05f;
                UI::PushStyleColor(uiCol_Button, (vec4)ImColor::HSV(hue, 0.6f, 0.6f));
                UI::PushStyleColor(uiCol_ButtonHovered, (vec4)ImColor::HSV(hue, 0.7f, 0.7f));
                UI::PushStyleColor(uiCol_ButtonActive, (vec4)ImColor::HSV(hue, 0.8f, 0.8f));
                UI::Button(label, vec2(40.0f + sinf((float)(line + n)) * 20.0f, 0.0f));
                UI::PopStyleColor(3);
                UI::PopID();
            }
        }
        float scroll_x = UI::GetScrollX();
        float scroll_max_x = UI::GetScrollMaxX();
        UI::EndChild();
        UI::PopStyleVar(2);
        float scroll_x_delta = 0.0f;
        UI::SmallButton("<<");
        if (UI::IsItemActive())
            scroll_x_delta = -UI::GetIO().DeltaTime * 1000.0f;
        UI::SameLine();
        UI::Text("Scroll from code"); UI::SameLine();
        UI::SmallButton(">>");
        if (UI::IsItemActive())
            scroll_x_delta = +UI::GetIO().DeltaTime * 1000.0f;
        UI::SameLine();
        UI::Text("%.0f/%.0f", scroll_x, scroll_max_x);
        if (scroll_x_delta != 0.0f)
        {
            // Demonstrate a trick: you can use Begin to set yourself in the context of another window
            // (here we are already out of your child window)
            UI::BeginChild("scrolling");
            UI::SetScrollX(UI::GetScrollX() + scroll_x_delta);
            UI::EndChild();
        }
        UI::Spacing();

        static bool show_horizontal_contents_size_demo_window = false;
        UI::Checkbox("Show Horizontal contents size demo window", &show_horizontal_contents_size_demo_window);

        if (show_horizontal_contents_size_demo_window)
        {
            static bool show_h_scrollbar = true;
            static bool show_button = true;
            static bool show_tree_nodes = true;
            static bool show_text_wrapped = false;
            static bool show_columns = true;
            static bool show_tab_bar = true;
            static bool show_child = false;
            static bool explicit_content_size = false;
            static float contents_size_x = 300.0f;
            if (explicit_content_size)
                UI::SetNextWindowContentSize(vec2(contents_size_x, 0.0f));
            UI::Begin("Horizontal contents size demo window", &show_horizontal_contents_size_demo_window, show_h_scrollbar ? uiWindowFlags_HorizontalScrollbar : 0);
            IMGUI_DEMO_MARKER("Layout/Scrolling/Horizontal contents size demo window");
            UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(2, 0));
            UI::PushStyleVar(uiStyleVar_FramePadding, vec2(2, 0));
            HelpMarker(
                "Test how different widgets react and impact the work rectangle growing when horizontal scrolling is enabled.\n\n"
                "Use 'Metrics->Tools->Show windows rectangles' to visualize rectangles.");
            UI::Checkbox("H-scrollbar", &show_h_scrollbar);
            UI::Checkbox("Button", &show_button);            // Will grow contents size (unless explicitly overwritten)
            UI::Checkbox("Tree nodes", &show_tree_nodes);    // Will grow contents size and display highlight over full width
            UI::Checkbox("Text wrapped", &show_text_wrapped);// Will grow and use contents size
            UI::Checkbox("Columns", &show_columns);          // Will use contents size
            UI::Checkbox("Tab bar", &show_tab_bar);          // Will use contents size
            UI::Checkbox("Child", &show_child);              // Will grow and use contents size
            UI::Checkbox("Explicit content size", &explicit_content_size);
            UI::Text("Scroll %.1f/%.1f %.1f/%.1f", UI::GetScrollX(), UI::GetScrollMaxX(), UI::GetScrollY(), UI::GetScrollMaxY());
            if (explicit_content_size)
            {
                UI::SameLine();
                UI::SetNextItemWidth(UI::CalcTextSize("123456").x);
                UI::DragFloat("##csx", &contents_size_x);
                vec2 p = UI::GetCursorScreenPos();
                UI::GetWindowDrawList()->AddRectFilled(p, vec2(p.x + 10, p.y + 10), IM_COL32_WHITE);
                UI::GetWindowDrawList()->AddRectFilled(vec2(p.x + contents_size_x - 10, p.y), vec2(p.x + contents_size_x, p.y + 10), IM_COL32_WHITE);
                UI::Dummy(vec2(0, 10));
            }
            UI::PopStyleVar(2);
            UI::Barrier();
            if (show_button)
            {
                UI::Button("this is a 300-wide button", vec2(300, 0));
            }
            if (show_tree_nodes)
            {
                bool open = true;
                if (UI::TreeNode("this is a tree node"))
                {
                    if (UI::TreeNode("another one of those tree node..."))
                    {
                        UI::Text("Some tree contents");
                        UI::TreePop();
                    }
                    UI::TreePop();
                }
                UI::CollapsingHeader("CollapsingHeader", &open);
            }
            if (show_text_wrapped)
            {
                UI::TextWrapped("This text should automatically wrap on the edge of the work rectangle.");
            }
            if (show_columns)
            {
                UI::Text("Tables:");
                if (UI::BeginTable("table", 4, uiTableFlags_Borders))
                {
                    for (int n = 0; n < 4; n++)
                    {
                        UI::TableNextColumn();
                        UI::Text("Width %.2f", UI::GetContentRegionAvail().x);
                    }
                    UI::EndTable();
                }
                UI::Text("Columns:");
                UI::Columns(4);
                for (int n = 0; n < 4; n++)
                {
                    UI::Text("Width %.2f", UI::GetColumnWidth());
                    UI::NextColumn();
                }
                UI::Columns(1);
            }
            if (show_tab_bar && UI::BeginTabBar("Hello"))
            {
                if (UI::BeginTabItem("OneOneOne")) { UI::EndTabItem(); }
                if (UI::BeginTabItem("TwoTwoTwo")) { UI::EndTabItem(); }
                if (UI::BeginTabItem("ThreeThreeThree")) { UI::EndTabItem(); }
                if (UI::BeginTabItem("FourFourFour")) { UI::EndTabItem(); }
                UI::EndTabBar();
            }
            if (show_child)
            {
                UI::BeginChild("child", vec2(0, 0), uiChildFlags_Borders);
                UI::EndChild();
            }
            UI::End();
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Text Clipping"))
    {
        IMGUI_DEMO_MARKER("Layout/Text Clipping");
        static vec2 size(100.0f, 100.0f);
        static vec2 offset(30.0f, 30.0f);
        UI::DragFloat2("size", (float*)&size, 0.5f, 1.0f, 200.0f, "%.0f");
        UI::TextWrapped("(Click and drag to scroll)");

        HelpMarker(
            "(Left) Using UI::PushClipRect():\n"
            "Will alter ImGui hit-testing logic + ImDrawList rendering.\n"
            "(use this if you want your clipping rectangle to affect interactions)\n\n"
            "(Center) Using ImDrawList::PushClipRect():\n"
            "Will alter ImDrawList rendering only.\n"
            "(use this as a shortcut if you are only using ImDrawList calls)\n\n"
            "(Right) Using ImDrawList::AddText() with a fine ClipRect:\n"
            "Will alter only this specific ImDrawList::AddText() rendering.\n"
            "This is often used internally to avoid altering the clipping rectangle and minimize draw calls.");

        for (int n = 0; n < 3; n++)
        {
            if (n > 0)
                UI::SameLine();

            UI::PushID(n);
            UI::InvisibleButton("##canvas", size);
            if (UI::IsItemActive() && UI::IsMouseDragging(uiMouseButton_Left))
            {
                offset.x += UI::GetIO().MouseDelta.x;
                offset.y += UI::GetIO().MouseDelta.y;
            }
            UI::PopID();
            if (!UI::IsItemVisible()) // Skip rendering as ImDrawList elements are not clipped.
                continue;

            const vec2 p0 = UI::GetItemRectMin();
            const vec2 p1 = UI::GetItemRectMax();
            const char* text_str = "Line 1 hello\nLine 2 clip me!";
            const vec2 text_pos = vec2(p0.x + offset.x, p0.y + offset.y);
            ImDrawList* draw_list = UI::GetWindowDrawList();
            switch (n)
            {
            case 0:
                UI::PushClipRect(p0, p1, true);
                draw_list->AddRectFilled(p0, p1, IM_COL32(90, 90, 120, 255));
                draw_list->AddText(text_pos, IM_COL32_WHITE, text_str);
                UI::PopClipRect();
                break;
            case 1:
                draw_list->PushClipRect(p0, p1, true);
                draw_list->AddRectFilled(p0, p1, IM_COL32(90, 90, 120, 255));
                draw_list->AddText(text_pos, IM_COL32_WHITE, text_str);
                draw_list->PopClipRect();
                break;
            case 2:
                vec4 clip_rect(p0.x, p0.y, p1.x, p1.y); // AddText() takes a vec4* here so let's convert.
                draw_list->AddRectFilled(p0, p1, IM_COL32(90, 90, 120, 255));
                draw_list->AddText(UI::GetFont(), UI::GetFontSize(), text_pos, IM_COL32_WHITE, text_str, NULL, 0.0f, &clip_rect);
                break;
            }
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Overlap Mode"))
    {
        IMGUI_DEMO_MARKER("Layout/Overlap Mode");
        static bool enable_allow_overlap = true;

        HelpMarker(
            "Hit-testing is by default performed in item submission order, which generally is perceived as 'back-to-front'.\n\n"
            "By using SetNextItemAllowOverlap() you can notify that an item may be overlapped by another. "
            "Doing so alters the hovering logic: items using AllowOverlap mode requires an extra frame to accept hovered state.");
        UI::Checkbox("Enable AllowOverlap", &enable_allow_overlap);

        vec2 button1_pos = UI::GetCursorScreenPos();
        vec2 button2_pos = vec2(button1_pos.x + 50.0f, button1_pos.y + 50.0f);
        if (enable_allow_overlap)
            UI::SetNextItemAllowOverlap();
        UI::Button("Button 1", vec2(80, 80));
        UI::SetCursorScreenPos(button2_pos);
        UI::Button("Button 2", vec2(80, 80));

        // This is typically used with width-spanning items.
        // (note that Selectable() has a dedicated flag uiSelectFlags_AllowOverlap, which is a shortcut
        // for using SetNextItemAllowOverlap(). For demo purpose we use SetNextItemAllowOverlap() here.)
        if (enable_allow_overlap)
            UI::SetNextItemAllowOverlap();
        UI::Selectable("Some Selectable", false);
        UI::SameLine();
        UI::SmallButton("++");

        UI::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowPopups()
//-----------------------------------------------------------------------------

static void DemoWindowPopups()
{
    if (!UI::CollapsingHeader("Popups & Modal windows"))
        return;

    // The properties of popups windows are:
    // - They block normal mouse hovering detection outside them. (*)
    // - Unless modal, they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
    // - Their visibility state (~bool) is held internally by Dear ImGui instead of being held by the programmer as
    //   we are used to with regular Begin() calls. User can manipulate the visibility state by calling OpenPopup().
    // (*) One can use IsItemHovered(uiHoverFlags_AllowWhenBlockedByPopup) to bypass it and detect hovering even
    //     when normally blocked by a popup.
    // Those three properties are connected. The library needs to hold their visibility state BECAUSE it can close
    // popups at any time.

    // Typical use for regular windows:
    //   bool my_tool_is_active = false; if (UI::Button("Open")) my_tool_is_active = true; [...] if (my_tool_is_active) Begin("My Tool", &my_tool_is_active) { [...] } End();
    // Typical use for popups:
    //   if (UI::Button("Open")) UI::OpenPopup("MyPopup"); if (UI::BeginPopup("MyPopup")) { [...] EndPopup(); }

    // With popups we have to go through a library call (here OpenPopup) to manipulate the visibility state.
    // This may be a bit confusing at first but it should quickly make sense. Follow on the examples below.

    if (UI::TreeNode("Popups"))
    {
        UI::TextWrapped(
            "When a popup is active, it inhibits interacting with windows that are behind the popup. "
            "Clicking outside the popup closes it.");

        static int selected_fish = -1;
        const char* names[] = { "Bream", "Haddock", "Mackerel", "Pollock", "Tilefish" };
        static bool toggles[] = { true, false, false, false, false };

        // Simple selection popup (if you want to show the current selection inside the Button itself,
        // you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
        if (UI::Button("Select.."))
            UI::OpenPopup("my_select_popup");
        UI::SameLine();
        UI::TextUnformatted(selected_fish == -1 ? "<None>" : names[selected_fish]);
        if (UI::BeginPopup("my_select_popup"))
        {
            UI::BarrierText("Aquarium");
            for (int i = 0; i < IM_COUNTOF(names); i++)
                if (UI::Selectable(names[i]))
                    selected_fish = i;
            UI::EndPopup();
        }

        // Showing a menu with toggles
        if (UI::Button("Toggle.."))
            UI::OpenPopup("my_toggle_popup");
        if (UI::BeginPopup("my_toggle_popup"))
        {
            for (int i = 0; i < IM_COUNTOF(names); i++)
                UI::MenuItem(names[i], "", &toggles[i]);
            if (UI::BeginMenu("Sub-menu"))
            {
                UI::MenuItem("Click me");
                UI::EndMenu();
            }

            UI::Barrier();
            UI::Text("Tooltip here");
            UI::SetItemTooltip("I am a tooltip over a popup");

            if (UI::Button("Stacked Popup"))
                UI::OpenPopup("another popup");
            if (UI::BeginPopup("another popup"))
            {
                for (int i = 0; i < IM_COUNTOF(names); i++)
                    UI::MenuItem(names[i], "", &toggles[i]);
                if (UI::BeginMenu("Sub-menu"))
                {
                    UI::MenuItem("Click me");
                    if (UI::Button("Stacked Popup"))
                        UI::OpenPopup("another popup");
                    if (UI::BeginPopup("another popup"))
                    {
                        UI::Text("I am the last one here.");
                        UI::EndPopup();
                    }
                    UI::EndMenu();
                }
                UI::EndPopup();
            }
            UI::EndPopup();
        }

        // Call the more complete ShowExampleMenuFile which we use in various places of this demo
        if (UI::Button("With a menu.."))
            UI::OpenPopup("my_file_popup");
        if (UI::BeginPopup("my_file_popup", uiWindowFlags_MenuBar))
        {
            if (UI::BeginMenuBar())
            {
                if (UI::BeginMenu("File"))
                {
                    ShowExampleMenuFile();
                    UI::EndMenu();
                }
                if (UI::BeginMenu("Edit"))
                {
                    UI::MenuItem("Dummy");
                    UI::EndMenu();
                }
                UI::EndMenuBar();
            }
            UI::Text("Hello from popup!");
            UI::Button("This is a dummy button..");
            UI::EndPopup();
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Context menus"))
    {
        HelpMarker("\"Context\" functions are simple helpers to associate a Popup to a given Item or Window identifier.");

        // BeginPopupContextItem() is a helper to provide common/simple popup behavior of essentially doing:
        //     if (id == 0)
        //         id = GetItemID(); // Use last item id
        //     if (IsItemHovered() && IsMouseReleased(uiMouseButton_Right))
        //         OpenPopup(id);
        //     return BeginPopup(id);
        // For advanced uses you may want to replicate and customize this code.
        // See more details in BeginPopupContextItem().

        // Example 1
        // When used after an item that has an ID (e.g. Button), we can skip providing an ID to BeginPopupContextItem(),
        // and BeginPopupContextItem() will use the last item ID as the popup ID.
        {
            const char* names[5] = { "Label1", "Label2", "Label3", "Label4", "Label5" };
            static int selected = -1;
            for (int n = 0; n < 5; n++)
            {
                if (UI::Selectable(names[n], selected == n))
                    selected = n;
                if (UI::BeginPopupContextItem()) // <-- use last item id as popup id
                {
                    selected = n;
                    UI::Text("This is a popup for \"%s\"!", names[n]);
                    if (UI::Button("Close"))
                        UI::CloseCurrentPopup();
                    UI::EndPopup();
                }
                UI::SetItemTooltip("Right-click to open popup");
            }
        }

        // Example 2
        // Popup on a Text() element which doesn't have an identifier: we need to provide an identifier to BeginPopupContextItem().
        // Using an explicit identifier is also convenient if you want to activate the popups from different locations.
        {
            HelpMarker("Text() elements don't have stable identifiers so we need to provide one.");
            static float value = 0.5f;
            UI::Text("Value = %.3f <-- (1) right-click this text", value);
            if (UI::BeginPopupContextItem("my popup"))
            {
                if (UI::Selectable("Set to zero")) value = 0.0f;
                if (UI::Selectable("Set to PI")) value = 3.1415f;
                UI::SetNextItemWidth(-FLT_MIN);
                UI::DragFloat("##Value", &value, 0.1f, 0.0f, 0.0f);
                UI::EndPopup();
            }

            // We can also use OpenPopupOnItemClick() to toggle the visibility of a given popup.
            // Here we make it that right-clicking this other text element opens the same popup as above.
            // The popup itself will be submitted by the code above.
            UI::Text("(2) Or right-click this text");
            UI::OpenPopupOnItemClick("my popup", uiPopupFlags_MouseButtonRight);

            // Back to square one: manually open the same popup.
            if (UI::Button("(3) Or click this button"))
                UI::OpenPopup("my popup");
        }

        // Example 3
        // When using BeginPopupContextItem() with an implicit identifier (NULL == use last item ID),
        // we need to make sure your item identifier is stable.
        // In this example we showcase altering the item label while preserving its identifier, using the ### operator (see FAQ).
        {
            HelpMarker("Showcase using a popup ID linked to item ID, with the item having a changing label + stable ID using the ### operator.");
            static char name[32] = "Label1";
            char buf[64];
            sprintf(buf, "Button: %s###Button", name); // ### operator override ID ignoring the preceding label
            UI::Button(buf);
            if (UI::BeginPopupContextItem())
            {
                UI::Text("Edit name:");
                UI::InputText("##edit", name, IM_COUNTOF(name));
                if (UI::Button("Close"))
                    UI::CloseCurrentPopup();
                UI::EndPopup();
            }
            UI::SameLine(); UI::Text("(<-- right-click here)");
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Modals"))
    {
        UI::TextWrapped("Modal windows are like popups but the user cannot close them by clicking outside.");

        if (UI::Button("Delete.."))
            UI::OpenPopup("Delete?");

        // Always center this window when appearing
        vec2 center = UI::GetMainViewport()->GetCenter();
        UI::SetNextWindowPos(center, uiCond_Appearing, vec2(0.5f, 0.5f));

        if (UI::BeginPopupModal("Delete?", NULL, uiWindowFlags_AutoResize))
        {
            UI::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!");
            UI::Barrier();

            //static int unused_i = 0;
            //UI::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

            static bool dont_ask_me_next_time = false;
            UI::PushStyleVar(uiStyleVar_FramePadding, vec2(0, 0));
            UI::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
            UI::PopStyleVar();

            if (UI::Button("OK", vec2(120, 0))) { UI::CloseCurrentPopup(); }
            UI::SetItemDefaultFocus();
            UI::SameLine();
            if (UI::Button("Cancel", vec2(120, 0))) { UI::CloseCurrentPopup(); }
            UI::EndPopup();
        }

        if (UI::Button("Stacked modals.."))
            UI::OpenPopup("Stacked 1");
        if (UI::BeginPopupModal("Stacked 1", NULL, uiWindowFlags_MenuBar))
        {
            if (UI::BeginMenuBar())
            {
                if (UI::BeginMenu("File"))
                {
                    if (UI::MenuItem("Some menu item")) {}
                    UI::EndMenu();
                }
                UI::EndMenuBar();
            }
            UI::Text("Hello from Stacked The First\nUsing style.Colors[uiCol_ModalWindowDimBg] behind it.");

            // Testing behavior of widgets stacking their own regular popups over the modal.
            static int item = 1;
            static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            UI::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
            UI::ColorEdit4("Color", color);

            if (UI::Button("Add another modal.."))
                UI::OpenPopup("Stacked 2");

            // Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which
            // will close the popup. Note that the visibility state of popups is owned by imgui, so the input value
            // of the bool actually doesn't matter here.
            bool unused_open = true;
            if (UI::BeginPopupModal("Stacked 2", &unused_open))
            {
                UI::Text("Hello from Stacked The Second!");
                UI::ColorEdit4("Color", color); // Allow opening another nested popup
                if (UI::Button("Close"))
                    UI::CloseCurrentPopup();
                UI::EndPopup();
            }

            if (UI::Button("Close"))
                UI::CloseCurrentPopup();
            UI::EndPopup();
        }

        UI::TreePop();
    }

    if (UI::TreeNode("Menus inside a regular window"))
    {
        UI::TextWrapped("Below we are testing adding menu items to a regular window. It's rather unusual but should work!");
        UI::Barrier();

        UI::MenuItem("Menu item", "Ctrl+M");
        if (UI::BeginMenu("Menu inside a regular window"))
        {
            ShowExampleMenuFile();
            UI::EndMenu();
        }
        UI::Barrier();
        UI::TreePop();
    }
}

// Dummy data structure that we use for the Table demo.
// (pre-C++11 doesn't allow us to instantiate ImVector<MyItem> template if this structure is defined inside the demo function)
namespace {
// We are passing our own identifier to TableSetupColumn() to facilitate identifying columns in the sorting code.
// This identifier will be passed down into uiTableSortSpec::ColumnUserID.
// But it is possible to omit the user id parameter of TableSetupColumn() and just use the column index instead! (uiTableSortSpec::ColumnIndex)
// If you don't use sorting, you will generally never care about giving column an ID!
enum MyItemColumnID {
    MyItemColumnID_ID,
    MyItemColumnID_Name,
    MyItemColumnID_Action,
    MyItemColumnID_Quantity,
    MyItemColumnID_Description
};
struct MyItem {
    int         ID;
    const char* Name;
    int         Quantity;
    // We have a problem which is affecting _only this demo_ and should not affect your code:
    // As we don't rely on std:: or other third-party library to compile dear imgui, we only have reliable access to qsort(),
    // however qsort doesn't allow passing user data to comparing function.
    // As a workaround, we are storing the sort specs in a static/global for the comparing function to access.
    // In your own use case you would probably pass the sort specs to your sorting/comparing functions directly and not use a global.
    // We could technically call UI::TableGetSortSpecs() in CompareWithSortSpecs(), but considering that this function is called
    // very often by the sorting algorithm it would be a little wasteful.
    static const uiTableSortSpecs* s_current_sort_specs;
    static void SortWithSortSpecs(uiTableSortSpecs* sort_specs, MyItem* items, int items_count) {
        s_current_sort_specs = sort_specs; // Store in variable accessible by the sort function.
        if (items_count > 1)
            qsort(items, (size_t)items_count, sizeof(items[0]), MyItem::CompareWithSortSpecs);
        s_current_sort_specs = NULL;
    }
    // Compare function to be used by qsort()
    static int IMGUI_CDECL CompareWithSortSpecs(const void* lhs, const void* rhs) {
        const MyItem* a = (const MyItem*)lhs;
        const MyItem* b = (const MyItem*)rhs;
        for (int n = 0; n < s_current_sort_specs->SpecsCount; n++) {
            // Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
            // We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
            const uiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
            int delta = 0;
            switch (sort_spec->ColumnUserID)
            {
            case MyItemColumnID_ID:          delta = (a->ID - b->ID);             break;
            case MyItemColumnID_Name:        delta = (strcmp(a->Name, b->Name));  break;
            case MyItemColumnID_Quantity:    delta = (a->Quantity - b->Quantity); break;
            case MyItemColumnID_Description: delta = (strcmp(a->Name, b->Name));  break;
            default: IM_ASSERT(0); break;
            }
            if (delta > 0) return (sort_spec->SortDirection == Var::SortDir::Ascend) ? +1 : -1;
            if (delta < 0) return (sort_spec->SortDirection == Var::SortDir::Ascend) ? -1 : +1;
        }
        // qsort() is instable so always return a way to differentiate items.
        // Your own compare function may want to avoid fallback on implicit sort specs.
        // e.g. a Name compare if it wasn't already part of the sort specs.
        return a->ID - b->ID;
    }
};
const uiTableSortSpecs* MyItem::s_current_sort_specs = NULL;
}
// Make the UI compact because there are so many fields
static void PushStyleCompact() {
    uiStyle& style = UI::GetStyle();
    UI::PushStyleVarY(uiStyleVar_FramePadding, (float)(int)(style.FramePadding.y * 0.60f));
    UI::PushStyleVarY(uiStyleVar_ItemSpacing,  (float)(int)(style.ItemSpacing.y  * 0.60f));
}
static void PopStyleCompact() { UI::PopStyleVar(2); }
// Show a combo box with a choice of sizing policies
static void EditTableSizingFlags(uiTableFlags* p_flags) {
    struct EnumDesc { uiTableFlags Value; const char* Name; const char* Tooltip; };
    static const EnumDesc policies[] = {
        { uiTableFlags_None,              "Default",                        "Use default sizing policy:\n- uiTableFlags_SizingFixedFit if ScrollX is on or if host window has uiWindowFlags_AutoResize.\n- uiTableFlags_SizingStretchSame otherwise." },
        { uiTableFlags_SizingFixedFit,    "uiTableFlags_SizingFixedFit",    "Columns default to _WidthFixed (if resizable) or _WidthAuto (if not resizable), matching contents width." },
        { uiTableFlags_SizingFixedSame,   "uiTableFlags_SizingFixedSame",   "Columns are all the same width, matching the maximum contents width.\nImplicitly disable uiTableFlags_Resizable and enable uiTableFlags_NoKeepColumnsVisible." },
        { uiTableFlags_SizingStretchProp, "uiTableFlags_SizingStretchProp", "Columns default to _WidthStretch with weights proportional to their widths." },
        { uiTableFlags_SizingStretchSame, "uiTableFlags_SizingStretchSame", "Columns default to _WidthStretch with same weights." }
    };
    int idx;
    for (idx = 0; idx < IM_COUNTOF(policies); idx++)
        if (policies[idx].Value == (*p_flags & uiTableFlags_SizingMask_)) break;
    const char* preview_text = (idx < IM_COUNTOF(policies)) ? policies[idx].Name + (idx > 0 ? strlen("uiTableFlags") : 0) : "";
    if (UI::BeginCombo("Sizing Policy", preview_text)) {
        for (int n = 0; n < IM_COUNTOF(policies); n++)
            if (UI::Selectable(policies[n].Name, idx == n))
                *p_flags = (*p_flags & ~uiTableFlags_SizingMask_) | policies[n].Value;
        UI::EndCombo();
    }
    UI::SameLine();
    UI::TextDisabled("(?)");
    if (UI::BeginItemTooltip()) {
        UI::PushTextWrapPos(UI::GetFontSize() * 50.0f);
        for (int m = 0; m < IM_COUNTOF(policies); m++) {
            UI::Barrier();
            UI::Text("%s:", policies[m].Name);
            UI::Barrier();
            UI::SetCursorPosX(UI::GetCursorPosX() + UI::GetStyle().IndentSpacing * 0.5f);
            UI::TextUnformatted(policies[m].Tooltip);
        }
        UI::PopTextWrapPos();
        UI::EndTooltip();
    }
}
static void EditTableColumnsFlags(uiTableColumnFlags* p_flags) {
    UI::CheckboxFlags("_Disabled", p_flags, uiTableColumnFlags_Disabled); UI::SameLine(); HelpMarker("Master disable flag (also hide from context menu)");
    UI::CheckboxFlags("_DefaultHide", p_flags, uiTableColumnFlags_DefaultHide);
    UI::CheckboxFlags("_DefaultSort", p_flags, uiTableColumnFlags_DefaultSort);
    if (UI::CheckboxFlags("_WidthStretch", p_flags, uiTableColumnFlags_WidthStretch))
        *p_flags &= ~(uiTableColumnFlags_WidthMask_ ^ uiTableColumnFlags_WidthStretch);
    if (UI::CheckboxFlags("_WidthFixed", p_flags, uiTableColumnFlags_WidthFixed))
        *p_flags &= ~(uiTableColumnFlags_WidthMask_ ^ uiTableColumnFlags_WidthFixed);
    UI::CheckboxFlags("_NoResize", p_flags, uiTableColumnFlags_NoResize);
    UI::CheckboxFlags("_NoReorder", p_flags, uiTableColumnFlags_NoReorder);
    UI::CheckboxFlags("_NoHide", p_flags, uiTableColumnFlags_NoHide);
    UI::CheckboxFlags("_NoClip", p_flags, uiTableColumnFlags_NoClip);
    UI::CheckboxFlags("_NoSort", p_flags, uiTableColumnFlags_NoSort);
    UI::CheckboxFlags("_NoSortAscending", p_flags, uiTableColumnFlags_NoSortAscending);
    UI::CheckboxFlags("_NoSortDescending", p_flags, uiTableColumnFlags_NoSortDescending);
    UI::CheckboxFlags("_NoHeaderLabel", p_flags, uiTableColumnFlags_NoHeaderLabel);
    UI::CheckboxFlags("_NoHeaderWidth", p_flags, uiTableColumnFlags_NoHeaderWidth);
    UI::CheckboxFlags("_PreferSortAscending", p_flags, uiTableColumnFlags_PreferSortAscending);
    UI::CheckboxFlags("_PreferSortDescending", p_flags, uiTableColumnFlags_PreferSortDescending);
    UI::CheckboxFlags("_IndentEnable", p_flags, uiTableColumnFlags_IndentEnable); UI::SameLine(); HelpMarker("Default for column 0");
    UI::CheckboxFlags("_IndentDisable", p_flags, uiTableColumnFlags_IndentDisable); UI::SameLine(); HelpMarker("Default for column >0");
    UI::CheckboxFlags("_AngledHeader", p_flags, uiTableColumnFlags_AngledHeader);
}
static void ShowTableColumnsStatusFlags(uiTableColumnFlags flags) {
    UI::CheckboxFlags("_IsEnabled", &flags, uiTableColumnFlags_IsEnabled);
    UI::CheckboxFlags("_IsVisible", &flags, uiTableColumnFlags_IsVisible);
    UI::CheckboxFlags("_IsSorted", &flags, uiTableColumnFlags_IsSorted);
    UI::CheckboxFlags("_IsHovered", &flags, uiTableColumnFlags_IsHovered);
}
//-----------------------------------------------------------------------------
// [SECTION] DemoWindowTables()
//-----------------------------------------------------------------------------

static void DemoWindowTables()
{
    //UI::SetNextItemOpen(true, uiCond_Once);
    if (!UI::CollapsingHeader("Tables & Columns"))
        return;

    // Using those as a base value to create width/height that are factor of the size of our font
    const float TEXT_BASE_WIDTH = UI::CalcTextSize("A").x;
    const float TEXT_BASE_HEIGHT = UI::GetTextLineHeightWithSpacing();

    UI::PushID("Tables");

    int open_action = -1;
    if (UI::Button("Expand all"))
        open_action = 1;
    UI::SameLine();
    if (UI::Button("Collapse all"))
        open_action = 0;
    UI::SameLine();

    // Options
    static bool disable_indent = false;
    UI::Checkbox("Disable tree indentation", &disable_indent);
    UI::SameLine();
    HelpMarker("Disable the indenting of tree nodes so demo tables can use the full window width.");
    UI::Barrier();
    if (disable_indent)
        UI::PushStyleVar(uiStyleVar_IndentSpacing, 0.0f);

    // About Styling of tables
    // Most settings are configured on a per-table basis via the flags passed to BeginTable() and TableSetupColumns APIs.
    // There are however a few settings that a shared and part of the uiStyle structure:
    //   style.CellPadding                          // Padding within each cell
    //   style.Colors[uiCol_TableHeaderBg]       // Table header background
    //   style.Colors[uiCol_TableBorderStrong]   // Table outer and header borders
    //   style.Colors[uiCol_TableBorderLight]    // Table inner borders
    //   style.Colors[uiCol_TableRowBg]          // Table row background when uiTableFlags_RowBg is enabled (even rows)
    //   style.Colors[uiCol_TableRowBgAlt]       // Table row background when uiTableFlags_RowBg is enabled (odds rows)

    // Demos
    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Basic"))
    {
        IMGUI_DEMO_MARKER("Tables/Basic");
        // Here we will showcase three different ways to output a table.
        // They are very simple variations of a same thing!

        // [Method 1] Using TableNextRow() to create a new row, and TableSetColumnIndex() to select the column.
        // In many situations, this is the most flexible and easy to use pattern.
        HelpMarker("Using TableNextRow() + calling TableSetColumnIndex() _before_ each cell, in a loop.");
        if (UI::BeginTable("table1", 3))
        {
            for (int row = 0; row < 4; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("Row %d Column %d", row, column);
                }
            }
            UI::EndTable();
        }

        // [Method 2] Using TableNextColumn() called multiple times, instead of using a for loop + TableSetColumnIndex().
        // This is generally more convenient when you have code manually submitting the contents of each column.
        HelpMarker("Using TableNextRow() + calling TableNextColumn() _before_ each cell, manually.");
        if (UI::BeginTable("table2", 3))
        {
            for (int row = 0; row < 4; row++)
            {
                UI::TableNextRow();
                UI::TableNextColumn();
                UI::Text("Row %d", row);
                UI::TableNextColumn();
                UI::Text("Some contents");
                UI::TableNextColumn();
                UI::Text("123.456");
            }
            UI::EndTable();
        }

        // [Method 3] We call TableNextColumn() _before_ each cell. We never call TableNextRow(),
        // as TableNextColumn() will automatically wrap around and create new rows as needed.
        // This is generally more convenient when your cells all contains the same type of data.
        HelpMarker(
            "Only using TableNextColumn(), which tends to be convenient for tables where every cell contains "
            "the same type of contents.\n This is also more similar to the old NextColumn() function of the "
            "Columns API, and provided to facilitate the Columns->Tables API transition.");
        if (UI::BeginTable("table3", 3))
        {
            for (int item = 0; item < 14; item++)
            {
                UI::TableNextColumn();
                UI::Text("Item %d", item);
            }
            UI::EndTable();
        }

        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Borders, background"))
    {
        IMGUI_DEMO_MARKER("Tables/Borders, background");
        // Expose a few Borders related flags interactively
        enum ContentsType { CT_Text, CT_FillButton };
        static uiTableFlags flags = uiTableFlags_Borders | uiTableFlags_RowBg;
        static bool display_headers = false;
        static int contents_type = CT_Text;

        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_RowBg", &flags, uiTableFlags_RowBg);
        UI::CheckboxFlags("uiTableFlags_Borders", &flags, uiTableFlags_Borders);
        UI::SameLine(); HelpMarker("uiTableFlags_Borders\n = uiTableFlags_BordersInnerV\n | uiTableFlags_BordersOuterV\n | uiTableFlags_BordersInnerH\n | uiTableFlags_BordersOuterH");
        UI::Indent();

        UI::CheckboxFlags("uiTableFlags_BordersH", &flags, uiTableFlags_BordersH);
        UI::Indent();
        UI::CheckboxFlags("uiTableFlags_BordersOuterH", &flags, uiTableFlags_BordersOuterH);
        UI::CheckboxFlags("uiTableFlags_BordersInnerH", &flags, uiTableFlags_BordersInnerH);
        UI::Unindent();

        UI::CheckboxFlags("uiTableFlags_BordersV", &flags, uiTableFlags_BordersV);
        UI::Indent();
        UI::CheckboxFlags("uiTableFlags_BordersOuterV", &flags, uiTableFlags_BordersOuterV);
        UI::CheckboxFlags("uiTableFlags_BordersInnerV", &flags, uiTableFlags_BordersInnerV);
        UI::Unindent();

        UI::CheckboxFlags("uiTableFlags_BordersOuter", &flags, uiTableFlags_BordersOuter);
        UI::CheckboxFlags("uiTableFlags_BordersInner", &flags, uiTableFlags_BordersInner);
        UI::Unindent();

        UI::AlignTextToFramePadding(); UI::Text("Cell contents:");
        UI::SameLine(); UI::RadioButton("Text", &contents_type, CT_Text);
        UI::SameLine(); UI::RadioButton("FillButton", &contents_type, CT_FillButton);
        UI::Checkbox("Display headers", &display_headers);
        UI::CheckboxFlags("uiTableFlags_NoBordersInBody", &flags, uiTableFlags_NoBordersInBody); UI::SameLine(); HelpMarker("Disable vertical borders in columns Body (borders will always appear in Headers)");
        PopStyleCompact();

        if (UI::BeginTable("table1", 3, flags))
        {
            // Display headers so we can inspect their interaction with borders
            // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them now. See other sections for details)
            if (display_headers)
            {
                UI::TableSetupColumn("One");
                UI::TableSetupColumn("Two");
                UI::TableSetupColumn("Three");
                UI::TableHeadersRow();
            }

            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    char buf[32];
                    sprintf(buf, "Hello %d,%d", column, row);
                    if (contents_type == CT_Text)
                        UI::TextUnformatted(buf);
                    else if (contents_type == CT_FillButton)
                        UI::Button(buf, vec2(-FLT_MIN, 0.0f));
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Resizable, stretch"))
    {
        IMGUI_DEMO_MARKER("Tables/Resizable, stretch");
        // By default, if we don't enable ScrollX the sizing policy for each column is "Stretch"
        // All columns maintain a sizing weight, and they will occupy all available width.
        static uiTableFlags flags = uiTableFlags_SizingStretchSame | uiTableFlags_Resizable | uiTableFlags_BordersOuter | uiTableFlags_BordersV | uiTableFlags_ContextMenuInBody;
        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags, uiTableFlags_Resizable);
        UI::CheckboxFlags("uiTableFlags_BordersV", &flags, uiTableFlags_BordersV);
        UI::SameLine(); HelpMarker(
            "Using the _Resizable flag automatically enables the _BordersInnerV flag as well, "
            "this is why the resize borders are still showing when unchecking this.");
        PopStyleCompact();

        if (UI::BeginTable("table1", 3, flags))
        {
            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("Hello %d,%d", column, row);
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Resizable, fixed"))
    {
        IMGUI_DEMO_MARKER("Tables/Resizable, fixed");
        // Here we use uiTableFlags_SizingFixedFit (even though _ScrollX is not set)
        // So columns will adopt the "Fixed" policy and will maintain a fixed width regardless of the whole available width (unless table is small)
        // If there is not enough available width to fit all columns, they will however be resized down.
        // FIXME-TABLE: Providing a stretch-on-init would make sense especially for tables which don't have saved settings
        HelpMarker(
            "Using _Resizable + _SizingFixedFit flags.\n"
            "Fixed-width columns generally makes more sense if you want to use horizontal scrolling.\n\n"
            "Double-click a column border to auto-fit the column to its contents.");
        PushStyleCompact();
        static uiTableFlags flags = uiTableFlags_SizingFixedFit | uiTableFlags_Resizable | uiTableFlags_BordersOuter | uiTableFlags_BordersV | uiTableFlags_ContextMenuInBody;
        UI::CheckboxFlags("uiTableFlags_NoHostExtendX", &flags, uiTableFlags_NoHostExtendX);
        PopStyleCompact();

        if (UI::BeginTable("table1", 3, flags))
        {
            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("Hello %d,%d", column, row);
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Resizable, mixed"))
    {
        IMGUI_DEMO_MARKER("Tables/Resizable, mixed");
        HelpMarker(
            "Using TableSetupColumn() to alter resizing policy on a per-column basis.\n\n"
            "When combining Fixed and Stretch columns, generally you only want one, maybe two trailing columns to use _WidthStretch.");
        static uiTableFlags flags = uiTableFlags_SizingFixedFit | uiTableFlags_RowBg | uiTableFlags_Borders | uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable;

        if (UI::BeginTable("table1", 3, flags))
        {
            UI::TableSetupColumn("AAA", uiTableColumnFlags_WidthFixed);
            UI::TableSetupColumn("BBB", uiTableColumnFlags_WidthFixed);
            UI::TableSetupColumn("CCC", uiTableColumnFlags_WidthStretch);
            UI::TableHeadersRow();
            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("%s %d,%d", (column == 2) ? "Stretch" : "Fixed", column, row);
                }
            }
            UI::EndTable();
        }
        if (UI::BeginTable("table2", 6, flags))
        {
            UI::TableSetupColumn("AAA", uiTableColumnFlags_WidthFixed);
            UI::TableSetupColumn("BBB", uiTableColumnFlags_WidthFixed);
            UI::TableSetupColumn("CCC", uiTableColumnFlags_WidthFixed | uiTableColumnFlags_DefaultHide);
            UI::TableSetupColumn("DDD", uiTableColumnFlags_WidthStretch);
            UI::TableSetupColumn("EEE", uiTableColumnFlags_WidthStretch);
            UI::TableSetupColumn("FFF", uiTableColumnFlags_WidthStretch | uiTableColumnFlags_DefaultHide);
            UI::TableHeadersRow();
            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 6; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("%s %d,%d", (column >= 3) ? "Stretch" : "Fixed", column, row);
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Reorderable, hideable, with headers"))
    {
        IMGUI_DEMO_MARKER("Tables/Reorderable, hideable, with headers");
        HelpMarker(
            "Click and drag column headers to reorder columns.\n\n"
            "Right-click on a header to open a context menu.");
        static uiTableFlags flags = uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable | uiTableFlags_BordersOuter | uiTableFlags_BordersV;
        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags, uiTableFlags_Resizable);
        UI::CheckboxFlags("uiTableFlags_Reorderable", &flags, uiTableFlags_Reorderable);
        UI::CheckboxFlags("uiTableFlags_Hideable", &flags, uiTableFlags_Hideable);
        UI::CheckboxFlags("uiTableFlags_NoBordersInBody", &flags, uiTableFlags_NoBordersInBody);
        UI::CheckboxFlags("uiTableFlags_NoBordersInBodyUntilResize", &flags, uiTableFlags_NoBordersInBodyUntilResize); UI::SameLine(); HelpMarker("Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers)");
        UI::CheckboxFlags("uiTableFlags_HighlightHoveredColumn", &flags, uiTableFlags_HighlightHoveredColumn);
        PopStyleCompact();

        if (UI::BeginTable("table1", 3, flags))
        {
            // Submit columns name with TableSetupColumn() and call TableHeadersRow() to create a row with a header in each column.
            // (Later we will show how TableSetupColumn() has other uses, optional flags, sizing weight etc.)
            UI::TableSetupColumn("One");
            UI::TableSetupColumn("Two");
            UI::TableSetupColumn("Three");
            UI::TableHeadersRow();
            for (int row = 0; row < 6; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("Hello %d,%d", column, row);
                }
            }
            UI::EndTable();
        }

        // Use outer_size.x == 0.0f instead of default to make the table as tight as possible
        // (only valid when no scrolling and no stretch column)
        if (UI::BeginTable("table2", 3, flags | uiTableFlags_SizingFixedFit, vec2(0.0f, 0.0f)))
        {
            UI::TableSetupColumn("One");
            UI::TableSetupColumn("Two");
            UI::TableSetupColumn("Three");
            UI::TableHeadersRow();
            for (int row = 0; row < 6; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("Fixed %d,%d", column, row);
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Padding"))
    {
        IMGUI_DEMO_MARKER("Tables/Padding");
        // First example: showcase use of padding flags and effect of BorderOuterV/BorderInnerV on X padding.
        // We don't expose BorderOuterH/BorderInnerH here because they have no effect on X padding.
        HelpMarker(
            "We often want outer padding activated when any using features which makes the edges of a column visible:\n"
            "e.g.:\n"
            "- BorderOuterV\n"
            "- any form of row selection\n"
            "Because of this, activating BorderOuterV sets the default to PadOuterX. "
            "Using PadOuterX or NoPadOuterX you can override the default.\n\n"
            "Actual padding values are using style.CellPadding.\n\n"
            "In this demo we don't show horizontal borders to emphasize how they don't affect default horizontal padding.");

        static uiTableFlags flags1 = uiTableFlags_BordersV;
        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_PadOuterX", &flags1, uiTableFlags_PadOuterX);
        UI::SameLine(); HelpMarker("Enable outer-most padding (default if uiTableFlags_BordersOuterV is set)");
        UI::CheckboxFlags("uiTableFlags_NoPadOuterX", &flags1, uiTableFlags_NoPadOuterX);
        UI::SameLine(); HelpMarker("Disable outer-most padding (default if uiTableFlags_BordersOuterV is not set)");
        UI::CheckboxFlags("uiTableFlags_NoPadInnerX", &flags1, uiTableFlags_NoPadInnerX);
        UI::SameLine(); HelpMarker("Disable inner padding between columns (double inner padding if BordersOuterV is on, single inner padding if BordersOuterV is off)");
        UI::CheckboxFlags("uiTableFlags_BordersOuterV", &flags1, uiTableFlags_BordersOuterV);
        UI::CheckboxFlags("uiTableFlags_BordersInnerV", &flags1, uiTableFlags_BordersInnerV);
        static bool show_headers = false;
        UI::Checkbox("show_headers", &show_headers);
        PopStyleCompact();

        if (UI::BeginTable("table_padding", 3, flags1))
        {
            if (show_headers)
            {
                UI::TableSetupColumn("One");
                UI::TableSetupColumn("Two");
                UI::TableSetupColumn("Three");
                UI::TableHeadersRow();
            }

            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    if (row == 0)
                    {
                        UI::Text("Avail %.2f", UI::GetContentRegionAvail().x);
                    }
                    else
                    {
                        char buf[32];
                        sprintf(buf, "Hello %d,%d", column, row);
                        UI::Button(buf, vec2(-FLT_MIN, 0.0f));
                    }
                    //if (UI::TableGetColumnFlags() & uiTableColumnFlags_IsHovered)
                    //    UI::TableSetBgColor(uiTableBgTarget_CellBg, IM_COL32(0, 100, 0, 255));
                }
            }
            UI::EndTable();
        }

        // Second example: set style.CellPadding to (0.0) or a custom value.
        // FIXME-TABLE: Vertical border effectively not displayed the same way as horizontal one...
        HelpMarker("Setting style.CellPadding to (0,0) or a custom value.");
        static uiTableFlags flags2 = uiTableFlags_Borders | uiTableFlags_RowBg;
        static vec2 cell_padding(0.0f, 0.0f);
        static bool show_widget_frame_bg = true;

        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_Borders", &flags2, uiTableFlags_Borders);
        UI::CheckboxFlags("uiTableFlags_BordersH", &flags2, uiTableFlags_BordersH);
        UI::CheckboxFlags("uiTableFlags_BordersV", &flags2, uiTableFlags_BordersV);
        UI::CheckboxFlags("uiTableFlags_BordersInner", &flags2, uiTableFlags_BordersInner);
        UI::CheckboxFlags("uiTableFlags_BordersOuter", &flags2, uiTableFlags_BordersOuter);
        UI::CheckboxFlags("uiTableFlags_RowBg", &flags2, uiTableFlags_RowBg);
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags2, uiTableFlags_Resizable);
        UI::Checkbox("show_widget_frame_bg", &show_widget_frame_bg);
        UI::SliderFloat2("CellPadding", &cell_padding.x, 0.0f, 10.0f, "%.0f");
        PopStyleCompact();

        UI::PushStyleVar(uiStyleVar_CellPadding, cell_padding);
        if (UI::BeginTable("table_padding_2", 3, flags2))
        {
            static char text_bufs[3 * 5][16]; // Mini text storage for 3x5 cells
            static bool init = true;
            if (!show_widget_frame_bg)
                UI::PushStyleColor(uiCol_FrameBg, 0);
            for (int cell = 0; cell < 3 * 5; cell++)
            {
                UI::TableNextColumn();
                if (init)
                    strcpy(text_bufs[cell], "edit me");
                UI::SetNextItemWidth(-FLT_MIN);
                UI::PushID(cell);
                UI::InputText("##cell", text_bufs[cell], IM_COUNTOF(text_bufs[cell]));
                UI::PopID();
            }
            if (!show_widget_frame_bg)
                UI::PopStyleColor();
            init = false;
            UI::EndTable();
        }
        UI::PopStyleVar();

        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Sizing policies"))
    {
        IMGUI_DEMO_MARKER("Tables/Explicit widths");
        static uiTableFlags flags1 = uiTableFlags_BordersV | uiTableFlags_BordersOuterH | uiTableFlags_RowBg | uiTableFlags_ContextMenuInBody;
        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags1, uiTableFlags_Resizable);
        UI::CheckboxFlags("uiTableFlags_NoHostExtendX", &flags1, uiTableFlags_NoHostExtendX);
        PopStyleCompact();

        static uiTableFlags sizing_policy_flags[4] = { uiTableFlags_SizingFixedFit, uiTableFlags_SizingFixedSame, uiTableFlags_SizingStretchProp, uiTableFlags_SizingStretchSame };
        for (int table_n = 0; table_n < 4; table_n++)
        {
            UI::PushID(table_n);
            UI::SetNextItemWidth(TEXT_BASE_WIDTH * 30);
            EditTableSizingFlags(&sizing_policy_flags[table_n]);

            // To make it easier to understand the different sizing policy,
            // For each policy: we display one table where the columns have equal contents width,
            // and one where the columns have different contents width.
            if (UI::BeginTable("table1", 3, sizing_policy_flags[table_n] | flags1))
            {
                for (int row = 0; row < 3; row++)
                {
                    UI::TableNextRow();
                    UI::TableNextColumn(); UI::Text("Oh dear");
                    UI::TableNextColumn(); UI::Text("Oh dear");
                    UI::TableNextColumn(); UI::Text("Oh dear");
                }
                UI::EndTable();
            }
            if (UI::BeginTable("table2", 3, sizing_policy_flags[table_n] | flags1))
            {
                for (int row = 0; row < 3; row++)
                {
                    UI::TableNextRow();
                    UI::TableNextColumn(); UI::Text("AAAA");
                    UI::TableNextColumn(); UI::Text("BBBBBBBB");
                    UI::TableNextColumn(); UI::Text("CCCCCCCCCCCC");
                }
                UI::EndTable();
            }
            UI::PopID();
        }

        UI::Spacing();
        UI::TextUnformatted("Advanced");
        UI::SameLine();
        HelpMarker(
            "This section allows you to interact and see the effect of various sizing policies "
            "depending on whether Scroll is enabled and the contents of your columns.");

        enum ContentsType { CT_ShowWidth, CT_ShortText, CT_LongText, CT_Button, CT_FillButton, CT_InputText };
        static uiTableFlags flags = uiTableFlags_ScrollY | uiTableFlags_Borders | uiTableFlags_RowBg | uiTableFlags_Resizable;
        static int contents_type = CT_ShowWidth;
        static int column_count = 3;

        PushStyleCompact();
        UI::PushID("Advanced");
        UI::PushItemWidth(TEXT_BASE_WIDTH * 30);
        EditTableSizingFlags(&flags);
        UI::Combo("Contents", &contents_type, "Show width\0Short Text\0Long Text\0Button\0Fill Button\0InputText\0");
        if (contents_type == CT_FillButton)
        {
            UI::SameLine();
            HelpMarker(
                "Be mindful that using right-alignment (e.g. size.x = -FLT_MIN) creates a feedback loop "
                "where contents width can feed into auto-column width can feed into contents width.");
        }
        UI::DragInt("Columns", &column_count, 0.1f, 1, 64, "%d", uiSliderFlags_AlwaysClamp);
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags, uiTableFlags_Resizable);
        UI::CheckboxFlags("uiTableFlags_PreciseWidths", &flags, uiTableFlags_PreciseWidths);
        UI::SameLine(); HelpMarker("Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.");
        UI::CheckboxFlags("uiTableFlags_ScrollX", &flags, uiTableFlags_ScrollX);
        UI::CheckboxFlags("uiTableFlags_ScrollY", &flags, uiTableFlags_ScrollY);
        UI::CheckboxFlags("uiTableFlags_NoClip", &flags, uiTableFlags_NoClip);
        UI::PopItemWidth();
        UI::PopID();
        PopStyleCompact();

        if (UI::BeginTable("table2", column_count, flags, vec2(0.0f, TEXT_BASE_HEIGHT * 7)))
        {
            for (int cell = 0; cell < 10 * column_count; cell++)
            {
                UI::TableNextColumn();
                int column = UI::TableGetColumnIndex();
                int row = UI::TableGetRowIndex();

                UI::PushID(cell);
                char label[32];
                static char text_buf[32] = "";
                sprintf(label, "Hello %d,%d", column, row);
                switch (contents_type)
                {
                case CT_ShortText:  UI::TextUnformatted(label); break;
                case CT_LongText:   UI::Text("Some %s text %d,%d\nOver two lines..", column == 0 ? "long" : "longeeer", column, row); break;
                case CT_ShowWidth:  UI::Text("W: %.1f", UI::GetContentRegionAvail().x); break;
                case CT_Button:     UI::Button(label); break;
                case CT_FillButton: UI::Button(label, vec2(-FLT_MIN, 0.0f)); break;
                case CT_InputText:  UI::SetNextItemWidth(-FLT_MIN); UI::InputText("##", text_buf, IM_COUNTOF(text_buf)); break;
                }
                UI::PopID();
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Vertical scrolling, with clipping"))
    {
        IMGUI_DEMO_MARKER("Tables/Vertical scrolling, with clipping");
        HelpMarker(
            "Here we activate ScrollY, which will create a child window container to allow hosting scrollable contents.\n\n"
            "We also demonstrate using uiListClipper to virtualize the submission of many items.");
        static uiTableFlags flags = uiTableFlags_ScrollY | uiTableFlags_RowBg | uiTableFlags_BordersOuter | uiTableFlags_BordersV | uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable;

        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_ScrollY", &flags, uiTableFlags_ScrollY);
        PopStyleCompact();

        // When using ScrollX or ScrollY we need to specify a size for our table container!
        // Otherwise by default the table will fit all available space, like a BeginChild() call.
        vec2 outer_size = vec2(0.0f, TEXT_BASE_HEIGHT * 8);
        if (UI::BeginTable("table_scrolly", 3, flags, outer_size))
        {
            UI::TableSetupScrollFreeze(0, 1); // Make top row always visible
            UI::TableSetupColumn("One", uiTableColumnFlags_None);
            UI::TableSetupColumn("Two", uiTableColumnFlags_None);
            UI::TableSetupColumn("Three", uiTableColumnFlags_None);
            UI::TableHeadersRow();

            // Demonstrate using clipper for large vertical lists
            uiListClipper clipper;
            clipper.Begin(1000);
            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    UI::TableNextRow();
                    for (int column = 0; column < 3; column++)
                    {
                        UI::TableSetColumnIndex(column);
                        UI::Text("Hello %d,%d", column, row);
                    }
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Horizontal scrolling"))
    {
        IMGUI_DEMO_MARKER("Tables/Horizontal scrolling");
        HelpMarker(
            "When ScrollX is enabled, the default sizing policy becomes uiTableFlags_SizingFixedFit, "
            "as automatically stretching columns doesn't make much sense with horizontal scrolling.\n\n"
            "Also note that as of the current version, you will almost always want to enable ScrollY along with ScrollX, "
            "because the container window won't automatically extend vertically to fix contents "
            "(this may be improved in future versions).");
        static uiTableFlags flags = uiTableFlags_ScrollX | uiTableFlags_ScrollY | uiTableFlags_RowBg | uiTableFlags_BordersOuter | uiTableFlags_BordersV | uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable;
        static int freeze_cols = 1;
        static int freeze_rows = 1;

        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags, uiTableFlags_Resizable);
        UI::CheckboxFlags("uiTableFlags_ScrollX", &flags, uiTableFlags_ScrollX);
        UI::CheckboxFlags("uiTableFlags_ScrollY", &flags, uiTableFlags_ScrollY);
        UI::SetNextItemWidth(UI::GetFrameHeight());
        UI::DragInt("freeze_cols", &freeze_cols, 0.2f, 0, 9, NULL, uiSliderFlags_NoInput);
        UI::SetNextItemWidth(UI::GetFrameHeight());
        UI::DragInt("freeze_rows", &freeze_rows, 0.2f, 0, 9, NULL, uiSliderFlags_NoInput);
        PopStyleCompact();

        // When using ScrollX or ScrollY we need to specify a size for our table container!
        // Otherwise by default the table will fit all available space, like a BeginChild() call.
        vec2 outer_size = vec2(0.0f, TEXT_BASE_HEIGHT * 8);
        if (UI::BeginTable("table_scrollx", 7, flags, outer_size))
        {
            UI::TableSetupScrollFreeze(freeze_cols, freeze_rows);
            UI::TableSetupColumn("Line #", uiTableColumnFlags_NoHide); // Make the first column not hideable to match our use of TableSetupScrollFreeze()
            UI::TableSetupColumn("One");
            UI::TableSetupColumn("Two");
            UI::TableSetupColumn("Three");
            UI::TableSetupColumn("Four");
            UI::TableSetupColumn("Five");
            UI::TableSetupColumn("Six");
            UI::TableHeadersRow();
            for (int row = 0; row < 20; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 7; column++)
                {
                    // Both TableNextColumn() and TableSetColumnIndex() return true when a column is visible or performing width measurement.
                    // Because here we know that:
                    // - A) all our columns are contributing the same to row height
                    // - B) column 0 is always visible,
                    // We only always submit this one column and can skip others.
                    // More advanced per-column clipping behaviors may benefit from polling the status flags via TableGetColumnFlags().
                    if (!UI::TableSetColumnIndex(column) && column > 0)
                        continue;
                    if (column == 0)
                        UI::Text("Line %d", row);
                    else
                        UI::Text("Hello world %d,%d", column, row);
                }
            }
            UI::EndTable();
        }

        UI::Spacing();
        UI::TextUnformatted("Stretch + ScrollX");
        UI::SameLine();
        HelpMarker(
            "Showcase using Stretch columns + ScrollX together: "
            "this is rather unusual and only makes sense when specifying an 'inner_width' for the table!\n"
            "Without an explicit value, inner_width is == outer_size.x and therefore using Stretch columns "
            "along with ScrollX doesn't make sense.");
        static uiTableFlags flags2 = uiTableFlags_SizingStretchSame | uiTableFlags_ScrollX | uiTableFlags_ScrollY | uiTableFlags_BordersOuter | uiTableFlags_RowBg | uiTableFlags_ContextMenuInBody;
        static float inner_width = 1000.0f;
        PushStyleCompact();
        UI::PushID("flags3");
        UI::PushItemWidth(TEXT_BASE_WIDTH * 30);
        UI::CheckboxFlags("uiTableFlags_ScrollX", &flags2, uiTableFlags_ScrollX);
        UI::DragFloat("inner_width", &inner_width, 1.0f, 0.0f, FLT_MAX, "%.1f");
        UI::PopItemWidth();
        UI::PopID();
        PopStyleCompact();
        if (UI::BeginTable("table2", 7, flags2, outer_size, inner_width))
        {
            for (int cell = 0; cell < 20 * 7; cell++)
            {
                UI::TableNextColumn();
                UI::Text("Hello world %d,%d", UI::TableGetColumnIndex(), UI::TableGetRowIndex());
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Columns flags"))
    {
        IMGUI_DEMO_MARKER("Tables/Columns flags");
        // Create a first table just to show all the options/flags we want to make visible in our example!
        const int column_count = 3;
        const char* column_names[column_count] = { "One", "Two", "Three" };
        static uiTableColumnFlags column_flags[column_count] = { uiTableColumnFlags_DefaultSort, uiTableColumnFlags_None, uiTableColumnFlags_DefaultHide };
        static uiTableColumnFlags column_flags_out[column_count] = { 0, 0, 0 }; // Output from TableGetColumnFlags()

        if (UI::BeginTable("table_columns_flags_checkboxes", column_count, uiTableFlags_None))
        {
            PushStyleCompact();
            for (int column = 0; column < column_count; column++)
            {
                UI::TableNextColumn();
                UI::PushID(column);
                UI::AlignTextToFramePadding(); // FIXME-TABLE: Workaround for wrong text baseline propagation across columns
                UI::Text("'%s'", column_names[column]);
                UI::Spacing();
                UI::Text("Input flags:");
                EditTableColumnsFlags(&column_flags[column]);
                UI::Spacing();
                UI::Text("Output flags:");
                UI::BeginDisabled();
                ShowTableColumnsStatusFlags(column_flags_out[column]);
                UI::EndDisabled();
                UI::PopID();
            }
            PopStyleCompact();
            UI::EndTable();
        }

        // Create the real table we care about for the example!
        // We use a scrolling table to be able to showcase the difference between the _IsEnabled and _IsVisible flags above,
        // otherwise in a non-scrolling table columns are always visible (unless using uiTableFlags_NoKeepColumnsVisible
        // + resizing the parent window down).
        const uiTableFlags flags
            = uiTableFlags_SizingFixedFit | uiTableFlags_ScrollX | uiTableFlags_ScrollY
            | uiTableFlags_RowBg | uiTableFlags_BordersOuter | uiTableFlags_BordersV
            | uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable | uiTableFlags_Sortable;
        vec2 outer_size = vec2(0.0f, TEXT_BASE_HEIGHT * 9);
        if (UI::BeginTable("table_columns_flags", column_count, flags, outer_size))
        {
            bool has_angled_header = false;
            for (int column = 0; column < column_count; column++)
            {
                has_angled_header |= (column_flags[column] & uiTableColumnFlags_AngledHeader) != 0;
                UI::TableSetupColumn(column_names[column], column_flags[column]);
            }
            if (has_angled_header)
                UI::TableAngledHeadersRow();
            UI::TableHeadersRow();
            for (int column = 0; column < column_count; column++)
                column_flags_out[column] = UI::TableGetColumnFlags(column);
            float indent_step = (float)((int)TEXT_BASE_WIDTH / 2);
            for (int row = 0; row < 8; row++)
            {
                // Add some indentation to demonstrate usage of per-column IndentEnable/IndentDisable flags.
                UI::Indent(indent_step);
                UI::TableNextRow();
                for (int column = 0; column < column_count; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("%s %s", (column == 0) ? "Indented" : "Hello", UI::TableGetColumnName(column));
                }
            }
            UI::Unindent(indent_step * 8.0f);

            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Columns widths"))
    {
        IMGUI_DEMO_MARKER("Tables/Columns widths");
        HelpMarker("Using TableSetupColumn() to setup default width.");

        static uiTableFlags flags1 = uiTableFlags_Borders | uiTableFlags_NoBordersInBodyUntilResize;
        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags1, uiTableFlags_Resizable);
        UI::CheckboxFlags("uiTableFlags_NoBordersInBodyUntilResize", &flags1, uiTableFlags_NoBordersInBodyUntilResize);
        PopStyleCompact();
        if (UI::BeginTable("table1", 3, flags1))
        {
            // We could also set uiTableFlags_SizingFixedFit on the table and all columns will default to uiTableColumnFlags_WidthFixed.
            UI::TableSetupColumn("one", uiTableColumnFlags_WidthFixed, 100.0f); // Default to 100.0f
            UI::TableSetupColumn("two", uiTableColumnFlags_WidthFixed, 200.0f); // Default to 200.0f
            UI::TableSetupColumn("three", uiTableColumnFlags_WidthFixed);       // Default to auto
            UI::TableHeadersRow();
            for (int row = 0; row < 4; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableSetColumnIndex(column);
                    if (row == 0)
                        UI::Text("(w: %5.1f)", UI::GetContentRegionAvail().x);
                    else
                        UI::Text("Hello %d,%d", column, row);
                }
            }
            UI::EndTable();
        }

        HelpMarker(
            "Using TableSetupColumn() to setup explicit width.\n\nUnless _NoKeepColumnsVisible is set, "
            "fixed columns with set width may still be shrunk down if there's not enough space in the host.");

        static uiTableFlags flags2 = uiTableFlags_None;
        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_NoKeepColumnsVisible", &flags2, uiTableFlags_NoKeepColumnsVisible);
        UI::CheckboxFlags("uiTableFlags_BordersInnerV", &flags2, uiTableFlags_BordersInnerV);
        UI::CheckboxFlags("uiTableFlags_BordersOuterV", &flags2, uiTableFlags_BordersOuterV);
        PopStyleCompact();
        if (UI::BeginTable("table2", 4, flags2))
        {
            // We could also set uiTableFlags_SizingFixedFit on the table and then all columns
            // will default to uiTableColumnFlags_WidthFixed.
            UI::TableSetupColumn("", uiTableColumnFlags_WidthFixed, 100.0f);
            UI::TableSetupColumn("", uiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 15.0f);
            UI::TableSetupColumn("", uiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 30.0f);
            UI::TableSetupColumn("", uiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 15.0f);
            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 4; column++)
                {
                    UI::TableSetColumnIndex(column);
                    if (row == 0)
                        UI::Text("(w: %5.1f)", UI::GetContentRegionAvail().x);
                    else
                        UI::Text("Hello %d,%d", column, row);
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Nested tables"))
    {
        IMGUI_DEMO_MARKER("Tables/Nested tables");
        HelpMarker("This demonstrates embedding a table into another table cell.");

        if (UI::BeginTable("table_nested1", 2, uiTableFlags_Borders | uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable))
        {
            UI::TableSetupColumn("A0");
            UI::TableSetupColumn("A1");
            UI::TableHeadersRow();

            UI::TableNextColumn();
            UI::Text("A0 Row 0");
            {
                float rows_height = (TEXT_BASE_HEIGHT * 2.0f) + (UI::GetStyle().CellPadding.y * 2.0f);
                if (UI::BeginTable("table_nested2", 2, uiTableFlags_Borders | uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable))
                {
                    UI::TableSetupColumn("B0");
                    UI::TableSetupColumn("B1");
                    UI::TableHeadersRow();

                    UI::TableNextRow(uiTableRowFlags_None, rows_height);
                    UI::TableNextColumn();
                    UI::Text("B0 Row 0");
                    UI::TableNextColumn();
                    UI::Text("B1 Row 0");
                    UI::TableNextRow(uiTableRowFlags_None, rows_height);
                    UI::TableNextColumn();
                    UI::Text("B0 Row 1");
                    UI::TableNextColumn();
                    UI::Text("B1 Row 1");

                    UI::EndTable();
                }
            }
            UI::TableNextColumn(); UI::Text("A1 Row 0");
            UI::TableNextColumn(); UI::Text("A0 Row 1");
            UI::TableNextColumn(); UI::Text("A1 Row 1");
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Row height"))
    {
        IMGUI_DEMO_MARKER("Tables/Row height");
        HelpMarker(
            "You can pass a 'min_row_height' to TableNextRow().\n\nRows are padded with 'style.CellPadding.y' on top and bottom, "
            "so effectively the minimum row height will always be >= 'style.CellPadding.y * 2.0f'.\n\n"
            "We cannot honor a _maximum_ row height as that would require a unique clipping rectangle per row.");
        if (UI::BeginTable("table_row_height", 1, uiTableFlags_Borders))
        {
            for (int row = 0; row < 8; row++)
            {
                float min_row_height = (float)(int)(TEXT_BASE_HEIGHT * 0.30f * row + UI::GetStyle().CellPadding.y * 2.0f);
                UI::TableNextRow(uiTableRowFlags_None, min_row_height);
                UI::TableNextColumn();
                UI::Text("min_row_height = %.2f", min_row_height);
            }
            UI::EndTable();
        }

        HelpMarker(
            "Showcase using SameLine(0,0) to share Current Line Height between cells.\n\n"
            "Please note that Tables Row Height is not the same thing as Current Line Height, "
            "as a table cell may contains multiple lines.");
        if (UI::BeginTable("table_share_lineheight", 2, uiTableFlags_Borders))
        {
            UI::TableNextRow();
            UI::TableNextColumn();
            UI::ColorButton("##1", vec4(0.13f, 0.26f, 0.40f, 1.0f), uiColorEditFlags_None, vec2(40, 40));
            UI::TableNextColumn();
            UI::Text("Line 1");
            UI::Text("Line 2");

            UI::TableNextRow();
            UI::TableNextColumn();
            UI::ColorButton("##2", vec4(0.13f, 0.26f, 0.40f, 1.0f), uiColorEditFlags_None, vec2(40, 40));
            UI::TableNextColumn();
            UI::SameLine(0.0f, 0.0f); // Reuse line height from previous column
            UI::Text("Line 1, with SameLine(0,0)");
            UI::Text("Line 2");

            UI::EndTable();
        }

        HelpMarker("Showcase altering CellPadding.y between rows. Note that CellPadding.x is locked for the entire table.");
        if (UI::BeginTable("table_changing_cellpadding_y", 1, uiTableFlags_Borders))
        {
            uiStyle& style = UI::GetStyle();
            for (int row = 0; row < 8; row++)
            {
                if ((row % 3) == 2)
                    UI::PushStyleVarY(uiStyleVar_CellPadding, 20.0f);
                UI::TableNextRow(uiTableRowFlags_None);
                UI::TableNextColumn();
                UI::Text("CellPadding.y = %.2f", style.CellPadding.y);
                if ((row % 3) == 2)
                    UI::PopStyleVar();
            }
            UI::EndTable();
        }

        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Outer size"))
    {
        IMGUI_DEMO_MARKER("Tables/Outer size");
        // Showcasing use of uiTableFlags_NoHostExtendX and uiTableFlags_NoHostExtendY
        // Important to that note how the two flags have slightly different behaviors!
        UI::Text("Using NoHostExtendX and NoHostExtendY:");
        PushStyleCompact();
        static uiTableFlags flags = uiTableFlags_Borders | uiTableFlags_Resizable | uiTableFlags_ContextMenuInBody | uiTableFlags_RowBg | uiTableFlags_SizingFixedFit | uiTableFlags_NoHostExtendX;
        UI::CheckboxFlags("uiTableFlags_NoHostExtendX", &flags, uiTableFlags_NoHostExtendX);
        UI::SameLine(); HelpMarker("Make outer width auto-fit to columns, overriding outer_size.x value.\n\nOnly available when ScrollX/ScrollY are disabled and Stretch columns are not used.");
        UI::CheckboxFlags("uiTableFlags_NoHostExtendY", &flags, uiTableFlags_NoHostExtendY);
        UI::SameLine(); HelpMarker("Make outer height stop exactly at outer_size.y (prevent auto-extending table past the limit).\n\nOnly available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.");
        PopStyleCompact();

        vec2 outer_size = vec2(0.0f, TEXT_BASE_HEIGHT * 5.5f);
        if (UI::BeginTable("table1", 3, flags, outer_size))
        {
            for (int row = 0; row < 10; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableNextColumn();
                    UI::Text("Cell %d,%d", column, row);
                }
            }
            UI::EndTable();
        }
        UI::SameLine();
        UI::Text("Hello!");

        UI::Spacing();

        UI::Text("Using explicit size:");
        if (UI::BeginTable("table2", 3, uiTableFlags_Borders | uiTableFlags_RowBg, vec2(TEXT_BASE_WIDTH * 30, 0.0f)))
        {
            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    UI::TableNextColumn();
                    UI::Text("Cell %d,%d", column, row);
                }
            }
            UI::EndTable();
        }
        UI::SameLine();
        if (UI::BeginTable("table3", 3, uiTableFlags_Borders | uiTableFlags_RowBg, vec2(TEXT_BASE_WIDTH * 30, 0.0f)))
        {
            const float rows_height = TEXT_BASE_HEIGHT * 1.5f + UI::GetStyle().CellPadding.y * 2.0f;
            for (int row = 0; row < 3; row++)
            {
                UI::TableNextRow(0, rows_height);
                for (int column = 0; column < 3; column++)
                {
                    UI::TableNextColumn();
                    UI::Text("Cell %d,%d", column, row);
                }
            }
            UI::EndTable();
        }

        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Background color"))
    {
        IMGUI_DEMO_MARKER("Tables/Background color");
        static uiTableFlags flags = uiTableFlags_RowBg;
        static int row_bg_type = 1;
        static int row_bg_target = 1;
        static int cell_bg_type = 1;

        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_Borders", &flags, uiTableFlags_Borders);
        UI::CheckboxFlags("uiTableFlags_RowBg", &flags, uiTableFlags_RowBg);
        UI::SameLine(); HelpMarker("uiTableFlags_RowBg automatically sets RowBg0 to alternative colors pulled from the Style.");
        UI::Combo("row bg type", (int*)&row_bg_type, "None\0Red\0Gradient\0");
        UI::Combo("row bg target", (int*)&row_bg_target, "RowBg0\0RowBg1\0"); UI::SameLine(); HelpMarker("Target RowBg0 to override the alternating odd/even colors,\nTarget RowBg1 to blend with them.");
        UI::Combo("cell bg type", (int*)&cell_bg_type, "None\0Blue\0"); UI::SameLine(); HelpMarker("We are colorizing cells to B1->C2 here.");
        IM_ASSERT(row_bg_type >= 0 && row_bg_type <= 2);
        IM_ASSERT(row_bg_target >= 0 && row_bg_target <= 1);
        IM_ASSERT(cell_bg_type >= 0 && cell_bg_type <= 1);
        PopStyleCompact();

        if (UI::BeginTable("table1", 5, flags))
        {
            for (int row = 0; row < 6; row++)
            {
                UI::TableNextRow();

                // Demonstrate setting a row background color with 'UI::TableSetBgColor(uiTableBgTarget_RowBgX, ...)'
                // We use a transparent color so we can see the one behind in case our target is RowBg1 and RowBg0 was already targeted by the uiTableFlags_RowBg flag.
                if (row_bg_type != 0)
                {
                    ImU32 row_bg_color = UI::GetColorU32(row_bg_type == 1 ? vec4(0.7f, 0.3f, 0.3f, 0.65f) : vec4(0.2f + row * 0.1f, 0.2f, 0.2f, 0.65f)); // Flat or Gradient?
                    UI::TableSetBgColor(uiTableBgTarget_RowBg0 + row_bg_target, row_bg_color);
                }

                // Fill cells
                for (int column = 0; column < 5; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("%c%c", 'A' + row, '0' + column);

                    // Change background of Cells B1->C2
                    // Demonstrate setting a cell background color with 'UI::TableSetBgColor(uiTableBgTarget_CellBg, ...)'
                    // (the CellBg color will be blended over the RowBg and ColumnBg colors)
                    // We can also pass a column number as a third parameter to TableSetBgColor() and do this outside the column loop.
                    if (row >= 1 && row <= 2 && column >= 1 && column <= 2 && cell_bg_type == 1)
                    {
                        ImU32 cell_bg_color = UI::GetColorU32(vec4(0.3f, 0.3f, 0.7f, 0.65f));
                        UI::TableSetBgColor(uiTableBgTarget_CellBg, cell_bg_color);
                    }
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Tree view"))
    {
        IMGUI_DEMO_MARKER("Tables/Tree view");
        static uiTableFlags table_flags = uiTableFlags_BordersV | uiTableFlags_BordersOuterH | uiTableFlags_Resizable | uiTableFlags_RowBg | uiTableFlags_NoBordersInBody;

        static uiTreeFlags tree_node_flags_base = uiTreeFlags_SpanAllColumns | uiTreeFlags_DefaultOpen | uiTreeFlags_DrawLinesFull;
        UI::CheckboxFlags("uiTreeFlags_SpanFullWidth",  &tree_node_flags_base, uiTreeFlags_SpanFullWidth);
        UI::CheckboxFlags("uiTreeFlags_SpanLabelWidth",  &tree_node_flags_base, uiTreeFlags_SpanLabelWidth);
        UI::CheckboxFlags("uiTreeFlags_SpanAllColumns", &tree_node_flags_base, uiTreeFlags_SpanAllColumns);
        UI::CheckboxFlags("uiTreeFlags_LabelSpanAllColumns", &tree_node_flags_base, uiTreeFlags_LabelSpanAllColumns);
        UI::SameLine(); HelpMarker("Useful if you know that you aren't displaying contents in other columns");

        HelpMarker("See \"Columns flags\" section to configure how indentation is applied to individual columns.");
        if (UI::BeginTable("3ways", 3, table_flags))
        {
            // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
            UI::TableSetupColumn("Name", uiTableColumnFlags_NoHide);
            UI::TableSetupColumn("Size", uiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
            UI::TableSetupColumn("Type", uiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
            UI::TableHeadersRow();

            // Simple storage to output a dummy file-system.
            struct MyTreeNode
            {
                const char*     Name;
                const char*     Type;
                int             Size;
                int             ChildIdx;
                int             ChildCount;
                static void DisplayNode(const MyTreeNode* node, const MyTreeNode* all_nodes)
                {
                    UI::TableNextRow();
                    UI::TableNextColumn();
                    const bool is_folder = (node->ChildCount > 0);

                    uiTreeFlags node_flags = tree_node_flags_base;
                    if (node != &all_nodes[0])
                        node_flags &= ~uiTreeFlags_LabelSpanAllColumns; // Only demonstrate this on the root node.

                    if (is_folder)
                    {
                        bool open = UI::TreeNodeEx(node->Name, node_flags);
                        if ((node_flags & uiTreeFlags_LabelSpanAllColumns) == 0)
                        {
                            UI::TableNextColumn();
                            UI::TextDisabled("--");
                            UI::TableNextColumn();
                            UI::TextUnformatted(node->Type);
                        }
                        if (open)
                        {
                            for (int child_n = 0; child_n < node->ChildCount; child_n++)
                                DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
                            UI::TreePop();
                        }
                    }
                    else
                    {
                        UI::TreeNodeEx(node->Name, node_flags | uiTreeFlags_Leaf | uiTreeFlags_Bullet | uiTreeFlags_NoTreePushOnOpen);
                        UI::TableNextColumn();
                        UI::Text("%d", node->Size);
                        UI::TableNextColumn();
                        UI::TextUnformatted(node->Type);
                    }
                }
            };
            static const MyTreeNode nodes[] =
            {
                { "Root with Long Name",          "Folder",       -1,       1, 3    }, // 0
                { "Music",                        "Folder",       -1,       4, 2    }, // 1
                { "Textures",                     "Folder",       -1,       6, 3    }, // 2
                { "desktop.ini",                  "System file",  1024,    -1,-1    }, // 3
                { "File1_a.wav",                  "Audio file",   123000,  -1,-1    }, // 4
                { "File1_b.wav",                  "Audio file",   456000,  -1,-1    }, // 5
                { "Image001.png",                 "Image file",   203128,  -1,-1    }, // 6
                { "Copy of Image001.png",         "Image file",   203256,  -1,-1    }, // 7
                { "Copy of Image001 (Final2).png","Image file",   203512,  -1,-1    }, // 8
            };

            MyTreeNode::DisplayNode(&nodes[0], nodes);

            UI::EndTable();
        }
        UI::TreePop();
    }

    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Item width"))
    {
        IMGUI_DEMO_MARKER("Tables/Item width");
        HelpMarker(
            "Showcase using PushItemWidth() and how it is preserved on a per-column basis.\n\n"
            "Note that on auto-resizing non-resizable fixed columns, querying the content width for "
            "e.g. right-alignment doesn't make sense.");
        if (UI::BeginTable("table_item_width", 3, uiTableFlags_Borders))
        {
            UI::TableSetupColumn("small");
            UI::TableSetupColumn("half");
            UI::TableSetupColumn("right-align");
            UI::TableHeadersRow();

            for (int row = 0; row < 3; row++)
            {
                UI::TableNextRow();
                if (row == 0)
                {
                    // Setup ItemWidth once (instead of setting up every time, which is also possible but less efficient)
                    UI::TableSetColumnIndex(0);
                    UI::PushItemWidth(TEXT_BASE_WIDTH * 3.0f); // Small
                    UI::TableSetColumnIndex(1);
                    UI::PushItemWidth(-UI::GetContentRegionAvail().x * 0.5f);
                    UI::TableSetColumnIndex(2);
                    UI::PushItemWidth(-FLT_MIN); // Right-aligned
                }

                // Draw our contents
                static float dummy_f = 0.0f;
                UI::PushID(row);
                UI::TableSetColumnIndex(0);
                UI::SliderFloat("float0", &dummy_f, 0.0f, 1.0f);
                UI::TableSetColumnIndex(1);
                UI::SliderFloat("float1", &dummy_f, 0.0f, 1.0f);
                UI::TableSetColumnIndex(2);
                UI::SliderFloat("##float2", &dummy_f, 0.0f, 1.0f); // No visible label since right-aligned
                UI::PopID();
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    // Demonstrate using TableHeader() calls instead of TableHeadersRow()
    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Custom headers"))
    {
        IMGUI_DEMO_MARKER("Tables/Custom headers");
        const int COLUMNS_COUNT = 3;
        if (UI::BeginTable("table_custom_headers", COLUMNS_COUNT, uiTableFlags_Borders | uiTableFlags_Reorderable | uiTableFlags_Hideable))
        {
            UI::TableSetupColumn("Apricot");
            UI::TableSetupColumn("Banana");
            UI::TableSetupColumn("Cherry");

            // Dummy entire-column selection storage
            // FIXME: It would be nice to actually demonstrate full-featured selection using those checkbox.
            static bool column_selected[3] = {};

            // Instead of calling TableHeadersRow() we'll submit custom headers ourselves.
            // (A different approach is also possible:
            //    - Specify uiTableColumnFlags_NoHeaderLabel in some TableSetupColumn() call.
            //    - Call TableHeadersRow() normally. This will submit TableHeader() with no name.
            //    - Then call TableSetColumnIndex() to position yourself in the column and submit your stuff e.g. Checkbox().)
            UI::TableNextRow(uiTableRowFlags_Headers);
            for (int column = 0; column < COLUMNS_COUNT; column++)
            {
                UI::TableSetColumnIndex(column);
                const char* column_name = UI::TableGetColumnName(column); // Retrieve name passed to TableSetupColumn()
                UI::PushID(column);
                UI::PushStyleVar(uiStyleVar_FramePadding, vec2(0, 0));
                UI::Checkbox("##checkall", &column_selected[column]);
                UI::PopStyleVar();
                UI::SameLine(0.0f, UI::GetStyle().ItemInnerSpacing.x);
                UI::TableHeader(column_name);
                UI::PopID();
            }

            // Submit table contents
            for (int row = 0; row < 5; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    char buf[32];
                    sprintf(buf, "Cell %d,%d", column, row);
                    UI::TableSetColumnIndex(column);
                    UI::Selectable(buf, column_selected[column]);
                }
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    // Demonstrate using uiTableColumnFlags_AngledHeader flag to create angled headers
    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Angled headers"))
    {
        IMGUI_DEMO_MARKER("Tables/Angled headers");
        const char* column_names[] = { "Track", "cabasa", "ride", "smash", "tom-hi", "tom-mid", "tom-low", "hihat-o", "hihat-c", "snare-s", "snare-c", "clap", "rim", "kick" };
        const int columns_count = IM_COUNTOF(column_names);
        const int rows_count = 12;

        static uiTableFlags table_flags = uiTableFlags_SizingFixedFit | uiTableFlags_ScrollX | uiTableFlags_ScrollY | uiTableFlags_BordersOuter | uiTableFlags_BordersInnerH | uiTableFlags_Hideable | uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_HighlightHoveredColumn;
        static uiTableColumnFlags column_flags = uiTableColumnFlags_AngledHeader | uiTableColumnFlags_WidthFixed;
        static bool bools[columns_count * rows_count] = {}; // Dummy storage selection storage
        static int frozen_cols = 1;
        static int frozen_rows = 2;
        UI::CheckboxFlags("_ScrollX", &table_flags, uiTableFlags_ScrollX);
        UI::CheckboxFlags("_ScrollY", &table_flags, uiTableFlags_ScrollY);
        UI::CheckboxFlags("_Resizable", &table_flags, uiTableFlags_Resizable);
        UI::CheckboxFlags("_Sortable", &table_flags, uiTableFlags_Sortable);
        UI::CheckboxFlags("_NoBordersInBody", &table_flags, uiTableFlags_NoBordersInBody);
        UI::CheckboxFlags("_HighlightHoveredColumn", &table_flags, uiTableFlags_HighlightHoveredColumn);
        UI::SetNextItemWidth(UI::GetFontSize() * 8);
        UI::SliderInt("Frozen columns", &frozen_cols, 0, 2);
        UI::SetNextItemWidth(UI::GetFontSize() * 8);
        UI::SliderInt("Frozen rows", &frozen_rows, 0, 2);
        UI::CheckboxFlags("Disable header contributing to column width", &column_flags, uiTableColumnFlags_NoHeaderWidth);

        if (UI::TreeNode("Style settings"))
        {
            UI::SameLine();
            HelpMarker("Giving access to some uiStyle value in this demo for convenience.");
            UI::SetNextItemWidth(UI::GetFontSize() * 8);
            UI::SliderAngle("style.TableAngledHeadersAngle", &UI::GetStyle().TableAngledHeadersAngle, -50.0f, +50.0f);
            UI::SetNextItemWidth(UI::GetFontSize() * 8);
            UI::SliderFloat2("style.TableAngledHeadersTextAlign", (float*)&UI::GetStyle().TableAngledHeadersTextAlign, 0.0f, 1.0f, "%.2f");
            UI::TreePop();
        }

        if (UI::BeginTable("table_angled_headers", columns_count, table_flags, vec2(0.0f, TEXT_BASE_HEIGHT * 12)))
        {
            UI::TableSetupColumn(column_names[0], uiTableColumnFlags_NoHide | uiTableColumnFlags_NoReorder);
            for (int n = 1; n < columns_count; n++)
                UI::TableSetupColumn(column_names[n], column_flags);
            UI::TableSetupScrollFreeze(frozen_cols, frozen_rows);

            UI::TableAngledHeadersRow(); // Draw angled headers for all columns with the uiTableColumnFlags_AngledHeader flag.
            UI::TableHeadersRow();       // Draw remaining headers and allow access to context-menu and other functions.
            for (int row = 0; row < rows_count; row++)
            {
                UI::PushID(row);
                UI::TableNextRow();
                UI::TableSetColumnIndex(0);
                UI::AlignTextToFramePadding();
                UI::Text("Track %d", row);
                for (int column = 1; column < columns_count; column++)
                    if (UI::TableSetColumnIndex(column))
                    {
                        UI::PushID(column);
                        UI::Checkbox("", &bools[row * columns_count + column]);
                        UI::PopID();
                    }
                UI::PopID();
            }
            UI::EndTable();
        }
        UI::TreePop();
    }

    // Demonstrate creating custom context menus inside columns,
    // while playing it nice with context menus provided by TableHeadersRow()/TableHeader()
    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Context menus"))
    {
        IMGUI_DEMO_MARKER("Tables/Context menus");
        HelpMarker(
            "By default, right-clicking over a TableHeadersRow()/TableHeader() line will open the default context-menu.\n"
            "Using uiTableFlags_ContextMenuInBody we also allow right-clicking over columns body.");
        static uiTableFlags flags1 = uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable | uiTableFlags_Borders | uiTableFlags_ContextMenuInBody;

        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_ContextMenuInBody", &flags1, uiTableFlags_ContextMenuInBody);
        PopStyleCompact();

        // Context Menus: first example
        // [1.1] Right-click on the TableHeadersRow() line to open the default table context menu.
        // [1.2] Right-click in columns also open the default table context menu (if uiTableFlags_ContextMenuInBody is set)
        const int COLUMNS_COUNT = 3;
        if (UI::BeginTable("table_context_menu", COLUMNS_COUNT, flags1))
        {
            UI::TableSetupColumn("One");
            UI::TableSetupColumn("Two");
            UI::TableSetupColumn("Three");

            // [1.1]] Right-click on the TableHeadersRow() line to open the default table context menu.
            UI::TableHeadersRow();

            // Submit dummy contents
            for (int row = 0; row < 4; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < COLUMNS_COUNT; column++)
                {
                    UI::TableSetColumnIndex(column);
                    UI::Text("Cell %d,%d", column, row);
                }
            }
            UI::EndTable();
        }

        // Context Menus: second example
        // [2.1] Right-click on the TableHeadersRow() line to open the default table context menu.
        // [2.2] Right-click on the ".." to open a custom popup
        // [2.3] Right-click in columns to open another custom popup
        HelpMarker(
            "Demonstrate mixing table context menu (over header), item context button (over button) "
            "and custom per-column context menu (over column body).");
        uiTableFlags flags2 = uiTableFlags_Resizable | uiTableFlags_SizingFixedFit | uiTableFlags_Reorderable | uiTableFlags_Hideable | uiTableFlags_Borders;
        if (UI::BeginTable("table_context_menu_2", COLUMNS_COUNT, flags2))
        {
            UI::TableSetupColumn("One");
            UI::TableSetupColumn("Two");
            UI::TableSetupColumn("Three");

            // [2.1] Right-click on the TableHeadersRow() line to open the default table context menu.
            UI::TableHeadersRow();
            for (int row = 0; row < 4; row++)
            {
                UI::TableNextRow();
                for (int column = 0; column < COLUMNS_COUNT; column++)
                {
                    // Submit dummy contents
                    UI::TableSetColumnIndex(column);
                    UI::Text("Cell %d,%d", column, row);
                    UI::SameLine();

                    // [2.2] Right-click on the ".." to open a custom popup
                    UI::PushID(row * COLUMNS_COUNT + column);
                    UI::SmallButton("..");
                    if (UI::BeginPopupContextItem())
                    {
                        UI::Text("This is the popup for Button(\"..\") in Cell %d,%d", column, row);
                        if (UI::Button("Close"))
                            UI::CloseCurrentPopup();
                        UI::EndPopup();
                    }
                    UI::PopID();
                }
            }

            // [2.3] Right-click anywhere in columns to open another custom popup
            // (instead of testing for !IsAnyItemHovered() we could also call OpenPopup() with uiPopupFlags_NoOpenOverExistingPopup
            // to manage popup priority as the popups triggers, here "are we hovering a column" are overlapping)
            int hovered_column = -1;
            for (int column = 0; column < COLUMNS_COUNT + 1; column++)
            {
                UI::PushID(column);
                if (UI::TableGetColumnFlags(column) & uiTableColumnFlags_IsHovered)
                    hovered_column = column;
                if (hovered_column == column && !UI::IsAnyItemHovered() && UI::IsMouseReleased(1))
                    UI::OpenPopup("MyPopup");
                if (UI::BeginPopup("MyPopup"))
                {
                    if (column == COLUMNS_COUNT)
                        UI::Text("This is a custom popup for unused space after the last column.");
                    else
                        UI::Text("This is a custom popup for Column %d", column);
                    if (UI::Button("Close"))
                        UI::CloseCurrentPopup();
                    UI::EndPopup();
                }
                UI::PopID();
            }

            UI::EndTable();
            UI::Text("Hovered column: %d", hovered_column);
        }
        UI::TreePop();
    }

    // Demonstrate creating multiple tables with the same ID
    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Synced instances"))
    {
        IMGUI_DEMO_MARKER("Tables/Synced instances");
        HelpMarker("Multiple tables with the same identifier will share their settings, width, visibility, order etc.");

        static uiTableFlags flags = uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable | uiTableFlags_Borders | uiTableFlags_SizingFixedFit | uiTableFlags_NoSavedSettings;
        UI::CheckboxFlags("uiTableFlags_Resizable", &flags, uiTableFlags_Resizable);
        UI::CheckboxFlags("uiTableFlags_ScrollY", &flags, uiTableFlags_ScrollY);
        UI::CheckboxFlags("uiTableFlags_SizingFixedFit", &flags, uiTableFlags_SizingFixedFit);
        UI::CheckboxFlags("uiTableFlags_HighlightHoveredColumn", &flags, uiTableFlags_HighlightHoveredColumn);
        for (int n = 0; n < 3; n++)
        {
            char buf[32];
            sprintf(buf, "Synced Table %d", n);
            bool open = UI::CollapsingHeader(buf, uiTreeFlags_DefaultOpen);
            if (open && UI::BeginTable("Table", 3, flags, vec2(0.0f, UI::GetTextLineHeightWithSpacing() * 5)))
            {
                UI::TableSetupColumn("One");
                UI::TableSetupColumn("Two");
                UI::TableSetupColumn("Three");
                UI::TableHeadersRow();
                const int cell_count = (n == 1) ? 27 : 9; // Make second table have a scrollbar to verify that additional decoration is not affecting column positions.
                for (int cell = 0; cell < cell_count; cell++)
                {
                    UI::TableNextColumn();
                    UI::Text("this cell %d", cell);
                }
                UI::EndTable();
            }
        }
        UI::TreePop();
    }

    // Demonstrate using Sorting facilities
    // This is a simplified version of the "Advanced" example, where we mostly focus on the code necessary to handle sorting.
    // Note that the "Advanced" example also showcase manually triggering a sort (e.g. if item quantities have been modified)
    static const char* template_items_names[] =
    {
        "Banana", "Apple", "Cherry", "Watermelon", "Grapefruit", "Strawberry", "Mango",
        "Kiwi", "Orange", "Pineapple", "Blueberry", "Plum", "Coconut", "Pear", "Apricot"
    };
    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Sorting"))
    {
        IMGUI_DEMO_MARKER("Tables/Sorting");
        // Create item list
        static ImVector<MyItem> items;
        if (items.Size == 0)
        {
            items.resize(50, MyItem());
            for (int n = 0; n < items.Size; n++)
            {
                const int template_n = n % IM_COUNTOF(template_items_names);
                MyItem& item = items[n];
                item.ID = n;
                item.Name = template_items_names[template_n];
                item.Quantity = (n * n - n) % 20; // Assign default quantities
            }
        }

        // Options
        static uiTableFlags flags =
            uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable | uiTableFlags_Sortable | uiTableFlags_SortMulti
            | uiTableFlags_RowBg | uiTableFlags_BordersOuter | uiTableFlags_BordersV | uiTableFlags_NoBordersInBody
            | uiTableFlags_ScrollY;
        PushStyleCompact();
        UI::CheckboxFlags("uiTableFlags_SortMulti", &flags, uiTableFlags_SortMulti);
        UI::SameLine(); HelpMarker("When sorting is enabled: hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).");
        UI::CheckboxFlags("uiTableFlags_SortTristate", &flags, uiTableFlags_SortTristate);
        UI::SameLine(); HelpMarker("When sorting is enabled: allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).");
        PopStyleCompact();

        if (UI::BeginTable("table_sorting", 4, flags, vec2(0.0f, TEXT_BASE_HEIGHT * 15), 0.0f))
        {
            // Declare columns
            // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
            // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
            // Demonstrate using a mixture of flags among available sort-related flags:
            // - uiTableColumnFlags_DefaultSort
            // - uiTableColumnFlags_NoSort / uiTableColumnFlags_NoSortAscending / uiTableColumnFlags_NoSortDescending
            // - uiTableColumnFlags_PreferSortAscending / uiTableColumnFlags_PreferSortDescending
            UI::TableSetupColumn("ID",       uiTableColumnFlags_DefaultSort          | uiTableColumnFlags_WidthFixed,   0.0f, MyItemColumnID_ID);
            UI::TableSetupColumn("Name",                                                  uiTableColumnFlags_WidthFixed,   0.0f, MyItemColumnID_Name);
            UI::TableSetupColumn("Action",   uiTableColumnFlags_NoSort               | uiTableColumnFlags_WidthFixed,   0.0f, MyItemColumnID_Action);
            UI::TableSetupColumn("Quantity", uiTableColumnFlags_PreferSortDescending | uiTableColumnFlags_WidthStretch, 0.0f, MyItemColumnID_Quantity);
            UI::TableSetupScrollFreeze(0, 1); // Make row always visible
            UI::TableHeadersRow();

            // Sort our data if sort specs have been changed!
            if (uiTableSortSpecs* sort_specs = UI::TableGetSortSpecs())
                if (sort_specs->SpecsDirty)
                {
                    MyItem::SortWithSortSpecs(sort_specs, items.Data, items.Size);
                    sort_specs->SpecsDirty = false;
                }

            // Demonstrate using clipper for large vertical lists
            uiListClipper clipper;
            clipper.Begin(items.Size);
            while (clipper.Step())
                for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
                {
                    // Display a data item
                    MyItem* item = &items[row_n];
                    UI::PushID(item->ID);
                    UI::TableNextRow();
                    UI::TableNextColumn();
                    UI::Text("%04d", item->ID);
                    UI::TableNextColumn();
                    UI::TextUnformatted(item->Name);
                    UI::TableNextColumn();
                    UI::SmallButton("None");
                    UI::TableNextColumn();
                    UI::Text("%d", item->Quantity);
                    UI::PopID();
                }
            UI::EndTable();
        }
        UI::TreePop();
    }

    // In this example we'll expose most table flags and settings.
    // For specific flags and settings refer to the corresponding section for more detailed explanation.
    // This section is mostly useful to experiment with combining certain flags or settings with each others.
    //UI::SetNextItemOpen(true, uiCond_Once); // [DEBUG]
    if (open_action != -1)
        UI::SetNextItemOpen(open_action != 0);
    if (UI::TreeNode("Advanced"))
    {
        IMGUI_DEMO_MARKER("Tables/Advanced");
        static uiTableFlags flags =
            uiTableFlags_Resizable | uiTableFlags_Reorderable | uiTableFlags_Hideable
            | uiTableFlags_Sortable | uiTableFlags_SortMulti
            | uiTableFlags_RowBg | uiTableFlags_Borders | uiTableFlags_NoBordersInBody
            | uiTableFlags_ScrollX | uiTableFlags_ScrollY
            | uiTableFlags_SizingFixedFit;
        static uiTableColumnFlags columns_base_flags = uiTableColumnFlags_None;

        enum ContentsType { CT_Text, CT_Button, CT_SmallButton, CT_FillButton, CT_Selectable, CT_SelectableSpanRow };
        static int contents_type = CT_SelectableSpanRow;
        const char* contents_type_names[] = { "Text", "Button", "SmallButton", "FillButton", "Selectable", "Selectable (span row)" };
        static int freeze_cols = 1;
        static int freeze_rows = 1;
        static int items_count = IM_COUNTOF(template_items_names) * 2;
        static vec2 outer_size_value = vec2(0.0f, TEXT_BASE_HEIGHT * 12);
        static float row_min_height = 0.0f; // Auto
        static float inner_width_with_scroll = 0.0f; // Auto-extend
        static bool outer_size_enabled = true;
        static bool show_headers = true;
        static bool show_wrapped_text = false;
        //static uiTextFilter filter;
        //UI::SetNextItemOpen(true, uiCond_Once); // FIXME-TABLE: Enabling this results in initial clipped first pass on table which tend to affect column sizing
        if (UI::TreeNode("Options"))
        {
            // Make the UI compact because there are so many fields
            PushStyleCompact();
            UI::PushItemWidth(TEXT_BASE_WIDTH * 28.0f);

            if (UI::TreeNodeEx("Features:", uiTreeFlags_DefaultOpen))
            {
                UI::CheckboxFlags("uiTableFlags_Resizable", &flags, uiTableFlags_Resizable);
                UI::CheckboxFlags("uiTableFlags_Reorderable", &flags, uiTableFlags_Reorderable);
                UI::CheckboxFlags("uiTableFlags_Hideable", &flags, uiTableFlags_Hideable);
                UI::CheckboxFlags("uiTableFlags_Sortable", &flags, uiTableFlags_Sortable);
                UI::CheckboxFlags("uiTableFlags_NoSavedSettings", &flags, uiTableFlags_NoSavedSettings);
                UI::CheckboxFlags("uiTableFlags_ContextMenuInBody", &flags, uiTableFlags_ContextMenuInBody);
                UI::TreePop();
            }

            if (UI::TreeNodeEx("Decorations:", uiTreeFlags_DefaultOpen))
            {
                UI::CheckboxFlags("uiTableFlags_RowBg", &flags, uiTableFlags_RowBg);
                UI::CheckboxFlags("uiTableFlags_BordersV", &flags, uiTableFlags_BordersV);
                UI::CheckboxFlags("uiTableFlags_BordersOuterV", &flags, uiTableFlags_BordersOuterV);
                UI::CheckboxFlags("uiTableFlags_BordersInnerV", &flags, uiTableFlags_BordersInnerV);
                UI::CheckboxFlags("uiTableFlags_BordersH", &flags, uiTableFlags_BordersH);
                UI::CheckboxFlags("uiTableFlags_BordersOuterH", &flags, uiTableFlags_BordersOuterH);
                UI::CheckboxFlags("uiTableFlags_BordersInnerH", &flags, uiTableFlags_BordersInnerH);
                UI::CheckboxFlags("uiTableFlags_NoBordersInBody", &flags, uiTableFlags_NoBordersInBody); UI::SameLine(); HelpMarker("Disable vertical borders in columns Body (borders will always appear in Headers)");
                UI::CheckboxFlags("uiTableFlags_NoBordersInBodyUntilResize", &flags, uiTableFlags_NoBordersInBodyUntilResize); UI::SameLine(); HelpMarker("Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers)");
                UI::TreePop();
            }

            if (UI::TreeNodeEx("Sizing:", uiTreeFlags_DefaultOpen))
            {
                EditTableSizingFlags(&flags);
                UI::SameLine(); HelpMarker("In the Advanced demo we override the policy of each column so those table-wide settings have less effect that typical.");
                UI::CheckboxFlags("uiTableFlags_NoHostExtendX", &flags, uiTableFlags_NoHostExtendX);
                UI::SameLine(); HelpMarker("Make outer width auto-fit to columns, overriding outer_size.x value.\n\nOnly available when ScrollX/ScrollY are disabled and Stretch columns are not used.");
                UI::CheckboxFlags("uiTableFlags_NoHostExtendY", &flags, uiTableFlags_NoHostExtendY);
                UI::SameLine(); HelpMarker("Make outer height stop exactly at outer_size.y (prevent auto-extending table past the limit).\n\nOnly available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.");
                UI::CheckboxFlags("uiTableFlags_NoKeepColumnsVisible", &flags, uiTableFlags_NoKeepColumnsVisible);
                UI::SameLine(); HelpMarker("Only available if ScrollX is disabled.");
                UI::CheckboxFlags("uiTableFlags_PreciseWidths", &flags, uiTableFlags_PreciseWidths);
                UI::SameLine(); HelpMarker("Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.");
                UI::CheckboxFlags("uiTableFlags_NoClip", &flags, uiTableFlags_NoClip);
                UI::SameLine(); HelpMarker("Disable clipping rectangle for every individual columns (reduce draw command count, items will be able to overflow into other columns). Generally incompatible with ScrollFreeze options.");
                UI::TreePop();
            }

            if (UI::TreeNodeEx("Padding:", uiTreeFlags_DefaultOpen))
            {
                UI::CheckboxFlags("uiTableFlags_PadOuterX", &flags, uiTableFlags_PadOuterX);
                UI::CheckboxFlags("uiTableFlags_NoPadOuterX", &flags, uiTableFlags_NoPadOuterX);
                UI::CheckboxFlags("uiTableFlags_NoPadInnerX", &flags, uiTableFlags_NoPadInnerX);
                UI::TreePop();
            }

            if (UI::TreeNodeEx("Scrolling:", uiTreeFlags_DefaultOpen))
            {
                UI::CheckboxFlags("uiTableFlags_ScrollX", &flags, uiTableFlags_ScrollX);
                UI::SameLine();
                UI::SetNextItemWidth(UI::GetFrameHeight());
                UI::DragInt("freeze_cols", &freeze_cols, 0.2f, 0, 9, NULL, uiSliderFlags_NoInput);
                UI::CheckboxFlags("uiTableFlags_ScrollY", &flags, uiTableFlags_ScrollY);
                UI::SameLine();
                UI::SetNextItemWidth(UI::GetFrameHeight());
                UI::DragInt("freeze_rows", &freeze_rows, 0.2f, 0, 9, NULL, uiSliderFlags_NoInput);
                UI::TreePop();
            }

            if (UI::TreeNodeEx("Sorting:", uiTreeFlags_DefaultOpen))
            {
                UI::CheckboxFlags("uiTableFlags_SortMulti", &flags, uiTableFlags_SortMulti);
                UI::SameLine(); HelpMarker("When sorting is enabled: hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).");
                UI::CheckboxFlags("uiTableFlags_SortTristate", &flags, uiTableFlags_SortTristate);
                UI::SameLine(); HelpMarker("When sorting is enabled: allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).");
                UI::TreePop();
            }

            if (UI::TreeNodeEx("Headers:", uiTreeFlags_DefaultOpen))
            {
                UI::Checkbox("show_headers", &show_headers);
                UI::CheckboxFlags("uiTableFlags_HighlightHoveredColumn", &flags, uiTableFlags_HighlightHoveredColumn);
                UI::CheckboxFlags("uiTableColumnFlags_AngledHeader", &columns_base_flags, uiTableColumnFlags_AngledHeader);
                UI::SameLine(); HelpMarker("Enable AngledHeader on all columns. Best enabled on selected narrow columns (see \"Angled headers\" section of the demo).");
                UI::TreePop();
            }

            if (UI::TreeNodeEx("Other:", uiTreeFlags_DefaultOpen))
            {
                UI::Checkbox("show_wrapped_text", &show_wrapped_text);

                UI::DragFloat2("##OuterSize", &outer_size_value.x);
                UI::SameLine(0.0f, UI::GetStyle().ItemInnerSpacing.x);
                UI::Checkbox("outer_size", &outer_size_enabled);
                UI::SameLine();
                HelpMarker("If scrolling is disabled (ScrollX and ScrollY not set):\n"
                    "- The table is output directly in the parent window.\n"
                    "- OuterSize.x < 0.0f will right-align the table.\n"
                    "- OuterSize.x = 0.0f will narrow fit the table unless there are any Stretch columns.\n"
                    "- OuterSize.y then becomes the minimum size for the table, which will extend vertically if there are more rows (unless NoHostExtendY is set).");

                // From a user point of view we will tend to use 'inner_width' differently depending on whether our table is embedding scrolling.
                // To facilitate toying with this demo we will actually pass 0.0f to the BeginTable() when ScrollX is disabled.
                UI::DragFloat("inner_width (when ScrollX active)", &inner_width_with_scroll, 1.0f, 0.0f, FLT_MAX);

                UI::DragFloat("row_min_height", &row_min_height, 1.0f, 0.0f, FLT_MAX);
                UI::SameLine(); HelpMarker("Specify height of the Selectable item.");

                UI::DragInt("items_count", &items_count, 0.1f, 0, 9999);
                UI::Combo("items_type (first column)", &contents_type, contents_type_names, IM_COUNTOF(contents_type_names));
                //filter.Draw("filter");
                UI::TreePop();
            }

            UI::PopItemWidth();
            PopStyleCompact();
            UI::Spacing();
            UI::TreePop();
        }

        // Update item list if we changed the number of items
        static ImVector<MyItem> items;
        static ImVector<int> selection;
        static bool items_need_sort = false;
        if (items.Size != items_count)
        {
            items.resize(items_count, MyItem());
            for (int n = 0; n < items_count; n++)
            {
                const int template_n = n % IM_COUNTOF(template_items_names);
                MyItem& item = items[n];
                item.ID = n;
                item.Name = template_items_names[template_n];
                item.Quantity = (template_n == 3) ? 10 : (template_n == 4) ? 20 : 0; // Assign default quantities
            }
        }

        const ImDrawList* parent_draw_list = UI::GetWindowDrawList();
        const int parent_draw_list_draw_cmd_count = parent_draw_list->CmdBuffer.Size;
        vec2 table_scroll_cur, table_scroll_max; // For debug display
        const ImDrawList* table_draw_list = NULL;  // "

        // Submit table
        const float inner_width_to_use = (flags & uiTableFlags_ScrollX) ? inner_width_with_scroll : 0.0f;
        if (UI::BeginTable("table_advanced", 6, flags, outer_size_enabled ? outer_size_value : vec2(0, 0), inner_width_to_use))
        {
            // Declare columns
            // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
            // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
            UI::TableSetupColumn("ID",           columns_base_flags | uiTableColumnFlags_DefaultSort | uiTableColumnFlags_WidthFixed | uiTableColumnFlags_NoHide, 0.0f, MyItemColumnID_ID);
            UI::TableSetupColumn("Name",         columns_base_flags | uiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
            UI::TableSetupColumn("Action",       columns_base_flags | uiTableColumnFlags_NoSort | uiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Action);
            UI::TableSetupColumn("Quantity",     columns_base_flags | uiTableColumnFlags_PreferSortDescending, 0.0f, MyItemColumnID_Quantity);
            UI::TableSetupColumn("Description",  columns_base_flags | ((flags & uiTableFlags_NoHostExtendX) ? 0 : uiTableColumnFlags_WidthStretch), 0.0f, MyItemColumnID_Description);
            UI::TableSetupColumn("Hidden",       columns_base_flags |  uiTableColumnFlags_DefaultHide | uiTableColumnFlags_NoSort);
            UI::TableSetupScrollFreeze(freeze_cols, freeze_rows);

            // Sort our data if sort specs have been changed!
            uiTableSortSpecs* sort_specs = UI::TableGetSortSpecs();
            if (sort_specs && sort_specs->SpecsDirty)
                items_need_sort = true;
            if (sort_specs && items_need_sort && items.Size > 1)
            {
                MyItem::SortWithSortSpecs(sort_specs, items.Data, items.Size);
                sort_specs->SpecsDirty = false;
            }
            items_need_sort = false;

            // Take note of whether we are currently sorting based on the Quantity field,
            // we will use this to trigger sorting when we know the data of this column has been modified.
            const bool sorts_specs_using_quantity = (UI::TableGetColumnFlags(3) & uiTableColumnFlags_IsSorted) != 0;

            // Show headers
            if (show_headers && (columns_base_flags & uiTableColumnFlags_AngledHeader) != 0)
                UI::TableAngledHeadersRow();
            if (show_headers)
                UI::TableHeadersRow();

            // Show data
            // FIXME-TABLE FIXME-NAV: How we can get decent up/down even though we have the buttons here?
#if 1
            // Demonstrate using clipper for large vertical lists
            uiListClipper clipper;
            clipper.Begin(items.Size);
            while (clipper.Step())
            {
                for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
#else
            // Without clipper
            {
                for (int row_n = 0; row_n < items.Size; row_n++)
#endif
                {
                    MyItem* item = &items[row_n];
                    //if (!filter.PassFilter(item->Name))
                    //    continue;

                    const bool item_is_selected = selection.contains(item->ID);
                    UI::PushID(item->ID);
                    UI::TableNextRow(uiTableRowFlags_None, row_min_height);

                    // For the demo purpose we can select among different type of items submitted in the first column
                    UI::TableSetColumnIndex(0);
                    char label[32];
                    sprintf(label, "%04d", item->ID);
                    if (contents_type == CT_Text)
                        UI::TextUnformatted(label);
                    else if (contents_type == CT_Button)
                        UI::Button(label);
                    else if (contents_type == CT_SmallButton)
                        UI::SmallButton(label);
                    else if (contents_type == CT_FillButton)
                        UI::Button(label, vec2(-FLT_MIN, 0.0f));
                    else if (contents_type == CT_Selectable || contents_type == CT_SelectableSpanRow)
                    {
                        uiSelectFlags selectable_flags = (contents_type == CT_SelectableSpanRow) ? uiSelectFlags_SpanAllColumns | uiSelectFlags_AllowOverlap : uiSelectFlags_None;
                        if (UI::Selectable(label, item_is_selected, selectable_flags, vec2(0, row_min_height)))
                        {
                            if (UI::GetIO().KeyCtrl)
                            {
                                if (item_is_selected)
                                    selection.find_erase_unsorted(item->ID);
                                else
                                    selection.push_back(item->ID);
                            }
                            else
                            {
                                selection.clear();
                                selection.push_back(item->ID);
                            }
                        }
                    }

                    if (UI::TableSetColumnIndex(1))
                        UI::TextUnformatted(item->Name);

                    // Here we demonstrate marking our data set as needing to be sorted again if we modified a quantity,
                    // and we are currently sorting on the column showing the Quantity.
                    // To avoid triggering a sort while holding the button, we only trigger it when the button has been released.
                    // You will probably need some extra logic if you want to automatically sort when a specific entry changes.
                    if (UI::TableSetColumnIndex(2))
                    {
                        if (UI::SmallButton("Chop")) { item->Quantity += 1; }
                        if (sorts_specs_using_quantity && UI::IsItemDeactivated()) { items_need_sort = true; }
                        UI::SameLine();
                        if (UI::SmallButton("Eat")) { item->Quantity -= 1; }
                        if (sorts_specs_using_quantity && UI::IsItemDeactivated()) { items_need_sort = true; }
                    }

                    if (UI::TableSetColumnIndex(3))
                        UI::Text("%d", item->Quantity);

                    UI::TableSetColumnIndex(4);
                    if (show_wrapped_text)
                        UI::TextWrapped("Lorem ipsum dolor sit amet");
                    else
                        UI::Text("Lorem ipsum dolor sit amet");

                    if (UI::TableSetColumnIndex(5))
                        UI::Text("1234");

                    UI::PopID();
                }
            }

            // Store some info to display debug details below
            table_scroll_cur = vec2(UI::GetScrollX(), UI::GetScrollY());
            table_scroll_max = vec2(UI::GetScrollMaxX(), UI::GetScrollMaxY());
            table_draw_list = UI::GetWindowDrawList();
            UI::EndTable();
        }
        static bool show_debug_details = false;
        UI::Checkbox("Debug details", &show_debug_details);
        if (show_debug_details && table_draw_list)
        {
            UI::SameLine(0.0f, 0.0f);
            const int table_draw_list_draw_cmd_count = table_draw_list->CmdBuffer.Size;
            if (table_draw_list == parent_draw_list)
                UI::Text(": DrawCmd: +%d (in same window)",
                    table_draw_list_draw_cmd_count - parent_draw_list_draw_cmd_count);
            else
                UI::Text(": DrawCmd: +%d (in child window), Scroll: (%.f/%.f) (%.f/%.f)",
                    table_draw_list_draw_cmd_count - 1, table_scroll_cur.x, table_scroll_max.x, table_scroll_cur.y, table_scroll_max.y);
        }
        UI::TreePop();
    }

    UI::PopID();

    DemoWindowColumns();

    if (disable_indent)
        UI::PopStyleVar();
}

// Demonstrate old/legacy Columns API!
// [2020: Columns are under-featured and not maintained. Prefer using the more flexible and powerful BeginTable() API!]
static void DemoWindowColumns()
{
    bool open = UI::TreeNode("Legacy Columns API");
    UI::SameLine();
    HelpMarker("Columns() is an old API! Prefer using the more flexible and powerful BeginTable() API!");
    if (!open)
        return;

    // Basic columns
    if (UI::TreeNode("Basic"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Basic");
        UI::Text("Without border:");
        UI::Columns(3, "mycolumns3", false);  // 3-ways, no border
        UI::Barrier();
        for (int n = 0; n < 14; n++)
        {
            char label[32];
            sprintf(label, "Item %d", n);
            if (UI::Selectable(label)) {}
            //if (UI::Button(label, vec2(-FLT_MIN,0.0f))) {}
            UI::NextColumn();
        }
        UI::Columns(1);
        UI::Barrier();

        UI::Text("With border:");
        UI::Columns(4, "mycolumns"); // 4-ways, with border
        UI::Barrier();
        UI::Text("ID"); UI::NextColumn();
        UI::Text("Name"); UI::NextColumn();
        UI::Text("Path"); UI::NextColumn();
        UI::Text("Hovered"); UI::NextColumn();
        UI::Barrier();
        const char* names[3] = { "One", "Two", "Three" };
        const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
        static int selected = -1;
        for (int i = 0; i < 3; i++)
        {
            char label[32];
            sprintf(label, "%04d", i);
            if (UI::Selectable(label, selected == i, uiSelectFlags_SpanAllColumns))
                selected = i;
            bool hovered = UI::IsItemHovered();
            UI::NextColumn();
            UI::Text(names[i]); UI::NextColumn();
            UI::Text(paths[i]); UI::NextColumn();
            UI::Text("%d", hovered); UI::NextColumn();
        }
        UI::Columns(1);
        UI::Barrier();
        UI::TreePop();
    }

    if (UI::TreeNode("Borders"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Borders");
        // NB: Future columns API should allow automatic horizontal borders.
        static bool h_borders = true;
        static bool v_borders = true;
        static int columns_count = 4;
        const int lines_count = 3;
        UI::SetNextItemWidth(UI::GetFontSize() * 8);
        UI::DragInt("##columns_count", &columns_count, 0.1f, 2, 10, "%d columns");
        if (columns_count < 2)
            columns_count = 2;
        UI::SameLine();
        UI::Checkbox("horizontal", &h_borders);
        UI::SameLine();
        UI::Checkbox("vertical", &v_borders);
        UI::Columns(columns_count, NULL, v_borders);
        for (int i = 0; i < columns_count * lines_count; i++)
        {
            if (h_borders && UI::GetColumnIndex() == 0)
                UI::Barrier();
            UI::PushID(i);
            UI::Text("%c%c%c", 'a' + i, 'a' + i, 'a' + i);
            UI::Text("Width %.2f", UI::GetColumnWidth());
            UI::Text("Avail %.2f", UI::GetContentRegionAvail().x);
            UI::Text("Offset %.2f", UI::GetColumnOffset());
            UI::Text("Long text that is likely to clip");
            UI::Button("Button", vec2(-FLT_MIN, 0.0f));
            UI::PopID();
            UI::NextColumn();
        }
        UI::Columns(1);
        if (h_borders)
            UI::Barrier();
        UI::TreePop();
    }

    // Create multiple items in a same cell before switching to next column
    if (UI::TreeNode("Mixed items"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Mixed items");
        UI::Columns(3, "mixed");
        UI::Barrier();

        UI::Text("Hello");
        UI::Button("Banana");
        UI::NextColumn();

        UI::Text("ImGui");
        UI::Button("Apple");
        static float foo = 1.0f;
        UI::InputFloat("red", &foo, 0.05f, 0, "%.3f");
        UI::Text("An extra line here.");
        UI::NextColumn();

        UI::Text("Sailor");
        UI::Button("Corniflower");
        static float bar = 1.0f;
        UI::InputFloat("blue", &bar, 0.05f, 0, "%.3f");
        UI::NextColumn();

        if (UI::CollapsingHeader("Category A")) { UI::Text("Blah blah blah"); } UI::NextColumn();
        if (UI::CollapsingHeader("Category B")) { UI::Text("Blah blah blah"); } UI::NextColumn();
        if (UI::CollapsingHeader("Category C")) { UI::Text("Blah blah blah"); } UI::NextColumn();
        UI::Columns(1);
        UI::Barrier();
        UI::TreePop();
    }

    // Word wrapping
    if (UI::TreeNode("Word-wrapping"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Word-wrapping");
        UI::Columns(2, "word-wrapping");
        UI::Barrier();
        UI::TextWrapped("The quick brown fox jumps over the lazy dog.");
        UI::TextWrapped("Hello Left");
        UI::NextColumn();
        UI::TextWrapped("The quick brown fox jumps over the lazy dog.");
        UI::TextWrapped("Hello Right");
        UI::Columns(1);
        UI::Barrier();
        UI::TreePop();
    }

    if (UI::TreeNode("Horizontal Scrolling"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Horizontal Scrolling");
        UI::SetNextWindowContentSize(vec2(1500.0f, 0.0f));
        vec2 child_size = vec2(0, UI::GetFontSize() * 20.0f);
        UI::BeginChild("##ScrollingRegion", child_size, uiChildFlags_None, uiWindowFlags_HorizontalScrollbar);
        UI::Columns(10);

        // Also demonstrate using clipper for large vertical lists
        int ITEMS_COUNT = 2000;
        uiListClipper clipper;
        clipper.Begin(ITEMS_COUNT);
        while (clipper.Step())
        {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                for (int j = 0; j < 10; j++)
                {
                    UI::Text("Line %d Column %d...", i, j);
                    UI::NextColumn();
                }
        }
        UI::Columns(1);
        UI::EndChild();
        UI::TreePop();
    }

    if (UI::TreeNode("Tree"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Tree");
        UI::Columns(2, "tree", true);
        for (int x = 0; x < 3; x++)
        {
            bool open1 = UI::TreeNode((void*)(intptr_t)x, "Node%d", x);
            UI::NextColumn();
            UI::Text("Node contents");
            UI::NextColumn();
            if (open1)
            {
                for (int y = 0; y < 3; y++)
                {
                    bool open2 = UI::TreeNode((void*)(intptr_t)y, "Node%d.%d", x, y);
                    UI::NextColumn();
                    UI::Text("Node contents");
                    if (open2)
                    {
                        UI::Text("Even more contents");
                        if (UI::TreeNode("Tree in column"))
                        {
                            UI::Text("The quick brown fox jumps over the lazy dog");
                            UI::TreePop();
                        }
                    }
                    UI::NextColumn();
                    if (open2)
                        UI::TreePop();
                }
                UI::TreePop();
            }
        }
        UI::Columns(1);
        UI::TreePop();
    }

    UI::TreePop();
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowInputs()
//-----------------------------------------------------------------------------

static void DemoWindowInputs()
{
    if (UI::CollapsingHeader("Inputs & Focus"))
    {
        uiIO& io = UI::GetIO();

        // Display inputs submitted to uiIO
        UI::SetNextItemOpen(true, uiCond_Once);
        bool inputs_opened = UI::TreeNode("Inputs");
        UI::SameLine();
        HelpMarker(
            "This is a simplified view. See more detailed input state:\n"
            "- in 'Tools->Metrics/Debugger->Inputs'.\n"
            "- in 'Tools->Debug Log->IO'.");
        if (inputs_opened)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Inputs");
            if (UI::IsMousePosValid())
                UI::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
            else
                UI::Text("Mouse pos: <INVALID>");
            UI::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
            UI::Text("Mouse down:");
            for (int i = 0; i < IM_COUNTOF(io.MouseDown); i++) if (UI::IsMouseDown(i)) { UI::SameLine(); UI::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
            UI::Text("Mouse wheel: %.1f", io.MouseWheel);
            UI::Text("Mouse clicked count:");
            for (int i = 0; i < IM_COUNTOF(io.MouseDown); i++) if (io.MouseClickedCount[i] > 0) { UI::SameLine(); UI::Text("b%d: %d", i, io.MouseClickedCount[i]); }

            // We iterate both legacy native range and named uiKey ranges. This is a little unusual/odd but this allows
            // displaying the data for old/new backends.
            // User code should never have to go through such hoops!
            // You can generally iterate between uiKey_NamedKey_BEGIN and uiKey_NamedKey_END.
            struct funcs { static bool IsLegacyNativeDupe(uiKey) { return false; } };
            uiKey start_key = uiKey_NamedKey_BEGIN;
            UI::Text("Keys down:");         for (uiKey key = start_key; key < uiKey_NamedKey_END; key = (uiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key) || !UI::IsKeyDown(key)) continue; UI::SameLine(); UI::Text((key < uiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", UI::GetKeyName(key), key); }
            UI::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
            UI::Text("Chars queue:");       for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; UI::SameLine();  UI::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.

            UI::TreePop();
        }

        // Display uiIO output flags
        UI::SetNextItemOpen(true, uiCond_Once);
        bool outputs_opened = UI::TreeNode("Outputs");
        UI::SameLine();
        HelpMarker(
            "The value of io.WantCaptureMouse and io.WantCaptureKeyboard are normally set by Dear ImGui "
            "to instruct your application of how to route inputs. Typically, when a value is true, it means "
            "Dear ImGui wants the corresponding inputs and we expect the underlying application to ignore them.\n\n"
            "The most typical case is: when hovering a window, Dear ImGui set io.WantCaptureMouse to true, "
            "and underlying application should ignore mouse inputs (in practice there are many and more subtle "
            "rules leading to how those flags are set).");
        if (outputs_opened)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Outputs");
            UI::Text("io.WantCaptureMouse: %d", io.WantCaptureMouse);
            UI::Text("io.WantCaptureMouseUnlessPopupClose: %d", io.WantCaptureMouseUnlessPopupClose);
            UI::Text("io.WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
            UI::Text("io.WantTextInput: %d", io.WantTextInput);
            UI::Text("io.WantSetMousePos: %d", io.WantSetMousePos);
            UI::Text("io.NavActive: %d, io.NavVisible: %d", io.NavActive, io.NavVisible);

            IMGUI_DEMO_MARKER("Inputs & Focus/Outputs/WantCapture override");
            if (UI::TreeNode("WantCapture override"))
            {
                HelpMarker(
                    "Hovering the colored canvas will override io.WantCaptureXXX fields.\n"
                    "Notice how normally (when set to none), the value of io.WantCaptureKeyboard would be false when hovering "
                    "and true when clicking.");
                static int capture_override_mouse = -1;
                static int capture_override_keyboard = -1;
                const char* capture_override_desc[] = { "None", "Set to false", "Set to true" };
                UI::SetNextItemWidth(UI::GetFontSize() * 15);
                UI::SliderInt("SetNextFrameWantCaptureMouse() on hover", &capture_override_mouse, -1, +1, capture_override_desc[capture_override_mouse + 1], uiSliderFlags_AlwaysClamp);
                UI::SetNextItemWidth(UI::GetFontSize() * 15);
                UI::SliderInt("SetNextFrameWantCaptureKeyboard() on hover", &capture_override_keyboard, -1, +1, capture_override_desc[capture_override_keyboard + 1], uiSliderFlags_AlwaysClamp);

                UI::ColorButton("##panel", vec4(0.7f, 0.1f, 0.7f, 1.0f), uiColorEditFlags_NoTooltip | uiColorEditFlags_NoDragDrop, vec2(128.0f, 96.0f)); // Dummy item
                if (UI::IsItemHovered() && capture_override_mouse != -1)
                    UI::SetNextFrameWantCaptureMouse(capture_override_mouse == 1);
                if (UI::IsItemHovered() && capture_override_keyboard != -1)
                    UI::SetNextFrameWantCaptureKeyboard(capture_override_keyboard == 1);

                UI::TreePop();
            }
            UI::TreePop();
        }

        // Demonstrate using Shortcut() and Routing Policies.
        // The general flow is:
        // - Code interested in a chord (e.g. "Ctrl+A") declares their intent.
        // - Multiple locations may be interested in same chord! Routing helps find a winner.
        // - Every frame, we resolve all claims and assign one owner if the modifiers are matching.
        // - The lower-level function is 'bool SetShortcutRouting()', returns true when caller got the route.
        // - Most of the times, SetShortcutRouting() is not called directly. User mostly calls Shortcut() with routing flags.
        // - If you call Shortcut() WITHOUT any routing option, it uses uiInputFlags_RouteFocused.
        // TL;DR: Most uses will simply be:
        // - Shortcut(uiMod_Ctrl | uiKey_A); // Use uiInputFlags_RouteFocused policy.
        if (UI::TreeNode("Shortcuts"))
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Shortcuts");
            static uiInputFlags route_options = uiInputFlags_Repeat;
            static uiInputFlags route_type = uiInputFlags_RouteFocused;
            UI::CheckboxFlags("uiInputFlags_Repeat", &route_options, uiInputFlags_Repeat);
            UI::RadioButton("uiInputFlags_RouteActive", &route_type, uiInputFlags_RouteActive);
            UI::RadioButton("uiInputFlags_RouteFocused (default)", &route_type, uiInputFlags_RouteFocused);
            UI::Indent();
            UI::BeginDisabled(route_type != uiInputFlags_RouteFocused);
            UI::CheckboxFlags("uiInputFlags_RouteOverActive##0", &route_options, uiInputFlags_RouteOverActive);
            UI::EndDisabled();
            UI::Unindent();
            UI::RadioButton("uiInputFlags_RouteGlobal", &route_type, uiInputFlags_RouteGlobal);
            UI::Indent();
            UI::BeginDisabled(route_type != uiInputFlags_RouteGlobal);
            UI::CheckboxFlags("uiInputFlags_RouteOverFocused", &route_options, uiInputFlags_RouteOverFocused);
            UI::CheckboxFlags("uiInputFlags_RouteOverActive", &route_options, uiInputFlags_RouteOverActive);
            UI::CheckboxFlags("uiInputFlags_RouteUnlessBgFocused", &route_options, uiInputFlags_RouteUnlessBgFocused);
            UI::EndDisabled();
            UI::Unindent();
            UI::RadioButton("uiInputFlags_RouteAlways", &route_type, uiInputFlags_RouteAlways);
            uiInputFlags flags = route_type | route_options; // Merged flags
            if (route_type != uiInputFlags_RouteGlobal)
                flags &= ~(uiInputFlags_RouteOverFocused | uiInputFlags_RouteOverActive | uiInputFlags_RouteUnlessBgFocused);

            UI::BarrierText("Using SetNextItemShortcut()");
            UI::Text("Ctrl+S");
            UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_S, flags | uiInputFlags_Tooltip);
            UI::Button("Save");
            UI::Text("Alt+F");
            UI::SetNextItemShortcut(uiMod_Alt | uiKey_F, flags | uiInputFlags_Tooltip);
            static float f = 0.5f;
            UI::SliderFloat("Factor", &f, 0.0f, 1.0f);

            UI::BarrierText("Using Shortcut()");
            const float line_height = UI::GetTextLineHeightWithSpacing();
            const uiKeyChord key_chord = uiMod_Ctrl | uiKey_A;

            UI::Text("Ctrl+A");
            UI::Text("IsWindowFocused: %d, Shortcut: %s", UI::IsWindowFocused(), UI::Shortcut(key_chord, flags) ? "PRESSED" : "...");

            UI::PushStyleColor(uiCol_ChildBg, vec4(1.0f, 0.0f, 1.0f, 0.1f));

            UI::BeginChild("WindowA", vec2(-FLT_MIN, line_height * 14), true);
            UI::Text("Press Ctrl+A and see who receives it!");
            UI::Barrier();

            // 1: Window polling for Ctrl+A
            UI::Text("(in WindowA)");
            UI::Text("IsWindowFocused: %d, Shortcut: %s", UI::IsWindowFocused(), UI::Shortcut(key_chord, flags) ? "PRESSED" : "...");

            // 2: InputText also polling for Ctrl+A: it always uses _RouteFocused internally (gets priority when active)
            // (Commented because the owner-aware version of Shortcut() is still in imgui_internal.h)
            //char str[16] = "Press Ctrl+A";
            //UI::Spacing();
            //UI::InputText("InputTextB", str, IM_COUNTOF(str), uiInputTextFlags_ReadOnly);
            //uiID item_id = UI::GetItemID();
            //UI::SameLine(); HelpMarker("Internal widgets always use _RouteFocused");
            //UI::Text("IsWindowFocused: %d, Shortcut: %s", UI::IsWindowFocused(), UI::Shortcut(key_chord, flags, item_id) ? "PRESSED" : "...");

            // 3: Dummy child is not claiming the route: focusing them shouldn't steal route away from WindowA
            UI::BeginChild("ChildD", vec2(-FLT_MIN, line_height * 4), true);
            UI::Text("(in ChildD: not using same Shortcut)");
            UI::Text("IsWindowFocused: %d", UI::IsWindowFocused());
            UI::EndChild();

            // 4: Child window polling for Ctrl+A. It is deeper than WindowA and gets priority when focused.
            UI::BeginChild("ChildE", vec2(-FLT_MIN, line_height * 4), true);
            UI::Text("(in ChildE: using same Shortcut)");
            UI::Text("IsWindowFocused: %d, Shortcut: %s", UI::IsWindowFocused(), UI::Shortcut(key_chord, flags) ? "PRESSED" : "...");
            UI::EndChild();

            // 5: In a popup
            if (UI::Button("Open Popup"))
                UI::OpenPopup("PopupF");
            if (UI::BeginPopup("PopupF"))
            {
                UI::Text("(in PopupF)");
                UI::Text("IsWindowFocused: %d, Shortcut: %s", UI::IsWindowFocused(), UI::Shortcut(key_chord, flags) ? "PRESSED" : "...");
                // (Commented because the owner-aware version of Shortcut() is still in imgui_internal.h)
                //UI::InputText("InputTextG", str, IM_COUNTOF(str), uiInputTextFlags_ReadOnly);
                //UI::Text("IsWindowFocused: %d, Shortcut: %s", UI::IsWindowFocused(), UI::Shortcut(key_chord, flags, UI::GetItemID()) ? "PRESSED" : "...");
                UI::EndPopup();
            }
            UI::EndChild();
            UI::PopStyleColor();

            UI::TreePop();
        }

        // Display mouse cursors
        if (UI::TreeNode("Mouse Cursors"))
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Mouse Cursors");
            const char* mouse_cursors_names[] = { "Arrow", "TextInput", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "Wait", "Progress", "NotAllowed" };
            IM_ASSERT(IM_COUNTOF(mouse_cursors_names) == uiMouseCursor_COUNT);

            uiMouseCursor current = UI::GetMouseCursor();
            const char* cursor_name = (current >= uiMouseCursor_Arrow) && (current < uiMouseCursor_COUNT) ? mouse_cursors_names[current] : "N/A";
            UI::Text("Current mouse cursor = %d: %s", current, cursor_name);
            UI::BeginDisabled(true);
            UI::CheckboxFlags("io.BackendFlags: HasMouseCursors", &io.BackendFlags, uiBackendFlags_HasMouseCursors);
            UI::EndDisabled();

            UI::Text("Hover to see mouse cursors:");
            UI::SameLine(); HelpMarker(
                "Your application can render a different mouse cursor based on what UI::GetMouseCursor() returns. "
                "If software cursor rendering (io.MouseDrawCursor) is set ImGui will draw the right cursor for you, "
                "otherwise your backend needs to handle it.");
            for (int i = 0; i < uiMouseCursor_COUNT; i++)
            {
                char label[32];
                sprintf(label, "Mouse cursor %d: %s", i, mouse_cursors_names[i]);
                UI::Bullet(); UI::Selectable(label, false);
                if (UI::IsItemHovered())
                    UI::SetMouseCursor(i);
            }
            UI::TreePop();
        }

        if (UI::TreeNode("Tabbing"))
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Tabbing");
            UI::Text("Use Tab/Shift+Tab to cycle through keyboard editable fields.");
            static char buf[32] = "hello";
            UI::InputText("1", buf, IM_COUNTOF(buf));
            UI::InputText("2", buf, IM_COUNTOF(buf));
            UI::InputText("3", buf, IM_COUNTOF(buf));
            UI::PushItemFlag(uiItemFlags_NoTabStop, true);
            UI::InputText("4 (tab skip)", buf, IM_COUNTOF(buf));
            UI::SameLine(); HelpMarker("Item won't be cycled through when using TAB or Shift+Tab.");
            UI::PopItemFlag();
            UI::InputText("5", buf, IM_COUNTOF(buf));
            UI::TreePop();
        }

        if (UI::TreeNode("Focus from code"))
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Focus from code");
            bool focus_1 = UI::Button("Focus on 1"); UI::SameLine();
            bool focus_2 = UI::Button("Focus on 2"); UI::SameLine();
            bool focus_3 = UI::Button("Focus on 3");
            int has_focus = 0;
            static char buf[128] = "click on a button to set focus";

            if (focus_1) UI::SetKeyboardFocusHere();
            UI::InputText("1", buf, IM_COUNTOF(buf));
            if (UI::IsItemActive()) has_focus = 1;

            if (focus_2) UI::SetKeyboardFocusHere();
            UI::InputText("2", buf, IM_COUNTOF(buf));
            if (UI::IsItemActive()) has_focus = 2;

            UI::PushItemFlag(uiItemFlags_NoTabStop, true);
            if (focus_3) UI::SetKeyboardFocusHere();
            UI::InputText("3 (tab skip)", buf, IM_COUNTOF(buf));
            if (UI::IsItemActive()) has_focus = 3;
            UI::SameLine(); HelpMarker("Item won't be cycled through when using TAB or Shift+Tab.");
            UI::PopItemFlag();

            if (has_focus)
                UI::Text("Item with focus: %d", has_focus);
            else
                UI::Text("Item with focus: <none>");

            // Use >= 0 parameter to SetKeyboardFocusHere() to focus an upcoming item
            static float f3[3] = { 0.0f, 0.0f, 0.0f };
            int focus_ahead = -1;
            if (UI::Button("Focus on X")) { focus_ahead = 0; } UI::SameLine();
            if (UI::Button("Focus on Y")) { focus_ahead = 1; } UI::SameLine();
            if (UI::Button("Focus on Z")) { focus_ahead = 2; }
            if (focus_ahead != -1) UI::SetKeyboardFocusHere(focus_ahead);
            UI::SliderFloat3("Float3", &f3[0], 0.0f, 1.0f);

            UI::TextWrapped("NB: Cursor & selection are preserved when refocusing last used item in code.");
            UI::TreePop();
        }

        if (UI::TreeNode("Dragging"))
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Dragging");
            UI::TextWrapped("You can use UI::GetMouseDragDelta(0) to query for the dragged amount on any widget.");
            for (int button = 0; button < 3; button++)
            {
                UI::Text("IsMouseDragging(%d):", button);
                UI::Text("  w/ default threshold: %d,", UI::IsMouseDragging(button));
                UI::Text("  w/ zero threshold: %d,", UI::IsMouseDragging(button, 0.0f));
                UI::Text("  w/ large threshold: %d,", UI::IsMouseDragging(button, 20.0f));
            }

            UI::Button("Drag Me");
            if (UI::IsItemActive())
                UI::GetForegroundDrawList()->AddLine(io.MouseClickedPos[0], io.MousePos, UI::GetColorU32(uiCol_Button), 4.0f); // Draw a line between the button and the mouse cursor

            // Drag operations gets "unlocked" when the mouse has moved past a certain threshold
            // (the default threshold is stored in io.MouseDragThreshold). You can request a lower or higher
            // threshold using the second parameter of IsMouseDragging() and GetMouseDragDelta().
            vec2 value_raw = UI::GetMouseDragDelta(0, 0.0f);
            vec2 value_with_lock_threshold = UI::GetMouseDragDelta(0);
            vec2 mouse_delta = io.MouseDelta;
            UI::Text("GetMouseDragDelta(0):");
            UI::Text("  w/ default threshold: (%.1f, %.1f)", value_with_lock_threshold.x, value_with_lock_threshold.y);
            UI::Text("  w/ zero threshold: (%.1f, %.1f)", value_raw.x, value_raw.y);
            UI::Text("io.MouseDelta: (%.1f, %.1f)", mouse_delta.x, mouse_delta.y);
            UI::TreePop();
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] About Window / ShowAboutWindow()
// Access from Dear ImGui Demo -> Tools -> About
//-----------------------------------------------------------------------------

void UI::ShowAboutWindow(bool* p_open)
{
    if (!UI::Begin("About Dear ImGui", p_open, uiWindowFlags_AutoResize))
    {
        UI::End();
        return;
    }
    IMGUI_DEMO_MARKER("Tools/About Dear ImGui");
    UI::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);

    UI::TextLinkOpenURL("Homepage", "https://github.com/ocornut/imgui");
    UI::SameLine();
    UI::TextLinkOpenURL("FAQ", "https://github.com/ocornut/imgui/blob/master/docs/FAQ.md");
    UI::SameLine();
    UI::TextLinkOpenURL("Wiki", "https://github.com/ocornut/imgui/wiki");
    UI::SameLine();
    UI::TextLinkOpenURL("Extensions", "https://github.com/ocornut/imgui/wiki/Useful-Extensions");
    UI::SameLine();
    UI::TextLinkOpenURL("Releases", "https://github.com/ocornut/imgui/releases");
    UI::SameLine();
    UI::TextLinkOpenURL("Funding", "https://github.com/ocornut/imgui/wiki/Funding");

    UI::Barrier();
    UI::Text("(c) 2014-2026 Omar Cornut");
    UI::Text("Developed by Omar Cornut and all Dear ImGui contributors.");
    UI::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");
    UI::Text("If your company uses this, please consider funding the project.");

    static bool show_config_info = false;
    UI::Checkbox("Config/Build Information", &show_config_info);
    if (show_config_info)
    {
        uiIO& io = UI::GetIO();
        uiStyle& style = UI::GetStyle();

        bool copy_to_clipboard = UI::Button("Copy to clipboard");
        vec2 child_size = vec2(0, UI::GetTextLineHeightWithSpacing() * 18);
        UI::BeginChild(UI::GetID("cfg_infos"), child_size, uiChildFlags_FrameStyle);
        if (copy_to_clipboard)
        {
            UI::LogToClipboard();
            UI::LogText("// (Copy from the next line. Keep the ``` markers for formatting.)\n");
            UI::LogText("```cpp\n"); // Back quotes will make text appears without formatting when pasting on GitHub
        }

        UI::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
        UI::Barrier();
        UI::Text("sizeof(size_t): %d, sizeof(ImDrawIdx): %d, sizeof(ImDrawVert): %d", (int)sizeof(size_t), (int)sizeof(ImDrawIdx), (int)sizeof(ImDrawVert));
        UI::Text("define: __cplusplus=%d", (int)__cplusplus);
#ifdef IMGUI_ENABLE_TEST_ENGINE
        UI::Text("define: IMGUI_ENABLE_TEST_ENGINE");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_WIN32_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_SHELL_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_DEFAULT_SHELL_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_FILE_FUNCTIONS
        UI::Text("define: IMGUI_DISABLE_FILE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_ALLOCATORS
        UI::Text("define: IMGUI_DISABLE_DEFAULT_ALLOCATORS");
#endif
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
        UI::Text("define: IMGUI_USE_BGRA_PACKED_COLOR");
#endif
#ifdef _WIN32
        UI::Text("define: _WIN32");
#endif
#ifdef _WIN64
        UI::Text("define: _WIN64");
#endif
#ifdef __linux__
        UI::Text("define: __linux__");
#endif
#ifdef __APPLE__
        UI::Text("define: __APPLE__");
#endif
#ifdef _MSC_VER
        UI::Text("define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef _MSVC_LANG
        UI::Text("define: _MSVC_LANG=%d", (int)_MSVC_LANG);
#endif
#ifdef __MINGW32__
        UI::Text("define: __MINGW32__");
#endif
#ifdef __MINGW64__
        UI::Text("define: __MINGW64__");
#endif
#ifdef __GNUC__
        UI::Text("define: __GNUC__=%d", (int)__GNUC__);
#endif
#ifdef __clang_version__
        UI::Text("define: __clang_version__=%s", __clang_version__);
#endif
#ifdef __EMSCRIPTEN__
        UI::Text("define: __EMSCRIPTEN__");
#ifdef __EMSCRIPTEN_MAJOR__
        UI::Text("Emscripten: %d.%d.%d", __EMSCRIPTEN_MAJOR__, __EMSCRIPTEN_MINOR__, __EMSCRIPTEN_TINY__);
#else
        UI::Text("Emscripten: %d.%d.%d", __EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__);
#endif
#endif
#ifdef IMGUI_HAS_VIEWPORT
        UI::Text("define: IMGUI_HAS_VIEWPORT");
#endif
#ifdef IMGUI_HAS_DOCK
        UI::Text("define: IMGUI_HAS_DOCK");
#endif
#ifdef NDEBUG
        UI::Text("define: NDEBUG");
#endif

        // Heuristic to detect no-op IM_ASSERT() macros
        // - This is designed so people opening bug reports would convey and notice that they have disabled asserts for Dear ImGui code.
        // - 16 is > strlen("((void)(_EXPR))") which we suggested in our imconfig.h template as a possible way to disable.
        int assert_runs_expression = 0;
        IM_ASSERT(++assert_runs_expression);
        int assert_expand_len = (int)strlen(IM_STRINGIFY((IM_ASSERT(true))));
        bool assert_maybe_disabled = (!assert_runs_expression || assert_expand_len <= 16);
        UI::Text("IM_ASSERT: runs expression: %s. expand size: %s%s",
            assert_runs_expression ? "OK" : "KO", (assert_expand_len > 16) ? "OK" : "KO", assert_maybe_disabled ? " (MAYBE DISABLED?!)" : "");
        if (assert_maybe_disabled)
        {
            UI::SameLine();
            HelpMarker("IM_ASSERT() calls assert() by default. Compiling with NDEBUG will usually strip out assert() to nothing, which is NOT recommended because we use asserts to notify of programmer mistakes!");
        }

        UI::Barrier();
        UI::Text("io.BackendPlatformName: %s", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
        UI::Text("io.BackendRendererName: %s", io.BackendRendererName ? io.BackendRendererName : "NULL");
        UI::Text("io.ConfigFlags: 0x%08X", io.ConfigFlags);
        if (io.ConfigFlags & uiConfigFlags_NavEnableKeyboard)        UI::Text(" NavEnableKeyboard");
        if (io.ConfigFlags & uiConfigFlags_NavEnableGamepad)         UI::Text(" NavEnableGamepad");
        if (io.ConfigFlags & uiConfigFlags_NoMouse)                  UI::Text(" NoMouse");
        if (io.ConfigFlags & uiConfigFlags_NoMouseCursorChange)      UI::Text(" NoMouseCursorChange");
        if (io.ConfigFlags & uiConfigFlags_NoKeyboard)               UI::Text(" NoKeyboard");
        if (io.ConfigFlags & uiConfigFlags_DockingEnable)            UI::Text(" DockingEnable");
        if (io.ConfigFlags & uiConfigFlags_ViewportsEnable)          UI::Text(" ViewportsEnable");
        if (io.MouseDrawCursor)                                         UI::Text("io.MouseDrawCursor");
        if (io.ConfigDpiScaleFonts)                                     UI::Text("io.ConfigDpiScaleFonts");
        if (io.ConfigDpiScaleViewports)                                 UI::Text("io.ConfigDpiScaleViewports");
        if (io.ConfigViewportsNoAutoMerge)                              UI::Text("io.ConfigViewportsNoAutoMerge");
        if (io.ConfigViewportsNoTaskBarIcon)                            UI::Text("io.ConfigViewportsNoTaskBarIcon");
        if (io.ConfigViewportsNoDecoration)                             UI::Text("io.ConfigViewportsNoDecoration");
        if (io.ConfigViewportsNoDefaultParent)                          UI::Text("io.ConfigViewportsNoDefaultParent");
        if (io.ConfigDockingNoSplit)                                    UI::Text("io.ConfigDockingNoSplit");
        if (io.ConfigDockingNoDockingOver)                              UI::Text("io.ConfigDockingNoDockingOver");
        if (io.ConfigDockingWithShift)                                  UI::Text("io.ConfigDockingWithShift");
        if (io.ConfigDockingAlwaysTabBar)                               UI::Text("io.ConfigDockingAlwaysTabBar");
        if (io.ConfigDockingTransparentPayload)                         UI::Text("io.ConfigDockingTransparentPayload");
        if (io.ConfigMacOSXBehaviors)                                   UI::Text("io.ConfigMacOSXBehaviors");
        if (io.ConfigNavMoveSetMousePos)                                UI::Text("io.ConfigNavMoveSetMousePos");
        if (io.ConfigNavCaptureKeyboard)                                UI::Text("io.ConfigNavCaptureKeyboard");
        if (io.ConfigInputTextCursorBlink)                              UI::Text("io.ConfigInputTextCursorBlink");
        if (io.ConfigWindowsResizeFromEdges)                            UI::Text("io.ConfigWindowsResizeFromEdges");
        if (io.ConfigWindowsMoveFromTitleBarOnly)                       UI::Text("io.ConfigWindowsMoveFromTitleBarOnly");
        if (io.ConfigMemoryCompactTimer >= 0.0f)                        UI::Text("io.ConfigMemoryCompactTimer = %.1f", io.ConfigMemoryCompactTimer);
        UI::Text("io.BackendFlags: 0x%08X", io.BackendFlags);
        if (io.BackendFlags & uiBackendFlags_HasGamepad)             UI::Text(" HasGamepad");
        if (io.BackendFlags & uiBackendFlags_HasMouseCursors)        UI::Text(" HasMouseCursors");
        if (io.BackendFlags & uiBackendFlags_HasSetMousePos)         UI::Text(" HasSetMousePos");
        if (io.BackendFlags & uiBackendFlags_PlatformHasViewports)   UI::Text(" PlatformHasViewports");
        if (io.BackendFlags & uiBackendFlags_HasMouseHoveredViewport)UI::Text(" HasMouseHoveredViewport");
        if (io.BackendFlags & uiBackendFlags_HasParentViewport)      UI::Text(" HasParentViewport");
        if (io.BackendFlags & uiBackendFlags_RendererHasVtxOffset)   UI::Text(" RendererHasVtxOffset");
        if (io.BackendFlags & uiBackendFlags_RendererHasTextures)    UI::Text(" RendererHasTextures");
        if (io.BackendFlags & uiBackendFlags_RendererHasViewports)   UI::Text(" RendererHasViewports");
        UI::Barrier();
        UI::Text("io.Fonts: %d fonts, Flags: 0x%08X, TexSize: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexData->Width, io.Fonts->TexData->Height);
        UI::Text("io.Fonts->FontLoaderName: %s", io.Fonts->FontLoaderName ? io.Fonts->FontLoaderName : "NULL");
        UI::Text("io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y);
        UI::Text("io.DisplayFramebufferScale: %.2f,%.2f", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        UI::Barrier();
        UI::Text("style.WindowPadding: %.2f,%.2f", style.WindowPadding.x, style.WindowPadding.y);
        UI::Text("style.WindowBorderSize: %.2f", style.WindowBorderSize);
        UI::Text("style.FramePadding: %.2f,%.2f", style.FramePadding.x, style.FramePadding.y);
        UI::Text("style.FrameRounding: %.2f", style.FrameRounding);
        UI::Text("style.FrameBorderSize: %.2f", style.FrameBorderSize);
        UI::Text("style.ItemSpacing: %.2f,%.2f", style.ItemSpacing.x, style.ItemSpacing.y);
        UI::Text("style.ItemInnerSpacing: %.2f,%.2f", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);

        if (copy_to_clipboard)
        {
            UI::LogText("\n```\n");
            UI::LogFinish();
        }
        UI::EndChild();
    }
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Style Editor / ShowStyleEditor()
//-----------------------------------------------------------------------------
// - ShowStyleSelector()
// - ShowStyleEditor()
//-----------------------------------------------------------------------------

// Demo helper function to select among default colors. See ShowStyleEditor() for more advanced options.
bool UI::ShowStyleSelector(const char* label)
{
    // FIXME: This is a bit tricky to get right as style are functions, they don't register a name nor the fact that one is active.
    // So we keep track of last active one among our limited selection.
    static int style_idx = -1;
    const char* style_names[] = { "Dark", "Light", "Classic" };
    bool ret = false;
    if (UI::BeginCombo(label, (style_idx >= 0 && style_idx < IM_COUNTOF(style_names)) ? style_names[style_idx] : ""))
    {
        for (int n = 0; n < IM_COUNTOF(style_names); n++)
        {
            if (UI::Selectable(style_names[n], style_idx == n, uiSelectFlags_SelectOnNav))
            {
                style_idx = n;
                ret = true;
                switch (style_idx)
                {
                case 0: UI::StyleColorsDark(); break;
                case 1: UI::StyleColorsLight(); break;
                case 2: UI::StyleColorsClassic(); break;
                }
            }
            else if (style_idx == n)
                UI::SetItemDefaultFocus();
        }
        UI::EndCombo();
    }
    return ret;
}

static const char* GetTreeLinesFlagsName(uiTreeFlags flags)
{
    if (flags == uiTreeFlags_DrawLinesNone) return "DrawLinesNone";
    if (flags == uiTreeFlags_DrawLinesFull) return "DrawLinesFull";
    if (flags == uiTreeFlags_DrawLinesToNodes) return "DrawLinesToNodes";
    return "";
}

// We omit the UI:: prefix in this function, as we don't expect user to be copy and pasting this code.
void UI::ShowStyleEditor(uiStyle* ref) {
    uiStyle& style = GetStyle();
    static uiStyle ref_saved_style;
    // Default to using internal storage as reference
    static bool init = true;
    if (init && ref == NULL) ref_saved_style = style;
    init = false;
    if (ref == NULL) ref = &ref_saved_style;
    // The logic behind dynamically changing 'max_border_size' is to not encourage people to increase border size too much: it'll likely reveal lots of subtle rendering artifacts and this isn't a priority right now.
    // Note that _MainScale is currently internal PLEASE DO NOT USE IN YOUR CODE.
    const float default_border_size = (float)(int)style._MainScale;
    const float max_border_size = IM_MAX(default_border_size, 2.0f);
    PushItemWidth(GetWindowWidth() * 0.50f);
    {
        // General
        BarrierText("General");
        if ((GetIO().BackendFlags & uiBackendFlags_RendererHasTextures) == 0) {
            BulletText("Warning: Font scaling will NOT be smooth, because\nuiBackendFlags_RendererHasTextures is not set!");
            BulletText("For instructions, see:");
            SameLine();
            TextLinkOpenURL("docs/BACKENDS.md", "https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md");
        }
        if (ShowStyleSelector("Colors##Selector")) ref_saved_style = style;
        ShowFontSelector("Fonts##Selector");
        if (DragFloat("FontSizeBase", &style.FontSizeBase, 0.20f, 5.0f, 100.0f, "%.0f"))
            style._NextFrameFontSizeBase = style.FontSizeBase; // FIXME: Temporary hack until we finish remaining work.
        SameLine(0.0f, 0.0f); Text(" (out %.2f)", GetFontSize());
        DragFloat("FontScaleMain", &style.FontScaleMain, 0.02f, 0.5f, 4.0f);
        BeginDisabled(GetIO().ConfigDpiScaleFonts);
        DragFloat("FontScaleDpi", &style.FontScaleDpi, 0.02f, 0.5f, 4.0f);
        SetItemTooltip("When io.ConfigDpiScaleFonts is set, this value is automatically overwritten.");
        EndDisabled();
        // Simplified Settings (expose floating-pointer border sizes as boolean representing 0.0f or 1.0f)
        if (SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f"))
            style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
        { bool border = (style.WindowBorderSize > 0.0f); if (Checkbox("WindowBorder", &border)) { style.WindowBorderSize = border ? default_border_size : 0.0f; } }
        SameLine();
        { bool border = (style.FrameBorderSize > 0.0f);  if (Checkbox("FrameBorder", &border)) { style.FrameBorderSize = border ? default_border_size : 0.0f; } }
        SameLine();
        { bool border = (style.PopupBorderSize > 0.0f);  if (Checkbox("PopupBorder", &border)) { style.PopupBorderSize = border ? default_border_size : 0.0f; } }
    }
    // Save/Revert button
    if (Button("Save Ref")) *ref = ref_saved_style = style;
    SameLine();
    if (Button("Revert Ref")) style = *ref;
    SameLine();
    HelpMarker(
        "Save/Revert in local non-persistent storage. Default Colors definition are not affected. "
        "Use \"Export\" below to save them somewhere.");
    
    BarrierText("Details");
    if (BeginTabBar("##tabs", uiTabBarFlags_None)) {
        if (BeginTabItem("Sizes")) {
            BarrierText("Main");
            SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
            SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
            SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
            SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
            SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
            SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
            SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");

            BarrierText("Borders");
            SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, max_border_size, "%.0f");
            SliderFloat("ChildBorderSize", &style.ChildBorderSize, 0.0f, max_border_size, "%.0f");
            SliderFloat("PopupBorderSize", &style.PopupBorderSize, 0.0f, max_border_size, "%.0f");
            SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, max_border_size, "%.0f");

            BarrierText("Rounding");
            SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");

            BarrierText("Scrollbar");
            SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
            SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat("ScrollbarPadding", &style.ScrollbarPadding, 0.0f, 10.0f, "%.0f");

            BarrierText("Tabs");
            SliderFloat("TabBorderSize", &style.TabBorderSize, 0.0f, max_border_size, "%.0f");
            SliderFloat("TabBarBorderSize", &style.TabBarBorderSize, 0.0f, max_border_size, "%.0f");
            SliderFloat("TabBarOverlineSize", &style.TabBarOverlineSize, 0.0f, IM_MAX(3.0f, max_border_size), "%.0f");
            SameLine(); HelpMarker("Overline is only drawn over the selected tab when uiTabBarFlags_DrawSelectedOverline is set.");
            DragFloat("TabMinWidthBase", &style.TabMinWidthBase, 0.5f, 1.0f, 500.0f, "%.0f");
            DragFloat("TabMinWidthShrink", &style.TabMinWidthShrink, 0.5f, 1.0f, 500.0f, "%0.f");
            DragFloat("TabCloseButtonMinWidthSelected", &style.TabCloseButtonMinWidthSelected, 0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthSelected < 0.0f) ? "%.0f (Always)" : "%.0f");
            DragFloat("TabCloseButtonMinWidthUnselected", &style.TabCloseButtonMinWidthUnselected, 0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthUnselected < 0.0f) ? "%.0f (Always)" : "%.0f");
            SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");

            BarrierText("Tables");
            SliderFloat2("CellPadding", (float*)&style.CellPadding, 0.0f, 20.0f, "%.0f");
            SliderAngle("TableAngledHeadersAngle", &style.TableAngledHeadersAngle, -50.0f, +50.0f);
            SliderFloat2("TableAngledHeadersTextAlign", (float*)&style.TableAngledHeadersTextAlign, 0.0f, 1.0f, "%.2f");

            BarrierText("Trees");
            bool combo_open = BeginCombo("TreeLinesFlags", GetTreeLinesFlagsName(style.TreeLinesFlags));
            SameLine();
            HelpMarker("[Experimental] Tree lines may not work in all situations (e.g. using a clipper) and may incurs slight traversal overhead.\n\nuiTreeFlags_DrawLinesFull is faster than uiTreeFlags_DrawLinesToNode.");
            if (combo_open)
            {
                const uiTreeFlags options[] = { uiTreeFlags_DrawLinesNone, uiTreeFlags_DrawLinesFull, uiTreeFlags_DrawLinesToNodes };
                for (uiTreeFlags option : options)
                    if (Selectable(GetTreeLinesFlagsName(option), style.TreeLinesFlags == option))
                        style.TreeLinesFlags = option;
                EndCombo();
            }
            SliderFloat("TreeLinesSize", &style.TreeLinesSize, 0.0f, max_border_size, "%.0f");
            SliderFloat("TreeLinesRounding", &style.TreeLinesRounding, 0.0f, 12.0f, "%.0f");

            BarrierText("Windows");
            SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
            SliderFloat("WindowBorderHoverPadding", &style.WindowBorderHoverPadding, 1.0f, 20.0f, "%.0f");
            int window_menu_button_position = style.WindowMenuButtonPosition + 1;
            if (Combo("WindowMenuButtonPosition", (int*)&window_menu_button_position, "None\0Left\0Right\0"))
                style.WindowMenuButtonPosition = (Var::Dir)(window_menu_button_position - 1);

            BarrierText("Widgets");
            SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f");
            SameLine(); HelpMarker("Alignment applies when a button is larger than its text content.");
            SliderFloat2("SelectableTextAlign", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f");
            SameLine(); HelpMarker("Alignment applies when a selectable is larger than its text content.");
            SliderFloat("BarrierSize", &style.BarrierSize, 0.0f, 10.0f, "%.0f");
            SliderFloat("BarrierTextBorderSize", &style.BarrierTextBorderSize, 0.0f, 10.0f, "%.0f");
            SliderFloat2("BarrierTextAlign", (float*)&style.BarrierTextAlign, 0.0f, 1.0f, "%.2f");
            SliderFloat2("BarrierTextPadding", (float*)&style.BarrierTextPadding, 0.0f, 40.0f, "%.0f");
            SliderFloat("LogSliderDeadzone", &style.LogSliderDeadzone, 0.0f, 12.0f, "%.0f");
            SliderFloat("ImageRounding", &style.ImageRounding, 0.0f, 12.0f, "%.0f");

            BarrierText("Docking");
            //SetCursorPosX(GetCursorPosX() + CalcItemWidth() - GetFrameHeight());
            Checkbox("DockingNodeHasCloseButton", &style.DockingNodeHasCloseButton);
            SliderFloat("DockingBarrierSize", &style.DockingBarrierSize, 0.0f, 12.0f, "%.0f");

            BarrierText("Tooltips");
            for (int n = 0; n < 2; n++)
                if (TreeNodeEx(n == 0 ? "HoverFlagsForTooltipMouse" : "HoverFlagsForTooltipNav"))
                {
                    uiHoverFlags* p = (n == 0) ? &style.HoverFlagsForTooltipMouse : &style.HoverFlagsForTooltipNav;
                    CheckboxFlags("uiHoverFlags_DelayNormal", p, uiHoverFlags_Delay);
                    CheckboxFlags("uiHoverFlags_Stationary", p, uiHoverFlags_Stationary);
                    CheckboxFlags("uiHoverFlags_NoSharedDelay", p, uiHoverFlags_NoSharedDelay);
                    TreePop();
                }

            BarrierText("Misc");
            SliderFloat2("DisplayWindowPadding", (float*)&style.DisplayWindowPadding, 0.0f, 30.0f, "%.0f"); SameLine(); HelpMarker("Apply to regular windows: amount which we enforce to keep visible when moving near edges of your screen.");
            SliderFloat2("DisplaySafeAreaPadding", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f"); SameLine(); HelpMarker("Apply to every windows, menus, popups, tooltips: amount where we avoid displaying contents. Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");

            EndTabItem();
        }

        if (BeginTabItem("Colors"))
        {
            static int output_dest = 0;
            static bool output_only_modified = true;
            if (Button("Export"))
            {
                if (output_dest == 0)
                    LogToClipboard();
                else
                    LogToTTY();
                LogText("vec4* colors = GetStyle().Colors;" IM_NEWLINE);
                for (int i = 0; i < uiCol_COUNT; i++)
                {
                    const vec4& col = style.Colors[i];
                    const char* name = GetStyleColorName(i);
                    if (!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(vec4)) != 0)
                        LogText("colors[uiCol_%s]%*s= vec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE,
                            name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
                }
                LogFinish();
            }
            SameLine(); SetNextItemWidth(GetFontSize() * 10); Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0");
            SameLine(); Checkbox("Only Modified Colors", &output_only_modified);

            static uiTextFilter filter;
            filter.Draw("Filter colors", GetFontSize() * 16);

            static uiColorEditFlags alpha_flags = 0;
            if (RadioButton("Opaque", alpha_flags == uiColorEditFlags_AlphaOpaque))       { alpha_flags = uiColorEditFlags_AlphaOpaque; } SameLine();
            if (RadioButton("Alpha",  alpha_flags == uiColorEditFlags_None))              { alpha_flags = uiColorEditFlags_None; } SameLine();
            if (RadioButton("Both",   alpha_flags == uiColorEditFlags_AlphaPreviewHalf))  { alpha_flags = uiColorEditFlags_AlphaPreviewHalf; } SameLine();
            HelpMarker(
                "In the color list:\n"
                "Left-click on color square to open color picker,\n"
                "Right-click to open edit options menu.");

            SetNextWindowSizeConstraints(vec2(0.0f, GetTextLineHeightWithSpacing() * 10), vec2(FLT_MAX, FLT_MAX));
            BeginChild("##colors", vec2(0, 0), uiChildFlags_Borders | uiChildFlags_NavFlattened, uiWindowFlags_AlwaysVerticalScrollbar | uiWindowFlags_AlwaysHorizontalScrollbar);
            PushItemWidth(GetFontSize() * -12);
            for (int i = 0; i < uiCol_COUNT; i++)
            {
                const char* name = GetStyleColorName(i);
                if (!filter.PassFilter(name))
                    continue;
                PushID(i);
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
                if (Button("?"))
                    DebugFlashStyleColor((uiCol)i);
                SetItemTooltip("Flash given color to identify places where it is used.");
                SameLine();
#endif
                ColorEdit4("##color", (float*)&style.Colors[i], uiColorEditFlags_AlphaBar | alpha_flags);
                if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(vec4)) != 0)
                {
                    // Tips: in a real user application, you may want to merge and use an icon font into the main font,
                    // so instead of "Save"/"Revert" you'd use icons!
                    // Read the FAQ and docs/FONTS.md about using icon fonts. It's really easy and super convenient!
                    SameLine(0.0f, style.ItemInnerSpacing.x); if (Button("Save")) { ref->Colors[i] = style.Colors[i]; }
                    SameLine(0.0f, style.ItemInnerSpacing.x); if (Button("Revert")) { style.Colors[i] = ref->Colors[i]; }
                }
                SameLine(0.0f, style.ItemInnerSpacing.x);
                TextUnformatted(name);
                PopID();
            }
            PopItemWidth();
            EndChild();

            EndTabItem();
        }

        if (BeginTabItem("Fonts"))
        {
            uiIO& io = GetIO();
            ImFontAtlas* atlas = io.Fonts;
            ShowFontAtlas(atlas);

            // Post-baking font scaling. Note that this is NOT the nice way of scaling fonts, read below.
            // (we enforce hard clamping manually as by default DragFloat/SliderFloat allows Ctrl+Click text to get out of bounds).
            /*
            BarrierText("Legacy Scaling");
            const float MIN_SCALE = 0.3f;
            const float MAX_SCALE = 2.0f;
            HelpMarker(
                "Those are old settings provided for convenience.\n"
                "However, the _correct_ way of scaling your UI is currently to reload your font at the designed size, "
                "rebuild the font atlas, and call style.ScaleAllSizes() on a reference uiStyle structure.\n"
                "Using those settings here will give you poor quality results.");
            PushItemWidth(GetFontSize() * 8);
            DragFloat("global scale", &io.FontGlobalScale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", uiSliderFlags_AlwaysClamp); // Scale everything
            //static float window_scale = 1.0f;
            //if (DragFloat("window scale", &window_scale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", uiSliderFlags_AlwaysClamp)) // Scale only this window
            //    SetWindowFontScale(window_scale);
            PopItemWidth();
            */

            EndTabItem();
        }

        if (BeginTabItem("Rendering"))
        {
            PushItemWidth(GetFontSize() * 8);
            DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, 10.0f, "%.2f");
            if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;

            // When editing the "Circle Segment Max Error" value, draw a preview of its effect on auto-tessellated circles.
            DragFloat("Circle Tessellation Max Error", &style.CircleTessellationMaxError , 0.005f, 0.10f, 5.0f, "%.2f", uiSliderFlags_AlwaysClamp);
            const bool show_samples = IsItemActive();
            if (show_samples)
                SetNextWindowPos(GetCursorScreenPos());
            if (show_samples && BeginTooltip())
            {
                TextUnformatted("(R = radius, N = approx number of segments)");
                Spacing();
                ImDrawList* draw_list = GetWindowDrawList();
                const float min_widget_width = CalcTextSize("R: MMM\nN: MMM").x;
                for (int n = 0; n < 8; n++)
                {
                    const float RAD_MIN = 5.0f;
                    const float RAD_MAX = 70.0f;
                    const float rad = RAD_MIN + (RAD_MAX - RAD_MIN) * (float)n / (8.0f - 1.0f);

                    BeginGroup();

                    // N is not always exact here due to how PathArcTo() function work internally
                    Text("R: %.f\nN: %d", rad, draw_list->_CalcCircleAutoSegmentCount(rad));

                    const float canvas_width = IM_MAX(min_widget_width, rad * 2.0f);
                    const float offset_x     = floorf(canvas_width * 0.5f);
                    const float offset_y     = floorf(RAD_MAX);

                    const vec2 p1 = GetCursorScreenPos();
                    draw_list->AddCircle(vec2(p1.x + offset_x, p1.y + offset_y), rad, GetColorU32(uiCol_Text));
                    Dummy(vec2(canvas_width, RAD_MAX * 2));

                    /*
                    const vec2 p2 = GetCursorScreenPos();
                    draw_list->AddCircleFilled(vec2(p2.x + offset_x, p2.y + offset_y), rad, GetColorU32(uiCol_Text));
                    Dummy(vec2(canvas_width, RAD_MAX * 2));
                    */

                    EndGroup();
                    SameLine();
                }
                EndTooltip();
            }
            SameLine();
            HelpMarker("When drawing circle primitives with \"num_segments == 0\" tessellation will be calculated automatically.");

            DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
            DragFloat("Disabled Alpha", &style.DisabledAlpha, 0.005f, 0.0f, 1.0f, "%.2f"); SameLine(); HelpMarker("Additional alpha multiplier for disabled items (multiply over current value of Alpha).");
            PopItemWidth();

            EndTabItem();
        }

        EndTabBar();
    }
    PopItemWidth();
}

//-----------------------------------------------------------------------------
// [SECTION] User Guide / ShowUserGuide()
//-----------------------------------------------------------------------------

// We omit the UI:: prefix in this function, as we don't expect user to be copy and pasting this code.
void UI::ShowUserGuide()
{
    uiIO& io = GetIO();
    BulletText("Double-click on title bar to collapse window.");
    BulletText(
        "Click and drag on lower corner or border to resize window.\n"
        "(double-click to auto fit window to its contents)");
    BulletText("Ctrl+Click on a slider or drag box to input value as text.");
    BulletText("Tab/Shift+Tab to cycle through keyboard editable fields.");
    BulletText("Ctrl+Tab/Ctrl+Shift+Tab to focus windows.");
    if (io.FontAllowUserScaling)
        BulletText("Ctrl+Mouse Wheel to zoom window contents.");
    BulletText("While inputting text:\n");
    Indent();
    BulletText("Ctrl+Left/Right to word jump.");
    BulletText("Ctrl+A or double-click to select all.");
    BulletText("Ctrl+X/C/V to use clipboard cut/copy/paste.");
    BulletText("Ctrl+Z to undo, Ctrl+Y/Ctrl+Shift+Z to redo.");
    BulletText("Escape to revert.");
    Unindent();
    BulletText("With Keyboard controls enabled:");
    Indent();
    BulletText("Arrow keys or Home/End/PageUp/PageDown to navigate.");
    BulletText("Space to activate a widget.");
    BulletText("Return to input text into a widget.");
    BulletText("Escape to deactivate a widget, close popup,\nexit a child window or the menu layer, clear focus.");
    BulletText("Alt to jump to the menu layer of a window.");
    BulletText("Menu or Shift+F10 to open a context menu.");
    Unindent();
    BulletText("With Gamepad controls enabled:");
    Indent();
    BulletText("D-Pad: Navigate / Tweak / Resize (in Windowing mode).");
    BulletText("%s Face button: Activate / Open / Toggle. Hold: activate with text input.", io.ConfigNavSwapGamepadButtons ? "East" : "South");
    BulletText("%s Face button: Cancel / Close / Exit.", io.ConfigNavSwapGamepadButtons ? "South" : "East");
    BulletText("West Face button: Toggle Menu. Hold for Windowing mode (Focus/Move/Resize windows).");
    BulletText("North Face button: Open Context Menu.");
    BulletText("L1/R1: Tweak Slower/Faster, Focus Previous/Next (in Windowing Mode).");
    Unindent();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Main Menu Bar / ShowExampleAppMainMenuBar()
//-----------------------------------------------------------------------------
// - ShowExampleAppMainMenuBar()
// - ShowExampleMenuFile()
//-----------------------------------------------------------------------------

// Demonstrate creating a "main" fullscreen menu bar and populating it.
// Note the difference between BeginMainMenuBar() and BeginMenuBar():
// - BeginMenuBar() = menu-bar inside current window (which needs the uiWindowFlags_MenuBar flag!)
// - BeginMainMenuBar() = helper to create menu-bar-sized window at the top of the main viewport + call BeginMenuBar() into it.
static void ShowExampleAppMainMenuBar()
{
    if (UI::BeginMainMenuBar())
    {
        if (UI::BeginMenu("File"))
        {
            IMGUI_DEMO_MARKER("Menu/File");
            ShowExampleMenuFile();
            UI::EndMenu();
        }
        if (UI::BeginMenu("Edit"))
        {
            IMGUI_DEMO_MARKER("Menu/Edit");
            if (UI::MenuItem("Undo", "Ctrl+Z")) {}
            if (UI::MenuItem("Redo", "Ctrl+Y", false, false)) {} // Disabled item
            UI::Barrier();
            if (UI::MenuItem("Cut", "Ctrl+X")) {}
            if (UI::MenuItem("Copy", "Ctrl+C")) {}
            if (UI::MenuItem("Paste", "Ctrl+V")) {}
            UI::EndMenu();
        }
        UI::EndMainMenuBar();
    }
}

// Note that shortcuts are currently provided for display only
// (future version will add explicit flags to BeginMenu() to request processing shortcuts)
static void ShowExampleMenuFile()
{
    IMGUI_DEMO_MARKER("Examples/Menu");
    UI::MenuItem("(demo menu)", NULL, false, false);
    if (UI::MenuItem("New")) {}
    if (UI::MenuItem("Open", "Ctrl+O")) {}
    if (UI::BeginMenu("Open Recent"))
    {
        UI::MenuItem("fish_hat.c");
        UI::MenuItem("fish_hat.inl");
        UI::MenuItem("fish_hat.h");
        if (UI::BeginMenu("More.."))
        {
            UI::MenuItem("Hello");
            UI::MenuItem("Sailor");
            if (UI::BeginMenu("Recurse.."))
            {
                ShowExampleMenuFile();
                UI::EndMenu();
            }
            UI::EndMenu();
        }
        UI::EndMenu();
    }
    if (UI::MenuItem("Save", "Ctrl+S")) {}
    if (UI::MenuItem("Save As..")) {}

    UI::Barrier();
    if (UI::BeginMenu("Options"))
    {
        IMGUI_DEMO_MARKER("Examples/Menu/Options");
        static bool enabled = true;
        UI::MenuItem("Enabled", "", &enabled);
        UI::BeginChild("child", vec2(0, UI::GetTextLineHeightWithSpacing() * 5.0f), uiChildFlags_Borders);
        for (int i = 0; i < 10; i++)
            UI::Text("Scrolling Text %d", i);
        UI::EndChild();
        static float f = 0.5f;
        static int n = 0;
        UI::SliderFloat("Value", &f, 0.0f, 1.0f);
        UI::InputFloat("Input", &f, 0.1f);
        UI::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        UI::EndMenu();
    }

    if (UI::BeginMenu("Colors"))
    {
        IMGUI_DEMO_MARKER("Examples/Menu/Colors");
        float sz = UI::GetTextLineHeight();
        for (int i = 0; i < uiCol_COUNT; i++)
        {
            const char* name = UI::GetStyleColorName((uiCol)i);
            vec2 p = UI::GetCursorScreenPos();
            UI::GetWindowDrawList()->AddRectFilled(p, vec2(p.x + sz, p.y + sz), UI::GetColorU32((uiCol)i));
            UI::Dummy(vec2(sz, sz));
            UI::SameLine();
            UI::MenuItem(name);
        }
        UI::EndMenu();
    }

    // Here we demonstrate appending again to the "Options" menu (which we already created above)
    // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
    // In a real code-base using it would make senses to use this feature from very different code locations.
    if (UI::BeginMenu("Options")) // <-- Append!
    {
        IMGUI_DEMO_MARKER("Examples/Menu/Append to an existing menu");
        static bool b = true;
        UI::Checkbox("SomeOption", &b);
        UI::EndMenu();
    }

    if (UI::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (UI::MenuItem("Checked", NULL, true)) {}
    UI::Barrier();
    if (UI::MenuItem("Quit", "Alt+F4")) {}
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, we are using a more C++ like approach of declaring a class to hold both data and functions.
struct ExampleAppConsole
{
    char                  InputBuf[256];
    ImVector<char*>       Items;
    ImVector<const char*> Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    uiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;

    ExampleAppConsole()
    {
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;

        // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");
        AutoScroll = true;
        ScrollToBottom = false;
        AddLog("Welcome to Dear ImGui!");
    }
    ~ExampleAppConsole()
    {
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            UI::MemFree(History[i]);
    }

    // Portable helpers
    static int   Stricmp(const char* s1, const char* s2)         { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
    static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
    static char* Strdup(const char* s)                           { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = UI::MemAlloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
    static void  Strtrim(char* s)                                { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

    void    ClearLog()
    {
        for (int i = 0; i < Items.Size; i++)
            UI::MemFree(Items[i]);
        Items.clear();
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_COUNTOF(buf), fmt, args);
        buf[IM_COUNTOF(buf)-1] = 0;
        va_end(args);
        Items.push_back(Strdup(buf));
    }

    void    Draw(const char* title, bool* p_open)
    {
        UI::SetNextWindowSize(vec2(520, 600), uiCond_FirstUseEver);
        if (!UI::Begin(title, p_open))
        {
            UI::End();
            return;
        }
        IMGUI_DEMO_MARKER("Examples/Console");

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
        // So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (UI::BeginPopupContextItem())
        {
            if (UI::MenuItem("Close Console"))
                *p_open = false;
            UI::EndPopup();
        }

        UI::TextWrapped(
            "This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
            "implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
        UI::TextWrapped("Enter 'HELP' for help.");

        // TODO: display items starting from the bottom

        if (UI::SmallButton("Add Debug Text"))  { AddLog("%d some text", Items.Size); AddLog("some more text"); AddLog("display very important message here!"); }
        UI::SameLine();
        if (UI::SmallButton("Add Debug Error")) { AddLog("[error] something went wrong"); }
        UI::SameLine();
        if (UI::SmallButton("Clear"))           { ClearLog(); }
        UI::SameLine();
        bool copy_to_clipboard = UI::SmallButton("Copy");
        //static float t = 0.0f; if (UI::GetTime() - t > 0.02f) { t = UI::GetTime(); AddLog("Spam %f", t); }

        UI::Barrier();

        // Options menu
        if (UI::BeginPopup("Options"))
        {
            UI::Checkbox("Auto-scroll", &AutoScroll);
            UI::EndPopup();
        }

        // Options, Filter
        UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_O, uiInputFlags_Tooltip);
        if (UI::Button("Options"))
            UI::OpenPopup("Options");
        UI::SameLine();
        Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        UI::Barrier();

        // Reserve enough left-over height for 1 separator + 1 input text
        uiStyle& style = UI::GetStyle();
        const float footer_height_to_reserve = style.BarrierSize + style.ItemSpacing.y + UI::GetFrameHeightWithSpacing();
        if (UI::BeginChild("ScrollingRegion", vec2(0, -footer_height_to_reserve), uiChildFlags_NavFlattened, uiWindowFlags_HorizontalScrollbar))
        {
            if (UI::BeginPopupContextWindow())
            {
                if (UI::Selectable("Clear")) ClearLog();
                UI::EndPopup();
            }

            // Display every line as a separate entry so we can change their color or add custom widgets.
            // If you only want raw text you can use UI::TextUnformatted(log.begin(), log.end());
            // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
            // to only process visible items. The clipper will automatically measure the height of your first item and then
            // "seek" to display only items in the visible area.
            // To use the clipper we can replace your standard loop:
            //      for (int i = 0; i < Items.Size; i++)
            //   With:
            //      uiListClipper clipper;
            //      clipper.Begin(Items.Size);
            //      while (clipper.Step())
            //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            // - That your items are evenly spaced (same height)
            // - That you have cheap random access to your elements (you can access them given their index,
            //   without processing all the ones before)
            // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
            // We would need random-access on the post-filtered list.
            // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
            // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
            // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
            // to improve this example code!
            // If your items are of variable height:
            // - Split them into same height items would be simpler and facilitate random-seeking into your list.
            // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
            UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(4, 1)); // Tighten spacing
            if (copy_to_clipboard)
                UI::LogToClipboard();
            for (const char* item : Items)
            {
                if (!Filter.PassFilter(item))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                vec4 color;
                bool has_color = false;
                if (strstr(item, "[error]")) { color = vec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
                else if (strncmp(item, "# ", 2) == 0) { color = vec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
                if (has_color)
                    UI::PushStyleColor(uiCol_Text, color);
                UI::TextUnformatted(item);
                if (has_color)
                    UI::PopStyleColor();
            }
            if (copy_to_clipboard)
                UI::LogFinish();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (ScrollToBottom || (AutoScroll && UI::GetScrollY() >= UI::GetScrollMaxY()))
                UI::SetScrollHereY(1.0f);
            ScrollToBottom = false;

            UI::PopStyleVar();
        }
        UI::EndChild();
        UI::Barrier();

        // Command-line
        bool reclaim_focus = false;
        uiInputTextFlags input_text_flags = uiInputTextFlags_EnterReturnsTrue | uiInputTextFlags_EscapeClearsAll | uiInputTextFlags_CallbackCompletion | uiInputTextFlags_CallbackHistory;
        if (UI::InputText("Input", InputBuf, IM_COUNTOF(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
        {
            char* s = InputBuf;
            Strtrim(s);
            if (s[0])
                ExecCommand(s);
            strcpy(s, "");
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        UI::SetItemDefaultFocus();
        if (reclaim_focus)
            UI::SetKeyboardFocusHere(-1); // Auto focus previous widget

        UI::End();
    }

    void    ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back.
        // This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = History.Size - 1; i >= 0; i--)
            if (Stricmp(History[i], command_line) == 0)
            {
                UI::MemFree(History[i]);
                History.erase(History.begin() + i);
                break;
            }
        History.push_back(Strdup(command_line));

        // Process command
        if (Stricmp(command_line, "CLEAR") == 0)
        {
            ClearLog();
        }
        else if (Stricmp(command_line, "HELP") == 0)
        {
            AddLog("Commands:");
            for (int i = 0; i < Commands.Size; i++)
                AddLog("- %s", Commands[i]);
        }
        else if (Stricmp(command_line, "HISTORY") == 0)
        {
            int first = History.Size - 10;
            for (int i = first > 0 ? first : 0; i < History.Size; i++)
                AddLog("%3d: %s\n", i, History[i]);
        }
        else
        {
            AddLog("Unknown command: '%s'\n", command_line);
        }

        // On command input, we scroll to bottom even if AutoScroll==false
        ScrollToBottom = true;
    }

    // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
    static int TextEditCallbackStub(uiInputTextCallbackData* data)
    {
        ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
        return console->TextEditCallback(data);
    }

    int     TextEditCallback(uiInputTextCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case uiInputTextFlags_CallbackCompletion:
            {
                // Example of TEXT COMPLETION

                // Locate beginning of current word
                const char* word_end = data->Buf + data->CursorPos;
                const char* word_start = word_end;
                while (word_start > data->Buf)
                {
                    const char c = word_start[-1];
                    if (c == ' ' || c == '\t' || c == ',' || c == ';')
                        break;
                    word_start--;
                }

                // Build a list of candidates
                ImVector<const char*> candidates;
                for (int i = 0; i < Commands.Size; i++)
                    if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
                        candidates.push_back(Commands[i]);

                if (candidates.Size == 0)
                {
                    // No match
                    AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
                }
                else if (candidates.Size == 1)
                {
                    // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0]);
                    data->InsertChars(data->CursorPos, " ");
                }
                else
                {
                    // Multiple matches. Complete as much as we can..
                    // So inputting "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                    int match_len = (int)(word_end - word_start);
                    for (;;)
                    {
                        int c = 0;
                        bool all_candidates_matches = true;
                        for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                            if (i == 0)
                                c = toupper(candidates[i][match_len]);
                            else if (c == 0 || c != toupper(candidates[i][match_len]))
                                all_candidates_matches = false;
                        if (!all_candidates_matches)
                            break;
                        match_len++;
                    }

                    if (match_len > 0)
                    {
                        data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                        data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                    }

                    // List matches
                    AddLog("Possible matches:\n");
                    for (int i = 0; i < candidates.Size; i++)
                        AddLog("- %s\n", candidates[i]);
                }

                break;
            }
        case uiInputTextFlags_CallbackHistory:
            {
                // Example of HISTORY
                const int prev_history_pos = HistoryPos;
                if (data->EventKey == uiKey_UpArrow)
                {
                    if (HistoryPos == -1)
                        HistoryPos = History.Size - 1;
                    else if (HistoryPos > 0)
                        HistoryPos--;
                }
                else if (data->EventKey == uiKey_DownArrow)
                {
                    if (HistoryPos != -1)
                        if (++HistoryPos >= History.Size)
                            HistoryPos = -1;
                }

                // A better implementation would preserve the data on the current input line along with cursor position.
                if (prev_history_pos != HistoryPos)
                {
                    const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
                    data->DeleteChars(0, data->BufTextLen);
                    data->InsertChars(0, history_str);
                }
            }
        }
        return 0;
    }
};

static void ShowExampleAppConsole(bool* p_open)
{
    static ExampleAppConsole console;
    console.Draw("Example: Console", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Image Viewer / ShowExampleAppImageViewer()
//-----------------------------------------------------------------------------

static void ShowExampleAppImageViewer(bool* p_open)
{
    ImFontAtlas* atlas = UI::GetIO().Fonts;
    ImTextureRef tex_ref = atlas->TexRef; // We don't have access to other textures in this demo!
    int tex_w = atlas->TexData->Width;
    int tex_h = atlas->TexData->Height;
    if (UI::Begin("Example: Image Viewer", p_open))
    {
        static ExampleImageViewerData image_viewer;
        ExampleImageViewer_DrawOptions(&image_viewer);
        vec2 canvas_size = UI::GetContentRegionAvail();
        vec2 canvas_min_size = UI::IsWindowAppearing() ? vec2(3.0f * tex_w, 4.0f * tex_h) : vec2(1.0f, 1.0f);
        canvas_size = vec2(IM_MAX(canvas_size.x, canvas_min_size.x), IM_MAX(canvas_size.y, canvas_min_size.y));
        ExampleImageViewer_DrawCanvas(&image_viewer, canvas_size, tex_ref, tex_w, tex_h);
    }
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Log / ShowExampleAppLog()
//-----------------------------------------------------------------------------

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
struct ExampleAppLog
{
    uiTextBuffer     Buf;
    uiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                AutoScroll;  // Keep scrolling if already at the bottom.

    ExampleAppLog()
    {
        AutoScroll = true;
        Clear();
    }

    void    Clear()
    {
        Buf.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        if (!UI::Begin(title, p_open))
        {
            UI::End();
            return;
        }

        // Options menu
        if (UI::BeginPopup("Options"))
        {
            UI::Checkbox("Auto-scroll", &AutoScroll);
            UI::EndPopup();
        }

        // Main window
        if (UI::Button("Options"))
            UI::OpenPopup("Options");
        UI::SameLine();
        bool clear = UI::Button("Clear");
        UI::SameLine();
        bool copy = UI::Button("Copy");
        UI::SameLine();
        Filter.Draw("Filter", -100.0f);

        UI::Barrier();

        if (UI::BeginChild("scrolling", vec2(0, 0), uiChildFlags_None, uiWindowFlags_HorizontalScrollbar))
        {
            if (clear)
                Clear();
            if (copy)
                UI::LogToClipboard();

            UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(0, 0));
            const char* buf = Buf.begin();
            const char* buf_end = Buf.end();
            if (Filter.IsActive())
            {
                // In this example we don't use the clipper when Filter is enabled.
                // This is because we don't have random access to the result of our filter.
                // A real application processing logs with ten of thousands of entries may want to store the result of
                // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
                for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end))
                        UI::TextUnformatted(line_start, line_end);
                }
            }
            else
            {
                // The simplest and easy way to display the entire buffer:
                //   UI::TextUnformatted(buf_begin, buf_end);
                // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
                // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
                // within the visible area.
                // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
                // on your side is recommended. Using uiListClipper requires
                // - A) random access into your data
                // - B) items all being the  same height,
                // both of which we can handle since we have an array pointing to the beginning of each line of text.
                // When using the filter (in the block of code above) we don't have random access into the data to display
                // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
                // it possible (and would be recommended if you want to search through tens of thousands of entries).
                uiListClipper clipper;
                clipper.Begin(LineOffsets.Size);
                while (clipper.Step())
                {
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                    {
                        const char* line_start = buf + LineOffsets[line_no];
                        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                        UI::TextUnformatted(line_start, line_end);
                    }
                }
                clipper.End();
            }
            UI::PopStyleVar();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (AutoScroll && UI::GetScrollY() >= UI::GetScrollMaxY())
                UI::SetScrollHereY(1.0f);
        }
        UI::EndChild();
        UI::End();
    }
};

// Demonstrate creating a simple log window with basic filtering.
static void ShowExampleAppLog(bool* p_open)
{
    static ExampleAppLog log;

    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    UI::SetNextWindowSize(vec2(500, 400), uiCond_FirstUseEver);
    UI::Begin("Example: Log", p_open);
    IMGUI_DEMO_MARKER("Examples/Log");
    if (UI::SmallButton("[Debug] Add 5 entries"))
    {
        static int counter = 0;
        const char* categories[3] = { "info", "warn", "error" };
        const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
        for (int n = 0; n < 5; n++)
        {
            const char* category = categories[counter % IM_COUNTOF(categories)];
            const char* word = words[counter % IM_COUNTOF(words)];
            log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                UI::GetFrameCount(), category, UI::GetTime(), word);
            counter++;
        }
    }
    UI::End();

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    log.Draw("Example: Log", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple Layout / ShowExampleAppLayout()
//-----------------------------------------------------------------------------

// Demonstrate create a window with multiple child windows.
static void ShowExampleAppLayout(bool* p_open)
{
    UI::SetNextWindowSize(vec2(500, 440), uiCond_FirstUseEver);
    if (UI::Begin("Example: Simple layout", p_open, uiWindowFlags_MenuBar))
    {
        IMGUI_DEMO_MARKER("Examples/Simple layout");
        if (UI::BeginMenuBar())
        {
            if (UI::BeginMenu("File"))
            {
                if (UI::MenuItem("Close", "Ctrl+W")) { *p_open = false; }
                UI::EndMenu();
            }
            UI::EndMenuBar();
        }

        // Left
        static int selected = 0;
        {
            UI::BeginChild("left pane", vec2(150, 0), uiChildFlags_Borders | uiChildFlags_ResizeX);
            for (int i = 0; i < 100; i++)
            {
                char label[128];
                sprintf(label, "MyObject %d", i);
                if (UI::Selectable(label, selected == i, uiSelectFlags_SelectOnNav))
                    selected = i;
            }
            UI::EndChild();
        }
        UI::SameLine();

        // Right
        {
            UI::BeginGroup();
            UI::BeginChild("item view", vec2(0, -UI::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            UI::Text("MyObject: %d", selected);
            UI::Barrier();
            if (UI::BeginTabBar("##Tabs", uiTabBarFlags_None))
            {
                if (UI::BeginTabItem("Description"))
                {
                    UI::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                    UI::EndTabItem();
                }
                if (UI::BeginTabItem("Details"))
                {
                    UI::Text("ID: 0123456789");
                    UI::EndTabItem();
                }
                UI::EndTabBar();
            }
            UI::EndChild();
            if (UI::Button("Revert")) {}
            UI::SameLine();
            if (UI::Button("Save")) {}
            UI::EndGroup();
        }
    }
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Property Editor / ShowExampleAppPropertyEditor()
//-----------------------------------------------------------------------------
// Some of the interactions are a bit lack-luster:
// - We would want pressing validating or leaving the filter to somehow restore focus.
// - We may want more advanced filtering (child nodes) and clipper support: both will need extra work.
// - We would want to customize some keyboard interactions to easily keyboard navigate between the tree and the properties.
//-----------------------------------------------------------------------------

struct ExampleAppPropertyEditor
{
    uiTextFilter     Filter;
    ExampleTreeNode*    SelectedNode = NULL;
    bool                UseClipper = false;

    void Draw(ExampleTreeNode* root_node)
    {
        IMGUI_DEMO_MARKER("Examples/Property editor");

        // Left side: draw tree
        // - Currently using a table to benefit from RowBg feature
        // - Our tree node are all of equal height, facilitating the use of a clipper.
        if (UI::BeginChild("##tree", vec2(300, 0), uiChildFlags_ResizeX | uiChildFlags_Borders | uiChildFlags_NavFlattened))
        {
            UI::PushItemFlag(uiItemFlags_NoNavDefaultFocus, true);
            UI::Checkbox("Use Clipper", &UseClipper);
            UI::SameLine();
            UI::Text("(%d root nodes)", root_node->Childs.Size);
            UI::SetNextItemWidth(-FLT_MIN);
            UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_F, uiInputFlags_Tooltip);
            if (UI::InputTextWithHint("##Filter", "incl,-excl", Filter.InputBuf, IM_COUNTOF(Filter.InputBuf), uiInputTextFlags_EscapeClearsAll))
                Filter.Build();
            UI::PopItemFlag();

            if (UI::BeginTable("##list", 1, uiTableFlags_RowBg))
            {
                if (UseClipper)
                    DrawClippedTree(root_node);
                else
                    DrawTree(root_node);
                UI::EndTable();
            }
        }
        UI::EndChild();

        // Right side: draw properties
        UI::SameLine();

        UI::BeginGroup(); // Lock X position
        if (ExampleTreeNode* node = SelectedNode)
        {
            UI::Text("%s", node->Name);
            UI::TextDisabled("UID: 0x%08X", node->UID);
            UI::Barrier();
            if (UI::BeginTable("##properties", 2, uiTableFlags_Resizable | uiTableFlags_ScrollY))
            {
                // Push object ID after we entered the table, so table is shared for all objects
                UI::PushID((int)node->UID);
                UI::TableSetupColumn("", uiTableColumnFlags_WidthFixed);
                UI::TableSetupColumn("", uiTableColumnFlags_WidthStretch, 2.0f); // Default twice larger
                if (node->HasData)
                {
                    // In a typical application, the structure description would be derived from a data-driven system.
                    // - We try to mimic this with our ExampleMemberInfo structure and the ExampleTreeNodeMemberInfos[] array.
                    // - Limits and some details are hard-coded to simplify the demo.
                    for (const ExampleMemberInfo& field_desc : ExampleTreeNodeMemberInfos)
                    {
                        UI::TableNextRow();
                        UI::PushID(field_desc.Name);
                        UI::TableNextColumn();
                        UI::AlignTextToFramePadding();
                        UI::TextUnformatted(field_desc.Name);
                        UI::TableNextColumn();
                        void* field_ptr = (void*)(((unsigned char*)node) + field_desc.Offset);
                        switch (field_desc.DataType)
                        {
                        case uiDataType_Bool:
                        {
                            IM_ASSERT(field_desc.DataCount == 1);
                            UI::Checkbox("##Editor", (bool*)field_ptr);
                            break;
                        }
                        case uiDataType_S32:
                        {
                            int v_min = INT_MIN, v_max = INT_MAX;
                            UI::SetNextItemWidth(-FLT_MIN);
                            UI::DragScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, 1.0f, &v_min, &v_max);
                            break;
                        }
                        case uiDataType_Float:
                        {
                            float v_min = 0.0f, v_max = 1.0f;
                            UI::SetNextItemWidth(-FLT_MIN);
                            UI::SliderScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, &v_min, &v_max);
                            break;
                        }
                        case uiDataType_String:
                        {
                            UI::InputText("##Editor", reinterpret_cast<char*>(field_ptr), 28);
                            break;
                        }
                        }
                        UI::PopID();
                    }
                }
                UI::PopID();
                UI::EndTable();
            }
        }
        UI::EndGroup();
    }

    // Custom search filter
    // - Here we apply on root node only.
    // - This does a case insensitive stristr which is pretty heavy. In a real large-scale app you would likely store a filtered list which in turns would be trivial to linearize.
    inline bool IsNodePassingFilter(ExampleTreeNode* node)
    {
        return node->Parent->Parent != NULL || Filter.PassFilter(node->Name);
    }

    // Basic version, recursive. This is how you would generally draw a tree.
    // - Simple but going to be noticeably costly if you have a large amount of nodes as DrawTreeNode() is called for all of them.
    // - On my desktop PC (2020), for 10K nodes in an optimized build this takes ~1.2 ms
    // - Unlike arrays or grids which are very easy to clip, trees are currently more difficult to clip.
    void DrawTree(ExampleTreeNode* node)
    {
        for (ExampleTreeNode* child : node->Childs)
            if (IsNodePassingFilter(child) && DrawTreeNode(child))
            {
                DrawTree(child);
                UI::TreePop();
            }
    }

    // More advanced version. Use a alternative clipping technique: fast-forwarding through non-visible chunks.
    // - On my desktop PC (2020), for 10K nodes in an optimized build this takes ~0.1 ms
    //   (in ExampleTree_CreateDemoTree(), change 'int ROOT_ITEMS_COUNT = 10000' to try with this amount of root nodes).
    // - 1. Use clipper with indeterminate count (items_count = INT_MAX): we need to call SeekCursorForItem() at the end once we know the count.
    // - 2. Use SetNextItemStorageID() to specify ID used for open/close storage, making it easy to call TreeNodeGetOpen() on any arbitrary node.
    // - 3. Linearize tree during traversal: our tree data structure makes it easy to access sibling and parents.
    // - Unlike clipping for a regular array or grid which may be done using random access limited to visible areas,
    //   this technique requires traversing most accessible nodes. This could be made more optimal with extra work,
    //   but this is a decent simplicity<>speed trade-off.
    // See https://github.com/ocornut/imgui/issues/3823 for discussions about this.
    void DrawClippedTree(ExampleTreeNode* root_node)
    {
        ExampleTreeNode* node = root_node->Childs[0]; // First node
        uiListClipper clipper;
        clipper.Begin(INT_MAX);
        while (clipper.Step())
            while (clipper.UserIndex < clipper.DisplayEnd && node != NULL)
                node = DrawClippedTreeNodeAndAdvanceToNext(&clipper, node);

        // Keep going to count nodes and submit final count so we have a reliable scrollbar.
        // - One could consider caching this value and only refreshing it occasionally e.g. window is focused and an action occurs.
        // - Incorrect but cheap approximation would be to use 'clipper_current_idx = IM_MAX(clipper_current_idx, root_node->Childs.Size)' instead.
        // - If either of those is implemented, the general cost will approach zero when scrolling is at the top of the tree.
        while (node != NULL)
            node = DrawClippedTreeNodeAndAdvanceToNext(&clipper, node);
        //clipper.UserIndex = IM_MAX(clipper.UserIndex, root_node->Childs.Size); // <-- Cheap approximation instead of while() loop above.
        clipper.SeekCursorForItem(clipper.UserIndex);
    }

    ExampleTreeNode* DrawClippedTreeNodeAndAdvanceToNext(uiListClipper* clipper, ExampleTreeNode* node)
    {
        if (IsNodePassingFilter(node))
        {
            // Draw node if within visible range
            bool is_open = false;
            if (clipper->UserIndex >= clipper->DisplayStart && clipper->UserIndex < clipper->DisplayEnd)
            {
                is_open = DrawTreeNode(node);
            }
            else
            {
                is_open = (node->Childs.Size > 0 && UI::TreeNodeGetOpen((uiID)node->UID));
                if (is_open)
                    UI::TreePush(node->Name);
            }
            clipper->UserIndex++;

            // Next node: recurse into childs
            if (is_open)
                return node->Childs[0];
        }

        // Next node: next sibling, otherwise move back to parent
        while (node != NULL)
        {
            if (node->IndexInParent + 1 < node->Parent->Childs.Size)
                return node->Parent->Childs[node->IndexInParent + 1];
            node = node->Parent;
            if (node->Parent == NULL)
                break;
            UI::TreePop();
        }
        return NULL;
    }

    // To support node with same name we incorporate node->UID into the item ID.
    // (this would more naturally be done using PushID(node->UID) + TreeNodeEx(node->Name, tree_flags),
    //   but it would require in DrawClippedTreeNodeAndAdvanceToNext() to add PushID() before TreePush(), and PopID() after TreePop(),
    //   so instead we use TreeNodeEx(node->UID, tree_flags, "%s", node->Name) here)
    bool DrawTreeNode(ExampleTreeNode* node)
    {
        UI::TableNextRow();
        UI::TableNextColumn();
        uiTreeFlags tree_flags = uiTreeFlags_None;
        tree_flags |= uiTreeFlags_OpenOnArrow | uiTreeFlags_OpenOnDoubleClick; // Standard opening mode as we are likely to want to add selection afterwards
        tree_flags |= uiTreeFlags_NavLeftJumpsToParent;  // Left arrow support
        tree_flags |= uiTreeFlags_SpanFullWidth;         // Span full width for easier mouse reach
        tree_flags |= uiTreeFlags_DrawLinesToNodes;      // Always draw hierarchy outlines
        if (node == SelectedNode)
            tree_flags |= uiTreeFlags_Selected;          // Draw selection highlight
        if (node->Childs.Size == 0)
            tree_flags |= uiTreeFlags_Leaf | uiTreeFlags_Bullet | uiTreeFlags_NoTreePushOnOpen; // Use _NoTreePushOnOpen + set is_open=false to avoid unnecessarily push/pop on leaves.
        if (node->DataMyBool == false)
            UI::PushStyleColor(uiCol_Text, UI::GetStyle().Colors[uiCol_TextDisabled]);
        UI::SetNextItemStorageID((uiID)node->UID);        // Use node->UID as storage id
        bool is_open = UI::TreeNodeEx((void*)(intptr_t)node->UID, tree_flags, "%s", node->Name);
        if (node->Childs.Size == 0)
            is_open = false;
        if (node->DataMyBool == false)
            UI::PopStyleColor();
        if (UI::IsItemFocused())
            SelectedNode = node;
        return is_open;
    }
};

// Demonstrate creating a simple property editor.
static void ShowExampleAppPropertyEditor(bool* p_open, uiDemoWindowData* demo_data)
{
    UI::SetNextWindowSize(vec2(430, 450), uiCond_FirstUseEver);
    if (!UI::Begin("Example: Property editor", p_open))
    {
        UI::End();
        return;
    }

    IMGUI_DEMO_MARKER("Examples/Property Editor");
    static ExampleAppPropertyEditor property_editor;
    if (demo_data->DemoTree == NULL)
        demo_data->DemoTree = ExampleTree_CreateDemoTree();
    property_editor.Draw(demo_data->DemoTree);

    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Long Text / ShowExampleAppLongText()
//-----------------------------------------------------------------------------

// Demonstrate/test rendering huge amount of text, and the incidence of clipping.
static void ShowExampleAppLongText(bool* p_open)
{
    UI::SetNextWindowSize(vec2(520, 600), uiCond_FirstUseEver);
    if (!UI::Begin("Example: Long text display", p_open))
    {
        UI::End();
        return;
    }
    IMGUI_DEMO_MARKER("Examples/Long text display");

    static int test_type = 0;
    static uiTextBuffer log;
    static int lines = 0;
    UI::Text("Printing unusually long amount of text.");
    UI::Combo("Test type", &test_type,
        "Single call to TextUnformatted()\0"
        "Multiple calls to Text(), clipped\0"
        "Multiple calls to Text(), not clipped (slow)\0");
    UI::Text("Buffer contents: %d lines, %d bytes", lines, log.size());
    if (UI::Button("Clear")) { log.clear(); lines = 0; }
    UI::SameLine();
    if (UI::Button("Add 1000 lines"))
    {
        for (int i = 0; i < 1000; i++)
            log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines + i);
        lines += 1000;
    }
    UI::BeginChild("Log");
    switch (test_type)
    {
    case 0:
        // Single call to TextUnformatted() with a big buffer
        UI::TextUnformatted(log.begin(), log.end());
        break;
    case 1:
        {
            // Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the uiListClipper helper.
            UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(0, 0));
            uiListClipper clipper;
            clipper.Begin(lines);
            while (clipper.Step())
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                    UI::Text("%i The quick brown fox jumps over the lazy dog", i);
            UI::PopStyleVar();
            break;
        }
    case 2:
        // Multiple calls to Text(), not clipped (slow)
        UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(0, 0));
        for (int i = 0; i < lines; i++)
            UI::Text("%i The quick brown fox jumps over the lazy dog", i);
        UI::PopStyleVar();
        break;
    }
    UI::EndChild();
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Auto Resize / ShowExampleAppAutoResize()
//-----------------------------------------------------------------------------

// Demonstrate creating a window which gets auto-resized according to its content.
static void ShowExampleAppAutoResize(bool* p_open)
{
    if (!UI::Begin("Example: Auto-resizing window", p_open, uiWindowFlags_AutoResize))
    {
        UI::End();
        return;
    }
    IMGUI_DEMO_MARKER("Examples/Auto-resizing window");

    static int lines = 10;
    UI::TextUnformatted(
        "Window will resize every-frame to the size of its content.\n"
        "Note that you probably don't want to query the window size to\n"
        "output your content because that would create a feedback loop.");
    UI::SliderInt("Number of lines", &lines, 1, 20);
    for (int i = 0; i < lines; i++)
        UI::Text("%*sThis is line %d", i * 4, "", i); // Pad with space to extend size horizontally
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Constrained Resize / ShowExampleAppConstrainedResize()
//-----------------------------------------------------------------------------

// Demonstrate creating a window with custom resize constraints.
// Note that size constraints currently don't work on a docked window (when in 'docking' branch)
static void ShowExampleAppConstrainedResize(bool* p_open)
{
    struct CustomConstraints
    {
        // Helper functions to demonstrate programmatic constraints
        // FIXME: This doesn't take account of decoration size (e.g. title bar), library should make this easier.
        // FIXME: None of the three demos works consistently when resizing from borders.
        static void AspectRatio(uiSizeCallbackData* data)
        {
            float aspect_ratio = *(float*)data->UserData;
            data->DesiredSize.y = (float)(int)(data->DesiredSize.x / aspect_ratio);
        }
        static void Square(uiSizeCallbackData* data)
        {
            data->DesiredSize.x = data->DesiredSize.y = IM_MAX(data->DesiredSize.x, data->DesiredSize.y);
        }
        static void Step(uiSizeCallbackData* data)
        {
            float step = *(float*)data->UserData;
            data->DesiredSize = vec2((int)(data->DesiredSize.x / step + 0.5f) * step, (int)(data->DesiredSize.y / step + 0.5f) * step);
        }
    };

    const char* test_desc[] =
    {
        "Between 100x100 and 500x500",
        "At least 100x100",
        "Resize vertical + lock current width",
        "Resize horizontal + lock current height",
        "Width Between 400 and 500",
        "Height at least 400",
        "Custom: Aspect Ratio 16:9",
        "Custom: Always Square",
        "Custom: Fixed Steps (100)",
    };

    // Options
    static bool auto_resize = false;
    static bool window_padding = true;
    static int type = 6; // Aspect Ratio
    static int display_lines = 10;

    // Submit constraint
    float aspect_ratio = 16.0f / 9.0f;
    float fixed_step = 100.0f;
    if (type == 0) UI::SetNextWindowSizeConstraints(vec2(100, 100), vec2(500, 500));         // Between 100x100 and 500x500
    if (type == 1) UI::SetNextWindowSizeConstraints(vec2(100, 100), vec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
    if (type == 2) UI::SetNextWindowSizeConstraints(vec2(-1, 0),    vec2(-1, FLT_MAX));      // Resize vertical + lock current width
    if (type == 3) UI::SetNextWindowSizeConstraints(vec2(0, -1),    vec2(FLT_MAX, -1));      // Resize horizontal + lock current height
    if (type == 4) UI::SetNextWindowSizeConstraints(vec2(400, -1),  vec2(500, -1));          // Width Between and 400 and 500
    if (type == 5) UI::SetNextWindowSizeConstraints(vec2(-1, 400),  vec2(-1, FLT_MAX));      // Height at least 400
    if (type == 6) UI::SetNextWindowSizeConstraints(vec2(0, 0),     vec2(FLT_MAX, FLT_MAX), CustomConstraints::AspectRatio, (void*)&aspect_ratio);   // Aspect ratio
    if (type == 7) UI::SetNextWindowSizeConstraints(vec2(0, 0),     vec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);                              // Always Square
    if (type == 8) UI::SetNextWindowSizeConstraints(vec2(0, 0),     vec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)&fixed_step);            // Fixed Step

    // Submit window
    if (!window_padding)
        UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0.0f, 0.0f));
    const uiWindowFlags window_flags = auto_resize ? uiWindowFlags_AutoResize : 0;
    const bool window_open = UI::Begin("Example: Constrained Resize", p_open, window_flags);
    if (!window_padding)
        UI::PopStyleVar();
    IMGUI_DEMO_MARKER("Examples/Constrained Resizing window");
    if (window_open)
    {
        if (UI::GetIO().KeyShift)
        {
            // Display a dummy viewport (in your real app you would likely use ImageButton() to display a texture)
            vec2 avail_size = UI::GetContentRegionAvail();
            vec2 pos = UI::GetCursorScreenPos();
            UI::ColorButton("viewport", vec4(0.5f, 0.2f, 0.5f, 1.0f), uiColorEditFlags_NoTooltip | uiColorEditFlags_NoDragDrop, avail_size);
            UI::SetCursorScreenPos(vec2(pos.x + 10, pos.y + 10));
            UI::Text("%.2f x %.2f", avail_size.x, avail_size.y);
        }
        else
        {
            UI::Text("(Hold Shift to display a dummy viewport)");
            if (UI::IsWindowDocked())
                UI::Text("Warning: Sizing Constraints won't work if the window is docked!");
            if (UI::Button("Set 200x200")) { UI::SetWindowSize(vec2(200, 200)); } UI::SameLine();
            if (UI::Button("Set 500x500")) { UI::SetWindowSize(vec2(500, 500)); } UI::SameLine();
            if (UI::Button("Set 800x200")) { UI::SetWindowSize(vec2(800, 200)); }
            UI::SetNextItemWidth(UI::GetFontSize() * 20);
            UI::Combo("Constraint", &type, test_desc, IM_COUNTOF(test_desc));
            UI::SetNextItemWidth(UI::GetFontSize() * 20);
            UI::DragInt("Lines", &display_lines, 0.2f, 1, 100);
            UI::Checkbox("Auto-resize", &auto_resize);
            UI::Checkbox("Window padding", &window_padding);
            for (int i = 0; i < display_lines; i++)
                UI::Text("%*sHello, sailor! Making this line long enough for the example.", i * 4, "");
        }
    }
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple overlay / ShowExampleAppSimpleOverlay()
//-----------------------------------------------------------------------------
// Demonstrate creating a simple static window with no decoration
// + a context-menu to choose which corner of the screen to use.
static void ShowExampleAppSimpleOverlay(bool* p_open) {
    static int location = 0;
    uiIO& io = UI::GetIO();
    uiWindowFlags window_flags = uiWindowFlags_NoDecoration | uiWindowFlags_NoDocking | uiWindowFlags_AutoResize | uiWindowFlags_NoSavedSettings | uiWindowFlags_NoFocusOnAppearing | uiWindowFlags_NoNav;
    if (location >= 0) {
        const float PAD = 10.0f;
        const uiViewport* viewport = UI::GetMainViewport();
        vec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        vec2 work_size = viewport->WorkSize;
        vec2 window_pos, window_pos_pivot;
        window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
        UI::SetNextWindowPos(window_pos, uiCond_Always, window_pos_pivot);
        UI::SetNextWindowViewport(viewport->ID);
        window_flags |= uiWindowFlags_NoMove;
    } else if (location == -2) {
        // Center window
        UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Always, vec2(0.5f, 0.5f));
        window_flags |= uiWindowFlags_NoMove;
    }
    UI::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (UI::Begin("Example: Simple overlay", p_open, window_flags)) {
        IMGUI_DEMO_MARKER("Examples/Simple overlay"); // Scroll up to the beginning of this function to see overlay flags
        UI::Text("Simple overlay\n" "(right-click to change position)");
        UI::Barrier();
        if (UI::IsMousePosValid())
            UI::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        else
            UI::Text("Mouse Position: <invalid>");
        if (UI::BeginPopupContextWindow()) {
            if (UI::MenuItem("Custom",       NULL, location == -1)) location = -1;
            if (UI::MenuItem("Center",       NULL, location == -2)) location = -2;
            if (UI::MenuItem("Top-left",     NULL, location == 0)) location = 0;
            if (UI::MenuItem("Top-right",    NULL, location == 1)) location = 1;
            if (UI::MenuItem("Bottom-left",  NULL, location == 2)) location = 2;
            if (UI::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
            if (p_open && UI::MenuItem("Close")) *p_open = false;
            UI::EndPopup();
        }
    }
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Manipulating Window Titles / ShowExampleAppWindowTitles()
//-----------------------------------------------------------------------------

// Demonstrate the use of "##" and "###" in identifiers to manipulate ID generation.
// This applies to all regular items as well.
// Read FAQ section "How can I have multiple widgets with the same label?" for details.
static void ShowExampleAppWindowTitles(bool*)
{
    const uiViewport* viewport = UI::GetMainViewport();
    const vec2 base_pos = viewport->Pos;

    // By default, Windows are uniquely identified by their title.
    // You can use the "##" and "###" markers to manipulate the display/ID.

    // Using "##" to display same title but have unique identifier.
    UI::SetNextWindowPos(vec2(base_pos.x + 100, base_pos.y + 100), uiCond_FirstUseEver);
    UI::Begin("Same title as another window##1");
    IMGUI_DEMO_MARKER("Examples/Manipulating window titles##1");
    UI::Text("This is window 1.\nMy title is the same as window 2, but my identifier is unique.");
    UI::End();

    UI::SetNextWindowPos(vec2(base_pos.x + 100, base_pos.y + 200), uiCond_FirstUseEver);
    UI::Begin("Same title as another window##2");
    IMGUI_DEMO_MARKER("Examples/Manipulating window titles##2");
    UI::Text("This is window 2.\nMy title is the same as window 1, but my identifier is unique.");
    UI::End();

    // Using "###" to display a changing title but keep a static identifier "AnimatedTitle"
    char buf[128];
    sprintf(buf, "Animated title %c %d###AnimatedTitle", "|/-\\"[(int)(UI::GetTime() / 0.25f) & 3], UI::GetFrameCount());
    UI::SetNextWindowPos(vec2(base_pos.x + 100, base_pos.y + 300), uiCond_FirstUseEver);
    UI::Begin(buf);
    IMGUI_DEMO_MARKER("Examples/Manipulating window titles##3");
    UI::Text("This window has a changing title.");
    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Custom Rendering using ImDrawList API / ShowExampleAppCustomRendering()
//-----------------------------------------------------------------------------

// Add a |_| looking shape
static void PathConcaveShape(ImDrawList* draw_list, float x, float y, float sz)
{
    const vec2 pos_norms[] = { { 0.0f, 0.0f }, { 0.3f, 0.0f }, { 0.3f, 0.7f }, { 0.7f, 0.7f }, { 0.7f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    for (const vec2& p : pos_norms)
        draw_list->PathLineTo(vec2(x + 0.5f + (int)(sz * p.x), y + 0.5f + (int)(sz * p.y)));
}

// Demonstrate using the low-level ImDrawList to draw custom shapes.
static void ShowExampleAppCustomRendering(bool* p_open)
{
    if (!UI::Begin("Example: Custom rendering", p_open))
    {
        UI::End();
        return;
    }
    IMGUI_DEMO_MARKER("Examples/Custom rendering");

    // Tip: If you do a lot of custom rendering, you probably want to use your own geometrical types and benefit of
    // overloaded operators, etc. Define IM_VEC2_CLASS_EXTRA in imconfig.h to create implicit conversions between your
    // types and vec2/vec4. Dear ImGui defines overloaded operators but they are internal to imgui.cpp and not
    // exposed outside (to avoid messing with your types) In this example we are not using the maths operators!

    if (UI::BeginTabBar("##TabBar"))
    {
        if (UI::BeginTabItem("Primitives"))
        {
            IMGUI_DEMO_MARKER("Examples/Custom rendering/Primitives");
            UI::PushItemWidth(-UI::GetFontSize() * 15);
            ImDrawList* draw_list = UI::GetWindowDrawList();

            // Draw gradients
            // (note that those are currently exacerbating our sRGB/Linear issues)
            // Calling UI::GetColorU32() multiplies the given colors by the current Style Alpha, but you may pass the IM_COL32() directly as well..
            UI::Text("Gradients");
            vec2 gradient_size = vec2(UI::CalcItemWidth(), UI::GetFrameHeight());
            {
                vec2 p0 = UI::GetCursorScreenPos();
                vec2 p1 = vec2(p0.x + gradient_size.x, p0.y + gradient_size.y);
                ImU32 col_a = UI::GetColorU32(IM_COL32(0, 0, 0, 255));
                ImU32 col_b = UI::GetColorU32(IM_COL32(255, 255, 255, 255));
                draw_list->AddRectFilledMultiColor(p0, p1, col_a, col_b, col_b, col_a);
                UI::InvisibleButton("##gradient1", gradient_size);
            }
            {
                vec2 p0 = UI::GetCursorScreenPos();
                vec2 p1 = vec2(p0.x + gradient_size.x, p0.y + gradient_size.y);
                ImU32 col_a = UI::GetColorU32(IM_COL32(0, 255, 0, 255));
                ImU32 col_b = UI::GetColorU32(IM_COL32(255, 0, 0, 255));
                draw_list->AddRectFilledMultiColor(p0, p1, col_a, col_b, col_b, col_a);
                UI::InvisibleButton("##gradient2", gradient_size);
            }

            // Draw a bunch of primitives
            UI::Text("All primitives");
            static float sz = 36.0f;
            static float thickness = 3.0f;
            static int ngon_sides = 6;
            static bool circle_segments_override = false;
            static int circle_segments_override_v = 12;
            static bool curve_segments_override = false;
            static int curve_segments_override_v = 8;
            static vec4 colf = vec4(1.0f, 1.0f, 0.4f, 1.0f);
            UI::DragFloat("Size", &sz, 0.2f, 2.0f, 100.0f, "%.0f");
            UI::DragFloat("Thickness", &thickness, 0.05f, 1.0f, 8.0f, "%.02f");
            UI::SliderInt("N-gon sides", &ngon_sides, 3, 12);
            UI::Checkbox("##circlesegmentoverride", &circle_segments_override);
            UI::SameLine(0.0f, UI::GetStyle().ItemInnerSpacing.x);
            circle_segments_override |= UI::SliderInt("Circle segments override", &circle_segments_override_v, 3, 40);
            UI::Checkbox("##curvessegmentoverride", &curve_segments_override);
            UI::SameLine(0.0f, UI::GetStyle().ItemInnerSpacing.x);
            curve_segments_override |= UI::SliderInt("Curves segments override", &curve_segments_override_v, 3, 40);
            UI::ColorEdit4("Color", &colf.x);

            const vec2 p = UI::GetCursorScreenPos();
            const ImU32 col = ImColor(colf);
            const float spacing = 10.0f;
            const ImDrawFlags corners_tl_br = ImDrawFlags_RoundTopLeft | ImDrawFlags_RoundBottomRight;
            const float rounding = sz / 5.0f;
            const int circle_segments = circle_segments_override ? circle_segments_override_v : 0;
            const int curve_segments = curve_segments_override ? curve_segments_override_v : 0;
            const vec2 cp3[3] = { vec2(0.0f, sz * 0.6f), vec2(sz * 0.5f, -sz * 0.4f), vec2(sz, sz) }; // Control points for curves
            const vec2 cp4[4] = { vec2(0.0f, 0.0f), vec2(sz * 1.3f, sz * 0.3f), vec2(sz - sz * 1.3f, sz - sz * 0.3f), vec2(sz, sz) };

            float x = p.x + 4.0f;
            float y = p.y + 4.0f;
            for (int n = 0; n < 2; n++)
            {
                // First line uses a thickness of 1.0f, second line uses the configurable thickness
                float th = (n == 0) ? 1.0f : thickness;
                draw_list->AddNgon(vec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, col, ngon_sides, th);                 x += sz + spacing;  // N-gon
                draw_list->AddCircle(vec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, col, circle_segments, th);          x += sz + spacing;  // Circle
                draw_list->AddEllipse(vec2(x + sz*0.5f, y + sz*0.5f), vec2(sz*0.5f, sz*0.3f), col, -0.3f, circle_segments, th); x += sz + spacing;  // Ellipse
                draw_list->AddRect(vec2(x, y), vec2(x + sz, y + sz), col, 0.0f, th);                            x += sz + spacing;  // Square
                draw_list->AddRect(vec2(x, y), vec2(x + sz, y + sz), col, rounding, th);                        x += sz + spacing;  // Square with all rounded corners
                draw_list->AddRect(vec2(x, y), vec2(x + sz, y + sz), col, rounding, th, corners_tl_br);         x += sz + spacing;  // Square with two rounded corners
                draw_list->AddTriangle(vec2(x+sz*0.5f,y), vec2(x+sz, y+sz-0.5f), vec2(x, y+sz-0.5f), col, th);x += sz + spacing;  // Triangle
                //draw_list->AddTriangle(vec2(x+sz*0.2f,y), vec2(x, y+sz-0.5f), vec2(x+sz*0.4f, y+sz-0.5f), col, th);x+= sz*0.4f + spacing; // Thin triangle
                PathConcaveShape(draw_list, x, y, sz); draw_list->PathStroke(col, th, ImDrawFlags_Closed);          x += sz + spacing;  // Concave Shape
                //draw_list->AddPolyline(concave_shape, IM_COUNTOF(concave_shape), col, ImDrawFlags_Closed, th);
                draw_list->AddLineH(x, x + sz, y, col, th);                                                         x += sz + spacing;  // Horizontal line (note: drawing a filled rectangle will be faster!)
                draw_list->AddLineV(x, y, y + sz, col, th);                                                         x += spacing;       // Vertical line (note: drawing a filled rectangle will be faster!)
                draw_list->AddLine(vec2(x, y), vec2(x + sz, y + sz), col, th);                                  x += sz + spacing;  // Diagonal line

                // Path
                draw_list->PathArcTo(vec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, 3.141592f, 3.141592f * -0.5f);
                draw_list->PathStroke(col, th);
                x += sz + spacing;

                // Quadratic Bezier Curve (3 control points)
                draw_list->AddBezierQuadratic(vec2(x + cp3[0].x, y + cp3[0].y), vec2(x + cp3[1].x, y + cp3[1].y), vec2(x + cp3[2].x, y + cp3[2].y), col, th, curve_segments);
                x += sz + spacing;

                // Cubic Bezier Curve (4 control points)
                draw_list->AddBezierCubic(vec2(x + cp4[0].x, y + cp4[0].y), vec2(x + cp4[1].x, y + cp4[1].y), vec2(x + cp4[2].x, y + cp4[2].y), vec2(x + cp4[3].x, y + cp4[3].y), col, th, curve_segments);

                x = p.x + 4;
                y += sz + spacing;
            }

            // Filled shapes
            draw_list->AddNgonFilled(vec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col, ngon_sides);             x += sz + spacing;  // N-gon
            draw_list->AddCircleFilled(vec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col, circle_segments);      x += sz + spacing;  // Circle
            draw_list->AddEllipseFilled(vec2(x + sz * 0.5f, y + sz * 0.5f), vec2(sz * 0.5f, sz * 0.3f), col, -0.3f, circle_segments); x += sz + spacing;// Ellipse
            draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + sz), col);                                    x += sz + spacing;  // Square
            draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + sz), col, 10.0f);                             x += sz + spacing;  // Square with all rounded corners
            draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + sz), col, 10.0f, corners_tl_br);              x += sz + spacing;  // Square with two rounded corners
            draw_list->AddTriangleFilled(vec2(x+sz*0.5f,y), vec2(x+sz, y+sz-0.5f), vec2(x, y+sz-0.5f), col);  x += sz + spacing;  // Triangle
            //draw_list->AddTriangleFilled(vec2(x+sz*0.2f,y), vec2(x, y+sz-0.5f), vec2(x+sz*0.4f, y+sz-0.5f), col); x += sz*0.4f + spacing; // Thin triangle
            PathConcaveShape(draw_list, x, y, sz); draw_list->PathFillConcave(col);                                 x += sz + spacing;  // Concave shape
            draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + thickness), col);                             x += sz + spacing;  // Horizontal line (faster than AddLine, but only handle integer thickness)
            draw_list->AddRectFilled(vec2(x, y), vec2(x + thickness, y + sz), col);                             x += spacing * 2.0f;// Vertical line (faster than AddLine, but only handle integer thickness)
            draw_list->AddRectFilled(vec2(x, y), vec2(x + 1, y + 1), col);                                      x += sz;            // Pixel (faster than AddLine)

            // Path
            draw_list->PathArcTo(vec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, 3.141592f * -0.5f, 3.141592f);
            draw_list->PathFillConvex(col);
            x += sz + spacing;

            // Quadratic Bezier Curve (3 control points)
            draw_list->PathLineTo(vec2(x + cp3[0].x, y + cp3[0].y));
            draw_list->PathBezierQuadraticCurveTo(vec2(x + cp3[1].x, y + cp3[1].y), vec2(x + cp3[2].x, y + cp3[2].y), curve_segments);
            draw_list->PathFillConvex(col);
            x += sz + spacing;

            draw_list->AddRectFilledMultiColor(vec2(x, y), vec2(x + sz, y + sz), IM_COL32(0, 0, 0, 255), IM_COL32(255, 0, 0, 255), IM_COL32(255, 255, 0, 255), IM_COL32(0, 255, 0, 255));
            x += sz + spacing;

            UI::Dummy(vec2((sz + spacing) * 13.2f, (sz + spacing) * 3.0f));
            UI::PopItemWidth();
            UI::EndTabItem();
        }

        if (UI::BeginTabItem("Canvas"))
        {
            IMGUI_DEMO_MARKER("Examples/Custom rendering/Canvas");
            static ImVector<vec2> points;
            static vec2 scrolling(0.0f, 0.0f);
            static bool opt_enable_grid = true;
            static bool opt_enable_context_menu = true;
            static bool adding_line = false;

            UI::Checkbox("Enable grid", &opt_enable_grid);
            UI::Checkbox("Enable context menu", &opt_enable_context_menu);
            UI::Text("Mouse Left: drag to add lines,\nMouse Right: drag to scroll, click for context menu.");

            // Typically you would use a BeginChild()/EndChild() pair to benefit from a clipping region + own scrolling.
            // Here we demonstrate that this can be replaced by simple offsetting + custom drawing + PushClipRect/PopClipRect() calls.
            // To use a child window instead we could use, e.g:
            //      UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0, 0));      // Disable padding
            //      UI::PushStyleColor(uiCol_ChildBg, IM_COL32(50, 50, 50, 255));  // Set a background color
            //      UI::BeginChild("canvas", vec2(0.0f, 0.0f), uiChildFlags_Borders, uiWindowFlags_NoMove);
            //      UI::PopStyleColor();
            //      UI::PopStyleVar();
            //      [...]
            //      UI::EndChild();

            // Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
            vec2 canvas_p0 = UI::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
            vec2 canvas_sz = UI::GetContentRegionAvail();   // Resize canvas to what's available
            if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
            if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
            vec2 canvas_p1 = vec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

            // Draw border and background color
            uiIO& io = UI::GetIO();
            ImDrawList* draw_list = UI::GetWindowDrawList();
            draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
            draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

            // This will catch our interactions
            UI::InvisibleButton("canvas", canvas_sz, uiButtonFlags_MouseButtonLeft | uiButtonFlags_MouseButtonRight);
            const bool is_hovered = UI::IsItemHovered(); // Hovered
            const bool is_active = UI::IsItemActive();   // Held
            const vec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
            const vec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

            // Add first and second point
            if (is_hovered && !adding_line && UI::IsMouseClicked(uiMouseButton_Left))
            {
                points.push_back(mouse_pos_in_canvas);
                points.push_back(mouse_pos_in_canvas);
                adding_line = true;
            }
            if (adding_line)
            {
                points.back() = mouse_pos_in_canvas;
                if (!UI::IsMouseDown(uiMouseButton_Left))
                    adding_line = false;
            }

            // Pan (we use a zero mouse threshold when there's no context menu)
            // You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
            const float mouse_threshold_for_pan = opt_enable_context_menu ? -1.0f : 0.0f;
            if (is_active && UI::IsMouseDragging(uiMouseButton_Right, mouse_threshold_for_pan))
            {
                scrolling.x += io.MouseDelta.x;
                scrolling.y += io.MouseDelta.y;
            }

            // Context menu (under default mouse threshold)
            vec2 drag_delta = UI::GetMouseDragDelta(uiMouseButton_Right);
            if (opt_enable_context_menu && drag_delta.x == 0.0f && drag_delta.y == 0.0f)
                UI::OpenPopupOnItemClick("context", uiPopupFlags_MouseButtonRight);
            if (UI::BeginPopup("context"))
            {
                if (adding_line)
                    points.resize(points.size() - 2);
                adding_line = false;
                if (UI::MenuItem("Remove one", NULL, false, points.Size > 0)) { points.resize(points.size() - 2); }
                if (UI::MenuItem("Remove all", NULL, false, points.Size > 0)) { points.clear(); }
                UI::EndPopup();
            }

            // Draw grid + all lines in the canvas
            draw_list->PushClipRect(canvas_p0, canvas_p1, true);
            if (opt_enable_grid)
            {
                const float GRID_STEP = 64.0f;
                for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                    draw_list->AddLineV(canvas_p0.x + x, canvas_p0.y, canvas_p1.y, IM_COL32(200, 200, 200, 40));
                for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                    draw_list->AddLineH(canvas_p0.x, canvas_p1.x, canvas_p0.y + y, IM_COL32(200, 200, 200, 40));
            }
            for (int n = 0; n < points.Size; n += 2)
                draw_list->AddLine(vec2(origin.x + points[n].x, origin.y + points[n].y), vec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
            draw_list->PopClipRect();

            UI::EndTabItem();
        }

        if (UI::BeginTabItem("BG/FG draw lists"))
        {
            IMGUI_DEMO_MARKER("Examples/Custom rendering/BG & FG draw lists");
            static bool draw_bg = true;
            static bool draw_fg = true;
            UI::Checkbox("Draw in Background draw list", &draw_bg);
            UI::SameLine(); HelpMarker("The Background draw list will be rendered below every Dear ImGui windows.");
            UI::Checkbox("Draw in Foreground draw list", &draw_fg);
            UI::SameLine(); HelpMarker("The Foreground draw list will be rendered over every Dear ImGui windows.");
            vec2 window_pos = UI::GetWindowPos();
            vec2 window_size = UI::GetWindowSize();
            vec2 window_center = vec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);
            if (draw_bg)
                UI::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 0, 10 + 4);
            if (draw_fg)
                UI::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 0, 10);
            UI::EndTabItem();
        }

        // Demonstrate out-of-order rendering via channels splitting
        // We use functions in ImDrawList as each draw list contains a convenience splitter,
        // but you can also instantiate your own ImDrawListSplitter if you need to nest them.
        if (UI::BeginTabItem("Draw Channels"))
        {
            IMGUI_DEMO_MARKER("Examples/Custom rendering/Draw Channels");
            ImDrawList* draw_list = UI::GetWindowDrawList();
            {
                UI::Text("Blue shape is drawn first: appears in back");
                UI::Text("Red shape is drawn after: appears in front");
                vec2 p0 = UI::GetCursorScreenPos();
                draw_list->AddRectFilled(vec2(p0.x, p0.y), vec2(p0.x + 50, p0.y + 50), IM_COL32(0, 0, 255, 255)); // Blue
                draw_list->AddRectFilled(vec2(p0.x + 25, p0.y + 25), vec2(p0.x + 75, p0.y + 75), IM_COL32(255, 0, 0, 255)); // Red
                UI::Dummy(vec2(75, 75));
            }
            UI::Barrier();
            {
                UI::Text("Blue shape is drawn first, into channel 1: appears in front");
                UI::Text("Red shape is drawn after, into channel 0: appears in back");
                vec2 p1 = UI::GetCursorScreenPos();

                // Create 2 channels and draw a Blue shape THEN a Red shape.
                // You can create any number of channels. Tables API use 1 channel per column in order to better batch draw calls.
                draw_list->ChannelsSplit(2);
                draw_list->ChannelsSetCurrent(1);
                draw_list->AddRectFilled(vec2(p1.x, p1.y), vec2(p1.x + 50, p1.y + 50), IM_COL32(0, 0, 255, 255)); // Blue
                draw_list->ChannelsSetCurrent(0);
                draw_list->AddRectFilled(vec2(p1.x + 25, p1.y + 25), vec2(p1.x + 75, p1.y + 75), IM_COL32(255, 0, 0, 255)); // Red

                // Flatten/reorder channels. Red shape is in channel 0 and it appears below the Blue shape in channel 1.
                // This works by copying draw indices only (vertices are not copied).
                draw_list->ChannelsMerge();
                UI::Dummy(vec2(75, 75));
                UI::Text("After reordering, contents of channel 0 appears below channel 1.");
            }
            UI::EndTabItem();
        }

        UI::EndTabBar();
    }

    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Docking, DockSpace / ShowExampleAppDockSpace()
//-----------------------------------------------------------------------------

struct uiDemoDockspaceArgs
{
    bool                IsFullscreen = true;
    bool                KeepWindowPadding = false; // Keep WindowPadding to help understand that DockSpace() is a widget inside the window.
    uiDockFlags  DockSpaceFlags  = uiDockFlags_None;
};

// THIS IS A DEMO FOR ADVANCED USAGE OF DockSpace().
// MOST REGULAR APPLICATIONS WANTING TO ALLOW DOCKING WINDOWS ON THE EDGE OF YOUR SCREEN CAN SIMPLY USE:
//    UI::NewFrame(); + UI::DockSpaceOverViewport();                                                   // Create a dockspace in main viewport
// OR:
//    UI::NewFrame(); + UI::DockSpaceOverViewport(0, nullptr, uiDockFlags_PassthruCentralNode); // Create a dockspace in main viewport, where central node is transparent.
// Demonstrate using DockSpace() to create an explicit docking node within an existing window, with various options.
// Read https://github.com/ocornut/imgui/wiki/Docking for details.
// The reasons we do not use DockSpaceOverViewport() in this demo is because:
// - (1) we allow the host window to be floating/moveable instead of filling the viewport (when args->IsFullscreen == false)
//       which is mostly to showcase the idea that DockSpace() may be submitted anywhere.
//       Also see 'Demo->Examples->Documents' for a less abstract version of this.
// - (2) we allow the host window to have padding (when args->UsePadding == true)
// - (3) we expose variety of other flags.
static void ShowExampleAppDockSpaceAdvanced(uiDemoDockspaceArgs* args, bool* p_open)
{
    uiDockFlags dockspace_flags = args->DockSpaceFlags;

    // We are using the uiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    uiWindowFlags window_flags = uiWindowFlags_NoDocking;
    if (args->IsFullscreen)
    {
        // Fullscreen dockspace: practically the same as calling DockSpaceOverViewport();
        const uiViewport* viewport = UI::GetMainViewport();
        UI::SetNextWindowPos(viewport->WorkPos);
        UI::SetNextWindowSize(viewport->WorkSize);
        UI::SetNextWindowViewport(viewport->ID);
        UI::PushStyleVar(uiStyleVar_WindowRounding, 0.0f);
        UI::PushStyleVar(uiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= uiWindowFlags_NoTitleBar | uiWindowFlags_NoCollapse | uiWindowFlags_NoResize | uiWindowFlags_NoMove;
        window_flags |= uiWindowFlags_NoBringToFrontOnFocus | uiWindowFlags_NoNavFocus;
        window_flags |= uiWindowFlags_NoBackground;
    }
    else
    {
        // Floating dockspace
        dockspace_flags &= ~uiDockFlags_PassthruCentralNode;
    }

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!args->KeepWindowPadding)
        UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0.0f, 0.0f));
    UI::Begin("Window with a DockSpace", p_open, window_flags);
    if (!args->KeepWindowPadding)
        UI::PopStyleVar();

    if (args->IsFullscreen)
        UI::PopStyleVar(2);

    // Submit the DockSpace widget inside our window
    // - Note that the id here is different from the one used by DockSpaceOverViewport(), so docking state won't get transfered between "Basic" and "Advanced" demos.
    // - If we made the ShowExampleAppDockSpaceBasic() calculate its own ID and pass it to DockSpaceOverViewport() the ID could easily match.
    uiID dockspace_id = UI::GetID("MyDockSpace");
    UI::DockSpace(dockspace_id, vec2(0.0f, 0.0f), dockspace_flags);

    UI::End();
}

static void ShowExampleAppDockSpaceBasic(uiDockFlags flags)
{
    // Basic version which you can use in many apps:
    // e.g:
    //   UI::DockSpaceOverViewport();
    // or:
    //   UI::DockSpaceOverViewport(0, nullptr, uiDockFlags_PassthruCentralNode); // Central node will be transparent
    // or:
    //   uiViewport* viewport = UI::GetMainViewport();
    //   UI::DockSpaceOverViewport(0, viewport, uiDockFlags_None);

    UI::DockSpaceOverViewport(0, nullptr, flags);
}

void ShowExampleAppDockSpace(bool* p_open)
{
    static int opt_demo_mode = 0;
    static bool opt_demo_mode_changed = false;
    static uiDemoDockspaceArgs args;

    if (opt_demo_mode == 0)
        ShowExampleAppDockSpaceBasic(args.DockSpaceFlags);
    else
        ShowExampleAppDockSpaceAdvanced(&args, p_open);

    // Refocus our window to minimize perceived loss of focus when changing mode (caused by the fact that each use a different window, which would not happen in a real app)
    if (opt_demo_mode_changed)
        UI::SetNextWindowFocus();
    UI::Begin("Examples: Dockspace", p_open, uiWindowFlags_MenuBar);
    opt_demo_mode_changed = false;
    opt_demo_mode_changed |= UI::RadioButton("Basic demo mode", &opt_demo_mode, 0);
    opt_demo_mode_changed |= UI::RadioButton("Advanced demo mode", &opt_demo_mode, 1);

    UI::BarrierText("Options");

    if ((UI::GetIO().ConfigFlags & uiConfigFlags_DockingEnable) == 0)
    {
        ShowDockingDisabledMessage();
    }
    else if (opt_demo_mode == 0)
    {
        args.DockSpaceFlags &= uiDockFlags_PassthruCentralNode; // Allowed flags
        UI::CheckboxFlags("Flag: PassthruCentralNode", &args.DockSpaceFlags, uiDockFlags_PassthruCentralNode);
    }
    else if (opt_demo_mode == 1)
    {
        UI::Checkbox("Fullscreen", &args.IsFullscreen);
        UI::Checkbox("Keep Window Padding", &args.KeepWindowPadding);
        UI::SameLine();
        HelpMarker("This is mostly exposed to facilitate understanding that a DockSpace() is _inside_ a window.");
        UI::BeginDisabled(args.IsFullscreen == false);
        UI::CheckboxFlags("Flag: PassthruCentralNode",      &args.DockSpaceFlags, uiDockFlags_PassthruCentralNode);
        UI::EndDisabled();
        UI::CheckboxFlags("Flag: NoDockingOverCentralNode", &args.DockSpaceFlags, uiDockFlags_NoDockingOverCentralNode);
        UI::CheckboxFlags("Flag: NoDockingSplit",           &args.DockSpaceFlags, uiDockFlags_NoDockingSplit);
        UI::CheckboxFlags("Flag: NoUndocking",              &args.DockSpaceFlags, uiDockFlags_NoUndocking);
        UI::CheckboxFlags("Flag: NoResize",                 &args.DockSpaceFlags, uiDockFlags_NoResize);
        UI::CheckboxFlags("Flag: AutoHideTabBar",           &args.DockSpaceFlags, uiDockFlags_AutoHideTabBar);
    }

    // Show demo options and help
    if (UI::BeginMenuBar())
    {
        if (UI::BeginMenu("Help"))
        {
            UI::TextUnformatted(
                "This demonstrates the use of UI::DockSpace() which allows you to manually\ncreate a docking node _within_ another window." "\n"
                "The \"Basic\" version uses the UI::DockSpaceOverViewport() helper. Most applications can probably use this.");
            UI::Barrier();
            UI::TextUnformatted("When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
                "- Drag from window title bar or their tab to dock/undock." "\n"
                "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
                "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
                "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)");
            UI::Barrier();
            UI::TextUnformatted("More details:"); UI::Bullet(); UI::SameLine(); UI::TextLinkOpenURL("Docking Wiki page", "https://github.com/ocornut/imgui/wiki/Docking");
            UI::BulletText("Read comments in ShowExampleAppDockSpace()");
            UI::EndMenu();
        }
        UI::EndMenuBar();
    }

    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Documents Handling / ShowExampleAppDocuments()
//-----------------------------------------------------------------------------

// Simplified structure to mimic a Document model
struct MyDocument
{
    char        Name[32];   // Document title
    int         UID;        // Unique ID (necessary as we can change title)
    bool        Open;       // Set when open (we keep an array of all available documents to simplify demo code!)
    bool        OpenPrev;   // Copy of Open from last update.
    bool        Dirty;      // Set when the document has been modified
    vec4      Color;      // An arbitrary variable associated to the document

    MyDocument(int uid, const char* name, bool open = true, const vec4& color = vec4(1.0f, 1.0f, 1.0f, 1.0f))
    {
        UID = uid;
        snprintf(Name, sizeof(Name), "%s", name);
        Open = OpenPrev = open;
        Dirty = false;
        Color = color;
    }
    void DoOpen()       { Open = true; }
    void DoForceClose() { Open = false; Dirty = false; }
    void DoSave()       { Dirty = false; }
};

struct ExampleAppDocuments
{
    ImVector<MyDocument>    Documents;
    ImVector<MyDocument*>   CloseQueue;
    MyDocument*             RenamingDoc = NULL;
    bool                    RenamingStarted = false;

    ExampleAppDocuments()
    {
        Documents.push_back(MyDocument(0, "Lettuce",             true,  vec4(0.4f, 0.8f, 0.4f, 1.0f)));
        Documents.push_back(MyDocument(1, "Eggplant",            true,  vec4(0.8f, 0.5f, 1.0f, 1.0f)));
        Documents.push_back(MyDocument(2, "Carrot",              true,  vec4(1.0f, 0.8f, 0.5f, 1.0f)));
        Documents.push_back(MyDocument(3, "Tomato",              false, vec4(1.0f, 0.3f, 0.4f, 1.0f)));
        Documents.push_back(MyDocument(4, "A Rather Long Title", false, vec4(0.4f, 0.8f, 0.8f, 1.0f)));
        Documents.push_back(MyDocument(5, "Some Document",       false, vec4(0.8f, 0.8f, 1.0f, 1.0f)));
    }

    // As we allow to change document name, we append a never-changing document ID so tabs are stable
    void GetTabName(MyDocument* doc, char* out_buf, size_t out_buf_size)
    {
        snprintf(out_buf, out_buf_size, "%s###doc%d", doc->Name, doc->UID);
    }

    // Display placeholder contents for the Document
    void DisplayDocContents(MyDocument* doc)
    {
        UI::PushID(doc);
        UI::Text("Document \"%s\"", doc->Name);
        UI::PushStyleColor(uiCol_Text, doc->Color);
        UI::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
        UI::PopStyleColor();

        UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_R, uiInputFlags_Tooltip);
        if (UI::Button("Rename.."))
        {
            RenamingDoc = doc;
            RenamingStarted = true;
        }
        UI::SameLine();

        UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_M, uiInputFlags_Tooltip);
        if (UI::Button("Modify"))
            doc->Dirty = true;

        UI::SameLine();
        UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_S, uiInputFlags_Tooltip);
        if (UI::Button("Save"))
            doc->DoSave();

        UI::SameLine();
        UI::SetNextItemShortcut(uiMod_Ctrl | uiKey_W, uiInputFlags_Tooltip);
        if (UI::Button("Close"))
            CloseQueue.push_back(doc);
        UI::ColorEdit3("color", &doc->Color.x);  // Useful to test drag and drop and hold-dragged-to-open-tab behavior.
        UI::PopID();
    }

    // Display context menu for the Document
    void DisplayDocContextMenu(MyDocument* doc)
    {
        if (!UI::BeginPopupContextItem())
            return;

        char buf[256];
        sprintf(buf, "Save %s", doc->Name);
        if (UI::MenuItem(buf, "Ctrl+S", false, doc->Open))
            doc->DoSave();
        if (UI::MenuItem("Rename...", "Ctrl+R", false, doc->Open))
            RenamingDoc = doc;
        if (UI::MenuItem("Close", "Ctrl+W", false, doc->Open))
            CloseQueue.push_back(doc);
        UI::EndPopup();
    }

    // [Optional] Notify the system of Tabs/Windows closure that happened outside the regular tab interface.
    // If a tab has been closed programmatically (aka closed from another source such as the Checkbox() in the demo,
    // as opposed to clicking on the regular tab closing button) and stops being submitted, it will take a frame for
    // the tab bar to notice its absence. During this frame there will be a gap in the tab bar, and if the tab that has
    // disappeared was the selected one, the tab bar will report no selected tab during the frame. This will effectively
    // give the impression of a flicker for one frame.
    // We call SetTabItemClosed() to manually notify the Tab Bar or Docking system of removed tabs to avoid this glitch.
    // Note that this completely optional, and only affect tab bars with the uiTabBarFlags_Reorderable flag.
    void NotifyOfDocumentsClosedElsewhere()
    {
        for (MyDocument& doc : Documents)
        {
            if (!doc.Open && doc.OpenPrev)
                UI::SetTabItemClosed(doc.Name);
            doc.OpenPrev = doc.Open;
        }
    }
};

void ShowExampleAppDocuments(bool* p_open)
{
    static ExampleAppDocuments app;

    // Options
    enum Target
    {
        Target_None,
        Target_Tab,                 // Create documents as local tab into a local tab bar
        Target_DockSpaceAndWindow   // Create documents as regular windows, and create an embedded dockspace
    };
    static Target opt_target = Target_Tab;
    static bool opt_reorderable = true;
    static uiTabBarFlags opt_fitting_flags = uiTabBarFlags_FitDefault_;

    // When (opt_target == Target_DockSpaceAndWindow) there is the possibily that one of our child Document window (e.g. "Eggplant")
    // that we emit gets docked into the same spot as the parent window ("Example: Documents").
    // This would create a problematic feedback loop because selecting the "Eggplant" tab would make the "Example: Documents" tab
    // not visible, which in turn would stop submitting the "Eggplant" window.
    // We avoid this problem by submitting our documents window even if our parent window is not currently visible.
    // Another solution may be to make the "Example: Documents" window use the uiWindowFlags_NoDocking.

    bool window_contents_visible = UI::Begin("Example: Documents", p_open, uiWindowFlags_MenuBar);
    if (!window_contents_visible && opt_target != Target_DockSpaceAndWindow)
    {
        UI::End();
        return;
    }
    IMGUI_DEMO_MARKER("Examples/Documents");

    // Menu
    if (UI::BeginMenuBar())
    {
        if (UI::BeginMenu("File"))
        {
            int open_count = 0;
            for (MyDocument& doc : app.Documents)
                open_count += doc.Open ? 1 : 0;

            if (UI::BeginMenu("Open", open_count < app.Documents.Size))
            {
                for (MyDocument& doc : app.Documents)
                    if (!doc.Open && UI::MenuItem(doc.Name))
                        doc.DoOpen();
                UI::EndMenu();
            }
            if (UI::MenuItem("Close All Documents", NULL, false, open_count > 0))
                for (MyDocument& doc : app.Documents)
                    app.CloseQueue.push_back(&doc);
            if (UI::MenuItem("Exit") && p_open)
                *p_open = false;
            UI::EndMenu();
        }
        UI::EndMenuBar();
    }

    // [Debug] List documents with one checkbox for each
    for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
    {
        MyDocument& doc = app.Documents[doc_n];
        if (doc_n > 0)
            UI::SameLine();
        UI::PushID(&doc);
        if (UI::Checkbox(doc.Name, &doc.Open))
            if (!doc.Open)
                doc.DoForceClose();
        UI::PopID();
    }
    UI::PushItemWidth(UI::GetFontSize() * 12);
    UI::Combo("Output", (int*)&opt_target, "None\0TabBar+Tabs\0DockSpace+Window\0");
    UI::PopItemWidth();
    bool redock_all = false;
    if (opt_target == Target_Tab)                { UI::SameLine(); UI::Checkbox("Reorderable Tabs", &opt_reorderable); }
    if (opt_target == Target_DockSpaceAndWindow) { UI::SameLine(); redock_all = UI::Button("Redock all"); }

    UI::Barrier();

    // About the uiWindowFlags_UnsavedDocument / uiTabItemFlags_UnsavedDocument flags.
    // They have multiple effects:
    // - Display a dot next to the title.
    // - Tab is selected when clicking the X close button.
    // - Closure is not assumed (will wait for user to stop submitting the tab).
    //   Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    //   We need to assume closure by default otherwise waiting for "lack of submission" on the next frame would leave an empty
    //   hole for one-frame, both in the tab-bar and in tab-contents when closing a tab/window.
    //   The rarely used SetTabItemClosed() function is a way to notify of programmatic closure to avoid the one-frame hole.

    // Tabs
    if (opt_target == Target_Tab)
    {
        uiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? uiTabBarFlags_Reorderable : 0);
        tab_bar_flags |= uiTabBarFlags_DrawSelectedOverline;
        if (UI::BeginTabBar("##tabs", tab_bar_flags))
        {
            if (opt_reorderable)
                app.NotifyOfDocumentsClosedElsewhere();

            // [DEBUG] Stress tests
            //if ((UI::GetFrameCount() % 30) == 0) docs[1].Open ^= 1;            // [DEBUG] Automatically show/hide a tab. Test various interactions e.g. dragging with this on.
            //if (UI::GetIO().KeyCtrl) UI::SetTabItemSelected(docs[1].Name);  // [DEBUG] Test SetTabItemSelected(), probably not very useful as-is anyway..

            // Submit Tabs
            for (MyDocument& doc : app.Documents)
            {
                if (!doc.Open)
                    continue;

                // As we allow to change document name, we append a never-changing document id so tabs are stable
                char doc_name_buf[64];
                app.GetTabName(&doc, doc_name_buf, sizeof(doc_name_buf));
                uiTabItemFlags tab_flags = (doc.Dirty ? uiTabItemFlags_UnsavedDocument : 0);
                bool visible = UI::BeginTabItem(doc_name_buf, &doc.Open, tab_flags);

                // Cancel attempt to close when unsaved add to save queue so we can display a popup.
                if (!doc.Open && doc.Dirty)
                {
                    doc.Open = true;
                    app.CloseQueue.push_back(&doc);
                }

                app.DisplayDocContextMenu(&doc);
                if (visible)
                {
                    app.DisplayDocContents(&doc);
                    UI::EndTabItem();
                }
            }

            UI::EndTabBar();
        }
    }
    else if (opt_target == Target_DockSpaceAndWindow)
    {
        if (UI::GetIO().ConfigFlags & uiConfigFlags_DockingEnable)
        {
            app.NotifyOfDocumentsClosedElsewhere();

            // Create a DockSpace node where any window can be docked
            uiID dockspace_id = UI::GetID("MyDockSpace");
            UI::DockSpace(dockspace_id);

            // Create Windows
            for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
            {
                MyDocument* doc = &app.Documents[doc_n];
                if (!doc->Open)
                    continue;

                UI::SetNextWindowDockID(dockspace_id, redock_all ? uiCond_Always : uiCond_FirstUseEver);
                uiWindowFlags window_flags = (doc->Dirty ? uiWindowFlags_UnsavedDocument : 0);
                bool visible = UI::Begin(doc->Name, &doc->Open, window_flags);

                // Cancel attempt to close when unsaved add to save queue so we can display a popup.
                if (!doc->Open && doc->Dirty)
                {
                    doc->Open = true;
                    app.CloseQueue.push_back(doc);
                }

                app.DisplayDocContextMenu(doc);
                if (visible)
                    app.DisplayDocContents(doc);

                UI::End();
            }
        }
        else
        {
            ShowDockingDisabledMessage();
        }
    }

    // Early out other contents
    if (!window_contents_visible)
    {
        UI::End();
        return;
    }

    // Display renaming UI
    if (app.RenamingDoc != NULL)
    {
        if (app.RenamingStarted)
            UI::OpenPopup("Rename");
        if (UI::BeginPopup("Rename"))
        {
            UI::SetNextItemWidth(UI::GetFontSize() * 30);
            if (UI::InputText("###Name", app.RenamingDoc->Name, IM_COUNTOF(app.RenamingDoc->Name), uiInputTextFlags_EnterReturnsTrue))
            {
                UI::CloseCurrentPopup();
                app.RenamingDoc = NULL;
            }
            if (app.RenamingStarted)
                UI::SetKeyboardFocusHere(-1);
            UI::EndPopup();
        }
        else
        {
            app.RenamingDoc = NULL;
        }
        app.RenamingStarted = false;
    }

    // Display closing confirmation UI
    if (!app.CloseQueue.empty())
    {
        int close_queue_unsaved_documents = 0;
        for (int n = 0; n < app.CloseQueue.Size; n++)
            if (app.CloseQueue[n]->Dirty)
                close_queue_unsaved_documents++;

        if (close_queue_unsaved_documents == 0)
        {
            // Close documents when all are unsaved
            for (int n = 0; n < app.CloseQueue.Size; n++)
                app.CloseQueue[n]->DoForceClose();
            app.CloseQueue.clear();
        }
        else
        {
            if (!UI::IsPopupOpen("Save?"))
                UI::OpenPopup("Save?");
            if (UI::BeginPopupModal("Save?", NULL, uiWindowFlags_AutoResize))
            {
                UI::Text("Save change to the following items?");
                float item_height = UI::GetTextLineHeightWithSpacing();
                if (UI::BeginChild(UI::GetID("frame"), vec2(-FLT_MIN, 6.25f * item_height), uiChildFlags_FrameStyle))
                    for (MyDocument* doc : app.CloseQueue)
                        if (doc->Dirty)
                            UI::Text("%s", doc->Name);
                UI::EndChild();

                vec2 button_size(UI::GetFontSize() * 7.0f, 0.0f);
                if (UI::Button("Yes", button_size))
                {
                    for (MyDocument* doc : app.CloseQueue)
                    {
                        if (doc->Dirty)
                            doc->DoSave();
                        doc->DoForceClose();
                    }
                    app.CloseQueue.clear();
                    UI::CloseCurrentPopup();
                }
                UI::SameLine();
                if (UI::Button("No", button_size))
                {
                    for (MyDocument* doc : app.CloseQueue)
                        doc->DoForceClose();
                    app.CloseQueue.clear();
                    UI::CloseCurrentPopup();
                }
                UI::SameLine();
                if (UI::Button("Cancel", button_size))
                {
                    app.CloseQueue.clear();
                    UI::CloseCurrentPopup();
                }
                UI::EndPopup();
            }
        }
    }

    UI::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Assets Browser / ShowExampleAppAssetsBrowser()
//-----------------------------------------------------------------------------

//#include "imgui_internal.h" // NavMoveRequestTryWrapping()

struct ExampleAsset
{
    uiID ID;
    int     Type;

    ExampleAsset(uiID id, int type) { ID = id; Type = type; }

    static const uiTableSortSpecs* s_current_sort_specs;

    static void SortWithSortSpecs(uiTableSortSpecs* sort_specs, ExampleAsset* items, int items_count)
    {
        s_current_sort_specs = sort_specs; // Store in variable accessible by the sort function.
        if (items_count > 1)
            qsort(items, (size_t)items_count, sizeof(items[0]), ExampleAsset::CompareWithSortSpecs);
        s_current_sort_specs = NULL;
    }

    // Compare function to be used by qsort()
    static int IMGUI_CDECL CompareWithSortSpecs(const void* lhs, const void* rhs)
    {
        const ExampleAsset* a = (const ExampleAsset*)lhs;
        const ExampleAsset* b = (const ExampleAsset*)rhs;
        for (int n = 0; n < s_current_sort_specs->SpecsCount; n++)
        {
            const uiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
            int delta = 0;
            if (sort_spec->ColumnIndex == 0)
                delta = ((int)a->ID - (int)b->ID);
            else if (sort_spec->ColumnIndex == 1)
                delta = (a->Type - b->Type);
            if (delta > 0)
                return (sort_spec->SortDirection == Var::SortDir::Ascend) ? +1 : -1;
            if (delta < 0)
                return (sort_spec->SortDirection == Var::SortDir::Ascend) ? -1 : +1;
        }
        return (int)a->ID - (int)b->ID;
    }
};
const uiTableSortSpecs* ExampleAsset::s_current_sort_specs = NULL;
struct ExampleAssetsBrowser {
    // Options
    bool            ShowTypeOverlay = true;
    bool            AllowSorting = true;
    bool            AllowBoxSelect = true;                  // Will set uiMultiSelectFlags_BoxSelect2d
    bool            AllowBoxSelectInsideSelection = false;  // Will set uiMultiSelectFlags_SelectOnClickAlways
    bool            AllowDragUnselected = false;            // Will set uiMultiSelectFlags_SelectOnClickRelease
    float           IconSize = 0;
    int             IconSpacing = 10;
    int             IconHitSpacing = 4;                     // Increase hit-spacing if you want to make it possible to clear or box-select from gaps. Some spacing is required to able to amend with Shift+box-select. Value is small in Explorer.
    bool            StretchSpacing = true;
    bool            UseScrollX = false;                     // Debug: submit twice the number of items per line (overflow horizontally to exercise ScrollX + box-select)

    // State
    ImVector<ExampleAsset> Items;               // Our items
    ExampleSelectionWithDeletion Selection;     // Our selection (uiSelectionBasicStorage + helper funcs to handle deletion)
    uiID         NextItemId = 0;             // Unique identifier when creating new items
    bool            RequestDelete = false;      // Deferred deletion request
    bool            RequestSort = false;        // Deferred sort request
    float           ZoomWheelAccum = 0.0f;      // Mouse wheel accumulator to handle smooth wheels better

    // Calculated sizes for layout, output of UpdateLayoutSizes(). Could be locals but our code is simpler this way.
    vec2          LayoutItemSize;
    vec2          LayoutItemStep;             // == LayoutItemSize + LayoutItemSpacing
    float           LayoutItemSpacing = 0.0f;
    float           LayoutSelectableSpacing = 0.0f;
    float           LayoutOuterPadding = 0.0f;
    int             LayoutColumnCount = 0;
    int             LayoutLineCount = 0;

    // Functions
    ExampleAssetsBrowser()
    {
        AddItems(10000);
    }
    void AddItems(int count)
    {
        if (Items.Size == 0)
            NextItemId = 0;
        Items.reserve(Items.Size + count);
        for (int n = 0; n < count; n++, NextItemId++)
            Items.push_back(ExampleAsset(NextItemId, (NextItemId % 20) < 15 ? 0 : (NextItemId % 20) < 18 ? 1 : 2));
        RequestSort = true;
    }
    void ClearItems()
    {
        Items.clear();
        Selection.Clear();
    }

    // Logic would be written in the main code BeginChild() and outputting to local variables.
    // We extracted it into a function so we can call it easily from multiple places.
    void UpdateLayoutSizes(float avail_width)
    {
        // Layout: when not stretching: allow extending into right-most spacing.
        LayoutItemSpacing = (float)IconSpacing;
        if (StretchSpacing == false)
            avail_width += floorf(LayoutItemSpacing * 0.5f);

        // Layout: calculate number of icon per line and number of lines
        LayoutItemSize = vec2(floorf(IconSize), floorf(IconSize));
        LayoutColumnCount = IM_MAX((int)(avail_width / (LayoutItemSize.x + LayoutItemSpacing)), 1);

        // Layout: when stretching: allocate remaining space to more spacing. Round before division, so item_spacing may be non-integer.
        if (StretchSpacing && LayoutColumnCount > 1)
            LayoutItemSpacing = floorf(avail_width - LayoutItemSize.x * LayoutColumnCount) / LayoutColumnCount;

        if (UseScrollX)
            LayoutColumnCount *= 2;
        LayoutLineCount = (Items.Size + LayoutColumnCount - 1) / LayoutColumnCount;

        LayoutItemStep = vec2(LayoutItemSize.x + LayoutItemSpacing, LayoutItemSize.y + LayoutItemSpacing);
        LayoutSelectableSpacing = IM_MAX(floorf(LayoutItemSpacing) - IconHitSpacing, 0.0f);
        LayoutOuterPadding = floorf(LayoutItemSpacing * 0.5f);
    }

    void Draw(const char* title, bool* p_open)
    {
        if (IconSize <= 0.0f)
            IconSize = UI::CalcTextSize("99999").x;

        UI::SetNextWindowSize(vec2(IconSize * 25, IconSize * 15), uiCond_FirstUseEver);
        if (!UI::Begin(title, p_open, uiWindowFlags_MenuBar))
        {
            UI::End();
            return;
        }
        IMGUI_DEMO_MARKER("Examples/Assets Browser");

        // Menu bar
        if (UI::BeginMenuBar())
        {
            if (UI::BeginMenu("File"))
            {
                if (UI::MenuItem("Add 10000 items"))
                    AddItems(10000);
                if (UI::MenuItem("Clear items"))
                    ClearItems();
                UI::Barrier();
                if (UI::MenuItem("Close", NULL, false, p_open != NULL))
                    *p_open = false;
                UI::EndMenu();
            }
            if (UI::BeginMenu("Edit"))
            {
                if (UI::MenuItem("Delete", "Del", false, Selection.Size > 0))
                    RequestDelete = true;
                UI::EndMenu();
            }
            if (UI::BeginMenu("Options"))
            {
                UI::PushItemWidth(UI::GetFontSize() * 10);

                UI::BarrierText("Contents");
                UI::Checkbox("Show Type Overlay", &ShowTypeOverlay);
                UI::Checkbox("Allow Sorting", &AllowSorting);

                UI::BarrierText("Selection Behavior");
                UI::Checkbox("Allow box-selection", &AllowBoxSelect);
                if (UI::Checkbox("Allow box-selection from selected items", &AllowBoxSelectInsideSelection) && AllowBoxSelectInsideSelection)
                    AllowDragUnselected = false;
                if (UI::Checkbox("Allow dragging unselected item", &AllowDragUnselected) && AllowDragUnselected)
                    AllowBoxSelectInsideSelection = false;

                UI::BarrierText("Layout");
                UI::SliderFloat("Icon Size", &IconSize, 16.0f, 128.0f, "%.0f");
                UI::SameLine(); HelpMarker("Use Ctrl+Wheel to zoom");
                UI::SliderInt("Icon Spacing", &IconSpacing, 0, 32);
                UI::SliderInt("Icon Hit Spacing", &IconHitSpacing, 0, 32);
                UI::Checkbox("Stretch Spacing", &StretchSpacing);
                UI::Checkbox("Use ScrollX", &UseScrollX);
                UI::PopItemWidth();
                UI::EndMenu();
            }
            UI::EndMenuBar();
        }

        // Show a table with ONLY one header row to showcase the idea/possibility of using this to provide a sorting UI
        if (AllowSorting)
        {
            UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(0, 0));
            uiTableFlags table_flags_for_sort_specs = uiTableFlags_Sortable | uiTableFlags_SortMulti | uiTableFlags_SizingFixedFit | uiTableFlags_Borders;
            if (UI::BeginTable("for_sort_specs_only", 2, table_flags_for_sort_specs, vec2(0.0f, UI::GetFrameHeight())))
            {
                UI::TableSetupColumn("Index");
                UI::TableSetupColumn("Type");
                UI::TableHeadersRow();
                if (uiTableSortSpecs* sort_specs = UI::TableGetSortSpecs())
                    if (sort_specs->SpecsDirty || RequestSort)
                    {
                        ExampleAsset::SortWithSortSpecs(sort_specs, Items.Data, Items.Size);
                        sort_specs->SpecsDirty = RequestSort = false;
                    }
                UI::EndTable();
            }
            UI::PopStyleVar();
        }

        uiIO& io = UI::GetIO();
        UI::SetNextWindowContentSize(vec2(0.0f, LayoutOuterPadding + LayoutLineCount * (LayoutItemSize.y + LayoutItemSpacing)));
        if (UI::BeginChild("Assets", vec2(0.0f, -UI::GetTextLineHeightWithSpacing()), uiChildFlags_Borders, uiWindowFlags_NoMove | uiWindowFlags_HorizontalScrollbar))
        {
            ImDrawList* draw_list = UI::GetWindowDrawList();

            const float avail_width = UI::GetContentRegionAvail().x;
            UpdateLayoutSizes(avail_width);

            // Calculate and store start position.
            vec2 start_pos = UI::GetCursorScreenPos();
            start_pos = vec2(start_pos.x + LayoutOuterPadding, start_pos.y + LayoutOuterPadding);
            UI::SetCursorScreenPos(start_pos);

            // Multi-select
            uiMultiSelectFlags ms_flags = uiMultiSelectFlags_ClearOnEscape | uiMultiSelectFlags_ClearOnClickVoid;

            // - Enable box-select (in 2D mode, so that changing box-select rectangle X1/X2 boundaries will affect clipped items)
            if (AllowBoxSelect)
                ms_flags |= uiMultiSelectFlags_BoxSelect2d;

            // - Selection mode
            if (AllowDragUnselected)
                ms_flags |= uiMultiSelectFlags_SelectOnClickRelease; // Rarely used: Allows dragging an unselected item without selecting it(rarely used)
            else if (AllowBoxSelectInsideSelection)
                ms_flags |= uiMultiSelectFlags_SelectOnClickAlways; // Rarely used: Prevents Drag and Drop from being used on multiple-selection, but allows e.g. BoxSelect to always reselect even when clicking inside an existing selection.

            // - Enable keyboard wrapping on X axis
            // (FIXME-MULTISELECT: We haven't designed/exposed a general nav wrapping api yet, so this flag is provided as a courtesy to avoid doing:
            //    UI::NavMoveRequestTryWrapping(UI::GetCurrentWindow(), ImGuiNavMoveFlags_WrapX);
            // When we finish implementing a more general API for this, we will obsolete this flag in favor of the new system)
            ms_flags |= uiMultiSelectFlags_NavWrapX;

            uiMultiSelectIO* ms_io = UI::BeginMultiSelect(ms_flags, Selection.Size, Items.Size);

            // Use custom selection adapter: store ID in selection (recommended)
            Selection.UserData = this;
            Selection.AdapterIndexToStorageId = [](uiSelectionBasicStorage* self_, int idx) { ExampleAssetsBrowser* self = (ExampleAssetsBrowser*)self_->UserData; return self->Items[idx].ID; };
            Selection.ApplyRequests(ms_io);

            const bool want_delete = (UI::Shortcut(uiKey_Delete, uiInputFlags_Repeat) && (Selection.Size > 0)) || RequestDelete;
            const int item_curr_idx_to_focus = want_delete ? Selection.ApplyDeletionPreLoop(ms_io, Items.Size) : -1;
            RequestDelete = false;

            // Push LayoutSelectableSpacing (which is LayoutItemSpacing minus hit-spacing, if we decide to have hit gaps between items)
            // Altering style ItemSpacing may seem unnecessary as we position every items using SetCursorScreenPos()...
            // But it is necessary for two reasons:
            // - Selectables uses it by default to visually fill the space between two items.
            // - The vertical spacing would be measured by Clipper to calculate line height if we didn't provide it explicitly (here we do).
            UI::PushStyleVar(uiStyleVar_ItemSpacing, vec2(LayoutSelectableSpacing, LayoutSelectableSpacing));

            // Rendering parameters
            const ImU32 icon_type_overlay_colors[3] = { 0, IM_COL32(200, 70, 70, 255), IM_COL32(70, 170, 70, 255) };
            const ImU32 icon_bg_color = UI::GetColorU32(IM_COL32(35, 35, 35, 220));
            const vec2 icon_type_overlay_size = vec2(4.0f, 4.0f);
            const bool display_label = (LayoutItemSize.x >= UI::CalcTextSize("999").x);

            const int column_count = LayoutColumnCount;
            uiListClipper clipper;
            clipper.Begin(LayoutLineCount, LayoutItemStep.y);
            if (item_curr_idx_to_focus != -1)
                clipper.IncludeItemByIndex(item_curr_idx_to_focus / column_count); // Ensure focused item line is not clipped.
            if (ms_io->RangeSrcItem != -1)
                clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem / column_count); // Ensure RangeSrc item line is not clipped.
            while (clipper.Step())
            {
                for (int line_idx = clipper.DisplayStart; line_idx < clipper.DisplayEnd; line_idx++)
                {
                    const int item_min_idx_for_current_line = line_idx * column_count;
                    const int item_max_idx_for_current_line = IM_MIN((line_idx + 1) * column_count, Items.Size);
                    for (int item_idx = item_min_idx_for_current_line; item_idx < item_max_idx_for_current_line; ++item_idx)
                    {
                        ExampleAsset* item_data = &Items[item_idx];
                        UI::PushID((int)item_data->ID);

                        // Position item
                        vec2 pos = vec2(start_pos.x + (item_idx % column_count) * LayoutItemStep.x, start_pos.y + line_idx * LayoutItemStep.y);
                        UI::SetCursorScreenPos(pos);

                        UI::SetNextItemSelectionUserData(item_idx);
                        bool item_is_selected = Selection.Contains((uiID)item_data->ID);
                        bool item_is_visible = UI::IsRectVisible(LayoutItemSize);
                        UI::Selectable("", item_is_selected, uiSelectFlags_None, LayoutItemSize);

                        // Update our selection state immediately (without waiting for EndMultiSelect() requests)
                        // because we use this to alter the color of our text/icon.
                        if (UI::IsItemToggledSelection())
                            item_is_selected = !item_is_selected;

                        // Focus (for after deletion)
                        if (item_curr_idx_to_focus == item_idx)
                            UI::SetKeyboardFocusHere(-1);

                        // Drag and drop
                        if (UI::BeginDragDropSource())
                        {
                            // Create payload with full selection OR single unselected item.
                            // (the later is only possible when using uiMultiSelectFlags_SelectOnClickRelease)
                            if (UI::GetDragDropPayload() == NULL)
                            {
                                ImVector<uiID> payload_items;
                                void* it = NULL;
                                uiID id = 0;
                                if (!item_is_selected)
                                    payload_items.push_back(item_data->ID);
                                else
                                    while (Selection.GetNextSelectedItem(&it, &id))
                                        payload_items.push_back(id);
                                UI::SetDragDropPayload("ASSETS_BROWSER_ITEMS", payload_items.Data, (size_t)payload_items.size_in_bytes());
                            }

                            // Display payload content in tooltip, by extracting it from the payload data
                            // (we could read from selection, but it is more correct and reusable to read from payload)
                            const uiPayload* payload = UI::GetDragDropPayload();
                            const int payload_count = (int)payload->DataSize / (int)sizeof(uiID);
                            UI::Text("%d assets", payload_count);

                            UI::EndDragDropSource();
                        }

                        // Render icon (a real app would likely display an image/thumbnail here)
                        // Because we use uiMultiSelectFlags_BoxSelect2d, clipping vertical may occasionally be larger, so we coarse-clip our rendering as well.
                        if (item_is_visible)
                        {
                            vec2 box_min(pos.x - 1, pos.y - 1);
                            vec2 box_max(box_min.x + LayoutItemSize.x + 2, box_min.y + LayoutItemSize.y + 2); // Dubious
                            draw_list->AddRectFilled(box_min, box_max, icon_bg_color); // Background color
                            if (ShowTypeOverlay && item_data->Type != 0)
                            {
                                ImU32 type_col = icon_type_overlay_colors[item_data->Type % IM_COUNTOF(icon_type_overlay_colors)];
                                draw_list->AddRectFilled(vec2(box_max.x - 2 - icon_type_overlay_size.x, box_min.y + 2), vec2(box_max.x - 2, box_min.y + 2 + icon_type_overlay_size.y), type_col);
                            }
                            if (display_label)
                            {
                                ImU32 label_col = UI::GetColorU32(item_is_selected ? uiCol_Text : uiCol_TextDisabled);
                                char label[32];
                                sprintf(label, "%d", item_data->ID);
                                draw_list->AddText(vec2(box_min.x, box_max.y - UI::GetFontSize()), label_col, label);
                            }
                        }

                        UI::PopID();
                    }
                }
            }
            clipper.End();
            if (Items.Size == 0)
                UI::Dummy(vec2(0, 0));
            UI::PopStyleVar(); // uiStyleVar_ItemSpacing

            // Context menu
            if (UI::BeginPopupContextWindow())
            {
                UI::Text("Selection: %d items", Selection.Size);
                UI::Barrier();
                if (UI::MenuItem("Delete", "Del", false, Selection.Size > 0))
                    RequestDelete = true;
                UI::EndPopup();
            }

            ms_io = UI::EndMultiSelect();
            Selection.ApplyRequests(ms_io);
            if (want_delete)
                Selection.ApplyDeletionPostLoop(ms_io, Items, item_curr_idx_to_focus);

            // Zooming with Ctrl+Wheel
            if (UI::IsWindowAppearing())
                ZoomWheelAccum = 0.0f;
            if (UI::IsWindowHovered() && io.MouseWheel != 0.0f && UI::IsKeyDown(uiMod_Ctrl) && UI::IsAnyItemActive() == false)
            {
                ZoomWheelAccum += io.MouseWheel;
                if (fabsf(ZoomWheelAccum) >= 1.0f)
                {
                    // Calculate hovered item index from mouse location
                    // FIXME: Locking aiming on 'hovered_item_idx' (with a cool-down timer) would ensure zoom keeps on it.
                    const float hovered_item_nx = (io.MousePos.x - start_pos.x + LayoutItemSpacing * 0.5f) / LayoutItemStep.x;
                    const float hovered_item_ny = (io.MousePos.y - start_pos.y + LayoutItemSpacing * 0.5f) / LayoutItemStep.y;
                    const int hovered_item_idx = ((int)hovered_item_ny * LayoutColumnCount) + (int)hovered_item_nx;
                    //UI::SetTooltip("%f,%f -> item %d", hovered_item_nx, hovered_item_ny, hovered_item_idx); // Move those 4 lines in block above for easy debugging

                    // Zoom
                    IconSize *= powf(1.1f, (float)(int)ZoomWheelAccum);
                    IconSize = IM_CLAMP(IconSize, 16.0f, 128.0f);
                    ZoomWheelAccum -= (int)ZoomWheelAccum;
                    UpdateLayoutSizes(avail_width);

                    // Manipulate scroll to that we will land at the same Y location of currently hovered item.
                    // - Calculate next frame position of item under mouse
                    // - Set new scroll position to be used in next UI::BeginChild() call.
                    float hovered_item_rel_pos_y = ((float)(hovered_item_idx / LayoutColumnCount) + fmodf(hovered_item_ny, 1.0f)) * LayoutItemStep.y;
                    hovered_item_rel_pos_y += UI::GetStyle().WindowPadding.y;
                    float mouse_local_y = io.MousePos.y - UI::GetWindowPos().y;
                    UI::SetScrollY(hovered_item_rel_pos_y - mouse_local_y);
                }
            }
        }
        UI::EndChild();

        UI::Text("Selected: %d/%d items", Selection.Size, Items.Size);
        UI::End();
    }
};

void ShowExampleAppAssetsBrowser(bool* p_open)
{
    IMGUI_DEMO_MARKER("Examples/Assets Browser");
    static ExampleAssetsBrowser assets_browser;
    assets_browser.Draw("Example: Assets Browser", p_open);
}

// End of Demo code
#else

void UI::ShowAboutWindow(bool*) {}
void UI::ShowDemoWindow(bool*) {}
void UI::ShowUserGuide() {}
void UI::ShowStyleEditor(uiStyle*) {}
bool UI::ShowStyleSelector(const char*) { return false; }

#endif // #ifndef IMGUI_DISABLE_DEMO_WINDOWS

#endif // #ifndef IMGUI_DISABLE
