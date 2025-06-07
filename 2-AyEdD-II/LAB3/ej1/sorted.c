#include "sorted.h"

void swap(struct Par* a, struct Par* b) {
    struct Par temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Par arr[], int low, int high) {
    struct Par pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].first < pivot.first) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort_recursive(struct Par arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void quick_sort(struct Par arr[], size_t size) {
    quick_sort_recursive(arr, 0, size - 1);
}
