#ifndef PROPERTYSTYLE_H
#define PROPERTYSTYLE_H

#include <QProxyStyle>

extern bool preventDrawItemText;

class PropertyStyle : public QProxyStyle
{
    Q_OBJECT
public:
    PropertyStyle();
    void	drawControl(ControlElement element, const QStyleOption * option, QPainter * painter,
                        const QWidget * widget = 0) const;

signals:
    
public slots:
    
};

#endif // PROPERTYSTYLE_H
