#pragma once
#include <vector>
#include <windows.h>
#include <unordered_map>

enum class Key : int
{
    // Mouse buttons
    MouseLeft = VK_LBUTTON,
    MouseRight = VK_RBUTTON,
    MouseCancel = VK_CANCEL,
    MouseMiddle = VK_MBUTTON,
    MouseX1 = VK_XBUTTON1,
    MouseX2 = VK_XBUTTON2,

    // Control keys
    Backspace = VK_BACK,
    Tab = VK_TAB,
    Clear = VK_CLEAR,
    Enter = VK_RETURN,
    Shift = VK_SHIFT,
    Control = VK_CONTROL,
    Alt = VK_MENU,
    Pause = VK_PAUSE,
    CapsLock = VK_CAPITAL,
    Escape = VK_ESCAPE,
    Space = VK_SPACE,

    // IME / international input
    Kana = VK_KANA,
    Hangul = VK_HANGUL,
    ImeOn = VK_IME_ON,
    Junja = VK_JUNJA,
    Final = VK_FINAL,
    Hanja = VK_HANJA,
    Kanji = VK_KANJI,
    ImeOff = VK_IME_OFF,
    Convert = VK_CONVERT,
    NonConvert = VK_NONCONVERT,
    Accept = VK_ACCEPT,
    ModeChange = VK_MODECHANGE,

    // Navigation
    PageUp = VK_PRIOR,
    PageDown = VK_NEXT,
    End = VK_END,
    Home = VK_HOME,
    Left = VK_LEFT,
    Up = VK_UP,
    Right = VK_RIGHT,
    Down = VK_DOWN,
    Select = VK_SELECT,
    Print = VK_PRINT,
    Execute = VK_EXECUTE,
    PrintScreen = VK_SNAPSHOT,
    Insert = VK_INSERT,
    Delete = VK_DELETE,
    Help = VK_HELP,

    // Number row
    Num0 = '0',
    Num1 = '1',
    Num2 = '2',
    Num3 = '3',
    Num4 = '4',
    Num5 = '5',
    Num6 = '6',
    Num7 = '7',
    Num8 = '8',
    Num9 = '9',

    // Letters
    A = 'A', B = 'B', C = 'C', D = 'D',
    E = 'E', F = 'F', G = 'G', H = 'H',
    I = 'I', J = 'J', K = 'K', L = 'L',
    M = 'M', N = 'N', O = 'O', P = 'P',
    Q = 'Q', R = 'R', S = 'S', T = 'T',
    U = 'U', V = 'V', W = 'W', X = 'X',
    Y = 'Y', Z = 'Z',

    // Windows / application keys
    LeftWindows = VK_LWIN,
    RightWindows = VK_RWIN,
    Applications = VK_APPS,
    Sleep = VK_SLEEP,

    // Numeric keypad
    Numpad0 = VK_NUMPAD0,
    Numpad1 = VK_NUMPAD1,
    Numpad2 = VK_NUMPAD2,
    Numpad3 = VK_NUMPAD3,
    Numpad4 = VK_NUMPAD4,
    Numpad5 = VK_NUMPAD5,
    Numpad6 = VK_NUMPAD6,
    Numpad7 = VK_NUMPAD7,
    Numpad8 = VK_NUMPAD8,
    Numpad9 = VK_NUMPAD9,
    Multiply = VK_MULTIPLY,
    Add = VK_ADD,
    Separator = VK_SEPARATOR,
    Subtract = VK_SUBTRACT,
    Decimal = VK_DECIMAL,
    Divide = VK_DIVIDE,

    // Function keys
    F1 = VK_F1,
    F2 = VK_F2,
    F3 = VK_F3,
    F4 = VK_F4,
    F5 = VK_F5,
    F6 = VK_F6,
    F7 = VK_F7,
    F8 = VK_F8,
    F9 = VK_F9,
    F10 = VK_F10,
    F11 = VK_F11,
    F12 = VK_F12,
    F13 = VK_F13,
    F14 = VK_F14,
    F15 = VK_F15,
    F16 = VK_F16,
    F17 = VK_F17,
    F18 = VK_F18,
    F19 = VK_F19,
    F20 = VK_F20,
    F21 = VK_F21,
    F22 = VK_F22,
    F23 = VK_F23,
    F24 = VK_F24,

    // Lock keys
    NumLock = VK_NUMLOCK,
    ScrollLock = VK_SCROLL,

    // Left/right modifiers
    LeftShift = VK_LSHIFT,
    RightShift = VK_RSHIFT,
    LeftControl = VK_LCONTROL,
    RightControl = VK_RCONTROL,
    LeftAlt = VK_LMENU,
    RightAlt = VK_RMENU,

    // Browser keys
    BrowserBack = VK_BROWSER_BACK,
    BrowserForward = VK_BROWSER_FORWARD,
    BrowserRefresh = VK_BROWSER_REFRESH,
    BrowserStop = VK_BROWSER_STOP,
    BrowserSearch = VK_BROWSER_SEARCH,
    BrowserFavorites = VK_BROWSER_FAVORITES,
    BrowserHome = VK_BROWSER_HOME,

    // Media / volume keys
    VolumeMute = VK_VOLUME_MUTE,
    VolumeDown = VK_VOLUME_DOWN,
    VolumeUp = VK_VOLUME_UP,
    MediaNextTrack = VK_MEDIA_NEXT_TRACK,
    MediaPreviousTrack = VK_MEDIA_PREV_TRACK,
    MediaStop = VK_MEDIA_STOP,
    MediaPlayPause = VK_MEDIA_PLAY_PAUSE,

    // Launch keys
    LaunchMail = VK_LAUNCH_MAIL,
    LaunchMediaSelect = VK_LAUNCH_MEDIA_SELECT,
    LaunchApp1 = VK_LAUNCH_APP1,
    LaunchApp2 = VK_LAUNCH_APP2,

    // OEM / punctuation keys
    Oem1 = VK_OEM_1,
    OemPlus = VK_OEM_PLUS,
    OemComma = VK_OEM_COMMA,
    OemMinus = VK_OEM_MINUS,
    OemPeriod = VK_OEM_PERIOD,
    Oem2 = VK_OEM_2,
    Oem3 = VK_OEM_3,
    Oem4 = VK_OEM_4,
    Oem5 = VK_OEM_5,
    Oem6 = VK_OEM_6,
    Oem7 = VK_OEM_7,
    Oem8 = VK_OEM_8,
    Oem102 = VK_OEM_102,

    // Additional / legacy keys
    ProcessKey = VK_PROCESSKEY,
    Packet = VK_PACKET,
    Attn = VK_ATTN,
    CrSel = VK_CRSEL,
    ExSel = VK_EXSEL,
    EraseEof = VK_EREOF,
    Play = VK_PLAY,
    Zoom = VK_ZOOM,
    NoName = VK_NONAME,
    Pa1 = VK_PA1,
    OemClear = VK_OEM_CLEAR
};

class Input {
public:
    Input() = delete;
    static void Update();
	static bool IsKeyHeld(Key key);
    static bool IsKeyReleased(Key key);
    static bool IsKeyPressed(Key key);
private:
    inline static std::unordered_map<int, bool> s_CurrentKeys;
    inline static std::unordered_map<int, bool> s_PreviousKeys;
};