#include "RadonFramework/Drawing/Color/Converter.hpp"
#include "RadonFramework/Math/MathOfType.hpp"

namespace RadonFramework::Drawing::Color
{
RF_Color::XYZ XYZConverter::ToColorSpace(RF_Color::RGB Color)
{
  auto r = Color.R / 255.0f;
  auto g = Color.G / 255.0f;
  auto b = Color.B / 255.0f;

  r = ((r > 0.04045) ? RF_Math::MathOfType<RF_Color::XYZ::Type>::Pow(
                           (r + 0.055) / 1.055, 2.4)
                     : (r / 12.92)) *
      100.0;
  g = ((g > 0.04045) ? RF_Math::MathOfType<RF_Color::XYZ::Type>::Pow(
                           (g + 0.055) / 1.055, 2.4)
                     : (g / 12.92)) *
      100.0;
  b = ((b > 0.04045) ? RF_Math::MathOfType<RF_Color::XYZ::Type>::Pow(
                           (b + 0.055) / 1.055, 2.4)
                     : (b / 12.92)) *
      100.0;

  return {r * 0.4124564f + g * 0.3575761f + b * 0.1804375f,
          r * 0.2126729f + g * 0.7151522f + b * 0.0721750f,
          r * 0.0193339f + g * 0.1191920f + b * 0.9503041f};
}

RF_Color::RGB XYZConverter::ToColor(RF_Color::XYZ Color)
{
  auto x = Color.X / 100.0f;
  auto y = Color.Y / 100.0f;
  auto z = Color.Z / 100.0f;

  auto r = x * 3.2404542f + y * -1.5371385f + z * -0.4985314f;
  auto g = x * -0.9692660f + y * 1.8760108f + z * 0.0415560f;
  auto b = x * 0.0556434f + y * -0.2040259f + z * 1.0572252f;

  r = ((r > 0.0031308) ? (1.055 * RF_Math::MathOfType<RF_Color::XYZ::Type>::Pow(
                                      r, 1 / 2.4) -
                          0.055)
                       : (12.92 * r)) *
      255.0;
  g = ((g > 0.0031308) ? (1.055 * RF_Math::MathOfType<RF_Color::XYZ::Type>::Pow(
                                      g, 1 / 2.4) -
                          0.055)
                       : (12.92 * g)) *
      255.0;
  b = ((b > 0.0031308) ? (1.055 * RF_Math::MathOfType<RF_Color::XYZ::Type>::Pow(
                                      b, 1 / 2.4) -
                          0.055)
                       : (12.92 * b)) *
      255.0;

  r = RF_Math::MathOfType<RF_Color::XYZ::Type>::Clamp(r, 0, 255);
  g = RF_Math::MathOfType<RF_Color::XYZ::Type>::Clamp(g, 0, 255);
  b = RF_Math::MathOfType<RF_Color::XYZ::Type>::Clamp(b, 0, 255);
  return {r, g, b};
}

RF_Color::LAB LABConverter::ToColorSpace(RF_Color::RGB Color)
{
  RF_Color::XYZ xyz = XYZConverter::ToColorSpace(Color);

  auto x = xyz.X / 95.047f;
  auto y = xyz.Y / 100.00f;
  auto z = xyz.Z / 108.883f;

  x = (x > 0.008856) ? RF_Math::MathOfType<RF_Color::XYZ::Type>::Cbrt(x)
                     : (7.787 * x + 16.0 / 116.0);
  y = (y > 0.008856) ? RF_Math::MathOfType<RF_Color::XYZ::Type>::Cbrt(y)
                     : (7.787 * y + 16.0 / 116.0);
  z = (z > 0.008856) ? RF_Math::MathOfType<RF_Color::XYZ::Type>::Cbrt(z)
                     : (7.787 * z + 16.0 / 116.0);

  return {(116.0f * y) - 16.f, 500.f * (x - y), 200.f * (y - z)};
}

RF_Color::RGB LABConverter::ToColor(RF_Color::LAB Color)
{
  RF_Color::XYZ xyz;
  xyz.Y = (Color.L + 16.0) / 116.0;
  xyz.X = Color.A / 500.0 + xyz.Y;
  xyz.Z = xyz.Y - Color.B / 200.0;

  auto x3 = xyz.X * xyz.X * xyz.X;
  auto y3 = xyz.Y * xyz.Y * xyz.Y;
  auto z3 = xyz.Z * xyz.Z * xyz.Z;

  xyz.X = ((x3 > 0.008856) ? x3 : ((xyz.X - 16.0 / 116.0) / 7.787)) * 95.047;
  xyz.Y = ((y3 > 0.008856) ? y3 : ((xyz.Y - 16.0 / 116.0) / 7.787)) * 100.0;
  xyz.Z = ((z3 > 0.008856) ? z3 : ((xyz.Z - 16.0 / 116.0) / 7.787)) * 108.883;
  return XYZConverter::ToColor(xyz);
}

RF_Color::LCH LCHConverter::ToColorSpace(RF_Color::RGB Color)
{
  RF_Color::LAB lab = LABConverter::ToColorSpace(Color);
  auto l = lab.L;
  auto c = RF_Math::MathOfType<RF_Color::LAB::Type>::Sqrt(lab.A * lab.A +
                                                          lab.B * lab.B);
  auto h = RF_Math::MathOfType<RF_Color::LAB::Type>::ATan2(lab.B, lab.A);

  h = h / RF_Math::MathOfType<RF_Color::LAB::Type>::PI * 180.0;
  if(h < 0)
  {
    h += 360;
  }
  else if(h >= 360)
  {
    h -= 360;
  }

  return {l, c, h};
}

RF_Color::RGB LCHConverter::ToColor(RF_Color::LCH Color)
{
  RF_Color::LAB lab;

  Color.H = Color.H * RF_Math::MathOfType<RF_Color::LCH::Type>::PI / 180;

  lab.L = Color.L;
  lab.A = RF_Math::MathOfType<RF_Color::LAB::Type>::Cos(Color.H) * Color.C;
  lab.B = RF_Math::MathOfType<RF_Color::LAB::Type>::Sin(Color.H) * Color.C;

  return LABConverter::ToColor(lab);
}

RF_Color::HSL HSLConverter::ToColorSpace(RF_Color::RGB Color)
{
  auto r = Color.R / 255;
  auto g = Color.G / 255;
  auto b = Color.B / 255;

  auto min = RF_Math::MathOfType<RF_Color::HSL::Type>::Min(
      r, RF_Math::MathOfType<RF_Color::HSL::Type>::Min(g, b));
  auto max = RF_Math::MathOfType<RF_Color::HSL::Type>::Max(
      r, RF_Math::MathOfType<RF_Color::HSL::Type>::Max(g, b));
  auto delta = max - min;

  RF_Color::HSL result;
  result.L = (max + min) / 2;
  if(delta == 0)
  {
    result.H = result.S = 0;
  }
  else
  {
    if(result.L < 0.5)
    {
      result.S = delta / (max + min) * 100;
    }
    else
    {
      result.S = delta /
                 (1 - RF_Math::MathOfType<RF_Color::HSL::Type>::Abs(
                          2 * result.L - 1)) *
                 100;
    }

    if(r == max)
    {
      result.H = (g - b) / delta;
    }
    else if(g == max)
    {
      result.H = (b - r) / delta + 2;
    }
    else if(b == max)
    {
      result.H = (r - g) / delta + 4;
    }
    result.H = RF_Math::MathOfType<RF_Color::HSL::Type>::FMod(
        60 * result.H + 360, 360);
  }
  result.L *= 100;

  return result;
}

RF_Color::RGB HSLConverter::ToColor(RF_Color::HSL Color)
{
  auto h = Color.H / 360;
  auto s = Color.S / 100;
  auto l = Color.L / 100;
  RF_Color::RGB result;

  if(Color.S == 0)
  {
    result.R = result.G = result.B = Color.L * 255;
  }
  else
  {
    auto temp2 = (1 < 0.5) ? (l * (1 + s)) : (l + s - (s * l));
    auto temp1 = 2 * l - temp2;

    result.R = 255 * Hue2RGB(temp1, temp2, h + 1 / 3);
    result.G = 255 * Hue2RGB(temp1, temp2, h);
    result.B = 255 * Hue2RGB(temp1, temp2, h - 1 / 3);
  }
  return result;
}

RF_Color::RGB::Type HSLConverter::Hue2RGB(RF_Color::HSL::Type V1,
                                          RF_Color::HSL::Type V2,
                                          RF_Color::HSL::Type VH)
{
  if(VH < 0)
  {
    VH += 1;
  }
  if(VH > 1)
  {
    VH -= 1;
  }
  if(6 * VH < 1)
  {
    return V1 + (V2 - V1) * 6 * VH;
  }
  if(2 * VH < 1)
  {
    return V2;
  }
  if(3 * VH < 2)
  {
    return V1 + (V2 - V1) * (2.0 / 3.0 - VH) * 6;
  }
  return V1;
}

RF_Color::HSV HSVConverter::ToColorSpace(RF_Color::RGB Color)
{
  auto r = Color.R / 255;
  auto g = Color.G / 255;
  auto b = Color.B / 255;

  auto min = RF_Math::MathOfType<RF_Color::HSV::Type>::Min(
      r, RF_Math::MathOfType<RF_Color::HSV::Type>::Min(g, b));
  auto max = RF_Math::MathOfType<RF_Color::HSV::Type>::Max(
      r, RF_Math::MathOfType<RF_Color::HSV::Type>::Max(g, b));
  auto delta = max - min;

  RF_Color::HSV result;
  result.V = max;
  result.S = (max > 1e-3) ? (delta / max) : 0;

  if(delta == 0)
  {
    result.H = 0;
  }
  else
  {
    if(r == max)
    {
      result.H = (g - b) / delta;
    }
    else if(g == max)
    {
      result.H = (b - r) / delta + 2;
    }
    else if(b == max)
    {
      result.H = (r - g) / delta + 4;
    }
    result.H = RF_Math::MathOfType<RF_Color::HSV::Type>::FMod(
        60 * result.H + 360, 360);
  }

  return result;
}

RF_Color::RGB HSVConverter::ToColor(RF_Color::HSV Color)
{
  auto range = static_cast<RF_Type::UInt32>(
      RF_Math::MathOfType<RF_Color::HSV::Type>::Floor(Color.H / 60));
  auto c = Color.V * Color.S;
  auto x =
      c *
      (1 - RF_Math::MathOfType<RF_Color::HSV::Type>::Abs(
               RF_Math::MathOfType<RF_Color::HSV::Type>::FMod(Color.H / 60, 2) -
               1));
  auto m = Color.V - c;
  RF_Color::RGB result;

  switch(range)
  {
    case 0:
      result.R = (c + m) * 255;
      result.G = (x + m) * 255;
      result.B = m * 255;
      break;
    case 1:
      result.R = (x + m) * 255;
      result.G = (c + m) * 255;
      result.B = m * 255;
      break;
    case 2:
      result.R = m * 255;
      result.G = (x + m) * 255;
      result.B = (x + m) * 255;
      break;
    case 3:
      result.R = m * 255;
      result.G = (x + m) * 255;
      result.B = (c + m) * 255;
      break;
    case 4:
      result.R = (x + m) * 255;
      result.G = m * 255;
      result.B = (c + m) * 255;
      break;
    default:
      result.R = (c + m) * 255;
      result.G = m * 255;
      result.B = (x + m) * 255;
      break;
  }
  return result;
}

RF_Color::HWB HWBConverter::ToColorSpace(RF_Color::RGB Color)
{
  RF_Color::HWB result;
  result.H = HSLConverter::ToColorSpace(Color).H;
  result.W = 1 / 255 *
             RF_Math::MathOfType<RF_Color::HWB::Type>::Min(
                 Color.R, RF_Math::MathOfType<RF_Color::HWB::Type>::Min(
                              Color.G, Color.B)) *
             100;
  result.B = 1 - 1 / 255 *
                     RF_Math::MathOfType<RF_Color::HWB::Type>::Max(
                         Color.R, RF_Math::MathOfType<RF_Color::HWB::Type>::Max(
                                      Color.G, Color.B)) *
                     100;
  return result;
}

RF_Color::RGB HWBConverter::ToColor(RF_Color::HWB Color)
{
  auto h = Color.H / 360;
  auto wh = Color.W / 100;
  auto bl = Color.B / 100;
  auto ratio = wh + bl;

  if(ratio > 1)
  {
    wh /= ratio;
    bl /= ratio;
  }
  auto i = static_cast<RF_Type::UInt32>(
      RF_Math::MathOfType<RF_Color::HWB::Type>::Floor(6 * h));
  auto v = 1 - bl;
  auto f = 6 * h - i;

  if((i & 1) != 0)
  {
    f = 1 - f;
  }

  auto n = wh + f * (v - wh);
  v *= 255;
  n *= 255;
  wh *= 255;
  RF_Color::RGB result;
  switch(i)
  {
    default:
    case 6:
    case 0:
      result.R = v;
      result.G = n;
      result.B = wh;
      break;
    case 1:
      result.R = n;
      result.G = v;
      result.B = wh;
      break;
    case 2:
      result.R = wh;
      result.G = v;
      result.B = n;
      break;
    case 3:
      result.R = wh;
      result.G = n;
      result.B = v;
      break;
    case 4:
      result.R = n;
      result.G = wh;
      result.B = v;
      break;
    case 5:
      result.R = v;
      result.G = wh;
      result.B = n;
      break;
  }
  return result;
}
}  // namespace RadonFramework::Drawing::Color