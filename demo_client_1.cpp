#include "demo_final_1.cpp"
// #include "test2_m.cpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Insert Node
    // Delete Node
    // Delete Treap
    // Copy Treap
    // Display

    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    Treap_t<int> t_1;
    t_1.insert(19);
    t_1.insert(23);
    t_1.insert(5);
    t_1.insert(1);
    t_1.insert(90);
    t_1.insert(28);
    t_1.insert(55);

    // for(int i = 0; i<30; i++)
    // {
    //     t_1.insert(rand()%100);
    // }

    cout<<"Tree T_1:\n\n"<<t_1<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
    
    Treap_t<double> t_2;
    t_2.insert(1.5);
    t_2.insert(83.972);
    t_2.insert(5.0);
    t_2.insert(12.28);
    t_2.insert(59.08);
    t_2.insert(3.14);
    t_2.insert(99.99);
    
    cout<<"Tree T_2:\n\n"<<t_2<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    Treap_t<string> t_3;
    t_3.insert("D");
    t_3.insert("B");
    t_3.insert("G");
    t_3.insert("A");
    t_3.insert("P");
    t_3.insert("Q");
    t_3.insert("T");

    cout<<"Tree T_3:\n\n"<<t_3<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout << "Deleting G and T from t_3\n\n";
    t_3.delete_("G");
    t_3.delete_("T");

    cout<<"Tree T_3:\n\n"<<t_3<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    vector<int> v_1 = {9, 82, 158, 1912, 174, 242, 99, 108, 235, 911, 100, 102, 555};

    //build constructor - O(n)
    Treap_t<int> t_4(v_1.begin(), v_1.end());

    cout << "Using generic build constructor to construct T_4\n\n";
    cout<<"Tree T_4:\n\n"<<t_4<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    //copy ctor call
    Treap_t<int> t_5(t_1);
    cout << "Using Copy constructor to copy from T_1\n\n";
    cout<<"Tree T_5:\n\n"<<t_5<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
    
    //copy constructor for double
    Treap_t<double> t_6 = t_2;
    cout << "Using Copy constructor to copy from T_2\n\n";
    cout<<"Tree T_6:\n\n"<<t_6<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
    
    //copy assignment operator for string
    Treap_t<string> t_7;
    t_7 = t_3;
    cout << "Using Copy assignment operator to copy from T_3\n\n";
    cout<<"Tree T_7:\n\n"<<t_7<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout << "Using Copy assignment operator to copy from T_1 where T_4 was not initially empty\n\n";
    cout<<"Assigning t_4 to t_1\n\n";
    t_1 = t_4;

    cout<<"Tree T_1:\n\n"<<t_1<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout<<"Tree T_4:\n\n"<<t_4<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";


    // Treap_t<int> t_5 = {1,2,3,4,5};

    // cout<<"Tree T_5:\n\n"<<t_5<<"\n";
    // cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";



}


