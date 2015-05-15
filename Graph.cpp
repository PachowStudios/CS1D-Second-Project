#include "Graph.h"

bool Graph::LoadFromJson(const QJsonArray &json)
{
	for (auto &arrayItem : json)
	{
		QJsonObject connectionJson = arrayItem.toObject();

		if (connectionJson.contains("A") &&
			connectionJson.contains("B") &&
			connectionJson.contains("Weight"))
			SetConnection(connectionJson["A"].toInt(),
			              connectionJson["B"].toInt(),
			              connectionJson["Weight"].toInt());
		else
			return false;
	}

	return true;
}

QJsonArray Graph::SaveToJson() const
{
	QJsonArray json;

	for (GraphIterator vertex = vertices.begin();
		 vertex != vertices.end();
		 vertex++)
	{
		for (VertexIterator connection = vertex.value().begin();
			 connection != vertex.value().end();
			 connection++)
		{
			QJsonObject connectionJson;

			connectionJson["A"]      = vertex.key();
			connectionJson["B"]      = connection.key();
			connectionJson["Weight"] = connection.value();

			json.append(connectionJson);
		}
	}

	return json;
}

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

Path Graph::CalculatePath(int start, int finish) const
{
	if (!nodes.contains(start) || !nodes.contains(finish))
		return QList<int>();

	QHash<int, int> distances;
	QHash<int, int> previous;
	QList<int> tempNodes;
	Path path;

	auto comparator = [&](int left, int right)
	{
		return distances[left] > distances[right];
	};

	for (GraphIterator vertex = vertices.begin(); 
		 vertex != vertices.end(); 
		 vertex++)
	{
		if (vertex.key() == start)
			distances[vertex.key()] = 0;
		else
			distances[vertex.key()] = std::numeric_limits<int>::max();

		tempNodes.push_back(vertex.key());
		std::push_heap(tempNodes.begin(), tempNodes.end(), comparator);
	}

	while (!tempNodes.empty())
	{
		std::pop_heap(tempNodes.begin(), tempNodes.end(), comparator);
		int smallest = tempNodes.back();
		tempNodes.pop_back();

		if (smallest == finish)
		{
			while (previous.find(smallest) != previous.end())
			{
				path.push_front(smallest);
				smallest = previous[smallest];
			}

			break;
		}

		if (distances[smallest] == std::numeric_limits<int>::max())
			break;

		for (VertexIterator neighbor = vertices[smallest].begin(); 
			 neighbor != vertices[smallest].end();
			 neighbor++)
		{
			int alt = distances[smallest] + neighbor.value();

			if (alt < distances[neighbor.key()])
			{
				distances[neighbor.key()] = alt;
				previous[neighbor.key()] = smallest;
				std::make_heap(tempNodes.begin(), tempNodes.end(), comparator);
			}
		}
	}

	path.push_front(start);

	return path;
}

int Graph::CalculateDistance(QList<int> path) const
{
	int distance = 0;

	if (path.count() == 0)
		return -1;

	for (int i = 1; i < path.count(); i++)
	{
		distance += vertices[path[i - 1]][path[i]];
	}

	return distance;
}