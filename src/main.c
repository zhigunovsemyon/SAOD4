#include <stdio.h> /*printf*/
#include <stdlib.h>/*EXIT_SUCCESS*/
#include <string.h> /*memcpy*/

#define byte char

void PrintArray(int const *const Arr, int const len) {
	for (int i = 0; i < len; i++){
		printf("%d ", Arr[i]);
	}
	putchar('\n');
}

void My_quicksort(void *const source, size_t len, size_t sizeofel, int(*compar)(void*,void*)) {
	byte *mem = (byte *)source;//Текущий указатель на память
	byte arr1[len * sizeofel], arr2[len * sizeofel]; // Два плеча массива
	size_t sizeof1arr = 0, sizeof2arr = 0; //Длинны массивов

	byte pivot[sizeofel]; //Ключ сортировки
	memcpy(pivot, mem, sizeofel);

	for (size_t i = 0; i < len; i++){
		int comp_res = compar(pivot, mem);
		if (comp_res < 0)	{
			memcpy(arr1, mem, sizeofel);
			sizeof1arr++;
		} else {
			memcpy(arr2, mem, sizeofel);
			sizeof2arr++;
		}
		mem += sizeofel;
	}

	if (sizeof1arr > 1){
		My_quicksort(arr1, sizeof1arr, sizeofel, compar);
	}
	if (sizeof2arr > 1){
		My_quicksort(arr2, sizeof2arr, sizeofel, compar);
	}

	memcpy((byte *)source, arr1, sizeof1arr * sizeofel);
	memcpy((byte *)source + (sizeof1arr * sizeofel), arr2, sizeof2arr * sizeofel);
}

int AscIntSort(void *a, void* b){
	int x = *(int *)a, y = *(int *)b;
	return (x > y) - (x < y);
}

int NoSort([[maybe_unused]] void *a, [[maybe_unused]] void *b) {
	return 0;
}

int main(void) {
	int const A[] = {10, 1, 3, -9, 11, -8, 0, 1, 3, 4, 89, 122, 0, -88, -2, 23, 10, -3, 1};
	size_t const A_len = sizeof(A) / sizeof(int);

	printf("Массив до изменения: ");
	PrintArray(A, A_len);
	
	My_quicksort((void *)A, A_len, sizeof(int), AscIntSort);
	// My_quicksort((void *)A, A_len, sizeof(int), NoSort);
	
	printf("Массив после изменения: ");
	PrintArray(A, A_len);


	return EXIT_SUCCESS;
}
