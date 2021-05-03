#include "demo_final.cpp"



bool IsOdd (int i) 
{
  return ((i%2)==1);
}




int main()
{

    // Insert Node
    // Delete Node
    // Delete Treap
    // Copy Treap
    // Use build constructor to insert
    // Display

    
    // Merge
    // Split

    // Union
    // Intersection
    // Diff

    // Traversals??
    
    
    
    // Search
    // Iterator
    // Member Find
    // Member Replace



    cout<<"test\n";
    Treap_t<int> t1;
    // t1.insert(1,2);
    // t1.insert(3,4);
    // t1.insert(2,3);

    // for(int i=0; i<123127; i++)
    // {
    //     t1.insert(rand());
    // }

    
    t1.insert(30);
    t1.insert(50);
    t1.insert(70);
    t1.insert(20);
    t1.insert(40);
    t1.insert(80);
    // Treap_t<int> t2(t1);
    // t2.insert(100);
    // t1.insert(90);

    cout<<"t1\n";
    cout<<t1;
    cout<<"\n\n\n";
    // cout<<"t2\n";
    // cout<<t2;
    // cout<<"\n\n\n";

    // Treap_t<int,int>::Iterator it

    // Treap_t<int,int> t3;
    // t3 = t1;
    // cout<<t3;
    t1.preorder();


    // if(t1.search(90) != nullptr) 
    //     cout << "found\n";
    // else 
    //     cout << "not found\n";



    // auto it_begin = t2.begin();
    // auto it_end = t2.end();

    // auto it = find(t1.begin(), t1.end(), 40);
    // while(it_begin != it_end)
    // {
    //     // if(*it_begin == 40)
    //     //     *it_begin = 17203432;
    //     cout << *it_begin << "\n";
    //     ++it_begin;
    //     // cout << it_begin << "\n";

    // }
    // if(it!=t1.end())
    // {
    //     cout<<"FOUND" <<*it<<"\n";

    //     cout<<"reverse order\n";
    //     while(it!=t1.begin())
    //     {
    //         cout<<*it<<"\n";
    //         it--;
    //     }
    // }

    // cout << count(t1.begin(), t1.end(), 40) << "\n";

    // cout << "checked iterator\n";
    // cout<<*it<<"\n";


    //checking copy
    // int a[10];
    // copy(t1.begin(),t1.end(),a);
    // for(int i = 0;i < 7; ++i)
    // {
    //     cout<<a[i]<<"\t";
    // }
    // cout<<"\n";

    //checking split
    srand(8);
    Treap_t<int> t1_l;
    Treap_t<int> t1_r;
    t1.split(45,&t1_l,&t1_r);
    t1_l.insert(1000);
    t1_r.insert(20);
    t1_r.insert(30);
    t1_l.insert(50);
    // cout<<"after split\n\n";


    // cout<<"t1\n"<<t1<<"\n\n\n";
    cout<<"t1_l\n"<<t1_l<<"\n\n\n";
    cout<<"t1_r\n"<<t1_r<<"\n\n\n";

    // Treap_t<int> diff;
    // diff.diff_treap(&t1_r, &t1_r);

    // cout<<"diff:\n"<<diff<<"\n\n\n";
    // Treap_t<int> t2;
    // t2.merge(&t1_l,&t1_r);
    // cout<<"t2\n\n"<<t2;

    // Treap_t<int> *t3 = nullptr;
    // Treap_t<int> *t4 = nullptr;
    // Treap_t<int> t5;
    // Treap_t<int> t6;
    // // t5.merge(t3,t4);
    // // cout<<"t5\n\n"<<t5;
    // t5.merge(&t5,&t6);
    // // cout<<"t4\n\n"<<t4;
    // cout<<"t5\n\n"<<t5;

    // Treap_t<int> t8;
    Treap_t<int> t9;
    t9.insert(130);
    t9.insert(140);
    t9.insert(120);
    t9.insert(150);

    Treap_t<int> diff;
    diff.diff_treap(&t9, &t1_r);

    cout<<"diff:\n"<<diff<<"\n\n\n";
    // // cout<<"test obj\n\n";
    // cout<<"t1_l\n\n"<<t1_l;
    // cout<<"t9\n\n"<<t9;
    // t8.union_treaps(&t1_l, &t1_r);
    // t8.intersect_treaps(&t1_l, &t9);
    // cout<<"t8\n\n"<<t8;
    // t8.union_treaps(&t8, &t8);
    // cout<<"test after union\n\n";
    // cout<<"t8\n\n"<<t8;
    // cout<<"t1l\n\n"<<t1_l;
    // cout<<"t1r\n\n"<<t1_r;

    vector<int> a1 = {1, 2, 3, 5};
    deque<int> a2 = {4, 5, 7, 1, 2};
    list<int> a3 = {1, 2, 3, 5};
    Treap_t<int> b1(a1.begin(), a1.end());
    Treap_t<int> b2(a2.begin(), a2.end());
    Treap_t<int> b3(a3.begin(), a3.end());
    Treap_t<int> b4;
    // copy(a1.begin(), a1.end(), b4.begin());
    cout << "b1:\n" << b1 << "\n";
    cout << "b2:\n" << b2 << "\n";
    cout << "b3:\n" << b3 << "\n";

    cout << *(b2.find(b2.begin(), b2.end(), 5))<<"\n";
    cout << *(b2.find(++++b2.begin(), b2.end(), 7))<<"\n";
    cout << *(b2.find(b2.begin(), ++++++b2.begin(), 2))<<"\n";
    cout << "b2:\n" << b2 << "\n";
    
    b2.replace(++b2.begin(), b2.end(), 14312, 10);
    
    cout << "b2:\n" << b2 << "\n";
    Treap_t<int> b5;
    // b5.copy(a2.begin(), a2.end(), b5.begin());
    // if(it != b2.end())
    // {
    //     cout<<"Found : "<<*it<<"\n";
    // }
    // else
    // {
    //     cout<<"Not found\n";
    // }
    

}