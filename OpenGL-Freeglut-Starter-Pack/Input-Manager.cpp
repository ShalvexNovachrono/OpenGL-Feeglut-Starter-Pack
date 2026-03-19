#include "Input-Manager.h"

CDeltaInputAction::~CDeltaInputAction() {
    keyPairs.Clear();
}

void CDeltaInputAction::SetDisabled(bool value) {
    disabled = value;
}

bool CDeltaInputAction::isDisabled() const {
    return disabled;
}

void CDeltaInputAction::AddKeyPairs(KeyPairs pairs) {
    keyPairs.Append(pairs);   
}

float CDeltaInputAction::GetDelta(CInputManager* inputManager, float& deltaTime) {
    if (disabled) return 0.0f;

    bool pos = false, neg = false;
    for (int i = 0; i < keyPairs.Size(); i++) {
        const auto& kp = keyPairs[i];
        if (inputManager->IsDown(kp.keyA)) pos = true;
        else if (inputManager->IsDown(kp.keyB)) neg = true;
    }

    if (pos) {
        keyPairDelta += sensitivity * deltaTime;
    }
    else if (neg) {
        keyPairDelta -= sensitivity * deltaTime;
    }
    else if (keyPairDelta != 0.0f) {
        float s = (keyPairDelta > 0.0f ? 1.0f : -1.0f);
        keyPairDelta -= s * sensitivity * deltaTime;
        if (abs(keyPairDelta) < (sensitivity * deltaTime * 1.1f)) keyPairDelta = 0.0f;
    }

    keyPairDelta = Clamp(keyPairDelta, -1.0f, 1.0f);
    return keyPairDelta;
}

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

    auto& entries = deltaInputActions.GetEntries();
    for (int i = 0; i < entries.Size(); i++) {
        entries[i].value.GetDelta(this, deltaTime);
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

void CInputManager::AddDeltaInputAction(string actionName, KeyPairs pairs) {
    CDeltaInputAction* action = deltaInputActions.GetPtr(actionName);
    if (action) {
        action->AddKeyPairs(pairs);
    } else {
        CDeltaInputAction newAction;
        newAction.AddKeyPairs(pairs);
        deltaInputActions.Add(actionName, newAction);
    }
}

void CInputManager::SetDeltaInputSensitivity(string actionName, float sensitivity) {
    CDeltaInputAction* action = deltaInputActions.GetPtr(actionName);
    if (action) {
        action->SetSensitivity(sensitivity);
    }
}

float CInputManager::GetDeltaInputAction(string actionName) {
    CDeltaInputAction* action = deltaInputActions.GetPtr(actionName);
    if (action) {
        return action->GetCurrentDelta();
    }
    return 0.0f;
}

void CInputManager::SetCursorVisible(bool visible) {
    if (visible) {
        glutSetCursor(GLUT_CURSOR_INHERIT);
    } else {
        glutSetCursor(GLUT_CURSOR_NONE);
    }
}

void CInputManager::SetCursorStyle(int cursorStyle) {
    glutSetCursor(cursorStyle);
}

void CInputManager::SetCursorRightArrow() {
    glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
}

void CInputManager::SetCursorLeftArrow() {
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

void CInputManager::SetCursorInfo() {
    glutSetCursor(GLUT_CURSOR_INFO);
}

void CInputManager::SetCursorDestroy() {
    glutSetCursor(GLUT_CURSOR_DESTROY);
}

void CInputManager::SetCursorHelp() {
    glutSetCursor(GLUT_CURSOR_HELP);
}

void CInputManager::SetCursorCycle() {
    glutSetCursor(GLUT_CURSOR_CYCLE);
}

void CInputManager::SetCursorSpray() {
    glutSetCursor(GLUT_CURSOR_SPRAY);
}

void CInputManager::SetCursorWait() {
    glutSetCursor(GLUT_CURSOR_WAIT);
}

void CInputManager::SetCursorText() {
    glutSetCursor(GLUT_CURSOR_TEXT);
}

void CInputManager::SetCursorCrosshair() {
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
}

void CInputManager::SetCursorNone() {
    glutSetCursor(GLUT_CURSOR_NONE);
}

void CInputManager::SetCursorInherit() {
    glutSetCursor(GLUT_CURSOR_INHERIT);
}
