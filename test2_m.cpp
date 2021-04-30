#include <iostream>
using namespace std;
#include <algorithm>

// template<class InputIterator, class T>
//   InputIterator find (InputIterator first, InputIterator last, const T& val)
// {
//   while (first!=last) {
//     if (*first==val) return first;
//     ++first;
//   }
//   return last;
// }

template <typename key_t, typename priorities_t>
class Treap_node_t
{
    private:

    //pair that holds key and priority associated with the node
    pair<key_t, priorities_t> node_val;

    //pointer to the left child of the node
    Treap_node_t *left_n;

    //pointer to the right child of the node
    Treap_node_t *right_n;


    public:

    //constructor
    Treap_node_t(key_t key, priorities_t prior)
    : node_val(key, prior),left_n(nullptr), right_n(nullptr)
    {}

    //copy constructor
    Treap_node_t(const Treap_node_t &rhs)
    {
        this->node_val.first = rhs.node_val.first;
        this->node_val.second = rhs.node_val.second;
        this->right_n = nullptr;
        this->left_n = nullptr;
    }

    //copy assignment operator
    Treap_node_t& operator=(const Treap_node_t &rhs)
    {
        this->node_val.first = rhs.node_val.first;
        this->node_val.second = rhs.node_val.second;
        this->right_n = nullptr;
        this->left_n = nullptr;
        return *this;
    }

    //destructor
    ~Treap_node_t()
    {

    }

    //function to overload put out operator
    friend ostream& operator<<(ostream &o, const Treap_node_t<key_t, priorities_t> &rhs)
    {
        o << "Key: " << rhs.node_val.first << "\n";
        o << "Priority: " << rhs.node_val.second << "\n";
        return o;
    }

    //function to insert a node into the treap
    Treap_node_t* insert_node(Treap_node_t* root ,key_t key, priorities_t prior)
    {
        //tree is empty
        if(!root)
        {
            Treap_node_t *temp = new Treap_node_t(key, prior);
            return temp;
        }

        else if(key < root->node_val.first)
        {
            root->left_n = insert_node(root->left_n,key, prior);

            if(prior > root->node_val.second)
            {
                root = right_rotate(root);
            }
        }

        else if(key > root->node_val.first)
        {
            root->right_n = insert_node(root->right_n,key,prior);

            if(prior > root->node_val.second)
            {
                root = left_rotate(root);
            }

        }

        else
        {
            root->node_val.second = prior;
        }

        return root;
    }

    //function to perform inorder traversal of the treap
    void inorder_traversal(Treap_node_t<key_t, priorities_t> *root) const
    {
        if(root)
        {
            inorder_traversal(root->left_n);
            cout << *root;
            inorder_traversal(root->right_n);
        }
    }


    //function to perform preorder traversal of the treap
    void preorder_traversal(Treap_node_t<key_t, priorities_t> *root) const
    {
        if(root)
        {
            cout << *root;
            preorder_traversal(root->left_n);
            preorder_traversal(root->right_n);
        }
    }

    //function to perform postorder traversal of the treap
    void postorder_traversal(Treap_node_t<key_t, priorities_t> *root) const
    {
        if(root)
        {
            postorder_traversal(root->left_n);
            postorder_traversal(root->right_n);
            cout << *root;
        }
    }

    //static function to delete a node from the treap
    static void delete_treap(Treap_node_t<key_t,priorities_t> *root)
    {
        if(root)
        {
            delete_treap(root->left_n);
            delete_treap(root->right_n);
            // cout << "DELETING\n" << *root << "\n";
            delete root;
        }
    }

    //static function to copy a node of the treap
    static Treap_node_t<key_t,priorities_t>* copy_treap(Treap_node_t<key_t,priorities_t>** lhs, Treap_node_t<key_t,priorities_t> *root)
    {
        if(root)
        {
            (*lhs) = new Treap_node_t<key_t, priorities_t>(*root);
            (*lhs)->left_n = copy_treap(&((*lhs)->left_n), root->left_n);
            (*lhs)->right_n = copy_treap(&((*lhs)->right_n), root->right_n);
        }
        return *lhs;
    }

    //function to right rotate a node in the treap
    Treap_node_t* right_rotate(Treap_node_t* node)
    {
        Treap_node_t* left_subtree = node -> left_n;
        Treap_node_t* right_subtree_of_left_subtree = left_subtree -> right_n;

        left_subtree -> right_n = node;
        node -> left_n = right_subtree_of_left_subtree;

        return left_subtree;
    }

    //function to left rotate a node in the treap
    Treap_node_t* left_rotate(Treap_node_t* node)
    {
        Treap_node_t* right_subtree = node -> right_n;
        Treap_node_t* left_subtree_of_right_subtree = right_subtree -> left_n;

        right_subtree -> left_n = node;
        node -> right_n = left_subtree_of_right_subtree;

        return right_subtree;
    } 
    
    //function to search for a node in the treap
    Treap_node_t *search_node(Treap_node_t *root, key_t search_key)
    {
        if(root == nullptr || (root -> node_val).first == search_key)
        {
            return root;
        }
        if((root -> node_val).first < search_key)
        {
            return search_node(root -> right_n, search_key);
        }
        return search_node(root -> left_n, search_key);
    }

    //function to delete a node in the treap
    Treap_node_t* delete_node(Treap_node_t* root ,key_t key)
    {
        //tree is empty
        if(!root)
        {
            return root;
        }

        else if(key < root->node_val.first)
        {
            root->left_n = delete_node(root->left_n,key);
        }

        else if(key > root->node_val.first)
        {
            root->right_n = delete_node(root->right_n,key);
        }

        else if( !root->left_n )
        {
            Treap_node_t* temp = root->right_n;
            delete root;
            root = temp;
        }

        else if( !root->right_n )
        {
            Treap_node_t* temp = root->left_n;
            delete root;
            root = temp;
        }

        else if ( root->left_n->node_val.second > root->right_n->node_val.second )
        {
            root = right_rotate(root);
            root->right_n = delete_node(root->right_n, key);
        }
        
        else
        {
            root = left_rotate(root);
            root->left_n = delete_node(root->left_n, key);
        }

        return root;
    }

    key_t operator*()
    {
        return this->node_val.first;
    }

    Treap_node_t *inorder_succ_node(Treap_node_t *root)
    {
        Treap_node_t *node_x = this;
        if(node_x -> right_n != nullptr)
        {
            node_x = node_x -> right_n;

            while( node_x->left_n != nullptr )
            {
                node_x = node_x->left_n;
            }
            return node_x;
        }

        Treap_node_t *succ = nullptr;

        while(root != nullptr)
        {
            if(node_x -> node_val.first < root -> node_val.first)
            {
                succ = root;
                root = root -> left_n;
            }
            else if(node_x -> node_val.first > root -> node_val.first)
            {
                root = root -> right_n;
            }
            else
                break;
        }
        // cout<<*succ<<"\n";
        return succ;
    }

    Treap_node_t *inorder_predec_node(Treap_node_t *root)
    {
        Treap_node_t *node_x = this;
        if(node_x -> left_n != nullptr)
        {
            node_x = node_x -> left_n;

            while( node_x->right_n != nullptr )
            {
                node_x = node_x->right_n;
            }
            return node_x;
        }

        Treap_node_t *pred = nullptr;

        while(root != nullptr)
        {
            if(node_x -> node_val.first < root -> node_val.first)
            {
                root = root -> left_n;
            }
            else if(node_x -> node_val.first > root -> node_val.first)
            {
                pred = root;
                root = root -> right_n;
            }
            else
                break;
        }
        
        return pred;
    }

    Treap_node_t *iterator_begin()
    {
        Treap_node_t *temp = this;
        while(temp -> left_n != nullptr)
        {
            temp = temp -> left_n;
        }
        return temp;
    }

    Treap_node_t *iterator_end()
    {
        Treap_node_t *temp = this;
        while(temp -> right_n != nullptr)
        {
            temp = temp -> right_n;
        }
        return temp;
    }

    bool operator==(const Treap_node_t& rhs)
    {
        return this->node_val.first == rhs.node_val.first;
    }

    bool operator!=(const Treap_node_t& rhs)
    {
        return !(*this == rhs);
    }

};


template <typename key_t, typename priorities_t>
class Treap_t
{
    private:

    //pointer to the root of the treap
    Treap_node_t<key_t,priorities_t> *root;

    public:

    //constructor
    Treap_t(Treap_node_t<key_t,priorities_t> *root = nullptr)
    :
    root(root)
    {

    }

    //copy constructor
    Treap_t(const Treap_t &rhs)
    {
        Treap_node_t<key_t,priorities_t>::copy_treap(&(this->root), rhs.root);
    }

    //copy assignment operator
    Treap_t& operator=(const Treap_t &rhs)
    {
        Treap_node_t<key_t,priorities_t>::copy_treap(&(this->root), rhs.root);
        return *this;
    }

    //destructor
    ~Treap_t()
    {
        Treap_node_t<key_t,priorities_t>::delete_treap(this->root);
        cout<<"delete of treap done\n\n";
    }

    //function to insert a node into the treap
    void insert(key_t key, priorities_t prior)
    {
        this->root = this->root->insert_node(this->root,key,prior);
    }

    //function to overload the put out operator
    friend ostream& operator<<(ostream &o, const Treap_t<key_t, priorities_t> &rhs)
    {
        rhs.root->inorder_traversal(rhs.root);
        //cout<<*(rhs.root);
        return o;
    }

    //function to perform the preorder traversal of the treap
    void preorder()
    {
        this->root->preorder_traversal(this->root);
    }

    //function to perform the postorder traversal of the treap
    void postorder()
    {
        this->root->postorder_traversal(this->root);
    }

    Treap_node_t<key_t, priorities_t> *search(key_t search_key)
    {
        return this->root->search_node(this -> root, search_key);
    }


    //function to delete a node in the treap
    void delete_(key_t key)
    {
        this->root = this->root->delete_node(this->root,key);
    }

    // Treap_node_t<key_t, priorities_t> *inorder_succ(Treap_node_t<key_t, priorities_t> *node_x)
    // {
    //     return this->root->inorder_succ_node(this -> root, node_x);
    // }




    class Iterator
    {
    private:
        Treap_node_t<key_t,priorities_t> *ptr_it;
        Treap_node_t<key_t,priorities_t> *root;

    public:
        Iterator(Treap_node_t<key_t,priorities_t> *ptr_it, Treap_node_t<key_t,priorities_t> *root) : ptr_it(ptr_it), root(root) {}
        ~Iterator()
        {

        }

        // Add bidirectional support

        Iterator& operator++()
        {
            // return *(this->ptr_it->inorder_succ_node(this -> ptr_it, node_x));
            this->ptr_it = this->ptr_it->inorder_succ_node(this->root);

            return *this;
            // return Iterator(this->ptr_it->inorder_successor());

        }

        Iterator operator++(int)
        {
            Iterator temp(*this);
            ++*this;
            return temp;
        }

        Iterator& operator--()
        {
            
            this->ptr_it = this->ptr_it->inorder_predec_node(this->root);
            return *this;

        }

        Iterator operator--(int)
        {
            Iterator temp(*this);
            --*this;
            return temp;
        }

        // Change to lvalue usage
        key_t operator*()
        {
            return **(this->ptr_it);
        }

        bool operator==(const Iterator& rhs) const
        {
            // return this->ptr_it->node_val.first == rhs.ptr_it->node_val.first;
            if( this->ptr_it!=nullptr && rhs.ptr_it!=nullptr )
                return (*(this -> ptr_it) == *(rhs.ptr_it));
            else if( this->ptr_it==nullptr && rhs.ptr_it==nullptr )
                return 1;
            else return 0;
        }

        bool operator!=(const Iterator& rhs) const
        {
            return !(*this == rhs);
        }

        using difference_type = long;
        using value_type = long;
        using pointer = const long*;
        using reference = const long&;
        using iterator_category = std::bidirectional_iterator_tag;
    };

    Iterator begin()
    {
        return Iterator(this -> root -> iterator_begin(), this->root);
    }

    Iterator end()
    {
        return Iterator(nullptr, this->root);
    }

    
};

int main()
{
    cout<<"test\n";
    Treap_t<int,int> t1;
    // t1.insert(1,2);
    // t1.insert(3,4);
    // t1.insert(2,3);


    t1.insert(50,15);
    t1.insert(30,5);
    t1.insert(70,10);
    t1.insert(20,2);
    t1.insert(40,4);
    t1.insert(80,20);
    Treap_t<int,int> t2(t1);
    t2.insert(100,34);
    t1.insert(90,32);

    cout<<"t1\n";
    cout<<t1;
    cout<<"\n\n\n";
    cout<<"t2\n";
    cout<<t2;
    cout<<"\n\n\n";

    // Treap_t<int,int>::Iterator it

    // Treap_t<int,int> t3;
    // t3 = t1;
    // cout<<t3;
    //t1.preorder();


    // if(t1.search(90) != nullptr) 
    //     cout << "found\n";
    // else 
    //     cout << "not found\n";



    auto it_begin = t2.begin();
    auto it_end = t2.end();

    auto it = find(t1.begin(), t1.end(), 40);
    while(it_begin != it_end)
    {
        // if(*it_begin == 40)
        //     *it_begin = 17203432;
        cout << *it_begin << "\n";
        ++it_begin;
        // cout << it_begin << "\n";

    }
    if(it!=t1.end())
    {
        cout<<"FOUND" <<*it<<"\n";

        cout<<"reverse order\n";
        while(it!=t1.begin())
        {
            cout<<*it<<"\n";
            it--;
        }
    }

    cout << count(t1.begin(), t1.end(), 40) << "\n";

    cout << "checked iterator\n";
    // cout<<*it<<"\n";

}