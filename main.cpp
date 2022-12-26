#include <QApplication>
#include <QHBoxLayout>
#include <QPainter>

#include "output.h"
#include "option.h"
#include "stylehelper.h"

//Widht(X)
#define minSizeW_1 400
#define minSizeW_2 (19*35 + 5+5 + 19) //675 + 19
#define minSizeH 19*35 + 19*1 + 5+5 + 16 + 19  // 710 + 19



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget  wgt;

    CommonVariable* comVar = new CommonVariable;

    Output* obj_2 = new Output(&wgt, comVar);

    Option* obj_1 = new Option(&wgt, obj_2, comVar);
    obj_1->setGeometry( 0, 0, minSizeW_1, minSizeH );     // X, Y, Widht(X), Heigth(Y)




    //Layout setup
    QHBoxLayout* pHLayout = new QHBoxLayout;
    pHLayout->addWidget(obj_1);
    pHLayout->addWidget(obj_2);
    wgt.setLayout(pHLayout);


    //WGT setting
    wgt.setStyleSheet(StyleHelper::getMainWidgetStyle());



    wgt.resize( minSizeW_1 + minSizeW_2 , minSizeH );
    wgt.setMinimumSize( minSizeW_1 + minSizeW_2 , minSizeH );    // Widht(X), Heigth(Y)


    wgt.setWindowTitle("ITT: Infinity Tic-Tac ");
    wgt.show();

    return a.exec();
}
