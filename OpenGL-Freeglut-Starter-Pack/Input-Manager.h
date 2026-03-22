#ifndef InputManager
#define InputManager

#include "main.h"
#include "Array.h"
#include "Key-Value.h"
#include "Maths.h"

/// <summary>
/// Represents the state of a button or key, tracking its current and previous frame states.
/// </summary>
struct ButtonState {
    bool current = false;
    bool previous = false;

    /// <summary>
    /// Returns true if the button was pressed in the current frame.
    /// </summary>
    /// <returns>True if pressed this frame.</returns>
    bool Pressed() const { return current && !previous; }

    /// <summary>
    /// Returns true if the button was released in the current frame.
    /// </summary>
    /// <returns>True if released this frame.</returns>
    bool Released() const { return !current && previous; }

    /// <summary>
    /// Returns true if the button is currently being held down.
    /// </summary>
    /// <returns>True if held down.</returns>
    bool Held() const { return current && previous; }
};

/// <summary>
/// Defines the different types of mouse and keyboard interaction events.
/// </summary>
enum class MouseMovementState {
    MouseClick,
    MouseMotion,
    MousePassiveMotion,
    MouseScrollWheel,
    KeyboardPress
};

/// <summary>
/// Represents a pair of keys used for bipolar input (e.g., positive and negative axes).
/// </summary>
struct KeyPairs {
    int keyA, keyB;
};

class CInputManager;

/// <summary>
/// Base class for input actions that calculate a delta value based on input state.
/// </summary>
class CBaseInputActionType {
public:
    virtual ~CBaseInputActionType() = default;
    CBaseInputActionType() = default;
    
    /// <summary>
    /// Calculates the delta value for the action.
    /// </summary>
    /// <param name="inputManager">Pointer to the input manager.</param>
    /// <param name="deltaTime">Reference to the frame delta time.</param>
    /// <returns>The calculated delta value.</returns>
    virtual float GetDelta(CInputManager* inputManager, float& deltaTime) = 0;
};

/// <summary>
/// An input action that calculates a smooth delta value between -1 and 1 based on key pairs.
/// </summary>
class CDeltaInputAction : public CBaseInputActionType {
    CArray<KeyPairs> keyPairs;
    float keyPairDelta = 0.0f;
    float sensitivity = 5.0f; 
    bool disabled = false;
public:    
    CDeltaInputAction() = default;   
    ~CDeltaInputAction() override;
    
    /// <summary>
    /// Sets whether the input action is disabled.
    /// </summary>
    /// <param name="value">True to disable, false to enable.</param>
    void SetDisabled(bool value);

    /// <summary>
    /// Sets the sensitivity of the input action.
    /// </summary>
    /// <param name="value">The sensitivity value.</param>
    void SetSensitivity(float value) { sensitivity = value; }
    
    /// <summary>
    /// Checks if the input action is disabled.
    /// </summary>
    /// <returns>True if disabled.</returns>
    bool isDisabled() const;
    
    /// <summary>
    /// Adds a pair of keys to influence this delta action.
    /// </summary>
    /// <param name="pairs">The key pair (positive and negative keys).</param>
    void AddKeyPairs(KeyPairs pairs);
    
    /// <summary>
    /// Updates and returns the current delta value based on key states and sensitivity.
    /// </summary>
    /// <param name="inputManager">Pointer to the input manager.</param>
    /// <param name="deltaTime">Reference to the frame delta time.</param>
    /// <returns>The updated delta value.</returns>
    float GetDelta(CInputManager* inputManager, float& deltaTime) override;

    /// <summary>
    /// Returns the current delta value without updating it.
    /// </summary>
    /// <returns>The current delta value.</returns>
    float GetCurrentDelta() const { return keyPairDelta; }
};


/// <summary>
/// Manages input states for keyboard and mouse, providing access to button states, mouse movement, and virtual axes.
/// </summary>
class CInputManager {
private:
    float& deltaTime;
    
    static constexpr int maxMouseKeys = 3;
    static constexpr int maxKeyboardKeys = 512;

    CKeyValue<string, CDeltaInputAction> deltaInputActions;
    
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
    /// <summary>
    /// Initializes a new instance of the CInputManager class.
    /// </summary>
    /// <param name="DeltaTime">Reference to the global delta time.</param>
    CInputManager(float& DeltaTime);

    /// <summary>
    /// Updates internal states at the beginning of a frame. Should be called once per frame.
    /// </summary>
    void BeginFrame();

    /// <summary>
    /// Updates the state of a keyboard key.
    /// </summary>
    /// <param name="key">The key code.</param>
    /// <param name="isDown">True if the key is pressed.</param>
    /// <param name="cursorPosition">The mouse position at the time of the event.</param>
    /// <param name="state">The movement state associated with the event.</param>
    void SetKeyState(int key, bool isDown, Vec2 cursorPosition, MouseMovementState state);

    /// <summary>
    /// Checks if a key is currently held down.
    /// </summary>
    /// <param name="key">The key code.</param>
    /// <returns>True if the key is down.</returns>
    bool IsDown(int key) const;

    /// <summary>
    /// Checks if a key was just pressed this frame.
    /// </summary>
    /// <param name="key">The key code.</param>
    /// <returns>True if the key was just pressed.</returns>
    bool WasPressed(int key) const;

    /// <summary>
    /// Checks if a key was just released this frame.
    /// </summary>
    /// <param name="key">The key code.</param>
    /// <returns>True if the key was just released.</returns>
    bool WasReleased(int key) const;

    /// <summary>
    /// Updates the mouse position.
    /// </summary>
    /// <param name="position">The new mouse position.</param>
    /// <param name="state">The movement state associated with the change.</param>
    void SetMousePosition(Vec2 position, MouseMovementState state);

    /// <summary>
    /// Updates the state of a mouse button.
    /// </summary>
    /// <param name="key">The mouse button index (0 = left, 1 = middle, 2 = right).</param>
    /// <param name="isDown">True if the button is pressed.</param>
    /// <param name="cursorPosition">The mouse position at the time of the event.</param>
    /// <param name="state">The movement state associated with the event.</param>
    void SetMouseButtonState(int key, bool isDown, Vec2 cursorPosition, MouseMovementState state);

    /// <summary>
    /// Accumulates mouse wheel movement.
    /// </summary>
    /// <param name="delta">The scroll amount.</param>
    /// <param name="cursorPosition">The mouse position at the time of the scroll.</param>
    void AddMouseWheelDelta(int delta, Vec2 cursorPosition);

    /// <summary>
    /// Returns the current mouse position.
    /// </summary>
    /// <returns>The mouse position as a Vec2.</returns>
    Vec2 GetMousePosition() const;

    /// <summary>
    /// Checks if a mouse button is currently held down.
    /// </summary>
    /// <param name="key">The mouse button index (0 = left, 1 = middle, 2 = right).</param>
    /// <returns>True if the mouse button is down.</returns>
    bool IsMouseButtonDown(int key) const;

    /// <summary>
    /// Checks if a mouse button was just pressed this frame.
    /// </summary>
    /// <param name="key">The mouse button index.</param>
    /// <returns>True if the button was just pressed.</returns>
    bool WasMouseButtonPressed(int key) const;

    /// <summary>
    /// Checks if a mouse button was just released this frame.
    /// </summary>
    /// <param name="key">The mouse button index.</param>
    /// <returns>True if the button was just released.</returns>
    bool WasMouseButtonReleased(int key) const;

    /// <summary>
    /// Returns the mouse movement delta since the last frame.
    /// </summary>
    /// <returns>The mouse delta as a Vec2.</returns>
    Vec2 GetMouseDelta() const;

    /// <summary>
    /// Returns the current state of mouse interaction.
    /// </summary>
    /// <returns>The current MouseMovementState.</returns>
    MouseMovementState GetMouseMovementState() const;

    /// <summary>
    /// Returns a string representation of the current mouse movement state.
    /// </summary>
    /// <returns>A string describing the mouse state.</returns>
    string GetMouseMovementStateString() const;

    /// <summary>
    /// Returns the accumulated mouse wheel scroll delta for the current frame.
    /// </summary>
    /// <returns>The scroll delta.</returns>
    int GetMouseWheelDelta() const;
    
    /// <summary>
    /// Adds or updates a delta input action (virtual axis) controlled by key pairs.
    /// </summary>
    /// <param name="actionName">The name of the action.</param>
    /// <param name="pairs">The key pair that controls the action.</param>
    void AddDeltaInputAction(string actionName, KeyPairs pairs);

    /// <summary>
    /// Sets the sensitivity for a specific delta input action.
    /// </summary>
    /// <param name="actionName">The name of the action.</param>
    /// <param name="sensitivity">The new sensitivity value.</param>
    void SetDeltaInputSensitivity(string actionName, float sensitivity);

    /// <summary>
    /// Returns the current value of a delta input action.
    /// </summary>
    /// <param name="actionName">The name of the action.</param>
    /// <returns>The delta value (typically between -1 and 1).</returns>
    float GetDeltaInputAction(string actionName);

    /// <summary>
    /// Sets the visibility of the mouse cursor.
    /// </summary>
    /// <param name="visible">True to make the cursor visible, false to hide it.</param>
    void SetCursorVisible(bool visible);

    /// <summary>
    /// Sets the style of the mouse cursor.
    /// </summary>
    /// <param name="cursorStyle">The GLUT cursor style constant.</param>
    void SetCursorStyle(int cursorStyle);

    /// <summary>
    /// Sets the mouse cursor to a right arrow.
    /// </summary>
    void SetCursorRightArrow();

    /// <summary>
    /// Sets the mouse cursor to a left arrow.
    /// </summary>
    void SetCursorLeftArrow();

    /// <summary>
    /// Sets the mouse cursor to an info icon.
    /// </summary>
    void SetCursorInfo();

    /// <summary>
    /// Sets the mouse cursor to a destroy icon.
    /// </summary>
    void SetCursorDestroy();

    /// <summary>
    /// Sets the mouse cursor to a help icon.
    /// </summary>
    void SetCursorHelp();

    /// <summary>
    /// Sets the mouse cursor to a cycle icon.
    /// </summary>
    void SetCursorCycle();

    /// <summary>
    /// Sets the mouse cursor to a spray icon.
    /// </summary>
    void SetCursorSpray();

    /// <summary>
    /// Sets the mouse cursor to a wait icon.
    /// </summary>
    void SetCursorWait();

    /// <summary>
    /// Sets the mouse cursor to a text (I-beam) icon.
    /// </summary>
    void SetCursorText();

    /// <summary>
    /// Sets the mouse cursor to a crosshair.
    /// </summary>
    void SetCursorCrosshair();

    /// <summary>
    /// Sets the mouse cursor to be invisible.
    /// </summary>
    void SetCursorNone();

    /// <summary>
    /// Sets the mouse cursor to inherit the default system cursor.
    /// </summary>
    void SetCursorInherit();
};

#endif
