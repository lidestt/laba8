#include "file_reader.h"
#include "constants.h"
#include <fstream>
#include <cstring>
#include <iostream>

Time parseTime(char* timeStr) {
    Time time;
    char* context = nullptr;
    
    char* token = strtok_s(timeStr, ":", &context);
    time.hours = atoi(token);
    
    token = strtok_s(nullptr, ":", &context);
    time.minutes = atoi(token);
    
    token = strtok_s(nullptr, ":", &context);
    time.seconds = atoi(token);
    
    return time;
}

void readParticipants(const char* file_name, Participant* array[], int& size) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        size = 0;
        char buffer[MAX_STRING_SIZE];
        
        while (!file.eof() && size < MAX_FILE_ROWS_COUNT) {
            Participant* participant = new Participant;
            
            file >> participant->number;
            file >> participant->last_name;
            file >> participant->first_name;
            file >> participant->middle_name;
            
            file >> buffer;
            participant->start = parseTime(buffer);
            
            file >> buffer;
            participant->finish = parseTime(buffer);
            
            // Чтение клуба (может содержать пробелы)
            file.getline(buffer, MAX_STRING_SIZE);
            
            // Удаляем начальный пробел
            if (buffer[0] == ' ') {
                strcpy_s(participant->club, buffer + 1);
            } else {
                strcpy_s(participant->club, buffer);
            }
            
            array[size++] = participant;
        }
        file.close();
    } else {
        throw "Ошибка открытия файла";
    }
}