#pragma once

#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework::Drawing::Color
{
enum class ReferenceWhite
{
  A,
  B,
  C,
  E,
  F2,
  F7,
  F11,
  D50,
  D55,
  D65,
  D75,
  D93
};

enum class Gamma
{
  // Constant 1.0
  Const_1,
  // Constant 1.8
  Const_1_8,
  // Constant 2.2
  Const_2_2,
  // L*
  L,
  // Calculated by two functions which result is roughly 2.2
  sRGB
};

struct LCH
{
  using Type = RF_Type::Float32;
  Type L, C, H;
};

struct RGB
{
  using Type = RF_Type::Float32;
  Type R, G, B;
  void operator=(RGB Value)
  {
    R = Value.R;
    G = Value.G;
    B = Value.B;
  }
  bool operator!=(RGB Value)
  {
    return R == Value.R && G == Value.G && B == Value.B;
  }
};

struct LAB
{
  using Type = RF_Type::Float32;
  Type L, A, B;
};

struct XYZ
{
  using Type = RF_Type::Float32;
  Type X, Y, Z;
};

struct HSL
{
  using Type = RF_Type::Float32;
  Type H, S, L;
};

struct HSV
{
  using Type = RF_Type::Float32;
  Type H, S, V;
};

struct HWB
{
  using Type = RF_Type::Float32;
  Type H, W, B;
};

}  // namespace RadonFramework::Drawing::Color

namespace RF_Color = RadonFramework::Drawing::Color;