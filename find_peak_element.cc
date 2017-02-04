/* Given an array of integers, find a peak element in it.
 * An array element is peak if it is NOT smaller than its neighbors.
 * For corner elements, we need to consider only one neighbor.
 */

#include <iostream>
#include <vector>
using namespace std;

int peak(vector<int> elements) {
    if (elements.size() == 1) return elements[0];
    int left = 0; 
    int right = elements.size();
    while (left < right) {
        int m = (left + right) / 2;
        if (m >= 0 && m <= elements.size() - 1 &&
                elements[m] >= elements[m - 1] &&
                elements[m] >= elements[m + 1]) return elements[m];
        if (m == 0 && elements[m] > elements[m + 1]) return elements[m];
        if (m == elements.size() - 1 && elements[m] >= elements[m - 1]) return elements[m];
        if (elements[m] < elements[m - 1]) right = m - 1;
        else left = m + 1;
    }
    return elements[left];
}

int main() {
    vector<int> elements;
    int n;
    while (cin >> n) elements.push_back(n);
    cout << peak(elements) << endl;
    return 0;
}
