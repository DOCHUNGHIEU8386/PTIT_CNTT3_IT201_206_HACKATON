#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Operation {
    char url[100];
    char timestamp[100];
} Operation;

typedef struct StackNode {
    Operation data;
    struct StackNode* next;
} StackNode;

typedef struct HistoryNode {
    Operation data;
    struct HistoryNode* prev;
    struct HistoryNode* next;
} HistoryNode;

char* getCurrentTime() {
    static char buffer[100];
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);
    return buffer;
}

void push(StackNode** top, Operation op) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = op;
    newNode->next = *top;
    *top = newNode;
}

Operation pop(StackNode** top) {
    Operation empty = {"", ""};
    if (*top == NULL) return empty;
    StackNode* temp = *top;
    Operation op = temp->data;
    *top = (*top)->next;
    free(temp);
    return op;
}

int isEmpty(StackNode* top) {
    return top == NULL;
}

void clearStack(StackNode** top) {
    while (*top != NULL) {
        StackNode* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void addHistory(HistoryNode** head, Operation op) {
    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    newNode->data = op;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        HistoryNode* temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void showHistory(HistoryNode* head) {
    if (head == NULL) {
        printf("Lich su trong.\n");
        return;
    }
    printf("\n Lich su WEB.\n");
    while (head != NULL) {
        printf("- %s (%s)\n", head->data.url, head->data.timestamp);
        head = head->next;
    }
}

void clearHistory(HistoryNode** head) {
    HistoryNode* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void showMenu() {
    printf("\n======== WEB HISTORY ========\n");
    printf("1.Truy cap vao trang web moi\n");
    printf("2.Quay lai trang web truoc\n");
    printf("3.Di den trang web sau neu tung bi hack\n");
    printf("4.Hien thi trang hien tai\n");
    printf("5.In toan bo lich su duyet web\n");
    printf("6.Xoa bo lich su duyet web\n");
    printf("7.Ket thuc chuong trinh\n");
    printf("==================================================\n");
}

int main() {
    StackNode *back = NULL, *forward = NULL;
    HistoryNode* history = NULL;
    Operation current = {"", ""};

    char command[150];

    while (1) {
        showMenu();
        printf("Nhap lenh: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "VISIT ", 6) == 0) {
            if (strlen(current.url) > 0)
                push(&back, current);

            strcpy(current.url, command + 6);
            strcpy(current.timestamp, getCurrentTime());

            clearStack(&forward);
            addHistory(&history, current);

            printf("Da truy cap: %s\n", current.url);
        }
        else if (strcmp(command, "BACKWARD") == 0) {
            if (isEmpty(back)) {
                printf("Khong the quay lai.\n");
            } else {
                push(&forward, current);
                current = pop(&back);
                printf("Da quay lai: %s\n", current.url);
            }
        }
        else if (strcmp(command, "FORWARD") == 0) {
            if (isEmpty(forward)) {
                printf("Khong the tien toi.\n");
            } else {
                push(&back, current);
                current = pop(&forward);
                printf("Da tien toi: %s\n", current.url);
            }
        }
        else if (strcmp(command, "CURRENT") == 0) {
            if (strlen(current.url) == 0) {
                printf("Khong co trang hien tai.\n");
            } else {
                printf("Trang hien tai: %s (%s)\n", current.url, current.timestamp);
            }
        }
        else if (strcmp(command, "HISTORY") == 0) {
            showHistory(history);
        }
        else if (strcmp(command, "CLEAR HISTORY") == 0) {
            clearHistory(&history);
            printf("Da xoa toan bo lich su duyet web.\n");
        }
        else if (strcmp(command, "Thoat") == 0 || strcmp(command, "THOAT") == 0) {
            printf("Dang thoat\n");
            break;
        }
        else {
            printf("Lenh khong hop le vui long nhap lenh khac.\n");
        }
    }

    clearStack(&back);
    clearStack(&forward);
    clearHistory(&history);

    return 0;
}
