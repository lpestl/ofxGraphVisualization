#pragma once

class Node
{
public:
	Node(unsigned id);
	virtual ~Node();

	virtual void update() {};
	virtual void draw() {};

	unsigned getId() const;
protected:
	unsigned id_;
};

