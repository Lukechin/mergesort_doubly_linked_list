#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct __List {
    struct __List *next, *prev;
    int data;
} List;

void dump(List *node)
{
    int count = 0;
    while (node) {
        printf("%3d ", node->data);
        if(++count == 20) {
            printf("\n");
            count = 0;
        }
        node = node->next;
    }
    printf("\n");
}

void append(List **ref, int data)
{
    List *ptr = (List *)malloc(sizeof(List));
    ptr->data = data;
    ptr->next = ptr->prev = NULL;
    if(!(*ref)) {
        (*ref) = ptr;
    } else {
        ptr->next = *ref;
        (*ref)->prev = ptr;
        (*ref) = ptr;
    }
}

void split(List* source, List** left_ref, List** right_ref)
{
    if(!source || !source->next) {
        *left_ref = source;
        *right_ref = NULL;
        return;
    }

    List *slow = source;
    for (List *fast = source->next; fast;) {
        if((fast = fast->next)) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *left_ref = source;
    *right_ref = slow->next;
    slow->next = NULL;
}

static List* merge(List* left, List* right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    List *result;
    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
        result->prev = left->prev;
    } else {
        result = right;
        result->next = merge(left, right->next);
        result->prev = right->prev;
    }
    return result;
}

void mergeSort(List** head_ref)
{
    if(!head_ref || !(*head_ref)->next)
        return;

    List *left, *right;

    split(*head_ref, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *head_ref = merge(left, right);
}

bool validate(List* source)
{
    for (List *slow = source, *fast = source->next; fast;
            slow = slow->next, fast = fast->next) {
        if (fast->data < slow->data) {
            return false;
        }
    }
    return true;
}

void freeList(List* source)
{
    for (; source; source = source->next) free(source);
}

int main()
{
    List *list = NULL;
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        append(&list, rand() % 200 + 1);
    }

    dump(list);
    mergeSort(&list);
    dump(list);

    printf("Mergesort is %s\n", validate(list) ? "correct." : "wrong.");

    freeList(list);
    
    return 0;
}
