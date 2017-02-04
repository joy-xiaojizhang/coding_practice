#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> nums;

int get_upper_bound(int left, int right, int value) {
    if (right == 0) return 0;
    while (left + 1 < right) {
        int m = (left + right) / 2;
        if (nums[m] <= value) left = m;
        else right = m;
    }
    return left + 1;
}

void put(int value) {
    nums.insert(nums.begin() + get_upper_bound(0, nums.size(), value), value);
}

int get_rank(int value) {
    int left = 0;
    int right = nums.size();
    if (right == 0) return 0;
    while (left + 1 < right) {
        int m = (left + right) / 2;
        if (nums[m] < value) left = m;
        else right = m;
    }
    return left + (nums[left] < value);
}

int main() {
    put(10);
    put(10);
    put(20);
    put(20);
    put(30);
    put(30);
    for (int i = 0; i < nums.size(); i ++)
        cerr << nums[i] << " " << endl;
    cout << get_rank(9) << endl;
    cout << get_rank(10) << endl;
    cout << get_rank(11) << endl;
    cout << get_rank(19) << endl;
    cout << get_rank(20) << endl;
    cout << get_rank(21) << endl;
    return 0;
}
