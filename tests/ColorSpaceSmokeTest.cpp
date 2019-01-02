#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Drawing/Color/Spaces.hpp>
#include <RadonFramework/Drawing/Color/Converter.hpp>
#include <RadonFramework/Drawing/Color/Interpolation.hpp>

int main(int argc, char** argv)
{
  RadonFramework::Radon framework;

  {  // RGB interpolation
    RF_Color::RGB a{255, 0, 0};
    RF_Color::RGB b{0, 0, 255};
    RF_Color::RGB c{255, 255, 0};
    auto d = RF_Color::RGBInterpolation::At(a, b, 0.5);
    RF_ASSERT(d.R == 127.5 && d.G == 0 && d.B == 127.5,
              "RGB interpolation returned wrong result!");
    auto e = RF_Color::RGBInterpolation::At(b, c, 0.5);
    RF_ASSERT(e.R == 127.5 && e.G == 127.5 && e.B == 127.5,
              "RGB interpolation returned wrong result!");
    auto f = RF_Color::RGBInterpolation::At(b, c, 0);
    RF_ASSERT(f.R == b.R && f.G == b.G && f.B == b.B,
              "RGB interpolation returned wrong result!");
    auto g = RF_Color::RGBInterpolation::At(b, c, 1);
    RF_ASSERT(g.R == c.R && g.G == c.G && g.B == c.B,
              "RGB interpolation returned wrong result!");
  }
  {  // LCH interpolation
    RF_Color::LCH a{100, 140, 0};
    RF_Color::LCH b{50, 70, 180};
    auto c = RF_Color::LCHInterpolation::At(a, b, 0.5);
    RF_ASSERT(c.L == 75 && c.C == 105 && c.H == 90,
              "RGB interpolation returned wrong result!");
    auto d = RF_Color::LCHInterpolation::At(a, b, 0);
    RF_ASSERT(d.L == a.L && d.C == a.C && d.H == a.H,
              "RGB interpolation returned wrong result!");
    auto e = RF_Color::LCHInterpolation::At(a, b, 1);
    RF_ASSERT(e.L == b.L && e.C == b.C && e.H == b.H,
              "RGB interpolation returned wrong result!");
  }
  {  // HSL interpolation
    RF_Color::HSL a{100, 0.3, 0.3};
    RF_Color::HSL b{50, 0.8, 0.5};
    auto c = RF_Color::HSLInterpolation::At(a, b, 0.5);
    RF_ASSERT(RF_Math::Float32::IsAlmostEqual(c.L, 0.4) &&
                  RF_Math::Float32::IsAlmostEqual(c.S, 0.55) &&
                  RF_Math::Float32::IsAlmostEqual(c.H, 75),
              "RGB interpolation returned wrong result!");
    auto d = RF_Color::HSLInterpolation::At(a, b, 0);
    RF_ASSERT(d.L == a.L && d.S == a.S && d.H == a.H,
              "RGB interpolation returned wrong result!");
    auto e = RF_Color::HSLInterpolation::At(a, b, 1);
    RF_ASSERT(e.L == b.L && e.S == b.S && e.H == b.H,
              "RGB interpolation returned wrong result!");
  }
  {  // HSV interpolation
    RF_Color::HSV a{100, 0.3, 0.3};
    RF_Color::HSV b{50, 0.8, 0.5};
    auto c = RF_Color::HSVInterpolation::At(a, b, 0.5);
    RF_ASSERT(RF_Math::Float32::IsAlmostEqual(c.V, 0.4) &&
                  RF_Math::Float32::IsAlmostEqual(c.S, 0.55) &&
                  RF_Math::Float32::IsAlmostEqual(c.H, 75),
              "RGB interpolation returned wrong result!");
    auto d = RF_Color::HSVInterpolation::At(a, b, 0);
    RF_ASSERT(d.V == a.V && d.S == a.S && d.H == a.H,
              "RGB interpolation returned wrong result!");
    auto e = RF_Color::HSVInterpolation::At(a, b, 1);
    RF_ASSERT(e.V == b.V && e.S == b.S && e.H == b.H,
              "RGB interpolation returned wrong result!");
  }
  {  // HWB interpolation
    RF_Color::HWB a{100, 0.3, 0.3};
    RF_Color::HWB b{50, 0.8, 0.5};
    auto c = RF_Color::HWBInterpolation::At(a, b, 0.5);
    RF_ASSERT(RF_Math::Float32::IsAlmostEqual(c.H, 75) &&
                  RF_Math::Float32::IsAlmostEqual(c.W, 0.55) &&
                  RF_Math::Float32::IsAlmostEqual(c.B, 0.4),
              "RGB interpolation returned wrong result!");
    auto d = RF_Color::HWBInterpolation::At(a, b, 0);
    RF_ASSERT(d.H == a.H && d.W == a.W && d.B == a.B,
              "RGB interpolation returned wrong result!");
    auto e = RF_Color::HWBInterpolation::At(a, b, 1);
    RF_ASSERT(e.H == b.H && e.W == b.W && e.B == b.B,
              "RGB interpolation returned wrong result!");
  }
  {  // LAB interpolation
    RF_Color::LAB a{30, -29, 29};
    RF_Color::LAB b{80, 10, -14};
    auto c = RF_Color::LABInterpolation::At(a, b, 0.5);
    RF_ASSERT(RF_Math::Float32::IsAlmostEqual(c.L, 55) &&
                  RF_Math::Float32::IsAlmostEqual(c.A, -9.5) &&
                  RF_Math::Float32::IsAlmostEqual(c.B, 7.5),
              "RGB interpolation returned wrong result!");
    auto d = RF_Color::LABInterpolation::At(a, b, 0);
    RF_ASSERT(d.L == a.L && d.A == a.A && d.B == a.B,
              "RGB interpolation returned wrong result!");
    auto e = RF_Color::LABInterpolation::At(a, b, 1);
    RF_ASSERT(e.L == b.L && e.A == b.A && e.B == b.B,
              "RGB interpolation returned wrong result!");
  }
  {  // XYZ interpolation
    RF_Color::XYZ a{41, 21, 2};
    RF_Color::XYZ b{18, 7, 95};
    auto c = RF_Color::XYZInterpolation::At(a, b, 0.5);
    RF_ASSERT(RF_Math::Float32::IsAlmostEqual(c.X, 29.5) &&
                  RF_Math::Float32::IsAlmostEqual(c.Y, 14) &&
                  RF_Math::Float32::IsAlmostEqual(c.Z, 48.5),
              "RGB interpolation returned wrong result!");
    auto d = RF_Color::XYZInterpolation::At(a, b, 0);
    RF_ASSERT(d.X == a.X && d.Y == a.Y && d.Z == a.Z,
              "RGB interpolation returned wrong result!");
    auto e = RF_Color::XYZInterpolation::At(a, b, 1);
    RF_ASSERT(e.X == b.X && e.Y == b.Y && e.Z == b.Z,
              "RGB interpolation returned wrong result!");
  }
  RF_Thread::ThreadPool::Global().DisableAndWaitTillDone();
  return 0;
}