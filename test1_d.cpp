#include <iostream>
using namespace std;
#include <algorithm>

template <typename key_t, typename priorities_t>
class Treap_t
{
    private:
    pair<key_t, priorities_t> node_val;
    Treap_t *left_n;
    Treap_t *right_n;

    //copy, assignment and dtor


    public:
    Treap_t(key_t key, priorities_t prior, Treap_t *left_n = NULL, Treap_t* right_n = NULL)
    :
    node_val(key, prior),left_n(left_n), right_n(right_n)
    {

    }

    friend ostream& operator<<(ostream &o, const Treap_t<key_t, priorities_t> &rhs)
    {
        o << "Key: " << rhs.node_val.first << "\n";
        o << "Priority: " << rhs.node_val.second << "\n";
        return o;
    }

    void insert_bst(Treap_t *root, key_t key, priorities_t prior)
    {
        //tree is empty
        if(root == NULL)
        {
            root = new Treap_t<key_t,priorities_t>()
        }
    }


};


int main()
{
    cout<<"test\n";
    Treap_t<int,int>t1(1,2);
    cout<<t1;
}