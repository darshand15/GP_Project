#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

#define DELETE_PRINT 1


template <typename key_t>
class Treap_node_t
{
    private:

    //pair that holds key and priority associated with the node
    pair<key_t, int> node_val;

    //pointer to the left child of the node
    Treap_node_t *left_n;

    //pointer to the right child of the node
    Treap_node_t *right_n;

    //implementation field to mark a node as duplicate
    int duplicate = 0;


    public:

    //constructor
    Treap_node_t(key_t key, int prior)
    : node_val(key, prior),left_n(nullptr), right_n(nullptr)
    {

    }

    //copy constructor
    Treap_node_t(const Treap_node_t &rhs)
    {
        // cout<<"HERE2\n";
        this->node_val.first = rhs.node_val.first;
        this->node_val.second = rhs.node_val.second;
        this->right_n = nullptr;
        this->left_n = nullptr;
    }

    //move constructor
    Treap_node_t(Treap_node_t &&rhs)
    :left_n(rhs.left_n), right_n(rhs.right_n)
    {
        // cout<<"HERE2\n";
        this->node_val = std::move(rhs.node_val);
        this->duplicate = std::move(rhs.duplicate);
        rhs.right_n = nullptr;
        rhs.left_n = nullptr;
    }

    // build constructor
    template < typename iter_t >
    Treap_node_t(iter_t first, iter_t last)
    {
        if(first != last)
        {
            auto mid = first;
            int n = distance(first, last);
            advance(mid, n/2);
            // cout<<"F: "<<*first<<" M: "<<*mid<<"\n";
            *this = Treap_node_t(*mid, rand()%100 + 1);
            try
            {   
                this->left_n = new Treap_node_t(first, mid);
            }
            catch(...)
            {
                this->left_n = nullptr;
            }
            advance(mid, 1);
            try
            {
                this->right_n = new Treap_node_t(mid, last);
            }
            catch(...)
            {
                this->right_n = nullptr;
            }
            this->heapify();
        }
        else
        {
            throw "No object creation required";
        }
    }

    void heapify()
    {
        Treap_node_t *max_ = this;
        if( this->left_n != nullptr && this->left_n->node_val.second > max_->node_val.second )
        {
            max_ = this->left_n;
        }
        if( this->right_n != nullptr && this->right_n->node_val.second > max_->node_val.second )
        {
            max_ = this->right_n;
        }
        if(*max_ != *this)
        {
            int temp = this->node_val.second;
            this->node_val.second = max_->node_val.second;
            max_->node_val.second = temp;
            max_->heapify();
        }
    }

    //copy assignment operator
    Treap_node_t& operator=(const Treap_node_t &rhs)
    {
        cout<<"COPY ASSIGNMENT\n";
        if( this!=&rhs )
        {
            if(this->left_n)
            {
                delete this->left_n;
            }
            if(this->right_n)
            {
                delete this->right_n;
            }
            this->node_val.first = rhs.node_val.first;
            this->node_val.second = rhs.node_val.second;
            this->right_n = rhs.right_n;
            this->left_n = rhs.left_n;
        }
        return *this;
    }

    //move assignment operator
    Treap_node_t& operator=(Treap_node_t &&rhs)
    {
        if(this != &rhs)
        {
            if(this->left_n)
            {
                delete this->left_n;
            }
            this->left_n = rhs.left_n;
            rhs.left_n = nullptr;

            if(this->right_n)
            {
                delete this->right_n;
            }
            this->right_n = rhs.right_n;
            rhs.right_n = nullptr;
            this->node_val = std::move(rhs.node_val);
            this->duplicate = std::move(rhs.duplicate);
        }
        return *this;


        // if(this != &rhs)
        // {
        //     if(this->root != nullptr)
        //     {
        //         this->root->delete_treap();
        //     }
        //     this->root = rhs.root;
            
        //     #if DELETE_PRINT
        //     cout<<"delete of treap done\n\n";
        //     #endif

        //     this->priors = std::move(rhs.priors);
        //     this->choice = std::move(rhs.choice);
        //     rhs.root = nullptr;            
        // }

        // return *this;

    }

    //destructor
    ~Treap_node_t()
    {
        cout<<"Deleting node\n";
        cout<<*this<<"\n";
    }

    //function to overload put out operator
    friend ostream& operator<<(ostream &o, const Treap_node_t<key_t> &rhs)
    {
        o << "Key: " << rhs.node_val.first << "\n";
        o << "Priority: " << rhs.node_val.second << "\n";
        // o << "Duplicate: " << rhs.duplicate << "\n";
        return o;
    }

    //function to insert a node into the treap
    Treap_node_t* insert_node(Treap_node_t* root ,key_t key, int prior)
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
            root->duplicate = 1;
            root->node_val.second = prior;
            root->heapify();
        }

        return root;
    }

    //function to split treap
    void split_node(Treap_node_t **left_sub_treap_root, Treap_node_t **right_sub_treap_root)
    {
        *left_sub_treap_root = this->left_n;
        *right_sub_treap_root = this->right_n;
        this->left_n = nullptr;
        this->right_n = nullptr;
    }

    //function to merge two treaps
    void merge_node(Treap_node_t **merged_treap, Treap_node_t *left_sub_treap_n, Treap_node_t *right_sub_treap_n)
    {
        if(left_sub_treap_n == nullptr && right_sub_treap_n == nullptr)
        {
            *merged_treap = nullptr;
        }

        else if(left_sub_treap_n == nullptr)
        {
            *merged_treap = right_sub_treap_n;
        }

        else if(right_sub_treap_n == nullptr)
        {
            *merged_treap = left_sub_treap_n;
        }

        else if(left_sub_treap_n->node_val.second > right_sub_treap_n->node_val.second)
        {
            this->merge_node(&(left_sub_treap_n->right_n), left_sub_treap_n->right_n, right_sub_treap_n);
            *merged_treap = left_sub_treap_n;
        }

        else
        {
            this->merge_node(&(right_sub_treap_n->left_n), left_sub_treap_n, right_sub_treap_n->left_n);
            *merged_treap = right_sub_treap_n;
        }
    }

    Treap_node_t* union_node(Treap_node_t *left_treap, Treap_node_t *right_treap)
    {
        if(left_treap == nullptr && right_treap == nullptr)
        {
            return nullptr;
        }

        else if(left_treap == nullptr)
        {
            return right_treap;
        }

        else if(right_treap == nullptr)
        {
            return left_treap;
        }

        else if(left_treap->node_val.second < right_treap->node_val.second)
        {
            return this->union_node(right_treap, left_treap);
        }

        Treap_node_t *left_temp, *right_temp, *root;

        right_treap = right_treap->insert_node(right_treap, left_treap->node_val.first, 101+rand()%100);
        right_treap->split_node(&left_temp, &right_temp);
        
        // cout<<"Before new \n";
        root = new Treap_node_t(*left_treap);
        // cout<<"After new \n";
        root->left_n = union_node(left_treap->left_n, left_temp);
        root->right_n = union_node(left_treap->right_n, right_temp);

        return root;

    }

    //function to find the intersection of two treaps
    Treap_node_t* intersect_node(Treap_node_t *left_treap, Treap_node_t *right_treap)
    {
        if(left_treap == nullptr || right_treap == nullptr)
        {
            return nullptr;
        }

        else if(left_treap->node_val.second < right_treap->node_val.second)
        {
            return this->intersect_node(right_treap, left_treap);
        }

        Treap_node_t *left_temp, *right_temp, *root, *left, *right;

        right_treap = right_treap->insert_node(right_treap, left_treap->node_val.first, 110);
        right_treap->split_node(&left_temp, &right_temp);

        left = intersect_node(left_treap->left_n, left_temp);
        right = intersect_node(left_treap->right_n, right_temp);

        if(right_treap->duplicate)
        {
            // cout<<"HERE in DUP\n";
            root = new Treap_node_t(*left_treap);
            root->left_n = left;
            root->right_n = right;
            return root;
        }
        else
        {
            // cout<<"HERE in NOT DUP\n";
            Treap_node_t *temp = nullptr;
            
            left->merge_node(&(temp), left, right);
            left = nullptr;
            right = nullptr;
            return temp;
        }
    }

    Treap_node_t *diff_node(Treap_node_t *left_treap, Treap_node_t *right_treap, bool rt_subt)
    {
        if(left_treap == nullptr || right_treap == nullptr)
        {
            return rt_subt ? left_treap : right_treap;
        }

        else if(left_treap->node_val.second < right_treap->node_val.second)
        {
            return this->diff_node(right_treap, left_treap, !rt_subt);
        }

        Treap_node_t *left_temp, *right_temp, *root, *left, *right;

        right_treap = right_treap->insert_node(right_treap, left_treap->node_val.first, 110);
        right_treap->split_node(&left_temp, &right_temp);

        left = diff_node(left_treap->left_n, left_temp, rt_subt);
        right = diff_node(left_treap->right_n, right_temp, rt_subt);

        if( !right_treap->duplicate && rt_subt )
        {
            root = new Treap_node_t(*left_treap);
            root->left_n = left;
            root->right_n = right;
            return root;
        }
        else
        {
            Treap_node_t *temp = nullptr;

            left->merge_node(&(temp), left, right);
            left = nullptr;
            right = nullptr;

            return temp;
        }
    }

    //function to perform inorder traversal of the treap
    void inorder_traversal(Treap_node_t<key_t> *root) const
    {
        if(root)
        {
            inorder_traversal(root->left_n);
            cout << *root;
            inorder_traversal(root->right_n);
        }
    }


    //function to perform preorder traversal of the treap
    void preorder_traversal(Treap_node_t<key_t> *root) const
    {
        if(root)
        {
            cout << *root;
            preorder_traversal(root->left_n);
            preorder_traversal(root->right_n);
        }
    }

    //function to perform postorder traversal of the treap
    void postorder_traversal(Treap_node_t<key_t> *root) const
    {
        if(root)
        {
            postorder_traversal(root->left_n);
            postorder_traversal(root->right_n);
            cout << *root;
        }
    }

    //function to delete the treap
    void delete_treap()
    {
        if(this->left_n != nullptr)
        {
            this->left_n->delete_treap();
        }
        if(this->right_n != nullptr)
        {
            this->right_n->delete_treap();
        }
            
        #if DELETE_PRINT
            cout << "DELETING\n" << *this << "\n";
        #endif

        delete this;
    }

    //static function to copy the treap
    static Treap_node_t<key_t>* copy_treap(Treap_node_t<key_t>** lhs, Treap_node_t<key_t> *root)
    {
        if(root)
        {
            (*lhs) = new Treap_node_t<key_t>(*root);
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
        if(root == nullptr || root->node_val.first == search_key)
        {
            return root;
        }

        else if(root->node_val.first < search_key)
        {
            return search_node(root -> right_n, search_key);
        }

        else if(root->node_val.first > search_key)
        {
            return search_node(root -> left_n, search_key);
        }
        return nullptr;
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

        else if(root->left_n == nullptr)
        {
            Treap_node_t* temp = root->right_n;
            delete root;
            root = temp;
        }

        else if(root->right_n == nullptr)
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

    //function to overload the dereferencing operator for rvalue usage
    key_t operator*()
    {
        return this->node_val.first;
    }

    //function to find the inorder successor of a node
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

    //function to find the inorder predecessor of a node
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

    //function to find the first node of the tree based on inorder traversal
    Treap_node_t *iterator_begin()
    {
        Treap_node_t *temp = this;
        while(temp -> left_n != nullptr)
        {
            temp = temp -> left_n;
        }
        return temp;
    }

    //function to find the last node of the tree based on inorder traversal
    Treap_node_t *iterator_end()
    {
        Treap_node_t *temp = this;
        while(temp -> right_n != nullptr)
        {
            temp = temp -> right_n;
        }
        return temp;
    }

    //function to overload the equality operator
    bool operator==(const Treap_node_t& rhs)
    {
        return this->node_val.first == rhs.node_val.first;
    }

    //function to overload the inequality operator
    bool operator!=(const Treap_node_t& rhs)
    {
        return !(*this == rhs);
    }

    //function to print the treap as tree structure
    void print_2d_node(int space = 0)
    {
        space += 10;
        if( this->right_n!=nullptr )
        {
            this->right_n->print_2d_node(space);
        }

        cout<<"\n";

        for (int i = 10; i < space; i++) 
        {
            cout<<" "; 
        }

        cout << this->node_val.first << " " << this->node_val.second;

        if( this->left_n!=nullptr )
        {
            this->left_n->print_2d_node(space);
        }
    }
    
};


template <typename key_t>
class Treap_t
{
    private:

    //pointer to the root of the treap
    Treap_node_t<key_t> *root;

    //implementation field to decide the way the priorities are defined
    //'r' for random
    char choice;

    //implemetation field to store all the priorities defined
    vector<int> priors;

    public:

    //constructor
    Treap_t(char choice = 'r',Treap_node_t<key_t> *root = nullptr)
    :
    choice(choice), root(root)
    {

    }

    //copy constructor
    Treap_t(const Treap_t &rhs)
    {
        
        if(rhs.root != nullptr)
        {
            this->root = Treap_node_t<key_t>::copy_treap(&(this->root), rhs.root);
        }
        this->priors.resize(rhs.priors.size());
        copy(rhs.priors.begin(),rhs.priors.end(),this->priors.begin());
        this->choice = rhs.choice;
    }

    //build constructor
    template < typename iter_t >
    Treap_t(iter_t first, iter_t last)
    {
        // int n = distance(first, last);
        // advance(first, n/2);
        // cout<<"HERE\n";
        this->choice = 'r';
        this->root = nullptr;
        if(!is_sorted(first, last))
        {
            while(first != last)
            {
                this->insert(*first);
                ++first;
            }
        }
        else
        {
            this->root = new Treap_node_t<int>(first, last);
        }
        // this->root = (first, last);
    }



    //copy assignment operator
    Treap_t& operator=(const Treap_t &rhs)
    {
        if(this != &rhs)
        {
            if(this->root != nullptr)
            {
                this->root->delete_treap();
            }
            
            #if DELETE_PRINT
            cout<<"delete of treap done\n\n";
            #endif

            this->root = Treap_node_t<key_t>::copy_treap(&(this->root), rhs.root);
            this->priors.resize(rhs.priors.size());
            std::copy(rhs.priors.begin(),rhs.priors.end(),this->priors.begin());
            this->choice = rhs.choice;            
        }

        return *this;
    }

    //move constructor
    Treap_t(Treap_t&& rhs)
    : root(rhs.root)
    {
        this->choice = std::move(rhs.choice);
        this->priors = std::move(rhs.priors);
        rhs.root = nullptr;
    }

    //move assignment operator
    Treap_t& operator=(Treap_t &&rhs)
    {
        if(this != &rhs)
        {
            if(this->root != nullptr)
            {
                this->root->delete_treap();
            }
            this->root = rhs.root;
            
            #if DELETE_PRINT
            cout<<"delete of treap done\n\n";
            #endif

            this->priors = std::move(rhs.priors);
            this->choice = std::move(rhs.choice);
            rhs.root = nullptr;            
        }

        return *this;
    }

    //destructor
    ~Treap_t()
    {
        if(this->root != nullptr)
        {
            this->root->delete_treap();
        }
        #if DELETE_PRINT
        cout<<"delete of treap done\n\n";
        #endif
    }

    //function to insert a node into the treap
    void insert(key_t key)
    {
        int new_prior;
        switch(this->choice)
        {
            case 'r':
            {

                while((std::find(priors.begin(),priors.end(),new_prior = rand()%100 + 1))!=priors.end())
                {
                    break;
                }
                priors.emplace_back(new_prior);
                break;
            }
        }
        this->root = this->root->insert_node(this->root,key,new_prior);
    }

    //function to split a treap
    void split(key_t key, Treap_t *left_sub_treap, Treap_t *right_sub_treap)
    {
        this->root = this->root->insert_node(this->root, key, 101+rand()%100);
        this->root->split_node(&(left_sub_treap->root),&(right_sub_treap->root));
        
    }

    //function to merge two treaps
    //pre condition : elements of left subtreap are lesser than the elements of the right subtreap
    void merge(Treap_t *left_sub_treap, Treap_t *right_sub_treap)
    {
        // Handles Call through object address
        if(left_sub_treap->root == nullptr && right_sub_treap->root == nullptr)
        {
            this->root = nullptr;
        }

        else if(left_sub_treap->root == nullptr)
        {
            this->root = right_sub_treap->root;
            right_sub_treap->root = nullptr;
        }

        else if(right_sub_treap->root == nullptr)
        {
            this->root = left_sub_treap->root;
            left_sub_treap->root = nullptr;
        }

        else
        {
            left_sub_treap->root->merge_node(&(this->root), left_sub_treap->root, right_sub_treap->root);
            left_sub_treap->root = nullptr;
            right_sub_treap->root = nullptr;
        }

        
    }


    //function to perform union of two treaps
    void union_treaps(Treap_t *treap1, Treap_t *treap2)
    {
        // cout<<"test union";
        
        if(treap1->root == nullptr && treap2->root == nullptr)
        {
            this->root = nullptr;
            // cout<<"test11\n\n";
        }

        else if(treap1->root == nullptr)
        {
            *this = *treap2;
            // cout<<"test22\n\n";
        }

        else if(treap2->root == nullptr)
        {
            *this = *treap1;
            // cout<<"test33\n\n";
        }

        else
        {
            // cout<<"testtinhggggg";
            Treap_t<key_t> *temp1 = new Treap_t(), *temp2 = new Treap_t();
            
            *temp1 = *treap1;
            *temp2 = *treap2;

            // cout<<"TEMP1\n\n"<<*temp1<<"\n\n";
            // cout<<"TEMP2\n\n"<<*temp2<<"\n\n";
            // cout<<"before call to union node\n\n";
            this->root = temp1->root->union_node(temp1->root, temp2->root);
            // cout<<"after call to union node\n\n";
            // cout<<"TEMP1\n\n"<<*temp1<<"\n\n";
            // cout<<"TEMP2\n\n"<<*temp2<<"\n\n";
        }
    }

    //function to perform intersection of two treaps
    void intersect_treaps(Treap_t *treap1, Treap_t *treap2)
    {
        if(treap1->root == nullptr || treap2->root == nullptr)
        {
            this->root = nullptr;
        }

        else
        {
            Treap_t<key_t> *temp1 = new Treap_t(), *temp2 = new Treap_t();
            
            *temp1 = *treap1;
            *temp2 = *treap2;
            this->root = temp1->root->intersect_node(temp1->root, temp2->root);
        }
        
    }


    //function to find the set difference of two treaps
    void diff_treap(Treap_t *treap1, Treap_t *treap2)
    {
        if(treap1->root == nullptr && treap2->root == nullptr)
        {
            this->root = nullptr;
        }

        else if(treap1->root == nullptr)
        {
            *this = *treap2;
        }

        else if(treap2->root == nullptr)
        {
            *this = *treap1;
        }

        else
        {
            Treap_t<key_t> *temp1 = new Treap_t(), *temp2 = new Treap_t();
            
            *temp1 = *treap1;
            *temp2 = *treap2;
            this->root = temp1->root->diff_node(temp1->root, temp2->root, true);
            
        }
    }

    
    //function to delete a node in the treap
    void delete_(key_t key)
    {
        this->root = this->root->delete_node(this->root,key);
    }

    //function to overload the put out operator
    friend ostream& operator<<(ostream &o, const Treap_t<key_t> &rhs)
    {
        // rhs.root->inorder_traversal(rhs.root);
        rhs.print_2d();
        //cout<<*(rhs.root);
        return o;
    }

    //function to perform the preorder traversal of the treap
    void inorder()
    {
        this->root->inorder_traversal(this->root);
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

    
    //iterator class
    class Iterator
    {

        private:
            Treap_node_t<key_t> *ptr_it;

            //implementation field pointing to the root of the treap
            Treap_node_t<key_t> *root;

        public:

            //constructor
            Iterator(Treap_node_t<key_t> *ptr_it, Treap_node_t<key_t> *root) 
            : ptr_it(ptr_it), root(root) 
            {

            }
            
            //destructor
            ~Iterator()
            {

            }

            //function to overload the pre increment operator
            Iterator& operator++()
            {
                this->ptr_it = this->ptr_it->inorder_succ_node(this->root);
                return *this;
            }

            //function to overload the post increment operator
            Iterator operator++(int)
            {
                Iterator temp(*this);
                ++*this;
                return temp;
            }

            //function to overload the pre decrement operator
            Iterator& operator--()
            {
                
                this->ptr_it = this->ptr_it->inorder_predec_node(this->root);
                return *this;

            }

            //function to overload the post decrement operator
            Iterator operator--(int)
            {
                Iterator temp(*this);
                --*this;
                return temp;
            }

            //function to overload the dereferencing operator for rvalue usage
            key_t operator*()
            {
                return **(this->ptr_it);
            }

            //function to overload the equality operator
            bool operator==(const Iterator& rhs) const
            {
                // return this->ptr_it->node_val.first == rhs.ptr_it->node_val.first;
                if( this->ptr_it!=nullptr && rhs.ptr_it!=nullptr )
                {
                    return (*(this -> ptr_it) == *(rhs.ptr_it));
                }
                else if( this->ptr_it==nullptr && rhs.ptr_it==nullptr )
                {
                    return 1;
                }
                else 
                {
                    return 0;
                }
            }

            //function to overload the inequality operator
            bool operator!=(const Iterator& rhs) const
            {
                return !(*this == rhs);
            }

            //function to find if the iterator is the end of the container
            bool is_end()
            {
                return this->ptr_it == nullptr;
            }
            
            using difference_type = long;
            using value_type = long;
            using pointer = const long*;
            using reference = const long&;
            using iterator_category = std::bidirectional_iterator_tag;
    };


    //function to define the begin iterator
    Iterator begin()
    {
        return Iterator(this -> root -> iterator_begin(), this->root);
    }

    //function to define the end iterator
    Iterator end()
    {
        return Iterator(nullptr, this->root);
    }

    //function to search for a node in the treap
    Iterator find(Iterator first, Iterator last, key_t search_key)
    {
        if(first != last)
        {
            if( !last.is_end() )
            {
                auto last_orig = last;
                auto last_temp = --last;
                if(search_key >= *first && search_key <= *last_temp)
                {
                    Treap_node_t<key_t>* temp = this->root->search_node(this -> root, search_key);
                    if(temp != nullptr)
                    {
                        return Iterator(temp, this->root);
                    }
                    else 
                    {
                        return last_orig;
                    }
                }
                else
                {
                    return last_orig;
                }
            }
            else
            {
                // auto last_temp = Iterator(this->root->iterator_end(), this->root);
                if(search_key >= *first)
                {
                    Treap_node_t<key_t>* temp = this->root->search_node(this -> root, search_key);
                    if(temp != nullptr)
                    {
                        return Iterator(temp, this->root);
                    }
                    else 
                    {
                        return last;
                    }
                }
                else
                {
                    return last;
                }
            }
        }
        return last;
    }

    //function to replace a node with another node
    void replace(Iterator first, Iterator last, key_t old_value, key_t new_value)
    {
        if(this->find(first, last, old_value)!=last)
        {
            this->delete_(old_value);
            this->insert(new_value);
        }
        
    }

    void print_2d() const
    {
        if( this->root!=nullptr )
        {
            this->root->print_2d_node();
        }
    }
    
};

// int main()
// {
//     Treap_t<int> t_1;
//     t_1.insert(19);
//     t_1.insert(23);
//     t_1.insert(5);
//     t_1.insert(1);
//     t_1.insert(90);
//     t_1.insert(28);
//     t_1.insert(55);


//     cout<<"Tree T_1:\n\n"<<t_1<<"\n";
//     cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";


//     Treap_t<int> t_2(move(t_1));


//     cout<<"Tree T_2:\n\n"<<t_2<<"\n";
//     cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";


//     Treap_t<int> t_3 = move(t_2);
    
    
//     cout<<"Tree T_3:\n\n"<<t_3<<"\n";
//     cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";


//     Treap_t<int> t_4;
//     t_4 = move(t_3);


//     cout<<"Tree T_4:\n\n"<<t_4<<"\n";
//     cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";


//     vector<int> v_1 = {9, 82, 158, 1912, 174, 242, 99, 108, 235, 911, 100, 102, 555};


//     Treap_t<int> t_5(v_1.begin(), v_1.end());

//     cout<<"Tree T_5:\n\n"<<t_5<<"\n";
//     cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

//     t_5 = move(t_4);

//     cout<<"Tree T_5:\n\n"<<t_5<<"\n";
//     cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

//     Treap_node_t<int> n_1(62, 78);
//     cout<<"n_1\n"<<n_1<<"\n\n";

//     Treap_node_t<int> n_2(move(n_1));
//     cout<<"n_2\n"<<n_2<<"\n\n";

//     Treap_node_t<int> n_3 = move(n_2);
//     cout<<"n_3\n"<<n_3<<"\n\n";

    

//     Treap_node_t<int> n_5(4, 5);
//     n_5 = move(n_3);
//     cout<<"n_5\n"<<n_5<<"\n\n";

//     // Treap_node_t<int> n_2(move(n_1));
    

// }