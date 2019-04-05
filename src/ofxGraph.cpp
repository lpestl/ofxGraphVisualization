#include "ofxGraph.h"
#include "ofFileUtils.h"
#include "sstream"

void ofxGraph::setup()
{
}

void ofxGraph::update()
{
}

void ofxGraph::draw()
{
}

//bool ofxGraph::initFromFile(std::string fileName)
//{
//	ofFile initFile;
//	if (!initFile.open(fileName, ofFile::ReadOnly, false))
//		return false;
//
//	ofBuffer buff = initFile.readToBuffer();
//	auto lines = buff.getLines();
//	
//	std::vector<bool> init_flags;
//
//	for (auto line = lines.begin(); line != lines.end(); ++line)
//	{
//		std::stringstream ss;
//
//		/* Storing the whole string into string stream */
//		ss << line.asString();
//
//		/* Running loop till the end of the stream */
//		std::string temp;
//		int found;
//
//		std::vector<int> values;
//		while (!ss.eof()) 
//		{
//			/* extracting word by word from stream */
//			ss >> temp;
//
//			/* Checking the given word is integer or not */
//			if (std::stringstream(temp) >> found)
//				values.push_back(found);
//
//			/* To save from space at the end of string */
//			temp = "";
//		}
//
//		if (values.size() < 3)
//			continue;
//
//		addNode(values[0]);
//		addNode(values[1]);
//		// We use both direction graph
//		init_flags.push_back(addEdge(values[0], values[1], values[2]));
//		init_flags.push_back(addEdge(values[1], values[0], values[2]));
//	}
//
//	// TODO: Need remove return type and this crutch
//	for (auto && init_flag : init_flags)
//		if (!init_flag)
//			return false;
//
//	return true;
//}
//
//bool ofxGraph::addNode(unsigned id)
//{
//	if (nodes_.find(id) != nodes_.end())
//		return false;
//
//	nodes_[id] = std::make_shared<Node>(id);
//
//	return true;
//}
//
//bool ofxGraph::deleteNode(unsigned id)
//{
//	const auto erasingNode = nodes_.find(id);
//
//	if (erasingNode == nodes_.end())
//		return false;
//
//	nodes_.erase(erasingNode);
//
//	return true;
//}
//
//bool ofxGraph::addEdge(unsigned from_id, unsigned to_id, int weight)
//{
//	const auto it_fromNode = nodes_.find(from_id);
//	const auto it_toNode = nodes_.find(to_id);
//	
//	if ((it_fromNode == nodes_.end()) || (it_toNode == nodes_.end()))
//		return false;
//
//	auto it_edgeList = edges_.find(from_id);
//	if (it_edgeList != edges_.end())
//	{
//		auto contains = false;
//		for (const auto& edge : it_edgeList->second)
//		{
//			if (edge.get()->getDestNodeId() == to_id)
//			{
//				contains = true;
//				// TODO: This Exception situation
//				return false;
//			}
//		}
//
//		if (!contains)
//			it_edgeList->second.push_back(std::make_shared<Edge>(nodes_[from_id], nodes_[to_id], weight));
//
//		return true;
//	}
//
//	edges_[from_id] = std::vector<std::shared_ptr<Edge>>{ std::make_shared<Edge>(nodes_[from_id], nodes_[to_id], weight) };
//	return true;
//}
//
//bool ofxGraph::deleteEdge(unsigned from_id, unsigned to_id)
//{
//	// default
//	return false;
//}
//
//size_t ofxGraph::getNodesNumber()
//{
//	// default
//	return 0;
//}
//
//size_t ofxGraph::getInEdgesNumber(unsigned id)
//{
//	// default
//	return 0;
//}
//
//size_t ofxGraph::getOutEdgesNumber(unsigned id)
//{
//	// default
//	return 0;
//}
//
//size_t ofxGraph::getEdgesNumber(unsigned id, bool mergeBothDirEdge)
//{
//	// default
//	return 0;
//}
//
//std::vector<std::vector<std::shared_ptr<Edge>>> ofxGraph::getAdjacencyMatrix()
//{
//	// default
//	return std::vector<std::vector<std::shared_ptr<Edge>>> {};
//}
//
//std::vector<std::shared_ptr<Edge>> ofxGraph::getEdgesList()
//{
//	// default
//	return std::vector<std::shared_ptr<Edge>>{};
//}
