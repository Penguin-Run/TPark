#include "config_sort.h"
#include "io_manager.h"

/*
 Для более наглядного выделения памяти все функции работают с указателями на уже выделенную память.
 Исключение - функции ввода данных set_hard_data и console_input, которые возвращают указатель на выделенную память.
 */

// TODO: убрать с репо .idea папку
// TODO: переименовать все функции под один стиль
// TODO: сделать проверку указателей на входе функций и при выделении памяти
// TODO: поставить сззсрусл и исправить код по нему
// TODO: сделать новый ПР чтобы уже было покрытие

int main() {
    // ввод данных
    int* num_of_elements;
    soft_config* configs = set_hard_data(num_of_elements);
    /*
     Ввод через консоль:
     soft_config* configs = console_input(num_of_elements);
     */
    assert(*num_of_elements > 0);

    // сортировка по датам
    soft_config** configs_ptrs = (soft_config**) calloc(*num_of_elements, sizeof(soft_config*));
    date_sort(configs, configs_ptrs, *num_of_elements);

    // определение групп по именам функциональных классов
    char** classNames = (char**) calloc(*num_of_elements, sizeof(char*));
    int num_of_groups = find_group_names(configs_ptrs, classNames, *num_of_elements);

    // сортировка по группам
    soft_config*** config_groups_ptrs = (soft_config***) calloc(num_of_groups, sizeof(soft_config**));
    for (int i = 0; i < num_of_groups; i++) {
        config_groups_ptrs[i] = (soft_config**) calloc(*num_of_elements, sizeof(soft_config*));
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
