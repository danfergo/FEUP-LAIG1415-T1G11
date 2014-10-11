#ifndef NODE_F_H_
#define NODE_F_H_

#include "Primitive.h"
#include "Appearance.h"
#include <vector>

class Node
{
private:
	std::vector<Node *> descendants;
	std::vector<Primitive *> primitives;
	float transforms[16];
	Appearance * appearance;
public:
	Node();
	~Node();
	void processNode(Appearance * parentAppearance);
	void addPrimitive(Primitive * primitive);
	void Node::addDescendants(Node * descendant);
	void setAppearance(Appearance * appearance);
	bool hasAppearance() const;

	bool addRotation(std::string axis, float angle);
	void addRotationX(float angle);
	void addRotationY(float angle);
	void addRotationZ(float angle);
	void addScaling(float x, float y, float z);
	void addTranslation(float x, float y, float z);

};

#endif