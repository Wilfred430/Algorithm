#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int Memoized_Cut_Rod_Aux(const vector<int> &price, int rod_length, vector<int> &cut, vector<int> &first_cut)
{
    if (cut[rod_length] >= 0)
        return cut[rod_length];
    int q = INT_MIN;
    for (int i = 1; i <= rod_length; i++)
    {
        int temp = price[i] + Memoized_Cut_Rod_Aux(price, rod_length - i, cut, first_cut);
        if (temp > q)
        {
            q = temp;
            first_cut[rod_length] = i;
        }
    }
    cut[rod_length] = q;
    return q;
}

int Memoized_Cut_Rod(const vector<int> &price, int rod_length, vector<int> &first_cut)
{
    vector<int> cut(rod_length + 1, INT_MIN);
    cut[0] = 0;
    return Memoized_Cut_Rod_Aux(price, rod_length, cut, first_cut);
}

int Bottom_up_Cut_Rod(const vector<int> &price, int rod_length, vector<int> &first_cut)
{
    vector<int> cut(rod_length + 1, 0);
    cut[0] = 0;
    for (int j = 1; j <= rod_length; j++)
    {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++)
        {
            if (q < price[i] + cut[j - i])
            {
                q = price[i] + cut[j - i];
                first_cut[j] = i;
            }
        }
        cut[j] = q;
    }
    return cut[rod_length];
}

int main()
{
    int rod_length;
    cout << "input rod of length: ";
    cin >> rod_length;
    cout << "input price of rod of length : ";
    vector<int> price(rod_length + 1, 0);
    for (int i = 1; i <= rod_length; i++)
    {
        cin >> price[i];
    }
    cout << "-------------------------------------------------------------" << endl;
    cout << "Top_down" << endl;

    vector<int> first_cut(rod_length + 1, 0);
    int max_price = Memoized_Cut_Rod(price, rod_length, first_cut);
    cout << "maximum price: " << max_price << endl;

    vector<int> pieces;
    int n = rod_length;
    while (n > 0)
    {
        pieces.push_back(first_cut[n]);
        n -= first_cut[n];
    }
    for (int p : pieces)
        cout << p << " ";
    cout << endl;
    cout << "number of pieces: " << pieces.size() << endl;

    cout << endl;
    int min_price = rod_length * price[1];
    cout << "minimum price: " << min_price << endl;
    for (int i = 0; i < rod_length; i++)
        cout << "1 ";
    cout << endl;
    cout << "number of pieces: " << rod_length << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "Bottom-up:" << endl;

    vector<int> bu_first_cut(rod_length + 1, 0);
    int bu_max_price = Bottom_up_Cut_Rod(price, rod_length, bu_first_cut);
    cout << "maximum price: " << bu_max_price << endl;

    vector<int> bu_pieces;
    n = rod_length;
    while (n > 0)
    {
        bu_pieces.push_back(bu_first_cut[n]);
        n -= bu_first_cut[n];
    }
    for (int p : bu_pieces)
        cout << p << " ";
    cout << endl;
    cout << "number of pieces: " << bu_pieces.size() << endl;

    cout << endl;
    int bu_min_price = rod_length * price[1];
    cout << "minimum price: " << bu_min_price << endl;
    for (int i = 0; i < rod_length; i++)
        cout << "1 ";
    cout << endl;
    cout << "number of pieces: " << rod_length << endl;

    return 0;
}