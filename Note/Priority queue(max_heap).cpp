#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxHeapPriorityQueue
{
private:
    vector<int> heap;

    void heapify_up(int idx)
    {
        while (idx > 0)
        {
            int parent = (idx - 1) / 2;
            if (heap[idx] > heap[parent])
            {
                swap(heap[idx], heap[parent]);
                idx = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapify_down(int idx)
    {
        int size = heap.size();
        while (true)
        {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int largest = idx;
            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;
            if (largest != idx)
            {
                swap(heap[idx], heap[largest]);
                idx = largest;
            }
            else
            {
                break;
            }
        }
    }

public:
    // (a) Maximum(S): find the element with the largest key
    int maximum()
    {
        if (heap.empty())
            throw out_of_range("Heap is empty");
        return heap[0];
    }

    // (b) Extract-max(S): return and remove the element with the largest key
    int extract_max()
    {
        if (heap.empty())
            throw out_of_range("Heap is empty");
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return maxVal;
    }

    // (c) Increase-key(S, x, k): increase the value of element x to k
    // x: index, k: new key (must be greater than current key)
    void increase_key(int idx, int k)
    {
        if (idx < 0 || idx >= heap.size())
            throw out_of_range("Index out of range");
        if (k < heap[idx])
            throw invalid_argument("New key is smaller than current key");
        heap[idx] = k;
        heapify_up(idx);
    }

    // (d) Insert(S, x): insert a new element x
    void insert(int val)
    {
        heap.push_back(val);
        heapify_up(heap.size() - 1);
    }

    // 其他輔助函數
    bool empty()
    {
        return heap.empty();
    }

    int size()
    {
        return heap.size();
    }

    // 顯示所有元素（for debug）
    void print()
    {
        for (int v : heap)
            cout << v << " ";
        cout << endl;
    }
};

int main()
{
    MaxHeapPriorityQueue pq;
    pq.insert(10);
    pq.insert(30);
    pq.insert(20);
    pq.insert(5);

    cout << "Heap: "; pq.print();

    // (a) Maximum
    cout << "Maximum: " << pq.maximum() << endl;

    // (b) Extract-max
    cout << "Extract-max: " << pq.extract_max() << endl;
    cout << "Heap after extract-max: "; pq.print();

    // (c) Increase-key (將 index 2 的值由 10 增加到 25)
    pq.increase_key(2, 25);
    cout << "Heap after increase-key (index 2 to 25): "; pq.print();

    // (d) Insert
    pq.insert(40);
    cout << "Heap after insert 40: "; pq.print();

    return 0;
}