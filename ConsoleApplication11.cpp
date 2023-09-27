#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Структура для узла дерева
struct Node {
	int data; // Значение узла
	Node* left; // Указатель на левого потомка
	Node* right; // Указатель на правого потомка

	// Конструктор для узла, инициализирующий данные и указатели на nullptr
	Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Функция для добавления узла в дерево (без дубликатов)
Node* InsertWithoutDuplicates(Node* root, int data) {
	if (root == nullptr) {
		return new Node(data); // Если дерево пустое, создаем новый узел
	}

	if (data == root->data) {
		printf("Число уже существует в дереве\n");
		return root; // Если элемент уже существует в дереве, не вставляем его повторно
	}

	if (data < root->data) {
		root->left = InsertWithoutDuplicates(root->left, data); // Рекурсивно добавляем в левое поддерево
	}
	else {
		root->right = InsertWithoutDuplicates(root->right, data); // Рекурсивно добавляем в правое поддерево
	}
	return root;
}

// Функция для поиска значения в дереве
Node* Search(Node* root, int key) {
	if (root == nullptr || root->data == key) {
		return root; // Если узел пустой или содержит искомое значение, возвращаем узел
	}
	if (root->data < key) {
		return Search(root->right, key); // Если искомое значение больше, ищем в правом поддереве
	}
	return Search(root->left, key); // В противном случае ищем в левом поддереве
}

// Функция для вывода дерева на экран (90 градусов поворот)
void PrintTree(Node* root, int level) {
	if (root == nullptr) {
		return; // Если узел пустой, выходим из функции
	}
	PrintTree(root->right, level + 1); // Рекурсивно выводим правое поддерево
	for (int i = 0; i < level; i++) {
		printf(" "); // Выводим отступы в зависимости от уровня узла
	}
	printf("%d\n", root->data); // Выводим данные узла
	PrintTree(root->left, level + 1); // Рекурсивно выводим левое поддерево
}

// Функция для подсчета вхождений элемента в дерево
int CountOccurrences(Node* root, int key) {
	if (root == nullptr) {
		return 0; // Если узел пустой, возвращаем 0
	}
	int count = 0;
	if (root->data == key) {
		count++; // Если узел содержит искомое значение, увеличиваем счетчик
	}
	count += CountOccurrences(root->left, key); // Рекурсивно ищем в левом поддереве
	count += CountOccurrences(root->right, key); // Рекурсивно ищем в правом поддереве
	return count;
}

int main() {
	setlocale(LC_ALL, "RUS");
	Node* root = nullptr;
	int data;
	int start = 1;
	int stk = 1;
	//printf("-1 - окончание построения дерева\n");
	while (start) {
		printf("Введите число: ");
		scanf("%d", &data);

		printf("Хотите продолжить заполнение дерева? [1. Да] [0. Нет]: ");
		scanf("%d", &stk);
		
		if (stk == 0) {
			root = InsertWithoutDuplicates(root, data);
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else if (stk == 1) {
			root = InsertWithoutDuplicates(root, data);
		}
		else {
			printf("Ошибка ввода\n\n");
		}
	}

	printf("Дерево:\n");
	PrintTree(root, 0);

	printf("Введите значение для поиска: ");
	scanf("%d", &data);

	Node* result = Search(root, data);
	if (result != nullptr) {
		printf("Значение найдено: %d\n", result->data);
	}
	else {
		printf("Значение не найдено\n");
	}

	int occurrences = CountOccurrences(root, data);
	printf("Число %d встречается в дереве %d раз\n", data, occurrences);

	return 0;
}