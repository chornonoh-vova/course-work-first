#include "main_types.h"

//инициализация списка(создание массива указателей начального размера
void** initArray()
{
   //запрашиваем память для нового массива
    void** p = new void*[SIZE_FIRST+2];

    //опускаем указатель вниз на два элемента
    //чтобы он указывал на первый элемент, а не на служебные
    p = p + 2;

    //заполняем служебный элемент - кол-во элементов списка
    ((int*)p)[COUNT_POZ] = 0;

    //заполняем служебный элемент - размер массива
    ((int*)p)[SIZE_POZ] = SIZE_FIRST;

    for(int i = 0; i < ((int*)p)[SIZE_POZ]; i++) {
        p[i] = NULL;
    }

    return p;
}

//расширение массива на DELTA элементов
void expandArray(void** &array, int &size, int count)
{
    int oldSize = size; //сохранение старого размера массива
    size += DELTA;      //определение нового размера массива

    //вспомогательный указатель на массив указателей
    //выделение места под него
    void** arrayNew = new void*[size + 2];

    //копируем старый массив индексов в новый массив

    for (int i = 0; i < oldSize; i++) {
        arrayNew[i + 2] = array[i];
    }

    array = array - 2;

    delete [] array;

    array = arrayNew + 2;

    ((int*)array)[COUNT_POZ] = count;
    ((int*)array)[SIZE_POZ] = size;
}

int cmp_star(const void* val, char *key) {
    if (strcmp(((list_star*)val)->name_of_star, key) == 0) {
        return 0;
    } else if (strcmp(((list_star*)val)->name_of_star, key) == 1) {
        return 1;
    } else {
        return -1;
    }
}

int cmp_planet(const void* val, char *key) {
    if (strcmp(((list_planet*)val)->name_of_planet, key) == 0) {
        return 0;
    } else if (strcmp(((list_planet*)val)->name_of_planet, key) == 1) {
        return 1;
    } else {
        return -1;
    }
}
int cmp_sattelite(const void* val, char *key) {
    if (strcmp(((list_sattelite*)val)->sattelite_name, key) == 0) {
        return 0;
    } else if (strcmp(((list_sattelite*)val)->sattelite_name, key) == 1) {
        return 1;
    } else {
        return -1;
    }
}

void findElem(void** &start, char *key, int &pos, bool &findOK, cmp_func_find func_cmp) {
    int	middl;
    int	hi, low;
    int resultCompare;
    findOK = false;

    if (((int*)start)[COUNT_POZ] == 0) {
        pos = 0;
        return;
    }

    /*Устанавливаем границы поиска на границы массива*/
    low = 0;
    hi = ((int*)start)[COUNT_POZ] - 1;

    do {
        middl = (hi + low) / 2 ; /*индекс среднего элемента*/
        /*Вызов функции сравнения при помощи указателя на функцию*/

        resultCompare= func_cmp(start[middl], key);

        if (resultCompare== 0) {
            pos = middl; /*Элемент найден*/
            findOK = true;      /*элемент найден*/
            return;
        } else if (resultCompare == 1) {
            hi = middl - 1;
        } else {
            low = middl + 1;
        }

    } while  (low <= hi);

    pos = low;
}

void addElement(void **&start, void *p_new, int pos) {
    int count = ((int*)start)[COUNT_POZ];
    int size = ((int*)start)[SIZE_POZ];

    if (count == size) {
        expandArray(start, size, count);
    }

    if (pos == count) {
        start[pos] = p_new;
    } else {
        for (int k = count - 1; k >= pos; k--) {
            start[k+1] = start[k];
        }
        start[pos] = p_new;
    }
    count ++;

    ((int*)start)[COUNT_POZ] = count;
}

void addElementStar(void** &start, list_star* p_new) {
    p_new->subLvl = initArray();

    int posFinded;
    bool findOK;

    findElem(start, p_new -> name_of_star, posFinded, findOK, cmp_star);

    addElement(start, p_new, posFinded);
}

void addElementPlanet(void **&start, list_planet *p_new) {
    p_new->subLvl = initArray();

    int posFinded;
    bool findOK;

    findElem(start, p_new -> name_of_planet, posFinded, findOK, cmp_planet);

    addElement(start, p_new, posFinded);
}

void addElementSattelite(void **&start, list_sattelite *p_new) {
    int posFinded;
    bool findOK;

    findElem(start, p_new -> sattelite_name, posFinded, findOK, cmp_sattelite);

    addElement(start, p_new, posFinded);
}

void clear()
{
    void **starArray = getRoot();
    int starCount = ((int*)starArray)[COUNT_POZ];

    if (starArray == NULL || starCount == 0) {
        return;
    }
    for (int i = 0; i < starCount; i++) {

        void **planetArray = ((list_star*)starArray[i])->subLvl;
        int planetCount = ((int*)planetArray)[COUNT_POZ];

        if (planetCount == 0) {
            planetArray = planetArray - 2;
            delete []planetArray;
        }

        for (int j = 0; j < planetCount; j++) {

            void **satteliteArray = ((list_planet*)planetArray[j])->subLvl;
            int satteliteCount = ((int*)satteliteArray)[COUNT_POZ];

            if (satteliteCount == 0) {
                satteliteArray = satteliteArray - 2;
                delete []satteliteArray;
            }

            for (int k = 0; k < satteliteCount; k++) {
                delete ((list_sattelite*)satteliteArray[k]);
            }

            satteliteArray = satteliteArray - 2;
            delete []satteliteArray;
            delete ((list_planet*)planetArray[j]);
        }

        planetArray = planetArray - 2;
        delete []planetArray;
        delete ((list_star*)starArray[i]);
    }

    starArray = starArray - 2;
    delete []starArray;

    setRoot(initArray());
}

void clearListPlanet(void** &start)
{
    if (start == NULL) {
        return;
    }

    int planetCount = ((int*)start)[COUNT_POZ];

    for (int i = 0; i < planetCount; i++) {

        void **satteliteArray = ((list_planet*)start[i])->subLvl;
        int satteliteCount = ((int*)start)[COUNT_POZ];

        if (satteliteArray != NULL) {

            for (int j = 0; j < satteliteCount; j++) {

                delete (list_sattelite*)satteliteArray[j];
            }

            satteliteArray = satteliteArray - 2;
            delete []satteliteArray;
        }

        delete (list_planet*)start[i];
    }

    start = start - 2;
    delete []start;

    start = initArray();
}

void clearListSattelite(void** &start)
{
    if (start == NULL) {
        return;
    }

    int satteliteCount = ((int*)start)[COUNT_POZ];

    for (int i = 0; i < satteliteCount; i++) {

        delete (list_sattelite*)start[i];
    }

    start = start - 2;
    delete []start;

    start = initArray();
}
