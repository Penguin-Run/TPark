#ifndef HW_1_SOFT_CONFIG_H
#define HW_1_SOFT_CONFIG_H

#include <stdio.h>
#include <time.h>

typedef struct date{
    int day;
    int month;
    int year;
} date;

typedef struct soft_config {
    char* name;
    char* functional_class;
    int version_number;
    date install_date;
    date last_update_date;
} soft_config;

#endif //HW_1_SOFT_CONFIG_H
