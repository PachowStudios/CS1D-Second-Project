#include "Graph.h"

bool Graph::AddNode(int ID)
{
	if (nodes.contains(ID))
		return false;

	nodes.append(ID);

	return true;
}

bool Graph::RemoveNode(int ID)
{
	if (!nodes.contains(ID))
		return false;

	vertices.remove(ID);

	for (auto &node : vertices)
		node.remove(ID);

	return true;
}

bool Graph::SetConnection(int a, int b, int weight)
{
	if (!nodes.contains(a) || !nodes.contains(b))
		return false;

	vertices[a][b] = weight;
	vertices[b][a] = weight;

	return true;
}

bool Graph::RemoveConnection(int a, int b)
{
	if (!nodes.contains(a) || !nodes.contains(b))
		return false;

	vertices[a].remove(b);
	vertices[b].remove(a);

	return true;
}