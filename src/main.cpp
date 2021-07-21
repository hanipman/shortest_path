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

	std::vector<int> path;
	dijkstras_shortest_path(nodes::A, nodes::B, g, path);
	return 0;
}