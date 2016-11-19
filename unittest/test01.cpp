#include <string>

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

TEST(QueryNodeDegrees, Positive)
{
	Graph G;
	
	EXPECT_TRUE (G.add_node(1));
	EXPECT_TRUE (G.add_node(2));
	EXPECT_TRUE (G.add_node(3));
	EXPECT_TRUE (G.add_node(4));
	EXPECT_TRUE (G.add_node(5));
	EXPECT_TRUE (G.add_node(6));

	EXPECT_TRUE (G.add_edge(1, 5));
	EXPECT_TRUE (G.add_edge(2, 5));
	EXPECT_TRUE (G.add_edge(3, 5));
	EXPECT_TRUE (G.add_edge(4, 6));
	EXPECT_TRUE (G.add_edge(5, 4));
	EXPECT_TRUE (G.add_edge(5, 6));

	EXPECT_TRUE(G.total_nodes() == 6);
	EXPECT_TRUE(G.total_edges() == 6);
	
	EXPECT_TRUE(G.node_degree(5) == 5);
	EXPECT_TRUE(G.node_indegree(5) == 3);
	EXPECT_TRUE(G.node_outdegree(5) == 2);
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

TEST(NodeProperties, Positive)
{
	Graph G;

	G.add_node(1);

	// Test string node properties
	string expectedName = "John";
	EXPECT_TRUE(G.add_node_property("Name", STRING));
	EXPECT_TRUE(G.set_node_property(1, "Name", expectedName));
	EXPECT_TRUE(G.get_node_property(1, "Name").type == STRING);
	EXPECT_TRUE(G.get_node_property(1, "Name").value.valueStr.compare(expectedName) == 0);
	
	// Test numeric node properties
	EXPECT_TRUE(G.add_node_property("Age", DOUBLE));
	EXPECT_TRUE(G.set_node_property(1, "Age",  27));
	EXPECT_TRUE(G.get_node_property(1, "Age").type == DOUBLE);
	EXPECT_TRUE(G.get_node_property(1, "Age").value.valueNum == 27);

	// Overwriting properties should succeed
	EXPECT_TRUE(G.set_node_property(1, "Name", "Joe"));
	EXPECT_TRUE(G.set_node_property(1, "Age",  28));

	// If a property already exists, then add_node_property should fail
	EXPECT_FALSE(G.add_node_property("Age", DOUBLE));
	
	// If a property does not exists, then set_node_property should fail
	EXPECT_FALSE(G.set_node_property(1, "LastName", "Doe"));
	EXPECT_FALSE(G.set_node_property(1, "Income", 1000000));

	// Setting STRING values to DOUBLE properties should fail
	EXPECT_FALSE(G.set_node_property(1, "Age", "FooBar"));

	// Setting DOUBLE values to STRING properties should fail
	EXPECT_FALSE(G.set_node_property(1, "Name", 31415));
}

TEST(EdgeProperties, Positive)
{
	Graph G;

	G.add_edge(1, 2);

	// Test string edge properties
	string expectedName = "Miles";
	EXPECT_TRUE(G.add_edge_property("Units", STRING));
	EXPECT_TRUE(G.set_edge_property(1, 2, "Units", expectedName));
	EXPECT_TRUE(G.get_edge_property(1, 2, "Units").type == STRING);
	EXPECT_TRUE(G.get_edge_property(1, 2, "Units").value.valueStr.compare(expectedName) == 0);
	
	// Test numeric edge properties
	EXPECT_TRUE(G.add_edge_property("Lenght", DOUBLE));
	EXPECT_TRUE(G.set_edge_property(1, 2, "Lenght",  20));
	EXPECT_TRUE(G.get_edge_property(1, 2, "Lenght").type == DOUBLE);
	EXPECT_TRUE(G.get_edge_property(1, 2, "Lenght").value.valueNum == 20);

	// Overwriting properties should succeed
	string meters = "meters";
	EXPECT_TRUE(G.set_edge_property(1, 2, "Units", meters));
	EXPECT_TRUE(G.set_edge_property(1, 2, "Units", "Kilometers"));
	EXPECT_TRUE(G.set_edge_property(1, 2, "Lenght",  32.18));

	// If a property already exists, then add_edge_property should fail
	EXPECT_FALSE(G.add_edge_property("Lenght", DOUBLE));
	
	// If a property does not exists, then set_edge_property should fail
	EXPECT_FALSE(G.set_edge_property(1, 2, "Toll-Currency", "USD"));
	EXPECT_FALSE(G.set_edge_property(1, 2, "Toll-Cost", 4.5));

	// Setting STRING values to DOUBLE properties should fail
	EXPECT_FALSE(G.set_edge_property(1, 2, "Lenght", "FooBar"));

	// Setting DOUBLE values to STRING properties should fail
	EXPECT_FALSE(G.set_edge_property(1, 2, "Units", 31415));
}

TEST(EdgePropertiesWithKnownEdgeId, Positive)
{
	Graph G;

	EDGEID edgeId = 777;
	G.add_edge(edgeId, 1, 2);

	// Test string edge properties
	string expectedName = "Miles";
	EXPECT_TRUE(G.add_edge_property("Units", STRING));
	EXPECT_TRUE(G.set_edge_property(edgeId, "Units", expectedName));
	EXPECT_TRUE(G.get_edge_property(edgeId, "Units").type == STRING);
	EXPECT_TRUE(G.get_edge_property(edgeId, "Units").value.valueStr.compare(expectedName) == 0);
	
	// Test numeric edge properties
	EXPECT_TRUE(G.add_edge_property("Lenght", DOUBLE));
	EXPECT_TRUE(G.set_edge_property(edgeId, "Lenght",  20));
	EXPECT_TRUE(G.get_edge_property(edgeId, "Lenght").type == DOUBLE);
	EXPECT_TRUE(G.get_edge_property(edgeId, "Lenght").value.valueNum == 20);

	// Overwriting properties should succeed
	string meters = "meters";
	EXPECT_TRUE(G.set_edge_property(edgeId, "Units", meters));
	EXPECT_TRUE(G.set_edge_property(edgeId, "Units", "Kilometers"));
	EXPECT_TRUE(G.set_edge_property(edgeId, "Lenght",  32.18));

	// If a property already exists, then add_edge_property should fail
	EXPECT_FALSE(G.add_edge_property("Lenght", DOUBLE));
	
	// If a property does not exists, then set_edge_property should fail
	EXPECT_FALSE(G.set_edge_property(edgeId, "Toll-Currency", "USD"));
	EXPECT_FALSE(G.set_edge_property(edgeId, "Toll-Cost", 4.5));

	// Setting STRING values to DOUBLE properties should fail
	EXPECT_FALSE(G.set_edge_property(edgeId, "Lenght", "FooBar"));

	// Setting DOUBLE values to STRING properties should fail
	EXPECT_FALSE(G.set_edge_property(edgeId, "Units", 31415));
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}