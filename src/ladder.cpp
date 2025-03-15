#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <set>
#include <unordered_map>
#include <algorithm>
#include "ladder.h"

using namespace std;

constexpr int INF = numeric_limits<int>::max();

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;

    int diff_count = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff_count++;
            if (diff_count > d) return false;
            if (len1 > len2) i++;
            else if (len2 > len1) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return diff_count + abs(len1 - i - (len2 - j)) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    if (word_list.find(end_word) == word_list.end()) return {};

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) return new_ladder;

                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << (i + 1 < ladder.size() ? " " : " \n");
    }
}


#define my_assert(e) { cout << #e << ((e) ? " passed" : " failed") << endl; }
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}