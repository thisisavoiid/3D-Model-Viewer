#pragma once

struct Color {
    float r, g, b, a;

    /// <summary>
    /// Constructs a Color with the specified red, green, blue, and optional alpha components.
    /// </summary>
    /// <param name="r">
    /// The red component (0.0 – 1.0).
    /// </param>
    /// <param name="g">
    /// The green component (0.0 – 1.0).
    /// </param>
    /// <param name="b">
    /// The blue component (0.0 – 1.0).
    /// </param>
    /// <param name="a">
    /// The alpha component (0.0 – 1.0). Defaults to 1.0.
    /// </param>
    Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {
    }
};