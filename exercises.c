#include "array_functions.h"
#include "node.h"
#include "linkedlist_functions.h"

#include "bubblesort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void execute_1_1()
{
    printf("base implementation\n");
    // generate arrays
    int *arr8 = randomizedArray(8);
    int *arr16 = randomizedArray(16);
    int *arr64 = randomizedArray(64);
    // print arrays before and after sorting, check if all were successful
    int success = // 1 if all were successful, 0 otherwise
        testSortArray(arr8, 8, 1, 1, 'b') &&
        testSortArray(arr16, 16, 1, 1, 'b') &&
        testSortArray(arr64, 64, 1, 1, 'b') &&
        testSortArray(arr8, 8, 1, 1, 'i') &&
        testSortArray(arr16, 16, 1, 1, 'i') &&
        testSortArray(arr64, 64, 1, 1, 'i') &&
        testSortArray(arr8, 8, 1, 1, 'm') &&
        testSortArray(arr16, 16, 1, 1, 'm') &&
        testSortArray(arr64, 64, 1, 1, 'm') &&
        testSortArray(arr8, 8, 1, 1, 'q') &&
        testSortArray(arr16, 16, 1, 1, 'q') &&
        testSortArray(arr64, 64, 1, 1, 'q');
    // free memory of arrays
    free(arr8);
    free(arr16);
    free(arr64);

    if (success)
    {
        printf("\nAll sorting algorithms were successful!\n");
    }
    else
    {
        printf("\nAt least one sorting algorithm failed!\n");
    }
}

void execute_1_2()
{
    void (*shuffle_funcs[3])(int *array, int length) = {    // array of function pointers to shuffle functions
        &randomizeArray,
        &fillArrayAscening,
        &fillArrayDescending};

    void (*sort_funcs[4])(int *array, int length, int ascending) = {   // array of function pointers to sorting functions
        &bubbleSortArray,
        &insertionSortArray,
        &mergeSortArray,
        &quickSortArray};

    char shuffle_names[3][4] = {"rnd", "asc", "des"}; // names of shuffle types
    char sort_names[4][15] = {"bubble sort   ", "insertion sort", "merge sort    ", "quick sort    "}; // names of sorting algorithms
    int arr_sizes[7] = {8, 32, 128, 512, 2084, 8192, 32768}; // array sizes
    long times[4][21]; // array of times for each sorting algorithm and each array configuration
    int arr[32768]; // array for sorting

    printf("executing 1.2");

    for (int sort_algo = 0; sort_algo < 4; sort_algo++) // for each sorting algorithm
    {
        fprintf(stdout, "\n> %s\t0%%", sort_names[sort_algo]); // logging progress of sorting algorithm
        int progress = 0;  // progress of current sorting algorithm in %

        for (int arr_size = 0; arr_size < 7; arr_size++) // for each array size
        {
            for (int shuffleType = 0; shuffleType < 3; shuffleType++) // for each shuffle type
            {
                int current_size = arr_sizes[arr_size]; // current array size
                shuffle_funcs[shuffleType](arr, current_size); // initializing array 

                clock_t begin = clock(); // starting timer
                sort_funcs[sort_algo](arr, current_size, 1); // sorting array ascending
                clock_t end = clock(); // stopping timer

                times[sort_algo][3 * arr_size + shuffleType] = (end - begin) * 1000 / CLOCKS_PER_SEC; // saving time in ms

                // logging progress
                (progress < 10) ? printf("\b\b") : printf("\b\b\b"); // deleting previous progress log
                progress = (arr_size * 3 + shuffleType + 1) * 100 / (7 * 3); // calculating progress in %
                printf("%d%%", progress); // logging progress 
                fflush(stdout); // flushing stdout 
            }
        }
    }

    // printing results
    printf("\n\narray size\t"); // printing header of table
    for (int size = 0; size < 7; size++)
        printf("%d\t\t\t", arr_sizes[size]); // printing array sizes

    printf("\narray init\t"); // printing header of table
    for (int init = 0; init < 3 * 7; init++)
        printf("%s\t", shuffle_names[init % 3]); // printing shuffle types

    printf("\n"); 
    for (int i = 0; i < 23; i++) // printing line under header
        printf("--------");

    printf("\n");
    for (int sort = 0; sort < 4; sort++) // printing times for each sorting algorithm
    {
        printf("%s\t", sort_names[sort]); 
        for (int arr_conf = 0; arr_conf < 3 * 7; arr_conf++) // printing times for each array configuration
        {
            printf("%ldms\t", times[sort][arr_conf]); // printing time
        }
        printf("\n");
    }
}

void execute_1_3()
{
    long times[20]; // array of times for each sorting algorithm and each array configuration
    int ref_arr[2000], arr[2000]; // arrays for sorting
    randomizeArray(ref_arr, 2000); // initializing array

    for (int i = 0; i < 20; i++) // for each sorting algorithm 
    {
        copyArrayIntoArray(ref_arr, arr, 2000); // copying reference array into array to sort
        clock_t begin = clock(); // starting timer
        bubbleSortArray(arr, 2000, 1); // sorting array ascending
        clock_t end = clock(); // stopping timer

        times[i] = (end - begin) * 1000 / CLOCKS_PER_SEC; // saving time in ms 
    }

    long min = times[0], max = times[0], sum = 0; // variables for min, max and sum of times
    for (int i = 0; i < 20; i++) // calculating min, max and sum of times
    {
        if (times[i] < min) 
            min = times[i];
        if (times[i] > max)
            max = times[i];
        sum += times[i];
    }

    // printing results
    for (int i = 0; i < 20; i++)
        printf("[%d]\t%ldms\n", i, times[i]);

    printf("\nminimum time: %ld ms\nmaximum time: %ld ms\naverage time: %f ms\n", min, max, (float)sum / 20.0f);
}

void execute_1_4()
{
    clock_t begin1 = clock();                // start timer
    int *rndArr2048 = randomizedArray(2048); // create array

    clock_t end1 = clock();                                           // stop timer
    clock_t begin2 = clock();                                         // start timer
    struct Node *rndHead2048 = linkedListFromArray(rndArr2048, 2048); // create linked list
    clock_t end2 = clock();                                           // stop timer

    printf("array sort:\n");
    printArray(rndArr2048, 2048); // print the array
    clock_t begin3 = clock();     // start timer
    insertionSortArray(rndArr2048, 2048, 1);
    clock_t end3 = clock(); // stop timer
    printf("V\n");
    printArray(rndArr2048, 2048); // print the linked list

    printf("linked list sort:\n");
    printLinkedList(rndHead2048);                          // print the linked list
    clock_t begin4 = clock();                              // start timer
    rndHead2048 = insertionSortLinkedList(rndHead2048, 1); // sort the linked list
    clock_t end4 = clock();                                // stop timer
    printf("V\n");
    printLinkedList(rndHead2048); // print the linked list

    printf("\n\ntime to generate array:\t\t%f ms\n", (double)(end1 - begin1) / CLOCKS_PER_SEC * 1000); // print the time it took to generate the array
    printf("time to create linked list:\t%f ms\n", (double)(end2 - begin2) / CLOCKS_PER_SEC * 1000);   // print the time it took to create the linked list
    printf("time to sort array:\t\t%f ms\n", (double)(end3 - begin3) / CLOCKS_PER_SEC * 1000);         // print the time it took to sort the array
    printf("time to sort linked list:\t%f ms\n", (double)(end4 - begin4) / CLOCKS_PER_SEC * 1000);     // print the time it took to sort the linked list

    freeLinkedList(rndHead2048); // free the linked list
    free(rndArr2048);            // free the array
}