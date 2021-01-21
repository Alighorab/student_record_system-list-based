#include "interface.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>

static char *adminPassword;
static List list, *pl = &list;


void init_system(void) {
    list_init(pl, free);
    adminPassword = strdup("1234");
}


int add_record(char *name, int year, char *password) {
    studentRecord_t *new_std = (studentRecord_t*) malloc(sizeof(studentRecord_t));

    new_std->password = strdup(password);
    new_std->name = strdup(name);
    new_std->year = year;
    new_std->id = list_size(pl);

    list_ins_next(pl, list_tail(pl), new_std);
}

int edit_name(int id, char *name) {
    if (id > list_size(pl))
        return 0;

    ListElmt *pe = NULL;
    studentRecord_t *std = NULL;

    pe = find_elmt(pl, id);
    std = (studentRecord_t*) pe->data;

    free(std->name);
    std->name = strdup(name);

    return 1;
}

int edit_year(int id,int year) {
    if (id > list_size(pl))
        return 0;

    ListElmt *pe = NULL;
    studentRecord_t *std = NULL;

    pe = find_elmt(pl, id);
    std = (studentRecord_t*) pe->data;

    std->year = year;

    return 1;
}

int edit_password(int id, char *password) {
    if (id > list_size(pl))
        return 0;

    ListElmt *pe = NULL;
    studentRecord_t *std = NULL;

    pe = find_elmt(pl, id);
    std = (studentRecord_t*) pe->data;

    free(std->password);
    std->password = strdup(password);

    return 1;
}

int remove_record(int id) {
    if (id > list_size(pl))
        return 0;

    ListElmt *pe = NULL;
    studentRecord_t *std = NULL;

    pe = find_elmt(pl, id - 1);
    list_rem_next(pl, pe, &std);

    return 1;
}

int view_record(int id, void (*display)(studentRecord_t)) {
    if (id > list_size(pl))
        return 0;

    ListElmt *pe = NULL;
    studentRecord_t *std = NULL;

    pe = find_elmt(pl, id);
    list_retrieve(pl, pe, &std);

    display(*std);
    return 1;

}

void traverse_records(void(*display)(studentRecord_t)) {
    list_traverse(pl, display);
}

int check_admin_password(char *password) {
    if (!strcmp(password, adminPassword))
        return 1;
    return 0;
}

int set_admin_password(char *oldPassword, char *newPassword) {
    if (check_admin_password(oldPassword) == 1) {
        free(adminPassword);
        adminPassword = strdup(newPassword);
        return 1;
    }
    return 0;
}

int check_user_password(int id, char *password) {
    if (id > list_size(pl))
        return 0;

    ListElmt *pe = NULL;
    studentRecord_t *std = NULL;

    pe = find_elmt(pl, id);
    list_retrieve(pl, pe, &std);

    if (!strcmp(password, std->password)) {
        return 1;
    }
    return 0;
}