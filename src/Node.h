#pragma once

class Node
{
public:
	Node(unsigned id);
	~Node();

	unsigned getId() const;
private:
	unsigned id_;
};

