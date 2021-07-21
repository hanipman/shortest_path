// modified from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include <queue>
#include <map>
#include <vector>

#define INF 0x3f3f3f3f

namespace shortest_path {

	// node in the form (weight, node id)
	typedef std::pair<int, int> node;
	
	class Graph
	{
		// In a weighted graph, we need to store node weight and id
		// pair for every edge
		std::map<int, std::vector<std::pair<node, node>>> adj;

	public:
		Graph(); // Constructor

		/*
			Creates a node
			@param weight weight of the node
			@param id of the node
			@return a node type
		*/
		node createNode(int weight, int id);

		/*
			Adds an edge to the adjacency graph
			@param u node 1
			@param v node 2
		*/
		void addEdge(node u, node v);

		/*
			Allows read only access to adjacency graph
			@return constant reference to adjacency graph
		*/
		const std::vector<std::pair<node, node>>& at(int i);

		/*
			Iterator point to beginning of graph
			@return iterator of std::map.begin()
		*/
		std::map<int, std::vector<std::pair<node, node>>>::iterator begin();

		/*
			Iterator pointing to end of graph
			@return iterator of std::map.end()
		*/
		std::map<int, std::vector<std::pair<node, node>>>::iterator end();
	};

	/*
		Runs Dijkstras shortest path algorithm on adjacency graph until
		destination node is encountered. Parent map p is filled accordingly and
		used to recursively find the shortest path
		@param src integer id of the source node
		@param dest integer id of the destination node
		@param g Graph object containing adjacency graph
		@param p Parent map used to contain the closest parent of each node
		@return on success, returns node id of destination mode, -1 if not found
	*/
	int dijkstras_shortest_path(int src, int dest, Graph& g, std::vector<int>& path);

	/*
		Recursively fill vector with path from source node to destination node
		@param dest integer id of the destination node
		@param p Parent map used to contain the closest parent of each node
		@param path vector of integer ids that contains the shortest path
	*/
	void createPath(int dest, const std::map<int, int>& p, std::vector<int>& path);
}

#endif