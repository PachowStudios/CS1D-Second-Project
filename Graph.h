#ifndef GRAPH_H
#define GRAPH_H

#include <QHash>
#include <QList>

class Graph
{
public:
	Graph() = default;

	bool AddNode(int ID);
	bool RemoveNode(int ID);
	bool SetConnection(int a, int b, int weight);
	bool RemoveConnection(int a, int b);

private:
	QList<int> nodes;
	QHash<int, QHash<int, int>> vertices;
};

#endif