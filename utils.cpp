#include "utils.h"
#include <iostream>
#include <iomanip>
#include <cstdio>

void formatTime(int seconds, char* buffer) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;
    
    sprintf_s(buffer, 10, "%02d:%02d:%02d", hours, minutes, secs);
}

void printParticipant(Participant* participant) {
    std::cout << std::setw(4) << participant->number << " ";
    std::cout << std::setw(15) << std::left << participant->last_name << " ";
    std::cout << std::setw(10) << participant->first_name << " ";
    std::cout << std::setw(15) << participant->middle_name << " ";
    
    char startTime[10], finishTime[10];
    sprintf_s(startTime, "%02d:%02d:%02d", 
              participant->start.hours,
              participant->start.minutes,
              participant->start.seconds);
    
    sprintf_s(finishTime, "%02d:%02d:%02d",
              participant->finish.hours,
              participant->finish.minutes,
              participant->finish.seconds);
    
    std::cout << std::setw(10) << startTime << " ";
    std::cout << std::setw(10) << finishTime << " ";
    
    int raceTime = getRaceTimeInSeconds(participant);
    char raceTimeStr[10];
    formatTime(raceTime, raceTimeStr);
    
    std::cout << std::setw(10) << raceTimeStr << " ";
    std::cout << participant->club << std::endl;
}

void printParticipants(Participant* array[], int size) {
    std::cout << "\n===============================================================================================================\n";
    std::cout << std::setw(4) << "№" << " ";
    std::cout << std::setw(15) << std::left << "Фамилия" << " ";
    std::cout << std::setw(10) << "Имя" << " ";
    std::cout << std::setw(15) << "Отчество" << " ";
    std::cout << std::setw(10) << "Старт" << " ";
    std::cout << std::setw(10) << "Финиш" << " ";
    std::cout << std::setw(10) << "Результат" << " ";
    std::cout << "Клуб" << std::endl;
    std::cout << "===============================================================================================================\n";
    
    for (int i = 0; i < size; i++) {
        printParticipant(array[i]);
    }
    std::cout << "===============================================================================================================\n";
}

int getRaceTimeInSeconds(Participant* participant) {
    int start = participant->start.hours * 3600 + 
                participant->start.minutes * 60 + 
                participant->start.seconds;
    
    int finish = participant->finish.hours * 3600 + 
                 participant->finish.minutes * 60 + 
                 participant->finish.seconds;
    
    return finish - start;
}