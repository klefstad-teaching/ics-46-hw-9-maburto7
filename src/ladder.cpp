#include "ladder.h"

void error(string word1, string word2, string msg){

}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (str1.size() != str2.size()) return false;

    int count = 0;
    for (size_t i = 0; i < str1.size(); ++i) {
        if (str1[i] != str2[i]) {
            ++count;
            if (count > d) return false;
        }
    }
    return count <= d;
    }

bool is_adjacent(const string& word1, const string& word2){
    int countDifference = 0;
    for(unsigned int i = 0; i < word1.size();++i){
        if(word1[i] != word2[i]){
            ++countDifference;
            if(countDifference>1) return false;
        }
    }
    return countDifference == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
   std::unordered_set<std::string> words_visited;
   words_visited.insert(begin_word);

    queue<vector<string>> ladderQ;
    ladderQ.push({begin_word});

    while (!ladderQ.empty()) {
        vector<string> ladder = ladderQ.front();
        ladderQ.pop();

        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && words_visited.find(word) == words_visited.end()) {
                words_visited.insert(word);

                //copy vec
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                //shortest ladder
                if (word == end_word) return new_ladder; 

                ladderQ.push(new_ladder);
            }
        }
    }

    return {};

}


void print_word_ladder(const vector<string>& ladder){
    cout << "Word Ladder: ";
    for (const string& word : ladder) { cout << word << " ";}
    cout << endl;
    }



void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file) { std::cerr << "Unable to open the file " << file_name << std::endl; return; }
    string word;
    while (file >> word) { word_list.insert(word);}
    file.close();
}


void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "small.txt");
}