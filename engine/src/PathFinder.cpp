#include "include/PathFinder.h"
#include "include/PassabilityMap.h"
#include <queue>


PathFinder::node::node(int xp, int yp, int d, int p)
{
	xPos = xp; yPos = yp; level = d; priority = p;
}

void PathFinder::node::updatePriority(const int& xDest, const int& yDest)
{
	priority = level + estimate(xDest, yDest) * 10; //A*
}

void PathFinder::node::nextLevel(const int& i)
{
	level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

const int& PathFinder::node::estimate(const int& xDest, const int& yDest) const
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	d = static_cast<int>(sqrt(xd*xd + yd * yd));

	// Manhattan distance
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));

	return(d);
}


// ------------------------------------------------------------------------------------- //

string PathFinder::pathFind(const int& xStart, const int& yStart, const int& xFinish, const int& yFinish)
{
	const int n = (int)m_mapSize.x; // horizontal size of the map
	const int m = (int)m_mapSize.y; // vertical size size of the map
	
	static std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static node* n0;
	static node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the node maps
	for (y = 0; y < m; y++)
	{
		for (x = 0; x < n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[xStart][yStart] = n0->getPriority(); ; // mark it on the open nodes map
	// open_nodes_map[x][y] = n0->getPriority();

	// A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				m_resultPath.emplace_back(Vector2(x,y));
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i < dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					delete m0;
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy] > m0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

					// empty the larger size pq to the smaller one
					if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
					delete m0;
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return ""; // no route found
}

PathFinder::PathFinder()
	: m_startNodeIndex(Vector2::zero)
	, m_endNodeIndex(Vector2::zero)
	, m_working(false)
{
	ResetPassabilityMap();
}

void PathFinder::GetResult(vector<Vector2>& path)
{
	std::reverse(std::begin(m_resultPath), std::end(m_resultPath));
	path = m_resultPath;
}

void PathFinder::StartFinding(const Vector2& startPos, const Vector2& endPos)
{
	m_working = true;
	m_startNodeIndex = PassabilityMap::instance()->WorldToNodeIndex(startPos);
	m_endNodeIndex = PassabilityMap::instance()->WorldToNodeIndex(endPos);

	auto pMap = PassabilityMap::instance()->GetAllNodes();
	
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		for (int y = 0; y < m_mapSize.y; ++y)
		{
			map[x][y] = !pMap[x][y]->m_passible;
		}
	}

	m_resultPath.clear();
	
	std::thread th([this](){
		pathFind(m_startNodeIndex.x, m_startNodeIndex.y,
			m_endNodeIndex.x, m_endNodeIndex.y);

		for (int i = 0; i < m_resultPath.size(); ++i)
		{
			m_resultPath[i] = PassabilityMap::instance()->NodeIndexToWorld(m_resultPath[i]);
		}
		
		m_working = false;
	});
	th.join();
}

void PathFinder::ResetPassabilityMap()
{
	m_mapSize = PassabilityMap::instance()->GetMapSize();

	map.resize(m_mapSize.x);
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		map[x].resize(m_mapSize.y);
	}

	closed_nodes_map.resize(m_mapSize.x);
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		closed_nodes_map[x].resize(m_mapSize.y);
	}

	open_nodes_map.resize(m_mapSize.x);
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		open_nodes_map[x].resize(m_mapSize.y);
	}

	dir_map.resize(m_mapSize.x);
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		dir_map[x].resize(m_mapSize.y);
	}
}
