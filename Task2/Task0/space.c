

#include <stdio.h>
#include "space.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

Space *initRandomPoints(int n);

void printPoints(Space *space);

Point *findSmallerPoint(Space *space);

void printPoint(Point *pPoint);

void killPoint(Space *pSpace, Point *pPoint);

double getDistance(Point *p1, Point *p2);

Point *play(int pointsCount) {
    Space *space = initRandomPoints(pointsCount);
    Point *smaller;
    while (space->size > 0) {
        printf("Space:\n");
        printPoints(space);
        smaller = findSmallerPoint(space);
        killPoint(space, smaller);
    }
    return space->points[0];
}

void killPoint(Space *pSpace, Point *pPoint) {
    double smallestDistance = getDistance(pPoint, pSpace->points[0]);
    Point *nearestPoint = pSpace->points[0];
    for (int i = 0; i < pSpace->size; ++i) {
        double distance = getDistance(nearestPoint, pSpace->points[i]);
        if (smallestDistance > distance) {
            smallestDistance = distance;
            nearestPoint = pSpace->points[i];
        }
    }
    nearestPoint->value = nearestPoint->value + pPoint->value;
    for (int j = 0; j < pSpace->size; ++j) {
        if (pPoint == pSpace->points[j]) {
            for (int i = j; i < pSpace->size - 1; ++i) {
                pSpace->points[i] = pSpace->points[i + 1];
            }
            break;
        }
    }
    free(pPoint);
    pSpace->size = pSpace->size - 1;
}

double getDistance(Point *p1, Point *p2) {
    return sqrt(
            (p1->x - p2->x) * (p1->x - p2->x) +
            (p1->y - p2->y) * (p1->y - p2->y) +
            (p1->z - p2->z) * (p1->z - p2->z));
}


Point *findSmallerPoint(Space *space) {
    Point *smallerPoint = space->points[0];
    for (int i = 0; i < space->size; ++i) {
        if (space->points[i]->value < smallerPoint->value) {
            smallerPoint = space->points[i];
        }
    }
    return smallerPoint;
}


void printPoints(Space *space) {
    for (int i = 0; i < space->size; ++i) {
        printPoint(space->points[i]);
    }
}

void printPoint(Point *pPoint) {
    printf("value: %d\t x: %d, y: %d, z: %d;\n", pPoint->value, pPoint->x, pPoint->y, pPoint->z);
}

Space *initRandomPoints(int n) {
    srand(time(0));
    Space *space = malloc(sizeof(Space));
    space->points = calloc(n, sizeof(Point *));
    for (int i = 0; i < n; ++i) {
        space->points[i] = malloc(sizeof(Point));
        space->points[i]->value = rand() % 100;
        space->points[i]->x = rand() % 100;
        space->points[i]->y = rand() % 100;
        space->points[i]->z = rand() % 100;
    }
    space->size = n;
    return space;
}


