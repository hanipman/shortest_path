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
	adj_graph g;

	SECTION( "test node creation" )
	{
		node n = createNode(1, 2);
		REQUIRE(n.first == 1);
		REQUIRE(n.second == 2);
	}

	SECTION( "test edge creation" )
	{
		node a = createNode(1, 2);
		node b = createNode(3, 4);
		addEdge(g, a, b);
		REQUIRE(g.at(2).front() == std::make_pair(a, b));
	}
}

TEST_CASE( "Shortest path correctness", "[Shortest Path Correctness]") 
{
	adj_graph g;

	addEdge(g, createNode(0, nodes::A), createNode(4, nodes::B));
	addEdge(g, createNode(0, nodes::A), createNode(8, nodes::H));
	addEdge(g, createNode(4, nodes::B), createNode(8, nodes::C));
	addEdge(g, createNode(4, nodes::B), createNode(8, nodes::H));
	addEdge(g, createNode(8, nodes::C), createNode(7, nodes::D));
	addEdge(g, createNode(8, nodes::C), createNode(4, nodes::F));
	addEdge(g, createNode(7, nodes::D), createNode(9, nodes::E));
	addEdge(g, createNode(7, nodes::D), createNode(4, nodes::F));
	addEdge(g, createNode(9, nodes::E), createNode(4, nodes::F));
	addEdge(g, createNode(4, nodes::F), createNode(2, nodes::G));
	addEdge(g, createNode(2, nodes::G), createNode(8, nodes::H));
	addEdge(g, createNode(2, nodes::G), createNode(2, nodes::I));
	addEdge(g, createNode(8, nodes::H), createNode(2, nodes::I));

	SECTION( "Dijkstras correctness: A -> A" )
	{
		int dest_node = nodes::A;
		std::vector<int> path;

		int res = dijkstras_shortest_path(nodes::A, dest_node, g, path);

		std::vector<int> expected{ 0 };

		REQUIRE(res == 0);
		REQUIRE(path == expected);
	}

	SECTION( "Dijkstras correctness: A -> E" )
	{
		int dest_node = nodes::E;
		std::vector<int> path;

		int res = dijkstras_shortest_path(nodes::A, dest_node, g, path);

		std::vector<int> expected{ 0, 7, 6, 5, 4 };

		REQUIRE(res == 23);
		REQUIRE(path == expected);
	}
	
	SECTION( "Dijkstras correctness: F -> B" )
	{
		int dest_node = nodes::B;
		std::vector<int> path;

		int res = dijkstras_shortest_path(nodes::F, dest_node, g, path);

		std::vector<int> expected{ 5, 2, 1 };

		REQUIRE(res == 12);
		REQUIRE(path == expected);
	}
}

TEST_CASE( "Dijkstras algorithm failure", "[Shortest Path Failure]" )
{
	adj_graph g;

	std::vector<int> path;

	int res = dijkstras_shortest_path(nodes::A, nodes::B, g, path);

	REQUIRE(res == -1);
	REQUIRE(path.size() == 0);

	addEdge(g, createNode(0, nodes::A), createNode(4, nodes::B));
	addEdge(g, createNode(0, nodes::A), createNode(8, nodes::H));
	addEdge(g, createNode(4, nodes::B), createNode(8, nodes::C));
	addEdge(g, createNode(4, nodes::B), createNode(8, nodes::H));
	addEdge(g, createNode(8, nodes::C), createNode(7, nodes::D));
	addEdge(g, createNode(8, nodes::C), createNode(4, nodes::F));
	addEdge(g, createNode(7, nodes::D), createNode(9, nodes::E));
	addEdge(g, createNode(7, nodes::D), createNode(4, nodes::F));
	addEdge(g, createNode(9, nodes::E), createNode(4, nodes::F));
	addEdge(g, createNode(4, nodes::F), createNode(2, nodes::G));
	addEdge(g, createNode(2, nodes::G), createNode(8, nodes::H));
	addEdge(g, createNode(2, nodes::G), createNode(2, nodes::I));
	addEdge(g, createNode(8, nodes::H), createNode(2, nodes::I));

	res = dijkstras_shortest_path(25, nodes::B, g, path);
	
	REQUIRE(res == -1);
	REQUIRE(path.size() == 0);
}

TEST_CASE( "Shortest path with non consecutive node IDs", "[Node ID]" )
{
	adj_graph g;
	node heidel = createNode(0, 301);
	node moretti = createNode(2, 323);
	node costa = createNode(2, 322);
	node central = createNode(3, 304);
	node northern = createNode(2, 346);
	node eastern = createNode(3, 309);
	node ruins = createNode(1, 345);
	node southern = createNode(3, 305);
	
	addEdge(g, heidel, costa);
	addEdge(g, heidel, moretti);
	addEdge(g, costa, central);
	addEdge(g, central, northern);
	addEdge(g, moretti, northern);
	addEdge(g, moretti, eastern);
	addEdge(g, northern, eastern);
	addEdge(g, central, ruins);
	addEdge(g, ruins, southern);
	addEdge(g, eastern, southern);

	std::vector<int> path;
	
	int res = dijkstras_shortest_path(301, 346, g, path);

	std::vector<int> expected{ 301, 323, 346 };

	REQUIRE(res == 4);
	REQUIRE(path == expected);
}

TEST_CASE( "Single source multi destination shortest path correctness", "[SSMD]" )
{
	adj_graph g;

	addEdge(g, createNode(0, nodes::A), createNode(4, nodes::B));
	addEdge(g, createNode(0, nodes::A), createNode(8, nodes::H));
	addEdge(g, createNode(4, nodes::B), createNode(8, nodes::C));
	addEdge(g, createNode(4, nodes::B), createNode(8, nodes::H));
	addEdge(g, createNode(8, nodes::C), createNode(7, nodes::D));
	addEdge(g, createNode(8, nodes::C), createNode(4, nodes::F));
	addEdge(g, createNode(7, nodes::D), createNode(9, nodes::E));
	addEdge(g, createNode(7, nodes::D), createNode(4, nodes::F));
	addEdge(g, createNode(9, nodes::E), createNode(4, nodes::F));
	addEdge(g, createNode(4, nodes::F), createNode(2, nodes::G));
	addEdge(g, createNode(2, nodes::G), createNode(8, nodes::H));
	addEdge(g, createNode(2, nodes::G), createNode(2, nodes::I));
	addEdge(g, createNode(8, nodes::H), createNode(2, nodes::I));

	std::vector<int> path;

	std::set<int> dest{ nodes::D, nodes::G };

	std::vector<int> expected{ 0, 3, 5, 6, 7 };
	
	int res = single_source_multi_destination(nodes::A, dest, g, path);

	REQUIRE(res == 21);
	REQUIRE(path == expected);
}