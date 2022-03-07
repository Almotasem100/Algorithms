#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;

vector<int> longestSubSeq(vector<int> const& a) {

    int n = a.size();
    vector<vector<int>> lis;
    for(size_t i=0; i<n; i++) {
        lis.push_back({});
    }
    vector<int> d(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j] && d[i] < d[j]+1) {
                d[i] = d[j] + 1;
                lis[i].push_back(a[j]);
            }
        }
    }
    auto pos = distance(d.begin(),  std::max_element(d.begin(), d.end()));
    lis[pos].push_back(a[pos]);
    return lis[pos];
}


int main() {
    vector<int> arr = {7, 3, 8, 4, 2, 6};
    vector<int>result = longestSubSeq(arr);
    cout << "The Original Subsequence is: ";
    for(auto ele: arr) {
        cout<<ele<<" ";
    }
    cout << endl; 
    cout << "Length of Longest Increasing Subsequence is: " << result.size()<< endl;
    cout << "The Longest Increasing Subsequence is: ";
    for(auto ele: result) {
        cout<<ele<<" ";
    }
    return 0;
}