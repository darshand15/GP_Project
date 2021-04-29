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
    Treap_node_t(key_t key, priorities_t prior, Treap_node_t *left_n = nullptr, Treap_node_t* right_n = nullptr)
    :
    node_val(key, prior),left_n(left_n), right_n(right_n)
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

    void insert(key_t key, priorities_t prior)
    {
        this->root = this->root->insert_node(this->root,key,prior);
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

    cout<<t1;

    cout<<"\n\n\n";
    t1.preorder();
}