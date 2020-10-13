#include "soft_config.h"
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"

#ifndef HW_1_IO_MANAGER2_H
#define HW_1_IO_MANAGER2_H

#define HARD_DATA_SIZE 5

// input
void input_date(date* date);
softConfig* consoleInput(int* number_of_elements);
softConfig* setHardData(int* number_of_elements);

// output
void groupPrint(softConfig*** configs);

#endif //HW_1_IO_MANAGER2_H
