#include "../include/graph.h"
#include "gtest/gtest.h"

TEST(AddNodeTest, Positive)
{
	Graph G;
	EXPECT_TRUE (G.add_node(1));
	EXPECT_FALSE(G.add_node(1));
}

TEST(AddEdgeTest, Positive)
{
	Graph G;

	EXPECT_TRUE (G.add_node(1));
	EXPECT_TRUE (G.add_node(2));
	EXPECT_TRUE (G.add_edge(1, 2));
	EXPECT_FALSE (G.add_edge(1, 2));

	EXPECT_TRUE (G.add_edge(2, 3));
	EXPECT_FALSE(G.add_edge(2, 3));

	EXPECT_TRUE (G.add_edge(777, 3, 4));
	EXPECT_FALSE(G.add_edge(777, 3, 4));

	EXPECT_TRUE (G.add_edge(888, 4, 5));
	EXPECT_FALSE(G.add_edge(888, 5, 6));

	EXPECT_TRUE (G.add_edge(950, 5, 6));
	EXPECT_FALSE(G.add_edge(999, 5, 6));
}

TEST(DeleteNodeTest, Positive)
{
	Graph G;
	
	EXPECT_TRUE (G.add_node(1));
	EXPECT_TRUE (G.add_node(2));
	EXPECT_TRUE (G.add_node(3));
	EXPECT_TRUE (G.add_node(4));
	EXPECT_TRUE (G.add_node(5));
	EXPECT_TRUE (G.add_node(6));

	// This edges will be removed when node 5 is deleted
	EXPECT_TRUE (G.add_edge(1, 5));
	EXPECT_TRUE (G.add_edge(2, 5));
	EXPECT_TRUE (G.add_edge(3, 5));
	EXPECT_TRUE (G.add_edge(5, 4));
	EXPECT_TRUE (G.add_edge(5, 6));
	
	// This edge will survive
	EXPECT_TRUE (G.add_edge(4, 6));

	// Delete node 5
	EXPECT_TRUE (G.del_node(5));
	EXPECT_FALSE(G.del_node(5));

	EXPECT_TRUE(G.total_nodes() == 5);
	EXPECT_TRUE(G.total_edges() == 1);
}

TEST(DeleteEdgeTest, Positive)
{
	Graph G;

	EXPECT_TRUE (G.add_edge(1, 2));
	EXPECT_TRUE (G.add_edge(777, 2, 3));
	
	EXPECT_TRUE (G.del_edge(1, 2));
	EXPECT_FALSE(G.del_edge(1, 2));

	EXPECT_TRUE (G.del_edge(777));
	EXPECT_FALSE(G.del_edge(777));
}

TEST(PrintGraphTest, Positive)
{
	Graph G;
	G.add_node(1);
	G.add_node(2);
	G.add_edge(1, 2);

	G.print_graph();
	EXPECT_TRUE (true);
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}