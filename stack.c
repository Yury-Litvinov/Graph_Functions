#include "stack.h"

st_pn* push_pn(st_pn* head, char a) {
    st_pn* ptr = (st_pn*)malloc(sizeof(st_pn));
    ptr->symbol = a;
    ptr->next = head;
    return ptr;
}

char pop_pn(st_pn** head) {
    char a;
    if (*head == NULL) {
        a = '\0';
    } else {
        st_pn* ptr = *head;
        a = ptr->symbol;
        *head = ptr->next;
        free(ptr);
    }
    return a;
}

st_calc* push_calc(st_calc* head, double a) {
    st_calc* ptr = (st_calc*)malloc(sizeof(st_calc));
    ptr->digit = a;
    ptr->next = head;
    return ptr;
}

double pop_calc(st_calc** head) {
    st_calc* ptr = *head;
    double a = ptr->digit;
    *head = ptr->next;
    free(ptr);
    return a;
}
