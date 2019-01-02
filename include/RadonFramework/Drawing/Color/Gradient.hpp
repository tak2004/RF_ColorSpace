#pragma once

#include <RadonFramework/Drawing/Color/Spaces.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

#include <initializer_list>

namespace RadonFramework::Drawing::Color
{

struct GradientStep
{
  RF_Color::RGB RGB;
  RF_Type::Float32 Position;
};

class Gradient
{
public:
  Gradient(const std::initializer_list<GradientStep>& Steps);
  RF_Color::RGB ComputeAt(const RF_Type::Float32 Position) const;
protected:
  GradientStep* m_Steps;
  RF_Type::Size m_StepCount;

  GradientStep& GetNearestSmallerColor(RF_Type::Float32 Position) const;
  GradientStep& GetNearestLargerColor(RF_Type::Float32 Position) const;
};

}

namespace RF_Color = RadonFramework::Drawing::Color;