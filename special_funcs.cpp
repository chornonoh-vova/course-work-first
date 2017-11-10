#include "special_funcs.h"

list_planet *higher_radius(void **start)
{
    //если список пуст, выход из функции
    if (start == NULL) return NULL;
    //рабочие переменные для прохода по списку
    void **starArray = start;
    int starCount = ((int*)starArray)[COUNT_POZ];
    if (starCount == 0) return NULL;
    //рабочий указатель для сохранения результата
    list_planet *maxRadius = NULL;
    //рабочие переменные для нахождения максимального радиуса
    double max_radius = 0;

    for (int i = 0; i < starCount; i++) {
        //рабочие переменные для прохода по списку планет
        void **planetArray = ((list_star*)starArray[i])->subLvl;
        int planetCount = ((int*)planetArray)[COUNT_POZ];

        if (planetCount != 0) {
            for (int j = 0; j < planetCount; j++) {
                if (max_radius < ((list_planet*)planetArray[j])->radius) {
                    max_radius = ((list_planet*)planetArray[j])->radius;
                    maxRadius = (list_planet*)planetArray[j];
                }
            }
        }
    }
    return maxRadius;
}

void stars_count()
{
    void **starArray = getRoot();
    int starCount = ((int*)starArray)[COUNT_POZ];

    cout << "\nКоличество звезд в мультисписке: " << starCount << endl;
}
