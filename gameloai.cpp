#include <stdio.h>
#include <stdlib.h>

// C?u tr�c c?a ng�?i ch�i trong v?ng tr?n
struct Node {
    int position;
    struct Node* next;
};

// H�m t?o danh s�ch v?ng tr?n v?i N ng�?i ch�i
struct Node* taoVongTron(int N) {
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* tail = NULL;

    for (int i = 1; i <= N; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->position = i;
        newNode->next = head;

        if (head == NULL) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    tail->next = head; // Li�n k?t cu?i v? �?u t?o v?ng tr?n
    return head;
}

// H�m gi?i quy?t b�i to�n Josephus
int josephus(struct Node* head, int M) {
    struct Node* current = head;
    struct Node* prev = NULL;

    if (M == 0) {  // Tr�?ng h?p �?c bi?t khi M = 0
        while (current->next != current) {
            printf("Loai bo nguoi choi thu: %d\n", current->position);
            prev = current;
            current = current->next;
            prev->next = current;
            free(prev);
        }
        int winner = current->position;
        free(current);
        return winner;
    }

    if (M == 1) { // Tr�?ng h?p �?c bi?t khi M = 1
        while (current->next != current) {
            printf("Loai bo nguoi choi thu: %d\n", current->next->position);
            struct Node* temp = current->next;
            current->next = temp->next;
            free(temp);
            current = current->next;
        }
        int winner = current->position;
        free(current);
        return winner;
    }

    // Tr�?ng h?p M > 1
    while (current->next != current) {
        for (int i = 1; i < M; i++) {
            prev = current;
            current = current->next;
        }
        printf("Loai bo nguoi choi thu: %d\n", current->position);
        prev->next = current->next;
        free(current);
        current = prev->next;
    }
    int winner = current->position;
    free(current);
    return winner;
}

int main() {
    int N, M;
    printf("Nhap so luong nguoi choi N: ");
    scanf("%d", &N);
    printf("Nhap gia tri M (so nguoi bi loai bo moi luot): ");
    scanf("%d", &M);

    struct Node* head = taoVongTron(N);
    int winner = josephus(head, M);
    printf("Nguoi chien thang cuoi cung la nguoi thu: %d\n", winner);

    return 0;
}
