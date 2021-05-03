#include "demo_final.cpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Traversals
    // Search
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    Treap_t<int> t_1;
    t_1.insert(19);
    t_1.insert(23);
    t_1.insert(5);
    t_1.insert(1);
    t_1.insert(90);
    t_1.insert(28);
    t_1.insert(55);
    t_1.insert(82);
    t_1.insert(100);
    t_1.insert(9);
    
    Treap_t<double> t_2;
    t_2.insert(1.5);
    t_2.insert(83.972);
    t_2.insert(5.0);
    t_2.insert(12.28);
    t_2.insert(59.08);
    t_2.insert(3.14);
    t_2.insert(99.99);

    Treap_t<string> t_3;
    t_3.insert("D");
    t_3.insert("B");
    t_3.insert("G");
    t_3.insert("A");
    t_3.insert("P");
    t_3.insert("Q");
    t_3.insert("T");

    vector<int> v_1 = {9, 82, 158, 1912, 174, 242, 99, 108, 235, 911, 100, 102, 555};

    Treap_t<int> t_4(v_1.begin(), v_1.end());

    Treap_t<int> t_5;

    t_5.union_treaps(&t_1, &t_4);

    Treap_t<int> t_6;

    t_6.intersect_treaps(&t_1, &t_4);


    t_1.inorder();
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
    t_1.preorder();
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
    t_1.postorder();
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";


}


