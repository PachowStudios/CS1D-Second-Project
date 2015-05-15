#ifndef GRAPH_H
#define GRAPH_H

#include <QHash>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>
#include <limits>

class Graph
{
public:
	Graph() = default;

	bool       LoadFromJson(const QJsonArray &json);
	QJsonArray SaveToJson() const;

	bool AddNode(int ID);
	bool RemoveNode(int ID);
	bool SetConnection(int a, int b, int weight);
	bool RemoveConnection(int a, int b);

	QList<int> CalculatePath(int start, int finish) const;
	int        CalculateDistance(QList<int> path) const;

private:
	QList<int> nodes;
	QHash<int, QHash<int, int>> vertices;

	typedef QHash<int, QHash<int, int>>::const_iterator GraphIterator;
	typedef QHash<int, int>::const_iterator VertexIterator;
};

typedef QList<int> Path;

#endif