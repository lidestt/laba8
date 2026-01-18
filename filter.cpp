#include "filter.h"
#include <cstring>

// Фильтр 1: участники из клуба "Спартак"
bool isFromSpartak(Participant* participant) {
    return strcmp(participant->club, "Спартак") == 0;
}

// Фильтр 2: результат лучше 2:50:00
bool hasResultBetterThan250(Participant* participant) {
    int startSeconds = participant->start.hours * 3600 + 
                      participant->start.minutes * 60 + 
                      participant->start.seconds;
    
    int finishSeconds = participant->finish.hours * 3600 + 
                       participant->finish.minutes * 60 + 
                       participant->finish.seconds;
    
    int resultSeconds = finishSeconds - startSeconds;
    int targetSeconds = 2 * 3600 + 50 * 60; // 2:50:00 в секундах
    
    return resultSeconds < targetSeconds;
}

// Основная функция фильтрации
Participant** filterParticipants(
    Participant* array[],
    int size,
    bool (*check)(Participant* element),
    int& result_size) {
    
    Participant** filtered = new Participant*[size];
    result_size = 0;
    
    for (int i = 0; i < size; i++) {
        if (check(array[i])) {
            filtered[result_size++] = array[i];
        }
    }
    
    return filtered;
}