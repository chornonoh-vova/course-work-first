#ifndef MAIN_TYPES
#define MAIN_TYPES

//структуры для курсовой
//тема - космос
//нижний уровень - спутники
//средний уровень - планеты
//верхний уровень - звезды

#include <iostream>
#include <string.h>

using namespace std;

#define SIZE_FIRST 3
#define DELTA 3
#define COUNT_POZ -1
#define SIZE_POZ -2

//описание типов
//нижний уровень
typedef struct {
    char sattelite_name[25];        //имя спутника
    char planet_name[25];     //планета, вокруг которой вращается спутник
    double speed;            //скорость вращения (м/с)
} list_sattelite;

//средний уровень
typedef struct {
    char name_of_planet[25];        //название планеты
    double weight;			//масса планеты
    double radius;			//радиус планеты
    void** subLvl;                  //указатель на подсписок спутников
} list_planet;

//верхний уровень
typedef struct {
    char name_of_star[25];          //название
    double weight;              //масса звезды
    double distance;			//расстояние от земли до звезды
    void** subLvl;                  //указатель на подсписок групп
} list_star;

//описание типа для указателя на функцию сравнения
typedef int (*cmp_func_find)(const void* val, char *key);

//специальные функции для доступа к указателю
//на нижний уровень, "корню" мультисписка
void ** getRoot();
void setRoot(void ** p);

#endif // MAIN_TYPES

