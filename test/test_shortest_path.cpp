#define CATCH_CONFIG_MAIN
#include "catch.hpp"
// #include <catch2/catch.hpp>
#include "shortest_path.hpp"
#include <iostream>

using namespace shortest_path;

enum nodes
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I
};

TEST_CASE( "Graph members", "[Graph]" )
{
	Graph g = Graph();

	SECTION( "test node creation" )
	{
		node n = g.createNode(1, 2);
		REQUIRE(n.first == 1);
		REQUIRE(n.second == 2);
	}

	SECTION( "test edge creation" )
	{
		node a = g.createNode(1, 2);
		node b = g.createNode(3, 4);
		g.addEdge(a, b);
		REQUIRE(g.at(2).front() == std::make_pair(a, b));
	}
}

TEST_CASE( "Shortest path correctness", "[Shortest Path]") 
{
	Graph g = Graph();

	g.addEdge(g.createNode(0, nodes::A), g.createNode(4, nodes::B));
	g.addEdge(g.createNode(0, nodes::A), g.createNode(8, nodes::H));
	g.addEdge(g.createNode(4, nodes::B), g.createNode(8, nodes::C));
	g.addEdge(g.createNode(4, nodes::B), g.createNode(8, nodes::H));
	g.addEdge(g.createNode(8, nodes::C), g.createNode(7, nodes::D));
	g.addEdge(g.createNode(8, nodes::C), g.createNode(4, nodes::F));
	g.addEdge(g.createNode(7, nodes::D), g.createNode(9, nodes::E));
	g.addEdge(g.createNode(7, nodes::D), g.createNode(4, nodes::F));
	g.addEdge(g.createNode(9, nodes::E), g.createNode(4, nodes::F));
	g.addEdge(g.createNode(4, nodes::F), g.createNode(2, nodes::G));
	g.addEdge(g.createNode(2, nodes::G), g.createNode(8, nodes::H));
	g.addEdge(g.createNode(2, nodes::G), g.createNode(2, nodes::I));
	g.addEdge(g.createNode(8, nodes::H), g.createNode(2, nodes::I));

	SECTION( "Dijkstras correctness: A -> A" )
	{
		int dest_node = nodes::A;
		std::vector<int> path;

		dijkstras_shortest_path(nodes::A, dest_node, g, path);

		std::vector<int> expected{ 0 };

		REQUIRE(path == expected);
	}

	SECTION( "Dijkstras correctness: A -> E" )
	{
		int dest_node = nodes::E;
		std::vector<int> path;

		dijkstras_shortest_path(nodes::A, dest_node, g, path);

		std::vector<int> expected{ 0, 7, 6, 5, 4 };

		REQUIRE(path.size() == 5);
		REQUIRE(path == expected);
	}
	
	SECTION( "Dijkstras correctness: F -> B" )
	{
		int dest_node = nodes::B;
		std::vector<int> path;

		dijkstras_shortest_path(nodes::F, dest_node, g, path);

		std::vector<int> expected{ 5, 2, 1 };

		REQUIRE(path.size() == 3);
		REQUIRE(path == expected);
	}
}

TEST_CASE( "Shortest path with non consecutive node IDs", "[Node ID]" )
{
	Graph g = Graph();
	node heidel = g.createNode(0, 301);
	node moretti = g.createNode(2, 323);
	node costa = g.createNode(2, 322);
	node central = g.createNode(3, 304);
	node northern = g.createNode(2, 346);
	node eastern = g.createNode(3, 309);
	node ruins = g.createNode(1, 345);
	node southern = g.createNode(3, 305);
	
	g.addEdge(heidel, costa);
	g.addEdge(heidel, moretti);
	g.addEdge(costa, central);
	g.addEdge(central, northern);
	g.addEdge(moretti, northern);
	g.addEdge(moretti, eastern);
	g.addEdge(northern, eastern);
	g.addEdge(central, ruins);
	g.addEdge(ruins, southern);
	g.addEdge(eastern, southern);

	std::vector<int> path;
	
	dijkstras_shortest_path(301, 346, g, path);

	std::vector<int> expected{ 301, 323, 346 };

	REQUIRE(path.size() == 3);
	REQUIRE(path == expected);
}