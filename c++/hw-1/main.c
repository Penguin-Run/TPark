#include "config_sort.h"
#include "io_manager.h"

/*
 Для более наглядного выделения памяти все функции работают с указателями на уже выделенную память.
 Исключение - функции ввода данных set_hard_data и console_input, которые возвращают указатель на выделенную память.
 */

int main() {
    // ввод данных
    int* num_of_elements;
    soft_config* configs = set_hard_data(num_of_elements);
    if (!configs) {
        printf("ERROR: memory alloc error\n");
        return -1;
    }
    /*
     Ввод через консоль:
     soft_config* configs = console_input(num_of_elements);
     */
    if (*num_of_elements <= 0) {
        printf("ERROR: invalid number of elements\n");
        return -1;
    }

    // сортировка по датам
    soft_config** configs_ptrs = (soft_config**) calloc(*num_of_elements, sizeof(soft_config*));
    if (!configs_ptrs) {
        printf("ERROR: memory alloc error\n");
        return -1;
    }
    if (date_sort(configs, configs_ptrs, *num_of_elements) == -1) {
        printf("ERROR: memory error in the inner function\n");
        return -1;
    }

    // определение групп по именам функциональных классов
    char** classNames = (char**) calloc(*num_of_elements, sizeof(char*));
    if (!classNames) {
        printf("ERROR: memory alloc error\n");
        return -1;
    }
    int num_of_groups = find_group_names(configs_ptrs, classNames, *num_of_elements);
    if (num_of_groups == -1) {
        printf("ERROR: memory error in the inner function\n");
        return -1;
    }

    // сортировка по группам
    soft_config*** config_groups_ptrs = (soft_config***) calloc(num_of_groups, sizeof(soft_config**));
    if (!config_groups_ptrs) {
        printf("ERROR: memory alloc error\n");
        return -1;
    }
    for (int i = 0; i < num_of_groups; i++) {
        config_groups_ptrs[i] = (soft_config**) calloc(*num_of_elements, sizeof(soft_config*));
        if (!config_groups_ptrs[i]) {
            printf("ERROR: memory alloc error\n");
            return -1;
        }
    }
    if (group_sort(configs_ptrs, config_groups_ptrs, classNames, num_of_groups) == -1) {
        printf("ERROR: memory error in the inner function\n");
        return -1;
    }

    // сортировка по алфавиту в рамках групп
    if (alphabetical_sort(config_groups_ptrs) == -1) {
        printf("ERROR: memory error in the inner function\n");
        return -1;
    }

    // печать всех групп
    if (group_print(config_groups_ptrs) == -1) {
        printf("ERROR: memory error in the inner function\n");
        return -1;
    }

    // освобождение выделенной памяти
    free(configs);
    free(configs_ptrs);
    free(classNames);
    for (int i = 0; i < num_of_groups; i++) free(config_groups_ptrs[i]);
    free(config_groups_ptrs);
    return 0;
}
