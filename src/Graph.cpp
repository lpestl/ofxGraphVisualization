#include "Graph.h"
#include "ofFileUtils.h"
#include <sstream>
#include "ofLog.h"

Graph::Graph()
{
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
		
		// We use both direction graph
		addEdge(values[0], values[1], values[2]);
		//addEdge(values[1], values[0], values[2]);
	}
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

void Graph::createNodeInstance(unsigned id)
{
	nodes_[id] = std::make_shared<Node>(id);
}

void Graph::createEdgeInstance(unsigned from, unsigned to, int weight)
{
	adjacency_matrix_[from][to] = std::make_shared<Edge>(nodes_[from], nodes_[to], weight);
}
