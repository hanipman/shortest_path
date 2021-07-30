#include "shortest_path.hpp"

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

int main()
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
	dijkstras_shortest_path(nodes::A, nodes::B, g, path);
	return 0;
}