#pragma once
#include "CGFobject.h"
#include "CGFappearance.h"
#include <vector>

class Node
{
private:
	std::vector<Node *> descendants;
	std::vector<CGFobject *> primitives;
	float transforms[16];
	CGFappearance * appearance;
public:
	Node();
	~Node();
	void processNode(CGFappearance * parentAppearance);
	void addPrimitive(CGFobject * primitive);
	void Node::addDescendants(Node * descendant);
	void setAppearance(CGFappearance * appearance);
	bool hasAppearance() const;

	bool addRotation(std::string axis, float angle);
	void addRotationX(float angle);
	void addRotationY(float angle);
	void addRotationZ(float angle);
	void addScaling(float x, float y, float z);
	void addTranslation(float x, float y, float z);

};

