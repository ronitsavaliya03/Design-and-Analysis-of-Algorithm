#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Sorting algorithms
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[min_idx] > arr[j]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[largest] < arr[left]) {
        largest = left;
    }

    if (right < n && arr[largest] < arr[right]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        quickSort(arr, low, i);
        quickSort(arr, i + 2, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Search algorithms
int linearSearch(int arr[], int n, int search) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == search) {
            printf("Element found at index %d\n", i);
            return i;
        }
    }
    printf("Element not found!\n");
    return -1;
}

int binarySearch(int arr[], int n, int value) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == value) {
            printf("Element found at index %d\n", mid);
            return mid;
        } else if (arr[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("Element not found!\n");
    return -1;
}

// Helper functions
void readData(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < n; i++)
        fscanf(file, "%d", &arr[i]);
    fclose(file);
}

void testSearch(int (*searchFunc)(int[], int, int), const char *searchName, int isBinary) {
    const char *dataFiles[] = {"Files/array_100.txt", "Files/array_1000.txt", "Files/array_10000.txt", "Files/array_100000.txt"};
    int sizes[] = {100, 1000, 10000, 100000};

    printf("\n==== %s Search Results ====\n", searchName);

    for (int i = 0; i < 4; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed for size %d\n", n);
            continue;
        }

        readData(dataFiles[i], arr, n);

        printf("\nFor n = %d:\n", n);

        // Best Case
        int bestKey = isBinary ? arr[n/2] : arr[0];
        clock_t start = clock();
        searchFunc(arr, n, bestKey);
        clock_t end = clock();
        printf("Best Case Time: %.6f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Average Case
        int avgKey = isBinary ? arr[n/4] : arr[n/2];
        start = clock();
        searchFunc(arr, n, avgKey);
        end = clock();
        printf("Average Case Time: %.6f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Worst Case
        int worstKey = -1;
        start = clock();
        searchFunc(arr, n, worstKey);
        end = clock();
        printf("Worst Case Time: %.6f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        free(arr);
    }
}

void testSort(void (*sortFunc)(int[], int), const char *sortName) {
    const char *caseFiles[] = {"Files/worst.txt", "Files/average.txt", "Files/best.txt"};
    const char *caseNames[] = {"Worst Case", "Average Case", "Best Case"};
    int sizes[] = {100, 1000, 10000, 100000};

    printf("\n---- %s Sort Results ----\n", sortName);

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed for size %d\n", n);
            continue;
        }

        printf("\nFor n = %d:\n", n);

        for (int c = 0; c < 3; c++) {
            readData(caseFiles[c], arr, n);

            clock_t start = clock();
            sortFunc(arr, n);
            clock_t end = clock();

            printf("%s Time: %.4f seconds\n", caseNames[c], (double)(end - start) / CLOCKS_PER_SEC);
        }

        free(arr);
    }
}

void testQuickSort() {
    const char *caseFiles[] = {"Files/worst.txt", "Files/average.txt", "Files/best.txt"};
    const char *caseNames[] = {"Worst Case", "Average Case", "Best Case"};
    int sizes[] = {100, 1000, 10000, 100000};

    printf("\n---- Quick Sort Results ----\n");

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed for size %d\n", n);
            continue;
        }

        printf("\nFor n = %d:\n", n);

        for (int c = 0; c < 3; c++) {
            readData(caseFiles[c], arr, n);

            clock_t start = clock();
            quickSort(arr, 0, n-1);
            clock_t end = clock();

            printf("%s Time: %.4f seconds\n", caseNames[c], (double)(end - start) / CLOCKS_PER_SEC);
        }

        free(arr);
    }
}

void testMergeSort() {
    const char *caseFiles[] = {"Files/worst.txt", "Files/average.txt", "Files/best.txt"};
    const char *caseNames[] = {"Worst Case", "Average Case", "Best Case"};
    int sizes[] = {100, 1000, 10000, 100000};

    printf("\n---- Merge Sort Results ----\n");

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed for size %d\n", n);
            continue;
        }

        printf("\nFor n = %d:\n", n);

        for (int c = 0; c < 3; c++) {
            readData(caseFiles[c], arr, n);

            clock_t start = clock();
            mergeSort(arr, 0, n-1);
            clock_t end = clock();

            printf("%s Time: %.4f seconds\n", caseNames[c], (double)(end - start) / CLOCKS_PER_SEC);
        }

        free(arr);
    }
}

int main() {
    int choice;

    do {
        printf("\n===== Sorting and Searching Menu =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Heap Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Merge Sort\n");
        printf("7. Linear Search\n");
        printf("8. Binary Search\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: testSort(bubbleSort, "Bubble"); break;
            case 2: testSort(insertionSort, "Insertion"); break;
            case 3: testSort(selectionSort, "Selection"); break;
            case 4: testSort(heapSort, "Heap"); break;
            case 5: testQuickSort(); break;
            case 6: testMergeSort(); break;
            case 7: testSearch(linearSearch, "Linear", 0); break;
            case 8: testSearch(binarySearch, "Binary", 1); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
