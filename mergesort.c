#include <stdio.h>
#include <stdlib.h>

typedef struct __List {
    struct __List *next, *prev;
    int data;
} List;

void printList(List *node)
{
    int count = 0;
    while (node != NULL) {
        printf("%2d ", node->data);
        node = node->next;
        count++;
        if(count==20) {
            printf("\n");
            count = 0;
        }
    }
    printf("\n");
}

void insertNodeAtBegin(List **start_ref, int new_data)
{
    List *ptr = (List *)malloc(sizeof(List));
    ptr->data = new_data;
    ptr->next = ptr->prev = NULL;
    if((*start_ref)==NULL) {
        (*start_ref) = ptr;
    } else {
        ptr->next = *start_ref;
        (*start_ref)->prev = ptr;
        (*start_ref) = ptr;
    }
}

void findMidOfList(List* source, List** left_ref, List** right_ref)
{
    if(source==NULL || source->next==NULL) {
        *left_ref = source;
        *right_ref = NULL;
    } else {
        List *fast = source->next;
        List *slow = source;

        while(fast != NULL) {
            fast = fast->next;
            if(fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *left_ref = source;
        *right_ref = slow->next;
        slow->next = NULL;
    }
}

List* merge(List* left, List* right)
{
    if (left==NULL)
        return right;
    else if(right==NULL)
        return left;

    List *result = NULL;
    if(left->data<=right->data) {
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
    if((head_ref==NULL) || ((*head_ref)->next==NULL))
        return;

    List *head = *head_ref;
    List *left;
    List *right;

    findMidOfList(head, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *head_ref = merge(left, right);
}

int main()
{
    List *a = NULL;

    for (int i = 0; i < 100; i++) {
        insertNodeAtBegin(&a, rand()%100);
    }

    printList(a);
    mergeSort(&a);
    printList(a);

    return 0;
}