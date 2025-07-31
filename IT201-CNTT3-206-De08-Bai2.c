#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[100];
    int age;
} Student;

typedef struct Node {
    Student data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, Student s) {
    if (root == NULL) return createNode(s);
    if (s.id < root->data.id)
        root->left = insert(root->left, s);
    else if (s.id > root->data.id)
        root->right = insert(root->right, s);
    else
        printf("ID %d đã tồn tại!\n", s.id);
    return root;
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("ID: %d - Tên: %s - Tuổi: %d\n", root->data.id, root->data.name, root->data.age);
    inorder(root->right);
}

void showMenu() {
    printf("\n———————— STUDENT MANAGER ————————\n");
    printf("1. THÊM SINH VIÊN\n");
    printf("2. HIỂN THỊ DANH SÁCH SINH VIÊN\n");
    printf("3. TÌM KIẾM SINH VIÊN\n");
    printf("4. XÓA SINH VIÊN\n");
    printf("5. THOÁT\n");
    printf("Chọn chức năng: ");
}

int main() {
    Node* root = NULL;
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            Student s;
            printf("Nhập ID: ");
            scanf("%d", &s.id);
            getchar();
            printf("Nhập tên: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Nhập tuổi: ");
            scanf("%d", &s.age);
            root = insert(root, s);
        } else if (choice == 2) {
            printf("\n—— DANH SÁCH SINH VIÊN ——\n");
            inorder(root);
