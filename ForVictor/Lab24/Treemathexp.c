#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

// Структура узла дерева
typedef struct Node {
    char type; // 'o' for operator, 'n' for number, 'v' for variable
    char operator;
    double number;
    char variable;
    char numberString[32]; // строка для хранения формата числа
    struct Node *left;
    struct Node *right;
} Node;

// Функция для создания нового узла с оператором
Node* createOperatorNode(char operator) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = 'o';
    node->operator = operator;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для создания нового узла с числом
Node* createNumberNode(double number, const char *numberString) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = 'n';
    node->number = number;
    strncpy(node->numberString, numberString, sizeof(node->numberString));
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для создания нового узла с переменной
Node* createVariableNode(char variable) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = 'v';
    node->variable = variable;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Прототипы функций
Node* parseExpression(const char **expression);
Node* parseTerm(const char **expression);
Node* parseFactor(const char **expression);
void printTree(Node *root, int level);
void printInfix(Node *root, int parentPriority);
void transformUnaryMinus(Node **root);
void removeUnaryMinuses(Node **root);
void freeTree(Node *root);
int getPriority(char operator);

// Главная функция
int main() {
    // Установить локаль на Russian_Russia.65001 для поддержки UTF-8
    setlocale(LC_ALL, "Russian_Russia.65001");

    int time;

    char expression[256];
    printf("Введите арифметическое выражение без пробелов: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Удаление символа новой строки

    const char *expr = expression;
    Node *root = parseExpression(&expr);

    printf("\nИдет вычисление дерева, подождите");
    time = 2;
    while (time > 0) {
        printf(".");
	sleep(1);
	time = time - 1;
    }
    printf(".\n");
    sleep(1);
    
    printf("\nДерево выражения:\n");
    printTree(root, 0);

    printf("\nИдет преобразование унарного минуса, подождите");
    time = 2;
    while (time > 0) {
        printf(".");
	sleep(1);
	time = time - 1;
    }
    printf(".\n");
    sleep(1);

    transformUnaryMinus(&root);
    printf("\nДерево после преобразования унарного минуса:\n");
    printTree(root, 0);

    printf("\nПодождите еще чуть чуть, формируем дерево");
    time = 2;
    while (time > 0) {
        printf(".");
	sleep(1);
	time = time - 1;
    }
    printf(".\n");
    sleep(1);

    printf("\nВыражение после преобразования унарного минуса: ");
    printInfix(root, 0);
    printf("\n");

    freeTree(root);
    return 0;
}

// Функция для парсинга выражения и создания дерева (метод Рутинсхаузера)
Node* parseExpression(const char **expression) {
    Node *node = parseTerm(expression);

    while (**expression == '+' || **expression == '-') {
        char operator = **expression;
        (*expression)++;
        Node *newNode = createOperatorNode(operator);
        newNode->left = node;
        newNode->right = parseTerm(expression);
        node = newNode;
    }

    return node;
}

Node* parseTerm(const char **expression) {
    Node *node = parseFactor(expression);

    while (**expression == '*' || **expression == '/') {
        char operator = **expression;
        (*expression)++;
        Node *newNode = createOperatorNode(operator);
        newNode->left = node;
        newNode->right = parseFactor(expression);
        node = newNode;
    }

    return node;
}

Node* parseFactor(const char **expression) {
    while (isspace(**expression)) {
        (*expression)++;
    }

    if (**expression == '(') {
        (*expression)++;
        Node *node = parseExpression(expression);
        if (**expression == ')') {
            (*expression)++;
        }
        return node;
    } else if (isdigit(**expression) || **expression == '.') {
        char *end;
        const char *start = *expression;
        double value = strtod(*expression, &end);
        char numberString[32];
        strncpy(numberString, start, end - start);
        numberString[end - start] = '\0';
        Node *node = createNumberNode(value, numberString);
        *expression = end;
        return node;
    } else if (isalpha(**expression)) {
        char variable = **expression;
        (*expression)++;
        return createVariableNode(variable);
    } else if (**expression == '-') {
        (*expression)++;
        Node *node = createOperatorNode('-');
        node->right = parseFactor(expression);
        return node;
    }

    return NULL;
}

// Функция для вывода дерева
void printTree(Node *root, int level) {
    if (root == NULL) {
        return;
    }

    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    if (root->type == 'o') {
        printf("%c (уровень %d)\n", root->operator, level);
    } else if (root->type == 'n') {
        printf("%s (уровень %d)\n", root->numberString, level);
    } else if (root->type == 'v') {
        printf("%c (уровень %d)\n", root->variable, level);
    }
    printTree(root->left, level + 1);
}

// Функция для получения приоритета оператора
int getPriority(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '*' || operator == '/') {
        return 2;
    }
    return 0;
}

// Функция для вывода дерева в инфиксной записи
void printInfix(Node *root, int parentPriority) {
    if (root == NULL) {
        return;
    }

    int currentPriority = (root->type == 'o') ? getPriority(root->operator) : 0;
    int needParentheses = (root->type == 'o' && currentPriority < parentPriority);

    if (needParentheses) {
        printf("(");
    }

    printInfix(root->left, currentPriority);
    if (root->type == 'o') {
        printf(" %c ", root->operator);
    } else if (root->type == 'n') {
        printf("%s", root->numberString);
    } else if (root->type == 'v') {
        printf("%c", root->variable);
    }
    printInfix(root->right, currentPriority);

    if (needParentheses) {
        printf(")");
    }
}

// Вспомогательная функция для подсчета унарных минусов
int countUnaryMinuses(Node *root) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;
    if (root->type == 'o' && root->operator == '-') {
        count++;
        count += countUnaryMinuses(root->right);
    } else {
        count += countUnaryMinuses(root->left);
        count += countUnaryMinuses(root->right);
    }

    return count;
}

// Функция для преобразования унарного минуса
void transformUnaryMinus(Node **root) {
    if (*root == NULL) {
        return;
    }

    // Подсчет количества унарных минусов
    int minusCount = countUnaryMinuses(*root);

    // Если количество минусов четное, убираем все минусы
    if (minusCount % 2 == 0) {
        // Убираем все минусы
        removeUnaryMinuses(root);
    } else {
        // Убираем все минусы и добавляем один минус перед всем выражением
        removeUnaryMinuses(root);
        Node *newRoot = createOperatorNode('-');
        newRoot->right = *root;
        *root = newRoot;
    }
}

// Вспомогательная функция для удаления унарных минусов
void removeUnaryMinuses(Node **root) {
    if (*root == NULL) {
        return;
    }

    if ((*root)->type == 'o' && (*root)->operator == '-') {
        Node *right = (*root)->right;
        *root = right;
        removeUnaryMinuses(root);
    } else {
        removeUnaryMinuses(&((*root)->left));
        removeUnaryMinuses(&((*root)->right));
    }
}

// Функция для освобождения памяти дерева
void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
