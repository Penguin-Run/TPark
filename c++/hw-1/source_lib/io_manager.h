#include "soft_config.h"
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"

#ifndef HW_1_IO_MANAGER2_H
#define HW_1_IO_MANAGER2_H

#define HARD_DATA_SIZE 5

// input
void input_date(date* date);
soft_config* console_input(int* number_of_elements);
soft_config* set_hard_data(int* number_of_elements);

// output
void group_print(soft_config*** configs);

#endif //HW_1_IO_MANAGER2_H
