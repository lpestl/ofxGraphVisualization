#pragma once

class Node
{
public:
	Node(unsigned id);
	virtual ~Node();
	
	unsigned getId() const;
protected:
	unsigned id_;
};

