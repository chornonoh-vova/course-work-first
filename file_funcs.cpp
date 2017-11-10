#include "file_funcs.h"

void save_to_file(void **&start, const char *pathway)
{
    //открываем файл, переданный в pathway в режиме записи
    FILE* file = fopen(pathway, "wb");

    //если мультисписок пуст - выход из функции
    if (start == NULL) {
        fclose(file);
        return;
    }

    void **starArray = start;
    void **planetArray = NULL;
    void **satteliteArray = NULL;
    int starCount = ((int*)starArray)[COUNT_POZ];
    int planetCount = 0;
    int satteliteCount = 0;

    //если кол-во звезд равно 0, закрываем файл и выходим
    if (starCount == 0) {
        fclose(file);
        return;
    }

    //запись в файл кол-ва звезд
    fwrite(&starCount, sizeof(int), 1, file);

    //проход по верхнему уровню и запись
    for (int i = 0; i < starCount; i++) {

        //запись в файл одной звезды
        fwrite((list_star*)starArray[i], sizeof(list_star), 1, file);

        //переход к уровню планета
        planetArray = ((list_star*)starArray[i])->subLvl;
        planetCount = ((int*)planetArray)[COUNT_POZ];

        //запись в файл кол-ва планет
        fwrite(&planetCount, sizeof(int), 1, file);

        //если подсписок звезд не пуст, проходим по нему
        if (planetCount != 0) {

            for (int j = 0; j < planetCount; j++) {

                //запись в файл одной планеты
                fwrite((list_planet*)planetArray[j], sizeof(list_planet), 1, file);

                //переход к уровню спутник
                satteliteArray = ((list_planet*)planetArray[j])->subLvl;
                satteliteCount = ((int*)satteliteArray)[COUNT_POZ];

                //запись в файл кол-ва спутников
                fwrite(&satteliteCount, sizeof(int), 1, file);

                //если подсписок планет не пуст, проходим по нему
                if (satteliteCount != 0) {

                    for (int k = 0; k < satteliteCount; k++) {
                        //запись в файл одного спутника
                        fwrite((list_sattelite*)satteliteArray[k], sizeof(list_sattelite), 1, file);
                    }//end for_k
                }
                //если же подсписок плнетв пуст, ничего не записываем
            }//end for_j
        }
        //если же подсписок звезд пуст, ничего не записываем
    }//end for_i

    //после прохода по всему мультисписку закрываем файл
    fclose(file);
}

void restore_from_file(void **&start, const char *pathway)
{
    FILE *file = fopen(pathway, "rb");

    if (file == NULL) {
        return;
    }

    void **starArray = start;
    int starCount = 0;

    //читаем из файла кол-во звезд
    fread(&starCount, sizeof(int), 1, file);

    if (starCount == 0) {
        fclose(file);
        return;
    }

    //в цикле читаем весь мультисписок
    for(int i = 0; i < starCount; i++) {
        //создаем новый элемент в куче и считываем информацию из файла
        list_star *buf = new list_star;
        fread(buf, sizeof(list_star), 1, file);

        //добавляем элемент в список звезд
        addElementStar(starArray, buf);

        //читаем из файла кол-во планет
        void **planetArray = ((list_star*)starArray[i])->subLvl;
        int planetCount = 0;

        fread(&planetCount, sizeof(int), 1, file);

        if (planetCount != 0) {
            for (int j = 0; j < planetCount; j++) {
                //создаем новый элемент в куче и считываем информацию из файла
                list_planet *buf = new list_planet;
                fread(buf, sizeof(list_planet), 1, file);

                //добавляем элемент в список планет
                addElementPlanet(planetArray, buf);

                //читаем из файла кол-во спутников
                void **satteliteArray = ((list_planet*)planetArray[j])->subLvl;
                int satteliteCount = 0;

                fread(&satteliteCount, sizeof(int), 1, file);

                if (satteliteCount != 0) {
                    for (int k = 0; k < satteliteCount; k++) {
                        //создаем новый элемент в куче и считываем информацию из файла
                        list_sattelite *buf = new list_sattelite;
                        fread(buf, sizeof(list_sattelite), 1, file);
                        //добавляем элемент в список спутников
                        addElementSattelite(satteliteArray, buf);
                    }//end for_k
                }
                //если подсписок планет пуст, ничего не делаем
            }//end for_j
        }
        //если подсписок звезд пуст, ничего не делаем
    }//end for_i
    //закрываем файл
    fclose(file);
}
