#include "ladder.h"

void error(string word1, string word2, string msg){
    cout<<msg<<" with words: "<<word1<<" "<<word2<<endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if(str1==str2) return true;
    int s1 = str1.size(); int s2 = str2.size();
    if(abs(s1-s2) > d) return false;
    int count = 0, i = 0, j = 0;
    while(i < s1 && j < s2){
        if(str1[i] != str2[j]){ //check if char not the same
            if(s1 > s2) ++i; //if bigger length than remove
            else if(s1 < s2) ++j; //remove the other str
            else{++i;++j;} //go to next char
            ++count;
        } else{++i;++j;}
    }
    count += abs(s1 - i);
    count += abs(s2 - j);
    return count == d;
    }

bool is_adjacent(const string& word1, const string& word2){
    if(word1==word2) return true;
    int s1 = word1.length(); int s2 = word2.length();
    if(abs(s1-s2) > 1) return false;
    int count = 0, i = 0, j = 0;
    while(i < s1 && j < s2){
        if(word1[i] != word2[j]){
            if(s1 > s2) ++i;
            else if(s1 < s2) ++j;
            else{++i;++j;}
            ++count;
        } else{++i;++j;}
    }
    count += abs(s1 - i);
    count += abs(s2 - j);
    return count == 1;
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
    if(ladder.empty()){cout<< "No word ladder found.\n"; return;}
    cout << "Word ladder found: ";
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
    //load_words(word_list, "small.txt");
}