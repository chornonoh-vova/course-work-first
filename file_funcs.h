#ifndef FILE_FUNCS
#define FILE_FUNCS
//функции, обеспечивающие сохранение в файл
//и восстановление из файла

#include <cstdlib>
#include "main_types.h"
#include "main_funcs.h"

#define FILE_PATH "space.dat"

//сохранение списка в файл
//для сохранения в резервный файл необходимо при вызове функции
//в параметре pathway
//указать FILE_PATH
//вместо FILE_PATH

void save_to_file(void **&start, const char *pathway);

//восстановление списка из файла
//для восстановления из резервного файл необходимо при вызове функции
//в параметре pathway
//указать FILE_PATH
//вместо FILE_PATH

void restore_from_file(void **&start, const char *pathway);

#endif // FILE_FUNCS

