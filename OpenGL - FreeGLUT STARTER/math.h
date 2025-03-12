#pragma once

const float PI = 3.1415926;

/// <summary>
/// This function clamps a value between a minimum and maximum value.
/// </summary>
/// <param name="value"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
static float CLAMP(float value, float min, float max) {
    if (value < min) value = min;
    if (value > max) value = max;
    return value;
}