#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>

#include <QPoint>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <time.h>
#include <QPainter>

#include "commonvariable.h"
#include "stylehelper.h"

#define SizeBoard 19
#define EPIC_BIG_VALUE 30000

class Output : public QWidget
{
    Q_OBJECT

    /// Variable
public:
    enum PlayerType{
      PT_NON_ONE = 0,
      PT_ZERO    = 1,
      PT_CROSS   = 2
      //PT_BOT vs PT_BOT
    };
private:
                    /// For Bot
///_______________________________________________________________________
    char map[SizeBoard][SizeBoard];//Игровое поле ( = 0 - ничего нет, = 1 - нолик, id
    //= 2 - крестик, = 3 - выигравший нолик, = 4 - выигравший крестик
    //= 5 - последний поставленный нолик, = 6 - последний поставленный крестик)
    //int calc_fields[SizeBoard][SizeBoard];    //Рассчитанное значение оценочной функции


    int left_up,   right_up;       //нужны для будущей оптимизации подсчёта оценочной функции
    int left_down, right_down;

    int last_x; //координаты последне поставленного крестика или нолика
    int last_y;

    float attack_factor    = 1;  //Коэффициент агрессивности ИИ (1 - по умолчанию) ///!
    int   valuation_factor = 3; //Оценочный коэффициент
    ////
    int _x, _y;
    int max = 0;
    int maxDown = 1;
/// For Widget
///_______________________________________________________________________
    CommonVariable* comVar;
    QVector<QVector<QPushButton*>> buttons2DVector;

    /// Common public functions
public:
    Output( QWidget* ptr, CommonVariable *_comVar);

    /// Functions for Bot
private:

    int  runMinMax( PlayerType, int, int&, int&, int, int, int, int);
    int  runMinMax( PlayerType plr, int& bestMove_y, int& bestMove_x );

    void ii( );
    int  calculate( char id, int x, int y );
    int  calculate_2( char id, int x, int y );

    /// Functions for Widgets
private:
    void initMas();
    void clearingScreen();
    void LockButtons();
    void UnlockButtons();
    QPushButton* createButton( int i, int j );

protected:
  void paintEvent(QPaintEvent *event);

    /// Slots
public slots:
    void slotButtonClicked();
    void startSlotButton();
};

#endif // OUTPUT_H
