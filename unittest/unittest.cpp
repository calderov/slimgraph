#include <string>

#include "../include/digraph.h"
#include "../include/graph_algorithms.h"

#include "gtest/gtest.h"

TEST(AddNodeTest, Positive)
{
	DiGraph G;
	EXPECT_TRUE (G.add_node(1));
	EXPECT_FALSE(G.add_node(1));
}

TEST(AddEdgeTest, Positive)
{
	DiGraph G;

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
	DiGraph G;
	
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
	DiGraph G;

	EXPECT_TRUE (G.add_edge(1, 2));
	EXPECT_TRUE (G.add_edge(777, 2, 3));
	
	EXPECT_TRUE (G.del_edge(1, 2));
	EXPECT_FALSE(G.del_edge(1, 2));

	EXPECT_TRUE (G.del_edge(777));
	EXPECT_FALSE(G.del_edge(777));
}

TEST(QueryNodeDegrees, Positive)
{
	DiGraph G;
	
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
	DiGraph G;
	G.add_node(1);
	G.add_node(2);
	G.add_edge(1, 2);

	G.print_graph();
	EXPECT_TRUE (true);
}

TEST(NodeProperties, Positive)
{
	DiGraph G;

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

	// Setting a property value on an unexistant node should fail
	EXPECT_FALSE(G.set_node_property(999, "Name", expectedName));
	EXPECT_FALSE(G.set_node_property(999, "Name", "FooBar"));
	EXPECT_FALSE(G.set_node_property(999, "Age", 100));

	// Getting a property value from an unexistant node should result in an error
	EXPECT_TRUE(G.get_node_property(999, "Name").type == ERROR);
}

TEST(EdgeProperties, Positive)
{
	DiGraph G;

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

	// Setting a property value on an unexistant edge should fail
	EXPECT_FALSE(G.set_edge_property(3, 4, "Units", expectedName));
	EXPECT_FALSE(G.set_edge_property(3, 4, "Units", "FooBar"));
	EXPECT_FALSE(G.set_edge_property(3, 4, "Lenght", 100));

	// Getting a property value from an unexistant edge should result in an error
	EXPECT_TRUE(G.get_edge_property(5, 6, "Units").type == ERROR);

	// Querying for the EDGEID of an unexistenant edge should return BAD_EDGEID
	EXPECT_TRUE(G.get_edge_id(5, 6) == BAD_EDGEID);
}

TEST(EdgePropertiesWithKnownEdgeId, Positive)
{
	DiGraph G;

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

	// Setting a property value on an unexistant edge should fail
	EXPECT_FALSE(G.set_edge_property(999, "Units", expectedName));
	EXPECT_FALSE(G.set_edge_property(999, "Units", "FooBar"));
	EXPECT_FALSE(G.set_edge_property(999, "Lenght", 100));

	// Getting a property value from an unexistant edge should result in an error
	EXPECT_TRUE(G.get_edge_property(999, "Units").type == ERROR);
}

TEST(NodePropertyDeletion, Positive)
{
	DiGraph G;

	G.add_node(1);
	G.add_node(2);
	G.add_node(3);

	G.add_node_property("Prop1", DOUBLE);
	G.set_node_property(1, "Prop1", 1.0);
	G.set_node_property(2, "Prop1", 2.0);
	G.set_node_property(3, "Prop1", 3.0);

	G.add_node_property("Prop2", DOUBLE);
	G.set_node_property(1, "Prop2", 1.0);
	G.set_node_property(2, "Prop2", 2.0);
	G.set_node_property(3, "Prop2", 3.0);

	G.add_node_property("Prop3", DOUBLE);
	G.set_node_property(1, "Prop3", 1.0);
	G.set_node_property(2, "Prop3", 2.0);
	G.set_node_property(3, "Prop3", 3.0);

	// Delete node, expecting its properties are cleared
	EXPECT_TRUE(G.del_node(1));
	EXPECT_TRUE(G.get_node_property(1, "Prop1").type == ERROR);
	EXPECT_TRUE(G.get_node_property(1, "Prop2").type == ERROR);
	EXPECT_TRUE(G.get_node_property(1, "Prop3").type == ERROR);

	// Check property deletion
	EXPECT_TRUE(G.total_node_properties() == 3);
	EXPECT_TRUE(G.del_node_property("Prop1"));
	EXPECT_TRUE(G.total_node_properties() == 2);
	EXPECT_TRUE(G.del_all_node_properties());
	EXPECT_TRUE(G.total_node_properties() == 0);
}

TEST(EdgePropertyDeletion, Positive)
{
	DiGraph G;

	G.add_edge(1, 2);
	G.add_edge(2, 3);
	G.add_edge(3, 1);

	G.add_edge_property("Prop1", DOUBLE);
	G.set_edge_property(1, 2, "Prop1", 1.0);
	G.set_edge_property(2, 3, "Prop1", 2.0);
	G.set_edge_property(3, 1, "Prop1", 3.0);

	G.add_edge_property("Prop2", DOUBLE);
	G.set_edge_property(1, 2, "Prop2", 1.0);
	G.set_edge_property(2, 3, "Prop2", 2.0);
	G.set_edge_property(3, 1, "Prop2", 3.0);

	G.add_edge_property("Prop3", DOUBLE);
	G.set_edge_property(1, 2, "Prop3", 1.0);
	G.set_edge_property(2, 3, "Prop3", 2.0);
	G.set_edge_property(3, 1, "Prop3", 3.0);

	// Delete edge, expecting its properties are cleared
	EXPECT_TRUE(G.del_edge(1, 2));
	EXPECT_TRUE(G.get_edge_property(1, 2, "Prop1").type == ERROR);
	EXPECT_TRUE(G.get_edge_property(1, 2, "Prop2").type == ERROR);
	EXPECT_TRUE(G.get_edge_property(1, 2, "Prop3").type == ERROR);

	// Check property deletion
	EXPECT_TRUE(G.total_edge_properties() == 3);
	EXPECT_TRUE(G.del_edge_property("Prop1"));
	EXPECT_TRUE(G.total_edge_properties() == 2);
	EXPECT_TRUE(G.del_all_edge_properties());
	EXPECT_TRUE(G.total_edge_properties() == 0);
}

TEST(PrintProperties, Positive)
{
	DiGraph G;

	G.add_node(1);
	G.add_node(2);
	G.add_edge(1, 2);

	G.add_node_property("NodeStringProp", STRING);
	G.add_node_property("NodeDoubleProp", DOUBLE);
	G.print_node_properties();

	G.add_edge_property("EdgeStringProp", STRING);
	G.add_edge_property("EdgeDoubleProp", DOUBLE);
	G.print_edge_properties();


	G.set_node_property(1, "NodeStringProp", "FooBar");
	G.set_node_property(1, "NodeDoubleProp", 31415925);
	G.print_node_properties(1);

	G.set_edge_property(1, 2, "EdgeStringProp", "FooBar");
	G.set_edge_property(1, 2, "EdgeDoubleProp", 31415925);
	G.print_edge_properties(1, 2);

	EXPECT_TRUE(true);
}

TEST(NumericalPropertyToString, Positive)
{
	DiGraph G;

	G.add_node(0);
	G.add_node_property("Property0", DOUBLE);
	G.set_node_property(0, "Property0", 31415925);

	PROPERTY_RESULT propertyResult =  G.get_node_property(0, "Property0");

	std::string resultString = propertyResult.to_string();
	std::string expectedString = std::to_string(static_cast<double>(31415925.0));

	EXPECT_TRUE(resultString.compare(expectedString) == 0);
}

TEST(StringPropertyToString, Positive)
{
	DiGraph G;

	G.add_node(0);
	G.add_node_property("Property0", STRING);
	G.set_node_property(0, "Property0", "Example value");

	PROPERTY_RESULT propertyResult =  G.get_node_property(0, "Property0");

	std::string resultString = propertyResult.to_string();
	std::string expectedString = "Example value";

	EXPECT_TRUE(resultString.compare(expectedString) == 0);
}

TEST(ErrorPropertyToString, Positive)
{
	DiGraph G;

	G.add_node(0);

	// Get non existant property from graph
	PROPERTY_RESULT propertyResult =  G.get_node_property(0, "Property0");
	EXPECT_TRUE(propertyResult.type == ERROR);

	std::string resultString = propertyResult.to_string();
	std::string expectedString = "Error: Invalid value!";

	EXPECT_TRUE(resultString.compare(expectedString) == 0);
}

TEST(DfsWalk, Positive)
{
	DiGraph G;

	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.add_edge(0, 3);
	G.add_edge(0, 4);
	G.add_edge(0, 5);
	G.add_edge(0, 6);
	G.add_edge(0, 7);
	G.add_edge(0, 8);

	G.add_edge(1, 9);
	G.add_edge(1,10);
	G.add_edge(1,11);

	G.add_edge(11,12);
	G.add_edge(11,13);

	bool succeed = true;
	vector<NODEID> dfs = GraphAlgorithms::dfs(&G, 0);
	vector<NODEID> expectedDfs = {0, 8, 7, 6, 5, 4, 3, 2, 1, 11, 13, 12, 10, 9};

	EXPECT_TRUE(dfs.size() == expectedDfs.size());
	for (int i = 0; i < dfs.size(); i++)
		EXPECT_TRUE(dfs[i] == expectedDfs[i]);
}

TEST(BfsWalk, Positive)
{
	DiGraph G;

	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.add_edge(0, 3);
	G.add_edge(0, 4);
	G.add_edge(0, 5);
	G.add_edge(0, 6);
	G.add_edge(0, 7);
	G.add_edge(0, 8);

	G.add_edge(1, 9);
	G.add_edge(1,10);
	G.add_edge(1,11);

	G.add_edge(11,12);
	G.add_edge(11,13);

	bool succeed = true;
	vector<NODEID> bfs = GraphAlgorithms::bfs(&G, 0);
	vector<NODEID> expectedBfs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

	EXPECT_TRUE(bfs.size() == expectedBfs.size());
	for (int i = 0; i < bfs.size(); i++)
		EXPECT_TRUE(bfs[i] == expectedBfs[i]);
}

TEST(GettingExistingEdgeFromGraphSucceeds, Positive)
{
	DiGraph G;

	G.add_node(0);
	G.add_node(1);
	
	// Add edge with id 0, from node 0 to node 1
	G.add_edge(0, 0, 1);

	// Try to get edge with id 0
	EDGE e1 = G.get_edge(0);
	EXPECT_TRUE(e1.edgeId == 0);
	EXPECT_TRUE(e1.from == 0);
	EXPECT_TRUE(e1.to == 1);
	
	// Try to get edge from node 0 to node 1
	EDGE e2 = G.get_edge(0, 1);
	EXPECT_TRUE(e2.edgeId == 0);
	EXPECT_TRUE(e1.from == 0);
	EXPECT_TRUE(e1.to == 1);
}

TEST(GettingUnexistingNodeFromGraphReturnsBadNode, Positive)
{
	DiGraph G;

	G.add_node(0);
	NODE n = G.get_node(1);
	EXPECT_TRUE(n.nodeId == BAD_NODEID);
}

TEST(GettingUnexistingEdgeFromGraphReturnsBadEdge, Positive)
{
	DiGraph G;

	G.add_node(0);
	G.add_node(1);

	// Try to get unexistant edge with id 1
	EDGE e1 = G.get_edge(1);
	EXPECT_TRUE(e1.edgeId == BAD_EDGEID);
	
	// Try to get unexistant edge from node 0 to node 1
	EDGE e2 = G.get_edge(0, 1);
	EXPECT_TRUE(e2.edgeId == BAD_EDGEID);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}