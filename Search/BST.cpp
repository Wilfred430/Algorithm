#include <iostream>
using namespace std;

/**
 * 二元搜尋樹節點結構
 * data: 儲存節點的值
 * left: 指向左子樹
 * right: 指向右子樹
 */
struct Node {
    int data = 0;                // 節點資料
    Node *left = nullptr;        // 左子節點指標
    Node *right = nullptr;       // 右子節點指標
    
    // 節點建構子，初始化節點值
    Node(int value) : data(value) {}
};

/**
 * 在二元搜尋樹中插入新節點
 * @param Tree 樹的根節點指標的參考
 * @param element 要插入的元素值
 */
void InsertTree(Node* &Tree, const int element) {
    // 如果樹是空的，建立根節點
    if (Tree == nullptr) {
        Tree = new Node(element);
        return;
    }

    // 尋找插入位置
    Node* current = Tree;    // 當前節點
    Node* parent = nullptr;  // 父節點
    
    // 往下搜尋適當的插入位置
    while (current) {
        parent = current;
        if (element > current->data) {
            current = current->right;  // 往右子樹走
        }
        else if (element < current->data) {
            current = current->left;   // 往左子樹走
        }
        else {
            // 如果值已存在，直接返回
            return;
        }
    }

    // 建立新節點並連接到適當位置
    if (element > parent->data) {
        parent->right = new Node(element);  // 插入右子樹
    }
    else {
        parent->left = new Node(element);   // 插入左子樹
    }
}

/**
 * 在二元搜尋樹中搜尋特定值
 * @param Tree 樹的根節點指標
 * @param Target 要搜尋的目標值
 */
void Check(Node *Tree, const int Target) {
    while (Tree) {
        if (Target > Tree->data) {
            Tree = Tree->right;      // 目標值較大，往右子樹搜尋
        }
        else if (Target < Tree->data) {
            Tree = Tree->left;       // 目標值較小，往左子樹搜尋
        }
        else {
            cout << "Find!" << endl;  // 找到目標值
            return;
        }
    }
    cout << "Not find!" << endl;     // 沒有找到目標值
}

/**
 * 遞迴刪除整棵樹
 * @param Tree 要刪除的樹的根節點指標
 */
void DeleteTree(Node* Tree) {
    if (Tree == nullptr) return;
    
    DeleteTree(Tree->left);   // 刪除左子樹
    DeleteTree(Tree->right);  // 刪除右子樹
    delete Tree;             // 刪除當前節點
}

/**
 * 主程式
 * 功能：建立二元搜尋樹並進行搜尋操作
 */
int main() {
    int Size;
    cout << "Enter the size of array you want to search(enter zero to break): ";
    
    // 主要操作迴圈
    while (cin >> Size) {
        if (Size == 0) break;

        Node* Tree = nullptr;  // 初始化空樹
        int element;
        
        // 讀取輸入並建立樹
        cout << "Enter the entries of the array: ";
        for (int i = 0; i < Size; i++) {
            cin >> element;
            InsertTree(Tree, element);
        }

        // 執行搜尋操作
        cout << "Enter the samples you want to check(enter -1 to break): ";
        int tmp;
        while (cin >> tmp) {
            if (tmp == -1) break;
            Check(Tree, tmp);
        }

        // 清理記憶體
        DeleteTree(Tree);
    }

    return 0;
}
