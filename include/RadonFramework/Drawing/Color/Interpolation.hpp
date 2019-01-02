#pragma once

#include <RadonFramework/Drawing/Color/Spaces.hpp>

namespace RadonFramework::Drawing::Color
{

struct LCHInterpolation
{
  static LCH At(LCH Start, LCH End, RF_Type::Float32 Position);
};

struct RGBInterpolation
{
  static RGB At(RGB Start, RGB End, RF_Type::Float32 Position);
};

struct HSLInterpolation
{
  static HSL At(HSL Start, HSL End, RF_Type::Float32 Position);
};

struct HSVInterpolation
{
  static HSV At(HSV Start, HSV End, RF_Type::Float32 Position);
};

struct HWBInterpolation
{
  static HWB At(HWB Start, HWB End, RF_Type::Float32 Position);
};

struct LABInterpolation
{
  static LAB At(LAB Start, LAB End, RF_Type::Float32 Position);
};

struct XYZInterpolation
{
  static XYZ At(XYZ Start, XYZ End, RF_Type::Float32 Position);
};

}