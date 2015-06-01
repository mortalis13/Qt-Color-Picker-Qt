#include "sliderstyle.h"

#include <QStyleFactory>

SliderStyle::SliderStyle() : QProxyStyle(QStyleFactory::create("fusion"))
{
}

int SliderStyle::pixelMetric ( PixelMetric metric, const QStyleOption * option, const QWidget * widget ) const
{
    switch(metric) {
//      case PM_SliderControlThickness  : return 50;
    case PM_SliderLength  : return 30;
      default                         :
      return (QProxyStyle::pixelMetric(metric,option,widget));
    }
}
