#include <QtWidgets>

#include "norwegianwoodstyle.h"

NorwegianWoodStyle::NorwegianWoodStyle() : QProxyStyle(QStyleFactory::create("fusion"))
{
}

int NorwegianWoodStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
  switch (metric) {
    case PM_SliderLength:
      return 30;
    default:
      return QProxyStyle::pixelMetric(metric, option, widget);
  }
}
