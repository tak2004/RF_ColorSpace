#pragma once

#include <RadonFramework/Drawing/Color/Spaces.hpp>

namespace RadonFramework::Drawing::Color
{

struct XYZConverter
{
  static RF_Color::XYZ ToColorSpace(RF_Color::RGB Color);
  static RF_Color::RGB ToColor(RF_Color::XYZ Color);
};

struct LABConverter
{
  static RF_Color::LAB ToColorSpace(RF_Color::RGB Color);
  static RF_Color::RGB ToColor(RF_Color::LAB Color);
};

struct LCHConverter
{
  static RF_Color::LCH ToColorSpace(RF_Color::RGB Color);
  static RF_Color::RGB ToColor(RF_Color::LCH Color);
};

struct HSLConverter
{
  static RF_Color::HSL ToColorSpace(RF_Color::RGB Color);
  static RF_Color::RGB ToColor(RF_Color::HSL Color);
private:
  static RF_Color::RGB::Type Hue2RGB(RF_Color::HSL::Type V1,
                                     RF_Color::HSL::Type V2,
                                     RF_Color::HSL::Type VH);
};

struct HSVConverter
{
  static RF_Color::HSV ToColorSpace(RF_Color::RGB Color);
  static RF_Color::RGB ToColor(RF_Color::HSV Color);
};

struct HWBConverter
{
  static RF_Color::HWB ToColorSpace(RF_Color::RGB Color);
  static RF_Color::RGB ToColor(RF_Color::HWB Color);
};

}

namespace RF_Color = RadonFramework::Drawing::Color;