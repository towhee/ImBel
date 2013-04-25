#ifndef FONTS_H
#define FONTS_H

#include <QObject>
#include <QFontDatabase>
#include <QFont>

class Fonts : public QObject
{
    Q_OBJECT
public:
    explicit Fonts(QObject *parent = 0);

    void availableFonts();

signals:
    
public slots:
    
};

#endif // FONTS_H
