#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1.size() != str2.size()) return false;
    int diff_count = 0;
    for (size_t i = 0; i < str1.size(); ++i) {
        if (str1[i] != str2[i]) {
            if (++diff_count > d) return false;
        }
    }
    return diff_count == d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}