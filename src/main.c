#include <stdio.h>  /*printf*/
#include <stdlib.h> /*EXIT_SUCCESS*/
#include <string.h> /*memcpy*/
#include <stdbool.h> /*bool, true, false*/

#define DATATYPE short

// Однобайтовый тип данных
#define byte char

// Вывод массива int чисел Arr размера len через пробел с переносом в конце
void PrintArray(DATATYPE const *const Arr, size_t const len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", Arr[i]);
    }
    putchar('\n');
}

bool My_quicksort(void *const source, size_t const len, size_t const sizeofel,
                  int (*compar)(const void *, const void *)) {
    if (len <= 1)
        return false;

    byte *arr1 = (byte *)malloc(len * sizeofel); // Левое плечо массива
    byte *arr2 = (byte *)malloc(len * sizeofel); // Правое плечо массива
    byte *pivot = (byte *)malloc(sizeofel); // Ключ сортировки

    /* Проверка выделения памяти.Если хоть один раз выделить память не
        удалось, сортировщик завершает работу */
    if (!(arr1 && arr2 && pivot)) {
        free(arr1);
        free(arr2);
        free(pivot);
        return true;
    }

    size_t  sizeof1arr = 0, // Длина левого плеча
            sizeof2arr = 0; // Длина правого плеча
            
    //Копирование информации в ключ сортировки
    memcpy(pivot, source, sizeofel);

    for (size_t i = 1; i < len; i++) {
        byte const *const cur = (byte *)source + i * sizeofel;
        int comp_res = compar(pivot, cur);
        if (comp_res > 0) {
            memcpy(arr1 + sizeofel * sizeof1arr, 
                cur, sizeofel);
            sizeof1arr++;
        } else {
            memcpy(arr2 + sizeofel * sizeof2arr, 
                cur, sizeofel);
            sizeof2arr++;
        }
    }

    memcpy(arr1 + sizeofel * sizeof1arr, pivot, sizeofel);
    sizeof1arr++;

    My_quicksort(arr1, sizeof1arr, sizeofel, compar);
    My_quicksort(arr2, sizeof2arr, sizeofel, compar);

    memcpy((byte *)source, arr1, sizeof1arr * sizeofel);
    memcpy((byte *)source + (sizeof1arr * sizeofel), arr2,
           sizeof2arr * sizeofel);


    free(pivot);
    free(arr1);
    free(arr2);
    return false;
}

// Функция сортировки int чисел по возрастанию
int DescIntSort(const void *const a, const void *const b) {
    const DATATYPE x = *(DATATYPE *)a, y = *(DATATYPE *)b;
    return (x < y) - (x > y);
}

// Функция сортировки int чисел по возрастанию
int AscIntSort(const void *const a, const void *const b) {
    const DATATYPE x = *(DATATYPE *)a, y = *(DATATYPE *)b;
    return (x > y) - (x < y);
}

// Заглушка для qsort
int NoSort(const void *const a, const void *const b) {
    (void)a, (void)b;
    return 0;
}

int main(void) {
    DATATYPE const A[] = {
        /**/10, 1, 3, -9, 11, -8, 0, 1,
        1 + 3, 4, 89, 122, 0, -88, -2, 23, 10, -3, 1,
        1 + 10, 1, 3, -9, 11, -8, 0, 1, 3, 4, 89,
        21 + 10, 1, 3, -9, 11, -8, 0, 1, 3, 4, 89, 122, 0, 
        21 + -88, -2, 23, 10, -3, 1,
        13 + 10, 1, 3, -9, 11, -8, 0, 1, 3, 4, 89, -9, 11, -8, 0, 
        -1, 3, 4, 89, 122, 0, -88, -2, 
        -1 + 23, 10, -3, 
        -1 + 1};
    // Размер массива
    size_t const A_len = sizeof(A) / sizeof(DATATYPE);

    printf("Массив до изменения:\t");
    PrintArray(A, A_len);

    // qsort((void *)A, A_len, sizeof(int), AscIntSort);
    My_quicksort((void *)A, A_len, sizeof(DATATYPE), AscIntSort);
    printf("Массив после изменения:\t");
    PrintArray(A, A_len);
    
    My_quicksort((void *)A, A_len, sizeof(DATATYPE), DescIntSort);
    printf("Массив после изменения:\t");
    PrintArray(A, A_len);

    return EXIT_SUCCESS;
}
