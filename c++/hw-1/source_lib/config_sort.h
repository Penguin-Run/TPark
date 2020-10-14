#include "soft_config.h"

#ifndef HW_1_SOURCE_H
#define HW_1_SOURCE_H

// help funcs
date get_date(time_t deltaAgo);
int datecmp(date first, date second);
int is_unupdated(date first, date second);
soft_config** ascending_sort(soft_config** configs);

// main logic
int date_sort(soft_config* configs, soft_config** sortedConfigs, int num_of_elements);
int find_group_names(soft_config** configs, char** group_names, int num_of_elements);
int group_sort(soft_config** configs, soft_config*** configGroups, char** group_names, int num_of_groups);
int alphabetical_sort(soft_config*** config_groups);


#endif //HW_1_SOURCE_H
