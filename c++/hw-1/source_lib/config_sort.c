#include <stdio.h>
#include <stdlib.h>
#include "soft_config.h"
#include "string.h"
#include "assert.h"

#define HALF_YEAR_IN_SECONDS 15768000

// returns current date - deltaAgo (deltaAgo in seconds)
date get_date(time_t deltaAgo) {
    time_t curTime;
    time(&curTime);
    curTime -= deltaAgo;
    struct tm* halfYear = localtime(&curTime);
    date halfYearDate = {
            halfYear->tm_mday,
            halfYear->tm_mon,
            halfYear->tm_year + 1900
    };
    return halfYearDate;
}

// first > second = 1; first < second = 2; first == second = 0;
int datecmp(date first, date second) {
    if (first.year > second.year) return 1;
    else if (first.year < second.year) return 2;
    else {
        if (first.month > second.month) return 1;
        else if (first.month < second.month) return 2;
        else {
            if (first.day > second.day) return 1;
            else if (first.day < second.day) return 2;
            else return 0;
        }
    }

}

// 0 - has been updated at least one time, 1 - no updates done
int is_unupdated(date first, date second) {
    return ((first.year == second.year) && (first.month == second.month) && (first.day == second.day));
}

int date_sort(soft_config* configs, soft_config** sortedConfigs, int num_of_elements) {
    if (!configs) {
        printf("ERROR: NULL * pointer passed\n");
        return -1;
    }
    if (!sortedConfigs) {
        printf("ERROR: NULL ** pointer passed\n");
        return -1;
    }

    date halfYear = get_date(HALF_YEAR_IN_SECONDS);

    int sortCount = 0;
    for (int i = 0; i < num_of_elements; i++) {
        if (datecmp(configs[i].install_date, halfYear) == 2 &&
                is_unupdated(configs[i].install_date, configs[i].last_update_date)) {
            sortedConfigs[sortCount] = &configs[i];
            sortCount++;
        }
    }
}

int ascending_sort(soft_config** configs) {
    if (!configs) {
        printf("ERROR: NULL ** pointer passed\n");
        return -1;
    }
    int isSorted = 1;
    while(isSorted) {
        isSorted = 0;
        int i = 0;
        while (configs[i+1]) {
            if (strcmp(configs[i]->name, configs[i+1]->name) > 0) {
                char* temp = configs[i]->name;
                configs[i]->name = configs[i+1]->name;
                configs[i+1]->name = temp;
                isSorted = 1;
            }
            i++;
        }
    }

    return 0;
}

int find_group_names(soft_config** configs, char** group_names, int num_of_elements) {
    // найти все названия функциональных классов
    if (!configs || !group_names) {
        printf("ERROR: NULL ** pointer passed\n");
        return -1;
    }

    int funcClassCount = 0;

    for (int i = 0; i < num_of_elements; i++) {
        group_names[i] = "";
    }
    int i = 0;
    while (configs[i] != NULL) {
        int isInTheNames = 0;
        for (int j = 0; j < num_of_elements; j++) {
            if ((configs[i]->functional_class != NULL) && (group_names[j] != NULL)) {
                if (strcmp(configs[i]->functional_class, group_names[j]) == 0) {
                    isInTheNames = 1;
                }
            }
        }
        if (!isInTheNames) {
            group_names[funcClassCount] = configs[i]->functional_class;
            funcClassCount++;
        }
        i++;
    }
    return funcClassCount;
}

int group_sort(soft_config** configs, soft_config*** configGroups, char** group_names, int num_of_groups) {
    // функция для добавления элементов в соответствующие группы
    if (!configs || !configGroups || !group_names) {
        printf("ERROR: NULL pointer passed\n");
        return -1;
    }

    int groupElemCounter[num_of_groups];
    for (int i = 0; i < num_of_groups; i++) groupElemCounter[i] = 0;
    int i = 0;
    while(configs[i]) {
        for (int j = 0; j < num_of_groups; j++) {
            if (!configGroups[j]) {
                printf("ERROR: NULL pointer passed\n");
                return -1;
            }
            if (strcmp(group_names[j], configs[i]->functional_class) == 0) {
                configGroups[j][groupElemCounter[j]] = configs[i];
                groupElemCounter[j]++;
            }
        }
        i++;
    }
    return 0;
}

int alphabetical_sort(soft_config*** config_groups) {
    if (!config_groups) {
        printf("ERROR: NULL pointer passed\n");
        return -1;
    }
    int i = 0;
    while (config_groups[i]) {
        if (ascending_sort(config_groups[i]) == -1) return -1;
        i++;
    }
    return 0;
}


