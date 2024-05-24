#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Тип узла
typedef enum {
    FLOAT,
    INT,
    CHAR,
    ENUM
} NodeType;

// Структура узла
typedef struct Node {
    int id; // Добавленное поле идентификатора
    NodeType type;
    union {
        float f_val;
        int i_val;
        char c_val;
        int e_val;
    } data;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
} Node;

// Функция для создания нового узла
Node* create_node(NodeType type, int id) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->id = id; // Установка идентификатора
    new_node->type = type;
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->sibling = NULL;
    return new_node;
}

// Функция для добавления нового узла
void add_node(Node* parent, Node* new_node) {
    new_node->parent = parent;
    if (parent->child == NULL) {
        parent->child = new_node;
    } else {
        Node* temp = parent->child;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = new_node;
    }
}

// Функция для удаления узла и его поддерева
void delete_node(Node* node) {
    if (node == NULL) return;
    while (node->child != NULL) {
        delete_node(node->child);
    }
    if (node->sibling != NULL) {
        delete_node(node->sibling);
    }
    free(node);
}

// Функция для вычисления степени дерева
int tree_degree(Node* node) {
    if (node == NULL) return 0;
    int degree = 0;
    Node* temp = node->child;
    while (temp != NULL) {
        degree++;
        temp = temp->sibling;
    }
    int max_degree = degree;
    temp = node->child;
    while (temp != NULL) {
        int child_degree = tree_degree(temp);
        if (child_degree > max_degree) {
            max_degree = child_degree;
        }
        temp = temp->sibling;
    }
    return max_degree;
}

// Функция для текстовой визуализации дерева
void visualize_tree(Node* node, int depth) {
    if (node == NULL) return;
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    switch (node->type) {
        case FLOAT:
            printf("[ID: %d] %f\n", node->id, node->data.f_val);
            break;
        case INT:
            printf("[ID: %d] %d\n", node->id, node->data.i_val);
            break;
        case CHAR:
            printf("[ID: %d] %c\n", node->id, node->data.c_val);
            break;
        case ENUM:
            printf("[ID: %d] %d\n", node->id, node->data.e_val);
            break;
    }
    visualize_tree(node->child, depth + 1);
    visualize_tree(node->sibling, depth);
}

// Функция для поиска узла по идентификатору
Node* find_node_by_id(Node* node, int id) {
    if (node == NULL) return NULL;
    if (node->id == id) return node;
    Node* found = find_node_by_id(node->child, id);
    if (found != NULL) return found;
    return find_node_by_id(node->sibling, id);
}

// Пример меню для работы с деревом
void menu(Node* root) {
    int choice;
    int current_id = 1;  // Начальный идентификатор для узлов
    while (1) {
        printf("1. Add Node\n");
        printf("2. Visualize Tree\n");
        printf("3. Delete Node\n");
        printf("4. Calculate Tree Degree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 5) break;

        Node* new_node;
        int type;
        int int_val;
        float float_val;
        char char_val;
        int enum_val;
        Node* parent;
        int parent_id;


        switch (choice) {
            case 1:
                printf("Enter node type (0: FLOAT, 1: INT, 2: CHAR, 3: ENUM): ");
                scanf("%d", &type);
                new_node = create_node((NodeType)type, current_id++);
                switch (type) {
                    case FLOAT:
                        printf("Enter float value: ");
                        scanf("%f", &float_val);
                        new_node->data.f_val = float_val;
                        break;
                    case INT:
                        printf("Enter int value: ");
                        scanf("%d", &int_val);
                        new_node->data.i_val = int_val;
                        break;
                    case CHAR:
                        printf("Enter char value: ");
                        scanf(" %c", &char_val);
                        new_node->data.c_val = char_val;
                        break;
                    case ENUM:
                        printf("Enter enum value: ");
                        scanf("%d", &enum_val);
                        new_node->data.e_val = enum_val;
                        break;
                }
                printf("Enter parent node id: ");
                scanf("%d", &parent_id);
                parent = find_node_by_id(root, parent_id);
                if (parent) {
                    add_node(parent, new_node);
                } else {
                    printf("Parent not found.\n");
                    free(new_node); // Освобождаем память, если родитель не найден
                }
                break;

            case 2:
                visualize_tree(root, 0);
                break;

            case 3:
                printf("Enter node id to delete: ");
                scanf("%d", &parent_id);
                parent = find_node_by_id(root, parent_id);
                if (parent) {
                    delete_node(parent);
                } else {
                    printf("Node not found.\n");
                }
                break;

            case 4:
                printf("Tree Degree: %d\n", tree_degree(root));
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

int main() {
    // Создаем корневой узел дерева
    Node* root = create_node(INT, 0);
    root->data.i_val = 0;  // Присваиваем значение корневому узлу

    // Запускаем меню
    menu(root);

    // Удаляем дерево и освобождаем память
    delete_node(root);

    return 0;
}
