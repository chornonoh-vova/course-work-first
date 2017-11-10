#include <iostream>
#include <windows.h>

#include "main_types.h"
#include "main_funcs.h"
#include "file_funcs.h"
#include "special_funcs.h"

using namespace std;

void **root = initArray();

void ** getRoot() {
    return root;
}

void setRoot(void ** p) {
    root = p;
}

void show_multilist();

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleTitleA("Course work");

    int choise_high;
    int choise_low;

    for (;;) {
        system("cls");
        cout << "Операции с мультисписком космос: \n"
                "\t1. Добавление элемента\n"
                "\t2. Удаление элементов\n"
                "\t3. Вывод мультисписка на экран\n"
                "\t4. Операции с файлами\n"
                "\t5. Специальные операции\n"
                "\t6. Очистка списка и выход из программы\n";
        cout << "Ваш выбор: ";
        cin >> choise_high;

        switch (choise_high) {
        case 1: {
            system("cls");
            cout << "Какой элемент вы хотите добавить:\n"
                    "\t1. Звезда\n"
                    "\t2. Планету в определенную звездную систему\n"
                    "\t3. Спутника к определенной планете\n";
            cout << "Ваш выбор: ";
            cin >> choise_low;

            switch (choise_low) {
            case 1: {
                list_star *p_new = new list_star;

                cout << "\nВведите название звезды: ";
                cin.ignore();
                gets(p_new->name_of_star);

                cout << "\nВведите массу звезды в тоннах: ";
                cin >> p_new->weight;

                cout << "\nВведите расстояние от Земли к звезде:";
                cin >> p_new->distance;

                addElementStar(root, p_new);
            }//case 1
                break;
            case 2: {
                char buf[25];
                cout << "\nВ какую звездную систему добавить новую планету: ";
                cin.ignore();
                gets(buf);

                void **add;
                int pos;
                bool findOK;

                findElem(root, buf, pos, findOK, cmp_star);

                if (!findOK) {
                    cout << "\nЗвезда не найдена!!\n";
                } else {
                    add = ((list_star*)root[pos])->subLvl;

                    list_planet *p_new  = new list_planet;

                    cout << "\nВведите название планеты: ";
                    gets(p_new->name_of_planet);

                    cout << "\nВведите массу планеты: ";
                    cin >> p_new->weight;

                    cout << "\nВведите радиус планеты: ";
                    cin >> p_new->radius;

                    addElementPlanet(add, p_new);
                }
            }//case 2
                break;
            case 3: {
                char buf[25];
                cout << "\nВ какую звезду добавить новый спутник: ";
                cin.ignore();
                gets(buf);

                void **add;
                int pos;
                bool findOK;

                findElem(root, buf, pos, findOK, cmp_star);

                if (!findOK) {
                    cout << "\nЗвезда не найдена!!\n";
                } else {
                    add = ((list_star*)root[pos])->subLvl;

                    cout << "\nВ какую планету добавить новый спутник: ";
                    gets(buf);

                    findElem(add, buf, pos, findOK, cmp_planet);

                    if (!findOK) {
                        cout << "\nПланета не найдена!!\n";
                    } else {
                        void **addnew = ((list_planet*)add[pos])->subLvl;

                        list_sattelite *p_new = new list_sattelite;

                        cout << "\nВведите название спутника: ";
                        gets(p_new->sattelite_name);

                        cout << "\nВведите планету, вокруг которой он вращается: ";
                        gets(p_new->planet_name);


                        cout << "\nВведите скорость вращения: ";
                        cin >> p_new->speed;

                        addElementSattelite(addnew, p_new);
                    }
                }
            }//case 3
                break;
            default:
                break;
            }//switch low add
            //system("pause");
        }//case 1
            break;
        case 2: {
            system("cls");
            cout << "Что вы хотите удалить: \n"
                    "\t1. Удалить весь список\n"
                    "\t2. Удалить подсписок планет у определенной звезды\n"
                    "\t3. Удалить подсписок спутников у определенной планеты\n"
                    "Ваш выбор: ";
            cin >> choise_low;

            switch (choise_low) {
            case 1: {
                clear();
            }
                break;
            case 2: {
                char buf[25];
                cout << "\nВведите название звезды: ";
                cin.ignore();
                gets(buf);

                int pos;
                bool findOK;

                findElem(root, buf, pos, findOK, cmp_star);

                if (!findOK) {
                    cout << "\nЗвезда не найдена!!\n";
                } else {
                    clearListPlanet(((list_star*)root[pos])->subLvl);
                }
            }//case 2
                break;
            case 3: {
                char buf[25];
                cout << "\nВведите название звезды: ";
                cin.ignore();
                gets(buf);

                int pos;
                bool findOK;

                findElem(root, buf, pos, findOK, cmp_star);

                if (!findOK) {
                    cout << "\nЗвезда не найдена!!\n";
                } else {
                    void **clear = ((list_star*)root[pos])->subLvl;

                    cout << "\nВведите название планеты: ";
//                    cin.ignore();
                    gets(buf);

                    findElem(clear, buf, pos, findOK, cmp_planet);

                    if (!findOK) {
                        cout << "\nПланета не найдена\n";
                    } else {
                        clearListSattelite(((list_planet*)clear[pos])->subLvl);
                    }
                }
            }//case 3
                break;
            default:
                break;
            }//switch low clear
        }//case 2
            break;
        case 3: {
            show_multilist();
        }
            break;
        case 4: {
            system("cls");
            cout << "Выберите операцию: \n"
                    "\t1. Сохранить список в файл\n"
                    "\t2. Восстановить список из файла\n"
                    "Ваш выбор: ";
            cin >> choise_low;

            switch (choise_low) {
            case 1: {
                save_to_file(root, FILE_PATH);
            }
                break;
            case 2: {
                restore_from_file(root, FILE_PATH);
            }
            default:
                break;
            }//switch low file
        }//case 4
            break;
        case 5: {
            system("cls");
            cout << "Выберите операцию: \n"
                    "\t1. Поиск планеты с наибольшим радиусом\n"
                    "\t2. Подсчет общего количества звезд в мультисписке\n"
                    "Ваш выбор: ";
            cin >> choise_low;

            switch (choise_low) {
            case 1: {
                list_planet * finded = higher_radius(getRoot());

                if (finded == NULL) {
                    cout << "\nОшибка поиска\n";
                } else {
                cout << "\nНайденная планета: \n";
                cout << "Название планеты: " << finded->name_of_planet << endl;
                cout << "Масса планеты: " << finded->weight << endl;
                cout << "Радиус планеты: " << finded->radius << endl;
                }
            }
                break;
            case 2: {
                stars_count();
            }
                break;
            default:
                break;
            }//switch low special
        }//case 5*/
            break;
        case 6: {
            clear();
            exit(0);
        }
            break;
        default:
            break;

        }//switch high
        cout << endl;
        system("pause");
    }
}

void show_multilist() {
    void **starArray = getRoot();
    int starCount = ((int*)starArray)[COUNT_POZ];

    if (starArray == NULL || starCount == 0) {
        cout << "\nСписок пуст\n";
        return;
    }

    cout << "\nСписок звезд: \n";

    for (int i = 0; i < starCount; i++) {

        void **planetArray = ((list_star*)starArray[i])->subLvl;
        int planetCount = ((int*)planetArray)[COUNT_POZ];

        cout << "\n\tНазвание звезды: ";
        cout << ((list_star*)starArray[i])->name_of_star << endl;
        cout << "\tМасса звезды: ";
        cout << ((list_star*)starArray[i])->weight << endl;
        cout << "\tПримерное расстояние от Земли до звезды: ";
        cout << ((list_star*)starArray[i])->distance << endl;

        if (planetCount != 0) {
            cout << "\t" << "Список планет: \n";
            for (int j = 0; j < planetCount; j++) {

                void **satteliteArray = ((list_planet*)planetArray[j])->subLvl;
                int satteliteCount = ((int*)satteliteArray)[COUNT_POZ];

                cout << "\n\t\tНазвание планеты: ";
                cout << ((list_planet*)planetArray[j])->name_of_planet << endl;

                cout << "\t\tМасса планеты: ";
                cout << ((list_planet*)planetArray[j])->weight << endl;

                cout << "\t\tРадиус планеты: ";
                cout << ((list_planet*)planetArray[j])->radius << endl;

                if (satteliteCount != 0) {
                    cout << "\t\t" << "Cписок спутников: \n";
                    for (int k = 0; k < satteliteCount; k++) {
                        cout << "\n\t\t\tНазвание спутника:";
                        cout << ((list_sattelite*)satteliteArray[k])->sattelite_name << endl;
                        cout << "\t\t\tНазвание планеты, вокруг которой вращается спутник: ";
                        cout << ((list_sattelite*)satteliteArray[k])->planet_name << endl;
                        cout << "\t\t\tСкорость вращения (м/с): ";
                        cout << ((list_sattelite*)satteliteArray[k])->speed << endl;
                    }
                }
            }
        }
    }
}
