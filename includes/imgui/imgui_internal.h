// [SECTION] Header mess
// [SECTION] Forward declarations
// [SECTION] Context pointer
// [SECTION] STB libraries includes
// [SECTION] Macros
// [SECTION] Generic helpers
// [SECTION] ImDrawList support
// [SECTION] Style support
// [SECTION] Data types support
// [SECTION] Widgets support: flags, enums, data structures
// [SECTION] Popup support
// [SECTION] Inputs support
// [SECTION] Clipper support
// [SECTION] Navigation support
// [SECTION] Typing-select support
// [SECTION] Columns support
// [SECTION] Box-select support
// [SECTION] Multi-select support
// [SECTION] Docking support
// [SECTION] Viewport support
// [SECTION] Settings support
// [SECTION] Localization support
// [SECTION] Error handling, State recovery support
// [SECTION] Metrics, Debug tools
// [SECTION] Generic context hooks
// [SECTION] uiContext (main imgui context)
// [SECTION] uiWindowTempData, uiWindow
// [SECTION] Tab bar, Tab item support
// [SECTION] Table support
// [SECTION] UI internal API
// [SECTION] ImFontLoader
// [SECTION] ImFontAtlas internal API
// [SECTION] Test Engine specific hooks (imgui_test_engine)
#pragma once
#ifndef IMGUI_DISABLE
//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------
#ifndef IMGUI_VERSION
#include "imgui.h"
#endif
#include <stdio.h>  // FILE*, sscanf
#include <stdlib.h> // NULL, malloc, free, qsort, atoi, atof
#include <math.h>   // sqrtf, fabsf, fmodf, powf, floorf, ceilf, cosf, sinf
#include <limits.h> // INT_MIN, INT_MAX
#include "variables.h"
// Enable SSE intrinsics if available
#if (defined __SSE__ || defined __x86_64__ || defined _M_X64 || (defined(_M_IX86_FP) && (_M_IX86_FP >= 1))) && !defined(IMGUI_DISABLE_SSE) && !defined(_M_ARM64) && !defined(_M_ARM64EC)
#define IMGUI_ENABLE_SSE
#include <immintrin.h>
#if (defined __AVX__ || defined __SSE4_2__)
#define IMGUI_ENABLE_SSE4_2
#include <nmmintrin.h>
#endif
#endif
// Emscripten has partial SSE 4.2 support where _mm_crc32_u32 is not available. See https://emscripten.org/docs/porting/simd.html#id11 and #8213
#if defined(IMGUI_ENABLE_SSE4_2) && !defined(IMGUI_USE_LEGACY_CRC32_ADLER) && !defined(__EMSCRIPTEN__)
#define IMGUI_ENABLE_SSE4_2_CRC
#endif
// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4251)  // class 'xxx' needs to have dll-interface to be used by clients of struct 'xxx' // when IMGUI_API is set to__declspec(dllexport)
#pragma warning (disable: 26495) // [Static Analyzer] Variable 'XXX' is uninitialized. Always initialize a member variable (type.6).
#pragma warning (disable: 26812) // [Static Analyzer] The enum type 'xxx' is unscoped. Prefer 'enum class' over 'enum' (Enum.3).
#if defined(_MSC_VER) && _MSC_VER >= 1922 // MSVC 2019 16.2 or later
#pragma warning (disable: 5054)  // operator '|': deprecated between enumerations of different types
#endif
#endif
// Clang/GCC warnings with -Weverything
#if defined(__clang__)
#pragma clang diagnostic push
#if __has_warning("-Wunknown-warning-option")
#pragma clang diagnostic ignored "-Wunknown-warning-option"         // warning: unknown warning group 'xxx'
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"                // warning: unknown warning group 'xxx'
#pragma clang diagnostic ignored "-Wfloat-equal"                    // warning: comparing floating point with == or != is unsafe // storing and comparing against same constants ok, for ImFloor()
#pragma clang diagnostic ignored "-Wold-style-cast"                 // warning: use of old-style cast
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"  // warning: zero as null pointer constant
#pragma clang diagnostic ignored "-Wdouble-promotion"               // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma clang diagnostic ignored "-Wimplicit-int-float-conversion"  // warning: implicit conversion from 'xxx' to 'float' may lose precision
#pragma clang diagnostic ignored "-Wmissing-noreturn"               // warning: function 'xxx' could be declared with attribute 'noreturn'
#pragma clang diagnostic ignored "-Wdeprecated-enum-enum-conversion"// warning: bitwise operation between different enumeration types ('XXXFlags_' and 'XXXFlagsPrivate_') is deprecated
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"            // warning: 'xxx' is an unsafe pointer used for buffer access
#pragma clang diagnostic ignored "-Wnontrivial-memaccess"           // warning: first argument in call to 'memset' is a pointer to non-trivially copyable type
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"                          // warning: unknown option after '#pragma GCC diagnostic' kind
#pragma GCC diagnostic ignored "-Wfloat-equal"                      // warning: comparing floating-point with '==' or '!=' is unsafe
#pragma GCC diagnostic ignored "-Wclass-memaccess"                  // [__GNUC__ >= 8] warning: 'memset/memcpy' clearing/writing an object of type 'xxxx' with no trivial copy-assignment; use assignment or value-initialization instead
#pragma GCC diagnostic ignored "-Wdeprecated-enum-enum-conversion"  // warning: bitwise operation between different enumeration types ('XXXFlags_' and 'XXXFlagsPrivate_') is deprecated
#pragma GCC diagnostic ignored "-Wsign-conversion"                  // warning: conversion to 'xxxx' from 'xxxx' may change the sign of the result
#endif
// Legacy defines
#ifdef IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS // Renamed in 1.74
#error Use IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS
#endif
#ifdef IMGUI_DISABLE_MATH_FUNCTIONS // Renamed in 1.74
#error Use IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
#endif
// Enable stb_truetype by default unless FreeType is enabled.
// You can compile with both by defining both IMGUI_ENABLE_FREETYPE and IMGUI_ENABLE_STB_TRUETYPE together.
#ifndef IMGUI_ENABLE_FREETYPE
#define IMGUI_ENABLE_STB_TRUETYPE
#endif
//-----------------------------------------------------------------------------
// [SECTION] Forward declarations
//-----------------------------------------------------------------------------
// Utilities
// (other types which are not forwarded declared are: ImBitArray<>, ImSpan<>, ImSpanAllocator<>, ImStableVector<>, ImPool<>, ImChunkStream<>)
struct ImBitVector; // Store 1-bit per value
struct ImRect;      // An axis-aligned rectangle (2 points)
struct uiTextIndex; // Maintain a line index for a text buffer.
// ImDrawList/ImFontAtlas
struct ImDrawDataBuilder;          // Helper to build a ImDrawData instance
struct ImDrawListSharedData;       // Data shared between all ImDrawList instances
struct ImFontAtlasBuilder;         // Internal storage for incrementally packing and building a ImFontAtlas
struct ImFontAtlasPostProcessData; // Data available to potential texture post-processing functions
struct ImFontAtlasRectEntry;       // Packed rectangle lookup entry
// ImGui
struct uiBoxSelectState;          // Box-selection state (currently used by multi-selection, could potentially be used by others)
struct uiColorMod;                // Stacked color modifier, backup of modified data so we can restore it
struct uiContext;                 // Main Dear ImGui context
struct uiContextHook;             // Hook for extensions like uiTestEngine
struct uiDataTypeInfo;            // Type information associated to a uiDataType enum
struct uiDeactivatedItemData;     // Data for IsItemDeactivated()/IsItemDeactivatedAfterEdit() function.
struct uiDockContext;             // Docking system context
struct uiDockRequest;             // Docking system dock/undock queued request
struct uiDockNode;                // Docking system node (hold a list of Windows OR two child dock nodes)
struct uiDockNodeSettings;        // Storage for a dock node in .ini file (we preserve those even if the associated dock node isn't active during the session)
struct uiErrorRecoveryState;      // Storage of stack sizes for error handling and recovery
struct uiGroupData;               // Stacked storage data for BeginGroup()/EndGroup()
struct uiInputTextState;          // Internal state of the currently focused/edited text input box
struct uiInputTextDeactivateData; // Short term storage to backup text of a deactivating InputText() while another is stealing active id
struct uiLastItemData;            // Status storage for last submitted items
struct uiLocEntry;                // A localization entry.
struct uiMenuColumns;             // Simple column measurement, currently used for MenuItem() only
struct uiMultiSelectState;        // Multi-selection persistent state (for focused selection).
struct uiMultiSelectTempData;     // Multi-selection temporary state (while traversing).
struct uiNavItemData;             // Result of a keyboard/gamepad directional navigation move query result
struct uiMetricsConfig;           // Storage for ShowMetricsWindow() and DebugNodeXXX() functions
struct uiNextWindowData;          // Storage for SetNextWindow** functions
struct uiNextItemData;            // Storage for SetNextItem** functions
struct uiOldColumnData;           // Storage data for a single column for legacy Columns() api
struct uiOldColumns;              // Storage data for a columns set for legacy Columns() api
struct uiPopupData;               // Storage for current popup stack
struct uiSettingsHandler;         // Storage for one type registered in the .ini file
struct uiStyleMod;                // Stacked style modifier, backup of modified data so we can restore it
struct uiStyleVarInfo;            // Style variable information (e.g. to access style variables from an enum)
struct uiTabBar;                  // Storage for a tab bar
struct uiTabItem;                 // Storage for a tab item (within a tab bar)
struct uiTable;                   // Storage for a table
struct uiTableHeaderData;         // Storage for TableAngledHeadersRow()
struct uiTableColumn;             // Storage for one column of a table
struct uiTableInstanceData;       // Storage for one instance of a same table
struct uiTableTempData;           // Temporary storage for one table (one per table in the stack), shared between tables.
struct uiTableSettings;           // Storage for a table .ini settings
struct uiTableColumnsSettings;    // Storage for a column .ini settings
struct uiTreeNodeStackData;       // Temporary storage for TreeNode().
struct uiTypingSelectState;       // Storage for GetTypingSelectRequest()
struct uiTypingSelectRequest;     // Storage for GetTypingSelectRequest() (aimed to be public)
struct uiWindow;                  // Storage for one window
struct uiWindowDockStyle;         // Storage for window-style data which needs to be stored for docking purpose
struct uiWindowTempData;          // Temporary storage for one window (that's the data which in theory we could ditch at the end of the frame, in practice we currently keep it for each window)
struct uiWindowSettings;          // Storage for a window .ini settings (we keep one of those even if the actual window wasn't instanced during this session)
// Enumerations
// Use your programming IDE "Go to definition" facility on the names of the center columns to find the actual flags/enum lists.
enum uiLocKey : int;         // -> enum uiLocKey         // Enum: a localization entry for translation.
typedef int uiDataAuthority; // -> enum uiDataAuthority_ // Enum: for storing the source authority (dock node vs window) of a field
typedef int uiLayoutType;    // -> enum uiLayoutType_    // Enum: Horizontal or vertical
// Flags
typedef int ImDrawTextFlags;        // -> enum ImDrawTextFlags_      // Flags: for ImTextCalcWordWrapPositionEx()
typedef int uiActivateFlags;        // -> enum uiActivateFlags_      // Flags: for navigation/focus function (will be for ActivateItem() later)
typedef int uiDebugLogFlags;        // -> enum uiDebugLogFlags_      // Flags: for ShowDebugLogWindow(), g.DebugLogFlags
typedef int uiFocusRequestFlags;    // -> enum uiFocusRequestFlags_  // Flags: for FocusWindow()
typedef int uiItemStatusFlags;      // -> enum uiItemStatusFlags_    // Flags: for g.LastItemData.StatusFlags
typedef int uiOldColumnFlags;       // -> enum uiOldColumnFlags_     // Flags: for BeginColumns()
typedef int uiLogFlags;             // -> enum uiLogFlags_           // Flags: for LogBegin() text capturing function
typedef int uiNavRenderCursorFlags; // -> enum uiNavRenderCursorFlags_//Flags: for RenderNavCursor()
typedef int uiNavMoveFlags;         // -> enum uiNavMoveFlags_       // Flags: for navigation requests
typedef int uiNextItemDataFlags;    // -> enum uiNextItemDataFlags_  // Flags: for SetNextItemXXX() functions
typedef int uiNextWindowDataFlags;  // -> enum uiNextWindowDataFlags_// Flags: for SetNextWindowXXX() functions
typedef int uiScrollFlags;          // -> enum uiScrollFlags_        // Flags: for ScrollToItem() and navigation requests
typedef int uiBarrierFlags;         // -> enum uiBarrierFlags_       // Flags: for BarrierEx()
typedef int uiTextFlags;            // -> enum uiTextFlags_          // Flags: for TextEx()
typedef int uiTooltipFlags;         // -> enum uiTooltipFlags_       // Flags: for BeginTooltipEx()
typedef int uiTypingSelectFlags;    // -> enum uiTypingSelectFlags_  // Flags: for GetTypingSelectRequest()
typedef int uiWindowBgClickFlags;   // -> enum uiWindowBgClickFlags_ // Flags: for overriding behavior of clicking on window background/void.
typedef int uiWindowRefreshFlags;   // -> enum uiWindowRefreshFlags_ // Flags: for SetNextWindowRefreshPolicy()
// Table column indexing
typedef ImS16 uiTableColumnIdx;
typedef ImU16 uiTableDrawChannelIdx;
//-----------------------------------------------------------------------------
// [SECTION] Context pointer
//-----------------------------------------------------------------------------
#ifndef GImGui
extern IMGUI_API uiContext* GImGui; // Current implicit context pointer
#endif
//-----------------------------------------------------------------------------
// [SECTION] Macros
//-----------------------------------------------------------------------------
// Internal Drag and Drop payload types. String starting with '_' are reserved for Dear ImGui.
#define IMGUI_PAYLOAD_TYPE_WINDOW "_IMWINDOW" // Payload == uiWindow*
// Debug Printing Into TTY
// (since IMGUI_VERSION_NUM >= 18729: IMGUI_DEBUG_LOG was reworked into IMGUI_DEBUG_PRINTF (and removed framecount from it). If you were using a #define IMGUI_DEBUG_LOG please rename)
#ifndef IMGUI_DEBUG_PRINTF
#ifndef IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS
#define IMGUI_DEBUG_PRINTF(_FMT,...) printf(_FMT, __VA_ARGS__)
#else
#define IMGUI_DEBUG_PRINTF(_FMT,...) ((void)0)
#endif
#endif
// Debug Logging for ShowDebugLogWindow(). This is designed for relatively rare events so please don't spam.
#define IMGUI_DEBUG_LOG_ERROR(...)     do { if (g.DebugLogFlags & uiDebugLogFlags_EventError)     IMGUI_DEBUG_LOG(__VA_ARGS__); else g.DebugLogSkippedErrors++; } while (0)
#define IMGUI_DEBUG_LOG_ACTIVEID(...)  do { if (g.DebugLogFlags & uiDebugLogFlags_EventActiveId)  IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_FOCUS(...)     do { if (g.DebugLogFlags & uiDebugLogFlags_EventFocus)     IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_POPUP(...)     do { if (g.DebugLogFlags & uiDebugLogFlags_EventPopup)     IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_NAV(...)       do { if (g.DebugLogFlags & uiDebugLogFlags_EventNav)       IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_SELECTION(...) do { if (g.DebugLogFlags & uiDebugLogFlags_EventSelection) IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_CLIPPER(...)   do { if (g.DebugLogFlags & uiDebugLogFlags_EventClipper)   IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_IO(...)        do { if (g.DebugLogFlags & uiDebugLogFlags_EventIO)        IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_FONT(...)      do { uiContext* g2 = GImGui; if (g2 && g2->DebugLogFlags & uiDebugLogFlags_EventFont) IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0) // Called from ImFontAtlas function which may operate without a context.
#define IMGUI_DEBUG_LOG_INPUTROUTING(...) do{if (g.DebugLogFlags & uiDebugLogFlags_EventInputRouting)IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_DOCKING(...)   do { if (g.DebugLogFlags & uiDebugLogFlags_EventDocking)   IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
#define IMGUI_DEBUG_LOG_VIEWPORT(...)  do { if (g.DebugLogFlags & uiDebugLogFlags_EventViewport)  IMGUI_DEBUG_LOG(__VA_ARGS__); } while (0)
// Debug options (also see ones on top of imgui.cpp)
//#define IMGUI_DEBUG_BOXSELECT
// Static Asserts
#define IM_STATIC_ASSERT(_COND) static_assert(_COND, "")
// "Paranoid" Debug Asserts are meant to only be enabled during specific debugging/work, otherwise would slow down the code too much.
// We currently don't have many of those so the effect is currently negligible, but onward intent to add more aggressive ones in the code.
//#define IMGUI_DEBUG_PARANOID
#ifdef IMGUI_DEBUG_PARANOID
#define IM_ASSERT_PARANOID(_EXPR) IM_ASSERT(_EXPR)
#else
#define IM_ASSERT_PARANOID(_EXPR)
#endif
// Misc Macros
#define IM_PI                           3.14159265358979323846f
#ifdef _WIN32
#define IM_NEWLINE                      "\r\n"   // Play it nice with Windows users (Update: since 2018-05, Notepad finally appears to support Unix-style carriage returns!)
#else
#define IM_NEWLINE                      "\n"
#endif
#ifndef IM_TABSIZE                      // Until we move this to runtime and/or add proper tab support, at least allow users to compile-time override
#define IM_TABSIZE                      (4)
#endif
#define IM_MEMALIGN(_OFF,_ALIGN)        (((_OFF) + ((_ALIGN) - 1)) & ~((_ALIGN) - 1))           // Memory align e.g. IM_ALIGN(0,4)=0, IM_ALIGN(1,4)=4, IM_ALIGN(4,4)=4, IM_ALIGN(5,4)=8
#define IM_F32_TO_INT8_UNBOUND(_VAL)    ((int)((_VAL) * 255.0f + ((_VAL)>=0 ? 0.5f : -0.5f)))   // Unsaturated, for display purpose
#define IM_F32_TO_INT8_SAT(_VAL)        ((int)(ImSaturate(_VAL) * 255.0f + 0.5f))               // Saturated, always output 0..255
#define IM_TRUNC(_VAL)                  ((float)(int)(_VAL))                                    // Positive values only! ImTrunc() is not inlined in MSVC debug builds
#define IM_ROUND(_VAL)                  ((float)(int)((_VAL) + 0.5f))                           // Positive values only! 
// Hint for branch prediction
#if (defined(__cplusplus) && (__cplusplus >= 202002L)) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 202002L))
#define IM_LIKELY   [[likely]]
#define IM_UNLIKELY [[unlikely]]
#else
#define IM_LIKELY
#define IM_UNLIKELY
#endif
// Enforce cdecl calling convention for functions called by the standard library, in case compilation settings changed the default to e.g. __vectorcall
#ifdef _MSC_VER
#define IMGUI_CDECL __cdecl
#else
#define IMGUI_CDECL
#endif
// Warnings
#if defined(_MSC_VER) && !defined(__clang__)
#define IM_MSVC_WARNING_SUPPRESS(XXXX)  __pragma(warning(suppress: XXXX))
#else
#define IM_MSVC_WARNING_SUPPRESS(XXXX)
#endif
// Debug Tools
// Use 'Metrics/Debugger->Tools->Item Picker' to break into the call-stack of a specific item.
// This will call IM_DEBUG_BREAK() which you may redefine yourself. See https://github.com/scottt/debugbreak for more reference.
#ifndef IM_DEBUG_BREAK
#if defined (_MSC_VER)
#define IM_DEBUG_BREAK()    __debugbreak()
#elif defined(__clang__)
#define IM_DEBUG_BREAK()    __builtin_debugtrap()
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#define IM_DEBUG_BREAK()    __asm__ volatile("int3;nop")
#elif defined(__GNUC__) && defined(__thumb__)
#define IM_DEBUG_BREAK()    __asm__ volatile(".inst 0xde01")
#elif defined(__GNUC__) && defined(__arm__) && !defined(__thumb__)
#define IM_DEBUG_BREAK()    __asm__ volatile(".inst 0xe7f001f0")
#else
#define IM_DEBUG_BREAK()    IM_ASSERT(0)    // It is expected that you define IM_DEBUG_BREAK() into something that will break nicely in a debugger!
#endif
#endif // #ifndef IM_DEBUG_BREAK
// Format specifiers, printing 64-bit hasn't been decently standardized...
// In a real application you should be using PRId64 and PRIu64 from <inttypes.h> (non-windows) and on Windows define them yourself.
#if defined(_MSC_VER) && !defined(__clang__)
#define IM_PRId64 "I64d"
#define IM_PRIu64 "I64u"
#define IM_PRIX64 "I64X"
#else
#define IM_PRId64 "lld"
#define IM_PRIu64 "llu"
#define IM_PRIX64 "llX"
#endif
//-----------------------------------------------------------------------------
// [SECTION] Generic helpers
//-----------------------------------------------------------------------------
// - Helpers: Hashing
// - Helpers: Sorting
// - Helpers: Bit manipulation
// - Helpers: String
// - Helpers: Formatting
// - Helpers: UTF-8 <> wchar conversions
// - Helpers: vec2/vec4 operators
// - Helpers: Maths
// - Helpers: Geometry
// - Helper: vec1
// - Helper: vec2ih
// - Helper: ImRect
// - Helper: ImBitArray
// - Helper: ImBitVector
// - Helper: ImSpan<>, ImSpanAllocator<>
// - Helper: ImStableVector<>
// - Helper: ImPool<>
// - Helper: ImChunkStream<>
// - Helper: uiTextIndex
// - Helper: uiStorage
//-----------------------------------------------------------------------------
// Helpers: Hashing
IMGUI_API uiID        ImHashData(const void* data, size_t data_size, uiID seed = 0);
IMGUI_API uiID        ImHashStr(const char* data, size_t data_size = 0, uiID seed = 0);
IMGUI_API const char* ImHashSkipUncontributingPrefix(const char* label);
// Helpers: Sorting
#ifndef ImQsort
inline void ImQsort(void* base, size_t count, size_t size_of_element, int(IMGUI_CDECL *compare_func)(void const*, void const*)) { if (count > 1) qsort(base, count, size_of_element, compare_func); }
#endif
// Helpers: Color Blending
IMGUI_API ImU32 ImAlphaBlendColors(ImU32 col_a, ImU32 col_b);
// Helpers: Bit manipulation
inline bool         ImIsPowerOfTwo(int v)          { return v != 0 && (v & (v - 1)) == 0; }
inline bool         ImIsPowerOfTwo(ImU64 v)        { return v != 0 && (v & (v - 1)) == 0; }
inline int          ImUpperPowerOfTwo(int v)       { v--; v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16; v++; return v; }
inline unsigned int ImCountSetBits(unsigned int v) { unsigned int count = 0; while (v > 0) { v = v & (v - 1); count++; } return count; }
// Helpers: String
#define ImStrlen strlen
#define ImMemchr memchr
IMGUI_API int         ImStricmp(const char* str1, const char* str2);                     // Case insensitive compare.
IMGUI_API int         ImStrnicmp(const char* str1, const char* str2, size_t count);      // Case insensitive compare to a certain count.
IMGUI_API void        ImStrncpy(char* dst, const char* src, size_t count);               // Copy to a certain count and always zero terminate (strncpy doesn't).
IMGUI_API char*       ImStrdup(const char* str);                                         // Duplicate a string.
IMGUI_API void*       ImMemdup(const void* src, size_t size);                            // Duplicate a chunk of memory.
IMGUI_API char*       ImStrdupcpy(char* dst, size_t* p_dst_size, const char* str);       // Copy in provided buffer, recreate buffer if needed.
IMGUI_API const char* ImStrchrRange(const char* str_begin, const char* str_end, char c); // Find first occurrence of 'c' in string range.
IMGUI_API const char* ImStreolRange(const char* str, const char* str_end);               // End end-of-line
IMGUI_API const char* ImStristr(const char* haystack, const char* haystack_end, const char* needle, const char* needle_end);  // Find a substring in a string range.
IMGUI_API void        ImStrTrimBlanks(char* str);                                        // Remove leading and trailing blanks from a buffer.
IMGUI_API const char* ImStrSkipBlank(const char* str);                                   // Find first non-blank character.
IMGUI_API int         ImStrlenW(const ImWchar* str);                                     // Computer string length (ImWchar string)
IMGUI_API const char* ImStrbol(const char* buf_mid_line, const char* buf_begin);         // Find beginning-of-line
IM_MSVC_RUNTIME_CHECKS_OFF
inline char ImToUpper(char c)              { return (c >= 'a' && c <= 'z') ? c &= ~32 : c; }
inline bool ImCharIsBlankA(char c)         { return c == ' ' || c == '\t'; }
inline bool ImCharIsBlankW(unsigned int c) { return c == ' ' || c == '\t' || c == 0x3000; }
inline bool ImCharIsXdigitA(char c)        { return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }
IM_MSVC_RUNTIME_CHECKS_RESTORE
// Helpers: Formatting
IMGUI_API int         ImFormatString(char* buf, size_t buf_size, const char* fmt, ...) IM_FMTARGS(3);
IMGUI_API int         ImFormatStringV(char* buf, size_t buf_size, const char* fmt, va_list args) IM_FMTLIST(3);
IMGUI_API void        ImFormatStringToTempBuffer(const char** out_buf, const char** out_buf_end, const char* fmt, ...) IM_FMTARGS(3);
IMGUI_API void        ImFormatStringToTempBufferV(const char** out_buf, const char** out_buf_end, const char* fmt, va_list args) IM_FMTLIST(3);
IMGUI_API const char* ImParseFormatFindStart(const char* format);
IMGUI_API const char* ImParseFormatFindEnd(const char* format);
IMGUI_API const char* ImParseFormatTrimDecorations(const char* format, char* buf, size_t buf_size);
IMGUI_API void        ImParseFormatSanitizeForPrinting(const char* fmt_in, char* fmt_out, size_t fmt_out_size);
IMGUI_API const char* ImParseFormatSanitizeForScanning(const char* fmt_in, char* fmt_out, size_t fmt_out_size);
IMGUI_API int         ImParseFormatPrecision(const char* format, int default_value);
// Helpers: UTF-8 <> wchar conversions
IMGUI_API int         ImTextCharToUtf8(char out_buf[5], unsigned int c);                                                      // return output UTF-8 bytes count
IMGUI_API int         ImTextStrToUtf8(char* out_buf, int out_buf_size, const ImWchar* in_text, const ImWchar* in_text_end);   // return output UTF-8 bytes count
IMGUI_API int         ImTextCharFromUtf8(unsigned int* out_char, const char* in_text, const char* in_text_end);               // read one character. return input UTF-8 bytes count
IMGUI_API int         ImTextStrFromUtf8(ImWchar* out_buf, int out_buf_size, const char* in_text, const char* in_text_end, const char** in_remaining = NULL);   // return input UTF-8 bytes count
IMGUI_API int         ImTextCountCharsFromUtf8(const char* in_text, const char* in_text_end);                                 // return number of UTF-8 code-points (NOT bytes count)
IMGUI_API int         ImTextCountUtf8BytesFromChar(const char* in_text, const char* in_text_end);                             // return number of bytes to express one char in UTF-8
IMGUI_API int         ImTextCountUtf8BytesFromStr(const ImWchar* in_text, const ImWchar* in_text_end);                        // return number of bytes to express string in UTF-8
IMGUI_API const char* ImTextFindPreviousUtf8Codepoint(const char* in_text_start, const char* in_p);                           // return previous UTF-8 code-point.
IMGUI_API const char* ImTextFindValidUtf8CodepointEnd(const char* in_text_start, const char* in_text_end, const char* in_p);  // return previous UTF-8 code-point if 'in_p' is not the end of a valid one.
IMGUI_API int         ImTextCountLines(const char* in_text, const char* in_text_end);                                         // return number of lines taken by text. trailing carriage return doesn't count as an extra line.
// Helpers: High-level text functions (DO NOT USE!!! THIS IS A MINIMAL SUBSET OF LARGER UPCOMING CHANGES)
enum ImDrawTextFlags_ {
    ImDrawTextFlags_None           = 0,
    ImDrawTextFlags_CpuFineClip    = 1 << 0, // Must be == 1/true for legacy with 'bool cpu_fine_clip' arg to RenderText()
    ImDrawTextFlags_WrapKeepBlanks = 1 << 1,
    ImDrawTextFlags_StopOnNewLine  = 1 << 2,
};
IMGUI_API vec2        ImFontCalcTextSizeEx(ImFont* font, float size, float max_width, float wrap_width, const char* text_begin, const char* text_end_display, const char* text_end, const char** out_remaining, vec2* out_offset, ImDrawTextFlags flags);
IMGUI_API const char* ImFontCalcWordWrapPositionEx(ImFont* font, float size, const char* text, const char* text_end, float wrap_width, ImDrawTextFlags flags = 0);
IMGUI_API const char* ImTextCalcWordWrapNextLineStart(const char* text, const char* text_end, ImDrawTextFlags flags = 0); // trim trailing space and find beginning of next line
// Character classification for word-wrapping logic
enum ImWcharClass { ImWcharClass_Blank, ImWcharClass_Punct, ImWcharClass_Other };
IMGUI_API void ImTextInitClassifiers();
IMGUI_API void ImTextClassifierClear(ImU32* bits, unsigned int codepoint_min, unsigned int codepoint_end, ImWcharClass char_class);
IMGUI_API void ImTextClassifierSetCharClass(ImU32* bits, unsigned int codepoint_min, unsigned int codepoint_end, ImWcharClass char_class, unsigned int c);
IMGUI_API void ImTextClassifierSetCharClassFromStr(ImU32* bits, unsigned int codepoint_min, unsigned int codepoint_end, ImWcharClass char_class, const char* s);
// Helpers: File System
#ifdef IMGUI_DISABLE_FILE_FUNCTIONS
#define IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS
typedef void* ImFileHandle;
inline ImFileHandle ImFileOpen(const char*, const char*)                 { return NULL; }
inline bool         ImFileClose(ImFileHandle)                            { return false; }
inline ImU64        ImFileGetSize(ImFileHandle)                          { return (ImU64)-1; }
inline ImU64        ImFileRead(void*, ImU64, ImU64, ImFileHandle)        { return 0; }
inline ImU64        ImFileWrite(const void*, ImU64, ImU64, ImFileHandle) { return 0; }
#endif
#ifndef IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS
typedef FILE* ImFileHandle;
IMGUI_API ImFileHandle ImFileOpen(const char* filename, const char* mode);
IMGUI_API bool         ImFileClose(ImFileHandle file);
IMGUI_API ImU64        ImFileGetSize(ImFileHandle file);
IMGUI_API ImU64        ImFileRead(void* data, ImU64 size, ImU64 count, ImFileHandle file);
IMGUI_API ImU64        ImFileWrite(const void* data, ImU64 size, ImU64 count, ImFileHandle file);
#else
#define IMGUI_DISABLE_TTY_FUNCTIONS // Can't use stdout, fflush if we are not using default file functions
#endif
IMGUI_API void* ImFileLoadToMemory(const char* filename, const char* mode, size_t* out_file_size = NULL, int padding_bytes = 0);
// Helpers: Maths
IM_MSVC_RUNTIME_CHECKS_OFF
// - Wrapper for standard libs functions. (Note that imgui_demo.cpp does _not_ use them to keep the code easy to copy)
#ifndef IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
#define ImFabs(X)     fabsf(X)
#define ImSqrt(X)     sqrtf(X)
#define ImFmod(X, Y)  fmodf((X), (Y))
#define ImCos(X)      cosf(X)
#define ImSin(X)      sinf(X)
#define ImAcos(X)     acosf(X)
#define ImAtan2(Y, X) atan2f((Y), (X))
#define ImAtof(STR)   atof(STR)
#define ImCeil(X)     ceilf(X)
inline float  ImPow(float x, float y)   { return powf(x, y); } // DragBehaviorT/SliderBehaviorT uses ImPow with either float/double and need the precision
inline double ImPow(double x, double y) { return pow(x, y); }
inline float  ImLog(float x)            { return logf(x); }    // DragBehaviorT/SliderBehaviorT uses ImLog with either float/double and need the precision
inline double ImLog(double x)           { return log(x); }
inline int    ImAbs(int x)              { return x < 0 ? -x : x; }
inline float  ImAbs(float x)            { return fabsf(x); }
inline double ImAbs(double x)           { return fabs(x); }
inline float  ImSign(float x)           { return (x < 0.0f) ? -1.0f : (x > 0.0f) ? 1.0f : 0.0f; } // Sign operator - returns -1, 0 or 1 based on sign of argument
inline double ImSign(double x)          { return (x < 0.0) ? -1.0 : (x > 0.0) ? 1.0 : 0.0; }
#ifdef IMGUI_ENABLE_SSE
inline float  ImRsqrt(float x)          { return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x))); }
#else
inline float  ImRsqrt(float x)          { return 1.0f / sqrtf(x); }
#endif
inline double ImRsqrt(double x)         { return 1.0 / sqrt(x); }
#endif
// - ImMin/ImMax/ImClamp/ImLerp/ImSwap are used by widgets which support variety of types: signed/unsigned int/long long float/double
// (Exceptionally using templates here but we could also redefine them for those types)
template<typename T> T ImMin(T lhs, T rhs)                              { return lhs < rhs ? lhs : rhs; }
template<typename T> T ImMax(T lhs, T rhs)                              { return lhs >= rhs ? lhs : rhs; }
template<typename T> T ImClamp(T v, T mn, T mx)                         { return (v < mn) ? mn : (v > mx) ? mx : v; }
template<typename T> T ImLerp(double a, double b, float t)              { return (T)(a + (b - a) * (double)t); }
template<typename T> T ImLerp(T a, T b, float t)                        { return (T)((float)a + (float)(b - a) * t); }
template<typename T> void ImSwap(T& a, T& b)                            { T tmp = a; a = b; b = tmp; }
template<typename T> T ImAddClampOverflow(T a, T b, T mn, T mx)         { if (b < 0 && (a < mn - b)) return mn; if (b > 0 && (a > mx - b)) return mx; return a + b; }
template<typename T> T ImSubClampOverflow(T a, T b, T mn, T mx)         { if (b > 0 && (a < mn + b)) return mn; if (b < 0 && (a > mx + b)) return mx; return a - b; }
// - Misc maths helpers
inline vec2 ImMin(const vec2& lhs, const vec2& rhs)              { return vec2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y); }
inline vec2 ImMax(const vec2& lhs, const vec2& rhs)              { return vec2(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y); }
inline vec2 ImClamp(const vec2& v, const vec2&mn, const vec2&mx) { return vec2((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y); }
inline vec2 ImLerp(const vec2& a, const vec2& b, float t)        { return vec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
inline vec2 ImLerp(const vec2& a, const vec2& b, const vec2& t)  { return vec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
inline vec4 ImLerp(const vec4& a, const vec4& b, float t)        { return vec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
inline float ImSaturate(float f)                                 { return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
inline float ImLengthSqr(const vec2& lhs)                        { return (lhs.x * lhs.x) + (lhs.y * lhs.y); }
inline float ImLengthSqr(const vec4& lhs)                        { return (lhs.x * lhs.x) + (lhs.y * lhs.y) + (lhs.z * lhs.z) + (lhs.w * lhs.w); }
inline float ImInvLength(const vec2& lhs, float fail_value)      { float d = (lhs.x * lhs.x) + (lhs.y * lhs.y); if (d > 0.0f) return ImRsqrt(d); return fail_value; }
inline float ImTrunc(float f)                                    { return (float)(int)(f); }
inline vec2  ImTrunc(const vec2& v)                              { return vec2((float)(int)(v.x), (float)(int)(v.y)); }
inline float ImFloor(float f)                                    { return (float)((f >= 0 || (float)(int)f == f) ? (int)f : (int)f - 1); } // Decent replacement for floorf()
inline vec2  ImFloor(const vec2& v)                              { return vec2(ImFloor(v.x), ImFloor(v.y)); }
inline float ImTrunc64(float f)                                  { return (float)(ImS64)(f); }
inline float ImRound64(float f)                                  { return (float)(ImS64)(f + 0.5f); } // FIXME: Positive values only.
inline int   ImModPositive(int a, int b)                         { return (a + b) % b; }
inline float ImDot(const vec2& a, const vec2& b)                 { return a.x * b.x + a.y * b.y; }
inline vec2  ImRotate(const vec2& v, float cos_a, float sin_a)   { return vec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a); }
inline float ImLinearSweep(float current, float target, float speed) { if (current < target) return ImMin(current + speed, target); if (current > target) return ImMax(current - speed, target); return current; }
inline float ImLinearRemapClamp(float s0, float s1, float d0, float d1, float x) { return ImSaturate((x - s0) / (s1 - s0)) * (d1 - d0) + d0; }
inline vec2  ImMul(const vec2& lhs, const vec2& rhs)             { return vec2(lhs.x * rhs.x, lhs.y * rhs.y); }
inline bool  ImIsFloatAboveGuaranteedIntegerPrecision(float f) { return f <= -16777216 || f >= 16777216; }
inline float ImExponentialMovingAverage(float avg, float sample, int n){ avg -= avg / (float)n; avg += sample / (float)n; return avg; }
IM_MSVC_RUNTIME_CHECKS_RESTORE
// Helpers: Geometry
IMGUI_API vec2 ImBezierCubicCalc(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4, float t);
IMGUI_API vec2 ImBezierCubicClosestPoint(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4, const vec2& p, int num_segments);       // For curves with explicit number of segments
IMGUI_API vec2 ImBezierCubicClosestPointCasteljau(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4, const vec2& p, float tess_tol);// For auto-tessellated curves you can use tess_tol = style.CurveTessellationTol
IMGUI_API vec2 ImBezierQuadraticCalc(const vec2& p1, const vec2& p2, const vec2& p3, float t);
IMGUI_API vec2 ImLineClosestPoint(const vec2& a, const vec2& b, const vec2& p);
IMGUI_API bool ImTriangleContainsPoint(const vec2& a, const vec2& b, const vec2& c, const vec2& p);
IMGUI_API vec2 ImTriangleClosestPoint(const vec2& a, const vec2& b, const vec2& c, const vec2& p);
IMGUI_API void ImTriangleBarycentricCoords(const vec2& a, const vec2& b, const vec2& c, const vec2& p, float& out_u, float& out_v, float& out_w);
inline float   ImTriangleArea(const vec2& a, const vec2& b, const vec2& c) { return ImFabs((a.x * (b.y - c.y)) + (b.x * (c.y - a.y)) + (c.x * (a.y - b.y))) * 0.5f; }
inline bool    ImTriangleIsClockwise(const vec2& a, const vec2& b, const vec2& c) { return ((b.x - a.x) * (c.y - b.y)) - ((c.x - b.x) * (b.y - a.y)) > 0.0f; }
IM_MSVC_RUNTIME_CHECKS_OFF
// Helper: ImRect (2D axis aligned bounding-box)
// NB: we can't rely on vec2 math operators being available here!
struct IMGUI_API ImRect {
    vec2 Min; // Upper-left
    vec2 Max; // Lower-right
    constexpr ImRect()                                       : Min(0.0f, 0.0f), Max(0.0f, 0.0f) {}
    constexpr ImRect(const vec2& min, const vec2& max)   : Min(min), Max(max)               {}
    constexpr ImRect(const vec4& v)                        : Min(v.x, v.y), Max(v.z, v.w)     {}
    constexpr ImRect(float x1, float y1, float x2, float y2) : Min(x1, y1), Max(x2, y2)         {}
    vec2  GetCenter() const             { return vec2((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f); }
    vec2  GetSize() const               { return vec2(Max.x - Min.x, Max.y - Min.y); }
    float GetWidth() const              { return Max.x - Min.x; }
    float GetHeight() const             { return Max.y - Min.y; }
    float GetArea() const               { return (Max.x - Min.x) * (Max.y - Min.y); }
    vec2  GetTL() const                 { return Min; }                   // Top-left
    vec2  GetTR() const                 { return vec2(Max.x, Min.y); }  // Top-right
    vec2  GetBL() const                 { return vec2(Min.x, Max.y); }  // Bottom-left
    vec2  GetBR() const                 { return Max; }                   // Bottom-right
    bool  Contains(const vec2& p) const { return p.x     >= Min.x && p.y     >= Min.y && p.x     <  Max.x && p.y     <  Max.y; }
    bool  Contains(const ImRect& r) const { return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x <= Max.x && r.Max.y <= Max.y; }
    bool  ContainsWithPad(const vec2& p, const vec2& pad) const { return p.x >= Min.x - pad.x && p.y >= Min.y - pad.y && p.x < Max.x + pad.x && p.y < Max.y + pad.y; }
    bool  Overlaps(const ImRect& r) const { return r.Min.y <  Max.y && r.Max.y >  Min.y && r.Min.x <  Max.x && r.Max.x >  Min.x; }
    void  Add(const vec2& p)            { if (Min.x > p.x)     Min.x = p.x;     if (Min.y > p.y)     Min.y = p.y;     if (Max.x < p.x)     Max.x = p.x;     if (Max.y < p.y)     Max.y = p.y; }
    void  Add(const ImRect& r)          { if (Min.x > r.Min.x) Min.x = r.Min.x; if (Min.y > r.Min.y) Min.y = r.Min.y; if (Max.x < r.Max.x) Max.x = r.Max.x; if (Max.y < r.Max.y) Max.y = r.Max.y; }
    void  AddX(float x)                 { if (Min.x > x)       Min.x = x;       if (Max.x < x)       Max.x = x; }
    void  AddY(float y)                 { if (Min.y > y)       Min.y = y;       if (Max.y < y)       Max.y = y; }
    void  Expand(const float amount)    { Min.x -= amount;   Min.y -= amount;   Max.x += amount;   Max.y += amount; }
    void  Expand(const vec2& amount)    { Min.x -= amount.x; Min.y -= amount.y; Max.x += amount.x; Max.y += amount.y; }
    void  Translate(const vec2& d)      { Min.x += d.x; Min.y += d.y; Max.x += d.x; Max.y += d.y; }
    void  TranslateX(float dx)          { Min.x += dx; Max.x += dx; }
    void  TranslateY(float dy)          { Min.y += dy; Max.y += dy; }
    void  ClipWith(const ImRect& r)     { Min = ImMax(Min, r.Min); Max = ImMin(Max, r.Max); }                   // Simple version, may lead to an inverted rectangle, which is fine for Contains/Overlaps test but not for display.
    void  ClipWithFull(const ImRect& r) { Min = ImClamp(Min, r.Min, r.Max); Max = ImClamp(Max, r.Min, r.Max); } // Full version, ensure both points are fully clipped.
    bool  IsInverted() const            { return Min.x > Max.x || Min.y > Max.y; }
    vec4  ToVec4() const                { return vec4(Min.x, Min.y, Max.x, Max.y); }
    const vec4& AsVec4() const          { return *(const vec4*)&Min.x; }
};
// Helper: ImBitArray
#define       IM_BITARRAY_TESTBIT(_ARRAY, _N)                  ((_ARRAY[(_N) >> 5] & ((ImU32)1 << ((_N) & 31))) != 0) // Macro version of ImBitArrayTestBit(): ensure args have side-effect or are costly!
#define       IM_BITARRAY_CLEARBIT(_ARRAY, _N)                 ((_ARRAY[(_N) >> 5] &= ~((ImU32)1 << ((_N) & 31))))    // Macro version of ImBitArrayClearBit(): ensure args have side-effect or are costly!
inline size_t ImBitArrayGetStorageSizeInBytes(int bitcount)    { return (size_t)((bitcount + 31) >> 5) << 2; }
inline void   ImBitArrayClearAllBits(ImU32* arr, int bitcount) { memset(arr, 0, ImBitArrayGetStorageSizeInBytes(bitcount)); }
inline bool   ImBitArrayTestBit(const ImU32* arr, int n)       { ImU32 mask = (ImU32)1 << (n & 31); return (arr[n >> 5] & mask) != 0; }
inline void   ImBitArrayClearBit(ImU32* arr, int n)            { ImU32 mask = (ImU32)1 << (n & 31); arr[n >> 5] &= ~mask; }
inline void   ImBitArraySetBit(ImU32* arr, int n)              { ImU32 mask = (ImU32)1 << (n & 31); arr[n >> 5] |= mask; }
inline void   ImBitArraySetBitRange(ImU32* arr, int n, int n2) // Works on range [n..n2)
{
    n2--;
    while (n <= n2) {
        int a_mod = (n & 31);
        int b_mod = (n2 > (n | 31) ? 31 : (n2 & 31)) + 1;
        ImU32 mask = (ImU32)(((ImU64)1 << b_mod) - 1) & ~(ImU32)(((ImU64)1 << a_mod) - 1);
        arr[n >> 5] |= mask;
        n = (n + 32) & ~31;
    }
}
typedef ImU32* ImBitArrayPtr; // Name for use in structs
// Helper: ImBitArray class (wrapper over ImBitArray functions)
// Store 1-bit per value.
template<int BITCOUNT, int OFFSET = 0>
struct ImBitArray {
    ImU32 Data[(BITCOUNT + 31) >> 5];
    ImBitArray() { ClearAllBits(); }
    void ClearAllBits()             { memset(Data, 0, sizeof(Data)); }
    void SetAllBits()               { memset(Data, 255, sizeof(Data)); }
    bool TestBit(int n) const       { n += OFFSET; IM_ASSERT(n >= 0 && n < BITCOUNT); return IM_BITARRAY_TESTBIT(Data, n); }
    void SetBit(int n)              { n += OFFSET; IM_ASSERT(n >= 0 && n < BITCOUNT); ImBitArraySetBit(Data, n); }
    void ClearBit(int n)            { n += OFFSET; IM_ASSERT(n >= 0 && n < BITCOUNT); ImBitArrayClearBit(Data, n); }
    void SetBitRange(int n, int n2) { n += OFFSET; n2 += OFFSET; IM_ASSERT(n >= 0 && n < BITCOUNT && n2 > n && n2 <= BITCOUNT); ImBitArraySetBitRange(Data, n, n2); } // Works on range [n..n2)
    bool operator[](int n) const    { n += OFFSET; IM_ASSERT(n >= 0 && n < BITCOUNT); return IM_BITARRAY_TESTBIT(Data, n); }
};
// Helper: ImBitVector
// Store 1-bit per value.
struct IMGUI_API ImBitVector {
    ImVector<ImU32> Storage;
    void Create(int sz)       { Storage.resize((sz + 31) >> 5); memset(Storage.Data, 0, (size_t)Storage.Size * sizeof(Storage.Data[0])); }
    void Clear()              { Storage.clear(); }
    bool TestBit(int n) const { IM_ASSERT(n < (Storage.Size << 5)); return IM_BITARRAY_TESTBIT(Storage.Data, n); }
    void SetBit(int n)        { IM_ASSERT(n < (Storage.Size << 5)); ImBitArraySetBit(Storage.Data, n); }
    void ClearBit(int n)      { IM_ASSERT(n < (Storage.Size << 5)); ImBitArrayClearBit(Storage.Data, n); }
};
IM_MSVC_RUNTIME_CHECKS_RESTORE
// Helper: ImSpan<>
// Pointing to a span of data we don't own.
template<typename T>
struct ImSpan {
    T* Data;
    T* DataEnd;
    // Constructors, destructor
    inline ImSpan()                           { Data = DataEnd = NULL; }
    inline ImSpan(T* data, int size)          { Data = data; DataEnd = data + size; }
    inline ImSpan(T* data, T* data_end)       { Data = data; DataEnd = data_end; }
    inline void     set(T* data, int size)    { Data = data; DataEnd = data + size; }
    inline void     set(T* data, T* data_end) { Data = data; DataEnd = data_end; }
    inline int      size() const              { return (int)(ptrdiff_t)(DataEnd - Data); }
    inline int      size_in_bytes() const     { return (int)(ptrdiff_t)(DataEnd - Data) * (int)sizeof(T); }
    inline T&       operator[](int i)         { T* p = Data + i; IM_ASSERT(p >= Data && p < DataEnd); return *p; }
    inline const T& operator[](int i) const   { const T* p = Data + i; IM_ASSERT(p >= Data && p < DataEnd); return *p; }
    inline T*       begin()                   { return Data; }
    inline const T* begin() const             { return Data; }
    inline T*       end()                     { return DataEnd; }
    inline const T* end() const               { return DataEnd; }
    // Utilities
    inline int index_from_ptr(const T* it) const { IM_ASSERT(it >= Data && it < DataEnd); const ptrdiff_t off = it - Data; return (int)off; }
};
// Helper: ImSpanAllocator<>
// Facilitate storing multiple chunks into a single large block (the "arena")
// - Usage: call Reserve() N times, allocate GetArenaSizeInBytes() worth, pass it to SetArenaBasePtr(), call GetSpan() N times to retrieve the aligned ranges.
template<int CHUNKS>
struct ImSpanAllocator {
    char* BasePtr;
    int   CurrOff;
    int   CurrIdx;
    int   Offsets[CHUNKS];
    int   Sizes[CHUNKS];
    ImSpanAllocator()                               { memset((void*)this, 0, sizeof(*this)); }
    inline void  Reserve(int n, size_t sz, int a=4) { IM_ASSERT(n == CurrIdx && n < CHUNKS); CurrOff = IM_MEMALIGN(CurrOff, a); Offsets[n] = CurrOff; Sizes[n] = (int)sz; CurrIdx++; CurrOff += (int)sz; }
    inline int   GetArenaSizeInBytes()              { return CurrOff; }
    inline void  SetArenaBasePtr(void* base_ptr)    { BasePtr = (char*)base_ptr; }
    inline void* GetSpanPtrBegin(int n)             { IM_ASSERT(n >= 0 && n < CHUNKS && CurrIdx == CHUNKS); return (void*)(BasePtr + Offsets[n]); }
    inline void* GetSpanPtrEnd(int n)               { IM_ASSERT(n >= 0 && n < CHUNKS && CurrIdx == CHUNKS); return (void*)(BasePtr + Offsets[n] + Sizes[n]); }
    template<typename T>
    inline void  GetSpan(int n, ImSpan<T>* span)    { span->set((T*)GetSpanPtrBegin(n), (T*)GetSpanPtrEnd(n)); }
};
// Helper: ImStableVector<>
// Allocating chunks of BLOCKSIZE items. Objects pointers are never invalidated when growing, only by clear().
// Important: does not destruct anything!
// Implemented only the minimum set of functions we need for it.
template<typename T, int BLOCKSIZE>
struct ImStableVector {
    int          Size = 0;
    int          Capacity = 0;
    ImVector<T*> Blocks;
    // Functions
    inline ~ImStableVector() { for (T* block : Blocks) IM_FREE(block); }
    inline void clear()              { Size = Capacity = 0; Blocks.clear_delete(); }
    inline void resize(int new_size) { if (new_size > Capacity) reserve(new_size); Size = new_size; }
    inline void reserve(int new_cap) {
        new_cap = IM_MEMALIGN(new_cap, BLOCKSIZE);
        int old_count = Capacity / BLOCKSIZE;
        int new_count = new_cap / BLOCKSIZE;
        if (new_count <= old_count) return;
        Blocks.resize(new_count);
        for (int n = old_count; n < new_count; n++) Blocks[n] = (T*)IM_ALLOC(sizeof(T) * BLOCKSIZE);
        Capacity = new_cap;
    }
    inline T&       operator[](int i)       { IM_ASSERT(i >= 0 && i < Size); return Blocks[i / BLOCKSIZE][i % BLOCKSIZE]; }
    inline const T& operator[](int i) const { IM_ASSERT(i >= 0 && i < Size); return Blocks[i / BLOCKSIZE][i % BLOCKSIZE]; }
    inline T*       push_back(const T& v)   { int i = Size; IM_ASSERT(i >= 0); if (Size == Capacity) reserve(Capacity + BLOCKSIZE); void* ptr = &Blocks[i / BLOCKSIZE][i % BLOCKSIZE]; memcpy(ptr, &v, sizeof(v)); Size++; return (T*)ptr; }
};
// Helper: ImPool<>
// Basic keyed storage for contiguous instances, slow/amortized insertion, O(1) indexable, O(Log N) queries by ID over a dense/hot buffer,
// Honor constructor/destructor. Add/remove invalidate all pointers. Indexes have the same lifetime as the associated object.
typedef int ImPoolIdx;
template<typename T>
struct ImPool {
    ImVector<T> Buf;        // Contiguous data
    uiStorage   Map;        // ID->Index
    ImPoolIdx   FreeIdx;    // Next free idx to use
    ImPoolIdx   AliveCount; // Number of active/alive items (for display purpose)

    ImPool()  { FreeIdx = AliveCount = 0; }
    ~ImPool() { Clear(); }
    T*        GetByKey(uiID key)              { int idx = Map.GetInt(key, -1); return (idx != -1) ? &Buf[idx] : NULL; }
    T*        GetByIndex(ImPoolIdx n)         { return &Buf[n]; }
    ImPoolIdx GetIndex(const T* p) const      { IM_ASSERT(p >= Buf.Data && p < Buf.Data + Buf.Size); return (ImPoolIdx)(p - Buf.Data); }
    T*        GetOrAddByKey(uiID key)         { int* p_idx = Map.GetIntRef(key, -1); if (*p_idx != -1) return &Buf[*p_idx]; *p_idx = FreeIdx; return Add(); }
    bool      Contains(const T* p) const      { return (p >= Buf.Data && p < Buf.Data + Buf.Size); }
    void      Clear()                         { for (int n = 0; n < Map.Data.Size; n++) { int idx = Map.Data[n].val_i; if (idx != -1) Buf[idx].~T(); } Map.Clear(); Buf.clear(); FreeIdx = AliveCount = 0; }
    T*        Add()                           { int idx = FreeIdx; if (idx == Buf.Size) { Buf.resize(Buf.Size + 1); FreeIdx++; } else { FreeIdx = *(int*)&Buf[idx]; } IM_PLACEMENT_NEW(&Buf[idx]) T(); AliveCount++; return &Buf[idx]; }
    void      Remove(uiID key, const T* p)    { Remove(key, GetIndex(p)); }
    void      Remove(uiID key, ImPoolIdx idx) { Buf[idx].~T(); *(int*)&Buf[idx] = FreeIdx; FreeIdx = idx; Map.SetInt(key, -1); AliveCount--; }
    void      Reserve(int capacity)           { Buf.reserve(capacity); Map.Data.reserve(capacity); }
    // To iterate a ImPool: for (int n = 0; n < pool.GetMapSize(); n++) if (T* t = pool.TryGetMapData(n)) { ... }
    // Can be avoided if you know .Remove() has never been called on the pool, or AliveCount == GetMapSize()
    int GetAliveCount() const      { return AliveCount; }      // Number of active/alive items in the pool (for display purpose)
    int GetBufSize() const         { return Buf.Size; }
    int GetMapSize() const         { return Map.Data.Size; }   // It is the map we need iterate to find valid items, since we don't have "alive" storage anywhere
    T*  TryGetMapData(ImPoolIdx n) { int idx = Map.Data[n].val_i; if (idx == -1) return NULL; return GetByIndex(idx); }
};
// Helper: ImChunkStream<>
// Build and iterate a contiguous stream of variable-sized structures.
// This is used by Settings to store persistent data while reducing allocation count.
// We store the chunk size first, and align the final size on 4 bytes boundaries.
// The tedious/zealous amount of casting is to avoid -Wcast-align warnings.
template<typename T>
struct ImChunkStream {
    ImVector<char> Buf;
    void clear()                     { Buf.clear(); }
    bool empty() const               { return Buf.Size == 0; }
    int  size() const                { return Buf.Size; }
    T*   alloc_chunk(size_t sz)      { size_t HDR_SZ = 4; sz = IM_MEMALIGN(HDR_SZ + sz, 4u); int off = Buf.Size; Buf.resize(off + (int)sz); ((int*)(void*)(Buf.Data + off))[0] = (int)sz; return (T*)(void*)(Buf.Data + off + (int)HDR_SZ); }
    T*   begin()                     { size_t HDR_SZ = 4; if (!Buf.Data) return NULL; return (T*)(void*)(Buf.Data + HDR_SZ); }
    T*   next_chunk(T* p)            { size_t HDR_SZ = 4; IM_ASSERT(p >= begin() && p < end()); p = (T*)(void*)((char*)(void*)p + chunk_size(p)); if (p == (T*)(void*)((char*)end() + HDR_SZ)) return (T*)0; IM_ASSERT(p < end()); return p; }
    int  chunk_size(const T* p)      { return ((const int*)p)[-1]; }
    T*   end()                       { return (T*)(void*)(Buf.Data + Buf.Size); }
    int  offset_from_ptr(const T* p) { IM_ASSERT(p >= begin() && p < end()); const ptrdiff_t off = (const char*)p - Buf.Data; return (int)off; }
    T*   ptr_from_offset(int off)    { IM_ASSERT(off >= 4 && off < Buf.Size); return (T*)(void*)(Buf.Data + off); }
    void swap(ImChunkStream<T>& rhs) { rhs.Buf.swap(Buf); }
};
// Helper: uiTextIndex
// Maintain a line index for a text buffer. This is a strong candidate to be moved into the public API.
struct uiTextIndex {
    ImVector<int> Offsets;
    int           EndOffset = 0; // Because we don't own text buffer we need to maintain EndOffset (may bake in LineOffsets?)
    void          clear()                                 { Offsets.clear(); EndOffset = 0; }
    int           size()                                  { return Offsets.Size; }
    const char*   get_line_begin(const char* base, int n) { return base + (Offsets.Size != 0 ? Offsets[n] : 0); }
    const char*   get_line_end(const char* base, int n)   { return base + (n + 1 < Offsets.Size ? (Offsets[n + 1] - 1) : EndOffset); }
    void          append(const char* base, int old_size, int new_size);
};
// Helper: uiStorage
IMGUI_API uiStoragePair* ImLowerBound(uiStoragePair* in_begin, uiStoragePair* in_end, uiID key);
//-----------------------------------------------------------------------------
// [SECTION] ImDrawList support
//-----------------------------------------------------------------------------
// ImDrawList: Helper function to calculate a circle's segment count given its radius and a "maximum error" value.
// Estimation of number of circle segment based on error is derived using method described in https://stackoverflow.com/a/2244088/15194693
// Number of segments (N) is calculated using equation:
//   N = ceil ( pi / acos(1 - error / r) )     where r > 0, error <= r
// Our equation is significantly simpler that one in the post thanks for choosing segment that is
// perpendicular to X axis. Follow steps in the article from this starting condition and you will
// will get this result.
//
// Rendering circles with an odd number of segments, while mathematically correct will produce
// asymmetrical results on the raster grid. Therefore we're rounding N to next even number (7->8, 8->8, 9->10 etc.)
#define IM_ROUNDUP_TO_EVEN(_V)                                  ((((_V) + 1) / 2) * 2)
#define IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_MIN                     4
#define IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_MAX                     512
#define IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC(_RAD,_MAXERROR)    ImClamp(IM_ROUNDUP_TO_EVEN((int)ImCeil(IM_PI / ImAcos(1 - ImMin((_MAXERROR), (_RAD)) / (_RAD)))), IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_MIN, IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_MAX)
// Raw equation from IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC rewritten for 'r' and 'error'.
#define IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC_R(_N,_MAXERROR)    ((_MAXERROR) / (1 - ImCos(IM_PI / ImMax((float)(_N), IM_PI))))
#define IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC_ERROR(_N,_RAD)     ((1 - ImCos(IM_PI / ImMax((float)(_N), IM_PI))) / (_RAD))
// ImDrawList: Lookup table size for adaptive arc drawing, cover full circle.
#ifndef IM_DRAWLIST_ARCFAST_TABLE_SIZE
#define IM_DRAWLIST_ARCFAST_TABLE_SIZE                          48 // Number of samples in lookup table.
#endif
#define IM_DRAWLIST_ARCFAST_SAMPLE_MAX                          IM_DRAWLIST_ARCFAST_TABLE_SIZE // Sample index _PathArcToFastEx() for 360 angle.
// Data shared between all ImDrawList instances
// Conceptually this could have been called e.g. ImDrawListSharedContext
// Typically one ImGui context would create and maintain one of this.
// You may want to create your own instance of you try to ImDrawList completely without ImGui. In that case, watch out for future changes to this structure.
struct IMGUI_API ImDrawListSharedData {
    vec2          TexUvWhitePixel;       // UV of white pixel in the atlas (== FontAtlas->TexUvWhitePixel)
    const vec4*   TexUvLines;            // UV of anti-aliased lines in the atlas (== FontAtlas->TexUvLines)
    ImFontAtlas*    FontAtlas;             // Current font atlas
    ImFont*         Font;                  // Current font (used for simplified AddText overload)
    float           FontSize;              // Current font size (used for for simplified AddText overload)
    float           FontScale;             // Current font scale (== FontSize / Font->FontSize)
    float           CurveTessellationTol;  // Tessellation tolerance when using PathBezierCurveTo()
    float           CircleSegmentMaxError; // Number of circle segments to use per pixel of radius for AddCircle() etc
    float           InitialFringeScale;    // Initial scale to apply to AA fringe
    ImDrawListFlags InitialFlags;          // Initial flags at the beginning of the frame (it is possible to alter flags on a per-drawlist basis afterwards)
    vec4          ClipRectFullscreen;    // Value for PushClipRectFullscreen()
    ImVector<vec2> TempBuffer;           // Temporary write buffer
    ImVector<ImDrawList*> DrawLists;       // All draw lists associated to this ImDrawListSharedData
    uiContext*      Context;               // [OPTIONAL] Link to Dear ImGui context. 99% of ImDrawList/ImFontAtlas can function without an ImGui context, but this facilitate handling one legacy edge case.
    // Lookup tables
    vec2          ArcFastVtx[IM_DRAWLIST_ARCFAST_TABLE_SIZE]; // Sample points on the quarter of the circle.
    float           ArcFastRadiusCutoff;                        // Cutoff radius after which arc drawing will fallback to slower PathArcTo()
    ImU8            CircleSegmentCounts[64];    // Precomputed segment count for given radius before we calculate it dynamically (to avoid calculation overhead)
    ImDrawListSharedData();
    ~ImDrawListSharedData();
    void SetCircleTessellationMaxError(float max_error);
};
struct ImDrawDataBuilder {
    ImVector<ImDrawList*>* Layers[2]; // Pointers to global layers for: regular, tooltip. LayersP[0] is owned by DrawData.
    ImVector<ImDrawList*>  LayerData1;
    ImDrawDataBuilder() { memset((void*)this, 0, sizeof(*this)); }
};
struct ImFontStackData {
    ImFont* Font;
    float   FontSizeBeforeScaling; // ~~ style.FontSizeBase
    float   FontSizeAfterScaling;  // ~~ g.FontSize
};
//-----------------------------------------------------------------------------
// [SECTION] Style support
//-----------------------------------------------------------------------------

struct uiStyleVarInfo
{
    ImU32           Count : 8;      // 1+
    uiDataType   DataType : 8;
    ImU32           Offset : 16;    // Offset in parent structure
    void* GetVarPtr(void* parent) const { return (void*)((unsigned char*)parent + Offset); }
};

// Stacked color modifier, backup of modified data so we can restore it
struct uiColorMod
{
    uiCol        Col;
    vec4          BackupValue;
};

// Stacked style modifier, backup of modified data so we can restore it. Data type inferred from the variable.
struct uiStyleMod
{
    uiStyleVar   VarIdx;
    union           { int BackupInt[2]; float BackupFloat[2]; };
    uiStyleMod(uiStyleVar idx, int v)     { VarIdx = idx; BackupInt[0] = v; }
    uiStyleMod(uiStyleVar idx, float v)   { VarIdx = idx; BackupFloat[0] = v; }
    uiStyleMod(uiStyleVar idx, vec2 v)  { VarIdx = idx; BackupFloat[0] = v.x; BackupFloat[1] = v.y; }
};

//-----------------------------------------------------------------------------
// [SECTION] Data types support
//-----------------------------------------------------------------------------

struct uiDataTypeStorage
{
    ImU8        Data[8];        // Opaque storage to fit any data up to uiDataType_COUNT
};

// Type information associated to one uiDataType. Retrieve with DataTypeGetInfo().
struct uiDataTypeInfo
{
    size_t      Size;           // Size in bytes
    const char* Name;           // Short descriptive name for the type, for debugging
    const char* PrintFmt;       // Default printf format for the type
    const char* ScanFmt;        // Default scanf format for the type
};

// Extend uiDataType_
enum uiDataTypePrivate_
{
    uiDataType_Pointer = uiDataType_COUNT,
    uiDataType_ID,
};

//-----------------------------------------------------------------------------
// [SECTION] Widgets support: flags, enums, data structures
//-----------------------------------------------------------------------------

// Extend uiItemFlags
// - input: PushItemFlag() manipulates g.CurrentItemFlags, g.NextItemData.ItemFlags, ItemAdd() calls may add extra flags too.
// - output: stored in g.LastItemData.ItemFlags
enum uiItemFlagsPrivate_
{
    // Controlled by user
    uiItemFlags_ReadOnly                 = 1 << 11, // false     // [ALPHA] Allow hovering interactions but underlying value is not changed.
    uiItemFlags_MixedValue               = 1 << 12, // false     // [BETA] Represent a mixed/indeterminate value, generally multi-selection where values differ. Currently only supported by Checkbox() (later should support all sorts of widgets)
    uiItemFlags_NoWindowHoverableCheck   = 1 << 13, // false     // Disable hoverable check in ItemHoverable()
    uiItemFlags_AllowOverlap             = 1 << 14, // false     // Allow being overlapped by another widget. Not-hovered to Hovered transition deferred by a frame.
    uiItemFlags_NoNavDisableMouseHover   = 1 << 15, // false     // Nav keyboard/gamepad mode doesn't disable hover highlight (behave as if NavHighlightItemUnderNav==false).
    uiItemFlags_NoMarkEdited             = 1 << 16, // false     // Skip calling MarkItemEdited()
    uiItemFlags_NoFocus                  = 1 << 17, // false     // [EXPERIMENTAL: Not very well specced] Clicking doesn't take focus. Automatically sets uiButtonFlags_NoFocus + uiButtonFlags_NoNavFocus in ButtonBehavior().

    // Controlled by widget code
    uiItemFlags_Inputable                = 1 << 20, // false     // [WIP] Auto-activate input mode when tab focused. Currently only used and supported by a few items before it becomes a generic feature.
    uiItemFlags_HasSelectionUserData     = 1 << 21, // false     // Set by SetNextItemSelectionUserData()
    uiItemFlags_IsMultiSelect            = 1 << 22, // false     // Set by SetNextItemSelectionUserData()

    uiItemFlags_Default_                 = uiItemFlags_AutoClosePopups,    // Please don't change, use PushItemFlag() instead.

    // Obsolete
    //uiItemFlags_SelectableDontClosePopup = !uiItemFlags_AutoClosePopups, // Can't have a redirect as we inverted the behavior
};

// Status flags for an already submitted item
// - output: stored in g.LastItemData.StatusFlags
enum uiItemStatusFlags_
{
    uiItemStatusFlags_None               = 0,
    uiItemStatusFlags_HoveredRect        = 1 << 0,   // Mouse position is within item rectangle (does NOT mean that the window is in correct z-order and can be hovered!, this is only one part of the most-common IsItemHovered test)
    uiItemStatusFlags_HasDisplayRect     = 1 << 1,   // g.LastItemData.DisplayRect is valid
    uiItemStatusFlags_Edited             = 1 << 2,   // Value exposed by item was edited in the current frame (should match the bool return value of most widgets)
    uiItemStatusFlags_ToggledSelection   = 1 << 3,   // Set when Selectable(), TreeNode() reports toggling a selection. We can't report "Selected", only state changes, in order to easily handle clipping with less issues.
    uiItemStatusFlags_ToggledOpen        = 1 << 4,   // Set when TreeNode() reports toggling their open state.
    uiItemStatusFlags_HasDeactivated     = 1 << 5,   // Set if the widget/group is able to provide data for the uiItemStatusFlags_Deactivated flag.
    uiItemStatusFlags_Deactivated        = 1 << 6,   // Only valid if uiItemStatusFlags_HasDeactivated is set.
    uiItemStatusFlags_HoveredWindow      = 1 << 7,   // Override the HoveredWindow test to allow cross-window hover testing.
    uiItemStatusFlags_Visible            = 1 << 8,   // [WIP] Set when item is overlapping the current clipping rectangle (Used internally. Please don't use yet: API/system will change as we refactor Itemadd()).
    uiItemStatusFlags_HasClipRect        = 1 << 9,   // g.LastItemData.ClipRect is valid.
    uiItemStatusFlags_HasShortcut        = 1 << 10,  // g.LastItemData.Shortcut valid. Set by SetNextItemShortcut() -> ItemAdd().
    //uiItemStatusFlags_FocusedByTabbing = 1 << 8,   // Removed IN 1.90.1 (Dec 2023). The trigger is part of g.NavActivateId. See commit 54c1bdeceb.
    uiItemStatusFlags_EditedInternal     = 1 << 11,  // Similar to uiItemStatusFlags_Edited but bypassing uiItemFlags_NoMarkEdited.

    // Additional status + semantic for uiTestEngine
#ifdef IMGUI_ENABLE_TEST_ENGINE
    uiItemStatusFlags_Openable           = 1 << 20,  // Item is an openable (e.g. TreeNode)
    uiItemStatusFlags_Opened             = 1 << 21,  // Opened status
    uiItemStatusFlags_Checkable          = 1 << 22,  // Item is a checkable (e.g. CheckBox, MenuItem)
    uiItemStatusFlags_Checked            = 1 << 23,  // Checked status
    uiItemStatusFlags_Inputable          = 1 << 24,  // Item is a text-inputable (e.g. InputText, SliderXXX, DragXXX)
#endif
};

// Extend uiHoverFlags_
enum uiHoverFlagsPrivate_
{
    uiHoverFlags_DelayMask_                    = uiHoverFlags_Delay | uiHoverFlags_NoSharedDelay,
    uiHoverFlags_AllowedMaskForIsWindowHovered = uiHoverFlags_ChildWindows | uiHoverFlags_RootWindow | uiHoverFlags_AnyWindow | uiHoverFlags_NoPopupHierarchy | uiHoverFlags_DockHierarchy | uiHoverFlags_AllowWhenBlockedByPopup | uiHoverFlags_AllowWhenBlockedByActiveItem | uiHoverFlags_ForTooltip | uiHoverFlags_Stationary,
    uiHoverFlags_AllowedMaskForIsItemHovered   = uiHoverFlags_AllowWhenBlockedByPopup | uiHoverFlags_AllowWhenBlockedByActiveItem | uiHoverFlags_AllowWhenOverlapped | uiHoverFlags_AllowWhenDisabled | uiHoverFlags_NoNavOverride | uiHoverFlags_ForTooltip | uiHoverFlags_Stationary | uiHoverFlags_DelayMask_,
};

// Extend uiInputTextFlags_
enum uiInputTextFlagsPrivate_
{
    // [Internal]
    uiInputTextFlags_Multiline           = 1 << 26,  // For internal use by InputTextMultiline()
    uiInputTextFlags_TempInput           = 1 << 27,  // For internal use by TempInputText(), will skip calling ItemAdd(). Require bounding-box to strictly match.
    uiInputTextFlags_LocalizeDecimalPoint= 1 << 28,  // For internal use by InputScalar() and TempInputScalar()
};

// Extend uiButtonFlags_
enum uiButtonFlagsPrivate_
{
    uiButtonFlags_PressedOnClick         = 1 << 4,   // return true on click (mouse down event)
    uiButtonFlags_PressedOnClickRelease  = 1 << 5,   // [Default] return true on click + release on same item <-- this is what the majority of Button are using
    uiButtonFlags_PressedOnClickReleaseAnywhere = 1 << 6, // return true on click + release even if the release event is not done while hovering the item
    uiButtonFlags_PressedOnRelease       = 1 << 7,   // return true on release (default requires click+release). Prior to 2026/03/20 this implied uiButtonFlags_NoHoldingActiveId but they are separate now.
    uiButtonFlags_PressedOnDoubleClick   = 1 << 8,   // return true on double-click (default requires click+release)
    uiButtonFlags_PressedOnDragDropHold  = 1 << 9,   // return true when held into while we are drag and dropping another item (used by e.g. tree nodes, collapsing headers)
    //uiButtonFlags_Repeat               = 1 << 10,  // hold to repeat -> use uiItemFlags_ButtonRepeat instead.
    uiButtonFlags_FlattenChildren        = 1 << 11,  // allow interactions even if a child window is overlapping
    //uiButtonFlags_DontClosePopups      = 1 << 13,  // disable automatically closing parent popup on press
    //uiButtonFlags_Disabled             = 1 << 14,  // disable interactions -> use BeginDisabled() or uiItemFlags_Disabled
    uiButtonFlags_AlignTextBaseLine      = 1 << 15,  // vertically align button to match text baseline - ButtonEx() only // FIXME: Should be removed and handled by SmallButton(), not possible currently because of DC.CursorPosPrevLine
    uiButtonFlags_NoKeyModsAllowed       = 1 << 16,  // disable mouse interaction if a key modifier is held
    uiButtonFlags_NoHoldingActiveId      = 1 << 17,  // don't set ActiveId while holding the mouse (uiButtonFlags_PressedOnClick only)
    uiButtonFlags_NoNavFocus             = 1 << 18,  // don't override navigation focus when activated (FIXME: this is essentially used every time an item uses uiItemFlags_NoNav, but because legacy specs don't requires LastItemData to be set ButtonBehavior(), we can't poll g.LastItemData.ItemFlags)
    uiButtonFlags_NoHoveredOnFocus       = 1 << 19,  // don't report as hovered when nav focus is on this item
    uiButtonFlags_NoSetKeyOwner          = 1 << 20,  // don't set key/input owner on the initial click (note: mouse buttons are keys! often, the key in question will be uiKey_MouseLeft!)
    uiButtonFlags_NoTestKeyOwner         = 1 << 21,  // don't test key/input owner when polling the key (note: mouse buttons are keys! often, the key in question will be uiKey_MouseLeft!)
    uiButtonFlags_NoFocus                = 1 << 22,  // [EXPERIMENTAL: Not very well specced]. Don't focus parent window when clicking.
    uiButtonFlags_PressedOnMask_         = uiButtonFlags_PressedOnClick | uiButtonFlags_PressedOnClickRelease | uiButtonFlags_PressedOnClickReleaseAnywhere | uiButtonFlags_PressedOnRelease | uiButtonFlags_PressedOnDoubleClick | uiButtonFlags_PressedOnDragDropHold,
    uiButtonFlags_PressedOnDefault_      = uiButtonFlags_PressedOnClickRelease,
    //uiButtonFlags_NoKeyModifiers       = uiButtonFlags_NoKeyModsAllowed, // Renamed in 1.91.4
};

// Extend uiComboFlags_
enum uiComboFlagsPrivate_
{
    uiComboFlags_CustomPreview           = 1 << 20,  // enable BeginComboPreview()
};

// Extend uiSliderFlags_
enum uiSliderFlagsPrivate_
{
    uiSliderFlags_Vertical               = 1 << 20,  // Should this slider be orientated vertically?
    uiSliderFlags_ReadOnly               = 1 << 21,  // Consider using g.NextItemData.ItemFlags |= uiItemFlags_ReadOnly instead.
};

// Extend uiSelectFlags_
enum uiSelectFlagsPrivate_
{
    // NB: need to be in sync with last value of uiSelectFlags_
    uiSelectFlags_NoHoldingActiveID      = 1 << 20,
    uiSelectFlags_SelectOnClick          = 1 << 22,  // Override button behavior to react on Click (default is Click+Release)
    uiSelectFlags_SelectOnRelease        = 1 << 23,  // Override button behavior to react on Release (default is Click+Release)
    uiSelectFlags_SpanAvailWidth         = 1 << 24,  // Span all avail width even if we declared less for layout purpose. FIXME: We may be able to remove this (added in 6251d379, 2bcafc86 for menus)
    uiSelectFlags_SetNavIdOnHover        = 1 << 25,  // Set Nav/Focus ID on mouse hover (used by MenuItem)
    uiSelectFlags_NoPadWithHalfSpacing   = 1 << 26,  // Disable padding each side with ItemSpacing * 0.5f
    uiSelectFlags_NoSetKeyOwner          = 1 << 27,  // Don't set key/input owner on the initial click (note: mouse buttons are keys! often, the key in question will be uiKey_MouseLeft!)
};

// Extend uiTreeFlags_
enum uiTreeFlagsPrivate_
{
    uiTreeFlags_NoNavFocus                 = 1 << 27,// Don't claim nav focus when interacting with this item (#8551)
    uiTreeFlags_ClipLabelForTrailingButton = 1 << 28,// FIXME-WIP: Hard-coded for CollapsingHeader()
    uiTreeFlags_UpsideDownArrow            = 1 << 29,// FIXME-WIP: Turn Down arrow into an Up arrow, for reversed trees (#6517)
    uiTreeFlags_OpenOnMask_                = uiTreeFlags_OpenOnDoubleClick | uiTreeFlags_OpenOnArrow,
    uiTreeFlags_DrawLinesMask_             = uiTreeFlags_DrawLinesNone | uiTreeFlags_DrawLinesFull | uiTreeFlags_DrawLinesToNodes,
};

enum uiBarrierFlags_
{
    uiBarrierFlags_None                    = 0,
    uiBarrierFlags_Horizontal              = 1 << 0,   // Axis default to current layout type, so generally Horizontal unless e.g. in a menu bar
    uiBarrierFlags_Vertical                = 1 << 1,
    uiBarrierFlags_SpanAllColumns          = 1 << 2,   // Make Bar cover all columns of a legacy Columns() set.
};

// Flags for FocusWindow(). This is not called uiFocusFlags to avoid confusion with public-facing uiFocusFlags.
// FIXME: Once we finishing replacing more uses of GetTopMostPopupModal()+IsWindowWithinBeginStackOf()
// and FindBlockingModal() with this, we may want to change the flag to be opt-out instead of opt-in.
enum uiFocusRequestFlags_
{
    uiFocusRequestFlags_None                 = 0,
    uiFocusRequestFlags_RestoreFocusedChild  = 1 << 0,   // Find last focused child (if any) and focus it instead.
    uiFocusRequestFlags_UnlessBelowModal     = 1 << 1,   // Do not set focus if the window is below a modal.
};

enum uiTextFlags_
{
    uiTextFlags_None                         = 0,
    uiTextFlags_NoWidthForLargeClippedText   = 1 << 0,
};

enum uiTooltipFlags_
{
    uiTooltipFlags_None                      = 0,
    uiTooltipFlags_OverridePrevious          = 1 << 1,   // Clear/ignore previously submitted tooltip (defaults to append)
};

// FIXME: this is in development, not exposed/functional as a generic feature yet.
// Horizontal/Vertical enums are fixed to 0/1 so they may be used to index vec2
enum uiLayoutType_
{
    uiLayoutType_Horizontal = 0,
    uiLayoutType_Vertical = 1
};

// Flags for LogBegin() text capturing function
enum uiLogFlags_
{
    uiLogFlags_None = 0,

    uiLogFlags_OutputTTY         = 1 << 0,
    uiLogFlags_OutputFile        = 1 << 1,
    uiLogFlags_OutputBuffer      = 1 << 2,
    uiLogFlags_OutputClipboard   = 1 << 3,
    uiLogFlags_OutputMask_       = uiLogFlags_OutputTTY | uiLogFlags_OutputFile | uiLogFlags_OutputBuffer | uiLogFlags_OutputClipboard,
};

// X/Y enums are fixed to 0/1 so they may be used to index vec2
enum uiAxis
{
    uiAxis_None = -1,
    uiAxis_X = 0,
    uiAxis_Y = 1
};

enum uiPlotType
{
    uiPlotType_Lines,
    uiPlotType_Histogram,
};

// Storage data for BeginComboPreview()/EndComboPreview()
struct IMGUI_API uiComboPreviewData
{
    ImRect          PreviewRect;
    vec2          BackupCursorPos;
    vec2          BackupCursorMaxPos;
    vec2          BackupCursorPosPrevLine;
    float           BackupPrevLineTextBaseOffset;
    uiLayoutType BackupLayout;

    uiComboPreviewData() { memset((void*)this, 0, sizeof(*this)); }
};

// Stacked storage data for BeginGroup()/EndGroup()
struct IMGUI_API uiGroupData
{
    uiID     WindowID;
    vec2      BackupCursorPos;
    vec2      BackupCursorMaxPos;
    vec2      BackupCursorPosPrevLine;
    vec1      BackupIndent;
    vec1      BackupGroupOffset;
    vec2      BackupCurrLineSize;
    float       BackupCurrLineTextBaseOffset;
    uiID     BackupActiveIdIsAlive;
    bool        BackupActiveIdHasBeenEditedThisFrame;
    bool        BackupDeactivatedIdIsAlive;
    bool        BackupHoveredIdIsAlive;
    bool        BackupIsNext;
    bool        EmitItem;
};

// Simple column measurement, currently used for MenuItem() only.. This is very short-sighted/throw-away code and NOT a generic helper.
struct IMGUI_API uiMenuColumns
{
    ImU32       TotalWidth;
    ImU32       NextTotalWidth;
    ImU16       Spacing;
    ImU16       OffsetIcon;         // Always zero for now
    ImU16       OffsetLabel;        // Offsets are locked in Update()
    ImU16       OffsetShortcut;
    ImU16       OffsetMark;
    ImU16       Widths[4];          // Width of:   Icon, Label, Shortcut, Mark  (accumulators for current frame)

    uiMenuColumns() { memset((void*)this, 0, sizeof(*this)); }
    void        Update(float spacing, bool window_reappearing);
    float       DeclColumns(float w_icon, float w_label, float w_shortcut, float w_mark);
    void        CalcNextTotalWidth(bool update_offsets);
};

// Internal temporary state for deactivating InputText() instances.
// Store as part of uiDeactivatedItemData?
struct IMGUI_API uiInputTextDeactivatedState
{
    uiID            ID;              // widget id owning the text state (which just got deactivated)
    ImVector<char>     TextA;           // text buffer

    uiInputTextDeactivatedState()    { memset((void*)this, 0, sizeof(*this)); }
    void    ClearFreeMemory()           { ID = 0; TextA.clear(); }
};

// Forward declare imstb_textedit.h structure + make its main configuration define accessible
#undef IMSTB_TEXTEDIT_STRING
#undef IMSTB_TEXTEDIT_CHARTYPE
#define IMSTB_TEXTEDIT_STRING             uiInputTextState
#define IMSTB_TEXTEDIT_CHARTYPE           char
#define IMSTB_TEXTEDIT_GETWIDTH_NEWLINE   (-1.0f)
#define IMSTB_TEXTEDIT_UNDOSTATECOUNT     99
#define IMSTB_TEXTEDIT_UNDOCHARCOUNT      999
namespace ImStb { struct STB_TexteditState; }
typedef ImStb::STB_TexteditState ImStbTexteditState;

// Internal state of the currently focused/edited text input box
// For a given item ID, access with UI::GetInputTextState()
struct IMGUI_API uiInputTextState
{
    uiContext*           Ctx;                    // parent UI context (needs to be set explicitly by parent).
    ImStbTexteditState*     Stb;                    // State for stb_textedit.h
    uiInputTextFlags     Flags;                  // copy of InputText() flags. may be used to check if e.g. uiInputTextFlags_Password is set.
    uiID                 ID;                     // widget id owning the text state
    int                     TextLen;                // UTF-8 length of the string in TextA (in bytes)
    const char*             TextSrc;                // == TextA.Data unless read-only, in which case == buf passed to InputText(). For _ReadOnly fields, pointer will be null outside the InputText() call.
    ImVector<char>          TextA;                  // main UTF8 buffer. TextA.Size is a buffer size! Should always be >= buf_size passed by user (and of course >= CurLenA + 1).
    ImVector<char>          TextToRevertTo;         // value to revert to when pressing Escape = backup of end-user buffer at the time of focus (in UTF-8, unaltered)
    ImVector<char>          CallbackTextBackup;     // temporary storage for callback to support automatic reconcile of undo-stack
    int                     BufCapacity;            // end-user buffer capacity (include zero terminator)
    vec2                  Scroll;                 // horizontal offset (managed manually) + vertical scrolling (pulled from child window's own Scroll.y)
    int                     LineCount;              // last line count (solely for debugging)
    float                   WrapWidth;              // word-wrapping width
    float                   CursorAnim;             // timer for cursor blink, reset on every user action so the cursor reappears immediately
    bool                    CursorFollow;           // set when we want scrolling to follow the current cursor position (not always!)
    bool                    CursorCenterY;          // set when we want scrolling to be centered over the cursor position (while resizing a word-wrapping field)
    bool                    SelectedAllMouseLock;   // after a double-click to select all, we ignore further mouse drags to update selection
    bool                    EditedBefore;           // edited since activated
    bool                    EditedThisFrame;        // edited this frame
    bool                    WantReloadUserBuf;      // force a reload of user buf so it may be modified externally. may be automatic in future version.
    ImS8                    LastMoveDirectionLR;    // Var::Dir_Left or Var::Dir_Right. track last movement direction so when cursor cross over a word-wrapping boundaries we can display it on either line depending on last move.s
    int                     ReloadSelectionStart;
    int                     ReloadSelectionEnd;

    uiInputTextState();
    ~uiInputTextState();
    void        ClearText()                 { TextLen = 0; TextA[0] = 0; CursorClamp(); }
    void        ClearFreeMemory()           { TextA.clear(); TextToRevertTo.clear(); }
    void        OnKeyPressed(int key);      // Cannot be inline because we call in code in stb_textedit.h implementation
    void        OnCharPressed(unsigned int c);
    float       GetPreferredOffsetX() const;
    const char* GetText()                   { return TextA.Data ? TextA.Data : ""; }

    // Cursor & Selection
    void        CursorAnimReset();
    void        CursorClamp();
    bool        HasSelection() const;
    void        ClearSelection();
    int         GetCursorPos() const;
    int         GetSelectionStart() const;
    int         GetSelectionEnd() const;
    void        SetSelection(int start, int end);
    void        SelectAll();

    // Reload user buf (WIP #2890)
    // If you modify underlying user-passed const char* while active you need to call this (InputText V2 may lift this)
    //   strcpy(my_buf, "hello");
    //   if (uiInputTextState* state = UI::GetInputTextState(id)) // id may be UI::GetItemID() is last item
    //       state->ReloadUserBufAndSelectAll();
    void        ReloadUserBufAndSelectAll();
    void        ReloadUserBufAndKeepSelection();
    void        ReloadUserBufAndMoveToEnd();
};

enum uiWindowRefreshFlags_
{
    uiWindowRefreshFlags_None                = 0,
    uiWindowRefreshFlags_TryToAvoidRefresh   = 1 << 0,   // [EXPERIMENTAL] Try to keep existing contents, USER MUST NOT HONOR BEGIN() RETURNING FALSE AND NOT APPEND.
    uiWindowRefreshFlags_RefreshOnHover      = 1 << 1,   // [EXPERIMENTAL] Always refresh on hover
    uiWindowRefreshFlags_RefreshOnFocus      = 1 << 2,   // [EXPERIMENTAL] Always refresh on focus
    // Refresh policy/frequency, Load Balancing etc.
};

enum uiWindowBgClickFlags_
{
    uiWindowBgClickFlags_None                = 0,
    uiWindowBgClickFlags_Move                = 1 << 0,   // Click on bg/void + drag to move window. Cleared by default when using io.ConfigWindowsMoveFromTitleBarOnly.
};

enum uiNextWindowDataFlags_
{
    uiNextWindowDataFlags_None               = 0,
    uiNextWindowDataFlags_HasPos             = 1 << 0,
    uiNextWindowDataFlags_HasSize            = 1 << 1,
    uiNextWindowDataFlags_HasContentSize     = 1 << 2,
    uiNextWindowDataFlags_HasCollapsed       = 1 << 3,
    uiNextWindowDataFlags_HasSizeConstraint  = 1 << 4,
    uiNextWindowDataFlags_HasFocus           = 1 << 5,
    uiNextWindowDataFlags_HasBgAlpha         = 1 << 6,
    uiNextWindowDataFlags_HasScroll          = 1 << 7,
    uiNextWindowDataFlags_HasWindowFlags     = 1 << 8,
    uiNextWindowDataFlags_HasChildFlags      = 1 << 9,
    uiNextWindowDataFlags_HasRefreshPolicy   = 1 << 10,
    uiNextWindowDataFlags_HasViewport        = 1 << 11,
    uiNextWindowDataFlags_HasDock            = 1 << 12,
    uiNextWindowDataFlags_HasWindowClass     = 1 << 13,
};

// Storage for SetNexWindow** functions
struct uiNextWindowData
{
    uiNextWindowDataFlags    HasFlags;

    // Members below are NOT cleared. Always rely on HasFlags.
    uiCond                   PosCond;
    uiCond                   SizeCond;
    uiCond                   CollapsedCond;
    uiCond                   DockCond;
    vec2                      PosVal;
    vec2                      PosPivotVal;
    vec2                      SizeVal;
    vec2                      ContentSizeVal;
    vec2                      ScrollVal;
    uiWindowFlags            WindowFlags;            // Only honored by BeginTable()
    uiChildFlags             ChildFlags;
    bool                        PosUndock;
    bool                        CollapsedVal;
    ImRect                      SizeConstraintRect;
    uiSizeCallback           SizeCallback;
    void*                       SizeCallbackUserData;
    float                       BgAlphaVal;             // Override background alpha
    uiID                     ViewportId;
    uiID                     DockId;
    uiWindowClass            WindowClass;
    vec2                      MenuBarOffsetMinVal;    // (Always on) This is not exposed publicly, so we don't clear it and it doesn't have a corresponding flag (could we? for consistency?)
    uiWindowRefreshFlags     RefreshFlagsVal;

    uiNextWindowData()       { memset((void*)this, 0, sizeof(*this)); }
    inline void ClearFlags()    { HasFlags = uiNextWindowDataFlags_None; }
};

enum uiNextItemDataFlags_
{
    uiNextItemDataFlags_None             = 0,
    uiNextItemDataFlags_HasWidth         = 1 << 0,
    uiNextItemDataFlags_HasOpen          = 1 << 1,
    uiNextItemDataFlags_HasShortcut      = 1 << 2,
    uiNextItemDataFlags_HasRefVal        = 1 << 3,
    uiNextItemDataFlags_HasStorageID     = 1 << 4,
    uiNextItemDataFlags_HasColorMarker   = 1 << 5,
};

struct uiNextItemData
{
    uiNextItemDataFlags      HasFlags;           // Called HasFlags instead of Flags to avoid mistaking this
    uiItemFlags              ItemFlags;          // Currently only tested/used for uiItemFlags_AllowOverlap and uiItemFlags_HasSelectionUserData.

    // Members below are NOT cleared by ItemAdd() meaning they are still valid during e.g. NavProcessItem(). Always rely on HasFlags.
    uiID                     FocusScopeId;       // Set by SetNextItemSelectionUserData()
    uiSelectionUserData      SelectionUserData;  // Set by SetNextItemSelectionUserData() (note that NULL/0 is a valid value, we use -1 == uiSelectionUserData_Invalid to mark invalid values)
    float                       Width;              // Set by SetNextItemWidth()
    uiKeyChord               Shortcut;           // Set by SetNextItemShortcut()
    uiInputFlags             ShortcutFlags;      // Set by SetNextItemShortcut()
    bool                        OpenVal;            // Set by SetNextItemOpen()
    ImU8                        OpenCond;           // Set by SetNextItemOpen()
    uiDataTypeStorage        RefVal;             // Not exposed yet, for uiInputTextFlags_ParseEmptyAsRefVal
    uiID                     StorageId;          // Set by SetNextItemStorageID()
    ImU32                       ColorMarker;        // Set by SetNextItemColorMarker(). Not exposed yet, supported by DragScalar,SliderScalar and for uiSliderFlags_ColorMarkers.

    uiNextItemData()         { memset((void*)this, 0, sizeof(*this)); SelectionUserData = -1; }
    inline void ClearFlags()    { HasFlags = uiNextItemDataFlags_None; ItemFlags = uiItemFlags_None; } // Also cleared manually by ItemAdd()!
};

// Status storage for the last submitted item
struct uiLastItemData
{
    uiID                 ID;
    uiItemFlags          ItemFlags;          // See uiItemFlags_ (called 'InFlags' before v1.91.4).
    uiItemStatusFlags    StatusFlags;        // See uiItemStatusFlags_
    ImRect                  Rect;               // Full rectangle
    ImRect                  NavRect;            // Navigation scoring rectangle (not displayed)
    // Rarely used fields are not explicitly cleared, only valid when the corresponding uiItemStatusFlags are set.
    ImRect                  DisplayRect;        // Display rectangle. ONLY VALID IF (StatusFlags & uiItemStatusFlags_HasDisplayRect) is set.
    ImRect                  ClipRect;           // Clip rectangle at the time of submitting item. ONLY VALID IF (StatusFlags & uiItemStatusFlags_HasClipRect) is set..
    uiKeyChord           Shortcut;           // Shortcut at the time of submitting item. ONLY VALID IF (StatusFlags & uiItemStatusFlags_HasShortcut) is set..

    uiLastItemData()     { memset((void*)this, 0, sizeof(*this)); }
};

// Store data emitted by TreeNode() for usage by TreePop()
// - To implement uiTreeFlags_NavLeftJumpsToParent: store the minimum amount of data
//   which we can't infer in TreePop(), to perform the equivalent of NavApplyItemToResult().
//   Only stored when the node is a potential candidate for landing on a Left arrow jump.
struct uiTreeNodeStackData
{
    uiID                 ID;
    uiTreeFlags      TreeFlags;
    uiItemFlags          ItemFlags;      // Used for nav landing
    ImRect                  NavRect;        // Used for nav landing
    float                   DrawLinesX1;
    float                   DrawLinesToNodesY2;
    uiTableColumnIdx     DrawLinesTableColumn;
};

// sizeof() = 20
struct IMGUI_API uiErrorRecoveryState
{
    short SizeOfWindowStack;
    short SizeOfIDStack;
    short SizeOfTreeStack;
    short SizeOfColorStack;
    short SizeOfStyleVarStack;
    short SizeOfFontStack;
    short SizeOfFocusScopeStack;
    short SizeOfGroupStack;
    short SizeOfItemFlagsStack;
    short SizeOfBeginPopupStack;
    short SizeOfDisabledStack;

    uiErrorRecoveryState() { memset((void*)this, 0, sizeof(*this)); }
};

// Data saved for each window pushed into the stack
struct uiWindowStackData
{
    uiWindow*            Window;
    uiLastItemData       ParentLastItemDataBackup;
    uiErrorRecoveryState StackSizesInBegin;          // Store size of various stacks for asserting
    bool                    DisabledOverrideReenable;   // Non-child window override disabled flag
    float                   DisabledOverrideReenableAlphaBackup;
};

struct uiShrinkWidthItem
{
    int         Index;
    float       Width;
    float       InitialWidth;
};

struct uiPtrOrIndex
{
    void*       Ptr;            // Either field can be set, not both. e.g. Dock node tab bars are loose while BeginTabBar() ones are in a pool.
    int         Index;          // Usually index in a main pool.

    uiPtrOrIndex(void* ptr)  { Ptr = ptr; Index = -1; }
    uiPtrOrIndex(int index)  { Ptr = NULL; Index = index; }
};

// Data used by IsItemDeactivated()/IsItemDeactivatedAfterEdit() functions
// Also see uiInputTextDeactivatedState which is an extension for this for InputText()
struct uiDeactivatedItemData
{
    uiID     ID;
    int         ElapseFrame;
    bool        HasBeenEditedBefore;
    bool        IsAlive;
};

//-----------------------------------------------------------------------------
// [SECTION] Popup support
//-----------------------------------------------------------------------------

enum uiPopupPositionPolicy
{
    uiPopupPositionPolicy_Default,
    uiPopupPositionPolicy_ComboBox,
    uiPopupPositionPolicy_Tooltip,
};

// Storage for popup stacks (g.OpenPopupStack and g.BeginPopupStack)
struct uiPopupData
{
    uiID             PopupId;        // Set on OpenPopup()
    uiWindow*        Window;         // Resolved on BeginPopup() - may stay unresolved if user never calls OpenPopup()
    uiWindow*        RestoreNavWindow;// Set on OpenPopup(), a NavWindow that will be restored on popup close
    int                 ParentNavLayer; // Resolved on BeginPopup(). Actually a uiNavLayer type (declared down below), initialized to -1 which is not part of an enum, but serves well-enough as "not any of layers" value
    int                 OpenFrameCount; // Set on OpenPopup()
    uiID             OpenParentId;   // Set on OpenPopup(), we need this to differentiate multiple menu sets from each others (e.g. inside menu bar vs loose menu items)
    vec2              OpenPopupPos;   // Set on OpenPopup(), preferred popup position (typically == OpenMousePos when using mouse)
    vec2              OpenMousePos;   // Set on OpenPopup(), copy of mouse position at the time of opening popup

    uiPopupData()    { memset((void*)this, 0, sizeof(*this)); ParentNavLayer = OpenFrameCount = -1; }
};

//-----------------------------------------------------------------------------
// [SECTION] Inputs support
//-----------------------------------------------------------------------------

// Bit array for named keys
typedef ImBitArray<uiKey_NamedKey_COUNT, -uiKey_NamedKey_BEGIN>    ImBitArrayForNamedKeys;

// [Internal] Key ranges
#define uiKey_LegacyNativeKey_BEGIN  0
#define uiKey_LegacyNativeKey_END    512
#define uiKey_Keyboard_BEGIN         (uiKey_NamedKey_BEGIN)
#define uiKey_Keyboard_END           (uiKey_GamepadStart)
#define uiKey_Gamepad_BEGIN          (uiKey_GamepadStart)
#define uiKey_Gamepad_END            (uiKey_GamepadRStickDown + 1)
#define uiKey_Mouse_BEGIN            (uiKey_MouseLeft)
#define uiKey_Mouse_END              (uiKey_MouseWheelY + 1)
#define uiKey_Aliases_BEGIN          (uiKey_Mouse_BEGIN)
#define uiKey_Aliases_END            (uiKey_Mouse_END)

// [Internal] Named shortcuts for Navigation
#define uiKey_NavKeyboardTweakSlow   uiMod_Ctrl
#define uiKey_NavKeyboardTweakFast   uiMod_Shift
#define uiKey_NavGamepadTweakSlow    uiKey_GamepadL1
#define uiKey_NavGamepadTweakFast    uiKey_GamepadR1
#define uiKey_NavGamepadActivate     (g.IO.ConfigNavSwapGamepadButtons ? uiKey_GamepadFaceRight : uiKey_GamepadFaceDown)
#define uiKey_NavGamepadCancel       (g.IO.ConfigNavSwapGamepadButtons ? uiKey_GamepadFaceDown : uiKey_GamepadFaceRight)
#define uiKey_NavGamepadMenu         uiKey_GamepadFaceLeft    // Toggle menu layer. Hold to enable Windowing.
#define uiKey_NavGamepadContextMenu  uiKey_GamepadFaceUp      // Open context menu (same as Shift+F10)

enum uiInputEventType
{
    uiInputEventType_None = 0,
    uiInputEventType_MousePos,
    uiInputEventType_MouseWheel,
    uiInputEventType_MouseButton,
    uiInputEventType_MouseViewport,
    uiInputEventType_Key,
    uiInputEventType_Text,
    uiInputEventType_Focus,
    uiInputEventType_COUNT
};

enum uiInputSource : int
{
    uiInputSource_None = 0,
    uiInputSource_Mouse,         // Note: may be Mouse or TouchScreen or Pen. See io.MouseSource to distinguish them.
    uiInputSource_Keyboard,
    uiInputSource_Gamepad,
    uiInputSource_COUNT
};

// FIXME: Structures in the union below need to be declared as anonymous unions appears to be an extension?
// Using vec2() would fail on Clang 'union member 'MousePos' has a non-trivial default constructor'
struct uiInputEventMousePos      { float PosX, PosY; uiMouseSource MouseSource; };
struct uiInputEventMouseWheel    { float WheelX, WheelY; uiMouseSource MouseSource; };
struct uiInputEventMouseButton   { int Button; bool Down; uiMouseSource MouseSource; };
struct uiInputEventMouseViewport { uiID HoveredViewportID; };
struct uiInputEventKey           { uiKey Key; bool Down; float AnalogValue; };
struct uiInputEventText          { unsigned int Char; };
struct uiInputEventAppFocused    { bool Focused; };

struct uiInputEvent
{
    uiInputEventType             Type;
    uiInputSource                Source;
    ImU32                           EventId;        // Unique, sequential increasing integer to identify an event (if you need to correlate them to other data).
    union
    {
        uiInputEventMousePos     MousePos;       // if Type == uiInputEventType_MousePos
        uiInputEventMouseWheel   MouseWheel;     // if Type == uiInputEventType_MouseWheel
        uiInputEventMouseButton  MouseButton;    // if Type == uiInputEventType_MouseButton
        uiInputEventMouseViewport MouseViewport; // if Type == uiInputEventType_MouseViewport
        uiInputEventKey          Key;            // if Type == uiInputEventType_Key
        uiInputEventText         Text;           // if Type == uiInputEventType_Text
        uiInputEventAppFocused   AppFocused;     // if Type == uiInputEventType_Focus
    };
    bool                            AddedByTestEngine;

    uiInputEvent() { memset((void*)this, 0, sizeof(*this)); }
};

// Input function taking an 'uiID owner_id' argument defaults to (uiKeyOwner_Any == 0) aka don't test ownership, which matches legacy behavior.
#define uiKeyOwner_Any           ((uiID)0)    // Accept key that have an owner, UNLESS a call to SetKeyOwner() explicitly used uiInputFlags_LockThisFrame or uiInputFlags_LockUntilRelease.
#define uiKeyOwner_NoOwner       ((uiID)-1)   // Require key to have no owner.
//#define uiKeyOwner_None uiKeyOwner_NoOwner  // We previously called this 'uiKeyOwner_None' but it was inconsistent with our pattern that _None values == 0 and quite dangerous. Also using _NoOwner makes the IsKeyPressed() calls more explicit.

typedef ImS16 uiKeyRoutingIndex;

// Routing table entry (sizeof() == 16 bytes)
struct uiKeyRoutingData
{
    uiKeyRoutingIndex            NextEntryIndex;
    ImU16                           Mods;               // Technically we'd only need 4-bits but for simplify we store uiMod_ values which need 16-bits.
    ImU16                           RoutingCurrScore;   // [DEBUG] For debug display
    ImU16                           RoutingNextScore;   // Lower is better (0: perfect score)
    uiID                         RoutingCurr;
    uiID                         RoutingNext;

    uiKeyRoutingData()           { NextEntryIndex = -1; Mods = 0; RoutingCurrScore = RoutingNextScore = 0; RoutingCurr = RoutingNext = uiKeyOwner_NoOwner; }
};

// Routing table: maintain a desired owner for each possible key-chord (key + mods), and setup owner in NewFrame() when mods are matching.
// Stored in main context (1 instance)
struct uiKeyRoutingTable
{
    uiKeyRoutingIndex            Index[uiKey_NamedKey_COUNT]; // Index of first entry in Entries[]
    ImVector<uiKeyRoutingData>   Entries;
    ImVector<uiKeyRoutingData>   EntriesNext;                    // Double-buffer to avoid reallocation (could use a shared buffer)

    uiKeyRoutingTable()          { Clear(); }
    void Clear()                    { for (int n = 0; n < IM_COUNTOF(Index); n++) Index[n] = -1; Entries.clear(); EntriesNext.clear(); }
};

// This extends uiKeyData but only for named keys (legacy keys don't support the new features)
// Stored in main context (1 per named key). In the future it might be merged into uiKeyData.
struct uiKeyOwnerData
{
    uiID     OwnerCurr;
    uiID     OwnerNext;
    bool        LockThisFrame;      // Reading this key requires explicit owner id (until end of frame). Set by uiInputFlags_LockThisFrame.
    bool        LockUntilRelease;   // Reading this key requires explicit owner id (until key is released). Set by uiInputFlags_LockUntilRelease. When this is true LockThisFrame is always true as well.

    uiKeyOwnerData()             { OwnerCurr = OwnerNext = uiKeyOwner_NoOwner; LockThisFrame = LockUntilRelease = false; }
};

// Extend uiInputFlags_
// Flags for extended versions of IsKeyPressed(), IsMouseClicked(), Shortcut(), SetKeyOwner(), SetItemKeyOwner()
// Don't mistake with uiInputTextFlags! (which is for UI::InputText() function)
enum uiInputFlagsPrivate_
{
    // Flags for IsKeyPressed(), IsKeyChordPressed(), IsMouseClicked(), Shortcut()
    // - Repeat mode: Repeat rate selection
    uiInputFlags_RepeatRateDefault           = 1 << 1,   // Repeat rate: Regular (default)
    uiInputFlags_RepeatRateNavMove           = 1 << 2,   // Repeat rate: Fast
    uiInputFlags_RepeatRateNavTweak          = 1 << 3,   // Repeat rate: Faster
    // - Repeat mode: Specify when repeating key pressed can be interrupted.
    // - In theory uiInputFlags_RepeatUntilOtherKeyPress may be a desirable default, but it would break too many behavior so everything is opt-in.
    uiInputFlags_RepeatUntilRelease          = 1 << 4,   // Stop repeating when released (default for all functions except Shortcut). This only exists to allow overriding Shortcut() default behavior.
    uiInputFlags_RepeatUntilKeyModsChange    = 1 << 5,   // Stop repeating when released OR if keyboard mods are changed (default for Shortcut)
    uiInputFlags_RepeatUntilKeyModsChangeFromNone = 1 << 6,  // Stop repeating when released OR if keyboard mods are leaving the None state. Allows going from Mod+Key to Key by releasing Mod.
    uiInputFlags_RepeatUntilOtherKeyPress    = 1 << 7,   // Stop repeating when released OR if any other keyboard key is pressed during the repeat

    // Flags for SetKeyOwner(), SetItemKeyOwner()
    // - Locking key away from non-input aware code. Locking is useful to make input-owner-aware code steal keys from non-input-owner-aware code. If all code is input-owner-aware locking would never be necessary.
    uiInputFlags_LockThisFrame               = 1 << 20,  // Further accesses to key data will require EXPLICIT owner ID (uiKeyOwner_Any/0 will NOT accepted for polling). Cleared at end of frame.
    uiInputFlags_LockUntilRelease            = 1 << 21,  // Further accesses to key data will require EXPLICIT owner ID (uiKeyOwner_Any/0 will NOT accepted for polling). Cleared when the key is released or at end of each frame if key is released.

    // - Condition for SetItemKeyOwner()
    uiInputFlags_CondHovered                 = 1 << 22,  // Only set if item is hovered (default to both)
    uiInputFlags_CondActive                  = 1 << 23,  // Only set if item is active (default to both)
    uiInputFlags_CondDefault_                = uiInputFlags_CondHovered | uiInputFlags_CondActive,

    // [Internal] Mask of which function support which flags
    uiInputFlags_RepeatRateMask_             = uiInputFlags_RepeatRateDefault | uiInputFlags_RepeatRateNavMove | uiInputFlags_RepeatRateNavTweak,
    uiInputFlags_RepeatUntilMask_            = uiInputFlags_RepeatUntilRelease | uiInputFlags_RepeatUntilKeyModsChange | uiInputFlags_RepeatUntilKeyModsChangeFromNone | uiInputFlags_RepeatUntilOtherKeyPress,
    uiInputFlags_RepeatMask_                 = uiInputFlags_Repeat | uiInputFlags_RepeatRateMask_ | uiInputFlags_RepeatUntilMask_,
    uiInputFlags_CondMask_                   = uiInputFlags_CondHovered | uiInputFlags_CondActive,
    uiInputFlags_RouteTypeMask_              = uiInputFlags_RouteActive | uiInputFlags_RouteFocused | uiInputFlags_RouteGlobal | uiInputFlags_RouteAlways,
    uiInputFlags_RouteOptionsMask_           = uiInputFlags_RouteOverFocused | uiInputFlags_RouteOverActive | uiInputFlags_RouteUnlessBgFocused | uiInputFlags_RouteFromRootWindow,
    uiInputFlags_SupportedByIsKeyPressed     = uiInputFlags_RepeatMask_,
    uiInputFlags_SupportedByIsMouseClicked   = uiInputFlags_Repeat,
    uiInputFlags_SupportedByShortcut         = uiInputFlags_RepeatMask_ | uiInputFlags_RouteTypeMask_ | uiInputFlags_RouteOptionsMask_,
    uiInputFlags_SupportedBySetNextItemShortcut = uiInputFlags_RepeatMask_ | uiInputFlags_RouteTypeMask_ | uiInputFlags_RouteOptionsMask_ | uiInputFlags_Tooltip,
    uiInputFlags_SupportedBySetKeyOwner      = uiInputFlags_LockThisFrame | uiInputFlags_LockUntilRelease,
    uiInputFlags_SupportedBySetItemKeyOwner  = uiInputFlags_SupportedBySetKeyOwner | uiInputFlags_CondMask_,
};

//-----------------------------------------------------------------------------
// [SECTION] Clipper support
//-----------------------------------------------------------------------------

// Note that Max is exclusive, so perhaps should be using a Begin/End convention.
struct uiListClipperRange
{
    int     Min;
    int     Max;
    bool    PosToIndexConvert;      // Begin/End are absolute position (will be converted to indices later)
    ImS8    PosToIndexOffsetMin;    // Add to Min after converting to indices
    ImS8    PosToIndexOffsetMax;    // Add to Min after converting to indices

    static uiListClipperRange    FromIndices(int min, int max)                               { uiListClipperRange r = { min, max, false, 0, 0 }; return r; }
    static uiListClipperRange    FromPositions(float y1, float y2, int off_min, int off_max) { uiListClipperRange r = { (int)y1, (int)y2, true, (ImS8)off_min, (ImS8)off_max }; return r; }
};

// Temporary clipper data, buffers shared/reused between instances
struct uiListClipperData
{
    uiListClipper*               ListClipper;
    float                           LossynessOffset;
    int                             StepNo;
    int                             ItemsFrozen;
    ImVector<uiListClipperRange> Ranges;

    uiListClipperData()          { memset((void*)this, 0, sizeof(*this)); }
    void                            Reset(uiListClipper* clipper) { ListClipper = clipper; StepNo = ItemsFrozen = 0; Ranges.resize(0); }
};

//-----------------------------------------------------------------------------
// [SECTION] Navigation support
//-----------------------------------------------------------------------------

enum uiActivateFlags_
{
    uiActivateFlags_None                 = 0,
    uiActivateFlags_PreferInput          = 1 << 0,       // Favor activation that requires keyboard text input (e.g. for Slider/Drag). Default for Enter key.
    uiActivateFlags_PreferTweak          = 1 << 1,       // Favor activation for tweaking with arrows or gamepad (e.g. for Slider/Drag). Default for Space key and if keyboard is not used.
    uiActivateFlags_TryToPreserveState   = 1 << 2,       // Request widget to preserve state if it can (e.g. InputText will try to preserve cursor/selection)
    uiActivateFlags_FromTabbing          = 1 << 3,       // Activation requested by a tabbing request (uiNavMoveFlags_IsTabbing)
    uiActivateFlags_FromShortcut         = 1 << 4,       // Activation requested by an item shortcut via SetNextItemShortcut() function.
    uiActivateFlags_FromFocusApi         = 1 << 5,       // Activation requested by an api request (uiNavMoveFlags_FocusApi)
};

// Early work-in-progress API for ScrollToItem()
// FIXME: Missing flags to request making both edges visible when possible.
enum uiScrollFlags_
{
    uiScrollFlags_None                   = 0,
    uiScrollFlags_KeepVisibleEdgeX       = 1 << 0,       // If item is not visible: scroll as little as possible on X axis to bring item back into view [default for X axis]
    uiScrollFlags_KeepVisibleEdgeY       = 1 << 1,       // If item is not visible: scroll as little as possible on Y axis to bring item back into view [default for Y axis for windows that are already visible]
    uiScrollFlags_KeepVisibleCenterX     = 1 << 2,       // If item is not visible: scroll to make the item centered on X axis [rarely used]
    uiScrollFlags_KeepVisibleCenterY     = 1 << 3,       // If item is not visible: scroll to make the item centered on Y axis
    uiScrollFlags_AlwaysCenterX          = 1 << 4,       // Always center the result item on X axis [rarely used]
    uiScrollFlags_AlwaysCenterY          = 1 << 5,       // Always center the result item on Y axis [default for Y axis for appearing window)
    uiScrollFlags_NoScrollParent         = 1 << 6,       // Disable forwarding scrolling to parent window if required to keep item/rect visible (only scroll window the function was applied to).
    uiScrollFlags_MaskX_                 = uiScrollFlags_KeepVisibleEdgeX | uiScrollFlags_KeepVisibleCenterX | uiScrollFlags_AlwaysCenterX,
    uiScrollFlags_MaskY_                 = uiScrollFlags_KeepVisibleEdgeY | uiScrollFlags_KeepVisibleCenterY | uiScrollFlags_AlwaysCenterY,
};

enum uiNavRenderCursorFlags_
{
    uiNavRenderCursorFlags_None          = 0,
    uiNavRenderCursorFlags_Compact       = 1 << 1,       // Compact highlight, no padding/distance from focused item
    uiNavRenderCursorFlags_AlwaysDraw    = 1 << 2,       // Draw rectangular highlight if (g.NavId == id) even when g.NavCursorVisible == false, aka even when using the mouse.
    uiNavRenderCursorFlags_NoRounding    = 1 << 3,
};

enum uiNavMoveFlags_
{
    uiNavMoveFlags_None                  = 0,
    uiNavMoveFlags_LoopX                 = 1 << 0,   // On failed request, restart from opposite side
    uiNavMoveFlags_LoopY                 = 1 << 1,
    uiNavMoveFlags_WrapX                 = 1 << 2,   // On failed request, request from opposite side one line down (when NavDir==right) or one line up (when NavDir==left)
    uiNavMoveFlags_WrapY                 = 1 << 3,   // This is not super useful but provided for completeness
    uiNavMoveFlags_WrapMask_             = uiNavMoveFlags_LoopX | uiNavMoveFlags_LoopY | uiNavMoveFlags_WrapX | uiNavMoveFlags_WrapY,
    uiNavMoveFlags_AllowCurrentNavId     = 1 << 4,   // Allow scoring and considering the current NavId as a move target candidate. This is used when the move source is offset (e.g. pressing PageDown actually needs to send a Up move request, if we are pressing PageDown from the bottom-most item we need to stay in place)
    uiNavMoveFlags_AlsoScoreVisibleSet   = 1 << 5,   // Store alternate result in NavMoveResultLocalVisible that only comprise elements that are already fully visible (used by PageUp/PageDown)
    uiNavMoveFlags_ScrollToEdgeY         = 1 << 6,   // Force scrolling to min/max (used by Home/End) // FIXME-NAV: Aim to remove or reword as uiScrollFlags
    uiNavMoveFlags_Forwarded             = 1 << 7,
    uiNavMoveFlags_DebugNoResult         = 1 << 8,   // Dummy scoring for debug purpose, don't apply result
    uiNavMoveFlags_FocusApi              = 1 << 9,   // Requests from focus API can land/focus/activate items even if they are marked with _NoTabStop (see NavProcessItemForTabbingRequest() for details)
    uiNavMoveFlags_IsTabbing             = 1 << 10,  // == Focus + Activate if item is Inputable + DontChangeNavHighlight
    uiNavMoveFlags_IsPageMove            = 1 << 11,  // Identify a PageDown/PageUp request.
    uiNavMoveFlags_Activate              = 1 << 12,  // Activate/select target item.
    uiNavMoveFlags_NoSelect              = 1 << 13,  // Don't trigger selection by not setting g.NavJustMovedTo
    uiNavMoveFlags_NoSetNavCursorVisible = 1 << 14,  // Do not alter the nav cursor visible state
    uiNavMoveFlags_NoClearActiveId       = 1 << 15,  // (Experimental) Do not clear active id when applying move result
};

enum uiNavLayer
{
    uiNavLayer_Main  = 0,    // Main scrolling layer
    uiNavLayer_Menu  = 1,    // Menu layer (access with Alt)
    uiNavLayer_COUNT
};

// Storage for navigation query/results
struct uiNavItemData
{
    uiWindow*        Window;         // Init,Move    // Best candidate window (result->ItemWindow->RootWindowForNav == request->Window)
    uiID             ID;             // Init,Move    // Best candidate item ID
    uiID             FocusScopeId;   // Init,Move    // Best candidate focus scope ID
    ImRect              RectRel;        // Init,Move    // Best candidate bounding box in window relative space
    uiItemFlags      ItemFlags;      // ????,Move    // Best candidate item flags
    float               DistBox;        //      Move    // Best candidate box distance to current NavId
    float               DistCenter;     //      Move    // Best candidate center distance to current NavId
    float               DistAxial;      //      Move    // Best candidate axial distance to current NavId
    uiSelectionUserData SelectionUserData;//I+Mov    // Best candidate SetNextItemSelectionUserData() value. Valid if (ItemFlags & uiItemFlags_HasSelectionUserData)

    uiNavItemData()  { Clear(); }
    void Clear()        { Window = NULL; ID = FocusScopeId = 0; ItemFlags = 0; SelectionUserData = -1; DistBox = DistCenter = DistAxial = FLT_MAX; }
};

// Storage for PushFocusScope(), g.FocusScopeStack[], g.NavFocusRoute[]
struct uiFocusScopeData
{
    uiID             ID;
    uiID             WindowID;
};

//-----------------------------------------------------------------------------
// [SECTION] Typing-select support
//-----------------------------------------------------------------------------

// Flags for GetTypingSelectRequest()
enum uiTypingSelectFlags_
{
    uiTypingSelectFlags_None                 = 0,
    uiTypingSelectFlags_AllowBackspace       = 1 << 0,   // Backspace to delete character inputs. If using: ensure GetTypingSelectRequest() is not called more than once per frame (filter by e.g. focus state)
    uiTypingSelectFlags_AllowSingleCharMode  = 1 << 1,   // Allow "single char" search mode which is activated when pressing the same character multiple times.
};

// Returned by GetTypingSelectRequest(), designed to eventually be public.
struct IMGUI_API uiTypingSelectRequest
{
    uiTypingSelectFlags  Flags;              // Flags passed to GetTypingSelectRequest()
    int                     SearchBufferLen;
    const char*             SearchBuffer;       // Search buffer contents (use full string. unless SingleCharMode is set, in which case use SingleCharSize).
    bool                    SelectRequest;      // Set when buffer was modified this frame, requesting a selection.
    bool                    SingleCharMode;     // Notify when buffer contains same character repeated, to implement special mode. In this situation it preferred to not display any on-screen search indication.
    ImS8                    SingleCharSize;     // Length in bytes of first letter codepoint (1 for ascii, 2-4 for UTF-8). If (SearchBufferLen==RepeatCharSize) only 1 letter has been input.
};

// Storage for GetTypingSelectRequest()
struct IMGUI_API uiTypingSelectState
{
    uiTypingSelectRequest Request;           // User-facing data
    char            SearchBuffer[64];           // Search buffer: no need to make dynamic as this search is very transient.
    uiID         FocusScope;
    int             LastRequestFrame = 0;
    float           LastRequestTime = 0.0f;
    bool            SingleCharModeLock = false; // After a certain single char repeat count we lock into SingleCharMode. Two benefits: 1) buffer never fill, 2) we can provide an immediate SingleChar mode without timer elapsing.

    uiTypingSelectState() { memset((void*)this, 0, sizeof(*this)); }
    void            Clear()  { SearchBuffer[0] = 0; SingleCharModeLock = false; } // We preserve remaining data for easier debugging
};

//-----------------------------------------------------------------------------
// [SECTION] Columns support
//-----------------------------------------------------------------------------
// Flags for internal's BeginColumns(). This is an obsolete API. Prefer using BeginTable() nowadays!
enum uiOldColumnFlags_ {
    uiOldColumnFlags_None                   = 0,
    uiOldColumnFlags_NoBorder               = 1 << 0, // Disable column dividers
    uiOldColumnFlags_NoResize               = 1 << 1, // Disable resizing columns when clicking on the dividers
    uiOldColumnFlags_NoPreserveWidths       = 1 << 2, // Disable column width preservation when adjusting columns
    uiOldColumnFlags_NoForceWithinWindow    = 1 << 3, // Disable forcing columns to fit within window
    uiOldColumnFlags_GrowParentContentsSize = 1 << 4, // Restore pre-1.51 behavior of extending the parent window contents size but _without affecting the columns width at all_. Will eventually remove.
};
struct uiOldColumnData {
    float            OffsetNorm; // Column start offset, normalized 0.0 (far left) -> 1.0 (far right)
    float            OffsetNormBeforeResize;
    uiOldColumnFlags Flags; // Not exposed
    ImRect           ClipRect;
    uiOldColumnData() { memset((void*)this, 0, sizeof(*this)); }
};
struct uiOldColumns {
    uiID             ID;
    uiOldColumnFlags Flags;
    bool             IsFirstFrame;
    bool             IsBeingResized;
    int              Current;
    int              Count;
    float            OffMinX, OffMaxX;         // Offsets from HostWorkRect.Min.x
    float            LineMinY, LineMaxY;
    float            HostCursorPosY;           // Backup of CursorPos at the time of BeginColumns()
    float            HostCursorMaxPosX;        // Backup of CursorMaxPos at the time of BeginColumns()
    ImRect           HostInitialClipRect;      // Backup of ClipRect at the time of BeginColumns()
    ImRect           HostBackupClipRect;       // Backup of ClipRect during PushColumnsBackground()/PopColumnsBackground()
    ImRect           HostBackupParentWorkRect; //Backup of WorkRect at the time of BeginColumns()
    ImVector<uiOldColumnData> Columns;
    ImDrawListSplitter Splitter;
    uiOldColumns() { memset((void*)this, 0, sizeof(*this)); }
};
//-----------------------------------------------------------------------------
// [SECTION] Box-select support
//-----------------------------------------------------------------------------

struct uiBoxSelectState
{
    // Active box-selection data (persistent, 1 active at a time)
    uiID                 ID;
    bool                    IsActive;
    bool                    IsStarting;
    bool                    IsStartedFromVoid;  // Starting click was not from an item.
    bool                    IsStartedSetNavIdOnce;
    bool                    RequestClear;
    uiKeyChord           KeyMods : 16;       // Latched key-mods for box-select logic.
    vec2                  StartPosRel;        // Start position in window-contents relative space (to support scrolling)
    vec2                  EndPosRel;          // End position in window-contents relative space
    vec2                  ScrollAccum;        // Scrolling accumulator (to behave at high-frame spaces)
    uiWindow*            Window;

    // Temporary/Transient data
    bool                    UnclipMode;         // (Temp/Transient, here in hot area). Set/cleared by the BeginMultiSelect()/EndMultiSelect() owning active box-select.
    ImRect                  UnclipRect;         // Rectangle where ItemAdd() clipping may be temporarily disabled. Need support by multi-select supporting widgets.
    ImRect                  UnclipRects[2];     // Per-axis versions.
    ImRect                  BoxSelectRectPrev;  // Selection rectangle in absolute coordinates (derived every frame from BoxSelectStartPosRel and MousePos)
    ImRect                  BoxSelectRectCurr;

    uiBoxSelectState()   { memset((void*)this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] Multi-select support
//-----------------------------------------------------------------------------

// We always assume that -1 is an invalid value (which works for indices and pointers)
#define uiSelectionUserData_Invalid        ((uiSelectionUserData)-1)

// Temporary storage for multi-select
struct IMGUI_API uiMultiSelectTempData
{
    uiMultiSelectIO      IO;                 // MUST BE FIRST FIELD. Requests are set and returned by BeginMultiSelect()/EndMultiSelect() + written to by user during the loop.
    uiMultiSelectState*  Storage;
    uiID                 FocusScopeId;       // Copied from g.CurrentFocusScopeId (unless another selection scope was pushed manually)
    uiMultiSelectFlags   Flags;
    vec2                  ScopeRectMin;
    vec2                  BackupCursorMaxPos;
    //uiSelectionUserData CurrSubmittedItem; // Copy of last submitted item data, used to merge output ranges.
    //uiSelectionUserData PrevSubmittedItem; // Copy of previous submitted item data, used to merge output ranges.
    uiID                 BoxSelectId;
    uiKeyChord           KeyMods;
    ImS8                    LoopRequestSetAll;  // -1: no operation, 0: clear all, 1: select all.
    bool                    IsEndIO;            // Set when switching IO from BeginMultiSelect() to EndMultiSelect() state.
    bool                    IsFocused;          // Set if currently focusing the selection scope (any item of the selection). May be used if you have custom shortcut associated to selection.
    bool                    IsKeyboardSetRange; // Set by BeginMultiSelect() when using Shift+Navigation. Because scrolling may be affected we can't afford a frame of lag with Shift+Navigation.
    bool                    NavIdPassedBy;
    bool                    RangeSrcPassedBy;   // Set by the item that matches RangeSrcItem.
    bool                    RangeDstPassedBy;   // Set by the item that matches NavJustMovedToId when IsSetRange is set.

    uiMultiSelectTempData()  { Clear(); }
    void Clear()            { size_t io_sz = sizeof(IO); ClearIO(); memset((void*)(&IO + 1), 0, sizeof(*this) - io_sz); } // Zero-clear except IO as we preserve IO.Requests[] buffer allocation.
    void ClearIO()          { IO.Requests.resize(0); IO.RangeSrcItem = IO.NavIdItem = uiSelectionUserData_Invalid; IO.NavIdSelected = IO.RangeSrcReset = false; }
};

// Persistent storage for multi-select (as long as selection is alive)
struct IMGUI_API uiMultiSelectState
{
    uiWindow*            Window;
    uiID                 ID;
    int                     LastFrameActive;    // Last used frame-count, for GC.
    int                     LastSelectionSize;  // Set by BeginMultiSelect() based on optional info provided by user. May be -1 if unknown.
    ImS8                    RangeSelected;      // -1 (don't have) or true/false
    ImS8                    NavIdSelected;      // -1 (don't have) or true/false
    uiSelectionUserData  RangeSrcItem;       //
    uiSelectionUserData  NavIdItem;          // SetNextItemSelectionUserData() value for NavId (if part of submitted items)

    uiMultiSelectState() { Window = NULL; ID = 0; LastFrameActive = LastSelectionSize = 0; RangeSelected = NavIdSelected = -1; RangeSrcItem = NavIdItem = uiSelectionUserData_Invalid; }
};

//-----------------------------------------------------------------------------
// [SECTION] Docking support
//-----------------------------------------------------------------------------

#define DOCKING_HOST_DRAW_CHANNEL_BG 0  // Dock host: background fill
#define DOCKING_HOST_DRAW_CHANNEL_FG 1  // Dock host: decorations and contents

#ifdef IMGUI_HAS_DOCK

// Store the source authority (dock node vs window) of a field
enum uiDataAuthority_
{
    uiDataAuthority_Auto,
    uiDataAuthority_DockNode,
    uiDataAuthority_Window,
};

enum uiDockNodeState
{
    uiDockNodeState_Unknown,
    uiDockNodeState_HostWindowHiddenBecauseSingleWindow,
    uiDockNodeState_HostWindowHiddenBecauseWindowsAreResizing,
    uiDockNodeState_HostWindowVisible,
};

// sizeof() 176~216
struct IMGUI_API uiDockNode {
    uiID                 ID;
    uiDockFlags      SharedFlags;                // (Write) Flags shared by all nodes of a same dockspace hierarchy (inherited from the root node)
    uiDockFlags      LocalFlags;                 // (Write) Flags specific to this node
    uiDockFlags      LocalFlagsInWindows;        // (Write) Flags specific to this node, applied from windows
    uiDockFlags      MergedFlags;                // (Read)  Effective flags (== SharedFlags | LocalFlagsInNode | LocalFlagsInWindows)
    uiDockNodeState      State;
    uiDockNode*          ParentNode;
    uiDockNode*          ChildNodes[2];              // [Split node only] Child nodes (left/right or top/bottom). Consider switching to an array.
    ImVector<uiWindow*>  Windows;                    // Note: unordered list! Iterate TabBar->Tabs for user-order.
    uiTabBar*            TabBar;
    vec2                  Pos;                        // Current position
    vec2                  Size;                       // Current size
    vec2                  SizeRef;                    // [Split node only] Last explicitly written-to size (overridden when using a splitter affecting the node), used to calculate Size.
    uiAxis               SplitAxis;                  // [Split node only] Split axis (X or Y)
    ImU32                   LastBgColor;
    uiWindowClass        WindowClass;                // [Root node only]

    uiWindow*            HostWindow;
    uiWindow*            VisibleWindow;              // Generally point to window which is ID is == SelectedTabID, but when CTRL+Tabbing this can be a different window.
    uiDockNode*          CentralNode;                // [Root node only] Pointer to central node.
    uiDockNode*          OnlyNodeWithWindows;        // [Root node only] Set when there is a single visible node within the hierarchy.
    int                     CountNodeWithWindows;       // [Root node only]
    int                     LastFrameAlive;             // Last frame number the node was updated or kept alive explicitly with DockSpace() + uiDockFlags_KeepAliveOnly
    int                     LastFrameActive;            // Last frame number the node was updated.
    int                     LastFrameFocused;           // Last frame number the node was focused.
    uiID                 LastFocusedNodeId;          // [Root node only] Which of our child docking node (any ancestor in the hierarchy) was last focused.
    uiID                 SelectedTabId;              // [Leaf node only] Which of our tab/window is selected.
    uiID                 WantCloseTabId;             // [Leaf node only] Set when closing a specific tab/window.
    uiID                 RefViewportId;              // Reference viewport ID from visible window when HostWindow == NULL.
    uiDataAuthority      AuthorityForPos         :3;
    uiDataAuthority      AuthorityForSize        :3;
    uiDataAuthority      AuthorityForViewport    :3;
    bool                    IsVisible               :1; // Set to false when the node is hidden (usually disabled as it has no active window)
    bool                    IsFocused               :1;
    bool                    IsBgDrawnThisFrame      :1;
    bool                    HasCloseButton          :1; // Provide space for a close button (if any of the docked window has one). Note that button may be hidden on window without one.
    bool                    HasWindowMenuButton     :1;
    bool                    HasCentralNodeChild     :1;
    bool                    WantCloseAll            :1; // Set when closing all tabs at once.
    bool                    WantLockSizeOnce        :1;
    bool                    WantMouseMove           :1; // After a node extraction we need to transition toward moving the newly created host window
    bool                    WantHiddenTabBarUpdate  :1;
    bool                    WantHiddenTabBarToggle  :1;

    uiDockNode(uiID id);
    ~uiDockNode();
    bool                    IsRootNode() const      { return ParentNode == NULL; }
    bool                    IsDockSpace() const     { return (MergedFlags & uiDockFlags_DockSpace) != 0; }
    bool                    IsFloatingNode() const  { return ParentNode == NULL && (MergedFlags & uiDockFlags_DockSpace) == 0; }
    bool                    IsCentralNode() const   { return (MergedFlags & uiDockFlags_CentralNode) != 0; }
    bool                    IsHiddenTabBar() const  { return (MergedFlags & uiDockFlags_HiddenTabBar) != 0; } // Hidden tab bar can be shown back by clicking the small triangle
    bool                    IsNoTabBar() const      { return (MergedFlags & uiDockFlags_NoTabBar) != 0; }     // Never show a tab bar
    bool                    IsSplitNode() const     { return ChildNodes[0] != NULL; }
    bool                    IsLeafNode() const      { return ChildNodes[0] == NULL; }
    bool                    IsEmpty() const         { return ChildNodes[0] == NULL && Windows.Size == 0; }
    ImRect                  Rect() const            { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }

    void                    SetLocalFlags(uiDockFlags flags) { LocalFlags = flags; UpdateMergedFlags(); }
    void                    UpdateMergedFlags()     { MergedFlags = SharedFlags | LocalFlags | LocalFlagsInWindows; }
};

// List of colors that are stored at the time of Begin() into Docked Windows.
// We currently store the packed colors in a simple array window->DockStyle.Colors[].
// A better solution may involve appending into a log of colors in uiContext + store offsets into those arrays in uiWindow,
// but it would be more complex as we'd need to double-buffer both as e.g. drop target may refer to window from last frame.
enum uiWindowDockStyleCol
{
    uiWindowDockStyleCol_Text,
    uiWindowDockStyleCol_TabHovered,
    uiWindowDockStyleCol_TabFocused,
    uiWindowDockStyleCol_TabSelected,
    uiWindowDockStyleCol_TabSelectedOverline,
    uiWindowDockStyleCol_TabDimmed,
    uiWindowDockStyleCol_TabDimmedSelected,
    uiWindowDockStyleCol_TabDimmedSelectedOverline,
    uiWindowDockStyleCol_UnsavedMarker,
    uiWindowDockStyleCol_COUNT
};

// We don't store style.Alpha: dock_node->LastBgColor embeds it and otherwise it would only affect the docking tab, which intuitively I would say we don't want to.
struct uiWindowDockStyle
{
    ImU32 Colors[uiWindowDockStyleCol_COUNT];
};

struct uiDockContext
{
    uiStorage                    Nodes;          // Map ID -> uiDockNode*: Active nodes
    ImVector<uiDockRequest>      Requests;
    ImVector<uiDockNodeSettings> NodesSettings;
    bool                            WantFullRebuild;
    uiDockContext()              { memset((void*)this, 0, sizeof(*this)); }
};

#endif // #ifdef IMGUI_HAS_DOCK

//-----------------------------------------------------------------------------
// [SECTION] Viewport support
//-----------------------------------------------------------------------------

// uiViewport Private/Internals fields (cardinal sin: we are using inheritance!)
// Every instance of uiViewport is in fact a uiViewportP.
struct uiViewportP : public uiViewport
{
    uiWindow*        Window;                 // Set when the viewport is owned by a window (and uiViewportFlags_CanHostOtherWindows is NOT set)
    int                 Idx;
    int                 LastFrameActive;        // Last frame number this viewport was activated by a window
    int                 LastFocusedStampCount;  // Last stamp number from when a window hosted by this viewport was focused (by comparing this value between two viewport we have an implicit viewport z-order we use as fallback)
    uiID             LastNameHash;
    vec2              LastPos;
    vec2              LastSize;
    float               Alpha;                  // Window opacity (when dragging dockable windows/viewports we make them transparent)
    float               LastAlpha;
    bool                LastFocusedHadNavWindow;// Instead of maintaining a LastFocusedWindow (which may harder to correctly maintain), we merely store weither NavWindow != NULL last time the viewport was focused.
    short               PlatformMonitor;
    float               BgFgDrawListsLastTimeActive[2]; // Last frame number the background (0) and foreground (1) draw lists were used
    ImDrawList*         BgFgDrawLists[2];       // Convenience background (0) and foreground (1) draw lists. We use them to draw software mouser cursor when io.MouseDrawCursor is set and to draw most debug overlays.
    ImDrawData          DrawDataP;
    ImDrawDataBuilder   DrawDataBuilder;        // Temporary data while building final ImDrawData
    vec2              LastPlatformPos;
    vec2              LastPlatformSize;
    vec2              LastRendererSize;

    // Per-viewport work area
    // - Insets are >= 0.0f values, distance from viewport corners to work area.
    // - BeginMainMenuBar() and DockspaceOverViewport() tend to use work area to avoid stepping over existing contents.
    // - Generally 'safeAreaInsets' in iOS land, 'DisplayCutout' in Android land.
    vec2              WorkInsetMin;           // Work Area inset locked for the frame. GetWorkRect() always fits within GetMainRect().
    vec2              WorkInsetMax;           // "
    vec2              BuildWorkInsetMin;      // Work Area inset accumulator for current frame, to become next frame's WorkInset
    vec2              BuildWorkInsetMax;      // "

    uiViewportP()                    { Window = NULL; Idx = -1; LastFrameActive = LastFocusedStampCount = -1; BgFgDrawListsLastTimeActive[0] = BgFgDrawListsLastTimeActive[1] = -1.0f; LastNameHash = 0; Alpha = LastAlpha = 1.0f; LastFocusedHadNavWindow = false; PlatformMonitor = -1; BgFgDrawLists[0] = BgFgDrawLists[1] = NULL; LastPlatformPos = LastPlatformSize = LastRendererSize = vec2(FLT_MAX, FLT_MAX); }
    ~uiViewportP()                   { if (BgFgDrawLists[0]) IM_DELETE(BgFgDrawLists[0]); if (BgFgDrawLists[1]) IM_DELETE(BgFgDrawLists[1]); }
    void    ClearRequestFlags()         { PlatformRequestClose = PlatformRequestMove = PlatformRequestResize = false; }

    // Calculate work rect pos/size given a set of offset (we have 1 pair of offset for rect locked from last frame data, and 1 pair for currently building rect)
    vec2  CalcWorkRectPos(const vec2& inset_min) const                           { return vec2(Pos.x + inset_min.x, Pos.y + inset_min.y); }
    vec2  CalcWorkRectSize(const vec2& inset_min, const vec2& inset_max) const { return vec2(ImMax(0.0f, Size.x - inset_min.x - inset_max.x), ImMax(0.0f, Size.y - inset_min.y - inset_max.y)); }
    void    UpdateWorkRect()            { WorkPos = CalcWorkRectPos(WorkInsetMin); WorkSize = CalcWorkRectSize(WorkInsetMin, WorkInsetMax); } // Update public fields

    // Helpers to retrieve ImRect (we don't need to store BuildWorkRect as every access tend to change it, hence the code asymmetry)
    ImRect  GetMainRect() const         { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }
    ImRect  GetWorkRect() const         { return ImRect(WorkPos.x, WorkPos.y, WorkPos.x + WorkSize.x, WorkPos.y + WorkSize.y); }
    ImRect  GetBuildWorkRect() const    { vec2 pos = CalcWorkRectPos(BuildWorkInsetMin); vec2 size = CalcWorkRectSize(BuildWorkInsetMin, BuildWorkInsetMax); return ImRect(pos.x, pos.y, pos.x + size.x, pos.y + size.y); }
};

//-----------------------------------------------------------------------------
// [SECTION] Settings support
//-----------------------------------------------------------------------------
// Windows data saved in imgui.ini file
// Because we never destroy or rename uiWindowSettings, we can store the names in a separate buffer easily.
// (this is designed to be stored in a ImChunkStream buffer, with the variable-length Name following our structure)
struct uiWindowSettings {
    uiID   ID;
    vec2ih Pos;        // NB: Settings position are stored RELATIVE to the viewport! Whereas runtime ones are absolute positions.
    vec2ih Size;
    vec2ih ViewportPos;
    uiID   ViewportId;
    uiID   DockId;     // ID of last known DockNode (even if the DockNode is invisible because it has only 1 active window), or 0 if none.
    uiID   ClassId;    // ID of window class if specified
    short  DockOrder;  // Order of the last time the window was visible within its DockNode. This is used to reorder windows that are reappearing on the same frame. Same value between windows that were active and windows that were none are possible.
    bool   Collapsed;
    bool   IsChild;
    bool   WantApply;  // Set when loaded from .ini data (to enable merging/loading .ini data into an already running context)
    bool   WantDelete; // Set to invalidate/delete the settings entry
    uiWindowSettings() { memset((void*)this, 0, sizeof(*this)); DockOrder = -1; }
    char* GetName() { return (char*)(this + 1); }
};
struct uiSettingsHandler {
    const char* TypeName; // Short description stored in .ini file. Disallowed characters: '[' ']'
    uiID  TypeHash;       // == ImHashStr(TypeName)
    void  (*ClearAllFn)(uiContext* ctx, uiSettingsHandler* handler);                                // Clear all settings data
    void  (*ReadInitFn)(uiContext* ctx, uiSettingsHandler* handler);                                // Read: Called before reading (in registration order)
    void* (*ReadOpenFn)(uiContext* ctx, uiSettingsHandler* handler, const char* name);              // Read: Called when entering into a new ini entry e.g. "[Window][Name]"
    void  (*ReadLineFn)(uiContext* ctx, uiSettingsHandler* handler, void* entry, const char* line); // Read: Called for every line of text within an ini entry
    void  (*ApplyAllFn)(uiContext* ctx, uiSettingsHandler* handler);                                // Read: Called after reading (in registration order)
    void  (*WriteAllFn)(uiContext* ctx, uiSettingsHandler* handler, uiTextBuffer* out_buf);      // Write: Output every entries into 'out_buf'
    void* UserData;
    uiSettingsHandler() { memset((void*)this, 0, sizeof(*this)); }
};
//-----------------------------------------------------------------------------
// [SECTION] Localization support
//-----------------------------------------------------------------------------

// This is experimental and not officially supported, it'll probably fall short of features, if/when it does we may backtrack.
enum uiLocKey : int
{
    uiLocKey_VersionStr,
    uiLocKey_TableSizeOne,
    uiLocKey_TableSizeAllFit,
    uiLocKey_TableSizeAllDefault,
    uiLocKey_TableResetOrder,
    uiLocKey_WindowingMainMenuBar,
    uiLocKey_WindowingPopup,
    uiLocKey_WindowingUntitled,
    uiLocKey_OpenLink_s,
    uiLocKey_CopyLink,
    uiLocKey_DockingHideTabBar,
    uiLocKey_DockingHoldShiftToDock,
    uiLocKey_DockingDragToUndockOrMoveNode,
    uiLocKey_COUNT
};

struct uiLocEntry
{
    uiLocKey     Key;
    const char*     Text;
};

//-----------------------------------------------------------------------------
// [SECTION] Error handling, State recovery support
//-----------------------------------------------------------------------------

// Macros used by Recoverable Error handling
// - Only dispatch error if _EXPR: evaluate as assert (similar to an assert macro).
// - The message will always be a string literal, in order to increase likelihood of being display by an assert handler.
// - See 'Demo->Configuration->Error Handling' and uiIO definitions for details on error handling.
// - Read https://github.com/ocornut/imgui/wiki/Error-Handling for details on error handling.
#ifndef IM_ASSERT_USER_ERROR
#define IM_ASSERT_USER_ERROR(_EXPR,_MSG)            do { if (!(_EXPR)) { if (UI::ErrorLog(_MSG)) { IM_ASSERT((_EXPR) && _MSG); } } } while (0)               // Recoverable User Error
#define IM_ASSERT_USER_ERROR_RET(_EXPR,_MSG)        do { if (!(_EXPR)) { if (UI::ErrorLog(_MSG)) { IM_ASSERT((_EXPR) && _MSG); } return; } } while (0)       // Recoverable User Error
#define IM_ASSERT_USER_ERROR_RETV(_EXPR,_RETV,_MSG) do { if (!(_EXPR)) { if (UI::ErrorLog(_MSG)) { IM_ASSERT((_EXPR) && _MSG); } return _RETV; } } while (0) // Recoverable User Error
#endif

// The error callback is currently not public, as it is expected that only advanced users will rely on it.
typedef void (*uiErrorCallback)(uiContext* ctx, void* user_data, const char* msg); // Function signature for g.ErrorCallback

//-----------------------------------------------------------------------------
// [SECTION] Metrics, Debug Tools
//-----------------------------------------------------------------------------

// See IMGUI_DEBUG_LOG() and IMGUI_DEBUG_LOG_XXX() macros.
enum uiDebugLogFlags_
{
    // Event types
    uiDebugLogFlags_None                 = 0,
    uiDebugLogFlags_EventError           = 1 << 0,   // Error submitted by IM_ASSERT_USER_ERROR()
    uiDebugLogFlags_EventActiveId        = 1 << 1,
    uiDebugLogFlags_EventFocus           = 1 << 2,
    uiDebugLogFlags_EventPopup           = 1 << 3,
    uiDebugLogFlags_EventNav             = 1 << 4,
    uiDebugLogFlags_EventClipper         = 1 << 5,
    uiDebugLogFlags_EventSelection       = 1 << 6,
    uiDebugLogFlags_EventIO              = 1 << 7,
    uiDebugLogFlags_EventFont            = 1 << 8,
    uiDebugLogFlags_EventInputRouting    = 1 << 9,
    uiDebugLogFlags_EventDocking         = 1 << 10,
    uiDebugLogFlags_EventViewport        = 1 << 11,

    uiDebugLogFlags_EventMask_           = uiDebugLogFlags_EventError | uiDebugLogFlags_EventActiveId | uiDebugLogFlags_EventFocus | uiDebugLogFlags_EventPopup | uiDebugLogFlags_EventNav | uiDebugLogFlags_EventClipper | uiDebugLogFlags_EventSelection | uiDebugLogFlags_EventIO | uiDebugLogFlags_EventFont | uiDebugLogFlags_EventInputRouting | uiDebugLogFlags_EventDocking | uiDebugLogFlags_EventViewport,
    uiDebugLogFlags_OutputToTTY          = 1 << 20,  // Also send output to TTY
    uiDebugLogFlags_OutputToDebugger     = 1 << 21,  // Also send output to Debugger Console [Windows only]
    uiDebugLogFlags_OutputToTestEngine   = 1 << 22,  // Also send output to Dear ImGui Test Engine
};

struct uiDebugAllocEntry
{
    int         FrameCount;
    ImS16       AllocCount;
    ImS16       FreeCount;
};

struct uiDebugAllocInfo
{
    int         TotalAllocCount;            // Number of call to MemAlloc().
    int         TotalFreeCount;
    ImS16       LastEntriesIdx;             // Current index in buffer
    uiDebugAllocEntry LastEntriesBuf[6]; // Track last 6 frames that had allocations

    uiDebugAllocInfo() { memset((void*)this, 0, sizeof(*this)); }
};

struct uiMetricsConfig
{
    bool        ShowDebugLog = false;
    bool        ShowIDStackTool = false;
    bool        ShowWindowsRects = false;
    bool        ShowWindowsBeginOrder = false;
    bool        ShowTablesRects = false;
    bool        ShowDrawCmdMesh = true;
    bool        ShowDrawCmdBoundingBoxes = true;
    bool        ShowTextEncodingViewer = false;
    bool        ShowTextureUsedRect = false;
    bool        ShowDockingNodes = false;
    int         ShowWindowsRectsType = -1;
    int         ShowTablesRectsType = -1;
    int         HighlightMonitorIdx = -1;
    uiID     HighlightViewportID = 0;
    bool        ShowFontPreview = true;
};

struct uiStackLevelInfo
{
    uiID                 ID;
    ImS8                    QueryFrameCount;            // >= 1: Sub-query in progress
    bool                    QuerySuccess;               // Sub-query obtained result from DebugHookIdInfo()
    ImS8                    DataType;                   // uiDataType
    int                     DescOffset;                 // -1 or offset into parent's ResultsPathsBuf

    uiStackLevelInfo()   { memset((void*)this, 0, sizeof(*this)); DataType = -1; DescOffset = -1; }
};

struct uiDebugItemPathQuery
{
    uiID                 MainID;                     // ID to query details for.
    bool                    Active;                     // Used to disambiguate the case when ID == 0 and e.g. some code calls PushOverrideID(0).
    bool                    Complete;                   // All sub-queries are finished (some may have failed).
    ImS8                    Step;                       // -1: query stack + init Results, >= 0: filling individual stack level.
    ImVector<uiStackLevelInfo> Results;
    uiTextBuffer         ResultsDescBuf;
    uiTextBuffer         ResultPathBuf;

    uiDebugItemPathQuery() { memset((void*)this, 0, sizeof(*this)); }
};

// State for ID Stack tool queries
struct uiIDStackTool
{
    bool                    OptHexEncodeNonAsciiChars;
    bool                    OptCopyToClipboardOnCtrlC;
    int                     LastActiveFrame;
    float                   CopyToClipboardLastTime;

    uiIDStackTool()      { memset((void*)this, 0, sizeof(*this)); LastActiveFrame = -1; OptHexEncodeNonAsciiChars = true; CopyToClipboardLastTime = -FLT_MAX; }
};

//-----------------------------------------------------------------------------
// [SECTION] Generic context hooks
//-----------------------------------------------------------------------------

typedef void (*uiContextHookCallback)(uiContext* ctx, uiContextHook* hook);
enum uiContextHookType { uiContextHookType_NewFramePre, uiContextHookType_NewFramePost, uiContextHookType_EndFramePre, uiContextHookType_EndFramePost, uiContextHookType_RenderPre, uiContextHookType_RenderPost, uiContextHookType_Shutdown, uiContextHookType_PendingRemoval_ };

struct uiContextHook
{
    uiID                     HookId;     // A unique ID assigned by AddContextHook()
    uiContextHookType        Type;
    uiID                     Owner;
    uiContextHookCallback    Callback;
    void*                       UserData;

    uiContextHook()          { memset((void*)this, 0, sizeof(*this)); }
};

typedef void (*uiDemoMarkerCallback)(const char* file, int line, const char* section);

//-----------------------------------------------------------------------------
// [SECTION] uiContext (main Dear ImGui context)
//-----------------------------------------------------------------------------

struct uiContext
{
    bool                    Initialized;
    bool                    WithinFrameScope;                   // Set by NewFrame(), cleared by EndFrame()
    bool                    WithinFrameScopeWithImplicitWindow; // Set by NewFrame(), cleared by EndFrame() when the implicit debug window has been pushed
    bool                    TestEngineHookItems;                // Will call test engine hooks: uiTestEngineHook_ItemAdd(), uiTestEngineHook_ItemInfo(), uiTestEngineHook_Log()
    int                     FrameCount;
    int                     FrameCountEnded;
    int                     FrameCountPlatformEnded;
    int                     FrameCountRendered;
    double                  Time;
    char                    ContextName[16];                    // Storage for a context name (to facilitate debugging multi-context setups)
    uiIO                 IO;
    uiPlatformIO         PlatformIO;
    uiStyle              Style;
    uiConfigFlags        ConfigFlagsCurrFrame;               // = g.IO.ConfigFlags at the time of NewFrame()
    uiConfigFlags        ConfigFlagsLastFrame;
    ImVector<ImFontAtlas*>  FontAtlases;                        // List of font atlases used by the context (generally only contains g.IO.Fonts aka the main font atlas)
    ImFont*                 Font;                               // Currently bound font. (== FontStack.back().Font)
    ImFontBaked*            FontBaked;                          // Currently bound font at currently bound size. (== Font->GetFontBaked(FontSize))
    float                   FontSize;                           // Currently bound font size == line height (== FontSizeBase + externals scales applied in the UpdateCurrentFontSize() function).
    float                   FontSizeBase;                       // Font size before scaling == style.FontSizeBase == value passed to PushFont() when specified.
    float                   FontBakedScale;                     // == FontBaked->Size / FontSize. Scale factor over baked size. Rarely used nowadays, very often == 1.0f.
    float                   FontRasterizerDensity;              // Current font density. Used by all calls to GetFontBaked().
    float                   CurrentDpiScale;                    // Current window/viewport DpiScale == CurrentViewport->DpiScale
    ImDrawListSharedData    DrawListSharedData;
    uiID                 WithinEndChildID;                   // Set within EndChild()
    uiID                 WithinEndPopupID;                   // Set within EndPopup()
    void*                   TestEngine;                         // Test engine user data

    // Inputs
    ImVector<uiInputEvent> InputEventsQueue;                 // Input events which will be trickled/written into IO structure.
    ImVector<uiInputEvent> InputEventsTrail;                 // Past input events processed in NewFrame(). This is to allow domain-specific application to access e.g mouse/pen trail.
    uiMouseSource        InputEventsNextMouseSource;
    ImU32                   InputEventsNextEventId;

    // Windows state
    ImVector<uiWindow*>  Windows;                            // Windows, sorted in display order, back to front
    ImVector<uiWindow*>  WindowsFocusOrder;                  // Root windows, sorted in focus order, back to front.
    ImVector<uiWindow*>  WindowsTempSortBuffer;              // Temporary buffer used in EndFrame() to reorder windows so parents are kept before their child
    ImVector<uiWindowStackData> CurrentWindowStack;
    uiStorage            WindowsById;                        // Map window's uiID to uiWindow*
    int                     WindowsActiveCount;                 // Number of unique windows submitted by frame
    float                   WindowsBorderHoverPadding;          // Padding around resizable windows for which hovering on counts as hovering the window == ImMax(style.TouchExtraPadding, style.WindowBorderHoverPadding). This isn't so multi-dpi friendly.
    uiID                 DebugBreakInWindow;                 // Set to break in Begin() call.
    uiWindow*            CurrentWindow;                      // Window being drawn into
    uiWindow*            HoveredWindow;                      // Window the mouse is hovering. Will typically catch mouse inputs.
    uiWindow*            HoveredWindowUnderMovingWindow;     // Hovered window ignoring MovingWindow. Only set if MovingWindow is set.
    uiWindow*            HoveredWindowBeforeClear;           // Window the mouse is hovering. Filled even with _NoMouse. This is currently useful for multi-context compositors.
    uiWindow*            MovingWindow;                       // Track the window we clicked on (in order to preserve focus). The actual window that is moved is generally MovingWindow->RootWindowDockTree.
    uiWindow*            WheelingWindow;                     // Track the window we started mouse-wheeling on. Until a timer elapse or mouse has moved, generally keep scrolling the same window even if during the course of scrolling the mouse ends up hovering a child window.
    vec2                  WheelingWindowRefMousePos;
    int                     WheelingWindowStartFrame;           // This may be set one frame before WheelingWindow is != NULL
    int                     WheelingWindowScrolledFrame;
    float                   WheelingWindowReleaseTimer;
    vec2                  WheelingWindowWheelRemainder;
    vec2                  WheelingAxisAvg;

    // Item/widgets state and tracking information
    uiID                 DebugDrawIdConflictsId;             // Set when we detect multiple items with the same identifier
    uiID                 DebugHookIdInfoId;                  // Will call core hooks: DebugHookIdInfo() from GetID functions, used by ID Stack Tool [next HoveredId/ActiveId to not pull in an extra cache-line]
    uiID                 HoveredId;                          // Hovered widget, filled during the frame
    uiID                 HoveredIdPreviousFrame;
    int                     HoveredIdPreviousFrameItemCount;    // Count numbers of items using the same ID as last frame's hovered id
    float                   HoveredIdTimer;                     // Measure contiguous hovering time
    float                   HoveredIdNotActiveTimer;            // Measure contiguous hovering time where the item has not been active
    bool                    HoveredIdAllowOverlap;
    bool                    HoveredIdIsDisabled;                // At least one widget passed the rect test, but has been discarded by disabled flag or popup inhibit. May be true even if HoveredId == 0.
    bool                    ItemUnclipByLog;                    // Disable ItemAdd() clipping, essentially a memory-locality friendly copy of LogEnabled
    uiID                 ActiveId;                           // Active widget
    uiID                 ActiveIdIsAlive;                    // Active widget has been seen this frame (we can't use a bool as the ActiveId may change within the frame)
    float                   ActiveIdTimer;
    bool                    ActiveIdIsJustActivated;            // Set at the time of activation for one frame
    bool                    ActiveIdAllowOverlap;               // Active widget allows another widget to steal active id (generally for overlapping widgets, but not always)
    bool                    ActiveIdNoClearOnFocusLoss;         // Disable losing active id if the active id window gets unfocused.
    bool                    ActiveIdHasBeenPressedBefore;       // Track whether the active id led to a press (this is to allow changing between PressOnClick and PressOnRelease without pressing twice). Used by range_select branch.
    bool                    ActiveIdHasBeenEditedBefore;        // Was the value associated to the widget Edited over the course of the Active state.
    bool                    ActiveIdHasBeenEditedThisFrame;
    bool                    ActiveIdFromShortcut;
    ImS8                    ActiveIdMouseButton;
    uiID                 ActiveIdDisabledId;                 // When clicking a disabled item we set ActiveId=window->MoveId to avoid interference with widget code. Actual item ID is stored here.
    vec2                  ActiveIdClickOffset;                // Clicked offset from upper-left corner, if applicable (currently only set by ButtonBehavior)
    uiInputSource        ActiveIdSource;                     // Activating source: uiInputSource_Mouse OR uiInputSource_Keyboard OR uiInputSource_Gamepad
    uiWindow*            ActiveIdWindow;
    uiID                 ActiveIdPreviousFrame;
    uiDeactivatedItemData DeactivatedItemData;
    uiDataTypeStorage    ActiveIdValueOnActivation;          // Backup of initial value at the time of activation. ONLY SET BY SPECIFIC WIDGETS: DragXXX and SliderXXX.
    uiID                 LastActiveId;                       // Store the last non-zero ActiveId, useful for animation.
    float                   LastActiveIdTimer;                  // Store the last non-zero ActiveId timer since the beginning of activation, useful for animation.

    // Key/Input Ownership + Shortcut Routing system
    // - The idea is that instead of "eating" a given key, we can link to an owner.
    // - Input query can then read input by specifying uiKeyOwner_Any (== 0), uiKeyOwner_NoOwner (== -1) or a custom ID.
    // - Routing is requested ahead of time for a given chord (Key + Mods) and granted in NewFrame().
    double                  LastKeyModsChangeTime;              // Record the last time key mods changed (affect repeat delay when using shortcut logic)
    double                  LastKeyModsChangeFromNoneTime;      // Record the last time key mods changed away from being 0 (affect repeat delay when using shortcut logic)
    double                  LastKeyboardKeyPressTime;           // Record the last time a keyboard key (ignore mouse/gamepad ones) was pressed.
    ImBitArrayForNamedKeys  KeysMayBeCharInput;                 // Lookup to tell if a key can emit char input, see IsKeyChordPotentiallyCharInput(). sizeof() = 20 bytes
    uiKeyOwnerData       KeysOwnerData[uiKey_NamedKey_COUNT];
    uiKeyRoutingTable    KeysRoutingTable;
    ImU32                   ActiveIdUsingNavDirMask;            // Active widget will want to read those nav move requests (e.g. can activate a button and move away from it)
    bool                    ActiveIdUsingAllKeyboardKeys;       // Active widget will want to read all keyboard keys inputs. (this is a shortcut for not taking ownership of 100+ keys, frequently used by drag operations)
    uiKeyChord           DebugBreakInShortcutRouting;        // Set to break in SetShortcutRouting()/Shortcut() calls.
    //ImU32                 ActiveIdUsingNavInputMask;          // [OBSOLETE] Since (IMGUI_VERSION_NUM >= 18804) : 'g.ActiveIdUsingNavInputMask |= (1 << uiNavInput_Cancel);' becomes --> 'SetKeyOwner(uiKey_Escape, g.ActiveId) and/or SetKeyOwner(uiKey_NavGamepadCancel, g.ActiveId);'

    // Next window/item data
    uiID                 CurrentFocusScopeId;                // Value for currently appending items == g.FocusScopeStack.back(). Not to be mistaken with g.NavFocusScopeId.
    uiItemFlags          CurrentItemFlags;                   // Value for currently appending items == g.ItemFlagsStack.back()
    uiID                 DebugLocateId;                      // Storage for DebugLocateItemOnHover() feature: this is read by ItemAdd() so we keep it in a hot/cached location
    uiNextItemData       NextItemData;                       // Storage for SetNextItem** functions
    uiLastItemData       LastItemData;                       // Storage for last submitted item (setup by ItemAdd)
    uiNextWindowData     NextWindowData;                     // Storage for SetNextWindow** functions
    bool                    DebugShowGroupRects;
    bool                    GcCompactAll;                       // Request full GC

    // Shared stacks
    uiCol                        DebugFlashStyleColorIdx;    // (Keep close to ColorStack to share cache line)
    ImVector<uiColorMod>         ColorStack;                 // Stack for PushStyleColor()/PopStyleColor() - inherited by Begin()
    ImVector<uiStyleMod>         StyleVarStack;              // Stack for PushStyleVar()/PopStyleVar() - inherited by Begin()
    ImVector<ImFontStackData>       FontStack;                  // Stack for PushFont()/PopFont() - inherited by Begin()
    ImVector<uiFocusScopeData>   FocusScopeStack;            // Stack for PushFocusScope()/PopFocusScope() - inherited by BeginChild(), pushed into by Begin()
    ImVector<uiItemFlags>        ItemFlagsStack;             // Stack for PushItemFlag()/PopItemFlag() - inherited by Begin()
    ImVector<uiGroupData>        GroupStack;                 // Stack for BeginGroup()/EndGroup() - not inherited by Begin()
    ImVector<uiPopupData>        OpenPopupStack;             // Which popups are open (persistent)
    ImVector<uiPopupData>        BeginPopupStack;            // Which level of BeginPopup() we are in (reset every frame)
    ImVector<uiTreeNodeStackData>TreeNodeStack;              // Stack for TreeNode()

    // Viewports
    ImVector<uiViewportP*> Viewports;                        // Active viewports (always 1+, and generally 1 unless multi-viewports are enabled). Each viewports hold their copy of ImDrawData.
    uiViewportP*         CurrentViewport;                    // We track changes of viewport (happening in Begin) so we can call Platform_OnChangedViewport()
    uiViewportP*         MouseViewport;
    uiViewportP*         MouseLastHoveredViewport;           // Last known viewport that was hovered by mouse (even if we are not hovering any viewport any more) + honoring the _NoInputs flag.
    uiID                 PlatformLastFocusedViewportId;
    uiPlatformMonitor    FallbackMonitor;                    // Virtual monitor used as fallback if backend doesn't provide monitor information.
    ImRect                  PlatformMonitorsFullWorkRect;       // Bounding box of all platform monitors
    int                     ViewportCreatedCount;               // Unique sequential creation counter (mostly for testing/debugging)
    int                     PlatformWindowsCreatedCount;        // Unique sequential creation counter (mostly for testing/debugging)
    int                     ViewportFocusedStampCount;          // Every time the front-most window changes, we stamp its viewport with an incrementing counter

    // Keyboard/Gamepad Navigation
    bool                    NavCursorVisible;                   // Nav focus cursor/rectangle is visible? We hide it after a mouse click. We show it after a nav move.
    bool                    NavHighlightItemUnderNav;           // Disable mouse hovering highlight. Highlight navigation focused item instead of mouse hovered item.
    //bool                  NavDisableHighlight;                // Old name for !g.NavCursorVisible before 1.91.4 (2024/10/18). OPPOSITE VALUE (g.NavDisableHighlight == !g.NavCursorVisible)
    //bool                  NavDisableMouseHover;               // Old name for g.NavHighlightItemUnderNav before 1.91.1 (2024/10/18) this was called When user starts using keyboard/gamepad, we hide mouse hovering highlight until mouse is touched again.
    bool                    NavMousePosDirty;                   // When set we will update mouse position if io.ConfigNavMoveSetMousePos is set (not enabled by default)
    bool                    NavIdIsAlive;                       // Nav widget has been seen this frame ~~ NavRectRel is valid
    uiID                 NavId;                              // Focused item for navigation
    uiWindow*            NavWindow;                          // Focused window for navigation. Could be called 'FocusedWindow'
    uiID                 NavFocusScopeId;                    // Focused focus scope (e.g. selection code often wants to "clear other items" when landing on an item of the same scope)
    uiNavLayer           NavLayer;                           // Focused layer (main scrolling layer, or menu/title bar layer)
    uiItemFlags          NavIdItemFlags;
    uiID                 NavActivateId;                      // ~~ (g.ActiveId == 0) && (IsKeyPressed(uiKey_Space) || IsKeyDown(uiKey_Enter) || IsKeyPressed(uiKey_NavGamepadActivate)) ? NavId : 0, also set when calling ActivateItemByID()
    uiID                 NavActivateDownId;                  // ~~ IsKeyDown(uiKey_Space) || IsKeyDown(uiKey_Enter) || IsKeyDown(uiKey_NavGamepadActivate) ? NavId : 0
    uiID                 NavActivatePressedId;               // ~~ IsKeyPressed(uiKey_Space) || IsKeyPressed(uiKey_Enter) || IsKeyPressed(uiKey_NavGamepadActivate) ? NavId : 0 (no repeat)
    uiActivateFlags      NavActivateFlags;
    ImVector<uiFocusScopeData> NavFocusRoute;                // Reversed copy focus scope stack for NavId (should contains NavFocusScopeId). This essentially follow the window->ParentWindowForFocusRoute chain.
    uiID                 NavHighlightActivatedId;
    float                   NavHighlightActivatedTimer;
    uiID                 NavOpenContextMenuItemId;
    uiID                 NavOpenContextMenuWindowId;
    uiID                 NavNextActivateId;                  // Set by ActivateItemByID(), queued until next frame.
    uiActivateFlags      NavNextActivateFlags;
    uiInputSource        NavInputSource;                     // Keyboard or Gamepad mode? THIS CAN ONLY BE uiInputSource_Keyboard or uiInputSource_Gamepad
    uiSelectionUserData  NavLastValidSelectionUserData;      // Last valid data passed to SetNextItemSelectionUser(), or -1. For current window. Not reset when focusing an item that doesn't have selection data.
    ImS8                    NavCursorHideFrames;
    //uiID               NavActivateInputId;                 // Removed in 1.89.4 (July 2023). This is now part of g.NavActivateId and sets g.NavActivateFlags |= uiActivateFlags_PreferInput. See commit c9a53aa74, issue #5606.

    // Navigation: Init & Move Requests
    bool                    NavAnyRequest;                      // ~~ NavMoveRequest || NavInitRequest this is to perform early out in ItemAdd()
    bool                    NavInitRequest;                     // Init request for appearing window to select first item
    bool                    NavInitRequestFromMove;
    uiNavItemData        NavInitResult;                      // Init request result (first item of the window, or one for which SetItemDefaultFocus() was called)
    bool                    NavMoveSubmitted;                   // Move request submitted, will process result on next NewFrame()
    bool                    NavMoveScoringItems;                // Move request submitted, still scoring incoming items
    bool                    NavMoveForwardToNextFrame;
    uiNavMoveFlags       NavMoveFlags;
    uiScrollFlags        NavMoveScrollFlags;
    uiKeyChord           NavMoveKeyMods;
    Var::Dir                NavMoveDir;                         // Direction of the move request (left/right/up/down)
    Var::Dir                NavMoveDirForDebug;
    Var::Dir                NavMoveClipDir;                     // FIXME-NAV: Describe the purpose of this better. Might want to rename?
    ImRect                  NavScoringRect;                     // Rectangle used for scoring, in screen space. Based of window->NavRectRel[], modified for directional navigation scoring.
    ImRect                  NavScoringNoClipRect;               // Some nav operations (such as PageUp/PageDown) enforce a region which clipper will attempt to always keep submitted. Unset/invalid if inverted.
    int                     NavScoringDebugCount;               // Metrics for debugging
    int                     NavTabbingDir;                      // Generally -1 or +1, 0 when tabbing without a nav id
    int                     NavTabbingCounter;                  // >0 when counting items for tabbing
    uiNavItemData        NavMoveResultLocal;                 // Best move request candidate within NavWindow
    uiNavItemData        NavMoveResultLocalVisible;          // Best move request candidate within NavWindow that are mostly visible (when using uiNavMoveFlags_AlsoScoreVisibleSet flag)
    uiNavItemData        NavMoveResultOther;                 // Best move request candidate within NavWindow's flattened hierarchy (when using uiWindowFlags_NavFlattened flag)
    uiNavItemData        NavTabbingResultFirst;              // First tabbing request candidate within NavWindow and flattened hierarchy

    // Navigation: record of last move request
    uiID                 NavJustMovedFromFocusScopeId;       // Just navigated from this focus scope id (result of a successfully MoveRequest).
    uiID                 NavJustMovedToId;                   // Just navigated to this id (result of a successfully MoveRequest).
    uiID                 NavJustMovedToFocusScopeId;         // Just navigated to this focus scope id (result of a successfully MoveRequest).
    uiKeyChord           NavJustMovedToKeyMods;
    bool                    NavJustMovedToIsTabbing;            // Copy of uiNavMoveFlags_IsTabbing. Maybe we should store whole flags.
    bool                    NavJustMovedToHasSelectionData;     // Copy of move result's ItemFlags & uiItemFlags_HasSelectionUserData). Maybe we should just store uiNavItemData.

    // Navigation: extra config options (will be made public eventually)
    // - Tabbing (Tab, Shift+Tab) and Windowing (Ctrl+Tab, Ctrl+Shift+Tab) are enabled REGARDLESS of uiConfigFlags_NavEnableKeyboard being set.
    // - Ctrl+Tab is reconfigurable because it is the only shortcut that may be polled when no window are focused. It also doesn't work e.g. Web platforms.
    bool                    ConfigNavEnableTabbing;             // = true. Enable tabbing (Tab, Shift+Tab). PLEASE LET ME KNOW IF YOU USE THIS.
    bool                    ConfigNavWindowingWithGamepad;      // = true. Enable Ctrl+Tab by holding uiKey_GamepadFaceLeft (== uiKey_NavGamepadMenu). When false, the button may still be used to toggle Menu layer.
    uiKeyChord           ConfigNavWindowingKeyNext;          // = uiMod_Ctrl | uiKey_Tab (or uiMod_Super | uiKey_Tab on OS X). Set to 0 to disable. For reconfiguration (see #4828)
    uiKeyChord           ConfigNavWindowingKeyPrev;          // = uiMod_Ctrl | uiMod_Shift | uiKey_Tab (or uiMod_Super | uiMod_Shift | uiKey_Tab on OS X)

    // Navigation: Windowing (Ctrl+Tab for list, or Menu button + keys or directional pads to move/resize)
    uiWindow*            NavWindowingTarget;                 // Target window when doing Ctrl+Tab (or Pad Menu + FocusPrev/Next), this window is temporarily displayed top-most!
    uiWindow*            NavWindowingTargetAnim;             // Record of last valid NavWindowingTarget until DimBgRatio and NavWindowingHighlightAlpha becomes 0.0f, so the fade-out can stay on it.
    uiWindow*            NavWindowingListWindow;             // Internal window actually listing the Ctrl+Tab contents
    float                   NavWindowingTimer;
    float                   NavWindowingHighlightAlpha;
    uiInputSource        NavWindowingInputSource;
    bool                    NavWindowingToggleLayer;            // Set while Alt or GamepadMenu is held, may be cleared by other operations, and processed when releasing the key.
    uiKey                NavWindowingToggleKey;              // Keyboard/gamepad key used when toggling to menu layer.
    vec2                  NavWindowingAccumDeltaPos;
    vec2                  NavWindowingAccumDeltaSize;

    // Render
    float                   DimBgRatio;                         // 0.0..1.0 animation when fading in a dimming background (for modal window and Ctrl+Tab list)

    // Drag and Drop
    bool                    DragDropActive;
    bool                    DragDropWithinSource;               // Set when within a BeginDragDropXXX/EndDragDropXXX block for a drag source.
    bool                    DragDropWithinTarget;               // Set when within a BeginDragDropXXX/EndDragDropXXX block for a drag target.
    uiDragDropFlags         DragDropSourceFlags;
    int                     DragDropSourceFrameCount;
    int                     DragDropMouseButton;
    uiPayload               DragDropPayload;
    ImRect                  DragDropTargetRect;                 // Store rectangle of current target candidate (we favor small targets when overlapping)
    ImRect                  DragDropTargetClipRect;             // Store ClipRect at the time of item's drawing
    uiID                    DragDropTargetId;
    uiID                    DragDropTargetFullViewport;
    uiDragDropFlags         DragDropAcceptFlagsCurr;
    uiDragDropFlags         DragDropAcceptFlagsPrev;
    float                   DragDropAcceptIdCurrRectSurface;    // Target item surface (we resolve overlapping targets by prioritizing the smaller surface)
    uiID                    DragDropAcceptIdCurr;               // Target item id (set at the time of accepting the payload)
    uiID                    DragDropAcceptIdPrev;               // Target item id from previous frame (we need to store this to allow for overlapping drag and drop targets)
    int                     DragDropAcceptFrameCount;           // Last time a target expressed a desire to accept the source
    uiID                    DragDropHoldJustPressedId;          // Set when holding a payload just made ButtonBehavior() return a press.
    ImVector<unsigned char> DragDropPayloadBufHeap;             // We don't expose the ImVector<> directly, uiPayload only holds pointer+size
    unsigned char           DragDropPayloadBufLocal[16];        // Local buffer for small payloads

    // Clipper
    int                         ClipperTempDataStacked;
    ImVector<uiListClipperData> ClipperTempData;

    // Tables
    uiTable*                  CurrentTable;
    uiID                         DebugBreakInTable;          // Set to break in BeginTable() call.
    int                          TablesTempDataStacked;      // Temporary table data size (because we leave previous instances undestructed, we generally don't use TablesTempData.Size)
    ImVector<uiTableTempData> TablesTempData;             // Temporary table data (buffers reused/shared across instances, support nesting)
    ImPool<uiTable>           Tables;                     // Persistent table data
    ImVector<float>              TablesLastTimeActive;       // Last used timestamp of each tables (SOA, for efficient GC)
    ImVector<ImDrawChannel>      DrawChannelsTempMergeBuffer;

    // Tab bars
    uiTabBar*                      CurrentTabBar;
    ImPool<uiTabBar>               TabBars;
    ImVector<uiPtrOrIndex>      CurrentTabBarStack;
    ImVector<uiShrinkWidthItem> ShrinkWidthBuffer;

    // Multi-Select state
    uiBoxSelectState                BoxSelectState;
    uiMultiSelectTempData*          CurrentMultiSelect;
    int                             MultiSelectTempDataStacked; // Temporary multi-select data size (because we leave previous instances undestructed, we generally don't use MultiSelectTempData.Size)
    ImVector<uiMultiSelectTempData> MultiSelectTempData;
    ImPool<uiMultiSelectState>      MultiSelectStorage;

    // Hover Delay system
    uiID  HoverItemDelayId;
    uiID  HoverItemDelayIdPreviousFrame;
    float HoverItemDelayTimer;                // Currently used by IsItemHovered()
    float HoverItemDelayClearTimer;           // Currently used by IsItemHovered(): grace time before g.TooltipHoverTimer gets cleared.
    uiID  HoverItemUnlockedStationaryId;      // Mouse has once been stationary on this item. Only reset after departing the item.
    uiID  HoverWindowUnlockedStationaryId;    // Mouse has once been stationary on this window. Only reset after departing the window.

    // Mouse state
    uiMouseCursor MouseCursor;
    float         MouseStationaryTimer;               // Time the mouse has been stationary (with some loose heuristic)
    vec2        MouseLastValidPos;

    // Widget state
    uiInputTextState            InputTextState;
    uiTextIndex                 InputTextLineIndex;                 // Temporary storage
    uiInputTextDeactivatedState InputTextDeactivatedState;
    ImFontBaked                 InputTextPasswordFontBackupBaked;
    ImFontFlags                 InputTextPasswordFontBackupFlags;
    uiID                        InputTextReactivateId;              // ID of InputText to reactivate on next frame (for io.ConfigInputTextEnterKeepActive behavior)
    uiID                        TempInputId;                        // Temporary text input when using Ctrl+Click on a slider, etc.
    uiDataTypeStorage           DataTypeZeroValue;                  // 0 for all data types
    int                         BeginMenuDepth;
    int                         BeginComboDepth;
    uiColorEditFlags            ColorEditOptions;                   // Store user options for color edit widgets
    uiID                        ColorEditCurrentID;                 // Set temporarily while inside of the parent-most ColorEdit4/ColorPicker4 (because they call each others).
    uiID                        ColorEditSavedID;                   // ID we are saving/restoring HS for
    float                       ColorEditSavedHue;                  // Backup of last Hue associated to LastColor, so we can restore Hue in lossy RGB<>HSV round trips
    float                       ColorEditSavedSat;                  // Backup of last Saturation associated to LastColor, so we can restore Saturation in lossy RGB<>HSV round trips
    ImU32                       ColorEditSavedColor;                // RGB value with alpha set to 0.
    vec4                      ColorPickerRef;                     // Initial/reference color at the time of opening the color picker.
    uiComboPreviewData       ComboPreviewData;
    ImRect                      WindowResizeBorderExpectedRect;     // Expected border rect, switch to relative edit if moving
    bool                        WindowResizeRelativeMode;
    short                       ScrollbarSeekMode;                  // 0: scroll to clicked location, -1/+1: prev/next page.
    float                       ScrollbarClickDeltaToGrabCenter;    // When scrolling to mouse location: distance between mouse and center of grab box, normalized in parent space.
    float                       SliderGrabClickOffset;
    float                       SliderCurrentAccum;                 // Accumulated slider delta when using navigation controls.
    bool                        SliderCurrentAccumDirty;            // Has the accumulated slider delta changed since last time we tried to apply it?
    bool                        DragCurrentAccumDirty;
    float                       DragCurrentAccum;                   // Accumulator for dragging modification. Always high-precision, not rounded by end-user precision settings
    float                       DragSpeedDefaultRatio;              // If speed == 0.0f, uses (max-min) * DragSpeedDefaultRatio
    float                       DisabledAlphaBackup;                // Backup for style.Alpha for BeginDisabled()
    short                       DisabledStackSize;
    short                       TooltipOverrideCount;
    uiWindow*                   TooltipPreviousWindow;              // Window of last tooltip submitted during the frame
    ImVector<char>              ClipboardHandlerData;               // If no custom clipboard handler is defined
    ImVector<uiID>              MenusIdSubmittedThisFrame;          // A list of menu IDs that were rendered at least once
    uiTypingSelectState         TypingSelectState;                  // State for GetTypingSelectRequest()
    // Platform support
    uiPlatformImeData           PlatformImeData;                    // Data updated by current frame. Will be applied at end of the frame. For some backends, this is required to have WantVisible=true in order to receive text message.
    uiPlatformImeData           PlatformImeDataPrev;                // Previous frame data. When changed we call the platform_io.Platform_SetImeDataFn() handler.
    // Extensions
    // FIXME: We could provide an API to register one slot in an array held in uiContext?
    ImVector<ImTextureData*> UserTextures;                      // List of textures created/managed by user or third-party extension. Automatically appended into platform_io.Textures[].
    uiDockContext        DockContext;
    void                    (*DockNodeWindowMenuHandler)(uiContext* ctx, uiDockNode* node, uiTabBar* tab_bar);
    // Settings
    bool                    SettingsLoaded;
    float                   SettingsDirtyTimer;                 // Save .ini Settings to memory when time reaches zero
    uiTextBuffer            SettingsIniData;                    // In memory .ini settings
    ImVector<uiSettingsHandler>      SettingsHandlers;       // List of .ini settings handlers
    ImChunkStream<uiWindowSettings>  SettingsWindows;        // uiWindow .ini settings entries
    ImChunkStream<uiTableSettings>   SettingsTables;         // uiTable .ini settings entries
    // Hooks
    ImVector<uiContextHook>          Hooks;                  // Hooks for extensions (e.g. test engine)
    uiID                             HookIdNext;             // Next available HookId
    uiDemoMarkerCallback             DemoMarkerCallback;
    // Localization
    const char*             LocalizationTable[uiLocKey_COUNT];
    // Capture/Logging
    bool                    LogEnabled;                         // Currently capturing
    bool                    LogLineFirstItem;
    uiLogFlags           LogFlags;                           // Capture flags/type
    uiWindow*               LogWindow;
    ImFileHandle            LogFile;                            // If != NULL log to stdout/ file
    uiTextBuffer            LogBuffer;                          // Accumulation buffer when log to clipboard. This is pointer so our GImGui static constructor doesn't call heap allocators.
    const char*             LogNextPrefix;                      // See comment in LogSetNextTextDecoration(): doesn't copy underlying data, use carefully!
    const char*             LogNextSuffix;
    float                   LogLinePosY;
    int                     LogDepthRef;
    int                     LogDepthToExpand;
    int                     LogDepthToExpandDefault;            // Default/stored value for LogDepthMaxExpand if not specified in the LogXXX function call.
    // Error Handling
    uiErrorCallback      ErrorCallback;                      // = NULL. May be exposed in public API eventually.
    void*                   ErrorCallbackUserData;              // = NULL
    vec2                  ErrorTooltipLockedPos;
    bool                    ErrorFirst;
    int                     ErrorCountCurrentFrame;             // [Internal] Number of errors submitted this frame.
    uiErrorRecoveryState StackSizesInNewFrame;               // [Internal]
    uiErrorRecoveryState*StackSizesInBeginForCurrentWindow;  // [Internal]

    // Debug Tools
    // (some of the highly frequently used data are interleaved in other structures above: DebugBreakXXX fields, DebugHookIdInfo, DebugLocateId etc.)
    int                     DebugDrawIdConflictsCount;          // Locked count (preserved when holding Ctrl)
    uiDebugLogFlags      DebugLogFlags;
    uiTextBuffer         DebugLogBuf;
    uiTextIndex          DebugLogIndex;
    int                     DebugLogSkippedErrors;
    uiDebugLogFlags      DebugLogAutoDisableFlags;
    ImU8                    DebugLogAutoDisableFrames;
    ImU8                    DebugLocateFrames;                  // For DebugLocateItemOnHover(). This is used together with DebugLocateId which is in a hot/cached spot above.
    bool                    DebugBreakInLocateId;               // Debug break in ItemAdd() call for g.DebugLocateId.
    uiKeyChord           DebugBreakKeyChord;                 // = uiKey_Pause
    ImS8                    DebugBeginReturnValueCullDepth;     // Cycle between 0..9 then wrap around.
    bool                    DebugItemPickerActive;              // Item picker is active (started with DebugStartItemPicker())
    ImU8                    DebugItemPickerMouseButton;
    uiID                 DebugItemPickerBreakId;             // Will call IM_DEBUG_BREAK() when encountering this ID
    float                   DebugFlashStyleColorTime;
    vec4                  DebugFlashStyleColorBackup;
    uiMetricsConfig      DebugMetricsConfig;
    uiDebugItemPathQuery DebugItemPathQuery;
    uiIDStackTool        DebugIDStackTool;
    uiDebugAllocInfo     DebugAllocInfo;
    uiDockNode*          DebugHoveredDockNode;               // Hovered dock node.
#if defined(IMGUI_DEBUG_HIGHLIGHT_ALL_ID_CONFLICTS) && !defined(IMGUI_DISABLE_DEBUG_TOOLS)
    uiStorage            DebugDrawIdConflictsAliveCount;
    uiStorage            DebugDrawIdConflictsHighlightSet;
#endif

    // Misc
    float                   FramerateSecPerFrame[60];           // Calculate estimate of framerate for user over the last 60 frames..
    int                     FramerateSecPerFrameIdx;
    int                     FramerateSecPerFrameCount;
    float                   FramerateSecPerFrameAccum;
    int                     WantCaptureMouseNextFrame;          // Explicit capture override via SetNextFrameWantCaptureMouse()/SetNextFrameWantCaptureKeyboard(). Default to -1.
    int                     WantCaptureKeyboardNextFrame;       // "
    int                     WantTextInputNextFrame;             // Copied in EndFrame() from g.PlatformImeData.WantTextInput. Needs to be set for some backends (SDL3) to emit character inputs.
    ImVector<char>          TempBuffer;                         // Temporary text buffer
    char                    TempKeychordName[64];

    uiContext(ImFontAtlas* shared_font_atlas);
    ~uiContext();
};

//-----------------------------------------------------------------------------
// [SECTION] uiWindowTempData, uiWindow
//-----------------------------------------------------------------------------
#define IMGUI_WINDOW_HARD_MIN_SIZE 4.0f
// Transient per-window data, reset at the beginning of the frame. This used to be called uiDrawContext, hence the DC variable name in uiWindow.
// (That's theory, in practice the delimitation between uiWindow and uiWindowTempData is quite tenuous and could be reconsidered..)
// (This doesn't need a constructor because we zero-clear it as part of uiWindow and all frame-temporary data are setup on Begin)
struct IMGUI_API uiWindowTempData {
    // Layout
    vec2   CursorPos;              // Current emitting position, in absolute coordinates.
    vec2   CursorPosPrevLine;
    vec2   CursorStartPos;         // Initial position after Begin(), generally ~ window position + WindowPadding.
    vec2   CursorMaxPos;           // Used to implicitly calculate ContentSize at the beginning of next frame, for scrolling range and auto-resize. Always growing during the frame.
    vec2   IdealMaxPos;            // Used to implicitly calculate ContentSizeIdeal at the beginning of next frame, for auto-resize only. Always growing during the frame.
    vec2   CurrLineSize;
    vec2   PrevLineSize;
    float  CurrLineTextBaseOffset; // Baseline offset (0.0f by default on a new line, generally == style.FramePadding.y when a framed item has been added).
    float  PrevLineTextBaseOffset;
    bool   IsNext;
    bool   IsSetPos;
    vec1   Indent;                 // Indentation / start position from left of window (increased by TreePush/TreePop, etc.)
    vec1   ColumnsOffset;          // Offset to the current column (if ColumnsCurrent > 0). FIXME: This and the above should be a stack to allow use cases like Tree->Column->Tree. Need revamp columns API.
    vec1   GroupOffset;
    vec2   CursorStartPosLossyness;// Record the loss of precision of CursorStartPos due to really large scrolling amount. This is used by clipper to compensate and fix the most common use case of large scroll area.
    // Keyboard/Gamepad navigation
    uiNavLayer NavLayerCurrent;        // Current layer, 0..31 (we currently only use 0..1)
    short NavLayersActiveMask;    // Which layers have been written to (result from previous frame)
    short NavLayersActiveMaskNext;// Which layers have been written to (accumulator for current frame)
    bool  NavIsScrollPushableX;   // Set when current work location may be scrolled horizontally when moving left / right. This is generally always true UNLESS within a column.
    bool  NavHideHighlightOneFrame;
    bool  NavWindowHasScrollY;    // Set per window when scrolling can be used (== ScrollMax.y > 0.0f)
    // Miscellaneous
    bool                MenuBarAppending;       // FIXME: Remove this
    vec2                MenuBarOffset;          // MenuBarOffset.x is sort of equivalent of a per-layer CursorPos.x, saved/restored as we switch to the menu bar. The only situation when MenuBarOffset.y is > 0 if when (SafeAreaPadding.y > FramePadding.y), often used on TVs.
    uiMenuColumns       MenuColumns;            // Simplified columns storage for menu items measurement
    int                 TreeDepth;              // Current tree depth.
    ImU32               TreeHasStackDataDepthMask;      // Store whether given depth has uiTreeNodeStackData data. Could be turned into a ImU64 if necessary.
    ImU32               TreeRecordsClippedNodesY2Mask;  // Store whether we should keep recording Y2. Cleared when passing clip max. Equivalent TreeHasStackDataDepthMask value should always be set.
    ImVector<uiWindow*> ChildWindows;
    uiStorage*          StateStorage;           // Current persistent per-window storage (store e.g. tree node open/close state)
    uiOldColumns*       CurrentColumns;         // Current columns set
    int                 CurrentTableIdx;        // Current table index (into g.Tables)
    uiLayoutType        LayoutType;
    uiLayoutType        ParentLayoutType;       // Layout type of parent window at the time of Begin()
    ImU32               ModalDimBgColor;
    // Status flags
    uiItemStatusFlags WindowItemStatusFlags;
    uiItemStatusFlags ChildItemStatusFlags;
    uiItemStatusFlags DockTabItemStatusFlags;
    ImRect            DockTabItemRect;
    // Local parameters stacks
    // We store the current settings outside of the vectors to increase memory locality (reduce cache misses). The vectors are rarely modified. Also it allows us to not heap allocate for short-lived windows which are not using those settings.
    float ItemWidth;                  // Current item width (>0.0: width in pixels, <0.0: align xx pixels to the right of window).
    float ItemWidthDefault;
    float TextWrapPos;                // Current text wrap pos.
    ImVector<float> ItemWidthStack;   // Store item widths to restore (attention: .back() is not == ItemWidth)
    ImVector<float> TextWrapPosStack; // Store text wrap pos to restore (attention: .back() is not == TextWrapPos)
};
// Storage for one window
struct IMGUI_API uiWindow {
    uiContext*           Ctx;                                // Parent UI context (needs to be set explicitly by parent).
    char*                Name;                               // Window name, owned by the window.
    uiID                 ID;                                 // == ImHashStr(Name)
    uiWindowFlags        Flags, FlagsPreviousFrame;          // See enum uiWindowFlags_
    uiChildFlags         ChildFlags;                         // Set when window is a child window. See enum uiChildFlags_
    uiWindowClass        WindowClass;                        // Advanced users only. Set with SetNextWindowClass()
    uiViewportP*         Viewport;                           // Always set in Begin(). Inactive windows may have a NULL value here if their viewport was discarded.
    uiID                 ViewportId;                         // We backup the viewport id (since the viewport may disappear or never be created if the window is inactive)
    vec2                 ViewportPos;                        // We backup the viewport position (since the viewport may disappear or never be created if the window is inactive)
    int                  ViewportAllowPlatformMonitorExtend; // Reset to -1 every frame (index is guaranteed to be valid between NewFrame..EndFrame), only used in the Appearing frame of a tooltip/popup to enforce clamping to a given monitor
    vec2                 Pos;                                // Position (always rounded-up to nearest pixel)
    vec2                 Size;                               // Current size (==SizeFull or collapsed title bar size)
    vec2                 SizeFull;                           // Size when non collapsed
    vec2                 ContentSize;                        // Size of contents/scrollable client area (calculated from the extents reach of the cursor) from previous frame. Does not include window decoration or window padding.
    vec2                 ContentSizeIdeal;
    vec2                 ContentSizeExplicit;                // Size of contents/scrollable client area explicitly request by the user via SetNextWindowContentSize().
    vec2                 WindowPadding;                      // Window padding at the time of Begin().
    float                WindowRounding;                     // Window rounding at the time of Begin(). May be clamped lower to avoid rendering artifacts with title bar, menu bar etc.
    float                WindowBorderSize;                   // Window border size at the time of Begin().
    float                TitleBarHeight,  MenuBarHeight;     // Note that those used to be function before 2024/05/28. If you have old code calling TitleBarHeight() you can change it to TitleBarHeight.
    float                DecoOuterSizeX1, DecoOuterSizeY1;   // Left/Up offsets. Sum of non-scrolling outer decorations (X1 generally == 0.0f. Y1 generally = TitleBarHeight + MenuBarHeight). Locked during Begin().
    float                DecoOuterSizeX2, DecoOuterSizeY2;   // Right/Down offsets (X2 generally == ScrollbarSize.x, Y2 == ScrollbarSizes.y).
    float                DecoInnerSizeX1, DecoInnerSizeY1;   // Applied AFTER/OVER InnerRect. Specialized for Tables as they use specialized form of clipping and frozen rows/columns are inside InnerRect (and not part of regular decoration sizes).
    int                  NameBufLen;                         // Size of buffer storing Name. May be larger than strlen(Name)!
    uiID                 MoveId;                             // == window->GetID("#MOVE")
    uiID                 TabId;                              // == window->GetID("#TAB")
    uiID                 ChildId;                            // ID of corresponding item in parent window (for navigation to return from child window to parent window)
    uiID                 PopupId;                            // ID in the popup stack when this window is used as a popup/menu (because we use generic Name/ID for recycling)
    vec2                 Scroll;
    vec2                 ScrollMax;
    vec2                 ScrollTarget;                       // target scroll position. stored as cursor position with scrolling canceled out, so the highest point is always 0.0f. (FLT_MAX for no change)
    vec2                 ScrollTargetCenterRatio;            // 0.0f = scroll so that target position is at top, 0.5f = scroll so that target position is centered
    vec2                 ScrollTargetEdgeSnapDist;           // 0.0f = no snapping, >0.0f snapping threshold
    vec2                 ScrollbarSizes;                     // Size taken by each scrollbars on their smaller axis. Pay attention! ScrollbarSizes.x == width of the vertical scrollbar, ScrollbarSizes.y = height of the horizontal scrollbar.
    bool                 ScrollbarX, ScrollbarY;             // Are scrollbars visible?
    bool                 ScrollbarXStabilizeEnabled;         // Was ScrollbarX previously auto-stabilized?
    ImU8                 ScrollbarXStabilizeToggledHistory;  // Used to stabilize scrollbar visibility in case of feedback loops
    bool                 ViewportOwned;
    bool                 Active;                             // Set to true on Begin(), unless Collapsed
    bool                 WasActive;
    bool                 WriteAccessed;                      // Set to true when any widget access the current window
    bool                 Collapsed;                          // Set when collapsing window to become only title-bar
    bool                 WantCollapseToggle;
    bool                 SkipItems;                          // Set when items can safely be all clipped (e.g. window not visible or collapsed)
    bool                 SkipRefresh;                        // [EXPERIMENTAL] Reuse previous frame drawn contents, Begin() returns false.
    bool                 Appearing;                          // Set during the frame where the window is appearing (or re-appearing)
    bool                 Hidden;                             // Do not display (== HiddenFrames*** > 0)
    bool                 IsFallbackWindow;                   // Set on the "Debug##Default" window.
    bool                 IsExplicitChild;                    // Set when passed _ChildWindow, left to false by BeginDocked()
    bool                 HasCloseButton;                     // Set when the window has a close button (p_open != NULL)
    signed char          ResizeBorderHovered;                // Current border being hovered for resize (-1: none, otherwise 0-3)
    signed char          ResizeBorderHeld;                   // Current border being held for resize (-1: none, otherwise 0-3)
    short                BeginCount;                         // Number of Begin() during the current frame (generally 0 or 1, 1+ if appending via multiple Begin/End pairs)
    short                BeginCountPreviousFrame;            // Number of Begin() during the previous frame
    short                BeginOrderWithinParent;             // Begin() order within immediate parent window, if we are a child window. Otherwise 0.
    short                BeginOrderWithinContext;            // Begin() order within entire imgui context. This is mostly used for debugging submission order related issues.
    short                FocusOrder;                         // Order within WindowsFocusOrder[], altered when windows are focused.
    Var::Dir             AutoPosLastDirection;
    ImS8                 AutoFitFramesX, AutoFitFramesY;
    bool                 AutoFitOnlyGrows;
    ImS8                 HiddenFramesCanSkipItems;           // Hide the window for N frames
    ImS8                 HiddenFramesCannotSkipItems;        // Hide the window for N frames while allowing items to be submitted so we can measure their size
    ImS8                 HiddenFramesForRenderOnly;          // Hide the window until frame N at Render() time only
    ImS8                 DisableInputsFrames;                // Disable window interactions for N frames
    uiWindowBgClickFlags BgClickFlags : 8;                   // Configure behavior of click+dragging on window bg/void or over items. Default sets by io.ConfigWindowsMoveFromTitleBarOnly. If you use this please report in #3379.
    uiCond               SetWindowPosAllowFlags : 8;         // store acceptable condition flags for SetNextWindowPos() use.
    uiCond               SetWindowSizeAllowFlags : 8;        // store acceptable condition flags for SetNextWindowSize() use.
    uiCond               SetWindowCollapsedAllowFlags : 8;   // store acceptable condition flags for SetNextWindowCollapsed() use.
    uiCond               SetWindowDockAllowFlags : 8;        // store acceptable condition flags for SetNextWindowDock() use.
    vec2                 SetWindowPosVal;                    // store window position when using a non-zero Pivot (position set needs to be processed when we know the window size)
    vec2                 SetWindowPosPivot;                  // store window pivot for positioning. vec2(0, 0) when positioning from top-left corner; vec2(0.5f, 0.5f) for centering; vec2(1, 1) for bottom right.
    ImVector<uiID>       IDStack;                            // ID stack. ID are hashes seeded with the value at the top of the stack. (In theory this should be in the TempData structure)
    uiWindowTempData     DC;                                 // Temporary per-window data, reset at the beginning of the frame. This used to be called uiDrawContext, hence the "DC" variable name.
    // The best way to understand what those rectangles are is to use the 'Metrics->Tools->Show Windows Rectangles' viewer.
    // The main 'OuterRect', omitted as a field, is window->Rect().
    ImRect OuterRectClipped;  // == Window->Rect() just after setup in Begin(). == window->Rect() for root window.
    ImRect InnerRect;         // Inner rectangle (omit title bar, menu bar, scroll bar)
    ImRect InnerClipRect;     // == InnerRect shrunk by WindowPadding*0.5f on each side, clipped within viewport or parent clip rect.
    ImRect WorkRect;          // Initially covers the whole scrolling region. Reduced by containers e.g columns/tables when active. Shrunk by WindowPadding*1.0f on each side. This is meant to replace ContentRegionRect over time (from 1.71+ onward).
    ImRect ParentWorkRect;    // Backup of WorkRect before entering a container such as columns/tables. Used by e.g. SpanAllColumns functions to easily access. Stacked containers are responsible for maintaining this. // FIXME-WORKRECT: Could be a stack?
    ImRect ClipRect;          // Current clipping/scissoring rectangle, evolve as we are using PushClipRect(), etc. == DrawList->clip_rect_stack.back().
    ImRect ContentRegionRect; // FIXME: This is currently confusing/misleading. It is essentially WorkRect but not handling of scrolling. We currently rely on it as right/bottom aligned sizing operation need some size to rely on.
    vec2ih HitTestHoleSize;   // Define an optional rectangular hole where mouse will pass-through the window.
    vec2ih HitTestHoleOffset;
    int       LastFrameActive;      // Last frame number the window was Active.
    int       LastFrameJustFocused; // Last frame number the window was made Focused.
    float     LastTimeActive;       // Last timestamp the window was Active (using float as we don't need high precision there)
    uiStorage StateStorage;
    ImVector<uiOldColumns> ColumnsStorage;
    float FontWindowScale;                    // User scale multiplier per-window, via SetWindowFontScale()
    float FontWindowScaleParents;
    float FontRefSize;                        // This is a copy of window->CalcFontSize() at the time of Begin(), trying to phase out CalcFontSize() especially as it may be called on non-current window.
    int   SettingsOffset;                     // Offset into SettingsWindows[] (offsets are always valid as we only grow the array from the back)
    ImDrawList* DrawList;                         // == &DrawListInst (for backward compatibility reason with code using imgui_internal.h we keep this a pointer)
    ImDrawList  DrawListInst;
    uiWindow* ParentWindow;                       // If we are a child _or_ popup _or_ docked window, this is pointing to our parent. Otherwise NULL.
    uiWindow* ParentWindowInBeginStack;
    uiWindow* RootWindow;                         // Point to ourself or first ancestor that is not a child window. Doesn't cross through popups/dock nodes.
    uiWindow* RootWindowPopupTree;                // Point to ourself or first ancestor that is not a child window. Cross through popups parent<>child.
    uiWindow* RootWindowDockTree;                 // Point to ourself or first ancestor that is not a child window. Cross through dock nodes.
    uiWindow* RootWindowForTitleBarHighlight;     // Point to ourself or first ancestor which will display TitleBgActive color when this window is active.
    uiWindow* RootWindowForNav;                   // Point to ourself or first ancestor which doesn't have the NavFlattened flag.
    uiWindow* ParentWindowForFocusRoute;          // Set to manual link a window to its logical parent so that Shortcut() chain are honored (e.g. Tool linked to Document)
    uiWindow* NavLastChildNavWindow;        // When going to the menu bar, we remember the child window we came from. (This could probably be made implicit if we kept g.Windows sorted by last focused including child window.)
    uiID      NavLastIds[uiNavLayer_COUNT]; // Last known NavId for this window, per layer (0/1)
    ImRect    NavRectRel[uiNavLayer_COUNT]; // Reference rectangle, in window relative space
    vec2      NavPreferredScoringPosRel[uiNavLayer_COUNT]; // Preferred X/Y position updated when moving on a given axis, reset to FLT_MAX.
    uiID      NavRootFocusScopeId;          // Focus Scope ID at the time of Begin()
    int  MemoryDrawListIdxCapacity; // Backup of last idx/vtx count, so when waking up the window we can preallocate and avoid iterative alloc/copy
    int  MemoryDrawListVtxCapacity;
    bool MemoryCompacted;           // Set when window extraneous data have been garbage collected
    // Docking
    bool  DockIsActive      :1;  // When docking artifacts are actually visible. When this is set, DockNode is guaranteed to be != NULL. ~~ (DockNode != NULL) && (DockNode->Windows.Size > 1).
    bool  DockNodeIsVisible :1;
    bool  DockTabIsVisible  :1;  // Is our window visible this frame? ~~ is the corresponding tab selected?
    bool  DockTabWantClose  :1;
    short DockOrder;             // Order of the last time the window was visible within its DockNode. This is used to reorder windows that are reappearing on the same frame. Same value between windows that were active and windows that were none are possible.
    uiWindowDockStyle DockStyle;
    uiDockNode* DockNode;        // Which node are we docked into. Important: Prefer testing DockIsActive in many cases as this will still be set when the dock node is hidden.
    uiDockNode* DockNodeAsHost;  // Which node are we owning (for parent windows)
    uiID        DockId;          // Backup of last valid DockNode->ID, so single window remember their dock node id even when they are not bound any more
public:
    uiWindow(uiContext* context, const char* name);
    ~uiWindow();
    uiID GetID(const char* str, const char* str_end = NULL);
    uiID GetID(const void* ptr);
    uiID GetID(int n);
    uiID GetIDFromPos(const vec2& p_abs);
    uiID GetIDFromRectangle(const ImRect& r_abs);
    // We don't use g.FontSize because the window may be != g.CurrentWindow.
    ImRect Rect() const         { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }
    ImRect TitleBarRect() const { return ImRect(Pos, vec2(Pos.x + SizeFull.x, Pos.y + TitleBarHeight)); }
    ImRect MenuBarRect() const  { float y1 = Pos.y + TitleBarHeight; return ImRect(Pos.x, y1, Pos.x + SizeFull.x, y1 + MenuBarHeight); }
    // [OBSOLETE] uiWindow::CalcFontSize() was removed in 1.92.0 because error-prone/misleading. You can use window->FontRefSize for a copy of g.FontSize at the time of the last Begin() call for this window.
    //float     CalcFontSize() const    { uiContext& g = *Ctx; return g.FontSizeBase * FontWindowScale * FontDpiScale * FontWindowScaleParents;
};
//-----------------------------------------------------------------------------
// [SECTION] Tab bar, Tab item support
//-----------------------------------------------------------------------------
// Extend uiTabBarFlags_
enum uiTabBarFlagsPrivate_ {
    uiTabBarFlags_DockNode     = 1 << 20, // Part of a dock node [we don't use this in the master branch but it facilitate branch syncing to keep this around]
    uiTabBarFlags_IsFocused    = 1 << 21,
    uiTabBarFlags_SaveSettings = 1 << 22, // FIXME: Settings are handled by the docking system, this only request the tab bar to mark settings dirty when reordering tabs
};
// Extend uiTabItemFlags_
enum uiTabItemFlagsPrivate_ {
    uiTabItemFlags_SectionMask_  = uiTabItemFlags_Leading | uiTabItemFlags_Trailing,
    uiTabItemFlags_NoCloseButton = 1 << 20,  // Track whether p_open was set or not (we'll need this info on the next frame to recompute ContentWidth during layout)
    uiTabItemFlags_Button        = 1 << 21,  // Used by TabItemButton, change the tab item behavior to mimic a button
    uiTabItemFlags_Invisible     = 1 << 22,  // To reserve space e.g. with uiTabItemFlags_Leading
    uiTabItemFlags_Unsorted      = 1 << 23,  // [Docking] Trailing tabs with the _Unsorted flag will be sorted based on the DockOrder of their Window.
};
// Storage for one active tab item (sizeof() 48 bytes)
struct uiTabItem {
    uiID           ID;
    uiTabItemFlags Flags;
    uiWindow*      Window;            // When TabItem is part of a DockNode's TabBar, we hold on to a window.
    int   LastFrameVisible;
    int   LastFrameSelected; // This allows us to infer an ordered list of the last activated tabs with little maintenance
    float Offset;            // Position relative to beginning of tab bar
    float Width;             // Width currently displayed
    float ContentWidth;      // Width of label + padding, stored during BeginTabItem() call (misnamed as "Content" would normally imply width of label only)
    float RequestedWidth;    // Width optionally requested by caller, -1.0f is unused
    ImS32 NameOffset;        // When Window==NULL, offset to name within parent uiTabBar::TabsNames
    ImS16 BeginOrder;        // BeginTabItem() order, used to re-order tabs after toggling uiTabBarFlags_Reorderable
    ImS16 IndexDuringLayout; // Index only used during TabBarLayout(). Tabs gets reordered so 'Tabs[n].IndexDuringLayout == n' but may mismatch during additions.
    bool  WantClose;         // Marked as closed by SetTabItemClosed()
    uiTabItem() { memset((void*)this, 0, sizeof(*this)); LastFrameVisible = LastFrameSelected = -1; RequestedWidth = -1.0f; NameOffset = -1; BeginOrder = IndexDuringLayout = -1; }
};
// Storage for a tab bar (sizeof() 160 bytes)
struct IMGUI_API uiTabBar {
    uiWindow*           Window;
    ImVector<uiTabItem> Tabs;
    uiTabBarFlags       Flags;
    uiID   ID;                     // Zero for tab-bars used by docking
    uiID   SelectedTabId;          // Selected tab/window
    uiID   NextSelectedTabId;      // Next selected tab/window. Will also trigger a scrolling animation
    uiID   NextScrollToTabId;
    uiID   VisibleTabId;           // Can occasionally be != SelectedTabId (e.g. when previewing contents for Ctrl+Tab preview)
    int    CurrFrameVisible;
    int    PrevFrameVisible;
    ImRect BarRect;
    float  BarRectPrevWidth;       // Backup of previous width. When width change we enforce keep horizontal scroll on focused tab.
    float  CurrTabsContentsHeight;
    float  PrevTabsContentsHeight; // Record the height of contents submitted below the tab bar
    float  WidthAllTabs;           // Actual width of all tabs (locked during layout)
    float  WidthAllTabsIdeal;      // Ideal width if all tabs were visible and not clipped
    float  ScrollingAnim;
    float  ScrollingTarget;
    float  ScrollingTargetDistToVisibility;
    float  ScrollingSpeed;
    float  ScrollingRectMinX;
    float  ScrollingRectMaxX;
    float  BarrierMinX;
    float  BarrierMaxX;
    uiID   ReorderRequestTabId;
    ImS16  ReorderRequestOffset;
    ImS8   BeginCount;
    bool   WantLayout;
    bool   VisibleTabWasSubmitted;
    bool   TabsAddedNew;           // Set to true when a new tab item or button has been added to the tab bar during last frame
    bool   ScrollButtonEnabled;
    ImS16  TabsActiveCount;        // Number of tabs submitted this frame.
    ImS16  LastTabItemIdx;         // Index of last BeginTabItem() tab for use by EndTabItem()
    float  ItemSpacingY;
    vec2   FramePadding;           // style.FramePadding locked at the time of BeginTabBar()
    vec2   BackupCursorPos;
    uiTextBuffer TabsNames;              // For non-docking tab bar we re-append names in a contiguous buffer.
    uiTabBar();
};
//-----------------------------------------------------------------------------
// [SECTION] Table support
//-----------------------------------------------------------------------------
#define IM_COL32_DISABLE        IM_COL32(0,0,0,1) // Special sentinel code which cannot be used as a regular color.
#define IMGUI_TABLE_MAX_COLUMNS 512               // Arbitrary "safety" maximum, may be lifted in the future if needed. Must fit in uiTableColumnIdx/uiTableDrawChannelIdx.
// [Internal] sizeof() ~ 112
// We use the terminology "Enabled" to refer to a column that is not Hidden by user/api.
// We use the terminology "Clipped" to refer to a column that is out of sight because of scrolling/clipping.
// This is in contrast with some user-facing api such as IsItemVisible() / IsRectVisible() which use "Visible" to mean "not clipped".
struct uiTableColumn {
    uiTableColumnFlags Flags; // Flags after some patching (not directly same as provided by user). See uiTableColumnFlags_
    float  WidthGiven;                     // Final/actual width visible == (MaxX - MinX), locked in TableUpdateLayout(). May be > WidthRequest to honor minimum width, may be < WidthRequest to honor shrinking columns down in tight space.
    float  MinX;                           // Absolute positions
    float  MaxX;
    float  WidthRequest;                   // Master width absolute value when !(Flags & _WidthStretch). When Stretch this is derived every frame from StretchWeight in TableUpdateLayout()
    float  WidthAuto;                      // Automatic width
    float  WidthMax;                       // Maximum width (FIXME: overwritten by each instance)
    float  StretchWeight;                  // Master width weight when (Flags & _WidthStretch). Often around ~1.0f initially.
    float  InitStretchWeightOrWidth;       // Value passed to TableSetupColumn(). For Width it is a content width (_without padding_).
    ImRect ClipRect;                       // Clipping rectangle for the column
    uiID   UserID;                         // Optional, value passed to TableSetupColumn()
    float  WorkMinX;                       // Contents region min ~(MinX + CellPaddingX + CellSpacingX1) == cursor start position when entering column
    float  WorkMaxX;                       // Contents region max ~(MaxX - CellPaddingX - CellSpacingX2)
    float  ItemWidth;                      // Current item width for the column, preserved across rows
    float  ContentMaxXFrozen;              // Contents maximum position for frozen rows (apart from headers), from which we can infer content width.
    float  ContentMaxXUnfrozen;
    float  ContentMaxXHeadersUsed;         // Contents maximum position for headers rows (regardless of freezing). TableHeader() automatically softclip itself + report ideal desired size, to avoid creating extraneous draw calls
    float  ContentMaxXHeadersIdeal;
    ImS16  NameOffset;                     // Offset into parent ColumnsNames[]
    uiTableColumnIdx DisplayOrder;                   // Index within Table's IndexToDisplayOrder[] (column may be reordered by users)
    uiTableColumnIdx IndexWithinEnabledSet;          // Index within enabled/visible set (<= IndexToDisplayOrder)
    uiTableColumnIdx PrevEnabledColumn;              // Index of prev enabled/visible column within Columns[], -1 if first enabled/visible column
    uiTableColumnIdx NextEnabledColumn;              // Index of next enabled/visible column within Columns[], -1 if last enabled/visible column
    uiTableColumnIdx SortOrder;                      // Index of this column within sort specs, -1 if not sorting on this column, 0 for single-sort, may be >0 on multi-sort
    uiTableDrawChannelIdx DrawChannelCurrent;            // Index within DrawSplitter.Channels[]
    uiTableDrawChannelIdx DrawChannelFrozen;             // Draw channels for frozen rows (often headers)
    uiTableDrawChannelIdx DrawChannelUnfrozen;           // Draw channels for unfrozen rows
    bool IsEnabled;                      // IsUserEnabled && (Flags & uiTableColumnFlags_Disabled) == 0
    bool IsUserEnabled;                  // Is the column not marked Hidden by the user? (unrelated to being off view, e.g. clipped by scrolling).
    bool IsUserEnabledNextFrame;
    bool IsVisibleX;                     // Is actually in view (e.g. overlapping the host window clipping rectangle, not scrolled).
    bool IsVisibleY;
    bool IsRequestOutput;                // Return value for TableSetColumnIndex() / TableNextColumn(): whether we request user to output contents or not.
    bool IsSkipItems;                    // Do we want item submissions to this column to be completely ignored (no layout will happen).
    bool IsPreserveWidthAuto;
    ImS8 NavLayerCurrent;                // uiNavLayer in 1 byte
    ImU8 AutoFitQueue;                   // Queue of 8 values for the next 8 frames to request auto-fit
    ImU8 CannotSkipItemsQueue;           // Queue of 8 values for the next 8 frames to disable Clipped/SkipItem
    ImU8 SortDirection : 2;              // Var::SortDir::Up or Var::SortDir::Descend
    ImU8 SortDirectionsAvailCount : 2;   // Number of available sort directions (0 to 3)
    ImU8 SortDirectionsAvailMask : 4;    // Mask of available sort directions (1-bit each)
    ImU8 SortDirectionsAvailList;        // Ordered list of available sort directions (2-bits each, total 8-bits)
    uiTableColumn() {
        memset((void*)this, 0, sizeof(*this));
        StretchWeight = WidthRequest = -1.0f;
        NameOffset = -1;
        DisplayOrder = IndexWithinEnabledSet = -1;
        PrevEnabledColumn = NextEnabledColumn = -1;
        SortOrder = -1;
        SortDirection = Var::SortDir::Hold;
        DrawChannelCurrent = DrawChannelFrozen = DrawChannelUnfrozen = (ImU8)-1;
    }
};
// Transient cell data stored per row. sizeof() ~ 6 bytes. color. column
struct uiTableCellData { ImU32 BgColor; uiTableColumnIdx Column; };
// Parameters for TableAngledHeadersRowEx()
// This may end up being refactored for more general purpose.
// sizeof() ~ 12 bytes
struct uiTableHeaderData {
    uiTableColumnIdx Index; // Column index
    ImU32 TextColor;
    ImU32 BgColor0;
    ImU32 BgColor1;
};
// Per-instance data that needs preserving across frames (seemingly most others do not need to be preserved aside from debug needs. Does that means they could be moved to uiTableTempData?)
// sizeof() ~ 24 bytes
struct uiTableInstanceData {
    uiID  TableInstanceID;
    float LastOuterHeight;         // Outer height from last frame
    float LastTopHeadersRowHeight; // Height of first consecutive header rows from last frame (FIXME: this is used assuming consecutive headers are in same frozen set)
    float LastFrozenHeight;        // Height of frozen section from last frame
    int   HoveredRowLast;          // Index of row which was hovered last frame.
    int   HoveredRowNext;          // Index of row hovered this frame, set after encountering it.
    uiTableInstanceData() { TableInstanceID = 0; LastOuterHeight = LastTopHeadersRowHeight = LastFrozenHeight = 0.0f; HoveredRowLast = HoveredRowNext = -1; }
};
// sizeof() ~ 592 bytes + heap allocs described in TableBeginInitMemory()
struct IMGUI_API uiTable {
    uiID         ID;
    uiTableFlags Flags;
    void*        RawData;                     // Single allocation to hold Columns[], DisplayOrderToIndex[], and RowCellData[]
    uiTableTempData* TempData;                // Transient data while table is active. Point within g.CurrentTableStack[]
    ImSpan<uiTableColumn> Columns;            // Point within RawData[]
    ImSpan<uiTableColumnIdx> DisplayOrderToIndex; // Point within RawData[]. Store display order of columns (when not reordered, the values are 0...Count-1)
    ImSpan<uiTableCellData> RowCellData;      // Point within RawData[]. Store cells background requests for current row.
    ImBitArrayPtr EnabledMaskByDisplayOrder;  // Column DisplayOrder -> IsEnabled map
    ImBitArrayPtr EnabledMaskByIndex;         // Column Index -> IsEnabled map (== not hidden by user/api) in a format adequate for iterating column without touching cold data
    ImBitArrayPtr VisibleMaskByIndex;         // Column Index -> IsVisibleX|IsVisibleY map (== not hidden by user/api && not hidden by scrolling/cliprect)
    uiTableFlags  SettingsLoadedFlags;        // Which data were loaded from the .ini file (e.g. when order is not altered we won't save order)
    int   SettingsOffset;             // Offset in g.SettingsTables
    int   LastFrameActive;
    int   ColumnsCount;               // Number of columns declared in BeginTable()
    int   CurrentRow;
    int   CurrentColumn;
    ImS16 InstanceCurrent;            // Count of BeginTable() calls with same ID in the same frame (generally 0). This is a little bit similar to BeginCount for a window, but multiple tables with the same ID are multiple tables, they are just synced.
    ImS16 InstanceInteracted;         // Mark which instance (generally 0) of the same ID is being interacted with
    float RowPosY1;
    float RowPosY2;
    float RowMinHeight;               // Height submitted to TableNextRow()
    float RowCellPaddingY;            // Top and bottom padding. Reloaded during row change.
    float RowTextBaseline;
    float RowIndentOffsetX;
    uiTableRowFlags RowFlags : 16; // Current row flags, see uiTableRowFlags_
    uiTableRowFlags LastRowFlags : 16;
    int   RowBgColorCounter; // Counter for alternating background colors (can be fast-forwarded by e.g clipper), not same as CurrentRow because header rows typically don't increase this.
    ImU32 RowBgColor[2];     // Background color override for current row.
    ImU32 BorderColorStrong;
    ImU32 BorderColorLight;
    float BorderX1;
    float BorderX2;
    float HostIndentX;
    float MinColumnWidth;
    float OuterPaddingX;
    float CellPaddingX;               // Padding from each borders. Locked in BeginTable()/Layout.
    float CellSpacingX1;              // Spacing between non-bordered cells. Locked in BeginTable()/Layout.
    float CellSpacingX2;
    float InnerWidth;                 // User value passed to BeginTable(), see comments at the top of BeginTable() for details.
    float ColumnsGivenWidth;          // Sum of current column width
    float ColumnsAutoFitWidth;        // Sum of ideal column width in order nothing to be clipped, used for auto-fitting and content width submission in outer window
    float ColumnsStretchSumWeights;   // Sum of weight of all enabled stretching columns
    float ResizedColumnNextWidth;
    float ResizeLockMinContentsX2;    // Lock minimum contents width while resizing down in order to not create feedback loops. But we allow growing the table.
    float RefScale;                   // Reference scale to be able to rescale columns on font/dpi changes.
    float AngledHeadersHeight;        // Set by TableAngledHeadersRow(), used in TableUpdateLayout()
    float AngledHeadersSlope;         // Set by TableAngledHeadersRow(), used in TableUpdateLayout()
    ImRect OuterRect;                 // Note: for non-scrolling table, OuterRect.Max.y is often FLT_MAX until EndTable(), unless a height has been specified in BeginTable().
    ImRect InnerRect;                 // InnerRect but without decoration. As with OuterRect, for non-scrolling tables, InnerRect.Max.y is "
    ImRect WorkRect;
    ImRect InnerClipRect;
    ImRect BgClipRect;                // We use this to cpu-clip cell background color fill, evolve during the frame as we cross frozen rows boundaries
    ImRect Bg0ClipRectForDrawCmd;     // Actual ImDrawCmd clip rect for BG0/1 channel. This tends to be == OuterWindow->ClipRect at BeginTable() because output in BG0/BG1 is cpu-clipped
    ImRect Bg2ClipRectForDrawCmd;     // Actual ImDrawCmd clip rect for BG2 channel. This tends to be a correct, tight-fit, because output to BG2 are done by widgets relying on regular ClipRect.
    ImRect HostClipRect;              // This is used to check if we can eventually merge our columns draw calls into the current draw call of the current window.
    ImRect HostBackupInnerClipRect;   // Backup of InnerWindow->ClipRect during PushTableBackground()/PopTableBackground()
    uiWindow* OuterWindow;            // Parent window for the table
    uiWindow* InnerWindow;            // Window holding the table data (== OuterWindow or a child window)
    uiTextBuffer ColumnsNames;        // Contiguous buffer holding columns names
    ImDrawListSplitter* DrawSplitter; // Shortcut to TempData->DrawSplitter while in table. Isolate draw commands per columns to avoid switching clip rect constantly
    uiTableInstanceData InstanceDataFirst;
    ImVector<uiTableInstanceData> InstanceDataExtra; // FIXME-OPT: Using a small-vector pattern would be good.
    uiTableColumnSortSpecs SortSpecsSingle;
    ImVector<uiTableColumnSortSpecs> SortSpecsMulti; // FIXME-OPT: Using a small-vector pattern would be good.
    uiTableSortSpecs SortSpecs;                  // Public facing sorts specs, this is what we return in TableGetSortSpecs()
    uiTableColumnIdx SortSpecsCount;
    uiTableColumnIdx ColumnsEnabledCount;        // Number of enabled columns (<= ColumnsCount)
    uiTableColumnIdx ColumnsEnabledFixedCount;   // Number of enabled columns using fixed width (<= ColumnsCount)
    uiTableColumnIdx DeclColumnsCount;           // Count calls to TableSetupColumn()
    uiTableColumnIdx AngledHeadersCount;         // Count columns with angled headers
    uiTableColumnIdx HoveredColumnBody;          // Index of column whose visible region is being hovered. Important: == ColumnsCount when hovering empty region after the right-most column!
    uiTableColumnIdx HoveredColumnBorder;        // Index of column whose right-border is being hovered (for resizing).
    uiTableColumnIdx HighlightColumnHeader;      // Index of column which should be highlighted.
    uiTableColumnIdx AutoFitSingleColumn;        // Index of single column requesting auto-fit.
    uiTableColumnIdx ResizedColumn;              // Index of column being resized. Reset when InstanceCurrent==0.
    uiTableColumnIdx LastResizedColumn;          // Index of column being resized from previous frame.
    uiTableColumnIdx HeldHeaderColumn;           // Index of column header being held.
    uiTableColumnIdx LastHeldHeaderColumn;       // Index of column header being held from previous frame.
    uiTableColumnIdx ReorderColumn;              // Index of column being reordered. (not cleared)
    uiTableColumnIdx ReorderColumnDstOrder;      // Requested display order of column being reordered.
    uiTableColumnIdx LeftMostEnabledColumn;      // Index of left-most non-hidden column.
    uiTableColumnIdx RightMostEnabledColumn;     // Index of right-most non-hidden column.
    uiTableColumnIdx LeftMostStretchedColumn;    // Index of left-most stretched column.
    uiTableColumnIdx RightMostStretchedColumn;   // Index of right-most stretched column.
    uiTableColumnIdx ContextPopupColumn;         // Column right-clicked on, of -1 if opening context menu from a neutral/empty spot
    uiTableColumnIdx FreezeRowsRequest;          // Requested frozen rows count
    uiTableColumnIdx FreezeRowsCount;            // Actual frozen row count (== FreezeRowsRequest, or == 0 when no scrolling offset)
    uiTableColumnIdx FreezeColumnsRequest;       // Requested frozen columns count
    uiTableColumnIdx FreezeColumnsCount;         // Actual frozen columns count (== FreezeColumnsRequest, or == 0 when no scrolling offset)
    uiTableColumnIdx RowCellDataCurrent;         // Index of current RowCellData[] entry in current row
    uiTableDrawChannelIdx DummyDrawChannel;      // Redirect non-visible columns here.
    uiTableDrawChannelIdx Bg2DrawChannelCurrent; // For Selectable() and other widgets drawing across columns after the freezing line. Index within DrawSplitter.Channels[]
    uiTableDrawChannelIdx Bg2DrawChannelUnfrozen;
    ImS8 NavLayer;                  // uiNavLayer at the time of BeginTable().
    bool IsLayoutLocked;            // Set by TableUpdateLayout() which is called when beginning the first row.
    bool IsInsideRow;               // Set when inside TableBeginRow()/TableEndRow().
    bool IsInitializing;
    bool IsSortSpecsDirty;
    bool IsUsingHeaders;            // Set when the first row had the uiTableRowFlags_Headers flag.
    bool IsContextPopupOpen;        // Set when default context menu is open (also see: ContextPopupColumn, InstanceInteracted).
    bool DisableDefaultContextMenu; // Disable default context menu. You may submit your own using TableBeginContextMenuPopup()/EndPopup()
    bool IsSettingsRequestLoad;
    bool IsSettingsDirty;           // Set when table settings have changed and needs to be reported into uiTableSettings data.
    bool IsDefaultDisplayOrder;     // Set when display order is unchanged from default (DisplayOrder contains 0...Count-1)
    bool IsResetAllRequest;
    bool IsResetDisplayOrderRequest;
    bool IsUnfrozenRows;            // Set when we got past the frozen row.
    bool IsDefaultSizingPolicy;     // Set if user didn't explicitly set a sizing policy in BeginTable()
    bool IsActiveIdAliveBeforeTable;
    bool IsActiveIdInTable;
    bool HasScrollbarYCurr;         // Whether ANY instance of this table had a vertical scrollbar during the current frame.
    bool HasScrollbarYPrev;         // Whether ANY instance of this table had a vertical scrollbar during the previous.
    bool MemoryCompacted;
    bool HostSkipItems;             // Backup of InnerWindow->SkipItem at the end of BeginTable(), because we will overwrite InnerWindow->SkipItem on a per-column basis
    uiTable() { memset((void*)this, 0, sizeof(*this)); LastFrameActive = -1; }
    ~uiTable() { IM_FREE(RawData); }
};
// Transient data that are only needed between BeginTable() and EndTable(), those buffers are shared (1 per level of stacked table).
// - Accessing those requires chasing an extra pointer so for very frequently used data we leave them in the main table structure.
// - We also leave out of this structure data that tend to be particularly useful for debugging/metrics.
// FIXME-TABLE: more transient data could be stored in a stacked uiTableTempData: e.g. SortSpecs.
// sizeof() ~ 136 bytes.
struct IMGUI_API uiTableTempData {
    uiID  WindowID;                    // Shortcut to g.Tables[TableIndex]->OuterWindow->ID.
    int   TableIndex;                  // Index in g.Tables.Buf[] pool
    float LastTimeActive;              // Last timestamp this structure was used
    float AngledHeadersExtraWidth;     // Used in EndTable()
    ImVector<uiTableHeaderData> AngledHeadersRequests;   // Used in TableAngledHeadersRow()
    vec2   UserOuterSize;              // outer_size.x passed to BeginTable()
    ImDrawListSplitter DrawSplitter;
    ImRect HostBackupWorkRect;         // Backup of InnerWindow->WorkRect at the end of BeginTable()
    ImRect HostBackupParentWorkRect;   // Backup of InnerWindow->ParentWorkRect at the end of BeginTable()
    vec2   HostBackupPrevLineSize;     // Backup of InnerWindow->DC.PrevLineSize at the end of BeginTable()
    vec2   HostBackupCurrLineSize;     // Backup of InnerWindow->DC.CurrLineSize at the end of BeginTable()
    vec2   HostBackupCursorMaxPos;     // Backup of InnerWindow->DC.CursorMaxPos at the end of BeginTable()
    vec1   HostBackupColumnsOffset;    // Backup of OuterWindow->DC.ColumnsOffset at the end of BeginTable()
    float  HostBackupItemWidth;        // Backup of OuterWindow->DC.ItemWidth at the end of BeginTable()
    int    HostBackupItemWidthStackSize;//Backup of OuterWindow->DC.ItemWidthStack.Size at the end of BeginTable()
    uiTableTempData() { memset((void*)this, 0, sizeof(*this)); LastTimeActive = -1.0f; }
};
// sizeof() ~ 16
struct uiTableColumnSettings {
    float            WidthOrWeight;
    uiID             UserID;
    uiTableColumnIdx Index;
    uiTableColumnIdx DisplayOrder;
    uiTableColumnIdx SortOrder;
    ImU8             SortDirection : 2;
    ImS8             IsEnabled : 2; // "Visible" in ini file
    ImU8             IsStretch : 1;
    uiTableColumnSettings() {
        WidthOrWeight = 0.0f;
        UserID = 0;
        Index = -1;
        DisplayOrder = SortOrder = -1;
        SortDirection = Var::SortDir::Hold;
        IsEnabled = -1;
        IsStretch = 0;
    }
};
// This is designed to be stored in a single ImChunkStream (1 header followed by N uiTableColumnSettings, etc.)
struct uiTableSettings {
    uiID             ID;              // Set to 0 to invalidate/delete the setting
    uiTableFlags     SaveFlags;       // Indicate data we want to save using the Resizable/Reorderable/Sortable/Hideable flags (could be using its own flags..)
    float            RefScale;        // Reference scale to be able to rescale columns on font/dpi changes.
    uiTableColumnIdx ColumnsCount;
    uiTableColumnIdx ColumnsCountMax; // Maximum number of columns this settings instance can store, we can recycle a settings instance with lower number of columns but not higher
    bool             WantApply;       // Set when loaded from .ini data (to enable merging/loading .ini data into an already running context)
    uiTableSettings() { memset((void*)this, 0, sizeof(*this)); }
    uiTableColumnSettings* GetColumnSettings() { return (uiTableColumnSettings*)(this + 1); }
};
//-----------------------------------------------------------------------------
// [SECTION] ImGui internal API
// No guarantee of forward compatibility here!
//-----------------------------------------------------------------------------
namespace UI {
    // Windows
    // We should always have a CurrentWindow in the stack (there is an implicit "Debug" window)
    // If this ever crashes because g.CurrentWindow is NULL, it means that either:
    // - UI::NewFrame() has never been called, which is illegal.
    // - You are calling ImGui functions after UI::EndFrame()/UI::Render() and before the next UI::NewFrame(), which is also illegal.
    IMGUI_API uiIO& GetIO(uiContext* ctx);
    IMGUI_API uiPlatformIO& GetPlatformIO(uiContext* ctx);
    inline float GetScale() { uiContext& g = *GImGui; return g.Style._MainScale; } // FIXME-DPI: I don't want to formalize this just yet. Because reasons. Please don't use.
    inline uiWindow* GetCurrentWindowRead() { uiContext& g = *GImGui; return g.CurrentWindow; }
    inline uiWindow* GetCurrentWindow()     { uiContext& g = *GImGui; g.CurrentWindow->WriteAccessed = true; return g.CurrentWindow; }
    IMGUI_API uiWindow* FindWindowByID(uiID id);
    IMGUI_API uiWindow* FindWindowByName(const char* name);
    IMGUI_API void UpdateWindowParentAndRootLinks(uiWindow* window, uiWindowFlags flags, uiWindow* parent_window);
    IMGUI_API void UpdateWindowSkipRefresh(uiWindow* window);
    IMGUI_API vec2 CalcWindowNextAutoFitSize(uiWindow* window);
    IMGUI_API bool IsWindowChildOf(uiWindow* window, uiWindow* potential_parent, bool popup_hierarchy, bool dock_hierarchy);
    IMGUI_API bool IsWindowInBeginStack(uiWindow* window);
    IMGUI_API bool IsWindowWithinBeginStackOf(uiWindow* window, uiWindow* potential_parent);
    IMGUI_API bool IsWindowAbove(uiWindow* potential_above, uiWindow* potential_below);
    IMGUI_API bool IsWindowNavFocusable(uiWindow* window);
    IMGUI_API void SetWindowPos(uiWindow* window, const vec2& pos, uiCond cond = 0);
    IMGUI_API void SetWindowSize(uiWindow* window, const vec2& size, uiCond cond = 0);
    IMGUI_API void SetWindowCollapsed(uiWindow* window, bool collapsed, uiCond cond = 0);
    IMGUI_API void SetWindowHitTestHole(uiWindow* window, const vec2& pos, const vec2& size);
    IMGUI_API void SetWindowHiddenAndSkipItemsForCurrentFrame(uiWindow* window);
    inline void    SetWindowParentWindowForFocusRoute(uiWindow* window, uiWindow* parent_window) { window->ParentWindowForFocusRoute = parent_window; } // You may also use SetNextWindowClass()'s FocusRouteParentWindowId field.
    inline ImRect  WindowRectAbsToRel(uiWindow* window, const ImRect& r) { vec2 off = window->DC.CursorStartPos; return ImRect(r.Min.x - off.x, r.Min.y - off.y, r.Max.x - off.x, r.Max.y - off.y); }
    inline ImRect  WindowRectRelToAbs(uiWindow* window, const ImRect& r) { vec2 off = window->DC.CursorStartPos; return ImRect(r.Min.x + off.x, r.Min.y + off.y, r.Max.x + off.x, r.Max.y + off.y); }
    inline vec2    WindowPosAbsToRel(uiWindow* window, const vec2& p)  { vec2 off = window->DC.CursorStartPos; return vec2(p.x - off.x, p.y - off.y); }
    inline vec2    WindowPosRelToAbs(uiWindow* window, const vec2& p)  { vec2 off = window->DC.CursorStartPos; return vec2(p.x + off.x, p.y + off.y); }
    // Windows: Display Order and Focus Order
    IMGUI_API void FocusWindow(uiWindow* window, uiFocusRequestFlags flags = 0);
    IMGUI_API void FocusTopMostWindowUnderOne(uiWindow* under_this_window, uiWindow* ignore_window, uiViewport* filter_viewport, uiFocusRequestFlags flags);
    IMGUI_API void BringWindowToFocusFront(uiWindow* window);
    IMGUI_API void BringWindowToDisplayFront(uiWindow* window);
    IMGUI_API void BringWindowToDisplayBack(uiWindow* window);
    IMGUI_API void BringWindowToDisplayBehind(uiWindow* window, uiWindow* above_window);
    IMGUI_API int  FindWindowDisplayIndex(uiWindow* window);
    IMGUI_API uiWindow* FindBottomMostVisibleWindowWithinBeginStack(uiWindow* window);
    // Windows: Idle, Refresh Policies [EXPERIMENTAL]
    IMGUI_API void SetNextWindowRefreshPolicy(uiWindowRefreshFlags flags);
    // Fonts, drawing
    IMGUI_API void RegisterUserTexture(ImTextureData* tex); // Register external texture. EXPERIMENTAL.
    IMGUI_API void UnregisterUserTexture(ImTextureData* tex);
    IMGUI_API void RegisterFontAtlas(ImFontAtlas* atlas);
    IMGUI_API void UnregisterFontAtlas(ImFontAtlas* atlas);
    IMGUI_API void SetCurrentFont(ImFont* font, float font_size_before_scaling, float font_size_after_scaling);
    IMGUI_API void UpdateCurrentFontSize(float restore_font_size_after_scaling);
    IMGUI_API void SetFontRasterizerDensity(float rasterizer_density);
    inline float   GetFontRasterizerDensity() { return GImGui->FontRasterizerDensity; }
    inline float   GetRoundedFontSize(float size) { return IM_ROUND(size); }
    IMGUI_API ImFont* GetDefaultFont();
    IMGUI_API void    PushPasswordFont();
    IMGUI_API void    PopPasswordFont();
    inline ImDrawList* GetForegroundDrawList(uiWindow* window) { return GetForegroundDrawList(window->Viewport); }
    IMGUI_API void    AddDrawListToDrawDataEx(ImDrawData* draw_data, ImVector<ImDrawList*>* out_list, ImDrawList* draw_list);
    // Init
    IMGUI_API void Initialize();
    IMGUI_API void Shutdown(); // Since 1.60 this is a _private_ function. You can call DestroyContext() to destroy the context created by CreateContext().
    // Context name & generic context hooks
    IMGUI_API void SetContextName(uiContext* ctx, const char* name);
    IMGUI_API uiID AddContextHook(uiContext* ctx, const uiContextHook* hook);
    IMGUI_API void RemoveContextHook(uiContext* ctx, uiID hook_to_remove);
    IMGUI_API void CallContextHooks(uiContext* ctx, uiContextHookType type);
    // NewFrame
    IMGUI_API void UpdateInputEvents(bool trickle_fast_inputs);
    IMGUI_API void UpdateHoveredWindowAndCaptureFlags(const vec2& mouse_pos);
    IMGUI_API void FindHoveredWindowEx(const vec2& pos, bool find_first_and_in_any_viewport, uiWindow** out_hovered_window, uiWindow** out_hovered_window_under_moving_window);
    IMGUI_API void StartMouseMovingWindow(uiWindow* window);
    IMGUI_API void StartMouseMovingWindowOrNode(uiWindow* window, uiDockNode* node, bool undock);
    IMGUI_API void StopMouseMovingWindow();
    IMGUI_API void UpdateMouseMovingWindowNewFrame();
    IMGUI_API void UpdateMouseMovingWindowEndFrame();
    // Viewports
    IMGUI_API void TranslateWindowsInViewport(uiViewportP* viewport, const vec2& old_pos, const vec2& new_pos, const vec2& old_size, const vec2& new_size);
    IMGUI_API void ScaleWindowsInViewport(uiViewportP* viewport, float scale);
    IMGUI_API void DestroyPlatformWindow(uiViewportP* viewport);
    IMGUI_API void SetWindowViewport(uiWindow* window, uiViewportP* viewport);
    IMGUI_API void SetCurrentViewport(uiWindow* window, uiViewportP* viewport);
    IMGUI_API const uiPlatformMonitor* GetViewportPlatformMonitor(uiViewport* viewport);
    IMGUI_API uiViewportP* FindHoveredViewportFromPlatformWindowStack(const vec2& mouse_platform_pos);
    // Settings
    IMGUI_API void MarkIniSettingsDirty();
    IMGUI_API void MarkIniSettingsDirty(uiWindow* window);
    IMGUI_API void ClearIniSettings();
    IMGUI_API void AddSettingsHandler(const uiSettingsHandler* handler);
    IMGUI_API void RemoveSettingsHandler(const char* type_name);
    IMGUI_API uiSettingsHandler* FindSettingsHandler(const char* type_name);
    // Settings - Windows
    IMGUI_API uiWindowSettings* CreateNewWindowSettings(const char* name);
    IMGUI_API uiWindowSettings* FindWindowSettingsByID(uiID id);
    IMGUI_API uiWindowSettings* FindWindowSettingsByWindow(uiWindow* window);
    IMGUI_API void              ClearWindowSettings(const char* name);
    // Localization
    IMGUI_API void     LocalizeRegisterEntries(const uiLocEntry* entries, int count);
    inline const char* LocalizeGetMsg(uiLocKey key) { uiContext& g = *GImGui; const char* msg = g.LocalizationTable[key]; return msg ? msg : "*Missing Text*"; }
    // Scrolling
    IMGUI_API void SetScrollX(uiWindow* window, float scroll_x);
    IMGUI_API void SetScrollY(uiWindow* window, float scroll_y);
    IMGUI_API void SetScrollFromPosX(uiWindow* window, float local_x, float center_x_ratio);
    IMGUI_API void SetScrollFromPosY(uiWindow* window, float local_y, float center_y_ratio);
    // Early work-in-progress API (ScrollToItem() will become public)
    IMGUI_API void ScrollToItem(uiScrollFlags flags = 0);
    IMGUI_API void ScrollToRect(uiWindow* window, const ImRect& rect, uiScrollFlags flags = 0);
    IMGUI_API vec2 ScrollToRectEx(uiWindow* window, const ImRect& rect, uiScrollFlags flags = 0);
    inline void ScrollToBringRectIntoView(uiWindow* window, const ImRect& rect) { ScrollToRect(window, rect, uiScrollFlags_KeepVisibleEdgeY); }
    // Basic Accessors
    inline uiItemStatusFlags GetItemStatusFlags() { uiContext& g = *GImGui; return g.LastItemData.StatusFlags; }
    inline uiID GetActiveID() { uiContext& g = *GImGui; return g.ActiveId; }
    inline uiID GetFocusID()  { uiContext& g = *GImGui; return g.NavId; }
    IMGUI_API void SetActiveID(uiID id, uiWindow* window);
    IMGUI_API void SetFocusID(uiID id, uiWindow* window);
    IMGUI_API void ClearActiveID();
    IMGUI_API uiID GetHoveredID();
    IMGUI_API void SetHoveredID(uiID id);
    IMGUI_API void KeepAliveID(uiID id);
    IMGUI_API void MarkItemEdited(uiID id); // Mark data associated to given item as "edited", used by IsItemDeactivatedAfterEdit() function.
    IMGUI_API void PushOverrideID(uiID id); // Push given value as-is at the top of the ID stack (whereas PushID combines old and new hashes)
    IMGUI_API uiID GetIDWithSeed(const char* str_id_begin, const char* str_id_end, uiID seed);
    IMGUI_API uiID GetIDWithSeed(int n, uiID seed);
    // Basic Helpers for widget code
    IMGUI_API void ItemSize(const vec2& size, float text_baseline_y = -1.0f);
    inline    void ItemSize(const ImRect& bb, float text_baseline_y = -1.0f) { ItemSize(bb.GetSize(), text_baseline_y); } // FIXME: This is a misleading API since we expect CursorPos to be bb.Min.
    IMGUI_API bool ItemAdd(const ImRect& bb, uiID id, const ImRect* nav_bb = NULL, uiItemFlags extra_flags = 0);
    IMGUI_API bool ItemHoverable(const ImRect& bb, uiID id, uiItemFlags item_flags);
    IMGUI_API bool IsWindowContentHoverable(uiWindow* window, uiHoverFlags flags = 0);
    IMGUI_API bool IsClippedEx(const ImRect& bb, uiID id);
    IMGUI_API void SetLastItemData(uiID item_id, uiItemFlags item_flags, uiItemStatusFlags status_flags, const ImRect& item_rect);
    IMGUI_API vec2 CalcItemSize(vec2 size, float default_w, float default_h);
    IMGUI_API float CalcWrapWidthForPos(const vec2& pos, float wrap_pos_x);
    IMGUI_API void PushMultiItemsWidths(int components, float width_full);
    IMGUI_API void ShrinkWidths(uiShrinkWidthItem* items, int count, float width_excess, float width_min);
    IMGUI_API void CalcClipRectVisibleItemsY(const ImRect& clip_rect, const vec2& pos, float items_height, int* out_visible_start, int* out_visible_end);
    // Parameter stacks (shared)
    IMGUI_API const uiStyleVarInfo* GetStyleVarInfo(uiStyleVar idx);
    IMGUI_API void BeginDisabledOverrideReenable();
    IMGUI_API void EndDisabledOverrideReenable();
    // Logging/Capture
    IMGUI_API void LogBegin(uiLogFlags flags, int auto_open_depth); // -> BeginCapture() when we design v2 api, for now stay under the radar by using the old name.
    IMGUI_API void LogToBuffer(int auto_open_depth = -1);           // Start logging/capturing to internal buffer
    IMGUI_API void LogRenderedText(const vec2* ref_pos, const char* text, const char* text_end = NULL);
    IMGUI_API void LogSetNextTextDecoration(const char* prefix, const char* suffix);
    // Childs
    IMGUI_API bool      BeginChildEx(const char* name, uiID id, const vec2& size_arg, uiChildFlags child_flags, uiWindowFlags window_flags);
    IMGUI_API uiWindow* FindFrontMostVisibleChildWindow(uiWindow* window);
    // Popups, Modals
    IMGUI_API bool      BeginPopupEx(uiID id, uiWindowFlags extra_window_flags);
    IMGUI_API bool      BeginPopupMenuEx(uiID id, const char* label, uiWindowFlags extra_window_flags);
    IMGUI_API void      OpenPopupEx(uiID id, uiPopupFlags popup_flags = uiPopupFlags_None);
    IMGUI_API void      ClosePopupToLevel(int remaining, bool restore_focus_to_window_under_popup);
    IMGUI_API void      ClosePopupsOverWindow(uiWindow* ref_window, bool restore_focus_to_window_under_popup);
    IMGUI_API void      ClosePopupsExceptModals();
    IMGUI_API bool      IsPopupOpen(uiID id, uiPopupFlags popup_flags);
    IMGUI_API ImRect    GetPopupAllowedExtentRect(uiWindow* window);
    IMGUI_API uiWindow* GetTopMostPopupModal();
    IMGUI_API uiWindow* GetTopMostAndVisiblePopupModal();
    IMGUI_API uiWindow* FindBlockingModal(uiWindow* window);
    IMGUI_API vec2      FindBestWindowPosForPopup(uiWindow* window);
    IMGUI_API vec2      FindBestWindowPosForPopupEx(const vec2& ref_pos, const vec2& size, Var::Dir* last_dir, const ImRect& r_outer, const ImRect& r_avoid, uiPopupPositionPolicy policy);
    IMGUI_API uiMouseButton GetMouseButtonFromPopupFlags(uiPopupFlags flags);
    IMGUI_API bool      IsPopupOpenRequestForItem(uiPopupFlags flags, uiID id);
    IMGUI_API bool      IsPopupOpenRequestForWindow(uiPopupFlags flags);
    // Tooltips
    IMGUI_API bool BeginTooltipEx(uiTooltipFlags tooltip_flags, uiWindowFlags extra_window_flags);
    IMGUI_API bool BeginTooltipHidden();
    // Menus
    IMGUI_API bool BeginViewportSideBar(const char* name, uiViewport* viewport, Var::Dir dir, float size, uiWindowFlags window_flags);
    IMGUI_API bool BeginMenuEx(const char* label, const char* icon, bool enabled = true);
    IMGUI_API bool MenuItemEx(const char* label, const char* icon, const char* shortcut = NULL, bool selected = false, bool enabled = true);
    // Combos
    IMGUI_API bool BeginComboPopup(uiID popup_id, const ImRect& bb, uiComboFlags flags);
    IMGUI_API bool BeginComboPreview();
    IMGUI_API void EndComboPreview();
    // Keyboard/Gamepad Navigation
    IMGUI_API void NavInitWindow(uiWindow* window, bool force_reinit);
    IMGUI_API void NavInitRequestApplyResult();
    IMGUI_API bool NavMoveRequestButNoResultYet();
    IMGUI_API void NavMoveRequestSubmit(Var::Dir move_dir, Var::Dir clip_dir, uiNavMoveFlags move_flags, uiScrollFlags scroll_flags);
    IMGUI_API void NavMoveRequestForward(Var::Dir move_dir, Var::Dir clip_dir, uiNavMoveFlags move_flags, uiScrollFlags scroll_flags);
    IMGUI_API void NavMoveRequestResolveWithLastItem(uiNavItemData* result);
    IMGUI_API void NavMoveRequestResolveWithPastTreeNode(uiNavItemData* result, const uiTreeNodeStackData* tree_node_data);
    IMGUI_API void NavMoveRequestCancel();
    IMGUI_API void NavMoveRequestApplyResult();
    IMGUI_API void NavMoveRequestTryWrapping(uiWindow* window, uiNavMoveFlags move_flags);
    IMGUI_API void NavHighlightActivated(uiID id);
    IMGUI_API void NavClearPreferredPosForAxis(uiAxis axis);
    IMGUI_API void SetNavCursorVisibleAfterMove();
    IMGUI_API void NavUpdateCurrentWindowIsScrollPushableX();
    IMGUI_API void SetNavWindow(uiWindow* window);
    IMGUI_API void SetNavID(uiID id, uiNavLayer nav_layer, uiID focus_scope_id, const ImRect& rect_rel);
    IMGUI_API void SetNavFocusScope(uiID focus_scope_id);
    // Focus/Activation
    // This should be part of a larger set of API: FocusItem(offset = -1), FocusItemByID(id), ActivateItem(offset = -1), ActivateItemByID(id) etc. which are
    // much harder to design and implement than expected. I have a couple of private branches on this matter but it's not simple. For now implementing the easy ones.
    IMGUI_API void FocusItem();               // Focus last item (no selection/activation).
    IMGUI_API void ActivateItemByID(uiID id); // Activate an item by ID (button, checkbox, tree node etc.). Activation is queued and processed on the next frame when the item is encountered again. Was called 'ActivateItem()' before 1.89.7.
    // Inputs
    // FIXME: Eventually we should aim to move e.g. IsActiveIdUsingKey() into IsKeyXXX functions.
    inline bool IsNamedKey(uiKey key)      { return key >= uiKey_NamedKey_BEGIN && key < uiKey_NamedKey_END; }
    inline bool IsNamedKeyOrMod(uiKey key) { return (key >= uiKey_NamedKey_BEGIN && key < uiKey_NamedKey_END) || key == uiMod_Ctrl || key == uiMod_Shift || key == uiMod_Alt || key == uiMod_Super; }
    inline bool IsLegacyKey(uiKey key)     { return key >= uiKey_LegacyNativeKey_BEGIN && key < uiKey_LegacyNativeKey_END; }
    inline bool IsKeyboardKey(uiKey key)   { return key >= uiKey_Keyboard_BEGIN && key < uiKey_Keyboard_END; }
    inline bool IsGamepadKey(uiKey key)    { return key >= uiKey_Gamepad_BEGIN && key < uiKey_Gamepad_END; }
    inline bool IsMouseKey(uiKey key)      { return key >= uiKey_Mouse_BEGIN && key < uiKey_Mouse_END; }
    inline bool IsAliasKey(uiKey key)      { return key >= uiKey_Aliases_BEGIN && key < uiKey_Aliases_END; }
    inline bool IsLRModKey(uiKey key)      { return key >= uiKey_LeftCtrl && key <= uiKey_RightSuper; }
    uiKeyChord  FixupKeyChord(uiKeyChord key_chord);
    inline uiKey ConvertSingleModFlagToKey(uiKey key) {
        if (key == uiMod_Ctrl) return uiKey_ReservedForModCtrl;
        if (key == uiMod_Shift) return uiKey_ReservedForModShift;
        if (key == uiMod_Alt) return uiKey_ReservedForModAlt;
        if (key == uiMod_Super) return uiKey_ReservedForModSuper;
        return key;
    }
    IMGUI_API uiKeyData*  GetKeyData(uiContext* ctx, uiKey key);
    inline uiKeyData*     GetKeyData(uiKey key)                                    { uiContext& g = *GImGui; return GetKeyData(&g, key); }
    IMGUI_API const char* GetKeyChordName(uiKeyChord key_chord);
    inline uiKey    MouseButtonToKey(uiMouseButton button)                   { IM_ASSERT(button >= 0 && button < uiMouseButton_COUNT); return (uiKey)(uiKey_MouseLeft + button); }
    IMGUI_API bool  IsMouseDragPastThreshold(uiMouseButton button, float lock_threshold = -1.0f);
    IMGUI_API vec2  GetKeyMagnitude2d(uiKey key_left, uiKey key_right, uiKey key_up, uiKey key_down);
    IMGUI_API float GetNavTweakPressedAmount(uiAxis axis);
    IMGUI_API int   CalcTypematicRepeatAmount(float t0, float t1, float repeat_delay, float repeat_rate);
    IMGUI_API void  GetTypematicRepeatRate(uiInputFlags flags, float* repeat_delay, float* repeat_rate);
    IMGUI_API void  TeleportMousePos(const vec2& pos);
    IMGUI_API void  SetActiveIdUsingAllKeyboardKeys();
    inline bool     IsActiveIdUsingNavDir(Var::Dir dir) { uiContext& g = *GImGui; return (g.ActiveIdUsingNavDirMask & (1 << dir)) != 0; }
    // [EXPERIMENTAL] Low-Level: Key/Input Ownership
    // - The idea is that instead of "eating" a given input, we can link to an owner id.
    // - Ownership is most often claimed as a result of reacting to a press/down event (but occasionally may be claimed ahead).
    // - Input queries can then read input by specifying uiKeyOwner_Any (== 0), uiKeyOwner_NoOwner (== -1) or a custom ID.
    // - Legacy input queries (without specifying an owner or _Any or _None) are equivalent to using uiKeyOwner_Any (== 0).
    // - Input ownership is automatically released on the frame after a key is released. Therefore:
    //   - for ownership registration happening as a result of a down/press event, the SetKeyOwner() call may be done once (common case).
    //   - for ownership registration happening ahead of a down/press event, the SetKeyOwner() call needs to be made every frame (happens if e.g. claiming ownership on hover).
    // - SetItemKeyOwner() is a shortcut for common simple case. A custom widget will probably want to call SetKeyOwner() multiple times directly based on its interaction state.
    // - This is marked experimental because not all widgets are fully honoring the Set/Test idioms. We will need to move forward step by step.
    //   Please open a GitHub Issue to submit your usage scenario or if there's a use case you need solved.
    IMGUI_API uiID GetKeyOwner(uiKey key);
    IMGUI_API void SetKeyOwner(uiKey key, uiID owner_id, uiInputFlags flags = 0);
    IMGUI_API void SetKeyOwnersForKeyChord(uiKeyChord key, uiID owner_id, uiInputFlags flags = 0);
    IMGUI_API bool SetItemKeyOwner(uiKey key, uiInputFlags flags);
    IMGUI_API bool TestKeyOwner(uiKey key, uiID owner_id); // Test that key is either not owned, either owned by 'owner_id'
    inline uiKeyOwnerData* GetKeyOwnerData(uiContext* ctx, uiKey key) { if (key & uiMod_Mask_) key = ConvertSingleModFlagToKey(key); IM_ASSERT(IsNamedKey(key)); return &ctx->KeysOwnerData[key - uiKey_NamedKey_BEGIN]; }
    // [EXPERIMENTAL] High-Level: Input Access functions w/ support for Key/Input Ownership
    // - Important: legacy IsKeyPressed(uiKey, bool repeat=true) _DEFAULTS_ to repeat, new IsKeyPressed() requires _EXPLICIT_ uiInputFlags_Repeat flag.
    // - Expected to be later promoted to public API, the prototypes are designed to replace existing ones (since owner_id can default to Any == 0)
    // - Specifying a value for 'uiID owner' will test that EITHER the key is NOT owned (UNLESS locked), EITHER the key is owned by 'owner'.
    //   Legacy functions use uiKeyOwner_Any meaning that they typically ignore ownership, unless a call to SetKeyOwner() explicitly used uiInputFlags_LockThisFrame or uiInputFlags_LockUntilRelease.
    // - Binding generators may want to ignore those for now, or suffix them with Ex() until we decide if this gets moved into public API.
    IMGUI_API bool IsKeyDown(uiKey key, uiID owner_id);
    IMGUI_API bool IsKeyPressed(uiKey key, uiInputFlags flags, uiID owner_id = 0); // Important: when transitioning from old to new IsKeyPressed(): old API has "bool repeat = true", so would default to repeat. New API requires explicit uiInputFlags_Repeat.
    IMGUI_API bool IsKeyReleased(uiKey key, uiID owner_id);
    IMGUI_API bool IsKeyChordPressed(uiKeyChord key_chord, uiInputFlags flags, uiID owner_id = 0);
    IMGUI_API bool IsMouseDown(uiMouseButton button, uiID owner_id);
    IMGUI_API bool IsMouseClicked(uiMouseButton button, uiInputFlags flags, uiID owner_id = 0);
    IMGUI_API bool IsMouseReleased(uiMouseButton button, uiID owner_id);
    IMGUI_API bool IsMouseDoubleClicked(uiMouseButton button, uiID owner_id);
    // Shortcut Testing & Routing
    // - Set Shortcut() and SetNextItemShortcut() in imgui.h
    // - When a policy (except for uiInputFlags_RouteAlways *) is set, Shortcut() will register itself with SetShortcutRouting(),
    //   allowing the system to decide where to route the input among other route-aware calls.
    //   (* using uiInputFlags_RouteAlways is roughly equivalent to calling IsKeyChordPressed(key) and bypassing route registration and check)
    // - When using one of the routing option:
    //   - The default route is uiInputFlags_RouteFocused (accept inputs if window is in focus stack. Deep-most focused window takes inputs. ActiveId takes inputs over deep-most focused window.)
    //   - Routes are requested given a chord (key + modifiers) and a routing policy.
    //   - Routes are resolved during NewFrame(): if keyboard modifiers are matching current ones: SetKeyOwner() is called + route is granted for the frame.
    //   - Each route may be granted to a single owner. When multiple requests are made we have policies to select the winning route (e.g. deep most window).
    //   - Multiple read sites may use the same owner id can all access the granted route.
    //   - When owner_id is 0 we use the current Focus Scope ID as a owner ID in order to identify our location.
    // - You can chain two unrelated windows in the focus stack using SetWindowParentWindowForFocusRoute()
    //   e.g. if you have a tool window associated to a document, and you want document shortcuts to run when the tool is focused.
    IMGUI_API bool Shortcut(uiKeyChord key_chord, uiInputFlags flags, uiID owner_id);
    IMGUI_API bool SetShortcutRouting(uiKeyChord key_chord, uiInputFlags flags, uiID owner_id); // owner_id needs to be explicit and cannot be 0
    IMGUI_API bool TestShortcutRouting(uiKeyChord key_chord, uiID owner_id);
    IMGUI_API uiKeyRoutingData* GetShortcutRoutingData(uiKeyChord key_chord);
    // Docking
    // (some functions are only declared in imgui.cpp, see Docking section)
    IMGUI_API void DockContextInitialize(uiContext* ctx);
    IMGUI_API void DockContextShutdown(uiContext* ctx);
    IMGUI_API void DockContextClearNodes(uiContext* ctx, uiID root_id, bool clear_settings_refs); // Use root_id==0 to clear all
    IMGUI_API void DockContextRebuildNodes(uiContext* ctx);
    IMGUI_API void DockContextNewFrameUpdateUndocking(uiContext* ctx);
    IMGUI_API void DockContextNewFrameUpdateDocking(uiContext* ctx);
    IMGUI_API void DockContextEndFrame(uiContext* ctx);
    IMGUI_API uiID DockContextGenNodeID(uiContext* ctx);
    IMGUI_API void DockContextQueueDock(uiContext* ctx, uiWindow* target, uiDockNode* target_node, uiWindow* payload, Var::Dir split_dir, float split_ratio, bool split_outer);
    IMGUI_API void DockContextQueueUndockWindow(uiContext* ctx, uiWindow* window);
    IMGUI_API void DockContextQueueUndockNode(uiContext* ctx, uiDockNode* node);
    IMGUI_API void DockContextProcessUndockWindow(uiContext* ctx, uiWindow* window, bool clear_persistent_docking_ref = true);
    IMGUI_API void DockContextProcessUndockNode(uiContext* ctx, uiDockNode* node);
    IMGUI_API bool DockContextCalcDropPosForDocking(uiWindow* target, uiDockNode* target_node, uiWindow* payload_window, uiDockNode* payload_node, Var::Dir split_dir, bool split_outer, vec2* out_pos);
    IMGUI_API uiDockNode* DockContextFindNodeByID(uiContext* ctx, uiID id);
    IMGUI_API void DockNodeWindowMenuHandler_Default(uiContext* ctx, uiDockNode* node, uiTabBar* tab_bar);
    IMGUI_API bool DockNodeBeginAmendTabBar(uiDockNode* node);
    IMGUI_API void DockNodeEndAmendTabBar();
    inline uiDockNode* DockNodeGetRootNode(uiDockNode* node) { while (node->ParentNode) node = node->ParentNode; return node; }
    inline bool DockNodeIsInHierarchyOf(uiDockNode* node, uiDockNode* parent) { while (node) { if (node == parent) return true; node = node->ParentNode; } return false; }
    inline int  DockNodeGetDepth(const uiDockNode* node) { int depth = 0; while (node->ParentNode) { node = node->ParentNode; depth++; } return depth; }
    inline uiID DockNodeGetWindowMenuButtonId(const uiDockNode* node) { return ImHashStr("#COLLAPSE", 0, node->ID); }
    inline uiDockNode* GetWindowDockNode() { uiContext& g = *GImGui; return g.CurrentWindow->DockNode; }
    IMGUI_API bool GetWindowAlwaysWantOwnTabBar(uiWindow* window);
    IMGUI_API void BeginDocked(uiWindow* window, bool* p_open);
    IMGUI_API void BeginDockableDragDropSource(uiWindow* window);
    IMGUI_API void BeginDockableDragDropTarget(uiWindow* window);
    IMGUI_API void SetWindowDock(uiWindow* window, uiID dock_id, uiCond cond);
    // Docking - Builder function needs to be generally called before the node is used/submitted.
    // - The DockBuilderXXX functions are designed to _eventually_ become a public API, but it is too early to expose it and guarantee stability.
    // - Do not hold on uiDockNode* pointers! They may be invalidated by any split/merge/remove operation and every frame.
    // - To create a DockSpace() node, make sure to set the uiDockFlags_DockSpace flag when calling DockBuilderAddNode().
    //   You can create dockspace nodes (attached to a window) _or_ floating nodes (carry its own window) with this API.
    // - DockBuilderSplitNode() create 2 child nodes within 1 node. The initial node becomes a parent node.
    // - If you intend to split the node immediately after creation using DockBuilderSplitNode(), make sure
    //   to call DockBuilderSetNodeSize() beforehand. If you don't, the resulting split sizes may not be reliable.
    // - Call DockBuilderFinish() after you are done.
    IMGUI_API void DockBuilderDockWindow(const char* window_name, uiID node_id);
    IMGUI_API uiDockNode*DockBuilderGetNode(uiID node_id);
    inline uiDockNode* DockBuilderGetCentralNode(uiID node_id)              { uiDockNode* node = DockBuilderGetNode(node_id); if (!node) return NULL; return DockNodeGetRootNode(node)->CentralNode; }
    IMGUI_API uiID DockBuilderAddNode(uiID node_id = 0, uiDockFlags flags = 0);
    IMGUI_API void DockBuilderRemoveNode(uiID node_id);                 // Remove node and all its child, undock all windows
    IMGUI_API void DockBuilderRemoveNodeDockedWindows(uiID node_id, bool clear_settings_refs = true);
    IMGUI_API void DockBuilderRemoveNodeChildNodes(uiID node_id);       // Remove all split/hierarchy. All remaining docked windows will be re-docked to the remaining root node (node_id).
    IMGUI_API void DockBuilderSetNodePos(uiID node_id, vec2 pos);
    IMGUI_API void DockBuilderSetNodeSize(uiID node_id, vec2 size);
    IMGUI_API uiID DockBuilderSplitNode(uiID node_id, Var::Dir split_dir, float size_ratio_for_node_at_dir, uiID* out_id_at_dir, uiID* out_id_at_opposite_dir); // Create 2 child nodes in this parent node.
    IMGUI_API void DockBuilderCopyDockSpace(uiID src_dockspace_id, uiID dst_dockspace_id, ImVector<const char*>* in_window_remap_pairs);
    IMGUI_API void DockBuilderCopyNode(uiID src_node_id, uiID dst_node_id, ImVector<uiID>* out_node_remap_pairs);
    IMGUI_API void DockBuilderCopyWindowSettings(const char* src_name, const char* dst_name);
    IMGUI_API void DockBuilderFinish(uiID node_id);
    // [EXPERIMENTAL] Focus Scope
    // This is generally used to identify a unique input location (for e.g. a selection set)
    // There is one per window (automatically set in Begin), but:
    // - Selection patterns generally need to react (e.g. clear a selection) when landing on one item of the set.
    //   So in order to identify a set multiple lists in same window may each need a focus scope.
    //   If you imagine an hypothetical BeginSelectionGroup()/EndSelectionGroup() api, it would likely call PushFocusScope()/EndFocusScope()
    // - Shortcut routing also use focus scope as a default location identifier if an owner is not provided.
    // We don't use the ID Stack for this as it is common to want them separate.
    IMGUI_API void PushFocusScope(uiID id);
    IMGUI_API void PopFocusScope();
    IMGUI_API bool IsInNavFocusRoute(uiID focus_scope_id);
    inline uiID    GetCurrentFocusScope() { uiContext& g = *GImGui; return g.CurrentFocusScopeId; }   // Focus scope we are outputting into, set by PushFocusScope()
    // Drag and Drop
    IMGUI_API bool IsDragDropActive();
    IMGUI_API bool BeginDragDropTargetCustom(const ImRect& bb, uiID id);
    IMGUI_API bool BeginDragDropTargetViewport(uiViewport* viewport, const ImRect* p_bb = NULL);
    IMGUI_API void ClearDragDrop();
    IMGUI_API bool IsDragDropPayloadBeingAccepted();
    IMGUI_API void RenderDragDropTargetRectForItem(const ImRect& bb);
    IMGUI_API void RenderDragDropTargetRectEx(ImDrawList* draw_list, const ImRect& bb, float rounding);
    // Typing-Select API
    // (provide Windows Explorer style "select items by typing partial name" + "cycle through items by typing same letter" feature)
    // (this is currently not documented nor used by main library, but should work. See "widgets_typingselect" in imgui_test_suite for usage code. Please let us know if you use this!)
    IMGUI_API uiTypingSelectRequest* GetTypingSelectRequest(uiTypingSelectFlags flags = uiTypingSelectFlags_None);
    IMGUI_API int TypingSelectFindMatch(uiTypingSelectRequest* req, int items_count, const char* (*get_item_name_func)(void*, int), void* user_data, int nav_item_idx);
    IMGUI_API int TypingSelectFindNextSingleCharMatch(uiTypingSelectRequest* req, int items_count, const char* (*get_item_name_func)(void*, int), void* user_data, int nav_item_idx);
    IMGUI_API int TypingSelectFindBestLeadingMatch(uiTypingSelectRequest* req, int items_count, const char* (*get_item_name_func)(void*, int), void* user_data);
    // Box-Select API
    IMGUI_API bool BeginBoxSelect(const ImRect& scope_rect, uiWindow* window, uiID box_select_id, uiMultiSelectFlags ms_flags);
    IMGUI_API void EndBoxSelect(const ImRect& scope_rect, uiMultiSelectFlags ms_flags);
    // Multi-Select API
    IMGUI_API void MultiSelectItemHeader(uiID id, bool* p_selected, uiButtonFlags* p_button_flags);
    IMGUI_API void MultiSelectItemFooter(uiID id, bool* p_selected, bool* p_pressed);
    IMGUI_API void MultiSelectAddSetAll(uiMultiSelectTempData* ms, bool selected);
    IMGUI_API void MultiSelectAddSetRange(uiMultiSelectTempData* ms, bool selected, int range_dir, uiSelectionUserData first_item, uiSelectionUserData last_item);
    inline uiBoxSelectState* GetBoxSelectState(uiID id)   { uiContext& g = *GImGui; return (id != 0 && g.BoxSelectState.ID == id && g.BoxSelectState.IsActive) ? &g.BoxSelectState : NULL; }
    inline uiMultiSelectState* GetMultiSelectState(uiID id) { uiContext& g = *GImGui; return g.MultiSelectStorage.GetByKey(id); }
    // Internal Columns API (this is not exposed because we will encourage transitioning to the Tables API)
    IMGUI_API void SetWindowClipRectBeforeSetChannel(uiWindow* window, const ImRect& clip_rect);
    IMGUI_API void BeginColumns(const char* str_id, int count, uiOldColumnFlags flags = 0); // setup number of columns. use an identifier to distinguish multiple column sets. close with EndColumns().
    IMGUI_API void EndColumns();                                                               // close columns
    IMGUI_API void PushColumnClipRect(int column_index);
    IMGUI_API void PushColumnsBackground();
    IMGUI_API void PopColumnsBackground();
    IMGUI_API uiID GetColumnsID(const char* str_id, int count);
    IMGUI_API uiOldColumns* FindOrCreateColumns(uiWindow* window, uiID id);
    IMGUI_API float GetColumnOffsetFromNorm(const uiOldColumns* columns, float offset_norm);
    IMGUI_API float GetColumnNormFromOffset(const uiOldColumns* columns, float offset);
    // Tables: Candidates for public API
    IMGUI_API void  TableOpenContextMenu(int column_n = -1);
    IMGUI_API void  TableSetColumnWidth(int column_n, float width);
    IMGUI_API void  TableSetColumnSortDirection(int column_n, Var::SortDir sort_direction, bool append_to_sort_specs);
    IMGUI_API int   TableGetHoveredRow();       // Retrieve *PREVIOUS FRAME* hovered row. This difference with TableGetHoveredColumn() is the reason why this is not public yet.
    IMGUI_API float TableGetHeaderRowHeight();
    IMGUI_API float TableGetHeaderAngledMaxLabelWidth();
    IMGUI_API void  TablePushBackgroundChannel();
    IMGUI_API void  TablePopBackgroundChannel();
    IMGUI_API void  TablePushColumnChannel(int column_n);
    IMGUI_API void  TablePopColumnChannel();
    IMGUI_API void  TableAngledHeadersRowEx(uiID row_id, float angle, float max_label_width, const uiTableHeaderData* data, int data_count);
    // Tables: Internals
    inline    uiTable*     GetCurrentTable() { uiContext& g = *GImGui; return g.CurrentTable; }
    IMGUI_API uiTable*     TableFindByID(uiID id);
    IMGUI_API bool         BeginTableEx(const char* name, uiID id, int columns_count, uiTableFlags flags = 0, const vec2& outer_size = vec2(0, 0), float inner_width = 0.0f);
    IMGUI_API void         TableBeginInitMemory(uiTable* table, int columns_count);
    IMGUI_API void         TableBeginApplyRequests(uiTable* table);
    IMGUI_API void         TableSetupDrawChannels(uiTable* table);
    IMGUI_API void         TableUpdateLayout(uiTable* table);
    IMGUI_API void         TableUpdateBorders(uiTable* table);
    IMGUI_API void         TableUpdateColumnsWeightFromWidth(uiTable* table);
    IMGUI_API void         TableApplyExternalUnclipRect(uiTable* table, ImRect& rect);
    IMGUI_API void         TableDrawBorders(uiTable* table);
    IMGUI_API void         TableDrawDefaultContextMenu(uiTable* table, uiTableFlags flags_for_section_to_display);
    IMGUI_API bool         TableBeginContextMenuPopup(uiTable* table);
    IMGUI_API void         TableMergeDrawChannels(uiTable* table);
    inline uiTableInstanceData* TableGetInstanceData(uiTable* table, int instance_no) { if (instance_no == 0) return &table->InstanceDataFirst; return &table->InstanceDataExtra[instance_no - 1]; }
    inline uiID            TableGetInstanceID(uiTable* table, int instance_no)   { return TableGetInstanceData(table, instance_no)->TableInstanceID; }
    IMGUI_API void         TableFixDisplayOrder(uiTable* table);
    IMGUI_API void         TableSortSpecsSanitize(uiTable* table);
    IMGUI_API void         TableSortSpecsBuild(uiTable* table);
    IMGUI_API Var::SortDir TableGetColumnNextSortDirection(uiTableColumn* column);
    IMGUI_API void         TableFixColumnSortDirection(uiTable* table, uiTableColumn* column);
    IMGUI_API float        TableGetColumnWidthAuto(uiTable* table, uiTableColumn* column);
    IMGUI_API void         TableBeginRow(uiTable* table);
    IMGUI_API void         TableEndRow(uiTable* table);
    IMGUI_API void         TableBeginCell(uiTable* table, int column_n);
    IMGUI_API void         TableEndCell(uiTable* table);
    IMGUI_API ImRect       TableGetCellBgRect(const uiTable* table, int column_n);
    IMGUI_API const char*  TableGetColumnName(const uiTable* table, int column_n);
    IMGUI_API uiID         TableGetColumnResizeID(uiTable* table, int column_n, int instance_no = 0);
    IMGUI_API float        TableCalcMaxColumnWidth(const uiTable* table, int column_n);
    IMGUI_API void         TableSetColumnWidthAutoSingle(uiTable* table, int column_n);
    IMGUI_API void         TableSetColumnWidthAutoAll(uiTable* table);
    IMGUI_API void         TableSetColumnDisplayOrder(uiTable* table, int column_n, int dst_order);
    IMGUI_API void         TableQueueSetColumnDisplayOrder(uiTable* table, int column_n, int dst_order);
    IMGUI_API void         TableRemove(uiTable* table);
    IMGUI_API void         TableGcCompactTransientBuffers(uiTable* table);
    IMGUI_API void         TableGcCompactTransientBuffers(uiTableTempData* table);
    IMGUI_API void         TableGcCompactSettings();

    // Tables: Settings
    IMGUI_API void             TableLoadSettings(uiTable* table);
    IMGUI_API void             TableSaveSettings(uiTable* table);
    IMGUI_API void             TableResetSettings(uiTable* table);
    IMGUI_API uiTableSettings* TableGetBoundSettings(uiTable* table);
    IMGUI_API void             TableSettingsAddSettingsHandler();
    IMGUI_API uiTableSettings* TableSettingsCreate(uiID id, int columns_count);
    IMGUI_API uiTableSettings* TableSettingsFindByID(uiID id);

    // Tab Bars
    inline    uiTabBar*  GetCurrentTabBar() { uiContext& g = *GImGui; return g.CurrentTabBar; }
    IMGUI_API uiTabBar*  TabBarFindByID(uiID id);
    IMGUI_API void          TabBarRemove(uiTabBar* tab_bar);
    IMGUI_API bool          BeginTabBarEx(uiTabBar* tab_bar, const ImRect& bb, uiTabBarFlags flags);
    IMGUI_API uiTabItem* TabBarFindTabByID(uiTabBar* tab_bar, uiID tab_id);
    IMGUI_API uiTabItem* TabBarFindTabByOrder(uiTabBar* tab_bar, int order);
    IMGUI_API uiTabItem* TabBarFindMostRecentlySelectedTabForActiveWindow(uiTabBar* tab_bar);
    IMGUI_API uiTabItem* TabBarGetCurrentTab(uiTabBar* tab_bar);
    inline int              TabBarGetTabOrder(uiTabBar* tab_bar, uiTabItem* tab) { return tab_bar->Tabs.index_from_ptr(tab); }
    IMGUI_API const char*   TabBarGetTabName(uiTabBar* tab_bar, uiTabItem* tab);
    IMGUI_API void          TabBarAddTab(uiTabBar* tab_bar, uiTabItemFlags tab_flags, uiWindow* window);
    IMGUI_API void          TabBarRemoveTab(uiTabBar* tab_bar, uiID tab_id);
    IMGUI_API void          TabBarCloseTab(uiTabBar* tab_bar, uiTabItem* tab);
    IMGUI_API void          TabBarQueueFocus(uiTabBar* tab_bar, uiTabItem* tab);
    IMGUI_API void          TabBarQueueFocus(uiTabBar* tab_bar, const char* tab_name);
    IMGUI_API void          TabBarQueueReorder(uiTabBar* tab_bar, uiTabItem* tab, int offset);
    IMGUI_API void          TabBarQueueReorderFromMousePos(uiTabBar* tab_bar, uiTabItem* tab, vec2 mouse_pos);
    IMGUI_API bool          TabBarProcessReorder(uiTabBar* tab_bar);
    IMGUI_API bool          TabItemEx(uiTabBar* tab_bar, const char* label, bool* p_open, uiTabItemFlags flags, uiWindow* docked_window);
    IMGUI_API void          TabItemSpacing(const char* str_id, uiTabItemFlags flags, float width);
    IMGUI_API vec2        TabItemCalcSize(const char* label, bool has_close_button_or_unsaved_marker);
    IMGUI_API vec2        TabItemCalcSize(uiWindow* window);
    IMGUI_API void          TabItemBackground(ImDrawList* draw_list, const ImRect& bb, uiTabItemFlags flags, ImU32 col);
    IMGUI_API void          TabItemLabelAndCloseButton(ImDrawList* draw_list, const ImRect& bb, uiTabItemFlags flags, vec2 frame_padding, const char* label, uiID tab_id, uiID close_button_id, bool is_contents_visible, bool* out_just_closed, bool* out_text_clipped);

    // Render helpers
    // AVOID USING OUTSIDE OF IMGUI.CPP! NOT FOR PUBLIC CONSUMPTION. THOSE FUNCTIONS ARE A MESS. THEIR SIGNATURE AND BEHAVIOR WILL CHANGE, THEY NEED TO BE REFACTORED INTO SOMETHING DECENT.
    // NB: All position are in absolute pixels coordinates (we are never using window coordinates internally)
    IMGUI_API void          RenderText(vec2 pos, const char* text, const char* text_end = NULL, bool hide_text_after_hash = true);
    IMGUI_API void          RenderTextWrapped(vec2 pos, const char* text, const char* text_end, float wrap_width);
    IMGUI_API void          RenderTextClipped(const vec2& pos_min, const vec2& pos_max, const char* text, const char* text_end, const vec2* text_size_if_known, const vec2& align = vec2(0, 0), const ImRect* clip_rect = NULL);
    IMGUI_API void          RenderTextClippedEx(ImDrawList* draw_list, const vec2& pos_min, const vec2& pos_max, const char* text, const char* text_end, const vec2* text_size_if_known, const vec2& align = vec2(0, 0), const ImRect* clip_rect = NULL);
    IMGUI_API void          RenderTextEllipsis(ImDrawList* draw_list, const vec2& pos_min, const vec2& pos_max, float ellipsis_max_x, const char* text, const char* text_end, const vec2* text_size_if_known);
    IMGUI_API void          RenderFrame(vec2 p_min, vec2 p_max, ImU32 fill_col, bool borders = true, float rounding = 0.0f);
    IMGUI_API void          RenderFrameBorder(vec2 p_min, vec2 p_max, float rounding = 0.0f);
    IMGUI_API void          RenderColorComponentMarker(const ImRect& bb, ImU32 col, float rounding);
    IMGUI_API void          RenderColorRectWithAlphaCheckerboard(ImDrawList* draw_list, vec2 p_min, vec2 p_max, ImU32 fill_col, float grid_step, vec2 grid_off, float rounding = 0.0f, ImDrawFlags flags = 0);
    IMGUI_API void          RenderNavCursor(const ImRect& bb, uiID id, uiNavRenderCursorFlags flags = uiNavRenderCursorFlags_None); // Navigation highlight
    IMGUI_API const char*   FindRenderedTextEnd(const char* text, const char* text_end = NULL); // Find the optional ## from which we stop displaying text.
    IMGUI_API void          RenderMouseCursor(vec2 pos, float scale, uiMouseCursor mouse_cursor, ImU32 col_fill, ImU32 col_border, ImU32 col_shadow);

    // Render helpers (those functions don't access any UI state!)
    IMGUI_API void          RenderArrow(ImDrawList* draw_list, vec2 pos, ImU32 col, Var::Dir dir, float scale = 1.0f);
    IMGUI_API void          RenderBullet(ImDrawList* draw_list, vec2 pos, ImU32 col);
    IMGUI_API void          RenderCheckMark(ImDrawList* draw_list, vec2 pos, ImU32 col, float sz);
    IMGUI_API void          RenderArrowPointingAt(ImDrawList* draw_list, vec2 pos, vec2 half_sz, Var::Dir direction, ImU32 col);
    IMGUI_API void          RenderArrowDockMenu(ImDrawList* draw_list, vec2 p_min, float sz, ImU32 col);
    IMGUI_API void          RenderRectFilledInRangeH(ImDrawList* draw_list, const ImRect& rect, ImU32 col, float fill_x0, float fill_x1, float rounding);
    IMGUI_API void          RenderRectFilledWithHole(ImDrawList* draw_list, const ImRect& outer, const ImRect& inner, ImU32 col, float rounding);
    IMGUI_API ImDrawFlags   CalcRoundingFlagsForRectInRect(const ImRect& r_in, const ImRect& r_outer, float threshold);

    // Widgets: Text
    IMGUI_API void          TextEx(const char* text, const char* text_end = NULL, uiTextFlags flags = 0);
    IMGUI_API void          TextAligned(float align_x, float size_x, const char* fmt, ...);               // FIXME-WIP: Works but API is likely to be reworked. This is designed for 1 item on the line. (#7024)
    IMGUI_API void          TextAlignedV(float align_x, float size_x, const char* fmt, va_list args);

    // Widgets
    IMGUI_API bool          ButtonEx(const char* label, const vec2& size_arg = vec2(0, 0), uiButtonFlags flags = 0);
    IMGUI_API bool          ArrowButtonEx(const char* str_id, Var::Dir dir, vec2 size_arg, uiButtonFlags flags = 0);
    IMGUI_API bool          ImageButtonEx(uiID id, ImTextureRef tex_ref, const vec2& image_size, const vec2& uv0, const vec2& uv1, const vec4& bg_col, const vec4& tint_col, uiButtonFlags flags = 0);
    IMGUI_API void          BarrierEx(uiBarrierFlags flags, float thickness = 1.0f);
    IMGUI_API void          BarrierTextEx(uiID id, const char* label, const char* label_end, float extra_width);
    IMGUI_API bool          CheckboxFlags(const char* label, ImS64* flags, ImS64 flags_value);
    IMGUI_API bool          CheckboxFlags(const char* label, ImU64* flags, ImU64 flags_value);
    // Widgets: Window Decorations
    IMGUI_API bool   CloseButton(uiID id, const vec2& pos);
    IMGUI_API bool   CollapseButton(uiID id, const vec2& pos, uiDockNode* dock_node);
    IMGUI_API void   Scrollbar(uiAxis axis);
    IMGUI_API bool   ScrollbarEx(const ImRect& bb, uiID id, uiAxis axis, ImS64* p_scroll_v, ImS64 avail_v, ImS64 contents_v, ImDrawFlags draw_rounding_flags = 0);
    IMGUI_API ImRect GetWindowScrollbarRect(uiWindow* window, uiAxis axis);
    IMGUI_API uiID   GetWindowScrollbarID(uiWindow* window, uiAxis axis);
    IMGUI_API uiID   GetWindowResizeCornerID(uiWindow* window, int n); // 0..3: corners
    IMGUI_API uiID   GetWindowResizeBorderID(uiWindow* window, Var::Dir dir);
    IMGUI_API void   ExtendHitBoxWhenNearViewportEdge(uiWindow* window, ImRect* bb, float threshold, uiAxis axis);
    // Widgets low-level behaviors
    IMGUI_API bool ButtonBehavior(const ImRect& bb, uiID id, bool* out_hovered, bool* out_held, uiButtonFlags flags = 0);
    IMGUI_API bool DragBehavior(uiID id, uiDataType data_type, void* p_v, float v_speed, const void* p_min, const void* p_max, const char* format, uiSliderFlags flags);
    IMGUI_API bool SliderBehavior(const ImRect& bb, uiID id, uiDataType data_type, void* p_v, const void* p_min, const void* p_max, const char* format, uiSliderFlags flags, ImRect* out_grab_bb);
    IMGUI_API bool SplitterBehavior(const ImRect& bb, uiID id, uiAxis axis, float* size1, float* size2, float min_size1, float min_size2, float hover_extend = 0.0f, float hover_visibility_delay = 0.0f, ImU32 bg_col = 0);
    // Widgets: Tree Nodes
    IMGUI_API bool TreeNodeBehavior(uiID id, uiTreeFlags flags, const char* label, const char* label_end = NULL);
    IMGUI_API void TreeNodeDrawLineToChildNode(const vec2& target_pos);
    IMGUI_API void TreeNodeDrawLineToTreePop(const uiTreeNodeStackData* data);
    IMGUI_API void TreePushOverrideID(uiID id);
    IMGUI_API void TreeNodeSetOpen(uiID storage_id, bool open);
    IMGUI_API bool TreeNodeUpdateNextOpen(uiID storage_id, uiTreeFlags flags);   // Return open state. Consume previous SetNextItemOpen() data, if any. May return true when logging.
    // Template functions are instantiated in imgui_widgets.cpp for a finite number of types.
    // To use them externally (for custom widget) you may need an "extern template" statement in your code in order to link to existing instances and silence Clang warnings (see #2036).
    // e.g. " extern template IMGUI_API float RoundScalarWithFormatT<float, float>(const char* format, uiDataType data_type, float v); "
    template<typename T, typename SIGNED_T, typename FLOAT_T> IMGUI_API float ScaleRatioFromValueT(uiDataType data_type, T v, T v_min, T v_max, float logarithmic_zero_epsilon, float zero_deadzone_size);
    template<typename T, typename SIGNED_T, typename FLOAT_T> IMGUI_API T     ScaleValueFromRatioT(uiDataType data_type, float t, T v_min, T v_max, float logarithmic_zero_epsilon, float zero_deadzone_size);
    template<typename T, typename SIGNED_T, typename FLOAT_T> IMGUI_API bool  DragBehaviorT(uiDataType data_type, T* v, float v_speed, T v_min, T v_max, const char* format, uiSliderFlags flags);
    template<typename T, typename SIGNED_T, typename FLOAT_T> IMGUI_API bool  SliderBehaviorT(const ImRect& bb, uiID id, uiDataType data_type, T* v, T v_min, T v_max, const char* format, uiSliderFlags flags, ImRect* out_grab_bb);
    template<typename T>                                      IMGUI_API T     RoundScalarWithFormatT(const char* format, uiDataType data_type, T v);
    template<typename T>                                      IMGUI_API bool  CheckboxFlagsT(const char* label, T* flags, T flags_value);
    // Data type helpers
    IMGUI_API const uiDataTypeInfo* DataTypeGetInfo(uiDataType data_type);
    IMGUI_API int  DataTypeFormatString(char* buf, int buf_size, uiDataType data_type, const void* p_data, const char* format);
    IMGUI_API void DataTypeApplyOp(uiDataType data_type, int op, void* output, const void* arg_1, const void* arg_2);
    IMGUI_API bool DataTypeApplyFromText(const char* buf, uiDataType data_type, void* p_data, const char* format, void* p_data_when_empty = NULL);
    IMGUI_API int  DataTypeCompare(uiDataType data_type, const void* arg_1, const void* arg_2);
    IMGUI_API bool DataTypeClamp(uiDataType data_type, void* p_data, const void* p_min, const void* p_max);
    IMGUI_API bool DataTypeIsZero(uiDataType data_type, const void* p_data);
    // InputText
    IMGUI_API bool InputTextEx(const char* label, const char* hint, char* buf, int buf_size, const vec2& size_arg, uiInputTextFlags flags, uiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API void InputTextDeactivateHook(uiID id);
    IMGUI_API bool TempInputText(const ImRect& bb, uiID id, const char* label, char* buf, size_t buf_size, uiInputTextFlags flags = 0, uiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool TempInputScalar(const ImRect& bb, uiID id, const char* label, uiDataType data_type, void* p_data, const char* format, const void* p_clamp_min = NULL, const void* p_clamp_max = NULL);
    inline bool    TempInputIsActive(uiID id)       { uiContext& g = *GImGui; return g.ActiveId == id && g.TempInputId == id; }
    inline uiInputTextState* GetInputTextState(uiID id)   { uiContext& g = *GImGui; return (id != 0 && g.InputTextState.ID == id) ? &g.InputTextState : NULL; } // Get input text state if active
    IMGUI_API void SetNextItemRefVal(uiDataType data_type, void* p_data);
    inline bool    IsItemActiveAsInputText() { uiContext& g = *GImGui; return g.ActiveId != 0 && g.ActiveId == g.LastItemData.ID && g.InputTextState.ID == g.LastItemData.ID; } // This may be useful to apply workaround that a based on distinguish whenever an item is active as a text input field.
    // Color
    IMGUI_API void ColorTooltip(const char* text, const float* col, uiColorEditFlags flags);
    IMGUI_API void ColorEditOptionsPopup(const float* col, uiColorEditFlags flags);
    IMGUI_API void ColorPickerOptionsPopup(const float* ref_col, uiColorEditFlags flags);
    inline void    SetNextItemColorMarker(ImU32 col) { uiContext& g = *GImGui; g.NextItemData.HasFlags |= uiNextItemDataFlags_HasColorMarker; g.NextItemData.ColorMarker = col; }
    // Plot
    IMGUI_API int PlotEx(uiPlotType plot_type, const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, const vec2& size_arg);
    // Shade functions (write over already created vertices)
    IMGUI_API void ShadeVertsLinearColorGradientKeepAlpha(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, vec2 gradient_p0, vec2 gradient_p1, ImU32 col0, ImU32 col1);
    IMGUI_API void ShadeVertsLinearUV(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, const vec2& a, const vec2& b, const vec2& uv_a, const vec2& uv_b, bool clamp);
    IMGUI_API void ShadeVertsTransformPos(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, const vec2& pivot_in, float cos_a, float sin_a, const vec2& pivot_out);
    // Garbage collection
    IMGUI_API void GcCompactTransientMiscBuffers();
    IMGUI_API void GcCompactTransientWindowBuffers(uiWindow* window);
    IMGUI_API void GcAwakeTransientWindowBuffers(uiWindow* window);
    // Error handling, State Recovery
    IMGUI_API bool ErrorLog(const char* msg);
    IMGUI_API void ErrorRecoveryStoreState(uiErrorRecoveryState* state_out);
    IMGUI_API void ErrorRecoveryTryToRecoverState(const uiErrorRecoveryState* state_in);
    IMGUI_API void ErrorRecoveryTryToRecoverWindowState(const uiErrorRecoveryState* state_in);
    IMGUI_API void ErrorCheckUsingSetCursorPosToExtendParentBoundaries();
    IMGUI_API void ErrorCheckEndFrameFinalizeErrorTooltip();
    IMGUI_API bool BeginErrorTooltip();
    IMGUI_API void EndErrorTooltip();
    // Demo Doc Marker for e.g. imgui_explorer
    IMGUI_API void DemoMarker(const char* file, int line, const char* section);
    // Debug Tools
    IMGUI_API void DebugAllocHook(uiDebugAllocInfo* info, int frame_count, void* ptr, size_t size); // size >= 0 : alloc, size = -1 : free
    IMGUI_API void DebugDrawCursorPos(ImU32 col = IM_COL32(255, 0, 0, 255));
    IMGUI_API void DebugDrawLineExtents(ImU32 col = IM_COL32(255, 0, 0, 255));
    IMGUI_API void DebugDrawItemRect(ImU32 col = IM_COL32(255, 0, 0, 255));
    IMGUI_API void DebugTextUnformattedWithLocateItem(const char* line_begin, const char* line_end);
    IMGUI_API void DebugLocateItem(uiID target_id);        // Call sparingly: only 1 at the same time!
    IMGUI_API void DebugLocateItemOnHover(uiID target_id); // Only call on reaction to a mouse Hover: because only 1 at the same time!
    IMGUI_API void DebugLocateItemResolveWithLastItem();
    IMGUI_API void DebugBreakClearData();
    IMGUI_API bool DebugBreakButton(const char* label, const char* description_of_location);
    IMGUI_API void DebugBreakButtonTooltip(bool keyboard_only, const char* description_of_location);
    IMGUI_API void ShowFontAtlas(ImFontAtlas* atlas);
    IMGUI_API ImU64 DebugTextureIDToU64(ImTextureID tex_id);
    IMGUI_API void DebugHookIdInfo(uiID id, uiDataType data_type, const void* data_id, const void* data_id_end);
    IMGUI_API void DebugNodeColumns(uiOldColumns* columns);
    IMGUI_API void DebugNodeDockNode(uiDockNode* node, const char* label);
    IMGUI_API void DebugNodeDrawList(uiWindow* window, uiViewportP* viewport, const ImDrawList* draw_list, const char* label);
    IMGUI_API void DebugNodeDrawCmdShowMeshAndBoundingBox(ImDrawList* out_draw_list, const ImDrawList* draw_list, const ImDrawCmd* draw_cmd, bool show_mesh, bool show_aabb);
    IMGUI_API void DebugNodeFont(ImFont* font);
    IMGUI_API void DebugNodeFontGlyphsForSrcMask(ImFont* font, ImFontBaked* baked, int src_mask);
    IMGUI_API void DebugNodeFontGlyph(ImFont* font, const ImFontGlyph* glyph);
    IMGUI_API void DebugNodeTexture(ImTextureData* tex, int int_id, const ImFontAtlasRect* highlight_rect = NULL); // ID used to facilitate persisting the "current" texture.
    IMGUI_API void DebugNodeStorage(uiStorage* storage, const char* label);
    IMGUI_API void DebugNodeTabBar(uiTabBar* tab_bar, const char* label);
    IMGUI_API void DebugNodeTable(uiTable* table);
    IMGUI_API void DebugNodeTableSettings(uiTableSettings* settings);
    IMGUI_API void DebugNodeInputTextState(uiInputTextState* state);
    IMGUI_API void DebugNodeTypingSelectState(uiTypingSelectState* state);
    IMGUI_API void DebugNodeMultiSelectState(uiMultiSelectState* state);
    IMGUI_API void DebugNodeWindow(uiWindow* window, const char* label);
    IMGUI_API void DebugNodeWindowSettings(uiWindowSettings* settings);
    IMGUI_API void DebugNodeWindowsList(ImVector<uiWindow*>* windows, const char* label);
    IMGUI_API void DebugNodeWindowsListByBeginStackParent(uiWindow** windows, int windows_size, uiWindow* parent_in_begin_stack);
    IMGUI_API void DebugNodeViewport(uiViewportP* viewport);
    IMGUI_API void DebugNodePlatformMonitor(uiPlatformMonitor* monitor, const char* label, int idx);
    IMGUI_API void DebugRenderKeyboardPreview(ImDrawList* draw_list);
    IMGUI_API void DebugRenderViewportThumbnail(ImDrawList* draw_list, uiViewportP* viewport, const ImRect& bb);
} // namespace UI
//-----------------------------------------------------------------------------
// [SECTION] ImFontLoader
//-----------------------------------------------------------------------------
// Hooks and storage for a given font backend.
// This structure is likely to evolve as we add support for incremental atlas updates.
// Conceptually this could be public, but API is still going to be evolve.
struct ImFontLoader {
    const char* Name;
    bool (*LoaderInit)(ImFontAtlas* atlas);
    void (*LoaderShutdown)(ImFontAtlas* atlas);
    bool (*FontSrcInit)(ImFontAtlas* atlas, ImFontConfig* src);
    void (*FontSrcDestroy)(ImFontAtlas* atlas, ImFontConfig* src);
    bool (*FontSrcContainsGlyph)(ImFontAtlas* atlas, ImFontConfig* src, ImWchar codepoint);
    bool (*FontBakedInit)(ImFontAtlas* atlas, ImFontConfig* src, ImFontBaked* baked, void* loader_data_for_baked_src);
    void (*FontBakedDestroy)(ImFontAtlas* atlas, ImFontConfig* src, ImFontBaked* baked, void* loader_data_for_baked_src);
    bool (*FontBakedLoadGlyph)(ImFontAtlas* atlas, ImFontConfig* src, ImFontBaked* baked, void* loader_data_for_baked_src, ImWchar codepoint, ImFontGlyph* out_glyph, float* out_advance_x);
    // Size of backend data, Per Baked * Per Source. Buffers are managed by core to avoid excessive allocations.
    // FIXME: At this point the two other types of buffers may be managed by core to be consistent?
    size_t FontBakedSrcLoaderDataSize;
    ImFontLoader() { memset((void*)this, 0, sizeof(*this)); }
};
#ifdef IMGUI_ENABLE_STB_TRUETYPE
IMGUI_API const ImFontLoader* ImFontAtlasGetFontLoaderForStbTruetype();
#endif
//-----------------------------------------------------------------------------
// [SECTION] ImFontAtlas internal API
//-----------------------------------------------------------------------------
#define IMGUI_FONT_SIZE_MAX                                (512.0f)
#define IMGUI_FONT_SIZE_THRESHOLD_FOR_LOADADVANCEXONLYMODE (128.0f)
// Helpers: ImTextureRef ==/!= operators provided as convenience
// (note that _TexID and _TexData are never set simultaneously)
inline bool operator==(const ImTextureRef& lhs, const ImTextureRef& rhs) { return lhs._TexID == rhs._TexID && lhs._TexData == rhs._TexData; }
inline bool operator!=(const ImTextureRef& lhs, const ImTextureRef& rhs) { return lhs._TexID != rhs._TexID || lhs._TexData != rhs._TexData; }
// Refer to ImFontAtlasPackGetRect() to better understand how this works.
#define ImFontAtlasRectId_IndexMask_       (0x0007FFFF) // 20-bits signed: index to access builder->RectsIndex[].
#define ImFontAtlasRectId_GenerationMask_  (0x3FF00000) // 10-bits: entry generation, so each ID is unique and get can safely detected old identifiers.
#define ImFontAtlasRectId_GenerationShift_ (20)
inline int               ImFontAtlasRectId_GetIndex(ImFontAtlasRectId id)      { return (id & ImFontAtlasRectId_IndexMask_); }
inline unsigned int      ImFontAtlasRectId_GetGeneration(ImFontAtlasRectId id) { return (unsigned int)(id & ImFontAtlasRectId_GenerationMask_) >> ImFontAtlasRectId_GenerationShift_; }
inline ImFontAtlasRectId ImFontAtlasRectId_Make(int index_idx, int gen_idx)    { IM_ASSERT(index_idx >= 0 && index_idx <= ImFontAtlasRectId_IndexMask_ && gen_idx <= (ImFontAtlasRectId_GenerationMask_ >> ImFontAtlasRectId_GenerationShift_)); return (ImFontAtlasRectId)(index_idx | (gen_idx << ImFontAtlasRectId_GenerationShift_)); }
// Packed rectangle lookup entry (we need an indirection to allow removing/reordering rectangles)
// User are returned ImFontAtlasRectId values which are meant to be persistent.
// We handle this with an indirection. While Rects[] may be in theory shuffled, compacted etc., RectsIndex[] cannot it is keyed by ImFontAtlasRectId.
// RectsIndex[] is used both as an index into Rects[] and an index into itself. This is basically a free-list. See ImFontAtlasBuildAllocRectIndexEntry() code.
// Having this also makes it easier to e.g. sort rectangles during repack.
struct ImFontAtlasRectEntry {
    int          TargetIndex : 20; // When Used: ImFontAtlasRectId -> into Rects[]. When unused: index to next unused RectsIndex[] slot to consume free-list.
    unsigned int Generation : 10;  // Increased each time the entry is reused for a new rectangle.
    unsigned int IsUsed : 1;
};
// Data available to potential texture post-processing functions
struct ImFontAtlasPostProcessData {
    ImFontAtlas*  FontAtlas;
    ImFont*       Font;
    ImFontConfig* FontSrc;
    ImFontBaked*  FontBaked;
    ImFontGlyph*  Glyph;
    // Pixel data
    void*           Pixels;
    ImTextureFormat Format;
    int             Pitch;
    int             Width;
    int             Height;
};

// We avoid dragging imstb_rectpack.h into public header (partly because binding generators are having issues with it)
#ifdef IMGUI_STB_NAMESPACE
namespace UI_STB_NAMESPACE { struct stbrp_node; }
typedef IMGUI_STB_NAMESPACE::stbrp_node stbrp_node_im;
#else
struct stbrp_node;
typedef stbrp_node stbrp_node_im;
#endif
struct stbrp_context_opaque { char data[80]; };
// Internal storage for incrementally packing and building a ImFontAtlas
struct ImFontAtlasBuilder {
    stbrp_context_opaque    PackContext;           // Actually 'stbrp_context' but we don't want to define this in the header file.
    ImVector<stbrp_node_im> PackNodes;
    ImVector<ImTextureRect> Rects;
    ImVector<ImFontAtlasRectEntry> RectsIndex;     // ImFontAtlasRectId -> index into Rects[]
    ImVector<unsigned char> TempBuffer;            // Misc scratch buffer
    int   RectsIndexFreeListStart; // First unused entry
    int   RectsPackedCount;      // Number of packed rectangles.
    int   RectsPackedSurface;    // Number of packed pixels. Used when compacting to heuristically find the ideal texture size.
    int   RectsDiscardedCount;
    int   RectsDiscardedSurface;
    int   FrameCount;            // Current frame count
    vec2i MaxRectSize;           // Largest rectangle to pack (de-facto used as a "minimum texture size")
    vec2i MaxRectBounds;         // Bottom-right most used pixels
    bool  LockDisableResize;     // Disable resizing texture
    bool  PreloadedAllGlyphsRanges; // Set when missing uiBackendFlags_RendererHasTextures features forces atlas to preload everything.
    // Cache of all ImFontBaked
    ImStableVector<ImFontBaked,32> BakedPool;
    uiStorage BakedMap; // BakedId --> ImFontBaked*
    int       BakedDiscardedCount;
    // Custom rectangle identifiers
    ImFontAtlasRectId PackIdMouseCursors; // White pixel + mouse cursors. Also happen to be fallback in case of packing failure.
    ImFontAtlasRectId PackIdLinesTexData;
    ImFontAtlasBuilder() { memset((void*)this, 0, sizeof(*this)); FrameCount = -1; RectsIndexFreeListStart = -1; PackIdMouseCursors = PackIdLinesTexData = -1; }
};
IMGUI_API void ImFontAtlasBuildInit(ImFontAtlas* atlas);
IMGUI_API void ImFontAtlasBuildDestroy(ImFontAtlas* atlas);
IMGUI_API void ImFontAtlasBuildMain(ImFontAtlas* atlas);
IMGUI_API void ImFontAtlasBuildSetupFontLoader(ImFontAtlas* atlas, const ImFontLoader* font_loader);
IMGUI_API void ImFontAtlasBuildNotifySetFont(ImFontAtlas* atlas, ImFont* old_font, ImFont* new_font);
IMGUI_API void ImFontAtlasBuildUpdatePointers(ImFontAtlas* atlas);
IMGUI_API void ImFontAtlasBuildRenderBitmapFromString(ImFontAtlas* atlas, int x, int y, int w, int h, const char* in_str, char in_marker_char);
IMGUI_API void ImFontAtlasBuildClear(ImFontAtlas* atlas); // Clear output and custom rects
IMGUI_API ImTextureData* ImFontAtlasTextureAdd(ImFontAtlas* atlas, int w, int h);
IMGUI_API void  ImFontAtlasTextureMakeSpace(ImFontAtlas* atlas);
IMGUI_API void  ImFontAtlasTextureRepack(ImFontAtlas* atlas, int w, int h);
IMGUI_API void  ImFontAtlasTextureGrow(ImFontAtlas* atlas, int old_w = -1, int old_h = -1);
IMGUI_API void  ImFontAtlasTextureCompact(ImFontAtlas* atlas);
IMGUI_API vec2i ImFontAtlasTextureGetSizeEstimate(ImFontAtlas* atlas);

IMGUI_API void ImFontAtlasBuildSetupFontSpecialGlyphs(ImFontAtlas* atlas, ImFont* font, ImFontConfig* src);
IMGUI_API void ImFontAtlasBuildLegacyPreloadAllGlyphRanges(ImFontAtlas* atlas); // Legacy
IMGUI_API void ImFontAtlasBuildGetOversampleFactors(ImFontConfig* src, ImFontBaked* baked, int* out_oversample_h, int* out_oversample_v);
IMGUI_API void ImFontAtlasBuildDiscardBakes(ImFontAtlas* atlas, int unused_frames);

IMGUI_API bool ImFontAtlasFontSourceInit(ImFontAtlas* atlas, ImFontConfig* src);
IMGUI_API void ImFontAtlasFontSourceAddToFont(ImFontAtlas* atlas, ImFont* font, ImFontConfig* src);
IMGUI_API void ImFontAtlasFontDestroySourceData(ImFontAtlas* atlas, ImFontConfig* src);
IMGUI_API bool ImFontAtlasFontInitOutput(ImFontAtlas* atlas, ImFont* font); // Using FontDestroyOutput/FontInitOutput sequence useful notably if font loader params have changed
IMGUI_API void ImFontAtlasFontDestroyOutput(ImFontAtlas* atlas, ImFont* font);
IMGUI_API void ImFontAtlasFontRebuildOutput(ImFontAtlas* atlas, ImFont* font);
IMGUI_API void ImFontAtlasFontDiscardBakes(ImFontAtlas* atlas, ImFont* font, int unused_frames);
IMGUI_API uiID         ImFontAtlasBakedGetId(uiID font_id, float baked_size, float rasterizer_density);
IMGUI_API ImFontBaked* ImFontAtlasBakedGetOrAdd(ImFontAtlas* atlas, ImFont* font, float font_size, float font_rasterizer_density);
IMGUI_API ImFontBaked* ImFontAtlasBakedGetClosestMatch(ImFontAtlas* atlas, ImFont* font, float font_size, float font_rasterizer_density);
IMGUI_API ImFontBaked* ImFontAtlasBakedAdd(ImFontAtlas* atlas, ImFont* font, float font_size, float font_rasterizer_density, uiID baked_id);
IMGUI_API void         ImFontAtlasBakedDiscard(ImFontAtlas* atlas, ImFont* font, ImFontBaked* baked);
IMGUI_API ImFontGlyph* ImFontAtlasBakedAddFontGlyph(ImFontAtlas* atlas, ImFontBaked* baked, ImFontConfig* src, const ImFontGlyph* in_glyph);
IMGUI_API void         ImFontAtlasBakedAddFontGlyphAdvancedX(ImFontAtlas* atlas, ImFontBaked* baked, ImFontConfig* src, ImWchar codepoint, float advance_x);
IMGUI_API void         ImFontAtlasBakedDiscardFontGlyph(ImFontAtlas* atlas, ImFont* font, ImFontBaked* baked, ImFontGlyph* glyph);
IMGUI_API void         ImFontAtlasBakedSetFontGlyphBitmap(ImFontAtlas* atlas, ImFontBaked* baked, ImFontConfig* src, ImFontGlyph* glyph, ImTextureRect* r, const unsigned char* src_pixels, ImTextureFormat src_fmt, int src_pitch);

IMGUI_API void              ImFontAtlasPackInit(ImFontAtlas* atlas);
IMGUI_API ImFontAtlasRectId ImFontAtlasPackAddRect(ImFontAtlas* atlas, int w, int h, ImFontAtlasRectEntry* overwrite_entry = NULL);
IMGUI_API ImTextureRect*    ImFontAtlasPackGetRect(ImFontAtlas* atlas, ImFontAtlasRectId id);
IMGUI_API ImTextureRect*    ImFontAtlasPackGetRectSafe(ImFontAtlas* atlas, ImFontAtlasRectId id);
IMGUI_API void              ImFontAtlasPackDiscardRect(ImFontAtlas* atlas, ImFontAtlasRectId id);

IMGUI_API void ImFontAtlasUpdateNewFrame(ImFontAtlas* atlas, int frame_count, bool renderer_has_textures);
IMGUI_API void ImFontAtlasAddDrawListSharedData(ImFontAtlas* atlas, ImDrawListSharedData* data);
IMGUI_API void ImFontAtlasRemoveDrawListSharedData(ImFontAtlas* atlas, ImDrawListSharedData* data);
IMGUI_API void ImFontAtlasUpdateDrawListsTextures(ImFontAtlas* atlas, ImTextureRef old_tex, ImTextureRef new_tex);
IMGUI_API void ImFontAtlasUpdateDrawListsSharedData(ImFontAtlas* atlas);

IMGUI_API void ImFontAtlasTextureBlockConvert(const unsigned char* src_pixels, ImTextureFormat src_fmt, int src_pitch, unsigned char* dst_pixels, ImTextureFormat dst_fmt, int dst_pitch, int w, int h);
IMGUI_API void ImFontAtlasTextureBlockPostProcess(ImFontAtlasPostProcessData* data);
IMGUI_API void ImFontAtlasTextureBlockPostProcessMultiply(ImFontAtlasPostProcessData* data, float multiply_factor);
IMGUI_API void ImFontAtlasTextureBlockFill(ImTextureData* dst_tex, int dst_x, int dst_y, int w, int h, ImU32 col);
IMGUI_API void ImFontAtlasTextureBlockCopy(ImTextureData* src_tex, int src_x, int src_y, ImTextureData* dst_tex, int dst_x, int dst_y, int w, int h);
IMGUI_API void ImFontAtlasTextureBlockQueueUpload(ImFontAtlas* atlas, ImTextureData* tex, int x, int y, int w, int h);

IMGUI_API bool ImTextureDataUpdateNewFrame(ImTextureData* tex);
IMGUI_API void ImTextureDataQueueUpload(ImTextureData* tex, int x, int y, int w, int h);
IMGUI_API int  ImTextureDataGetFormatBytesPerPixel(ImTextureFormat format);
IMGUI_API const char* ImTextureDataGetStatusName(ImTextureStatus status);
IMGUI_API const char* ImTextureDataGetFormatName(ImTextureFormat format);
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
IMGUI_API void ImFontAtlasDebugLogTextureRequests(ImFontAtlas* atlas);
#endif
IMGUI_API bool ImFontAtlasGetMouseCursorTexData(ImFontAtlas* atlas, uiMouseCursor cursor_type, vec2* out_offset, vec2* out_size, vec2 out_uv_border[2], vec2 out_uv_fill[2]);
//-----------------------------------------------------------------------------
// [SECTION] Test Engine specific hooks (imgui_test_engine)
//-----------------------------------------------------------------------------
#ifdef IMGUI_ENABLE_TEST_ENGINE
extern void        uiTestEngineHook_ItemAdd(uiContext* ctx, uiID id, const ImRect& bb, const uiLastItemData* item_data);           // item_data may be NULL
extern void        uiTestEngineHook_ItemInfo(uiContext* ctx, uiID id, const char* label, uiItemStatusFlags flags);
extern void        uiTestEngineHook_Log(uiContext* ctx, const char* fmt, ...);
extern const char* uiTestEngine_FindItemDebugLabel(uiContext* ctx, uiID id);
// In IMGUI_VERSION_NUM >= 18934: changed IMGUI_TEST_ENGINE_ITEM_ADD(bb,id) to IMGUI_TEST_ENGINE_ITEM_ADD(id,bb,item_data);
#define IMGUI_TEST_ENGINE_ITEM_ADD(_ID,_BB,_ITEM_DATA) if (g.TestEngineHookItems) uiTestEngineHook_ItemAdd(&g, _ID, _BB, _ITEM_DATA)    // Register item bounding box
#define IMGUI_TEST_ENGINE_ITEM_INFO(_ID,_LABEL,_FLAGS) if (g.TestEngineHookItems) uiTestEngineHook_ItemInfo(&g, _ID, _LABEL, _FLAGS)    // Register item label and status flags (optional)
#define IMGUI_TEST_ENGINE_LOG(_FMT,...)                uiTestEngineHook_Log(&g, _FMT, __VA_ARGS__)                                      // Custom log entry from user land into test log
#else
#define IMGUI_TEST_ENGINE_ITEM_ADD(_ID,_BB,_ITEM_DATA) ((void)0)
#define IMGUI_TEST_ENGINE_ITEM_INFO(_ID,_LABEL,_FLAGS) ((void)g)
#endif
//-----------------------------------------------------------------------------
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#ifdef _MSC_VER
#pragma warning (pop)
#endif
#endif // #ifndef IMGUI_DISABLE