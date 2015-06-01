#ifndef SLIDERSTYLE_H
#define SLIDERSTYLE_H

#include <QProxyStyle>

class SliderStyle : public QProxyStyle
{
public:
  SliderStyle();
  int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const;
};

#endif // SLIDERSTYLE_H
