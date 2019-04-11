#pragma once

class Node
{
public:
	Node(unsigned id);
	Node(const Node& node);
	virtual ~Node();
	
	unsigned getId() const;
protected:
	unsigned id_;
};

