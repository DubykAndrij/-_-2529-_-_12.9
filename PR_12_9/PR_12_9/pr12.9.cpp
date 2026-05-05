#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createNode(int value) {
    TreeNode* newNode = new TreeNode;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

TreeNode* createBinaryTree(int n) {
    if (n <= 0) return nullptr;
    int val;
    cout << "Введіть значення вузла: ";
    cin >> val;
    TreeNode* root = createNode(val);
    int leftSize = (n - 1) / 2;
    int rightSize = n - 1 - leftSize;
    root->left = createBinaryTree(leftSize);
    root->right = createBinaryTree(rightSize);
    return root;
}

void insertBST(TreeNode*& root, int value) {
    if (root == nullptr) {
        root = createNode(value);
        return;
    }
    if (value < root->data) {
        insertBST(root->left, value);
    }
    else if (value > root->data) {
        insertBST(root->right, value);
    }
}

TreeNode* createBST(int n) {
    TreeNode* root = nullptr;
    for (int i = 0; i < n; i++) {
        int val;
        cout << "Введіть значення " << i + 1 << ": ";
        cin >> val;
        insertBST(root, val);
    }
    return root;
}

void printTree(TreeNode* root, int highlightValue = -999999, int space = 0) {
    if (root == nullptr) return;
    int count = 5;
    space += count;

    printTree(root->right, highlightValue, space);

    cout << endl;
    for (int i = count; i < space; i++) cout << " ";

    if (root->data == highlightValue) {
        cout << "[" << root->data << "]\n";
    }
    else {
        cout << root->data << "\n";
    }

    printTree(root->left, highlightValue, space);
}

void storeBSTNodes(TreeNode* root, vector<TreeNode*>& nodes) {
    if (root == nullptr) return;
    storeBSTNodes(root->left, nodes);
    nodes.push_back(root);
    storeBSTNodes(root->right, nodes);
}

TreeNode* buildBalancedTree(vector<TreeNode*>& nodes, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    TreeNode* root = nodes[mid];
    root->left = buildBalancedTree(nodes, start, mid - 1);
    root->right = buildBalancedTree(nodes, mid + 1, end);
    return root;
}

void balanceBST(TreeNode*& root) {
    vector<TreeNode*> nodes;
    storeBSTNodes(root, nodes);
    int n = nodes.size();
    root = buildBalancedTree(nodes, 0, n - 1);
}

TreeNode* findMin(TreeNode* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

void deleteNodeBST(TreeNode*& root, int key) {
    if (root == nullptr) return;

    if (key < root->data) {
        deleteNodeBST(root->left, key);
    }
    else if (key > root->data) {
        deleteNodeBST(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            root = temp;
        }
        else {
            TreeNode* temp = findMin(root->right);
            root->data = temp->data;
            deleteNodeBST(root->right, temp->data);
        }
    }
}

void deleteBranch(TreeNode*& root) {
    if (root == nullptr) return;
    deleteBranch(root->left);
    deleteBranch(root->right);
    delete root;
    root = nullptr;
}

void removeBranchByValue(TreeNode*& root, int key) {
    if (root == nullptr) return;
    if (key < root->data) {
        removeBranchByValue(root->left, key);
    }
    else if (key > root->data) {
        removeBranchByValue(root->right, key);
    }
    else {
        deleteBranch(root);
    }
}

bool containsElement(TreeNode* root, int k) {
    if (root == nullptr) return false;
    if (root->data == k) return true;

    return containsElement(root->left, k) || containsElement(root->right, k);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    TreeNode* root = nullptr;
    int choice = -1;

    while (choice != 0) {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Створити звичайне бінарне дерево\n";
        cout << "2. Створити бінарне дерево пошуку (BST)\n";
        cout << "3. Додати елемент (для BST)\n";
        cout << "4. Видалити елемент за значенням (випадки 6, 7, 8)\n";
        cout << "5. Видалити цілу гілку за значенням кореня (випадок 9)\n";
        cout << "6. Збалансувати дерево (BST)\n";
        cout << "7. Перевірити наявність елемента k (Варіант 1)\n";
        cout << "8. Вивести дерево на екран\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        int n, val;
        bool found;

        switch (choice) {
        case 1:
            deleteBranch(root);
            cout << "Введіть кількість елементів: ";
            cin >> n;
            root = createBinaryTree(n);
            break;
        case 2:
            deleteBranch(root);
            cout << "Введіть кількість елементів: ";
            cin >> n;
            root = createBST(n);
            break;
        case 3:
            cout << "Введіть значення: ";
            cin >> val;
            insertBST(root, val);
            break;
        case 4:
            cout << "Введіть значення для видалення: ";
            cin >> val;
            deleteNodeBST(root, val);
            break;
        case 5:
            cout << "Введіть корінь гілки для видалення: ";
            cin >> val;
            removeBranchByValue(root, val);
            break;
        case 6:
            balanceBST(root);
            cout << "Дерево збалансовано.\n";
            break;
        case 7:
            cout << "Введіть значення k для пошуку: ";
            cin >> val;
            found = containsElement(root, val);
            if (found) {
                cout << "Елемент " << val << " знайдено!\n";
                printTree(root, val);
            }
            else {
                cout << "Елемент " << val << " не знайдено.\n";
            }
            break;
        case 8:
            cout << "Структура дерева (повернута на 90 градусів):\n";
            printTree(root);
            break;
        case 0:
            deleteBranch(root);
            cout << "Вихід.\n";
            break;
        default:
            cout << "Невірний вибір.\n";
        }
    }
    return 0;
}