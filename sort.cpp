#include "sort.h"
#include <cstring>
#include <iostream>

// 1. Сортировка обменом (Bubble sort)
void bubbleSort(Participant* array[], int size, 
                int (*compare)(Participant* a, Participant* b)) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(array[j], array[j + 1]) > 0) {
                Participant* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// Вспомогательная функция для быстрой сортировки
int partition(Participant* array[], int low, int high,
              int (*compare)(Participant* a, Participant* b)) {
    Participant* pivot = array[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (compare(array[j], pivot) <= 0) {
            i++;
            Participant* temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    
    Participant* temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    
    return i + 1;
}

// 2. Быстрая сортировка (Quick sort)
void quickSort(Participant* array[], int low, int high,
               int (*compare)(Participant* a, Participant* b)) {
    if (low < high) {
        int pi = partition(array, low, high, compare);
        quickSort(array, low, pi - 1, compare);
        quickSort(array, pi + 1, high, compare);
    }
}

// Обертка для быстрой сортировки
void quickSortWrapper(Participant* array[], int size,
                      int (*compare)(Participant* a, Participant* b)) {
    quickSort(array, 0, size - 1, compare);
}

// Функция вычисления времени забега в секундах
int getRaceTimeInSeconds(Participant* participant) {
    int start = participant->start.hours * 3600 + 
                participant->start.minutes * 60 + 
                participant->start.seconds;
    
    int finish = participant->finish.hours * 3600 + 
                 participant->finish.minutes * 60 + 
                 participant->finish.seconds;
    
    return finish - start;
}

// Критерий 1: По времени забега (по возрастанию)
int compareByRaceTime(Participant* a, Participant* b) {
    int timeA = getRaceTimeInSeconds(a);
    int timeB = getRaceTimeInSeconds(b);
    
    return timeA - timeB;
}

// Критерий 2: По клубу, затем по фамилии
int compareByClubAndLastName(Participant* a, Participant* b) {
    int clubCompare = strcmp(a->club, b->club);
    
    if (clubCompare != 0) {
        return clubCompare;
    }
    
    return strcmp(a->last_name, b->last_name);
}