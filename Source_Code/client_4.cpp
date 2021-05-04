#include "treap.h"
#include <iostream>
#include <string>

using namespace std;

bool IsOdd (int i) 
{
  return ((i%2)==1);
}

bool IsEven (int i) 
{
  return ((i%2)==0);
}

int main()
{
    // checking the following operations:
    // Iterators
    // Algorithms
    
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
    srand(16);
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

    Treap_t<string> t_3;
    t_3.insert("D");
    t_3.insert("B");
    t_3.insert("G");
    t_3.insert("A");
    t_3.insert("P");
    t_3.insert("Q");
    t_3.insert("T");

    cout<<"Tree T_1:\n\n"<<t_1<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout<<"Tree T_3:\n\n"<<t_3<<"\n";
    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
    
    cout<<"Generic Find\n\n";

    Treap_t<int>::Iterator it_1 = find(t_1.begin(), t_1.end(), 23);
    if(it_1 != t_1.end())
    {
        cout << "Key " << *it_1 << " found in T_1" << "\n\n";
    }
    else
    {
        cout << "Key " << 23 << " not found in T_1" << "\n\n";
    }

    Treap_t<int>::Iterator it_2 = find(t_1.begin(), t_1.end(), 364);

    if(it_2 != t_1.end())
    {
        cout << "Found key " << *it_2 << " in T_1" << "\n\n";
    }
    else
    {
        cout << "Key " << 364 << " not found in T_1" << "\n\n";
    }

    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout<<"Member Find\n\n";
    Treap_t<int>::Iterator it_3 = t_1.find(t_1.begin(), t_1.end(), 23);

    if(it_3 != t_1.end())
    {
        cout << "Found key " << *it_3 << " in T_1" << "\n\n";
    }
    else
    {
        cout << "Key " << 23 << " not found in T_1" << "\n\n";
    }

    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout<<"Generic Find_if\n\n";

    Treap_t<int>::Iterator it_4 = find_if(t_1.begin(), t_1.end(), IsEven);

    if(it_4 != t_1.end())
    {
        cout << "Found Even key " << *it_4 << " in T_1" << "\n\n";
    }
    else
    {
        cout << "Even Key not found in T_1" << "\n\n";
    }


    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout<<"Member Replace\n\n";

    t_3.replace(t_3.begin(), t_3.end(), "B", "H");
    t_3.replace(t_3.begin(), t_3.end(), "D", "F");
    t_3.replace(t_3.begin(), t_3.end(), "Y", "K");

    cout<<"T_3 after replacing B with H and D with F and trying to replace a non existent key Y with K\n" << t_3 << "\n\n";

    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout<<"Generic Count and Count_if\n\n";

    int c_1 = count(t_1.begin(), t_1.end(), 5);

    cout<<"Count of key " << 5 << " in T_1: " << c_1 << "\n\n";

    int c_2 = count_if(t_1.begin(), t_1.end(), IsOdd);

    cout<<"Count of Odd keys" << " in T_1 : " << c_2 << "\n\n";

    cout<<"\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
}


