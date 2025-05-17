#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Array
{
    int heap_size = 0;
    vector<int> v;
};

void Min_heapify(Array &a, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;
    if (l < a.heap_size && a.v[l] < a.v[i])
    {
        smallest = l;
    }
    if (r < a.heap_size && a.v[r] < a.v[smallest])
    {
        smallest = r;
    }
    if (smallest != i)
    {
        swap(a.v[i], a.v[smallest]);
        Min_heapify(a, smallest);
    }
}

void Build_min_heap(Array &a)
{
    a.heap_size = a.v.size();
    for (int i = (a.v.size() - 1) / 2; i >= 0; i--)
    {
        Min_heapify(a, i);
    }
}

void Heapsort(Array &a)
{
    Build_min_heap(a);
    for (int i = a.v.size() - 1; i >= 1; i--)
    {
        swap(a.v[0], a.v[i]);
        a.heap_size--;
        Min_heapify(a, 0);
    }
}

int main()
{
    int size, tmp;
    cout << "-----------------------------------------------------------------\nPlease enter the size of a array you insert lately: ";
    while (cin >> size) 
    {
        if (size <= 0) {
            cout << "Size must be positive. Try again.\n";
            continue;
        }

        Array a;
        a.v.reserve(size);
        cout << "Please enter the element of the array (separated by space): ";
        for (int i = 0; i < size; i++)
        {
            cin >> tmp;
            a.v.push_back(tmp);
        }

        Heapsort(a);

        cout << "After sorting: ";
        for (auto it : a.v)
        {
            cout << it << " ";
        }
        cout << endl;

        cout << "-----------------------------------------------------------------\nPlease enter the size of a array you insert lately: ";
    }

    return 0;
}