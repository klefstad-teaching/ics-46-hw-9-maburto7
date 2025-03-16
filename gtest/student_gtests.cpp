#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(WordLadderTest, BasicTest) {

    EXPECT_EQ(edit_distance_within("apple", "bapple",1), true);
    EXPECT_EQ(edit_distance_within("apple", "apple",1), true);
    EXPECT_EQ(is_adjacent("apple", "apple"), true);

    set<string> word_list = {"hit", "hot", "dot", "dog", "cog"};
    vector<string> ladder = generate_word_ladder("hit", "cog", word_list);
    vector<string> expected_ladder = {"hit", "hot", "dot", "dog", "cog"};
    EXPECT_EQ(ladder, expected_ladder);
}

TEST(WordLadderTest, NoLadderTest) {
    set<string> word_list = {"hit", "hot", "dot", "dog"};
    vector<string> ladder = generate_word_ladder("hit", "cog", word_list);
    vector<string> expected_ladder = {};
    EXPECT_EQ(ladder, expected_ladder);
}




TEST(DijkstraTest, Me) {

  
  Graph G;
    EXPECT_EQ(G.numVertices, 0);


    G.numVertices = 5;
    G.resize(G.numVertices);
    G[0].push_back(Edge(0, 1, 10));
    G[1].push_back(Edge(1, 2, 20));
    G[2].push_back(Edge(2, 3, 30));
    G[3].push_back(Edge(3, 4, 40));
    

    EXPECT_EQ(G.numVertices, 5);
    EXPECT_EQ(G[0].size(), 1);
}
