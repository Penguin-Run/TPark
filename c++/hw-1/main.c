#include "config_sort.h"
#include "io_manager.h"

/*
 Для более наглядного выделения памяти все функции работают с указателями на уже выделенную память.
 Исключение - функции ввода данных set_hard_data и console_input, которые возвращают указатель на выделенную память.
 */

// TODO: убрать с репо .idea папку
// TODO: поставить cppcheck и исправить код по нему
// TODO: сделать новый ПР чтобы уже было покрытие

int main() {
    // ввод данных
    int* num_of_elements;
    soft_config* configs = set_hard_data(num_of_elements);
    assert(configs);
    /*
     Ввод через консоль:
     soft_config* configs = console_input(num_of_elements);
     */
    assert(*num_of_elements > 0);

    // сортировка по датам
    soft_config** configs_ptrs = (soft_config**) calloc(*num_of_elements, sizeof(soft_config*));
    assert(configs_ptrs);
    date_sort(configs, configs_ptrs, *num_of_elements);

    // определение групп по именам функциональных классов
    char** classNames = (char**) calloc(*num_of_elements, sizeof(char*));
    assert(classNames);
    int num_of_groups = find_group_names(configs_ptrs, classNames, *num_of_elements);

    // сортировка по группам
    soft_config*** config_groups_ptrs = (soft_config***) calloc(num_of_groups, sizeof(soft_config**));
    assert(config_groups_ptrs);
    for (int i = 0; i < num_of_groups; i++) {
        config_groups_ptrs[i] = (soft_config**) calloc(*num_of_elements, sizeof(soft_config*));
        assert(config_groups_ptrs[i]);
    }
    group_sort(configs_ptrs, config_groups_ptrs, classNames, num_of_groups);

    // сортировка по алфавиту в рамках групп
    alphabetical_sort(config_groups_ptrs);

    // печать всех групп
    group_print(config_groups_ptrs);

    // освобождение выделенной памяти
    free(configs);
    free(configs_ptrs);
    free(classNames);
    for (int i = 0; i < num_of_groups; i++) free(config_groups_ptrs[i]);
    free(config_groups_ptrs);
    return 0;
}
