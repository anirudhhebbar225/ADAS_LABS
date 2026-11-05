
#include <stdio.h>
#include <pthread.h>

int arr[100];

void merge(int left, int mid, int right) {
    int temp[100];
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

void mergeSort(int left, int right);

void *sort(void *arg) {
    int *range = (int *)arg;

    mergeSort(range[0], range[1]);

    return NULL;
}

void mergeSort(int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    pthread_t t1, t2;

    int a[] = {left, mid};
    int b[] = {mid + 1, right};

    pthread_create(&t1, NULL, sort, a);
    pthread_create(&t2, NULL, sort, b);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    merge(left, mid, right);
}

int main() {
    int n, i;

    printf("Enter size: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    mergeSort(0, n - 1);

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
