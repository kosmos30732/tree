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
    char height;
public:
    Node(int _key = 0, Node* _left = nullptr, Node* _rigth = nullptr, char _height = 1)
    {
        key = _key;
        left = _left;
        right = _rigth;
        height = _height;
    }

    friend class FTree;
    friend class BFTree;
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
        if (this == &other)
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
        if (root==nullptr)
        {
            root = new Node(key);
            return true;
        }

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

        Node* cur = root;
        while (cur->left)
        {
            cur = cur->left;
        }

        return cur->key;
    }

    //return max key of tree
    int max_key()
    {
        if (root == nullptr)
        {
            cout << "Tree empty" << endl;
            return -1;
        }

        Node* cur = root;
        while (cur->right)
        {
            cur = cur->right;
        }

        return cur->key;
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

    friend class BFTree;
};

class BFTree: public FTree
{
    //вычисление коэфициента сбалансированности
    char height(Node* root)
    {
        if (root)
        {
            return root->height;
        }
        else
        {
            return 0;
        }
    }

    //вычисление коэфициента сбалансированности
    int BalanceFactor(Node* root)
    {
        return height(root->right) - height(root->left);
    }

    //коректировка height в процессе балансировки
    void CorHeight(Node* root)
    {
        char h_left = height(root->left);
        char h_rigth = height(root->right);
        root->height = (h_left > h_rigth ? h_left : h_rigth) + 1;
    }

    //малое правое вращение
    Node* R_Rotation(Node* root)
    {
        Node* other = root->left;
        root->left = other->right;
        other->right = root;
        CorHeight(root);
        CorHeight(other);
        return other;
    }

    //малое левое вращение
    Node* L_Rotation(Node* root)
    {
        Node* other = root->right;
        root->right = other->left;
        other->left = root;
        CorHeight(root);
        CorHeight(other);
        return other;
    }

    //балансировка узла путем вращения его поддеревьев
    Node* BalanceNode(Node* root)
    {
        CorHeight(root);
        if (BalanceFactor(root)==2)
        {
            //в правом поддереве его левое поддерево длиннее правого поддерева
            if (BalanceFactor(root->right)<0)
            {
                root->right = R_Rotation(root->right);
            }
            return L_Rotation(root);
        }

        if (BalanceFactor(root) == -2)
        {
            //в левом поддереве его правое поддерево длиннее левого поддерева
            if (BalanceFactor(root->left)>0)
            {
                root->left = L_Rotation(root->left);
            }
            return R_Rotation(root);
        }

        return root;
    }

    Node* Add_Node(Node* root, int key)
    {
        if (!root)
        {
            return new Node(key);
        }

        if (key<root->key)
        {
            root->left = Add_Node(root->left, key);
        }
        else
        {
            root->right = Add_Node(root->right, key);
        }
        
        return BalanceNode(root);
    }

public:
    void input_BFTree()
    {
        int n;
        cout << "How many keys in tree?" << endl;
        cin >> n;
        cout << "Enter keys: ";
        for (int i = 0; i < n; i++)
        {
            int key;
            cin >> key;
            root = Add_Node(root, key);
        }
    }

    void AddBFTree(int key)
    {
        root = Add_Node(root, key);
    }
};

int main()
{
    srand(unsigned int(time(NULL)));
    BFTree t;

    t.input_BFTree();
    cout << "-------------------------" << endl;
    t.PrintTree(t.GetRoot(), 0);

    int n = 5;

    for (int i = 0; i < n; i++)
    {
        int key;
        cin >> key;
        t.AddBFTree(key);
        cout << "-------------------------" << endl;
        t.PrintTree(t.GetRoot(), 0);
    }

    cout << "-------------------------" << endl;
    t.PrintTree(t.GetRoot(), 0);

    return 0;
}
