#include "output.h"

// max в, убрать в калкулейте,

Output::Output( QWidget* ptr, CommonVariable *_comVar ) : QWidget (ptr)
{
    buttons2DVector.resize(SizeBoard);

    comVar = _comVar;
    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout();
    ptopLayout->setContentsMargins( 5, 5, 5, 5 );
    ptopLayout->setSpacing( 1 );

    setLayout(ptopLayout);

    //creat Buttons
    for (int i = 0; i < SizeBoard; i++){
        buttons2DVector[i].resize(SizeBoard);

        for(int j = 0; j < SizeBoard; j++){
            QPushButton *button = new QPushButton;
            button->setFixedSize(35,35);
            button->setProperty("row", i);
            button->setProperty("column", j);
            button->setStyleSheet( StyleHelper::getButtonStyleLock() );
            connect(button, SIGNAL( clicked() ), SLOT( slotButtonClicked() ) );
            buttons2DVector[i][j] = button;
            ptopLayout->addWidget(button,i,j);
        }
    }

    //Setting Output
    this->setFixedSize(675 + 19, 710 + 19);

}
                /// Function for Bot
///__________________________________________________________________
int Output::runMinMax( Output::PlayerType plr, int& bestMove_y, int& bestMove_x ){

    srand( static_cast<unsigned int>(time(nullptr)));

    int test = 0;
    char id_1, id_2;
    bool isCross = (plr == PT_CROSS);
    int max_value = -1; // max result evaluation function (calculete)


    if( isCross ){
        id_1 = PT_CROSS;
        id_2 = PT_ZERO;
    }
    else{
        id_1 = PT_ZERO;
        id_2 = PT_CROSS;
    }

    //Расчитываем оценочную функцию для всех клеток
    for (int i = 0; i < SizeBoard; i++)
    {
        for (int j = 0; j < SizeBoard; j++)
        {
            if (map[i][j] == PT_NON_ONE)
            {
                //Расчет оценочной функции
                test = calculate(id_2,i,j) + calculate(id_1,i,j);       // 2 - крестик, 1 - нолик

                if ( test == max_value ){

                    bool Random = rand() % 2;
                    if( Random ){
                        test++;
                    }
                    else{
                        test--;
                    }
                }
                if( test > max_value ){

                    max_value = test;
                    bestMove_y = i;
                    bestMove_x = j;
                }
            }
        }
    }
    int y = bestMove_y;
    int x = bestMove_x;
    map[y][x] = id_1;
    //qDebug() << max_value;

    return max_value;
}

int Output::runMinMax( Output::PlayerType plr, int GameDown, int& bestMove_y, int& bestMove_x, int alpha, int beta, int i = -1, int j = -1 ){


    srand( static_cast<unsigned int>(time(nullptr)));

    char id_1, id_2;
    bool isCross = (plr == PT_CROSS);
    int test = 0;
    int help_var = 0;



   // qDebug() << max;

    if( isCross ){
        id_1 = PT_CROSS;
        id_2 = PT_ZERO;
    }
    else{
        id_1 = PT_ZERO;
        id_2 = PT_CROSS;
    }

    if ( GameDown > this->maxDown ){

        //return calculate_2(id_1, _y, _x); //+ (int)(calculate_2(id_2, i, j)*attack_factor);    /// 2
        return calculate_2(id_1, i, j); //+ (int)(calculate_2(id_2, i, j)*attack_factor);
    }

    if (GameDown == 0){                                  //проходим первую глубину и считаем. Если нет очевидных ходов ищем в глубь  // нолики
        max = runMinMax(plr, bestMove_y, bestMove_x);
        map[bestMove_y][bestMove_x] = id_1;
        GameDown++;
        qDebug() << max << "  = max";
    }

    if ( max < 5000){                                       // вторая глубина
        //Расчитываем оценочную функцию для всех клеток
        for (int i = 0; i < SizeBoard; i++)
        {
            for (int j = 0; j < SizeBoard; j++)
            {
                if (map[i][j] == PT_NON_ONE)
                {
                    //map[i][j] = id_2;       //2             //считаем для противоположного класса //крестики
                    if ( GameDown == 1){
                         _y = i;
                         _x = j;
                    }
                    test = runMinMax( isCross ? PT_CROSS : PT_ZERO, ++GameDown, bestMove_y, bestMove_x, -EPIC_BIG_VALUE, EPIC_BIG_VALUE, i, j );    // крестики
                    //test = runMinMax( isCross ? PT_ZERO : PT_CROSS, ++GameDown, bestMove_y, bestMove_x, -EPIC_BIG_VALUE, EPIC_BIG_VALUE, i, j );
                    //map[i][j] = PT_NON_ONE;

                    if ( test > help_var){
                        help_var = test;
                    }
                    if( test > max ){
                        map[bestMove_y][bestMove_x] = PT_NON_ONE;
                        max = test;
                        bestMove_y = i;
                        bestMove_x = j;
                    }

                    if (isCross)
                         alpha = qMax(alpha, test);
                    else
                        beta = qMin(beta, test);
                    if (beta < alpha)
                        break;

                }
            }
        }
    }
    qDebug() << help_var <<"max в глубине счет";

    map[bestMove_y][bestMove_x] = id_1;

    return max;
}

int Output::calculate(char id,int y,int x){
    //Подсчет оценочной функции
    //Ставим в массиве временно значение == id
    map[y][x] = id;
    int series_length = 0;//Текущая длина ряда
    int sum = 0;//Общее значение оценочной функции

    ///////////Расчет сверху вниз/////////
        //Проход по каждой клетке, которая может входить в ряд
        for (int i = 0; i < 5; i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((y-4+i) < 0) continue;
            if ((y+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ( (map[y-4+i+j][x] != id) && (map[y-4+i+j][x] != 0) ) // если не id и не "пусто", то серия ряда 0
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if ( map[y-4+i+j][x] != 0)
                    series_length++; //Ряд увеличивается
            }
            if (series_length == 1) series_length = 0;   //Ряд из самой клетки не учитываем
            if (series_length == 5) series_length = 100; //Выигрышная ситуация, ставим большое значение

            //Плюсуем серию к общей сумме
            int pow_st = valuation_factor;
            if ( series_length == 100 ){
                if (id == 2)
                    sum = 10000;//Большое значение при своем выигрыше
                else
                    sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else{
                for (int i = 0; i < series_length; i++)  //Возводим оценочный коэффициент в степень длины серии
                {
                    pow_st *= valuation_factor;
                }
            }
            sum += pow_st;
            series_length = 0;
        }
    ///////////Расчет слева направо/////////
        //Проход по каждой клетки, которая может входить в ряд
        for (int i = 0; i < 5; i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((x-4+i) < 0) continue;
            if ((x+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ((map[y][x-4+i+j] != id) && (map[y][x-4+i+j] != 0))
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if (map[y][x-4+i+j] != 0)
                    series_length++; //Ряд увеличивается
            }
            if (series_length == 1) series_length = 0; //Ряд из самой клетки не учитываем
            if (series_length == 5) series_length = 100; //Выигрышная ситуация, ставим большое значение

            //Плюсуем серию к общей сумме
            int pow_st = valuation_factor;
            if (series_length == 100)
            {
                if (id == 2)
                    sum = 10000;//Большое значение при своем выигрыше
                else
                    sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else
            {
                for (int i = 0; i < series_length; i++)//Возводим оценочный коэффициент в степень длины серии
                    {
                        pow_st *= valuation_factor;
                    }
            }
            sum += pow_st;
            series_length = 0;
        }

    ///////////Расчет по диагонали с левого верхнего/////////
        //Проход по каждой клетки, которая может входить в ряд
        for (int i = 0; i < 5; i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((y-4+i) < 0) continue;
            if ((x-4+i) < 0) continue;
            if ((x+i) > (SizeBoard - 1)) break;
            if ((y+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ((map[y-4+i+j][x-4+i+j] != id) && (map[y-4+i+j][x-4+i+j] != 0))
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if (map[y-4+i+j][x-4+i+j] != 0)
                    series_length++; //Ряд увеличивается
            }

            if (series_length == 1)
                series_length = 0; //Ряд из самой клетки не учитываем
            if (series_length == 5)
                series_length = 100; //Выигрышная ситуация, ставим большое значение
            //Плюсуем серию к общей сумме

            int pow_st = valuation_factor;
            if (series_length == 100)
            {
                if (id == 2)
                    sum = 10000;//Большое значение при своем выигрыше
                else
                    sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else
            {
                for (int i = 0; i < series_length; i++)//Возводим оценочный коэффициент в степень длины серии
                {
                    pow_st *= valuation_factor;
                }
            }
            sum += pow_st;
            series_length = 0;
        }

    ///////////Расчет по диагонали с левого нижнего/////////
        //Проход по каждой клетки, которая может входить в ряд
        for (int i = 0; i < 5;i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((x-4+i) < 0) continue;
            if ((y+4-i) > (SizeBoard - 1)) continue;
            if ((y-i) < 0) break;
            if ((x+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ( (map[y+4-i-j][x-4+i+j] != id) && (map[y+4-i-j][x-4+i+j] != 0) )
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if (map[y+4-i-j][x-4+i+j] != 0)
                    series_length++; //Ряд увеличивается
            }
            if (series_length == 1)
                series_length = 0; //Ряд из самой клетки не учитываем
            if (series_length == 5)
                series_length = 100; //Выигрышная ситуация, ставим большое значение

            //Плюсуем серию к общей сумме
            int pow_st = valuation_factor;
            if (series_length == 100)
            {
            if (id == 2)
                sum = 10000;//Большое значение при своем выигрыше
            else
                sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else
            {
                for (int i = 0; i < series_length; i++)//Возводим оценочный коэффициент в степень длины серии
                {
                    pow_st *= valuation_factor;
                }
            }
            sum += pow_st;
            series_length = 0;
        }

        //Возвращаем исходное значение
        if( max == 0)
            map[y][x] = 0;
        return sum;
}

int Output::calculate_2(char id,int y,int x){
    //Подсчет оценочной функции
    //Ставим в массиве временно значение == id
    map[y][x] = id;
    int series_length = 0;//Текущая длина ряда
    int sum = 0;//Общее значение оценочной функции

    ///////////Расчет сверху вниз/////////
        //Проход по каждой клетке, которая может входить в ряд
        for (int i = 0; i < 5; i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((y-4+i) < 0) continue;
            if ((y+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ( (map[y-4+i+j][x] != id) && (map[y-4+i+j][x] != 0) ) // если не id и не "пусто", то серия ряда 0
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if ( map[y-4+i+j][x] != 0)
                    series_length++; //Ряд увеличивается
            }
            if (series_length == 1) series_length = 0;   //Ряд из самой клетки не учитываем
            //if (series_length == 5) series_length = 100; //Выигрышная ситуация, ставим большое значение

            //Плюсуем серию к общей сумме
            int pow_st = valuation_factor;
            if ( series_length == 100 ){
//                if (id == 2)
//                    sum = 10000;//Большое значение при своем выигрыше
//                else
//                    sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else{
                for (int i = 0; i < series_length; i++)  //Возводим оценочный коэффициент в степень длины серии
                {
                    pow_st *= valuation_factor;
                }
            }
            sum += pow_st;
            series_length = 0;
        }
    ///////////Расчет слева направо/////////
        //Проход по каждой клетки, которая может входить в ряд
        for (int i = 0; i < 5; i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((x-4+i) < 0) continue;
            if ((x+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ((map[y][x-4+i+j] != id) && (map[y][x-4+i+j] != 0))
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if (map[y][x-4+i+j] != 0)
                    series_length++; //Ряд увеличивается
            }
            if (series_length == 1) series_length = 0; //Ряд из самой клетки не учитываем
            //if (series_length == 5) series_length = 100; //Выигрышная ситуация, ставим большое значение

            //Плюсуем серию к общей сумме
            int pow_st = valuation_factor;
            if (series_length == 100)
            {
//                if (id == 2)
//                    sum = 10000;//Большое значение при своем выигрыше
//                else
//                    sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else
            {
                for (int i = 0; i < series_length; i++)//Возводим оценочный коэффициент в степень длины серии
                    {
                        pow_st *= valuation_factor;
                    }
            }
            sum += pow_st;
            series_length = 0;
        }

    ///////////Расчет по диагонали с левого верхнего/////////
        //Проход по каждой клетки, которая может входить в ряд
        for (int i = 0; i < 5; i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((y-4+i) < 0) continue;
            if ((x-4+i) < 0) continue;
            if ((x+i) > (SizeBoard - 1)) break;
            if ((y+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ((map[y-4+i+j][x-4+i+j] != id) && (map[y-4+i+j][x-4+i+j] != 0))
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if (map[y-4+i+j][x-4+i+j] != 0)
                    series_length++; //Ряд увеличивается
            }

            if (series_length == 1)
                series_length = 0; //Ряд из самой клетки не учитываем
//            if (series_length == 5)
//                series_length = 100; //Выигрышная ситуация, ставим большое значение
            //Плюсуем серию к общей сумме

            int pow_st = valuation_factor;
            if (series_length == 100)
            {
//                if (id == 2)
//                    sum = 10000;//Большое значение при своем выигрыше
//                else
//                    sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else
            {
                for (int i = 0; i < series_length; i++)//Возводим оценочный коэффициент в степень длины серии
                {
                    pow_st *= valuation_factor;
                }
            }
            sum += pow_st;
            series_length = 0;
        }

    ///////////Расчет по диагонали с левого нижнего/////////
        //Проход по каждой клетки, которая может входить в ряд
        for (int i = 0; i < 5;i++)
        {
            //Проверка, не вышли ли за границы поля
            if ((x-4+i) < 0) continue;
            if ((y+4-i) > (SizeBoard - 1)) continue;
            if ((y-i) < 0) break;
            if ((x+i) > (SizeBoard - 1)) break;

            //Проход по всем возможным рядам, отстоящим от клетки не более чем на 5
            for (int j = 0; j < 5; j++)
            {
                if ( (map[y+4-i-j][x-4+i+j] != id) && (map[y+4-i-j][x-4+i+j] != 0) )
                {
                    //Конец ряда
                    series_length = 0;
                    break;
                }
                if (map[y+4-i-j][x-4+i+j] != 0)
                    series_length++; //Ряд увеличивается
            }
            if (series_length == 1)
                series_length = 0; //Ряд из самой клетки не учитываем
//            if (series_length == 5)
//                series_length = 100; //Выигрышная ситуация, ставим большое значение

            //Плюсуем серию к общей сумме
            int pow_st = valuation_factor;
            if (series_length == 100)
            {
//            if (id == 2)
//                sum = 10000;//Большое значение при своем выигрыше
//            else
//                sum = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
            }
            else
            {
                for (int i = 0; i < series_length; i++)//Возводим оценочный коэффициент в степень длины серии
                {
                    pow_st *= valuation_factor;
                }
            }
            sum += pow_st;
            series_length = 0;
        }

        //Возвращаем исходное значение

        map[y][x] = 0;
        return sum;
}

                /// Function for Widget

void Output::slotButtonClicked( )
{
    if ( !(comVar->playerLocked) ){
         QPushButton* button = dynamic_cast<QPushButton*>( sender() );
         int row = button->property("row").toInt();
         int column = button->property("column").toInt();

         int best_x = 0, best_y = 0;

         int win;

         if (comVar->tictacPlayer){
            map[row][column] = PT_CROSS;

            button->setStyleSheet(StyleHelper::getActiveCrossButtonStyle());
            win = runMinMax(PT_ZERO, 0, best_y, best_x, -EPIC_BIG_VALUE, EPIC_BIG_VALUE);
            //win = runMinMax(PT_ZERO, best_y, best_x);

            //button->setStyleSheet( StyleHelper::getButtonStyle() );
            buttons2DVector[best_y][best_x]->setStyleSheet(StyleHelper::getActiveZeroButtonStyle());


         }
         else{
             map[row][column] = PT_ZERO;
             button->setStyleSheet(StyleHelper::getActiveZeroButtonStyle());;
             win = runMinMax(PT_CROSS, 0, best_y, best_x, -EPIC_BIG_VALUE, EPIC_BIG_VALUE);
             //win = runMinMax(PT_CROSS, best_y, best_x);
             buttons2DVector[best_y][best_x]->setStyleSheet(StyleHelper::getActiveCrossButtonStyle());
             ///

         }

//         if( win >= 5000 && win < 10000){
//             comVar->playerLocked = true;
//             qDebug() << "Game Over!";
//         }
         qDebug() << win << " = win";
         max = 0;
         //qDebug() << " map[" << row << "][" << column << "] = " << "X";
         //qDebug() << " map[" << best_y << "][" << best_x << "] = " << "0";
    }

}

void Output::startSlotButton()
{
    //QPushButton* button = dynamic_cast<QPushButton*>( sender() );
    comVar->playerLocked = ( !(comVar->playerLocked) );

    if( comVar->playerLocked ){
        LockButtons();
    }
    else{
        UnlockButtons();
    }

    clearingScreen();
    if( !comVar->tictacPlayer && !(comVar->playerLocked)){

        int best_x, best_y;
        best_y = rand() % 5 + 8;
        best_x = rand() % 5 + 8;

        qDebug() << best_y << best_x;
        map[best_y][best_x] = PT_CROSS;
        buttons2DVector[best_y][best_x]->setStyleSheet(StyleHelper::getActiveCrossButtonStyle());
}

}
void Output::clearingScreen(){
    initMas();
}

void Output::LockButtons()
{
    for ( int i = 0; i < SizeBoard; i++ ){
        for ( int j = 0; j < SizeBoard; j++ ){
            buttons2DVector[i][j]->setStyleSheet(StyleHelper::getButtonStyleLock());
        }
    }
}

void Output::UnlockButtons()
{
    for ( int i = 0; i < SizeBoard; i++ ){
        for ( int j = 0; j < SizeBoard; j++ ){
            buttons2DVector[i][j]->setStyleSheet((StyleHelper::getButtonStyleUnlock()));
        }
    }
}

void Output::initMas(){
    for(int i = 0; i < SizeBoard; i++)
        for ( int j = 0; j < SizeBoard; j++){
            map[i][j] = 0;
        }
}

void Output::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    //QPixmap pix(":/resourses/BackgroundGameField.png");
    p.setBrush( QColor::fromRgbF(0,0,0) );
    p.drawRect(0, 0, width(), height() - 18);
}



