#pragma once
#include <vector>
#include "Utility/Math/Vectors/Vector.hpp"

namespace Hi_Engine::Algorithms
{
	namespace CU = CommonUtilities;

	/* A-Star Algorithm */
	// f(x) = g(x) + h(x)

	// where g(x) describes the true cost from the start node to the current node x, 
	// and h(x) is a heuristic function that estimates the cost in moving from x to the nearest goal node
	// (nearest, according to the metric).
	// a graph is a set of locations, connected via edges

	enum class eNodeStatus
	{
		Unvisited, Open, Closed
	};

	struct Node
	{
		CU::Vector2<unsigned> m_coordinates; 
		CU::Vector2<unsigned> m_parentCoordinates;

		/*int m_parentIndex;
		int m_g;
		int m_f;*/



		bool m_isTraversable;
		bool m_isVisited;
		float m_distanceToGoal;
		float m_x;
		float m_y;


		

		Node* m_parent = nullptr;
		int m_g = INT16_MAX; // check if correct with intmax..... shortest path to this node?! or how many step to get to this node -> can be changed/updated?
		eNodeStatus m_status = eNodeStatus::Unvisited;
		int m_h; // estimated distance to target/goal -> remains the same
		int m_f; // Sum of g and h 
	};


	struct MapData
	{
		int m_mapWidth; // or area width
		int m_mapHeight; // or area height
	};

	int CalculateManhattanDistance()	
	{
		return -1;
	}

	// rename someNodes?? someVertices? aGraph?? take in a map??
	template <typename T>
	std::vector<unsigned> AStar(const std::vector<T>& someNodes, unsigned aStartIndex, unsigned anEndIndex)
	{
		// 
		std::vector<Node> nodes(someNodes.size());

		auto startNode = nodes[aStartIndex];
		startNode.m_status = eNodeStatus::Open;
		startNode.m_g = 0;

		std::vector<Node> openNodes;
		openNodes.push_back(startNode);

		while (!openNodes.empty())
		{
			// get node with lowest f 

			// if that node is goal => return

			// mark n as closed
		}




		// Pick the node with lowest f and moves it from open to closed (we won't look at it again at this point)


	}

#pragma region Helper_Functions

#pragma endregion Helper_Functions
}