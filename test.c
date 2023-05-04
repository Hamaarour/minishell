#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

void append(Node** head_ref, char* new_value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    Node* last = *head_ref;

    new_node->value = new_value;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

void print_list(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    Node* head = NULL;
    int i = 1;

    while (i < argc) {
        append(&head, argv[i]);
        i++;
    }
    print_list(head);

    return 0;
}