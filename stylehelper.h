#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QString>


class StyleHelper
{

public:
    StyleHelper();
    static QString getMainWidgetStyle();
    //static QString getGameFieldStyle();

    //static QString getButtonStyle();
    static QString getButtonStyleUnlock();
    static QString getButtonStyleLock();

    static QString getActiveCrossButtonStyle();
    static QString getActiveZeroButtonStyle();
};

#endif // STYLEHELPER_H
