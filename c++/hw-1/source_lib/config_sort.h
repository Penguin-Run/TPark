#include "soft_config.h"

#ifndef HW_1_SOURCE_H
#define HW_1_SOURCE_H

date getDate(time_t deltaAgo);
int datecmp(date first, date second);
int isUnupdated(date first, date second);
void dateSort(softConfig* configs, softConfig** sortedConfigs, int num_of_elements);

int find_group_names(softConfig** configs, char** group_names, int num_of_elements);
softConfig*** groupSort(softConfig** configs, softConfig*** configGroups, char** group_names, int num_of_groups);

softConfig** ascendingSort(softConfig** configs);
void alphabetical_sort(softConfig*** config_groups);


#endif //HW_1_SOURCE_H
