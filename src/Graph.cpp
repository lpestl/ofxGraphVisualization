#include "Graph.h"
#include "ofFileUtils.h"
#include <sstream>
#include "ofLog.h"
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

Graph::Graph()
{
}

Graph::Graph(const Graph& graph)
{
	for (auto && node : graph.nodes_)
	{
		this->nodes_[node.first] = std::make_shared<Node>(*node.second.get());
	}

	for (auto && linePair : graph.adjacency_matrix_)
	{
		std::map<unsigned, std::shared_ptr<Edge>> copyLine;

		for (auto && pair : linePair.second)
		{
			if (pair.second != nullptr)
				copyLine[pair.first] = std::make_shared<Edge>(*pair.second.get(), this->nodes_[pair.second->getSourceNodeId()], this->nodes_[pair.second->getDestNodeId()]);
			else
				copyLine[pair.first] = nullptr;
		}

		this->adjacency_matrix_[linePair.first] = copyLine;
	}
}

Graph::~Graph()
{
}

void Graph::init(std::string path_to_file)
{
	ofFile initFile;
	if (!initFile.open(path_to_file, ofFile::ReadOnly, false))
		return;

	ofBuffer buff = initFile.readToBuffer();
	auto lines = buff.getLines();
	
	for (auto line = lines.begin(); line != lines.end(); ++line)
	{
		std::stringstream ss;

		/* Storing the whole string into string stream */
		ss << line.asString();

		/* Running loop till the end of the stream */
		std::string temp;
		int found;

		std::vector<int> values;
		while (!ss.eof()) 
		{
			/* extracting word by word from stream */
			ss >> temp;

			/* Checking the given word is integer or not */
			if (std::stringstream(temp) >> found)
				values.push_back(found);

			/* To save from space at the end of string */
			temp = "";
		}

		if (values.size() < 3) 
		{
			std::cout << "[INFO] This line in the file does not contain 3 int numbers: " << line.asString() << std::endl;
			continue;
		}

		addNode(values[0]);
		addNode(values[1]);
		
		addEdge(values[0], values[1], values[2]);
	}
}

void Graph::init(unsigned nodesCount, unsigned edgesCount)
{
	for (unsigned i = 1; i <= nodesCount; ++i)
		createNodeInstance(i);
	
	std::vector<unsigned> from;
	std::vector<unsigned> to;
	for (unsigned i = 1; i <= nodesCount; ++i)
	{
		from.push_back(i);
		to.push_back(i);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	if (edgesCount < getMaxEdgesCount() / 2)
	{
		unsigned count = 0;
		
		while (count < edgesCount)
		{
			std::shuffle(from.begin(), from.end(), std::default_random_engine(seed));
			std::shuffle(to.begin(), to.end(), std::default_random_engine(seed));

			for (auto && valueFrom : from)
			{
				bool isAdded = false;
				for (auto && valueTo : to)
				{
					if ((adjacency_matrix_[valueFrom][valueTo] == nullptr) && (valueFrom != valueTo))
					{
						createEdgeInstance(valueFrom, valueTo, 1);
						isAdded = true;
						count++;
						break;
					}
				}
				if (isAdded)
					break;
			}
		}
	} else
	{
		for (auto && valueFrom : from)
			for (auto && valueTo : to)
				if (valueFrom != valueTo)
					createEdgeInstance(valueFrom, valueTo, 1);

		unsigned count = getMaxEdgesCount();

		while (count > edgesCount)
		{
			std::shuffle(from.begin(), from.end(), std::default_random_engine(seed));
			std::shuffle(to.begin(), to.end(), std::default_random_engine(seed));

			for (auto&& valueFrom : from)
			{
				bool isDeleted = false;
				for (auto&& valueTo : to)
				{
					if (adjacency_matrix_[valueFrom][valueTo] != nullptr)
					{
						deleteEdge(valueFrom, valueTo);
						isDeleted = true;
						count--;
						break;
					}
				}
				if (isDeleted)
					break;
			}
		}
	}
}

void Graph::clear()
{
	for (auto && linePair : adjacency_matrix_)
	{
		for (auto && value : adjacency_matrix_[linePair.first])
		{
			value.second = nullptr;
		}

		adjacency_matrix_[linePair.first].clear();
	}
	adjacency_matrix_.clear();

	nodes_.clear();
}

void Graph::addNode(unsigned id)
{
	if (nodes_.find(id) != nodes_.end())
		return;
	
	//nodes_[id] = std::make_shared<Node>(id);
	createNodeInstance(id);

	std::map<unsigned, std::shared_ptr<Edge>> line;
	for (auto&& node : nodes_)
		line[node.first] = nullptr;

	adjacency_matrix_[id] = line;

	for (auto&& node : nodes_)
		adjacency_matrix_[node.first][id] = nullptr;	
}

void Graph::deleteNode(unsigned id)
{
	if (nodes_.find(id) == nodes_.end())
	{
		std::cout << "[WARN] Node with id = " << id << "not founded." << std::endl;
		return;
	}

	for (auto && node : nodes_)
		adjacency_matrix_[node.second->getId()].erase(id);

	adjacency_matrix_.erase(id);

	nodes_.erase(id);
}

void Graph::addEdge(unsigned from, unsigned to, int weight)
{
	if (nodes_.find(from) == nodes_.end())
	{
		std::cout << "[WARN] Node with id = " << from << "not founded." << std::endl;
		return;
	}

	if (nodes_.find(to) == nodes_.end())
	{
		std::cout << "[WARN] Node with id = " << to << "not founded." << std::endl;
		return;
	}

	if (adjacency_matrix_[from][to] != nullptr)
		adjacency_matrix_[from][to].get()->setWeight(weight);
	else
		//adjacency_matrix_[from][to] = std::make_shared<Edge>(nodes_[from], nodes_[to], weight);
		createEdgeInstance(from, to, weight);
}

void Graph::deleteEdge(unsigned from, unsigned to)
{
	if (nodes_.find(from) == nodes_.end())
	{
		std::cout << "[WARN] Node with id = " << from << "not founded." << std::endl;
		return;
	}

	if (nodes_.find(to) == nodes_.end())
	{
		std::cout << "[WARN] Node with id = " << to << "not founded." << std::endl;
		return;
	}

	if (adjacency_matrix_[from][to] == nullptr)
		std::cout << "[WARN] Edge from " << from << " to " << to << " not founded." << std::endl;
	else
		adjacency_matrix_[from][to] = nullptr;
}

size_t Graph::getInEdgesCount(unsigned node_id)
{
	if (nodes_.find(node_id) == nodes_.end())
	{
		std::cout << "[WARN] Node with id = " << node_id << "not founded." << std::endl;
		return 0;
	}

	// todo: check it
	size_t count = 0;
	for (auto && node : nodes_)
		if (adjacency_matrix_[node_id][node.second->getId()] != nullptr)
			count++;

	return count;
}

size_t Graph::getOutEdgesCount(unsigned node_id)
{
	if (nodes_.find(node_id) == nodes_.end())
	{
		std::cout << "[WARN] Node with id = " << node_id << "not founded." << std::endl;
		return 0;
	}

	// todo: check it
	size_t count = 0;
	for (auto&& node : nodes_)
		if (adjacency_matrix_[node.second->getId()][node_id] != nullptr)
			count++;

	return count;
}

int Graph::getNodesCount() const
{
	return nodes_.size();
}

int Graph::getMaxEdgesCount() const
{
	return nodes_.size() * (nodes_.size() - 1);
}

int Graph::getCurrEdgesCount()
{
	int count = 0;
	for (auto && pair : adjacency_matrix_)
		for (auto && value : pair.second)
			if (value.second != nullptr)
				count++;

	return count;
}

float Graph::getNetworkDensity()
{
	return static_cast<float>(getCurrEdgesCount()) / static_cast<float>(getMaxEdgesCount());
}

void Graph::createNodeInstance(unsigned id)
{
	nodes_[id] = std::make_shared<Node>(id);
}

void Graph::createEdgeInstance(unsigned from, unsigned to, int weight)
{
	adjacency_matrix_[from][to] = std::make_shared<Edge>(nodes_[from], nodes_[to], weight);
}
