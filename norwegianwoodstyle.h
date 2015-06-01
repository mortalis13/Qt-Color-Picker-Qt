#ifndef NORWEGIANWOODSTYLE_H
#define NORWEGIANWOODSTYLE_H

#include <QProxyStyle>

class QPainterPath;

class NorwegianWoodStyle : public QProxyStyle
{
    Q_OBJECT

public:
    NorwegianWoodStyle();

    int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const;
};

#endif
