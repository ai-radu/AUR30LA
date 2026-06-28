// all vars will ref this .h eventually, idk Release v8.5.something
#pragma once
// #include <glad.h>
#include <cmath>
#include <cstddef>
#include <cassert>
// to be removed
#include <assert.h>
#define UI_ASSERT(_EXPR) assert(_EXPR)

#define PI 3.14159265358979323846f
inline float radians(float degrees) {return degrees * (PI / 180.0f);}
inline float degrees(float radians) {return radians * (180.0f / PI);}
struct Var {
    enum Dir : int {
        None  = -1,
        Left  = 0,
        Right = 1,
        Up    = 2,
        Down  = 3,
        COUNT
    };
    enum SortDir : int {
    Hold    = 0,
    Ascend  = 1, // 0->9, A->Z etc.
    Descend = 2  // 9->0, Z->A etc.
    };
};
struct vec1 {
    float                    x;
    constexpr vec1()         : x(0.0f) {}
    constexpr vec1(float _x) : x(_x) {}
    float& operator[] (size_t idx)       { UI_ASSERT(idx == 0); return ((float*)(void*)(char*)this)[idx]; }
    float  operator[] (size_t idx) const { UI_ASSERT(idx == 0); return ((const float*)(const void*)(const char*)this)[idx]; }
};
inline vec1  operator* (const vec1& a, const float b) { return vec1(a.x * b  ); }
inline vec1  operator* (const float a, const vec1& b) { return vec1(a   * b.x); }
inline vec1  operator/ (const vec1& a, const float b) { return vec1(a.x / b  ); }
inline vec1  operator+ (const vec1& a, const vec1& b) { return vec1(a.x + b.x); }
inline vec1  operator- (const vec1& a, const vec1& b) { return vec1(a.x - b.x); }
inline vec1  operator* (const vec1& a, const vec1& b) { return vec1(a.x * b.x); }
inline vec1  operator/ (const vec1& a, const vec1& b) { return vec1(a.x / b.x); }
inline vec1  operator+ (const vec1& a)                { return a; }
inline vec1  operator- (const vec1& a)                { return vec1(-a.x); }
inline vec1& operator*=(vec1& a, const float b)       { a.x *= b;   return a; }
inline vec1& operator/=(vec1& a, const float b)       { a.x /= b;   return a; }
inline vec1& operator+=(vec1& a, const vec1& b)       { a.x += b.x; return a; }
inline vec1& operator-=(vec1& a, const vec1& b)       { a.x -= b.x; return a; }
inline vec1& operator*=(vec1& a, const vec1& b)       { a.x *= b.x; return a; }
inline vec1& operator/=(vec1& a, const vec1& b)       { a.x /= b.x; return a; }
inline bool  operator==(const vec1& a, const vec1& b) { return a.x == b.x; }
inline bool  operator!=(const vec1& a, const vec1& b) { return a.x != b.x; }
struct vec1i {
    int                     x;
    constexpr vec1i()       : x(0) {}
    constexpr vec1i(int _x) : x(_x) {}
};
struct vec1ih {
    short                            x;
    constexpr vec1ih()               : x(0) {}
    constexpr vec1ih(short _x)       : x(_x) {}
    constexpr explicit vec1ih(const vec1& rhs) : x((short)rhs.x) {}
};
struct vec2 {
    float                              x, y;
    constexpr vec2()                   : x(0.0f), y(0.0f) {}
    constexpr vec2(float _x, float _y) : x(_x), y(_y) {}
    float& operator[] (size_t idx)       { UI_ASSERT(idx == 0 || idx == 1); return ((float*)(void*)(char*)this)[idx]; }
    float  operator[] (size_t idx) const { UI_ASSERT(idx == 0 || idx == 1); return ((const float*)(const void*)(const char*)this)[idx]; }
};
inline vec2  operator* (const vec2& a, const float b) { return vec2(a.x * b,   a.y * b  ); }
inline vec2  operator* (const float a, const vec2& b) { return vec2(a   * b.x, a   * b.y); }
inline vec2  operator/ (const vec2& a, const float b) { return vec2(a.x / b,   a.y / b  ); }
inline vec2  operator+ (const vec2& a, const vec2& b) { return vec2(a.x + b.x, a.y + b.y); }
inline vec2  operator- (const vec2& a, const vec2& b) { return vec2(a.x - b.x, a.y - b.y); }
inline vec2  operator* (const vec2& a, const vec2& b) { return vec2(a.x * b.x, a.y * b.y); }
inline vec2  operator/ (const vec2& a, const vec2& b) { return vec2(a.x / b.x, a.y / b.y); }
inline vec2  operator+ (const vec2& a)                { return a; }
inline vec2  operator- (const vec2& a)                { return vec2(-a.x, -a.y); }
inline vec2& operator*=(vec2& a, const float b)       { a.x *= b;   a.y *= b;   return a; }
inline vec2& operator/=(vec2& a, const float b)       { a.x /= b;   a.y /= b;   return a; }
inline vec2& operator+=(vec2& a, const vec2& b)       { a.x += b.x; a.y += b.y; return a; }
inline vec2& operator-=(vec2& a, const vec2& b)       { a.x -= b.x; a.y -= b.y; return a; }
inline vec2& operator*=(vec2& a, const vec2& b)       { a.x *= b.x; a.y *= b.y; return a; }
inline vec2& operator/=(vec2& a, const vec2& b)       { a.x /= b.x; a.y /= b.y; return a; }
inline bool  operator==(const vec2& a, const vec2& b) { return a.x == b.x && a.y == b.y; }
inline bool  operator!=(const vec2& a, const vec2& b) { return a.x != b.x || a.y != b.y; }
struct vec2i {
    int                             x, y;
    constexpr vec2i()               : x(0), y(0) {}
    constexpr vec2i(int _x, int _y) : x(_x), y(_y) {}
};
struct vec2ih {
    short                                      x, y;
    constexpr vec2ih()                         : x(0), y(0) {}
    constexpr vec2ih(short _x, short _y)       : x(_x), y(_y) {}
    constexpr explicit vec2ih(const vec2& rhs) : x((short)rhs.x), y((short)rhs.y) {}
};
struct vec3 {
    float                                        x, y, z;
    constexpr vec3()                             : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    float& operator[] (size_t idx)       { UI_ASSERT(idx == 0 || idx == 1 || idx == 2); return ((float*)(void*)(char*)this)[idx]; }
    float  operator[] (size_t idx) const { UI_ASSERT(idx == 0 || idx == 1 || idx == 2); return ((const float*)(const void*)(const char*)this)[idx]; }
};
inline vec3  operator* (const vec3& a, const float b) { return vec3(a.x * b,   a.y * b,   a.z * b  ); }
inline vec3  operator* (const float a, const vec3& b) { return vec3(a   * b.x, a   * b.y, a   * b.z); }
inline vec3  operator/ (const vec3& a, const float b) { return vec3(a.x / b,   a.y / b,   a.z / b  ); }
inline vec3  operator+ (const vec3& a, const vec3& b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline vec3  operator- (const vec3& a, const vec3& b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline vec3  operator* (const vec3& a, const vec3& b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
inline vec3  operator/ (const vec3& a, const vec3& b) { return vec3(a.x / b.x, a.y / b.y, a.z / b.z); }
inline vec3  operator+ (const vec3& a)                { return a; }
inline vec3  operator- (const vec3& a)                { return vec3(-a.x, -a.y, -a.z); }
inline vec3& operator*=(vec3& a, const float b)       { a.x *= b;   a.y *= b;   a.z *= b;   return a; }
inline vec3& operator/=(vec3& a, const float b)       { a.x /= b;   a.y /= b;   a.z /= b;   return a; }
inline vec3& operator+=(vec3& a, const vec3& b)       { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
inline vec3& operator-=(vec3& a, const vec3& b)       { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
inline vec3& operator*=(vec3& a, const vec3& b)       { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
inline vec3& operator/=(vec3& a, const vec3& b)       { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; }
inline bool  operator==(const vec3& a, const vec3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
inline bool  operator!=(const vec3& a, const vec3& b) { return a.x != b.x || a.y != b.y || a.z != b.z; }
struct vec3i {
    int x, y, z;
    constexpr vec3i()                       : x(0), y(0), z(0) {}
    constexpr vec3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};
struct vec3ih {
    short x, y, z;
    constexpr vec3ih()                             : x(0), y(0), z(0) {}
    constexpr vec3ih(short _x, short _y, short _z) : x(_x), y(_y), z(_z) {}
    constexpr explicit vec3ih(const vec3& rhs) : x((short)rhs.x), y((short)rhs.y), z((short)rhs.z) {}
};
struct vec4 {
    float                                        x, y, z, w;
    constexpr vec4()                             : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    float& operator[] (size_t idx)       { UI_ASSERT(idx == 0 || idx == 1 || idx == 2 || idx == 3); return ((float*)(void*)(char*)this)[idx]; }
    float  operator[] (size_t idx) const { UI_ASSERT(idx == 0 || idx == 1 || idx == 2 || idx == 3); return ((const float*)(const void*)(const char*)this)[idx]; }
};
inline vec4  operator* (const vec4& a, const float b) { return vec4(a.x * b,   a.y * b,   a.z * b,   a.w * b  ); }
inline vec4  operator* (const float a, const vec4& b) { return vec4(a   * b.x, a   * b.y, a   * b.z, a   * b.w); }
inline vec4  operator/ (const vec4& a, const float b) { return vec4(a.x / b,   a.y / b,   a.z / b,   a.w / b  ); }
inline vec4  operator+ (const vec4& a, const vec4& b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline vec4  operator- (const vec4& a, const vec4& b) { return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline vec4  operator* (const vec4& a, const vec4& b) { return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
inline vec4  operator/ (const vec4& a, const vec4& b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
inline vec4  operator+ (const vec4& a)                { return a; }
inline vec4  operator- (const vec4& a)                { return vec4(-a.x, -a.y, -a.z, -a.w); }
inline vec4& operator*=(vec4& a, const float b)       { a.x *= b;   a.y *= b;   a.z *= b;   a.w *= b;   return a; }
inline vec4& operator/=(vec4& a, const float b)       { a.x /= b;   a.y /= b;   a.z /= b;   a.w /= b;   return a; }
inline vec4& operator+=(vec4& a, const vec4& b)       { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }
inline vec4& operator-=(vec4& a, const vec4& b)       { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }
inline vec4& operator*=(vec4& a, const vec4& b)       { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; }
inline vec4& operator/=(vec4& a, const vec4& b)       { a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; return a; }
inline bool  operator==(const vec4& a, const vec4& b) { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
inline bool  operator!=(const vec4& a, const vec4& b) { return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w; }
struct vec4i {
    int                                             x, y, z, w;
    constexpr vec4i()                               : x(0), y(0), z(0), w(0) {}
    constexpr vec4i(int _x, int _y, int _z, int _w) : x(_x), y(_y), z(_z), w(_w) {}
};
struct vec4ih {
    short                                                    x, y, z, w;
    constexpr vec4ih()                                       : x(0), y(0), z(0), w(0) {}
    constexpr vec4ih(short _x, short _y, short _z, short _w) : x(_x), y(_y), z(_z), w(_w) {}
    constexpr explicit vec4ih(const vec4& rhs) : x((short)rhs.x), y((short)rhs.y), z((short)rhs.z), w((short)rhs.w) {}
};
struct m4 {
    float data[4][4];
    m4() {for (int y = 0; y < 4; y++) {for (int x = 0; x < 4; x++) {data[y][x] = 0.0f;}}}
    m4(float diagonal) {
        for (int y = 0; y < 4; y++) {for (int x = 0; x < 4; x++) {data[y][x] = 0.0f;}}
        data[0][0] = diagonal;
        data[1][1] = diagonal;
        data[2][2] = diagonal;
        data[3][3] = diagonal;
    }
    float* operator[](size_t i) {return data[i];}
    const float* operator[](size_t i) const {return data[i];}
    static m4 identity() {return m4(1.0f);}
};
// m4 X multiplication
inline m4 operator*(const m4& a, const m4& b){
    m4 result;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result[row][col] =
                a[row][0] * b[0][col] +
                a[row][1] * b[1][col] +
                a[row][2] * b[2][col] +
                a[row][3] * b[3][col];
        }
    }
    return result;
}
// length
inline float length(const vec3& a) {return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);}
// normalize
inline vec3 normalize(const vec3& a) {
    float len = length(a);
    if (len <= 0.0f) return {};
    return a / len;
}
// dot
inline float dot(const vec3& a, const vec3& b) {return a.x * b.x + a.y * b.y + a.z * b.z;}
// angle
inline float angle(const vec3& a, const vec3& b) {
    float d = dot(normalize(a), normalize(b));
    d = fmaxf(-1.0f, fminf(1.0f, d));
    return acosf(d);
}
// cross
inline vec3 cross(const vec3& a, const vec3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
// rotate
inline vec3 rotate(const vec3& a, float angle, const vec3& axis) {
    vec3 n = normalize(axis);
    float c = cosf(angle);
    float s = sinf(angle);
    return a * c + cross(n, a) * s + n * dot(n, a) * (1.0f - c);
}
// lookAt
inline m4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
    vec3 f = normalize(center - eye);
    vec3 r = normalize(cross(f, up));
    vec3 u = cross(r, f);
    m4 result = m4::identity();
    result[0][0] = r.x;
    result[1][0] = r.y;
    result[2][0] = r.z;
    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[0][2] = -f.x;
    result[1][2] = -f.y;
    result[2][2] = -f.z;
    result[3][0] = -dot(r, eye);
    result[3][1] = -dot(u, eye);
    result[3][2] = dot(f, eye);
    return result;
}
// perspective
inline m4 perspective(float fovy, float aspect, float zNear, float zFar) {
    float tanHalfFovy = tanf(fovy / 2.0f);
    m4 result = {};
    result[0][0] = 1.0f / (aspect * tanHalfFovy);
    result[1][1] = 1.0f / tanHalfFovy;
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    return result;
}