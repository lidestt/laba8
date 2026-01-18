#ifndef UTILS_H
#define UTILS_H

#include "marathon_results.h"

void printParticipant(Participant* participant);
void printParticipants(Participant* array[], int size);
int getRaceTimeInSeconds(Participant* participant);
void formatTime(int seconds, char* buffer);

#endif