#include "propertystyle.h"
#include <QDebug>
#include <QtWidgets>

bool preventDrawItemText = false;

//PropertyStyle::PropertyStyle() :
//    QProxyStyle(QStyleFactory::create("windows"))
PropertyStyle::PropertyStyle() :
    QProxyStyle()
{

}

void PropertyStyle::drawControl(ControlElement element, const QStyleOption * option, QPainter * painter,
                    const QWidget * widget) const
{
    qDebug()<< "PropertyStyle::drawControl ";
    if (preventDrawItemText) return;
     QProxyStyle::drawControl(element, option, painter, widget);
    return;
}
