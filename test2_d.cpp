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
    Treap_node_t(key_t key, priorities_t prior, Treap_node_t *left_n = NULL, Treap_node_t* right_n = NULL)
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
 
};

template <typename key_t, typename priorities_t>
class Treap_t
{
    private:
    Treap_node_t<key_t,priorities_t> *root;

    public:
    Treap_t(Treap_node_t<key_t,priorities_t> *root = NULL)
    :
    root(root)
    {

    }

    //copy, assign, dtor

    void insert(Treap_t *treap, key_t key, priorities_t prior)
    {
        //tree is empty
        if(!treap->root)
        {
            Treap_node_t *temp = new Treap_node_t(key, prior);
            treap->root = temp;
        }



    }



};


int main()
{
    cout<<"test\n";
    Treap_t<int,int>t1();
    cout<<t1;
}