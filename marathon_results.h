#ifndef MARATHON_RESULTS_H
#define MARATHON_RESULTS_H

#include "constants.h"

struct Time {
    int hours;
    int minutes;
    int seconds;
};

struct Participant {
    int number;
    char last_name[MAX_STRING_SIZE];
    char first_name[MAX_STRING_SIZE];
    char middle_name[MAX_STRING_SIZE];
    Time start;
    Time finish;
    char club[MAX_STRING_SIZE];
};

#endif