# ITC: Tic-Tac
Игра крестики нолики на ~~бесконечном~~ большом поле. Задача первым поставить 5 в ряд. 
Игра написана на C++ с использованием библеотек QT Creator. В игре реализован бот, по алгоритму мин-макс с альфа-беттой отсечением.

## Описание 2х основных функций
+ int Output::runMinMax( Output::PlayerType plr, int GameDown, int& bestMove_y, int& bestMove_x ) 
Функция реализует алгоритм МинМакса с глубиной «GameDown». Функия выбирает лучшее решение компьютера, после условно ставит на лучшее место крестик или нолик (зависит за кого играет компьютер), далее выбирает лучшее решение для человека, если оценочная функция человека будет выше чем оценочная функция компьютера, то компьютер выбирает ход, где лучше для человека.
Оптимизацией функции является алгоритм Альфа-бетта. В функцию дополнительно вводятся два целочисленный числа типа int: alpha и beta. В начале они приравниваются к -30000 и +30000 соответственно. Далее, когда функция проходит клетку альфа приравнивается, если крестик, то к максимуму от alpha и от test, если нолик, то бета она приравнивается к минимуму от beta и test. И если beta < alpha, то процесс поиска наилучшего хода останавливается.

+ int Map::calculate(int id, int x, int y)
Задача функции вычислить число, для клетки поля с координатами «x» «y». Условно подставив туда крестик или нолик, в зависимости какой id был передан в функцию. Смысл функции состоит в том, что она считает длину каждого ряда (слева направо, сверху вниз, по диагонали с левого верхнего - в правый нижний и по диагонали с левого нижнего - в правый верхний). Далее, она возводит число (valuation_factor) в степень длины каждого ряда (по-отдельности) (series_length). Полученная сумма возвращается в качестве результата функции. Если найден победный ход возвращается число 10 тыс., если найден ход, где бот может проиграть, то возвращается число 5 тыс.

## Примеры партий 

![image](https://github.com/iSpaxer/ITT-Infinity_TicTac/assets/99914669/e815c3da-cf10-441b-b66b-bfc238691e5e)
![image](https://github.com/iSpaxer/ITT-Infinity_TicTac/assets/99914669/a770dbd3-ece6-411f-a538-169fb4a23031)

