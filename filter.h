#ifndef FILTER_H
#define FILTER_H

#include "marathon_results.h"

Participant** filterParticipants(
    Participant* array[],
    int size,
    bool (*check)(Participant* element),
    int& result_size
);

// Функции фильтрации
bool isFromSpartak(Participant* participant);
bool hasResultBetterThan250(Participant* participant);

#endif