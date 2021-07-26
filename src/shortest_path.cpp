#include "shortest_path.hpp"
#include <algorithm>
#include <iostream>
#include <exception>

shortest_path::Graph::Graph() {}

shortest_path::node shortest_path::Graph::createNode(int weight, int id)
{
	return std::make_pair(weight, id);
}

void shortest_path::Graph::addEdge(shortest_path::node u, shortest_path::node v)
{
	adj[u.second].push_back(std::make_pair(u, v));
	adj[v.second].push_back(std::make_pair(v, u));
}

const std::vector<std::pair<shortest_path::node, shortest_path::node>>& shortest_path::Graph::at(int i)
{
	return adj.at(i);
}

bool shortest_path::Graph::empty()
{
	return adj.empty();
}

std::map<int, std::vector<std::pair<shortest_path::node, shortest_path::node>>>::iterator shortest_path::Graph::begin() {
	return adj.begin();
}

std::map<int, std::vector<std::pair<shortest_path::node, shortest_path::node>>>::iterator shortest_path::Graph::end() {
	return adj.end();
}

// Prints shortest path from src to dest
int shortest_path::dijkstras_shortest_path(int src, int dest, shortest_path::Graph& g, std::vector<int>& path)
{
	if (g.empty())
	{
		return -1;
	}

	try
	{
		g.at(src);
	}
	catch (std::exception& e)
	{
		return -1;
	}

	if (src == dest)
	{
		path.push_back(src);
		return 0;
	}
	// Vector to track vertexes to be inspected
	std::priority_queue<node, std::vector<node>, std::greater<node>> pq;

	// Map to track visited nodes and their relaxed weights
	std::map<int, std::pair<int, bool>> node_map;

	std::map<int, int> p;

	// start with source node assuming weight 0
	pq.push(std::make_pair(0, src));
	node_map[src].first = 0;
	p[src] = -1;

	while (!pq.empty())
	{
		int u = pq.top().second;
		if (!node_map.contains(u))
			node_map[u] = std::make_pair(INF, false);
		node_map[u].second = true;

		pq.pop();

		// destination found exit condition
		if (u == dest)
		{
			createPath(dest, p, path);
			return node_map[u].first;
		}

		// examine cost of each node
		for (auto const& i : g.at(u))
		{
			int v = i.second.second;
			int weight = i.second.first;
			
			if (!node_map.contains(v))
				node_map[v] = std::make_pair(INF, false);

			if (!p.contains(v))
				p[v] = -1;

			// relax if node cost is less than current
			if (node_map[v].second == false && node_map[v].first > node_map[u].first + weight)
			{
				p[v] = u;
				node_map[v].first = node_map[u].first + weight;
				pq.push(std::make_pair(node_map[v].first, v));
			}
		}
	}
	return -1;
}


void shortest_path::createPath(int dest, const std::map<int, int>& p, std::vector<int>& path)
{
	if (p.at(dest) == -1)
	{
		path.push_back(dest);
		return;
	}
	createPath(p.at(dest), p, path);
	path.push_back(dest);
}

int shortest_path::single_source_multi_destination(int src_node, std::set<int> dest_list, shortest_path::Graph& g, std::vector<int>& path)
{
	if (g.empty())
	{
		return -1;
	}

	int src = src_node;
	bool dest_found = false;

	while (!dest_list.empty())
	{
		std::vector<int> temp_path;
		size_t d_size = dest_list.size();

		// src is one of the destinations, skip
		if (dest_list.contains(src))
		{
			path.push_back(src);
			dest_list.erase(src);
			continue;
		}

		// Vector to track vertexes to be inspected
		std::priority_queue<node, std::vector<node>, std::greater<node>> pq;

		// Map to track visited nodes and their relaxed weights
		std::map<int, std::pair<int, bool>> node_map;

		std::map<int, int> p;

		// start with source node assuming weight 0
		pq.push(std::make_pair(0, src));
		node_map[src].first = 0;
		p[src] = -1;
		
		while (!pq.empty())
		{
			int u = pq.top().second;
			// std::cout << "Examining " << u << std::endl;
			if (!node_map.contains(u))
				node_map[u] = std::make_pair(INF, false);
			node_map[u].second = true;

			pq.pop();

			// destination found, break loop to examine next node
			// std::cout << "Checking if dest_list contains " << u << ": ";
			if (dest_list.contains(u))
			{
				// std::cout << "true\n";
				createPath(u, p, temp_path);
				path.reserve(path.size() + temp_path.size());
				path.insert(path.end(), temp_path.begin(), temp_path.end());
				dest_list.erase(u);
				src = u;
				dest_found = true;
				break;
			}
			// std::cout << "false\n";

			// examine cost of each node
			// std::cout << "Relaxing edges...\n";
			for (auto const& i : g.at(u))
			{
				int v = i.second.second;
				int weight = i.second.first;
				
				if (!node_map.contains(v))
					node_map[v] = std::make_pair(INF, false);

				if (!p.contains(v))
					p[v] = -1;

				// relax if node cost is less than current
				if (node_map[v].second == false && node_map[v].first > node_map[u].first + weight)
				{
					p[v] = u;
					node_map[v].first = node_map[u].first + weight;
					pq.push(std::make_pair(node_map[v].first, v));
				}
			}
		}
		// no destination found after examining entire graph
		if (d_size == dest_list.size())
			break;
	}

	// destinations were found, check path for duplicates
	if (dest_found)
	{
		std::sort(path.begin(), path.end());
		path.erase(std::unique(path.begin(), path.end()), path.end());
	}
	return -1;
}