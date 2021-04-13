#pragma once

#include <StraveEngine/System/Export.hpp>


namespace Strave 
{
    class STRAVE_CONTROL_API Keyboard abstract final
    {
    public:
        enum class Key
        {
            Undefined = -1, // Unhandled key
            A = 0,          // The A key
            B,              // The B key
            C,              // The C key
            D,              // The D key
            E,              // The E key
            F,              // The F key
            G,              // The G key
            H,              // The H key
            I,              // The I key
            J,              // The J key
            K,              // The K key
            L,              // The L key
            M,              // The M key
            N,              // The N key
            O,              // The O key
            P,              // The P key
            Q,              // The Q key
            R,              // The R key
            S,              // The S key
            T,              // The T key
            U,              // The U key
            V,              // The V key
            W,              // The W key
            X,              // The X key
            Y,              // The Y key
            Z,              // The Z key
            Num0,           // The 0 key
            Num_1,          // The 1 key
            Num_2,          // The 2 key
            Num_3,          // The 3 key
            Num_4,          // The 4 key
            Num_5,          // The 5 key
            Num_6,          // The 6 key
            Num_7,          // The 7 key
            Num_8,          // The 8 key
            Num_9,          // The 9 key
            Escape,         // The Escape key
            L_Control,      // The left Control key
            L_Shift,        // The left Shift key
            L_Alt,          // The left Alt key
            L_System,       // The left OS key
            R_Control,      // The right Control key
            R_Shift,        // The right Shift key
            R_Alt,          // The right Alt key
            R_System,       // The right OS key
            Menu,           // The Menu key
            L_Bracket,      // The [ key
            R_Bracket,      // The ] key
            Semicolon,      // The ; key
            Comma,          // The , key
            Period,         // The . key
            Quote,          // The ' key
            Slash,          // The / key
            Backslah,       // The \ key
            Tidle,          // The ~ key
            Equal,          // The = key
            Hypen,          // The - key (hyphen)
            Space,          // The Space key
            Enter,          // The Enter/Return keys
            Backspace,      // The Backspace key
            Tab,            // The Tabulation key
            Page_Up,        // The Page up key
            Page_Down,      // The Page down key
            End,            // The End key
            Home,           // The Home key
            Insert,         // The Insert key
            Delete,         // The Delete key
            Add,            // The + key
            Substract,      // The - key (minus, usually from numpad)
            Multiply,       // The * key
            Divide,         // The / key
            Left,           // Left arrow
            Right,          // Right arrow
            Up,             // Up arrow
            Down,           // Down arrow
            Numpad_0,       // The numpad 0 key
            Numpad_1,       // The numpad 1 key
            Numpad_2,       // The numpad 2 key
            Numpad_3,       // The numpad 3 key
            Numpad_4,       // The numpad 4 key
            Numpad_5,       // The numpad 5 key
            Numpad_6,       // The numpad 6 key
            Numpad_7,       // The numpad 7 key
            Numpad_8,       // The numpad 8 key
            Numpad_9,       // The numpad 9 key
            F1,             // The F1 key
            F2,             // The F2 key
            F3,             // The F3 key
            F4,             // The F4 key
            F5,             // The F5 key
            F6,             // The F6 key
            F7,             // The F7 key
            F8,             // The F8 key
            F9,             // The F9 key
            F10,            // The F10 key
            F11,            // The F11 key
            F12,            // The F12 key
            F13,            // The F13 key
            F14,            // The F14 key
            F15,            // The F15 key
            Pause           // The Pause key
        };

    public:
        static bool IsKeyPressed(Keyboard::Key key);
    };
}
