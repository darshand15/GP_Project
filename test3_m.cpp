#include <iostream>
using namespace std;
#include <algorithm>

template <typename key_t, typename priorities_t>
class Treap_node_t
{
    private:
    pair<key_t, priorities_t> node_val;
    Treap_node_t *left_n;
    Treap_node_t *right_n;

    //copy, assignment and dtor


    public:
    Treap_node_t(key_t key, priorities_t prior)
    : node_val(key, prior),left_n(nullptr), right_n(nullptr)
    {}

    Treap_node_t(const Treap_node_t &rhs)
    {
        this->node_val.first = rhs.node_val.first;
        this->node_val.second = rhs.node_val.second;
        this->right_n = nullptr;
        this->left_n = nullptr;
    }

    Treap_node_t& operator=(const Treap_node_t &rhs)
    {
        this->node_val.first = rhs.node_val.first;
        this->node_val.second = rhs.node_val.second;
        this->right_n = nullptr;
        this->left_n = nullptr;
        return *this;
    }

    ~Treap_node_t()
    {

    }



    friend ostream& operator<<(ostream &o, const Treap_node_t<key_t, priorities_t> &rhs)
    {
        o << "Key: " << rhs.node_val.first << "\n";
        o << "Priority: " << rhs.node_val.second << "\n";
        return o;
    }


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




    void inorder_traversal(Treap_node_t<key_t, priorities_t> *root) const
    {
        if(root)
        {
            inorder_traversal(root->left_n);
            cout << *root;
            inorder_traversal(root->right_n);
        }
    }

    void preorder_traversal(Treap_node_t<key_t, priorities_t> *root) const
    {
        if(root)
        {
            cout << *root;
            preorder_traversal(root->left_n);
            preorder_traversal(root->right_n);
        }
    }

    static void delete_treap(Treap_node_t<key_t,priorities_t> *root)
    {
        if(root)
        {
            delete_treap(root->left_n);
            delete_treap(root->right_n);
            cout << "DELETING\n" << *root << "\n";
            delete root;
        }
    }

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


    Treap_node_t* right_rotate(Treap_node_t* node)
    {
        Treap_node_t* left_subtree = node -> left_n;
        Treap_node_t* right_subtree_of_left_subtree = left_subtree -> right_n;

        left_subtree -> right_n = node;
        node -> left_n = right_subtree_of_left_subtree;

        return left_subtree;
    }

    Treap_node_t* left_rotate(Treap_node_t* node)
    {
        Treap_node_t* right_subtree = node -> right_n;
        Treap_node_t* left_subtree_of_right_subtree = right_subtree -> left_n;

        right_subtree -> left_n = node;
        node -> right_n = left_subtree_of_right_subtree;

        return right_subtree;
    } 
    // friend void delete_treap(Treap_node_t<key_t,priorities_t> *root);


};
















template <typename key_t, typename priorities_t>
class Treap_t
{
    private:
    Treap_node_t<key_t,priorities_t> *root;

    public:
    Treap_t(Treap_node_t<key_t,priorities_t> *root = nullptr)
    :
    root(root)
    {

    }

    //copy, assign, dtor

    Treap_t(const Treap_t &rhs)
    {
        Treap_node_t<key_t,priorities_t>::copy_treap(&(this->root), rhs.root);
    }



    Treap_t& operator=(const Treap_t &rhs)
    {
        Treap_node_t<key_t,priorities_t>::copy_treap(&(this->root), rhs.root);
        return *this;
    }

    ~Treap_t()
    {
        Treap_node_t<key_t,priorities_t>::delete_treap(this->root);
    }



    void insert(key_t key, priorities_t prior)
    {
        this->root = this->root->insert_node(this->root,key,prior);
    }

    void delete_(key_t key)
    {
        this->root = this->root->delete_node(this->root,key);
    }

    friend ostream& operator<<(ostream &o, const Treap_t<key_t, priorities_t> &rhs)
    {
        rhs.root->inorder_traversal(rhs.root);
        //cout<<*(rhs.root);
        return o;
    }

    void preorder()
    {
        this->root->preorder_traversal(this->root);
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
    t2.delete_(70);
    t2.delete_(30);
    t2.delete_(50);
    t2.delete_(20);
    cout<<"t1\n";
    cout<<t1;
    cout<<"\n\n\n";
    cout<<"t2\n";
    cout<<t2;
    cout<<"\n\n\n";
    // t1.preorder();
}