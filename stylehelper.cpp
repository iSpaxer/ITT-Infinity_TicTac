#include "stylehelper.h"

/// Types style
    //purple
///" background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0.955, stop:0 rgba(85, 0, 255, 255), stop:1 rgba(195, 165, 255, 255));";


StyleHelper::StyleHelper()
{

}

QString StyleHelper::getMainWidgetStyle()
{
    return " background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0.955, stop:0 rgba(85, 0, 255, 255), stop:1 rgba(195, 165, 255, 255));";

}


QString StyleHelper::getButtonStyleLock()
{
    return "QPushButton{"
           "    border:         none;"
           "    border:         1px solid #222;"
           "    border-radius:  2.5px ;"
           "    background:     #272D39 ;"
           "}";
}

QString StyleHelper::getButtonStyleUnlock()
{

    return "QPushButton{"
           "    border:         none;"
           "    border:         1px solid #222;"
           "    border-radius:  2.5px ;"
           "    background:     #272D39 ;"
           "}"
           "QPushButton::hover{"
           "    background: #373D49;"
           "}";
}

QString StyleHelper::getActiveCrossButtonStyle()
{

        return "QPushButton{"
               "    border:         none;"
               "    border:         1px solid #222;"
               "    border-radius:  2.5px ;"
               "    background:     #272D39 url(:/resourses/cross_test.png) no-repeat center center;"
               "}";
//               "QPushButton::hover{"
//               "    background: #373D49;"
//               "}";
}

QString StyleHelper::getActiveZeroButtonStyle()
{
    return "QPushButton{"
           "    border:         none;"
           "    border:         1px solid #222;"
           "    border-radius:  2.5px ;"
           "    background:     #272D39 url(:/resourses/zero_test.png) no-repeat center center;"
           "}";
}
