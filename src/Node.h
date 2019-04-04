#pragma once

//#include <vector>
//#include "Edge.h"
//#include <memory>

//class Edge;

class Node
{
public:
	Node(unsigned id);
	~Node();

	unsigned getId() const;
private:
	unsigned id_;
	//std::vector<std::shared_ptr<Edge>> edges_;
};

