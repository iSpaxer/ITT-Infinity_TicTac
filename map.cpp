#include "map.h"
#include <iostream>
#include <windows.h>


Map::Map(){

    initMass( map );
    initMass(calc_fields);
}

Map::~Map(){
}

void Map::initMass( char (*m)[SizeBoard] ){

    for ( int i = 0; i < SizeBoard; i++ ){
        for ( int j = 0; j < SizeBoard; j++ ){
                m[i][j] = 0;
        }
    }
}

void Map::initMass( int (*m)[SizeBoard] ){
    for ( int i = 0; i < SizeBoard; i++ ){
        for ( int j = 0; j < SizeBoard; j++ ){
                m[i][j] = -1;
        }
    }
}

void Map::clear_map( ){
    for ( int i = 0; i < SizeBoard; i++ ){
        for ( int j = 0; j < SizeBoard; j++ ){
            if (map[i][j] != 2 || map[i][j] != 1){
                map[i][j] = 0;
            }
        }
    }
}

void Map::show(){
    std::cout << " |";
    for ( int i = 0; i < SizeBoard; i++){
        std::cout << i << '|';
    }
    std::cout << std::endl;

    for ( int i = 0; i < SizeBoard; i++){
        for ( int j = 0; j < SizeBoard; j++ ){
            if (j == 0){
                std::cout << i << '|';
            }
            if (map[i][j] == 0){
                std::cout << ' ';
            }
            if (map[i][j] == 1){
                std::cout << '0';
            }
            if (map[i][j] == 2){
                std::cout << 'X';
            }
            std::cout <<  "|";
        }
        std::cout << std::endl;
    }
}

void Map::put(){
    int x,y;
    int count = 0;
    char term;
    do{
        count++;
        std::cout << "Enter y: ";
        std::cin >> y;
        std::cout << "Enter x: ";
        std::cin >> x;
        if ( map[y][x] == 0 ){
            count % 2 == 0 ? term = 1 : term = 2;
            map[y][x] = term;
        }
        else{
            count--;
        }

        system("cls");
        show();
    }
    while( x != 5);
}

void Map::ii(){

    //Расчитываем оценочную функцию для всех клеток
    for (int i = 0; i < SizeBoard; i++)
    {
        for (int j = 0; j < SizeBoard; j++)
        {
            if (map[i][j] == 0)
            {
                //Расчет оценочной функции
                calc_fields[i][j] = calculate(2,i,j) + (int)((float)calculate(1,i,j)*attack_factor);       // 2 - крестик, 1 - нолик

            }
        }
    }
}

int Map::calculate(char id,int y,int x){
    //Подсчет оценочной функции
    //Ставим в массиве временно значение == id
    map[y][x] = id;
    int series_length = 0;//Текущая длина ряда
    int sum = 0;//Общее значение оценочной функции

    ///////////Расчет сверху вниз/////////
        //Проход по каждой клетки, которая может входить в ряд
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
                    return 10000;//Большое значение при своем выигрыше
                else
                    return 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
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
                    return 10000;//Большое значение при своем выигрыше
                else
                    return 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
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
                    pow_st = 10000;//Большое значение при своем выигрыше
                else
                    pow_st = 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
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
                return 10000;//Большое значение при своем выигрыше
            else
                return 5000; //Большое значение при выигрыше соперника, но меньшее, чем при своем
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

void Map::show_ii( ){
    for ( int i = 0; i < SizeBoard; i++){
        for ( int j = 0; j < SizeBoard; j++ ){
            std::cout << calc_fields[i][j] << '|';
        }
        std::cout << std::endl;
    }
}
