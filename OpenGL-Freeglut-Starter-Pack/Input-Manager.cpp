#include "Input-Manager.h"

CInputManager::CInputManager(float& DeltaTime) : deltaTime(DeltaTime) {
    keyboardKeys.Reserve(maxKeyboardKeys);
    for (int i = 0; i < maxKeyboardKeys; i++) {
        keyboardKeys.Append(ButtonState{});
    }

    mouseKeys.Reserve(maxMouseKeys);
    for (int i = 0; i < maxMouseKeys; i++) {
        mouseKeys.Append(ButtonState{});
    }
}

void CInputManager::BeginFrame() {
    mouseDelta = mousePosition - mouseLastPosition;
    mouseLastPosition = mousePosition;

    for (int i = 0; i < keyboardKeys.Size(); i++) {
        keyboardKeys[i].previous = keyboardKeys[i].current;
    }

    for (int i = 0; i < mouseKeys.Size(); i++) {
        mouseKeys[i].previous = mouseKeys[i].current;
    }

    mouseWheelDelta = 0;
}

void CInputManager::SetKeyState(int key, bool isDown, Vec2 cursorPosition, MouseMovementState state) {
    key = ClampKey(key);
    if (key < 0) return;
    if (key >= keyboardKeys.Size()) return;

    keyboardKeys[key].current = isDown;
    mousePosition = cursorPosition;
    currentMouseMovementState = state;
}

bool CInputManager::IsDown(int key) const {
    key = ClampKey(key);
    if (key < 0) return false;
    if (key >= keyboardKeys.Size()) return false;

    return keyboardKeys[key].current;
}

bool CInputManager::WasPressed(int key) const {
    key = ClampKey(key);
    if (key < 0) return false;
    if (key >= keyboardKeys.Size()) return false;

    return keyboardKeys[key].Pressed();
}

bool CInputManager::WasReleased(int key) const {
    key = ClampKey(key);
    if (key < 0) return false;
    if (key >= keyboardKeys.Size()) return false;

    return keyboardKeys[key].Released();
}

void CInputManager::SetMousePosition(Vec2 position, MouseMovementState state) {
    mousePosition = position;
    currentMouseMovementState = state;
}

void CInputManager::SetMouseButtonState(int key, bool isDown, Vec2 cursorPosition, MouseMovementState state) {
    key = ClampMouseKey(key);
    if (key < 0) return;
    if (key >= mouseKeys.Size()) return;

    mouseKeys[key].current = isDown;
    mousePosition = cursorPosition;
    currentMouseMovementState = state;
}

void CInputManager::AddMouseWheelDelta(int delta, Vec2 cursorPosition) {
    mouseWheelDelta += delta;
    mousePosition = cursorPosition;
    currentMouseMovementState = MouseMovementState::MouseScrollWheel;
}

Vec2 CInputManager::GetMousePosition() const {
    return mousePosition;
}

bool CInputManager::IsMouseButtonDown(int key) const {
    key = ClampMouseKey(key);
    if (key < 0) return false;
    if (key >= mouseKeys.Size()) return false;

    return mouseKeys[key].current;
}

bool CInputManager::WasMouseButtonPressed(int key) const {
    key = ClampMouseKey(key);
    if (key < 0) return false;
    if (key >= mouseKeys.Size()) return false;

    return mouseKeys[key].Pressed();
}

bool CInputManager::WasMouseButtonReleased(int key) const {
    key = ClampMouseKey(key);
    if (key < 0) return false;
    if (key >= mouseKeys.Size()) return false;

    return mouseKeys[key].Released();
}

Vec2 CInputManager::GetMouseDelta() const {    
    return mouseDelta;
}

MouseMovementState CInputManager::GetMouseMovementState() const {
    return currentMouseMovementState;
}

string CInputManager::GetMouseMovementStateString() const {
    switch (currentMouseMovementState) {
    case MouseMovementState::MouseClick: return "MouseClick";
    case MouseMovementState::MouseMotion: return "MouseMotion";
    case MouseMovementState::MousePassiveMotion: return "MousePassiveMotion";
    case MouseMovementState::MouseScrollWheel: return "MouseScrollWheel";
    case MouseMovementState::KeyboardPress: return "KeyboardPress";
    default: return "Unknown";
    }
}

int CInputManager::GetMouseWheelDelta() const {
    return mouseWheelDelta;
}
