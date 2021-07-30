#include <benchmark/benchmark.h>
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

adj_graph g;

void init(adj_graph& g)
{
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
}

static void BM_dijkstras_shortest_path(benchmark::State& state)
{
	adj_graph g;
	init(g);
	for (auto _ : state) {
		std::vector<int> path;
		dijkstras_shortest_path(nodes::A, state.range(0), g, path);
	}
}

BENCHMARK(BM_dijkstras_shortest_path)->Arg(nodes::B)->Arg(nodes::C)->Arg(nodes::D)->Arg(nodes::E)->Arg(nodes::F)->Arg(nodes::G)->Arg(nodes::H)->Arg(nodes::I);

static void BM_single_source_multi_destination(benchmark::State& state)
{
	adj_graph g;
	init(g);
	for (auto _ : state) {
		std::vector<int> path;
		std::set<int> dest{ (int)state.range(0), (int)state.range(1) };
		single_source_multi_destination(nodes::A, dest, g, path);
	}
}

BENCHMARK(BM_single_source_multi_destination)->Args({nodes::H, nodes::F})->Args({nodes::C, nodes::F});