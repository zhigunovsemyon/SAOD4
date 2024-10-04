#include <stdbool.h> /*bool, true, false*/
#include <stdio.h>   /*printf()*/
#include <stdlib.h>  /*EXIT_SUCCESS, malloc(), free()*/
#include <string.h>  /*memcpy()*/

// Тип данных, используемый в алгоритме
#define DATATYPE short
// Строка для вывода одного элемента в printf()
#define PRINT_STR "%d "

// Однобайтовый тип данных
typedef unsigned char byte;

void PrintArray(DATATYPE const *const Arr, size_t const len) {
    for (size_t i = 0; i < len; i++)
        printf(PRINT_STR, Arr[i]);

    putchar('\n');
}

/*  Алгоритм быстрой сортировки.В процессе рекурсивно выделяет память в куче.
    По неудаче с выделениением памяти возвращает true, при штатной работе --
   false. */
bool My_quicksort(
    void *const source, // Область памяти, которую надо сортировать
    size_t const element_count, // Число элементов
    size_t const element_size,  // Размер одного элемента
    int (*compar)(const void *const, const void *const) // Функция сравнения
) {
    // Пограничное условие рекурсивных вызовов.
    if (element_count <= 1)
        return false;

    // Левое плечо массива
    byte *const arr1 = (byte *)malloc(element_count * element_size);

    // Правое плечо массива
    byte *const arr2 = (byte *)malloc(element_count * element_size);
    // Ключ сортировки
    byte *const pivot = (byte *)malloc(element_size);

    /* Проверка выделения памяти.Если хоть один раз выделить память не
        удалось, сортировщик завершает работу */
    if (!(arr1 && arr2 && pivot)) {
        free(arr1);
        free(arr2);
        free(pivot);
        return true;
    }

    size_t sizeof1arr = 0, // Длина левого плеча
        sizeof2arr = 0;    // Длина правого плеча

    // Копирование информации в ключ сортировки
    memcpy(pivot, source, element_size);

    /*Цикл, перебирающий исходный массив
    (кроме первого элемента, занесённого в пивот) */
    for (size_t i = 1; i < element_count; i++) {
        // Указатель на текущий элемент исходного массива
        byte const *const cur = (byte *)source + i * element_size;

        // Определение по функции сортировки нужного плеча
        if (compar(pivot, cur) > 0) {
            // Копирование в левое плечо, увеличение счётчика его размера
            memcpy(arr1 + element_size * sizeof1arr, cur, element_size);
            sizeof1arr++;
        } else {
            // Копирование в правое плечо, увеличение счётчика его размера
            memcpy(arr2 + element_size * sizeof2arr, cur, element_size);
            sizeof2arr++;
        }
    }

    // Копирование ключа в край левого плеча, увеличение счётчика его размера
    memcpy(arr1 + element_size * sizeof1arr, pivot, element_size);
    sizeof1arr++;
    // Освобождение ключа за ненадобностью
    free(pivot);

    /*Рекурсивный запуск сортировок в каждом плече. */
    if (My_quicksort(arr1, sizeof1arr, element_size, compar) ||
        My_quicksort(arr2, sizeof2arr, element_size, compar)) {
        /*Если хоть одно из них завершилось ошибкой выделения памяти,
        вся память аварийно очищается, код ошибки возвращается выше*/
        free(arr1);
        free(arr2);
        return true;
    };

    // Слияние двух отсортированных половин
    memcpy((byte *)source, arr1, sizeof1arr * element_size);
    memcpy((byte *)source + (sizeof1arr * element_size), arr2,
           sizeof2arr * element_size);

    /*Штатное освобождение памяти*/
    free(arr1);
    free(arr2);
    return false;
}

// Функция сортировки int чисел по убыванию
int DescIntSort(const void *const a, const void *const b) {
    // Локальные копии объектов
    const DATATYPE x = *(DATATYPE *)a, y = *(DATATYPE *)b;
    /*  Если первое число больше второго, возврат -1,
        Если второе число больше первого, возврат +1
        Если два числа равны, оба неравенства ложны => 0 - 0 == 0*/
    return (x < y) - (x > y);
}

// Функция сортировки int чисел по возрастанию
int AscIntSort(const void *const a, const void *const b) {
    // Локальные копии объектов
    const DATATYPE x = *(DATATYPE *)a, y = *(DATATYPE *)b;
    /*  Если первое число больше второго, возврат +1,
        Если второе число больше первого, возврат -1
        Если два числа равны, оба неравенства ложны => 0 - 0 == 0*/
    return (x > y) - (x < y);
}

int main(void) {
    DATATYPE const A[] = {
        10,  1,  3,   -9, 11,  -8,      0,       1,  1 + 3,   4,     89,
        122, 0,  -88, -2, 23,  10,      -3,      1,  1 + 10,  1,     3,
        -9,  11, -8,  0,  1,   3,       4,       89, 21 + 10, 1,     3,
        -9,  11, -8,  0,  1,   3,       4,       89, 122,     0,     21 + -88,
        -2,  23, 10,  -3, 1,   13 + 10, 1,       3,  -9,      11,    -8,
        0,   1,  3,   4,  89,  -9,      11,      -8, 0,       -1,    3,
        4,   89, 122, 0,  -88, -2,      -1 + 23, 10, -3,      -1 + 1};
    // Размер массива
    size_t const A_len = sizeof(A) / sizeof(DATATYPE);

    printf("Массив до изменения:\t");
    PrintArray(A, A_len);

    if (My_quicksort((void *)A, A_len, sizeof(DATATYPE), AscIntSort)) {
        perror("My_quicksort");
        return EXIT_FAILURE;
    };
    printf("Массив после сорт-ки по возрастанию: ");
    PrintArray(A, A_len);

    if (My_quicksort((void *)A, A_len, sizeof(DATATYPE), DescIntSort)) {
        perror("My_quicksort");
        return EXIT_FAILURE;
    };
    printf("Массив после сорт-ки по убыванию   : ");
    PrintArray(A, A_len);

    return EXIT_SUCCESS;
}
