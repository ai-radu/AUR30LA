#include <iostream>
#include "aur.hpp"
#include "project.hpp"
static c1 sPopup = false;
static uiTextFilter settingsFilter;
static c32 engineHeaderOpen = -1;
static c1 debug   = false;
static c1 ship    = false;
c8 sPath[64] = "Default";
void renderKeyboard(ImDrawList* draw_list) {
    uiStyle& style = UI::GetStyle();
    static const f32 scale = UI::GetFontSize() / 13.0f;
    static const v2  key_size = v2(57.3f, 40.0f) * scale;
    static const f32 key_rounding = 3.0f * scale;
    static const v2  key_label_pos = v2(7.0f, 4.0f) * scale;
    
    v2 board_min = UI::GetCursorScreenPos();
    v2 board_max = v2(board_min.x + 3 * 420.5f, board_min.y + 3 * 80.0f);
    v2 start_pos = board_min;
    
    f32 x = start_pos.x;
    static c32 current_row = 0;
    
    struct KeyLayoutData { c32 Row; f32 Width; cc8* Label; INPUT::Key Key; };
    const KeyLayoutData keys_to_display[] = {
        {0, 1.0f, "Esc",      INPUT::Key_Escape},
        {0, 1.0f, "",         INPUT::Key_None},
        {0, 1.0f, "F1",       INPUT::Key_F1},
        {0, 1.0f, "F2",       INPUT::Key_F2},
        {0, 1.0f, "F3",       INPUT::Key_F3},
        {0, 1.0f, "F4",       INPUT::Key_F4},
        {0, 0.5f, "",         INPUT::Key_None},
        {0, 1.0f, "F5",       INPUT::Key_F5},
        {0, 1.0f, "F6",       INPUT::Key_F6},
        {0, 1.0f, "F7",       INPUT::Key_F7},
        {0, 1.0f, "F8",       INPUT::Key_F8},
        {0, 0.5f, "",         INPUT::Key_None},
        {0, 1.0f, "F9",       INPUT::Key_F9},
        {0, 1.0f, "F10",      INPUT::Key_F10},
        {0, 1.0f, "F11",      INPUT::Key_F11},
        {0, 1.0f, "F12",      INPUT::Key_F12},
        {0, 1.0f, "Print",    INPUT::Key_PrintScreen},
        {0, 1.0f, "Scroll",   INPUT::Key_ScrollLock},
        {0, 1.0f, "Pause",    INPUT::Key_Pause},
        
        {1, 1.0f, "~ `",      INPUT::Key_GraveAccent},
        {1, 1.0f, "1 !",      INPUT::Key_1},
        {1, 1.0f, "2 @",      INPUT::Key_2},
        {1, 1.0f, "3 #",      INPUT::Key_3},
        {1, 1.0f, "4 $",      INPUT::Key_4},
        {1, 1.0f, "5 %",      INPUT::Key_5},
        {1, 1.0f, "6 ^",      INPUT::Key_6},
        {1, 1.0f, "7 &",      INPUT::Key_7},
        {1, 1.0f, "8 *",      INPUT::Key_8},
        {1, 1.0f, "9 (",      INPUT::Key_9},
        {1, 1.0f, "0 )",      INPUT::Key_0},
        {1, 1.0f, "- _",      INPUT::Key_Minus},
        {1, 1.0f, "= +",      INPUT::Key_Equal},
        {1, 2.0f, "Back",     INPUT::Key_Backspace},
        {1, 1.0f, "Insert",   INPUT::Key_Insert},
        {1, 1.0f, "Home",     INPUT::Key_Home},
        {1, 1.0f, "PageU",    INPUT::Key_PageUp},
        {1, 1.0f, "NumLK",    INPUT::Key_NumLock},
        {1, 1.0f, "/",        INPUT::Key_KeypadDivide},
        {1, 1.0f, "*",        INPUT::Key_KeypadMultiply},
        {1, 1.0f, "-",        INPUT::Key_KeypadSubtract},
        
        {2, 1.5f, "Tab",      INPUT::Key_Tab},
        {2, 1.0f, "Q",        INPUT::Key_Q},
        {2, 1.0f, "W",        INPUT::Key_W},
        {2, 1.0f, "E",        INPUT::Key_E},
        {2, 1.0f, "R",        INPUT::Key_R},
        {2, 1.0f, "T",        INPUT::Key_T},
        {2, 1.0f, "Y",        INPUT::Key_Y},
        {2, 1.0f, "U",        INPUT::Key_U},
        {2, 1.0f, "I",        INPUT::Key_I},
        {2, 1.0f, "O",        INPUT::Key_O},
        {2, 1.0f, "P",        INPUT::Key_P},
        {2, 1.0f, "[ {",      INPUT::Key_LeftBracket},
        {2, 1.0f, "] }",      INPUT::Key_RightBracket},
        {2, 1.5f, "\\ |",     INPUT::Key_Backslash},
        {2, 1.0f, "Delete",   INPUT::Key_Delete},
        {2, 1.0f, "End",      INPUT::Key_End},
        {2, 1.0f, "PageD",    INPUT::Key_PageDown},
        {2, 1.0f, "7 Home",   INPUT::Key_Keypad7},
        {2, 1.0f, "8",        INPUT::Key_Keypad8},
        {2, 1.0f, "9 PgUp",   INPUT::Key_Keypad9},
        {2, 1.0f, "+",        INPUT::Key_KeypadAdd},

        {3, 1.75f, "CapsLK",  INPUT::Key_CapsLock},
        {3, 1.0f, "A",        INPUT::Key_A},
        {3, 1.0f, "S",        INPUT::Key_S},
        {3, 1.0f, "D",        INPUT::Key_D},
        {3, 1.0f, "F",        INPUT::Key_F},
        {3, 1.0f, "G",        INPUT::Key_G},
        {3, 1.0f, "H",        INPUT::Key_H},
        {3, 1.0f, "J",        INPUT::Key_J},
        {3, 1.0f, "K",        INPUT::Key_K},
        {3, 1.0f, "L",        INPUT::Key_L},
        {3, 1.0f, "; :",      INPUT::Key_Semicolon},
        {3, 1.0f, "' """,     INPUT::Key_Apostrophe},
        {3, 2.25f, "Enter",   INPUT::Key_Enter},
        {3, 3.0f, "",         INPUT::Key_None},
        {3, 1.0f, "4",        INPUT::Key_Keypad4},
        {3, 1.0f, "5",        INPUT::Key_Keypad5},
        {3, 1.0f, "6",        INPUT::Key_Keypad6},

        {4, 2.25f, "Shift",   INPUT::Key_LeftShift},
        {4, 1.0f, "Z",        INPUT::Key_Z},
        {4, 1.0f, "X",        INPUT::Key_X},
        {4, 1.0f, "C",        INPUT::Key_C},
        {4, 1.0f, "V",        INPUT::Key_V},
        {4, 1.0f, "B",        INPUT::Key_B},
        {4, 1.0f, "N",        INPUT::Key_N},
        {4, 1.0f, "M",        INPUT::Key_M},
        {4, 1.0f, ", <",      INPUT::Key_Comma},
        {4, 1.0f, ". >",      INPUT::Key_Period},
        {4, 1.0f, "/ ?",      INPUT::Key_Slash},
        {4, 2.75f, "Shift",   INPUT::Key_RightShift},
        {4, 1.0f, "",         INPUT::Key_None},
        {4, 1.0f, "Up",       INPUT::Key_UpArrow},
        {4, 1.0f, "",         INPUT::Key_None},
        {4, 1.0f, "1 End",    INPUT::Key_Keypad1},
        {4, 1.0f, "2",        INPUT::Key_Keypad2},
        {4, 1.0f, "3 PgDn",   INPUT::Key_Keypad3},
        {4, 1.0f, "Enter",    INPUT::Key_KeypadEnter},
        
        {5, 1.0f, "Ctrl",     INPUT::Key_LeftCtrl},
        {5, 1.0f, ":)",       INPUT::Key_LeftSuper},
        {5, 1.0f, "Alt",      INPUT::Key_LeftAlt},
        {5, 8.0f, "Spacebar", INPUT::Key_Space},
        {5, 1.0f, "Alt",      INPUT::Key_RightAlt},
        {5, 1.0f, ":D",       INPUT::Key_RightSuper},
        {5, 1.0f, "Menu",     INPUT::Key_Menu},
        {5, 1.0f, "Ctrl",     INPUT::Key_RightCtrl},
        {5, 1.0f, "Left",     INPUT::Key_LeftArrow},
        {5, 1.0f, "Down",     INPUT::Key_DownArrow},
        {5, 1.0f, "Right",    INPUT::Key_RightArrow},
        {5, 2.0f, "0 Ins",    INPUT::Key_Keypad0},
        {5, 1.0f, ". Del",    INPUT::Key_KeypadDecimal},
    };
    UI::Dummy(board_max - board_min);
    if (!UI::IsItemVisible()) return;
    draw_list->PushClipRect(board_min, board_max, true);
    for (c32 n = 0; n < IM_COUNTOF(keys_to_display); n++) {
        const KeyLayoutData* key_data = &keys_to_display[n];
        if (key_data->Row != current_row) { current_row = key_data->Row; x = start_pos.x; };
        float h = (key_data->Key == INPUT::Key_KeypadAdd || key_data->Key == INPUT::Key_KeypadEnter) ? key_size.y * 2 : key_size.y;
        v2 key_min = v2(x, start_pos.y + (float)key_data->Row * key_size.y);
        v2 key_max = key_min + v2(key_size.x * key_data->Width, h);
        if (key_data->Key != INPUT::Key_None) {
            draw_list->AddRectFilled(key_min, key_max, UI::GetColorU32(style.Colors[22]), key_rounding);
            draw_list->AddRect(key_min, key_max, UI::GetColorU32(style.Colors[5]), key_rounding);
        };
        v2 label_min = v2(key_min.x + key_label_pos.x, key_min.y + key_label_pos.y);
        draw_list->AddText(label_min, UI::GetColorU32(style.Colors[0]), key_data->Label);
        if (key_data->Key != INPUT::Key_None && UI::IsKeyDown(key_data->Key)) {
            draw_list->AddRectFilled(key_min, key_max, UI::GetColorU32(style.Colors[24]), key_rounding);
            draw_list->AddRect(key_min, key_max, UI::GetColorU32(style.Colors[5]), key_rounding);
            draw_list->AddText(label_min, UI::GetColorU32(style.Colors[0]), key_data->Label);
        }
        x += key_size.x * key_data->Width;
    }
    draw_list->PopClipRect();
}
template<typename Function>
void settingOption(const c8* c, c1* d, c1* s, Function f) {
    if (UI::BeginTable(c, 3, uiTableFlags_SizingStretchProp, v2(), 0, &settingsFilter)) {
        #if !AUR_DEBUG || !AUR_RELEASE
        static const std::string dL = "Debug##" + std::string(c);
        static const std::string rL = "Ship##"  + std::string(c);
        UI::TableSetupColumn("D", uiTableColumnFlags_WidthFixed);
        UI::TableSetupColumn("S", uiTableColumnFlags_WidthFixed);
        #endif
        UI::TableSetupColumn("T", uiTableColumnFlags_WidthStretch);
        UI::TableNextRow();
        #if !AUR_DEBUG || !AUR_RELEASE
        UI::TableNextColumn();
        UI::Checkbox(dL.c_str(), d);
        UI::TableNextColumn();
        UI::Checkbox(rL.c_str(), s);
        #endif
        UI::TableNextColumn();
        f();
        UI::EndTable();
    }
}
c8 graphicsOpt0[16] = "0x4E554C4C";
c8 graphicsOpt1[16] = "Low";
c8 graphicsOpt2[16] = "Medium";
c8 graphicsOpt3[16] = "High";
c8 graphicsOpt4[16] = "Ultra";
template<typename Basic, typename Low, typename Medium, typename High, typename Ultra>
void videoOption(cc8* label, c32& option, Basic&& basic, Low&& low, Medium&& medium, High&& high, Ultra&& ultra) {
    c8 i[64];
    std::snprintf(i, sizeof(i), "##%s", label);
    if (UI::BeginTable(i, 6, uiTableFlags_SizingStretchSame, v2(), 0, &settingsFilter)) {
        UI::TableNextRow();
        UI::TableNextColumn();
        UI::BeginDisabled(option == 0);
        if (UI::Button(graphicsOpt0, v2(-f32_MIN, 0))) basic();
        UI::EndDisabled();
        UI::TableNextColumn();
        UI::BeginDisabled(option == 1);
        if (UI::Button(graphicsOpt1, v2(-f32_MIN, 0))) low();
        UI::EndDisabled();
        UI::TableNextColumn();
        UI::BeginDisabled(option == 2);
        if (UI::Button(graphicsOpt2, v2(-f32_MIN, 0))) medium();
        UI::EndDisabled();
        UI::TableNextColumn();
        UI::BeginDisabled(option == 3);
        if (UI::Button(graphicsOpt3, v2(-f32_MIN, 0))) high();
        UI::EndDisabled();
        UI::TableNextColumn();
        UI::BeginDisabled(option == 4);
        if (UI::Button(graphicsOpt4, v2(-f32_MIN, 0))) ultra();
        UI::EndDisabled();
        UI::TableNextColumn();
        UI::TextUnformatted(label);
        UI::EndTable();
    };
}
void Settings() {
    uiStyle& style = UI::GetStyle();
    c1 sActive = UI::Begin("Settings", NULL, uiWindowFlags_MenuBar | uiWindowFlags_NoTitleBar | uiWindowFlags_NoMove | uiWindowFlags_NoResize | uiWindowFlags_NoCollapse );
    if (UI::BeginMenuBar()) {
        if (UI::MenuItem("Collapse")) engineHeaderOpen = 0;
        if (UI::MenuItem("Expand"))   engineHeaderOpen = 1;
        UI::SetNextItemWidth(-f32_MIN);
        settingsFilter.Draw("##engineFilter", "Type to search...");
        UI::EndMenuBar();
    };
    #if AUR_RELEASE
    uiViewport* vp = UI::GetMainViewport();
    const f32 pad = 75.0f;
    UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Always, v2(0.5f, 0.5f));
    UI::SetNextWindowSize(UI::GetMainViewport()->WorkSize - v2(pad * 2.0f, pad * 2.0f), uiCond_Always);
    UI::Begin("Settings##Gameplay", nullptr, uiWindowFlags_NoResize | uiWindowFlags_NoCollapse | uiWindowFlags_NoTitleBar);
    const f32 footer = UI::GetFrameHeightWithSpacing();
    if (UI::BeginChild("Content", v2(0, -footer), false))
    #endif
    if (UI::BeginTabBar("MyTabBar")) {
        if (UI::BeginTabItem("Gameplay")) {
            UI::SetNextItemWidth(-f32_MIN);
            settingsFilter.Draw("##gameplayFilter", "Type to search...");
            UI::SliderFloat("Screen Resolution", &camera.fov, 45.0f, 120.0f, "%.3f", &settingsFilter, aur.sliderFlags);
            UI::SliderFloat("Screen Percentage", &camera.fov, 45.0f, 120.0f, "%.3f", &settingsFilter, aur.sliderFlags);
            UI::Combo("Screen Mode",       (c32*)&aur.screenMode, "Windowed\0Borderless\0Fullscreen\0", &settingsFilter);
            UI::SliderFloat("Field of View",     &camera.fov, 45.0f, 120.0f, "%.3f", &settingsFilter, aur.sliderFlags);
            UI::SliderFloat("Mouse Sensitivity", &camera.sensitivity, 1.0f, 100.0f, "%.3f", &settingsFilter, aur.sliderFlags);
            if (UI::TreeNode("Accessibility##I")) {
                settingOption("Quick Save Saver", &debug, &ship, []{
                    UI::Checkbox("Quick Save Saver Enabled##QSS", &aur.autoLoad);
                    UI::SliderFloat("QuickSave Saver Timer##CS", &camera.sensitivity, 1.0f, 60.0f, "%.3f", 0, aur.sliderFlags);
                });
                UI::TreePop();
            };
            UI::EndTabItem();
        }
        if (UI::BeginTabItem("Audio")) {
            UI::SetNextItemWidth(-f32_MIN);
            settingsFilter.Draw("##audioFilter", "Type to search...");
            if (UI::TreeNode("Volume")) {
                UI::SliderFloat("Master Volume",  &camera.fov, 0.0f, 100.0f, "%.2f", &settingsFilter, aur.sliderFlags);
                UI::SliderFloat("Music",          &camera.fov, 0.0f, 100.0f, "%.2f", &settingsFilter, aur.sliderFlags);
                UI::SliderFloat("Ambiental",      &camera.fov, 0.0f, 100.0f, "%.2f", &settingsFilter, aur.sliderFlags);
                UI::SliderFloat("Sound Effects",  &camera.fov, 0.0f, 100.0f, "%.2f", &settingsFilter, aur.sliderFlags);
                UI::SliderFloat("User Interface", &camera.fov, 0.0f, 100.0f, "%.2f", &settingsFilter, aur.sliderFlags);
                settingOption("Dialog", &debug, &ship, []{
                    UI::SliderFloat("Dialog##DV", &camera.fov, 0.0f, 100.0f, "%.2f", 0, aur.sliderFlags);
                });
                settingOption("Background NPC's", &debug, &ship, []{
                    UI::SliderFloat("Background NPC's##BNV", &camera.fov, 0.0f, 100.0f, "%.2f", 0, aur.sliderFlags);
                });
                UI::TreePop();
            };
            if (UI::TreeNode("Accessibility##I")) {
                UI::TreePop();
            };
            UI::EndTabItem();
        }
        if (UI::BeginTabItem("Video")) {
            UI::SetNextItemWidth(-f32_MIN);
            settingsFilter.Draw("##videoFilter", "Type to search...");
            #if !AUR_RELEASE
            UI::InputText("Option 1", "graphicsOpt0", graphicsOpt0, sizeof(graphicsOpt0));
            UI::InputText("Option 2", "graphicsOpt1", graphicsOpt1, sizeof(graphicsOpt1));
            UI::InputText("Option 3", "graphicsOpt2", graphicsOpt2, sizeof(graphicsOpt2));
            UI::InputText("Option 4", "graphicsOpt3", graphicsOpt3, sizeof(graphicsOpt3));
            UI::InputText("Option 5", "graphicsOpt4", graphicsOpt4, sizeof(graphicsOpt4));
            #endif
            if (UI::TreeNode("Graphics")) {
                videoOption("Presets", PROJECT::Graphics::Presets,
                    // basic
                    [&]{PROJECT::Graphics::Presets            = 0;
                        PROJECT::Graphics::ViewDistance       = 0;
                        PROJECT::Graphics::AntiAliasing       = 0;
                        PROJECT::Graphics::PostProcessing     = 0;
                        PROJECT::Graphics::Shadows            = 0;
                        PROJECT::Graphics::GlobalIllumination = 0;
                        PROJECT::Graphics::Reflections        = 0;
                        PROJECT::Graphics::Textures           = 0;
                        PROJECT::Graphics::Effects            = 0;
                        PROJECT::Graphics::Foliage            = 0;
                        PROJECT::Graphics::Shading            = 0;
                        PROJECT::Graphics::Landscape          = 0;
                    },
                    // low
                    [&]{PROJECT::Graphics::Presets            = 1;
                        PROJECT::Graphics::ViewDistance       = 1;
                        PROJECT::Graphics::AntiAliasing       = 1;
                        PROJECT::Graphics::PostProcessing     = 1;
                        PROJECT::Graphics::Shadows            = 1;
                        PROJECT::Graphics::GlobalIllumination = 1;
                        PROJECT::Graphics::Reflections        = 1;
                        PROJECT::Graphics::Textures           = 1;
                        PROJECT::Graphics::Effects            = 1;
                        PROJECT::Graphics::Foliage            = 1;
                        PROJECT::Graphics::Shading            = 1;
                        PROJECT::Graphics::Landscape          = 1;
                    },
                    // medium
                    [&]{PROJECT::Graphics::Presets            = 2;
                        PROJECT::Graphics::ViewDistance       = 2;
                        PROJECT::Graphics::AntiAliasing       = 2;
                        PROJECT::Graphics::PostProcessing     = 2;
                        PROJECT::Graphics::Shadows            = 2;
                        PROJECT::Graphics::GlobalIllumination = 2;
                        PROJECT::Graphics::Reflections        = 2;
                        PROJECT::Graphics::Textures           = 2;
                        PROJECT::Graphics::Effects            = 2;
                        PROJECT::Graphics::Foliage            = 2;
                        PROJECT::Graphics::Shading            = 2;
                        PROJECT::Graphics::Landscape          = 2;
                    },
                    // high
                    [&]{PROJECT::Graphics::Presets            = 3;
                        PROJECT::Graphics::ViewDistance       = 3;
                        PROJECT::Graphics::AntiAliasing       = 3;
                        PROJECT::Graphics::PostProcessing     = 3;
                        PROJECT::Graphics::Shadows            = 3;
                        PROJECT::Graphics::GlobalIllumination = 3;
                        PROJECT::Graphics::Reflections        = 3;
                        PROJECT::Graphics::Textures           = 3;
                        PROJECT::Graphics::Effects            = 3;
                        PROJECT::Graphics::Foliage            = 3;
                        PROJECT::Graphics::Shading            = 3;
                        PROJECT::Graphics::Landscape          = 3;
                    },
                    // ultra
                    [&]{PROJECT::Graphics::Presets            = 4;
                        PROJECT::Graphics::ViewDistance       = 4;
                        PROJECT::Graphics::AntiAliasing       = 4;
                        PROJECT::Graphics::PostProcessing     = 4;
                        PROJECT::Graphics::Shadows            = 4;
                        PROJECT::Graphics::GlobalIllumination = 4;
                        PROJECT::Graphics::Reflections        = 4;
                        PROJECT::Graphics::Textures           = 4;
                        PROJECT::Graphics::Effects            = 4;
                        PROJECT::Graphics::Foliage            = 4;
                        PROJECT::Graphics::Shading            = 4;
                        PROJECT::Graphics::Landscape          = 4;
                    }
                );
                videoOption("View Distance", PROJECT::Graphics::ViewDistance,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::ViewDistance = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::ViewDistance = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::ViewDistance = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::ViewDistance = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::ViewDistance = 4; // ultra
                    }
                );
                videoOption("Anti-Aliasing", PROJECT::Graphics::AntiAliasing,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::AntiAliasing = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::AntiAliasing = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::AntiAliasing = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::AntiAliasing = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::AntiAliasing = 4; // ultra
                    }
                );
                videoOption("Post Processing", PROJECT::Graphics::PostProcessing,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::PostProcessing = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::PostProcessing = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::PostProcessing = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::PostProcessing = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::PostProcessing = 4; // ultra
                    }
                );
                videoOption("Shadows", PROJECT::Graphics::Shadows,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shadows = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shadows = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shadows = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shadows = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shadows = 4; // ultra
                    }
                );
                videoOption("Global Illumination", PROJECT::Graphics::GlobalIllumination,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::GlobalIllumination = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::GlobalIllumination = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::GlobalIllumination = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::GlobalIllumination = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::GlobalIllumination = 4; // ultra
                    }
                );
                videoOption("Reflections", PROJECT::Graphics::Reflections,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Reflections = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Reflections = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Reflections = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Reflections = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Reflections = 4; // ultra
                    }
                );
                videoOption("Textures", PROJECT::Graphics::Textures,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Textures = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Textures = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Textures = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Textures = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Textures = 4; // ultra
                    }
                );
                videoOption("Effects", PROJECT::Graphics::Effects,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Effects = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Effects = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Effects = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Effects = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Effects = 4; // ultra
                    }
                );
                videoOption("Foliage", PROJECT::Graphics::Foliage,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Foliage = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Foliage = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Foliage = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Foliage = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Foliage = 4; // ultra
                    }
                );
                videoOption("Shading", PROJECT::Graphics::Shading,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shading = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shading = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shading = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shading = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Shading = 4; // ultra
                    }
                );
                videoOption("Landscape", PROJECT::Graphics::Landscape,
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Landscape = 0; // basic
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Landscape = 1; // low
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Landscape = 2; // medium
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Landscape = 3; // high
                    },
                    [&]{PROJECT::Graphics::Presets = -1; PROJECT::Graphics::Landscape = 4;// ultra
                    }
                );
                UI::TreePop();
            };
            if (UI::TreeNode("Post Process")) {
                UI::TreePop();
            };
            if (UI::TreeNode("Accessibility##I")) {
                UI::TreePop();
            };
            UI::EndTabItem();
        }
        if (UI::BeginTabItem("User Interface")) {
            UI::SetNextItemWidth(-f32_MIN);
            settingsFilter.Draw("##inputFilter", "Type to search...");
            if (UI::TreeNode("Accessibility##I")) {
                UI::TreePop();
            };
            UI::EndTabItem();
        }
        if (UI::BeginTabItem("Input")) {
            UI::SetNextItemWidth(-f32_MIN);
            settingsFilter.Draw("##inputFilter", "Type to search...");
            #if !AUR_RELEASE
            renderKeyboard(UI::GetWindowDrawList());
            #endif
            if (UI::TreeNode("Key Binds")) {
                if (UI::TreeNode("Gameplay##KB")) {
                    settingOption("Forward", &debug, &ship, []{ // W
                        UI::Button("W##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Forward", "Forward", sPath, sizeof(sPath));
                    });
                    settingOption("Backward", &debug, &ship, []{ // S
                        UI::Button("S##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Backward", "Backward", sPath, sizeof(sPath));
                    });
                    settingOption("Left", &debug, &ship, []{ // A
                        UI::Button("A##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Left", "Left", sPath, sizeof(sPath));
                    });
                    settingOption("Right", &debug, &ship, []{ // D
                        UI::Button("D##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Right", "Right", sPath, sizeof(sPath));
                    });
                    settingOption("Run", &debug, &ship, []{ // Left-Shift
                        UI::Button("Left-Shift##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Run", "Run", sPath, sizeof(sPath));
                    });
                    settingOption("Jump", &debug, &ship, [] { // Space
                        UI::Button("Spacebar##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Jump", "Jump", sPath, sizeof(sPath));
                    });
                    settingOption("Crouch", &debug, &ship, []{ // Left-Ctrl
                        UI::Button("Left-Ctrl##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Crouch", "Crouch", sPath, sizeof(sPath));
                    });
                    settingOption("Interact", &debug, &ship, []{ // E
                        UI::Button("E##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Interact", "Interact", sPath, sizeof(sPath));
                    });
                    settingOption("Reload", &debug, &ship, []{ // R
                        UI::Button("R##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Reload", "Reload", sPath, sizeof(sPath));
                    });
                    settingOption("Flashlight", &debug, &ship, []{ // F
                        UI::Button("F##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Flashlight", "Flashlight", sPath, sizeof(sPath));
                    });
                    settingOption("Grenade", &debug, &ship, []{ // G
                        UI::Button("G##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Grenade", "Grenade", sPath, sizeof(sPath));
                    });
                    UI::TreePop();
                };
                if (UI::TreeNode("Technical##KB")) {
                    settingOption("Quick Save", &debug, &ship, []{ // 0
                        UI::Button("0##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Quick Save", "Quick Save", sPath, sizeof(sPath));
                    });
                    settingOption("Quick Load", &debug, &ship, []{ // 9
                        UI::Button("9##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Quick Load", "Quick Load", sPath, sizeof(sPath));
                    });
                    settingOption("Menu", &debug, &ship, []{ // Esc
                        UI::Button("Esc##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Menu", "Menu", sPath, sizeof(sPath));
                    });
                    settingOption("Inventory", &debug, &ship, []{ // Tab
                        UI::Button("Tab##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Inventory", "Inventory", sPath, sizeof(sPath));
                    });
                    settingOption("Backpack", &debug, &ship, []{ // B
                        UI::Button("B##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Backpack", "Backpack", sPath, sizeof(sPath));
                    });
                    settingOption("Character", &debug, &ship, []{ // C
                        UI::Button("C##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Character", "Character", sPath, sizeof(sPath));
                    });
                    settingOption("Quests", &debug, &ship, []{ // Q
                        UI::Button("Q##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Quests", "Quests", sPath, sizeof(sPath));
                    });
                    settingOption("Journal", &debug, &ship, []{ // Q
                        UI::Button("J##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Journal", "Journal", sPath, sizeof(sPath));
                    });
                    settingOption("Map", &debug, &ship, []{ // M
                        UI::Button("M##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Map", "Map", sPath, sizeof(sPath));
                    });
                    settingOption("Next Item", &debug, &ship, []{ // Scroll Wheel Up
                        UI::Button("Scroll Wheel Up##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Next Item", "Next Item", sPath, sizeof(sPath));
                    });
                    settingOption("Previous Item", &debug, &ship, []{ // Scroll Wheel Down
                        UI::Button("Scroll Wheel Down##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Next Item", "Next Item", sPath, sizeof(sPath));
                    });
                    settingOption("Cancel Action", &debug, &ship, []{ // X
                        UI::Button("X##k1", v2(250, 0));
                        UI::SameLine();
                        UI::TextUnformatted(sPath);
                        UI::SameLine();
                        UI::SetNextItemWidth((UI::GetContentRegionAvail().x - 100));
                        UI::InputText("Cancel Action", "Cancel", sPath, sizeof(sPath));
                    });
                    UI::TreePop();
                };
                UI::TreePop();
            };
            if (UI::TreeNode("Accessibility##I")) {
                settingOption("Double Click Delay", &debug, &ship, []{
                    UI::SliderFloat("Double Click Delay##MDCT", &INPUT::Settings::MouseDoubleClickDelay, 0.1f, 1.0f, "%.3f");
                });
                settingOption("Key Repeat Delay", &debug, &ship, []{
                    UI::SliderFloat("Key Repeat Delay##KRD", &INPUT::Settings::KeyRepeatDelay, 0.1f, 1.0f, "%.3f");
                });
                UI::TreePop();
            };
            UI::EndTabItem();
        }
        UI::EndTabBar();
    }
    #if AUR_RELEASE
    UI::EndChild();
    if (UI::BeginTable("sColumns", 3, uiTableFlags_SizingStretchSame)) {
        UI::TableNextRow();
        UI::TableNextColumn();
        if (UI::Button("Reset", v2(-f32_MIN, 0)));
        UI::TableNextColumn();
        if (UI::Button("Save", v2(-f32_MIN, 0)));
        UI::TableNextColumn();
        if (UI::Button("Back", v2(-f32_MIN, 0)));
        UI::EndTable();
    };
    UI::End();
    #endif
    #if !AUR_RELEASE
    if (engineHeaderOpen != -1) UI::SetNextItemOpen(engineHeaderOpen == 1, uiCond_Always);
    if (UI::CollapsingHeader("Project")) {
        // UI::InputText("Project Name", "Project Name",       project.name,     sizeof(project.name),     0, 0, 0, &settingsFilter);
        // UI::InputText("Save Data",    "Save Data Location", project.saveData, sizeof(project.saveData), 0, 0, 0, &settingsFilter);
    }
    if (engineHeaderOpen != -1) UI::SetNextItemOpen(engineHeaderOpen == 1, uiCond_Always);
    if (UI::CollapsingHeader("Editor")) {
        if (UI::TreeNode("Misc")) {
            if (UI::Combo("Themes##T", (c32*)&aur.currentTheme, "Dark\0Light\0Classic\0", &settingsFilter)) SwitchTheme(aur.currentTheme);
            UI::Combo("Viewport Panel Location", (c32*)&AUR::Editor::viewportPanel, "Left\0Right\0", &settingsFilter);
            UI::SliderFloat("Digital Mouse Cursor Scale", &INPUT::Settings::MouseCursorScale, 0.1f, 5.0f, "%.3f", &settingsFilter);
            UI::SliderInt("Tooltip Offset##TO", &AUR::Settings::tooltipOffset, -50, 50, "%d", &settingsFilter);
            UI::SetItemTooltip("Tooltip");
            UI::SliderFloat("Hover Delay##HD", &AUR::Settings::hoverDelay, 0.0f, 2.0f, "%.3f", &settingsFilter);
            UI::SetItemTooltip("Delay");
            UI::SliderFloat2("Window PaddingP",                 (f32*)&style.WindowPadding,          0.0f, 20.0f, "%.0f", &settingsFilter);
            UI::SliderFloat2("Display Window Padding",          (f32*)&style.DisplayWindowPadding,   0.0f, 30.0f, "%.0f", &settingsFilter);
            UI::SliderFloat2("Display Safe Area Padding",       (f32*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f", &settingsFilter);
            UI::SliderFloat2("Frame Padding",                   (f32*)&style.FramePadding,           0.0f, 20.0f, "%.0f", &settingsFilter);
            UI::SliderFloat2("Item Spacing",                    (f32*)&style.ItemSpacing,            0.0f, 20.0f, "%.0f", &settingsFilter);
            UI::SliderFloat2("Item Inner Spacing",              (f32*)&style.ItemInnerSpacing,       0.0f, 20.0f, "%.0f", &settingsFilter);
            UI::SliderFloat2("Touch Extra Padding",             (f32*)&style.TouchExtraPadding,      0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::SliderFloat ("Scrollbar Rounding",                    &style.ScrollbarRounding,      0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat ("Indent Spacing",                        &style.IndentSpacing,          0.0f, 30.0f, "%.0f", &settingsFilter);
            UI::SliderFloat ("Grab Min Size",                         &style.GrabMinSize,            1.0f, 20.0f, "%.0f", &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Border")) {
            UI::SliderFloat("Window Border Size",                     &style.WindowBorderSize,       0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Child Border Size",                      &style.ChildBorderSize,        0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Popup Border Size",                      &style.PopupBorderSize,        0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Frame Border Size",                      &style.FrameBorderSize,        0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Scrollbar Size",                         &style.ScrollbarSize,          1.0f, 20.0f, "%.0f", &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Rounding")) {
            UI::SliderFloat("Window Rounding",                        &style.WindowRounding,         0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Child Rounding",                         &style.ChildRounding,          0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Frame Rounding",                         &style.FrameRounding,          0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Popup Rounding",                         &style.PopupRounding,          0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Grab Rounding",                          &style.GrabRounding,           0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Tab Rounding",                           &style.TabRounding,            0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Image Rounding",                         &style.ImageRounding,          0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Scrollbar Padding",                      &style.ScrollbarPadding,       0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Tabs")) {
            UI::SliderFloat("Tab Border Size",                        &style.TabBorderSize,          0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Tab Bar Border Size",                    &style.TabBarBorderSize,       0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::SliderFloat("Tab Bar Overline Size",                  &style.TabBarOverlineSize,     0.0f, 10.0f, "%.0f", &settingsFilter);
            UI::DragFloat("Tab Min Width Base",                       &style.TabMinWidthBase,        0.5f,  1.0f, 500.0f, "%.0f", &settingsFilter);
            UI::DragFloat("Tab Min Width Shrink",                     &style.TabMinWidthShrink,      0.5f,  1.0f, 500.0f, "%.0f", &settingsFilter);
            UI::DragFloat("Tab Close Button Min Width Selected",      &style.TabCloseButtonMinWidthSelected,   0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthSelected < 0.0f)   ? "%.0f (Always)" : "%.0f", &settingsFilter);
            UI::DragFloat("Tab Close Button Min Width Unselected",    &style.TabCloseButtonMinWidthUnselected, 0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthUnselected < 0.0f) ? "%.0f (Always)" : "%.0f", &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Tables")) {
            UI::SliderFloat2("Cell Padding",                    (f32*)&style.CellPadding,                 0.0f,  20.0f, "%.0f", &settingsFilter);
            UI::SliderAngle ("Table Angled Headers Angle",            &style.TableAngledHeadersAngle,   -50.0f, +50.0f, "%.0f", &settingsFilter);
            UI::SliderFloat2("Table Angled Headers Text Align", (f32*)&style.TableAngledHeadersTextAlign, 0.0f,   1.0f, "%.2f", &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Window")) {
            UI::SliderFloat2("Window Title Align",              (f32*)&style.WindowTitleAlign,         0.0f,  1.0f, "%.2f", &settingsFilter);
            UI::SliderFloat("Window Border Hover Padding",            &style.WindowBorderHoverPadding, 1.0f, 20.0f, "%.0f", &settingsFilter);
            int window_menu_button_position = style.WindowMenuButtonPosition + 1;
            UI::Combo("Window Menu Button Position",            (c32*)&window_menu_button_position, "None\0Left\0Right\0", &settingsFilter);
            style.WindowMenuButtonPosition = (VAR::Dir)(window_menu_button_position - 1);
            UI::TreePop();
        }
        if (UI::TreeNode("Widgets")) {
            UI::SliderFloat2("Button Text Align",               (f32*)&style.ButtonTextAlign,     0.0f,  1.0f, "%.2f", &settingsFilter);
            UI::SliderFloat2("Selectable Text Align",           (f32*)&style.SelectableTextAlign, 0.0f,  1.0f, "%.2f", &settingsFilter);
            UI::SliderFloat2("Separator Text Align",            (f32*)&style.SeparatorTextAlign,  0.0f,  1.0f, "%.2f", &settingsFilter);
            UI::SliderFloat("Log Slider Deadzone",                    &style.LogSliderDeadzone,   0.0f, 12.0f, "%.0f", &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Sliders")) {
            UI::CheckboxFlags("Slider Color Marker Enabled",          &aur.sliderFlags, uiSliderFlags_ColorMarkers,    &settingsFilter);
            UI::SliderFloat  ("Slider Color Marker Size", &AUR::Editor::colorMarkerSize, 0.1f, 20.0f, 0,   &settingsFilter);
            UI::Combo        ("Slider Color Marker Position", (c32*)&AUR::Editor::colorMarkerPosition, "Left\0Right\0", &settingsFilter);
            UI::CheckboxFlags("Slider Always Clamp",                  &aur.sliderFlags, uiSliderFlags_AlwaysClamp,     &settingsFilter);
            UI::CheckboxFlags("Slider Clamp On Input",                &aur.sliderFlags, uiSliderFlags_ClampOnInput,    &settingsFilter);
            UI::CheckboxFlags("Slider Clamp Zero Range",              &aur.sliderFlags, uiSliderFlags_ClampZeroRange,  &settingsFilter);
            UI::CheckboxFlags("Slider Clamp No Round To Format",      &aur.sliderFlags, uiSliderFlags_NoRoundToFormat, &settingsFilter);
            UI::CheckboxFlags("Slider Clamp No Speed Tweaks",         &aur.sliderFlags, uiSliderFlags_NoSpeedTweaks,   &settingsFilter);
            UI::CheckboxFlags("Slider Clamp Wrap Around",             &aur.sliderFlags, uiSliderFlags_WrapAround,      &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Anti-Aliasing")) {
            UI::Checkbox("Anti-Aliasing Lines", &AUR::Settings::antiAliasedLines, &settingsFilter);
            UI::SetItemTooltip("When disabling anti-aliasing lines, you'll probably want to disable borders as well.");
            UI::Checkbox("Anti-Aliasing Lines Use Texture", &AUR::Settings::antiAliasedLinesUseTex, &settingsFilter);
            UI::SetItemTooltip("Faster lines using texture data. Require backend to render with bilinear filtering (not point/nearest filtering).");
            UI::Checkbox("Anti-Aliasing Fill", &AUR::Settings::antiAliasedFill, &settingsFilter);
            UI::TreePop();
        }
        if (UI::TreeNode("Terminal")) {
            UI::Checkbox("Terminal [NOTIF]",   &AUR::Editor::terminalNOTIF,   &settingsFilter);
            UI::Checkbox("Terminal [WARNING]", &AUR::Editor::terminalWARNING, &settingsFilter);
            UI::Checkbox("Terminal [ERROR]",   &AUR::Editor::terminalERROR,   &settingsFilter);
            UI::TreePop();
        }
    }
    #endif
    engineHeaderOpen = -1;
    UI::End();
    if (sActive &&
        UI::IsKeyDown(INPUT::Key_LeftCtrl) &&
        UI::IsKeyDown(INPUT::Key_LeftShift) &&
        UI::IsKeyPressed(INPUT::Key_H, false))  { sPopup = !sPopup; if (sPopup) UI::OpenPopup("Help##S"); };
    UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Appearing, v2(0.5f, 0.5f));
    if (sPopup) UI::OpenPopup("Help##S");
    if (UI::BeginPopupModal("Help##S", &sPopup, uiWindowFlags_AutoResize | uiWindowFlags_NoMove)) {
        UI::Text("Debug: Make the setting visible in the Debug build");
        UI::Text(" Ship: Make the setting visible in the Release build");
        UI::Separator();
        UI::Text("Some settings cannot be hidden.");
        UI::Text("If you wanna be a pos modify the source code, fu.");
        UI::EndPopup();
    }
}