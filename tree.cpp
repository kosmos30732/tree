#include <iostream>
#include <cstddef>
#include <ctime>
using namespace std;

class Node
{
    int key;
    Node* left, * right;
public:
    Node(int _key = 0, Node* _left = nullptr, Node* _rigth = nullptr)
    {
        key = _key;
        left = _left;
        right = _rigth;
    }

    friend class BinTree;
    friend class FTree;
};

class BinTree
{
    Node* root;
public:

    //конструктор по умолчанию
    //пустое дерево
    BinTree()
    {
        root = nullptr;
    }

    //n ключей со случайными значениями ключей
    BinTree(int n)
    {
        root = BTree(n);
    }
    Node* BTree(int n)
    {
        if (n==0)
        {
            return nullptr;
        }

        Node* root = new Node(rand() % 100);
        int n1;
        n1 = n / 2;
        root->left = BTree(n / 2);
        root->right = BTree(n - 1 - n / 2);

        return root;
    }

    BinTree(const BinTree& other)
    {
        if (other.root==nullptr)
        {
            root = nullptr;
        }
        else
        {
            root = new Node(other.root->key);
            root->left = CopyTree(other.root->left);
            root->right = CopyTree(other.root->right);
        }
    }
    Node* CopyTree(Node* other)
    {
        if (other==nullptr)
        {
            return nullptr;
        }

        Node* root = new Node(other->key);
        root->left = CopyTree(other->left);
        root->right = CopyTree(other->right);

        return root;
    }

    Node* GetRoot()
    {
        return root;
    }
};

int main()
{
    srand(unsigned int(time(NULL)));

    return 0;
}
