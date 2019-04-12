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

std::vector<unsigned> Graph::getNodesIds()
{
	std::vector<unsigned> ids;

	for (auto && pair : nodes_)
		ids.push_back(pair.second->getId());

	return ids;
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

// V - The number of vertices in the graph
int Graph::getNodesCount() const
{
	// V
	return nodes_.size();
}

// A - The possible number of edges in the graph
int Graph::getMaxEdgesCount() const
{
	// A = V * (V-1)
	return nodes_.size() * (nodes_.size() - 1);
}

// S - The number of observed connections (edges)
int Graph::getCurrEdgesCount()
{
	int count = 0;
	for (auto && pair : adjacency_matrix_)
		for (auto && value : pair.second)
			if (value.second != nullptr)
				count++;
	// S
	return count;
}

// ∆ - is the network density
float Graph::getNetworkDensity()
{
	// ∆ = S / (V * (V-1))
	return static_cast<float>(getCurrEdgesCount()) / static_cast<float>(getMaxEdgesCount());
}

// Fi - An array of forces of influence verticles (Nodes).
std::vector<float> Graph::getForces()
{
	// Fi
	std::vector<float> forces;
	// i
	for (auto && nodePair : nodes_)
	{
		// bs - Sum(bi) output edges count
		auto bs = 0;
		for (auto && columnValuePair : adjacency_matrix_[nodePair.first])
		{
			if (columnValuePair.second != nullptr)
				bs++;
		}

		// Fi = S / A * (Sum(bi))
		forces.push_back(getNetworkDensity() * bs);
	}

	// Fi array
	return forces;
}

// I(X,Y) = H(X) - H(Y/X) = ...
std::map<unsigned, float> Graph::getAmountInfos()
{
	std::map<unsigned, float> amounts;

	auto inProbs = getInputProbabilities();
	auto outProbs = getOutputProbabilities();
	   
	for (auto && nodePair : nodes_)
	{
		auto m = getInEdgesCount(nodePair.first);
		auto n = getOutEdgesCount(nodePair.first);

		float I = 0;
		// Ii(X,Y) = - SUM j..n ( SUM i..m ( p(Xi,Yj) ) * Log2 ( SUM i..m ( P(Xi, Yj) ) ) )
		float sumJN = 0;
		for (auto j = 0; j < n; ++j)
		{
			float sumIM = 0;
			for (auto i = 0; i < m; ++i)
			{
				// P(Xi, Yj) = P(Xi) * P(Yj)
				auto p = inProbs[nodePair.first] * outProbs[nodePair.first];
				sumIM += p;
			}

			sumJN += sumIM * std::log2f(sumIM);
		}
		I = -sumJN;
		//			 + SUM i..m ( SUM j..n ( P(Xi,Yj) ) * Log2 ( P (Xi, Yj) / SUM j..n (P(Xi, Yj)) ) )			
		float sumIM = 0;
		for (auto i = 0; i < m; ++i)
		{
			sumJN = 0;
			for (auto j =0; j < n; ++j)
			{
				// P(Xi, Yj) = P(Xi) * P(Yj)
				auto p = inProbs[nodePair.first] * outProbs[nodePair.first];
				sumJN += p;
			}

			sumIM += sumJN * std::log2f(inProbs[nodePair.first] * outProbs[nodePair.first] / sumJN);
		}

		I += sumIM;

		amounts[nodePair.first] = I;
	}

	return amounts;
}

// P(x)  - probability of communication
std::map<unsigned, float> Graph::getInputProbabilities()
{
	std::map<unsigned, float> probabilities;

	for (auto && nodePair : nodes_)
	{
		/*auto inCount = getInEdgesCount(nodePair.first);*/
		probabilities[nodePair.first] = 1. /*- static_cast<float>(inCount)*/ / (nodes_.size() - 1);
	}
	return probabilities;
}

// P(y) - probability of communication
std::map<unsigned, float> Graph::getOutputProbabilities()
{
	std::map<unsigned, float> probabilities;

	for (auto&& nodePair : nodes_)
	{
		/*auto outCount = getOutEdgesCount(nodePair.first);*/
		probabilities[nodePair.first] = 1. /*- static_cast<float>(outCount)*/ / (nodes_.size() - 1);
	}
	return probabilities;
}

void Graph::createNodeInstance(unsigned id)
{
	nodes_[id] = std::make_shared<Node>(id);
}

void Graph::createEdgeInstance(unsigned from, unsigned to, int weight)
{
	adjacency_matrix_[from][to] = std::make_shared<Edge>(nodes_[from], nodes_[to], weight);
}
