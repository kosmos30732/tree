#include <iostream>
#include <cstddef>
#include <ctime>
#include <vector>
#include <iterator>
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
    friend void PrintNode(Node*);
};

class FTree
{
    Node* root;
public:
    FTree()
    {
        root = nullptr;
    }

    //из n случайных чисел
    FTree(int n)
    {
        if (n == 0)
        {
            root = nullptr;
        }
        else
        {
            root = new Node(rand() % 100);
            for (int i = 1; i < n;)
            {
                if (Add(root, rand() % 100))
                {
                    i++;
                }
            }
        }
    }

    //построение по заданому массиву чисел
    FTree(int* a, int n)
    {
        if (n == 0)
        {
            root = nullptr;
        }
        else
        {
            root = new Node(a[0]);
            for (int i = 1; i < n; i++)
            {
                Add(root, a[i]);
            }
        }
    }
    
    FTree(const FTree& other)
    {
        if (other.root == nullptr)
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
        if (other == nullptr)
        {
            return nullptr;
        }

        Node* root = new Node(other->key);
        root->left = CopyTree(other->left);
        root->right = CopyTree(other->right);

        return root;
    }

    FTree& operator=(const FTree& other)
    {
        if (this->root == other.root)
        {
            return *this;
        }

        if (!root)
        {
            delete_FTree(root);
        }

        if (other.root == nullptr)
        {
            root = nullptr;
        }
        else
        {
            root = new Node(other.root->key);
            root->left = CopyTree(other.root->left);
            root->right = CopyTree(other.root->right);
        }

        return *this;
    }

    ~FTree()
    {
        delete_FTree(root);
        root = nullptr;
    }
    void delete_FTree(Node* root)
    {
        if (root)
        {
            delete_FTree(root->left);
            delete_FTree(root->right);
            delete root;
        }
    }

    bool Add(Node* root, int key)
    {
        Node* cur = root;
        while (cur && cur->key != key)
        {
            if (cur->key > key && !cur->left)
            {
                cur->left = new Node(key);
                return true;
            }

            if (cur->key < key && !cur->right)
            {
                cur->right = new Node(key);
                return true;
            }

            if (cur->key > key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }

        return false;
    }

    //return: true  если добавление успешно
    //        false инача
    bool AddNode(int key)
    {
        return Add(root, key);
    }

    void PrintTree(Node* root, int k)
    {
        if (root == nullptr)
        {
            return;
        }
        PrintTree(root->right, k + 3);
        for (int i = 0; i < k; i++)
        {
            cout << " ";
        }
        cout.width(2);
        cout << root->key << endl;
        PrintTree(root->left, k + 3);
    }
    
    Node* GetRoot()
    {
        return root;
    }

    void DeleteNode(int key)
    {
        Node* cur = root;
        Node* pred = nullptr;

        //ищем удаляемый элемент и его предка
        while (cur && cur->key != key)
        {
            pred = cur;
            if (cur->key>key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }

        //не найден удаляемый элемент
        if (!cur)
        {
            return;
        }

        //если нет потомка слева у удаляемого элмента то подвешиваем
        //предку провое его поддерево
        if (!cur->left)
        {
            if (pred && pred->left == cur)
            {
                pred->left = cur->right;
            }
            if (pred && pred->right == cur)
            {
                pred->right = cur->right;
            }
            delete cur;
            return;
        }

        //если нет потомка справа у удаляемого элмента то подвешиваем
        //предку левое его поддерево
        if (!cur->right)
        {
            if (pred && pred->left == cur)
            {
                pred->left = cur->left;
            }
            if (pred && pred->right == cur)
            {
                pred->right = cur->left;
            }
            delete cur;
            return;
        }

        //есть два поддерева, на место элемента вешаем
        //наименьший из его правого поддерева
        Node* min_right = cur->right;
        while (min_right->left)
        {
            min_right = min_right->left;
        }
        int temp_key = min_right->key;
        DeleteNode(temp_key);
        cur->key = temp_key;
    }

    //return min key of tree
    int min_key()
    {
        if (root == nullptr)
        {
            cout << "Tree empty" << endl;
            return -1;
        }
        return min_r(root);
    }

    int min_r(Node* root)
    {
        int m, m_temp;
        m = root->key;
        if (root->left)
        {
            m_temp = min_r(root->left);
            if (m_temp < m)
            {
                m = m_temp;
            }
        }
        if (root->right)
        {
            m_temp = min_r(root->right);
            if (m_temp < m)
            {
                m = m_temp;
            }
        }

        return m;
    }

    //return max key of tree
    int max_key()
    {
        if (root == nullptr)
        {
            cout << "Tree empty" << endl;
            return -1;
        }
        return max_r(root);
    }

    int max_r(Node* root)
    {
        int mx, mx_temp;
        mx = root->key;
        if (root->left)
        {
            mx_temp = max_r(root->left);
            if (mx_temp > mx)
            {
                mx = mx_temp;
            }
        }
        if (root->right)
        {
            mx_temp = max_r(root->right);
            if (mx_temp > mx)
            {
                mx = mx_temp;
            }
        }

        return mx;
    }

    void WidthTraversal()
    {
        vector <Node*> spisok;
        spisok.push_back(root);
        while (!spisok.empty())
        {
            cout << spisok.front()->key << " ";
            if (spisok.front()->left)
            {
                spisok.push_back(spisok.front()->left);
            }

            if (spisok.front()->right)
            {
                spisok.push_back(spisok.front()->right);
            }

            spisok.erase(spisok.begin(), spisok.begin() + 1);
        }
        cout << endl;
    }

    int NLR(int* a)
    {
        int k = 0;
        NLR_inarray(root, a, k);
        return k;
    }

    void NLR_inarray(Node* root, int* a, int& k)
    {
        if (root == nullptr)
        {
            return;
        }
        a[k++] = root->key;
        NLR_inarray(root->left, a, k);
        NLR_inarray(root->right, a, k);
    }

    //return: Node*   if Node find
    //        nullptr if Node not find
    Node* Find(int key)
    {
        Node* cur = root;
        while (cur&&cur->key!=key)
        {
            if (cur->key>key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        return cur;
    }
};

void PrintNode(Node* root)
{
    if (!root)
    {
        cout << "Empty Node" << endl;
        return;
    }
    cout << root->key << endl;
}

int main()
{
    srand(unsigned int(time(NULL)));

    int n;
    cin >> n;
    int* arr;
    arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    FTree t(arr, n);
    t.PrintTree(t.GetRoot(), 0);
    cout << "------------------------" << endl;
    
    //t.DeleteNode(85);
    //t.PrintTree(t.GetRoot(), 0);
    //cout << "------------------------" << endl;

    t.AddNode(34);
    t.PrintTree(t.GetRoot(), 0);
    cout << "------------------------" << endl;

    t.WidthTraversal();

    cout << t.min_key() << endl;
    cout << t.max_key() << endl;

    return 0;
}
