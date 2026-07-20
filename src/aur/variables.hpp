#pragma once
// #include <glad.h>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <cassert>

#include <assert.h>
#define AEA(expr) assert(expr) // here ?
#define AEA_PARANOID(_EXPR)
#define AEA_USER_ERROR(_EXPR,_MSG)            do { if (!(_EXPR)) { if (UI::ErrorLog(_MSG)) { AEA((_EXPR) && _MSG); } } } while (0)               // Recoverable User Error
#define AEA_USER_ERROR_RET(_EXPR,_MSG)        do { if (!(_EXPR)) { if (UI::ErrorLog(_MSG)) { AEA((_EXPR) && _MSG); } return; } } while (0)       // Recoverable User Error
#define AEA_USER_ERROR_RETV(_EXPR,_RETV,_MSG) do { if (!(_EXPR)) { if (UI::ErrorLog(_MSG)) { AEA((_EXPR) && _MSG); } return _RETV; } } while (0) // Recoverable User Error
#define PI 3.14159265358979323846f

using c1  = bool;                         // 1 byte
using c8  = char;                         // 1 byte
using cc8 = const char;                   // 1 byte
using s8  = int8_t;     // signed char    // 1 byte
using u8  = uint8_t;    // unsigned char  // 1 byte
using c16 = short;                        // 2 byte
using s16 = int16_t;    // signed short   // 2 byte
using u16 = uint16_t;   // unsigned short // 2 byte
using c32 = int;                          // 4 byte
using s32 = int32_t;    // signed int     // 4 byte
using u32 = uint32_t;   // unsigned int   // 4 byte
using f32 = float;                        // 4 byte
using c64 = long;                         // 8 byte
using s64 = int64_t;    // signed long    // 8 byte
using u64 = uint64_t;   // unsigned long  // 8 byte
using f64 = double;                       // 8 byte
using f80 = long double;                  // 8 byte
constexpr s8   s8_MIN = -128;
constexpr s8   s8_MAX = 127;
constexpr u8   u8_MIN = 0;
constexpr u8   u8_MAX = 255;
constexpr s16 s16_MIN = -32768;
constexpr s16 s16_MAX = 32767;
constexpr u16 u16_MIN = 0;
constexpr u16 u16_MAX = 65535;
constexpr s32 s32_MIN = -2147483647 - 1;
constexpr s32 s32_MAX = 2147483647;
constexpr u32 u32_MIN = 0;
constexpr u32 u32_MAX = 4294967295U;
constexpr f32 f32_MIN = 1.17549435082228750796873653722224568e-38F;
constexpr f32 f32_MAX = 3.40282346638528859811704183484516925e+38F;
constexpr s64 s64_MIN = -9223372036854775807LL - 1;
constexpr s64 s64_MAX = 9223372036854775807LL;
constexpr u64 u64_MIN = 0;
constexpr u64 u64_MAX = 18446744073709551615ULL;
enum dataType_ {
    dataType_c8,     // char
    dataType_s8,     // signed char
    dataType_u8,     // unsigned char
    dataType_s16,    // signed short
    dataType_u16,    // unsigned short
    dataType_s32,    // signed int
    dataType_u32,    // unsigned int
    dataType_s64,    // signed long
    dataType_u64,    // unsigned long
    dataType_f32,    // float
    dataType_f64,    // double
    dataType_bool,   // c1
    dataType_string, // c8*
    dataType_COUNT
};
struct VAR {
    using Dir = c32;
    enum Dir_ {
        Dir_None  = -1,
        Dir_Left  = 0,
        Dir_Right = 1,
        Dir_Up    = 2,
        Dir_Down  = 3,
        Dir_COUNT
    };
    using SortDir = c32;
    enum SortDir_ {
        SortDir_Hold    = 0,
        SortDir_Ascend  = 1, // 0->9, A->Z etc.
        SortDir_Descend = 2  // 9->0, Z->A etc.
    };
};
struct v1 {
    f32 x;
    constexpr v1()         : x(0.0f) {}
    constexpr v1(float _x) : x(_x) {}
    f32& operator[] (size_t idx)       { AEA(idx == 0); return ((f32*)(void*)(c8*)this)[idx]; }
    f32  operator[] (size_t idx) const { AEA(idx == 0); return ((const f32*)(const void*)(const c8*)this)[idx]; }
};
constexpr v1  operator* (const v1& a, const f32 b) { return v1(a.x * b  ); }
constexpr v1  operator* (const f32 a, const v1& b) { return v1(a   * b.x); }
constexpr v1  operator/ (const v1& a, const f32 b) { return v1(a.x / b  ); }
constexpr v1  operator+ (const v1& a, const v1& b) { return v1(a.x + b.x); }
constexpr v1  operator- (const v1& a, const v1& b) { return v1(a.x - b.x); }
constexpr v1  operator* (const v1& a, const v1& b) { return v1(a.x * b.x); }
constexpr v1  operator/ (const v1& a, const v1& b) { return v1(a.x / b.x); }
constexpr v1  operator+ (const v1& a)              { return a; }
constexpr v1  operator- (const v1& a)              { return v1(-a.x); }
constexpr v1& operator*=(v1& a, const f32   b)     { a.x *= b;   return a; }
constexpr v1& operator/=(v1& a, const f32   b)     { a.x /= b;   return a; }
constexpr v1& operator+=(v1& a, const v1& b)       { a.x += b.x; return a; }
constexpr v1& operator-=(v1& a, const v1& b)       { a.x -= b.x; return a; }
constexpr v1& operator*=(v1& a, const v1& b)       { a.x *= b.x; return a; }
constexpr v1& operator/=(v1& a, const v1& b)       { a.x /= b.x; return a; }
constexpr c1  operator==(const v1& a, const v1& b) { return a.x == b.x; }
constexpr c1  operator!=(const v1& a, const v1& b) { return a.x != b.x; }
struct v1i {
    c32 x;
    constexpr v1i()       : x(0) {}
    constexpr v1i(c32 _x) : x(_x) {}
};
struct v1ih {
    c16 x;
    constexpr v1ih()       : x(0) {}
    constexpr v1ih(c16 _x) : x(_x) {}
    constexpr explicit v1ih(const v1& rhs) : x((c16)rhs.x) {}
};
struct v2 {
    f32 x, y;
    constexpr v2()               : x(0.0f), y(0.0f) {}
    constexpr v2(f32 _x, f32 _y) : x(_x), y(_y) {}
    f32& operator[] (size_t idx)       { AEA(idx == 0 || idx == 1); return ((f32*)(void*)(c8*)this)[idx]; }
    f32  operator[] (size_t idx) const { AEA(idx == 0 || idx == 1); return ((const f32*)(const void*)(const c8*)this)[idx]; }
};
constexpr v2  operator* (const v2& a, const f32 b) { return v2(a.x * b,   a.y * b  ); }
constexpr v2  operator* (const f32 a, const v2& b) { return v2(a   * b.x, a   * b.y); }
constexpr v2  operator/ (const v2& a, const f32 b) { return v2(a.x / b,   a.y / b  ); }
constexpr v2  operator+ (const v2& a, const v2& b) { return v2(a.x + b.x, a.y + b.y); }
constexpr v2  operator- (const v2& a, const v2& b) { return v2(a.x - b.x, a.y - b.y); }
constexpr v2  operator* (const v2& a, const v2& b) { return v2(a.x * b.x, a.y * b.y); }
constexpr v2  operator/ (const v2& a, const v2& b) { return v2(a.x / b.x, a.y / b.y); }
constexpr v2  operator+ (const v2& a)              { return a; }
constexpr v2  operator- (const v2& a)              { return v2(-a.x, -a.y); }
constexpr v2& operator*=(v2& a, const f32 b)       { a.x *= b;   a.y *= b;   return a; }
constexpr v2& operator/=(v2& a, const f32 b)       { a.x /= b;   a.y /= b;   return a; }
constexpr v2& operator+=(v2& a, const v2& b)       { a.x += b.x; a.y += b.y; return a; }
constexpr v2& operator-=(v2& a, const v2& b)       { a.x -= b.x; a.y -= b.y; return a; }
constexpr v2& operator*=(v2& a, const v2& b)       { a.x *= b.x; a.y *= b.y; return a; }
constexpr v2& operator/=(v2& a, const v2& b)       { a.x /= b.x; a.y /= b.y; return a; }
constexpr c1  operator==(const v2& a, const v2& b) { return a.x == b.x && a.y == b.y; }
constexpr c1  operator!=(const v2& a, const v2& b) { return a.x != b.x || a.y != b.y; }
struct v2i {
    c32 x, y;
    constexpr v2i()               : x(0), y(0) {}
    constexpr v2i(c32 _x, c32 _y) : x(_x), y(_y) {}
};
struct v2ih {
    c16 x, y;
    constexpr v2ih()                       : x(0), y(0) {}
    constexpr v2ih(c16 _x, c16 _y)         : x(_x), y(_y) {}
    constexpr explicit v2ih(const v2& rhs) : x((c16)rhs.x), y((c16)rhs.y) {}
};
struct v3 {
    f32 x, y, z;
    constexpr v3()                             : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr v3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    f32& operator[] (size_t idx)       { AEA(idx == 0 || idx == 1 || idx == 2); return ((f32*)(void*)(c8*)this)[idx]; }
    f32  operator[] (size_t idx) const { AEA(idx == 0 || idx == 1 || idx == 2); return ((const f32*)(const void*)(const c8*)this)[idx]; }
};
constexpr v3  operator* (const v3& a, const f32 b) { return v3(a.x * b,   a.y * b,   a.z * b  ); }
constexpr v3  operator* (const f32 a, const v3& b) { return v3(a   * b.x, a   * b.y, a   * b.z); }
constexpr v3  operator/ (const v3& a, const f32 b) { return v3(a.x / b,   a.y / b,   a.z / b  ); }
constexpr v3  operator+ (const v3& a, const v3& b) { return v3(a.x + b.x, a.y + b.y, a.z + b.z); }
constexpr v3  operator- (const v3& a, const v3& b) { return v3(a.x - b.x, a.y - b.y, a.z - b.z); }
constexpr v3  operator* (const v3& a, const v3& b) { return v3(a.x * b.x, a.y * b.y, a.z * b.z); }
constexpr v3  operator/ (const v3& a, const v3& b) { return v3(a.x / b.x, a.y / b.y, a.z / b.z); }
constexpr v3  operator+ (const v3& a)              { return a; }
constexpr v3  operator- (const v3& a)              { return v3(-a.x, -a.y, -a.z); }
constexpr v3& operator*=(v3& a, const f32 b)       { a.x *= b;   a.y *= b;   a.z *= b;   return a; }
constexpr v3& operator/=(v3& a, const f32 b)       { a.x /= b;   a.y /= b;   a.z /= b;   return a; }
constexpr v3& operator+=(v3& a, const v3& b)       { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
constexpr v3& operator-=(v3& a, const v3& b)       { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
constexpr v3& operator*=(v3& a, const v3& b)       { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
constexpr v3& operator/=(v3& a, const v3& b)       { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; }
constexpr c1  operator==(const v3& a, const v3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
constexpr c1  operator!=(const v3& a, const v3& b) { return a.x != b.x || a.y != b.y || a.z != b.z; }
struct v3i {
    c32 x, y, z;
    constexpr v3i()                       : x(0), y(0), z(0) {}
    constexpr v3i(c32 _x, c32 _y, c32 _z) : x(_x), y(_y), z(_z) {}
};
struct v3ih {
    c16 x, y, z;
    constexpr v3ih()                       : x(0), y(0), z(0) {}
    constexpr v3ih(c16 _x, c16 _y, c16 _z) : x(_x), y(_y), z(_z) {}
    constexpr explicit v3ih(const v3& rhs) : x((c16)rhs.x), y((c16)rhs.y), z((c16)rhs.z) {}
};
struct v4 {
    f32 x, y, z, w;
    constexpr v4()                               : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr v4(f32 _x, f32 _y, f32 _z, f32 _w) : x(_x), y(_y), z(_z), w(_w) {}
    f32& operator[] (size_t idx)       { AEA(idx == 0 || idx == 1 || idx == 2 || idx == 3); return ((f32*)(void*)(c8*)this)[idx]; }
    f32  operator[] (size_t idx) const { AEA(idx == 0 || idx == 1 || idx == 2 || idx == 3); return ((const f32*)(const void*)(const c8*)this)[idx]; }
};
constexpr v4  operator* (const v4& a, const f32 b) { return v4(a.x * b,   a.y * b,   a.z * b,   a.w * b  ); }
constexpr v4  operator* (const f32 a, const v4& b) { return v4(a   * b.x, a   * b.y, a   * b.z, a   * b.w); }
constexpr v4  operator/ (const v4& a, const f32 b) { return v4(a.x / b,   a.y / b,   a.z / b,   a.w / b  ); }
constexpr v4  operator+ (const v4& a, const v4& b) { return v4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
constexpr v4  operator- (const v4& a, const v4& b) { return v4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
constexpr v4  operator* (const v4& a, const v4& b) { return v4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
constexpr v4  operator/ (const v4& a, const v4& b) { return v4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
constexpr v4  operator+ (const v4& a)              { return a; }
constexpr v4  operator- (const v4& a)              { return v4(-a.x, -a.y, -a.z, -a.w); }
constexpr v4& operator*=(v4& a, const f32 b)       { a.x *= b;   a.y *= b;   a.z *= b;   a.w *= b;   return a; }
constexpr v4& operator/=(v4& a, const f32 b)       { a.x /= b;   a.y /= b;   a.z /= b;   a.w /= b;   return a; }
constexpr v4& operator+=(v4& a, const v4& b)       { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }
constexpr v4& operator-=(v4& a, const v4& b)       { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }
constexpr v4& operator*=(v4& a, const v4& b)       { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; }
constexpr v4& operator/=(v4& a, const v4& b)       { a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; return a; }
constexpr c1  operator==(const v4& a, const v4& b) { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
constexpr c1  operator!=(const v4& a, const v4& b) { return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w; }
struct v4i {
    c32 x, y, z, w;
    constexpr v4i()                               : x(0), y(0), z(0), w(0) {}
    constexpr v4i(c32 _x, c32 _y, c32 _z, c32 _w) : x(_x), y(_y), z(_z), w(_w) {}
};
struct v4ih {
    c16 x, y, z, w;
    constexpr v4ih()                                 : x(0), y(0), z(0), w(0) {}
    constexpr v4ih(c16 _x, short _y, c16 _z, c16 _w) : x(_x), y(_y), z(_z), w(_w) {}
    constexpr explicit v4ih(const v4& rhs) : x((c16)rhs.x), y((c16)rhs.y), z((c16)rhs.z), w((c16)rhs.w) {}
};
struct m4 {
    f32 data[4][4];
    m4() {for (c32 y = 0; y < 4; y++) {for (c32 x = 0; x < 4; x++) {data[y][x] = 0.0f;}}}
    m4(f32 diagonal) {
        for (c32 y = 0; y < 4; y++) {for (c32 x = 0; x < 4; x++) {data[y][x] = 0.0f;}}
        data[0][0] = diagonal;
        data[1][1] = diagonal;
        data[2][2] = diagonal;
        data[3][3] = diagonal;
    }
    f32* operator[](size_t i) {return data[i];}
    const f32* operator[](size_t i) const {return data[i];}
    static m4 identity() {return m4(1.0f);}
};
// m4 X multiplication
inline m4 operator*(const m4& a, const m4& b){
    m4 result;
    for (u32 row = 0; row < 4; row++) {
        for (c32 col = 0; col < 4; col++) {
            result[row][col] =
            a[row][0] * b[0][col] +
            a[row][1] * b[1][col] +
            a[row][2] * b[2][col] +
            a[row][3] * b[3][col];
        }
    }
    return result;
}
constexpr f32 vPow(f32 x, f32 y)                               { return powf(x, y); } // DragBehaviorT/SliderBehaviorT uses vPow with either f32/f64 and need the precision
constexpr f64 vPow(f64 x, f64 y)                               { return pow(x, y); }
constexpr f32 vLog(f32 x)                                      { return logf(x); }    // DragBehaviorT/SliderBehaviorT uses vLog with either f32/f64 and need the precision
constexpr f64 vLog(f64 x)                                      { return log(x); }
constexpr c32 vAbs(c32 x)                                      { return x < 0 ? -x : x; }
constexpr f32 vAbs(f32 x)                                      { return fabsf(x); }
constexpr f64 vAbs(f64 x)                                      { return fabs(x); }
constexpr f32 vSign(f32 x)                                     { return (x < 0.0f) ? -1.0f : (x > 0.0f) ? 1.0f : 0.0f; } // Sign operator - returns -1, 0 or 1 based on sign of argument
constexpr f64 vSign(f64 x)                                     { return (x < 0.0) ? -1.0 : (x > 0.0) ? 1.0 : 0.0; }
constexpr f32 vRsqrt(f32 x)                                    { return 1.0f / sqrtf(x); }
constexpr f64 vRsqrt(f64 x)                                    { return 1.0 / sqrt(x); }
template<typename T> constexpr T vMin(T a, T b)                { return (a < b) ? a : b; }
constexpr v2  vMin(const v2& a, const v2& b)                   { return { vMin(a.x, b.x), vMin(a.y, b.y) }; }
template<typename T> constexpr T vMax(T a, T b)                { return (a > b) ? a : b; }
constexpr v2  vMax(const v2& a, const v2& b)                   { return { vMax(a.x, b.x), vMax(a.y, b.y) }; }
template<typename T> constexpr T vClamp(T v, T mn, T mx)       { return (v < mn) ? mn : (v > mx) ? mx : v; }
constexpr v2  vClamp(const v2& v, const v2&mn, const v2&mx)    { return v2((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y); }
constexpr v2  vLerp(const v2& a, const v2& b, f32 t)           { return v2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
constexpr v2  vLerp(const v2& a, const v2& b, const v2& t)     { return v2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
constexpr v4  vLerp(const v4& a, const v4& b, f32 t)           { return v4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
constexpr f32 vLerp(f32 a, f32 b, f32 t)                       { return a + (b - a) * t; }
template<typename T> void vSwap(T& a, T& b)                    { T tmp = a; a = b; b = tmp; }
template<typename T> T vAddClampOverflow(T a, T b, T mn, T mx) { if (b < 0 && (a < mn - b)) return mn; if (b > 0 && (a > mx - b)) return mx; return a + b; }
template<typename T> T vSubClampOverflow(T a, T b, T mn, T mx) { if (b > 0 && (a < mn + b)) return mn; if (b < 0 && (a > mx + b)) return mx; return a - b; }
constexpr f32 vSaturate(f32 f)                                 { return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
constexpr f32 vLengthSqr(const v2& lhs)                        { return (lhs.x * lhs.x) + (lhs.y * lhs.y); }
constexpr f32 vLengthSqr(const v4& lhs)                        { return (lhs.x * lhs.x) + (lhs.y * lhs.y) + (lhs.z * lhs.z) + (lhs.w * lhs.w); }
constexpr f32 vInvLength(const v2& lhs, f32 fail_value)        { f32 d = (lhs.x * lhs.x) + (lhs.y * lhs.y); if (d > 0.0f) return vRsqrt(d); return fail_value; }
constexpr f32 vTrunc(f32 f)                                    { return (f32)(c32)(f); }
constexpr v2  vTrunc(const v2& v)                              { return v2((f32)(c32)(v.x), (f32)(c32)(v.y)); }
constexpr f32 vFloor(f32 f)                                    { return (f32)((f >= 0 || (f32)(c32)f == f) ? (c32)f : (c32)f - 1); } // Decent replacement for floorf()
constexpr v2  vFloor(const v2& v)                              { return v2(vFloor(v.x), vFloor(v.y)); }
constexpr f32 vTrunc64(f32 f)                                  { return (f32)(s64)(f); }
constexpr f32 vRound64(f32 f)                                  { return (f32)(s64)(f + 0.5f); } // FIXME: Positive values only.
constexpr c32 vModPositive(c32 a, c32 b)                       { return (a + b) % b; }
constexpr f32 vDot(const v2& a, const v2& b)                   {return a.x * b.x + a.y * b.y;}
constexpr f32 vDot(const v3& a, const v3& b)                   {return a.x * b.x + a.y * b.y + a.z * b.z;}
constexpr v2  vRotate(const v2& v, f32 cos_a, f32 sin_a)       { return v2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a); }
constexpr f32 vLinearSweep(f32 current, f32 target, f32 speed) { if (current < target) return vMin(current + speed, target); if (current > target) return vMax(current - speed, target); return current; }
constexpr f32 vLinearRemapClamp(f32 s0, f32 s1, f32 d0, f32 d1, f32 x) { return vSaturate((x - s0) / (s1 - s0)) * (d1 - d0) + d0; }
constexpr v2  vMul(const v2& lhs, const v2& rhs)               { return v2(lhs.x * rhs.x, lhs.y * rhs.y); }
constexpr c1  vIsFloatAboveGuaranteedIntegerPrecision(f32 f)   { return f <= -16777216 || f >= 16777216; }
constexpr f32 vExponentialMovingAverage(f32 avg, f32 sample, c32 n) { avg -= avg / (f32)n; avg += sample / (f32)n; return avg; }
constexpr f32 vRadians(f32 degrees) {return degrees * (PI / 180.0f);}
constexpr f32 vDegrees(f32 radians) {return radians * (180.0f / PI);}
constexpr f32 vLength(const v3& a) {return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);}
// normalize
constexpr v3 normalize(const v3& a) {
    f32 len = vLength(a);
    if (len <= 0.0f) return {};
    return a / len;
}
// angle
constexpr f32 angle(const v3& a, const v3& b) {
    f32 d = vDot(normalize(a), normalize(b));
    d = fmaxf(-1.0f, fminf(1.0f, d));
    return acosf(d);
}
// cross
constexpr v3 cross(const v3& a, const v3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
// rotate
constexpr v3 rotate(const v3& a, f32 angle, const v3& axis) {
    v3 n  = normalize(axis);
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return a * c + cross(n, a) * s + n * vDot(n, a) * (1.0f - c);
}
// lookAt
inline m4 lookAt(const v3& eye, const v3& center, const v3& up) {
    v3 f = normalize(center - eye);
    v3 r = normalize(cross(f, up));
    v3 u = cross(r, f);
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
    result[3][0] = -vDot(r, eye);
    result[3][1] = -vDot(u, eye);
    result[3][2] = vDot(f, eye);
    return result;
}
// perspective
inline m4 perspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar) {
    f32 tanHalfFovy = tanf(fovy / 2.0f);
    m4 result = {};
    result[0][0] = 1.0f / (aspect * tanHalfFovy);
    result[1][1] = 1.0f / tanHalfFovy;
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    return result;
}