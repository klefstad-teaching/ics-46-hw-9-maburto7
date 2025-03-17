#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"


TEST(WordLadderTest, DistanceDiffTest) {
    EXPECT_EQ(edit_distance_within("apple", "bapple",1), true);
    EXPECT_EQ(edit_distance_within("apple", "apple",1), true);
    EXPECT_EQ(edit_distance_within("maple", "apple",2), true);
    EXPECT_EQ(edit_distance_within("maple", "apple",1), false);
    EXPECT_EQ(edit_distance_within("mas", "masson",1), false);

}


TEST(WordLadderTest, AdjacentTest) {
    EXPECT_EQ(is_adjacent("apple", "apple"), true);
    EXPECT_EQ(is_adjacent("apple", "appme"), true);
    EXPECT_EQ(is_adjacent("pale", "apple"), false);
}


TEST(WordLadderTest, BasicTest) {
    set<string> word_list = {"hit", "hot", "dot", "dog", "cog"};
    vector<string> ladder = generate_word_ladder("hit", "cog", word_list);
    vector<string> expected_ladder = {"hit", "hot", "dot", "dog", "cog"};
    EXPECT_EQ(ladder, expected_ladder);
}


TEST(WordLadderTest, LongerLadder) {
    set<string> word_list = {"hit", "hot", "dot", "dog", "cog", "log", "lot"};
    vector<string> ladder = generate_word_ladder("hit", "log", word_list);
    vector<string> expected_ladder = {"hit", "hot", "lot", "log"};
    EXPECT_EQ(ladder, expected_ladder);
}


TEST(WordLadderTest, NoLadderTest) {
    set<string> word_list = {"hit", "hot", "dot", "dog"};
    vector<string> ladder = generate_word_ladder("hit", "cog", word_list);
    vector<string> expected_ladder = {};
    EXPECT_EQ(ladder, expected_ladder);
}

TEST(DijkstraTest, MPathTest) {
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

TEST(DijkstraTest, NoPathExistentTest) {
    Graph G;
    G.numVertices = 3;
    G.resize(G.numVertices);
    G[0].push_back(Edge(0, 1, 1));
    vector<int> previous(3, -1);
    
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 1);
    EXPECT_EQ(distances[2], INT_MAX);
}


TEST(DijkstraTest, ExtractPathTest) {
    Graph G;
    G.numVertices = 5;
    G.resize(G.numVertices);
    G[0].push_back(Edge(0, 1, 5));
    G[1].push_back(Edge(1, 2, 10));
    G[2].push_back(Edge(2, 3, 15));
    G[3].push_back(Edge(3, 4, 20));

    vector<int> previous(5, -1);
    dijkstra_shortest_path(G, 0, previous);

    vector<int> path = extract_shortest_path({}, previous, 4);
    vector<int> expected_path = {0, 1, 2, 3, 4};

    EXPECT_EQ(path, expected_path);
}

TEST(DijkstraTest, InvalidSrcTest) {
    Graph G;
    G.numVertices = 3;
    G.resize(G.numVertices);

    vector<int> previous(3, -1);
    vector<int> distances = dijkstra_shortest_path(G, -1, previous);

    EXPECT_TRUE(distances.empty());

    distances = dijkstra_shortest_path(G, 5, previous);
    EXPECT_TRUE(distances.empty());
}

TEST(DijkstraTest, OnlyOneTest) {
    Graph G;
    G.numVertices = 1;
    G.resize(G.numVertices);

    vector<int> previous(1, -1);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(extract_shortest_path(distances, previous, 0), vector<int>({0}));
}




TEST(DijkstraTest, disconnectTest) {
    Graph G;
    G.numVertices = 5;
    G.resize(G.numVertices);

    vector<int> previous(5, -1);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], INF);
    EXPECT_EQ(distances[2], INF);
    EXPECT_EQ(distances[3], INF);
    EXPECT_EQ(distances[4], INF);
}


TEST(DijkstraTest, negativeFailTest) {
    Graph G;
    G.numVertices = 3;
    G.resize(G.numVertices);
    G[0].push_back(Edge(0, 1, -5));
    G[1].push_back(Edge(1, 2, 10));

    vector<int> previous(3, -1);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    distances = dijkstra_shortest_path(G, 3, previous);
    EXPECT_TRUE(distances.empty());
}

