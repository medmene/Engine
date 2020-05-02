#pragma once
#include "Core.h"
#include "Vector2.h"


struct PassabilityArea;

class PathFinder
{
private:
	static const int dir = 8; // number of possible directions to go at any position
	// if dir==4
	//static int dx[dir]={1, 0, -1, 0};
	//static int dy[dir]={0, 1, 0, -1};
	// if dir==8
	int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	class node
	{
		// current position
		int xPos;
		int yPos;
		// total distance already travelled to reach the node
		int level;
		// priority=level+remaining distance estimate
		int priority;  // smaller: higher priority

	public:
		node(int xp, int yp, int d, int p);

		int getxPos() const { return xPos; }
		int getyPos() const { return yPos; }
		int getLevel() const { return level; }
		int getPriority() const { return priority; }

		void updatePriority(const int & xDest, const int & yDest);

		// give better priority to going strait instead of diagonally
		void nextLevel(const int & i); // i: direction

		// Estimation function for the remaining distance to the goal.
		const int & estimate(const int & xDest, const int & yDest) const;
	};

	// Determine priority (in the priority queue)
	bool friend operator<(const node & a, const node & b)
	{
		return a.getPriority() > b.getPriority();
	}
public:
	// ------------------------------------------------------------------------------------- //

	PathFinder();
	
	bool InProgress() { return m_working; }
	void GetResult(vector<Vector2> &path);
	
	void StartFinding(const Vector2 & start, const Vector2 & end);
	void ResetPassabilityMap();
	
private:

	// A-star algorithm.
	// The route returned is a string of direction digits.
	string pathFind(const int & xStart, const int & yStart,
		const int & xFinish, const int & yFinish);
	
	Vector2					m_startNodeIndex;
	Vector2					m_endNodeIndex;
	
	Vector2					m_mapSize;
	vector<vector<int>>		map;
	vector<vector<int>>		closed_nodes_map; // map of closed (tried-out) nodes
	vector<vector<int>>		open_nodes_map; // map of open (not-yet-tried) nodes
	vector<vector<int>>		dir_map; // map of directions
	
	vector<Vector2>			m_resultPath;

	bool					m_working;
};