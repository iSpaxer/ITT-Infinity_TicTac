#ifndef MAP_H
#define MAP_H

#define SizeBoard 19

class Map {

private:
    char map[SizeBoard][SizeBoard];//Игровое поле ( = 0 - ничего нет, = 1 - нолик, id
    //= 2 - крестик, = 3 - выигравший нолик, = 4 - выигравший крестик
    //= 5 - последний поставленный нолик, = 6 - последний поставленный крестик)
    int calc_fields[SizeBoard][SizeBoard];    //Рассчитанное значение оценочной функции

    int left_up,   right_up;       //нужны для оптимизации подсчёта оценочной функции
    int left_down, right_down;

    int last_x; //координаты последне поставленного крестика или нолика
    int last_y;

    float attack_factor    = 1;  //Коэффициент агрессивности ИИ (1 - по умолчанию)
    int   valuation_factor = 3; //Оценочный коэффициент

    bool end_game = false;

    void clear_map();
    int  calculate(char id, int x, int y);//++
public:
    Map( );
    ~Map( );

    void initMass( char (*m)[SizeBoard] );
    void initMass( int  (*m)[SizeBoard] );//++

    void ii( );//++
    void show( );
    void show_ii( );
    void put( );//++
};


#endif // MAP_H
