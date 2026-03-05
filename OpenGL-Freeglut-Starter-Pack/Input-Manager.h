#ifndef InputManager
#define InputManager

#include "main.h"
#include "Array.h"
#include "Maths.h"

struct ButtonState {
    bool current = false;
    bool previous = false;

    bool Pressed() const { return current && !previous; }
    bool Released() const { return !current && previous; }
    bool Held() const { return current && previous; }
};

enum class MouseMovementState {
    MouseClick,
    MouseMotion,
    MousePassiveMotion,
    MouseScrollWheel,
    KeyboardPress
};

class CInputManager {
private:
    float& deltaTime;
    
    static constexpr int maxMouseKeys = 3;
    static constexpr int maxKeyboardKeys = 512;

    CArray<ButtonState> keyboardKeys;
    CArray<ButtonState> mouseKeys;
    
    int mouseWheelDelta = 0;
    Vec2 mousePosition, mouseLastPosition, mouseDelta;
    MouseMovementState currentMouseMovementState = MouseMovementState::MousePassiveMotion;

    static int ClampKey(int key) {
        return (key < 0) ? -1 : (key >= maxKeyboardKeys ? -1 : key);
    }

    static int ClampMouseKey(int key) {
        return (key < 0) ? -1 : (key >= maxMouseKeys ? -1 : key);
    }

public:
    CInputManager(float& DeltaTime);

    void BeginFrame();

    void SetKeyState(int key, bool isDown, Vec2 cursorPosition, MouseMovementState state);

    bool IsDown(int key) const;
    bool WasPressed(int key) const;
    bool WasReleased(int key) const;

    void SetMousePosition(Vec2 position, MouseMovementState state);
    void SetMouseButtonState(int key, bool isDown, Vec2 cursorPosition, MouseMovementState state);
    void AddMouseWheelDelta(int delta, Vec2 cursorPosition);

    Vec2 GetMousePosition() const;
    bool IsMouseButtonDown(int key) const;
    bool WasMouseButtonPressed(int key) const;
    bool WasMouseButtonReleased(int key) const;
    Vec2 GetMouseDelta() const;

    /// <summary>
    /// Returns the current state of mouse interaction.
    /// </summary>
    MouseMovementState GetMouseMovementState() const;

    string GetMouseMovementStateString() const;

    int GetMouseWheelDelta() const;
};

#endif
