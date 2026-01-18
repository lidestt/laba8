#ifndef SORT_H
#define SORT_H

#include "marathon_results.h"

// Прототипы функций сортировки
void bubbleSort(Participant* array[], int size, 
                int (*compare)(Participant* a, Participant* b));
void quickSort(Participant* array[], int low, int high,
               int (*compare)(Participant* a, Participant* b));
void quickSortWrapper(Participant* array[], int size,
                      int (*compare)(Participant* a, Participant* b));

// Функции сравнения
int compareByRaceTime(Participant* a, Participant* b);
int compareByClubAndLastName(Participant* a, Participant* b);

#endif