#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[min_idx] > arr[j])
            {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[largest] < arr[left])
    {
        largest = left;
    }

    if (right < n && arr[largest] < arr[right])
    {
        largest = right;
    }

    if (largest != i)
    {
        int temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int linearSearch(int arr[], int n, int search)
{
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == search)
        {
            flag = 1;
            printf("Searched element at %d\n", i);
            return search;
        }
    }

    printf("Element not found!\n");
}

int binarySearch(int arr[], int high, int value){
    int low=0;
    high=high-1;

    while (low<=high)
    {
        int mid=low+(high-low)/2;

        if(arr[mid]==value){
            printf("Searched element at %d\n", mid);
            return mid;
        }else if(arr[mid]>value){
            high=mid-1;
        }else{ 
            low=mid+1;
        }
    }

    printf("Element not found!\n");
}

void readData(const char *filename, int arr[], int n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < n; i++)
        fscanf(file, "%d", &arr[i]);
    fclose(file);
}

void testSearch(int (*searchFunc)(int[], int, int), const char *searchName, int bit)
{
    const char *dataFiles[] = {"Files/array_100.txt", "Files/array_1000.txt", "Files/array_10000.txt", "Files/array_100000.txt"};
    int sizes[] = {100, 1000, 10000, 100000};

    printf("\n==== %s Search Results ====\n", searchName);

    for (int i = 0; i < 4; i++)
    {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr)
        {
            printf("Memory allocation failed for size %d\n", n);
            continue;
        }

        readData(dataFiles[i], arr, n);
        printf("\nFor n = %d:\n", n);

        // Best Case
        int bestKey = (bit == 0 ? arr[0] : arr[n/2]);
        clock_t start = clock();
        searchFunc(arr, n, bestKey);
        clock_t end = clock();
        printf("Best Case Time: %.6f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Average Case
        int avgKey = (bit == 0 ? arr[n/2] : arr[n/4]);
        start = clock();
        searchFunc(arr, n, avgKey);
        end = clock();
        printf("Average Case Time: %.6f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Worst Case: element not present (e.g., -1)
        int worstKey = -1;
        start = clock();
        searchFunc(arr, n, worstKey);
        end = clock();
        printf("Worst Case Time: %.6f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        free(arr);
    }
}

void testSort(void (*sortFunc)(int[], int), const char *sortName)
{
    int sizes[] = {100, 1000, 10000, 100000};

    const char *caseFiles[] = {"Files/worst.txt", "Files/average.txt", "Files/best.txt"};
    const char *caseNames[] = {"Worst Case", "Average Case", "Best Case"};

    printf("\n---- %s Sort Results ----\n", sortName);

    for (int s = 0; s < 4; s++)
    {
        int n = sizes[s];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr)
        {
            printf("Memory allocation failed for size %d\n", n);
            continue;
        }

        printf("\nFor n = %d:\n", n);

        for (int c = 0; c < 3; c++)
        {
            readData(caseFiles[c], arr, n);

            clock_t start = clock();
            sortFunc(arr, n);
            clock_t end = clock();

            double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time taken to sort the array in %s: %.4f seconds\n", caseNames[c], timeTaken);
        }

        free(arr);
    }

    printf("------------------------------\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== Sorting Time Menu =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Heap Sort\n");
        printf("5. Linear Search\n");
        printf("6. Binary Search\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            testSort(bubbleSort, "Bubble");
            break;
        case 2:
            testSort(insertionSort, "Insertion");
            break;
        case 3:
            testSort(selectionSort, "Selection");
            break;
        case 4:
            testSort(heapSort, "Heap");
            break;
        case 5:
            testSearch(linearSearch, "Linear", 0);
            break;
        case 6:
            testSearch(binarySearch, "Binary", 1);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}