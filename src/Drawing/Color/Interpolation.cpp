#include "RadonFramework/Drawing/Color/Interpolation.hpp"

namespace RadonFramework::Drawing::Color
{
LCH LCHInterpolation::At(LCH Start, LCH End, RF_Type::Float32 Position)
{
  auto deltaHue = Start.H;
  if(End.H > Start.H && End.H - Start.H > 180)
  {
    deltaHue = End.H - (Start.H + 360);
  }
  else if(End.H < Start.H && Start.H - End.H > 180)
  {
    deltaHue = End.H + 360 - End.H;
  }
  else
  {
    deltaHue = End.H - Start.H;
  }

  auto hue = Start.H + Position * deltaHue;
  auto saturation = Start.C + Position * (End.C - Start.C);
  auto lighting = Start.L + Position * (End.L - Start.L);

  return {lighting, saturation, hue};
}

RGB RGBInterpolation::At(RGB Start, RGB End, RF_Type::Float32 Position)
{
  auto r = Start.R + Position * (End.R - Start.R);
  auto g = Start.G + Position * (End.G - Start.G);
  auto b = Start.B + Position * (End.B - Start.B);
  return {r, g, b};
}

HSL HSLInterpolation::At(HSL Start, HSL End, RF_Type::Float32 Position)
{
  auto deltaHue = Start.H;
  if(End.H > Start.H && End.H - Start.H > 180)
  {
    deltaHue = End.H - (Start.H + 360);
  }
  else if(End.H < Start.H && Start.H - End.H > 180)
  {
    deltaHue = End.H + 360 - End.H;
  }
  else
  {
    deltaHue = End.H - Start.H;
  }

  auto hue = Start.H + Position * deltaHue;
  auto saturation = Start.S + Position * (End.S - Start.S);
  auto lighting = Start.L + Position * (End.L - Start.L);

  return {hue, saturation, lighting};
}

HSV HSVInterpolation::At(HSV Start, HSV End, RF_Type::Float32 Position)
{
  auto deltaHue = Start.H;
  if(End.H > Start.H && End.H - Start.H > 180)
  {
    deltaHue = End.H - (Start.H + 360);
  }
  else if(End.H < Start.H && Start.H - End.H > 180)
  {
    deltaHue = End.H + 360 - End.H;
  }
  else
  {
    deltaHue = End.H - Start.H;
  }

  auto hue = Start.H + Position * deltaHue;
  auto saturation = Start.S + Position * (End.S - Start.S);
  auto lighting = Start.V + Position * (End.V - Start.V);

  return {hue, saturation, lighting};
}

HWB HWBInterpolation::At(HWB Start, HWB End, RF_Type::Float32 Position)
{
  auto deltaHue = Start.H;
  if(End.H > Start.H && End.H - Start.H > 180)
  {
    deltaHue = End.H - (Start.H + 360);
  }
  else if(End.H < Start.H && Start.H - End.H > 180)
  {
    deltaHue = End.H + 360 - End.H;
  }
  else
  {
    deltaHue = End.H - Start.H;
  }

  auto hue = Start.H + Position * deltaHue;
  auto whiteness = Start.W + Position * (End.W - Start.W);
  auto blackness = Start.B + Position * (End.B - Start.B);

  return {hue, whiteness, blackness};
}

LAB LABInterpolation::At(LAB Start, LAB End, RF_Type::Float32 Position)
{
  return {Start.L + Position * (End.L - Start.L),
          Start.A + Position * (End.A - Start.A),
          Start.B + Position * (End.B - Start.B)};
}

XYZ XYZInterpolation::At(XYZ Start, XYZ End, RF_Type::Float32 Position)
{
  return {Start.X + Position * (End.X - Start.X),
          Start.Y + Position * (End.Y - Start.Y),
          Start.Z + Position * (End.Z - Start.Z)};
}

}  // namespace RadonFramework::Drawing::Color