#ifndef HW_1_SOFT_CONFIG_H
#define HW_1_SOFT_CONFIG_H

#include <stdio.h>
#include <time.h>

typedef struct date{
    int day;
    int month;
    int year;
} date;

typedef struct softConfig {
    char* name;
    char* functionalClass;
    int versionNumber;
    date installDate;
    date lastUpdateDate;
} softConfig;

#endif //HW_1_SOFT_CONFIG_H
