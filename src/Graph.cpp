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

	nodes_[id] = std::make_shared<Node>(id);

	std::map<unsigned, std::shared_ptr<Edge>> line;
	for (auto&& node : nodes_)
		line[node.first] = nullptr;

	adjacency_matrix_[id] = line;

	for (auto&& node : nodes_)
		adjacency_matrix_[node.first][id] = nullptr;
	
	/*for (auto && row : adjacency_matrix_)
		row.second[id] = nullptr;

	for (auto&& column : adjacency_matrix_[id])
		column.second = nullptr;*/
}

void Graph::deleteNode(unsigned id)
{
	// todo:
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
		adjacency_matrix_[from][to] = std::make_shared<Edge>(nodes_[from], nodes_[to], weight);
}

void Graph::deleteEdge(unsigned from, unsigned to)
{
	// todo:
}

size_t Graph::getInEdgesCount(unsigned node_id)
{
	// todo:
	return 0;
}

size_t Graph::getOutEdgesCount(unsigned node_id)
{
	// todo:
	return 0;
}
