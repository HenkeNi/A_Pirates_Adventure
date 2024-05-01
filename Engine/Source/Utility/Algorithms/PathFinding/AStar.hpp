#pragma once
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>

namespace Hi_Engine::Algorithms::AStar
{
	struct AStarNode
	{
		AStarNode(int x, int y, int index, int heuristics)
			: X{ x }, Y{ y }, G{ 0 }, Parent{ nullptr }, IsVisited{ false }, Index{ index }, H{ heuristics }
		{
		}

		int G; // Cost from start node
		int H; // Heuristic cost to goal node
		
		int Index;

		// Coordinates
		int X;
		int Y;

		AStarNode* Parent;
		bool IsVisited;

		inline int F() const { return G + H; }
	};

	struct CompareAStarNode
	{
		bool operator() (const AStarNode* lhs, const AStarNode* rhs)
		{
			return lhs->F() > rhs->F();
		}
	};

	//int CalculateManhattanDistance(int nodeX, int nodeY, int goalX, int goalY)
	//{
	//	return std::abs(nodeX - goalX) + std::abs(nodeY - goalY);
	//}

	inline int CalculateManhattanDistance(int x, int y, int goalX, int goalY, int numCols) {
		return std::abs(x % numCols - goalX) + std::abs(y / numCols - goalY);
	}

	inline bool IsValidPosition(int x, int y, int rows, int cols)
	{
		return (x >= 0 && x < cols) && (y >= 0 && y < rows);
	}
	
	inline std::pair<int, int> CalculateCoordinates(int index, int gridWidth)
	{
		int x = index % gridWidth;
		int y = index / gridWidth;

		return { x, y };
	}


	inline std::vector<int> GeneratePath(const std::vector<int>& grid, int gridWidth, int start, int goal)
	{
		if (start == goal)
			return {};

		int cols = gridWidth;
		int rows = grid.size() / gridWidth;

		std::vector<AStarNode> nodes;
		nodes.reserve(grid.size());

		const auto& [goalX, goalY] = CalculateCoordinates(goal, gridWidth);

		for (int i = 0; i < grid.size(); ++i)
		{
			const auto& [nodeX, nodeY] = CalculateCoordinates(i, gridWidth);

			int heuristics = CalculateManhattanDistance(nodeX, nodeY, goalX, goalY, cols);
			nodes.emplace_back(nodeX, nodeY, i, heuristics);
		}

		auto* startNode = &nodes[start];
		auto* goalNode = &nodes[goal];
		
		startNode->G = 0;
		startNode->H = CalculateManhattanDistance(startNode->X, startNode->Y, goalNode->X, goalNode->Y, cols);

		std::priority_queue<AStarNode*, std::vector<AStarNode*>, CompareAStarNode> openNodes;
		openNodes.push(startNode);
		
		while (!openNodes.empty())
		{
			auto* currentNode = openNodes.top();
			openNodes.pop();

			currentNode->IsVisited = true;
				
			if (currentNode == goalNode)
			{
				std::vector<int> path;
				while (currentNode != nullptr)
				{
					path.emplace_back(currentNode->Index);
					currentNode = currentNode->Parent;
				}

				std::reverse(path.begin(), path.end());
				return path;
			}

			// explore neighbors
			static const int dx[] = { 1, -1, 0, 0 };
			static const int dy[] = { 0, 0, 1, -1 };

			for (int i = 0; i < 4; ++i)
			{
				int nx = currentNode->X + dx[i];
				int ny = currentNode->Y + dy[i];

				if (IsValidPosition(nx, ny, rows, cols) && grid[ny * cols + nx] != 1)
				{
					int neighborIndex = ny * cols + nx;
					AStarNode* neighbor = &nodes[neighborIndex];

					if (!neighbor->IsVisited)
					{
						int tentativeG = currentNode->G + 1;

						if (tentativeG < neighbor->G || !neighbor->Parent)
						{
							neighbor->G = tentativeG;
							neighbor->H = CalculateManhattanDistance(nx, ny, goalNode->X, goalNode->Y, cols);
							neighbor->Parent = currentNode;
							openNodes.push(neighbor);
						}
					}
				}
			}

		}

		return {};
	}
}