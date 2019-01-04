#include "RadonFramework/Drawing/Color/Gradient.hpp"
#include "RadonFramework/Drawing/Color/Converter.hpp"
#include "RadonFramework/Drawing/Color/Interpolation.hpp"
#include "RadonFramework/Core/Common/Assert.hpp"

namespace RadonFramework::Drawing::Color
{
Gradient::Gradient(const std::initializer_list<GradientStep>& Steps)
{
  m_StepCount = Steps.size();
  m_Steps = new GradientStep[m_StepCount];
  auto i = 0;
  for(auto step : Steps)
  {
    m_Steps[i] = step;
    ++i;
  }
}

RGB Gradient::ComputeAt(const RF_Type::Float32 Position) const
{
  RF_ASSERT(Position >= 0.0f && Position <= 1.0f,
            "Position must be between 0 and 1");
  auto& start = GetNearestSmallerColor(Position);
  auto& end = GetNearestLargerColor(Position);
  LCH startColor = LCHConverter::ToColorSpace(start.RGB);
  LCH endColor = LCHConverter::ToColorSpace(end.RGB);
  auto t = (Position - start.Position) / (end.Position - start.Position);
  auto color = LCHInterpolation::At(startColor, endColor, t);
  return LCHConverter::ToColor(color);
}

GradientStep& Gradient::GetNearestSmallerColor(RF_Type::Float32 Position) const
{
  RF_Type::Size index = 0;
  for(auto i = 0; i < m_StepCount; ++i)
  {
    if(m_Steps[i].Position < Position)
    {
      index = i;
    }
  }
  return m_Steps[index];
}

GradientStep& Gradient::GetNearestLargerColor(RF_Type::Float32 Position) const
{
  RF_Type::Size index = 0;
  for(auto i = 0; i < m_StepCount; ++i)
  {
    if(m_Steps[i].Position < Position)
    {
      index = i;
    }
  }

  if(index < m_StepCount - 1)
  {
    index += 1;
  }
  return m_Steps[index];
}
}  // namespace RadonFramework::Drawing::Color