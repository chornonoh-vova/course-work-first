#ifndef MAIN_FUNCS
#define MAIN_FUNCS

//основные функции проекта
#include "main_types.h"

//функции сравнения, на которые можно установить указатель cmp_func_find

//return 0 if element -> name... == key
//return -1 if element -> name... < key
//return 1 if element -> name... > key
int cmp_star(const void* val, char *key);
int cmp_planet(const void* val, char *key);
int cmp_sattelite(const void* val, char *key);

//функции,не зависящие от типа данных

//инициализация массива указателей
//возвращает указатель на созданный массив бестиповых указателей в куче
void** initArray();

//расширение массива на DELTA элементов
//параметры: указатель на "старый" массив указателей(по ссылке) - void** arrray
//           размер массива до расширения(по ссылке) - size
//           кол-во элементов массива(по значению) - count
void expandArray(void** &array, int &size, int count);

//поиск в массиве методом половинного деления
//параметры: указатель на массив, в котором производится поиск start
//           ключ поиска (string key)
//           позиция найденного элемента pos
//           переменная bool для проверки найден ли элемент findOK
//           указатель на функцию сравнения func_cmp
void findElem(void** &start, char *key, int &pos, bool &findOK, cmp_func_find func_cmp);

//функция добавления элемента в массив указателей
//параметры: указатель на массив, в который добавляем start
//           указатель на уже размещенный элемент в памяти p_new
//           позиция элемента для размещения в массиве
void addElement(void** &start,void* p_new, int pos);

void addElementStar(void** &start, list_star* p_new);

void addElementPlanet(void** &start, list_planet* p_new);

void addElementSattelite(void** &start, list_sattelite* p_new);

//удаление всех элементов
void clear();

//удаление элементов на подсписках
void clearListSattelite(void** &start);

void clearListPlanet(void** &start);

#endif // MAIN_FUNCS

