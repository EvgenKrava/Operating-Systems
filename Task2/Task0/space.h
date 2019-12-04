/*
Задание No0
В пространстве заданы n материальных точек. С некоторого момента точка с
наименьшей массой исчезает, передавая свою массу ближайшей к ней точке. Так
продолжается до тех пор, пока не останется одна точка. Реализовать этот процесс и найти
оставшуюся точку.
 */
#ifndef TASK2_SPACE_H
#define TASK2_SPACE_H
typedef struct point Point;

struct point {
    int value;
    int x;
    int y;
    int z;
};

typedef struct space Space;

struct space {
    Point **points;
    int size;
};

Point *play(int pointsCount);

Point *playWithPoints(Point **points, int pointsCount);

#endif //TASK2_SPACE_H
