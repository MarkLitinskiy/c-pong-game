#include <stdio.h>

int draw(int pointLeft, int pointRight, int leftPositionY,
int rightPositionY, int ballPositionX, int ballPositionY);
int moveBall();
int clash();
int winner(int left, int right);
int ballX = 40;  // Координата мяча X
int ballY = 12;  // Координата мяча Y
int vectorBallX = 1;  // Скорость мяча по X
int vectorBallY = 0;  // Скорость мяча по Y
int leftPosY = 12;  // Положение левой ракетки по Y
int rightPosY = 12;  // Положение правой ракетки по Y
const int leftPosX = 10;  // Положение левой ракетки по X
const int rightPosX = 70;  // Положение правой ракетки по X
int pointL = 0;  // Очки левого игрока
int pointR = 0;  // Очки правого игрока
int winCheck = 0;  // Флаг для конца игры
char lastButton = ' ';  // Флаг последней считанной клавиши

int main() {
    draw(pointL, pointR, leftPosY, rightPosY, ballX, ballY);  // Прорисовка начала
    while (winCheck == 0) {
        switch (getchar()) {
            case ('z'):
                lastButton = 'z';
                leftPosY = leftPosY + 1;  // Смещение левой ракетки вверх
                moveBall();
                clash();
                draw(pointL, pointR, leftPosY, rightPosY, ballX, ballY);
                break;
            case ('a'):
                lastButton = 'a';
                leftPosY = leftPosY - 1;  // Смещение левой ракетки вниз
                moveBall();
                clash();
                draw(pointL, pointR, leftPosY, rightPosY, ballX, ballY);
                break;
            case ('m'):
                lastButton = 'm';
                rightPosY = rightPosY + 1;  // Смещение правой ракетки вверх
                moveBall();
                clash();
                draw(pointL, pointR, leftPosY, rightPosY, ballX, ballY);
                break;
            case ('k'):
                lastButton = 'k';
                rightPosY = rightPosY - 1;  // Смещение правой ракетки вниз
                moveBall();
                clash();
                draw(pointL, pointR, leftPosY, rightPosY, ballX, ballY);
                break;
            case (' '):
                lastButton = ' ';
                moveBall();
                clash();
                draw(pointL, pointR, leftPosY, rightPosY, ballX, ballY);
                break;
        }
    }
    return 0;
}

int draw(int pointLeft, int pointRight, int leftPositionY,
    int rightPositionY, int ballPositionX,
        int ballPositionY) {  // Функция для отрисовки и удаления всего поля по пробелу
    /* pointLeft/Right - переменная счёта,
    left/rightPosition - центральные координаты вертикали для левой и правой ракетки,
    ballPositionX/Y - координаты мяча */
    printf("\033[0d\033[2J");  // Удаление всего в консоли
    printf("                              |Левый: %d||Правый: %d|\n", pointLeft,
           pointRight);  // Выведение счёта и переход на новую строку
    if (winCheck == 1) {  // Проверочка на отрисовку победы
        printf("Левый победил!");
        return 0;
    }
    if (winCheck == 2) {  // Проверочка на отрисовку победы
        printf("Правый победил!");
        return 0;
    }
    int flag1 = 0;  // Флаг для отрисовки ракеток, мяча и границ, чтобы смещения не было
    for (int high = 0; high <= 25; high++) {
        for (int width = 0; width <= 80; width++) {
            if (high == 0 || high == 25) {  // Отрисовка верхних границ
                printf("-");
                flag1 = 1;
            }
            if  (((high > 0 && high < 25) && width == 0) || (high > 0 && high < 25
                   && width == 80)) {  // Отрисовка левых и правых границ
                printf("|");
                flag1 = 1;
            }
            if (high == ballPositionY && width == ballPositionX) {  // Отрисовка мяча
                printf("*");
                flag1 = 1;
            }
            if (high >= 1 && high <= 24 && width == 40 && (ballPositionY != high ||
                ballPositionX != width)) {  // Отрисовка линии в середине
                printf("|");
                flag1 = 1;
            }
            if ((high == leftPositionY && width == leftPosX) || (high + 1 == leftPositionY &&
                width == leftPosX) || (high - 1 == leftPositionY &&
                width == leftPosX)) {  // Отрисовка левой ракетки
                printf("|");
                flag1 = 1;
            }
            if ((high == rightPositionY && width == rightPosX) || (high + 1 == rightPositionY
                && width == rightPosX) || (high - 1 == rightPositionY &&
                width == rightPosX)) {  // Отрисовка правой ракетки
                printf("|");
                flag1 = 1;
            }
            if (width == 80) {  // Перевод каретки на отрисовку следующей строки
            printf("\n");
                flag1 = 1;
            }
            if (flag1 == 0)  // Если ничего не нарисовали, то даём пробел
            printf(" ");
            flag1 = 0;  // Обнуление флага
        }
    }
    return 0;
}

int moveBall() {
    // Смещение координат мяча согласно векторам
    ballX = ballX + vectorBallX;
    ballY = ballY + vectorBallY;
    return 0;
}

int clash() {
    // Обработка столкновений от верхних и нижних границ
    if ((ballY <= 1 && (ballX >= 1 && ballX <= 78)) || (ballY >= 24 && (ballX >= 1 && ballX <= 78))) {
        vectorBallY = vectorBallY * (-1);  // Изменение вектора Y скорости на противоположный
    }
    /* Обработка столкновений от правой и левой границы
    (+ 1 очко победившему и постановка мяча на старт с вектором X в сторону забившего)*/
    if (ballX <= 1 && (ballY >= 1 && ballY <= 24)) {  // Левая сторона
        pointR = pointR + 1;  // Добавление одного очка
        // Постановка мяча на старт
        ballX = 40;  // Координата мяча X
        ballY = 12;  // Координата мяча Y
        // Постановка ракетки на старт
        leftPosY = 12;
        rightPosY = 12;
        vectorBallX = -1;  // Скорость мяча по X
        vectorBallY = 0;  // Скорость мяча по Y
        winner(pointL, pointR);  // Проверочка на победу
    }
    if (ballX >= 78 && (ballY >= 1 && ballY <= 24)) {  // Правая сторона
        pointL = pointL + 1;  // Добавление одного очка
        // Постановка мяча на старт
        ballX = 40;  // Координата мяча X
        ballY = 12;  // Координата мяча Y
        // Постановка ракетки на старт
        rightPosY = 12;
        leftPosY = 12;
        vectorBallX = 1;  // Скорость мяча по X
        vectorBallY = 0;  // Скорость мяча по Y
        winner(pointL, pointR);  // Проверочка на победу
    }
    // Обработка столкновений с левой ракеткой
    if ((ballX  == leftPosX +1) && (ballY == leftPosY || ballY == leftPosY + 1 || ballY == leftPosY - 1)) {
        vectorBallX = vectorBallX * (-1);
        switch (lastButton) {  // Отражение мяча движущейся ракеткой по касательной
            case ('a'):
                vectorBallY = 1;
                break;
            case ('z'):
                vectorBallY = -1;
                break;
            case ('k'):
                vectorBallY = 1;
                break;
            case ('m'):
                vectorBallY = -1;
                break;
        }
    }
    // Обработка столкновений с правой ракеткой
    if (ballX == rightPosX - 1 && (ballY == rightPosY || ballY == rightPosY + 1 || ballY == rightPosY - 1)) {
        vectorBallX = vectorBallX * (-1);
    switch (lastButton) {  // Отражение мяча движущейся ракеткой по касательной
        case ('a'):
            vectorBallY = 1;
            break;
        case ('z'):
            vectorBallY = -1;
            break;
        case ('k'):
            vectorBallY = 1;
            break;
        case ('m'):
            vectorBallY = -1;
            break;
    }
    }
    // Обработка столкновений ракеток с полями
    if (leftPosY < 2)
        leftPosY++;
    if (leftPosY > 23)
        leftPosY--;
    if (rightPosY < 2)
        rightPosY++;
    if (rightPosY > 23)
        rightPosY--;
    return 0;
}
int winner(int left, int right) {  // Проверочка на победу
    if (left == 21) {
        printf("Левый победил!");
        winCheck = 1;
    }
    if (right == 21) {
        printf("Правый победил!");
        winCheck = 2;
    }
    return 0;
}  // Всё хорошо
