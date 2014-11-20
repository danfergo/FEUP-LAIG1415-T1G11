#ifndef NODE_F_H_
#define NODE_F_H_

#include "Primitive.h"
#include "Appearance.h"
#include "../Animation.h"
#include <map>
#include <vector>

class Node
{
private:
	std::vector<Node *> descendants;
	std::vector<Primitive *> primitives;
	std::vector<Animation *> animations;
	std::map<Appearance *, int> displayListsIds;
	float transforms[16];
	Appearance * appearance;
	bool isDisplayList;
public:
	Node();
	~Node();
	void processNodeInitialization(Appearance * parentAppearance);
	void processNode(Appearance * parentAppearance);
	void addPrimitive(Primitive * primitive);
	void Node::addDescendants(Node * descendant);
	void setAppearance(Appearance * appearance);
	void addAnimation(Animation * animation);
	unsigned getLastAnimationEndTime() const;
	bool hasAppearance() const;
	void setDisplayList();

	void update(unsigned time);

	bool addRotation(std::string axis, float angle);
	void addRotationX(float angle);
	void addRotationY(float angle);
	void addRotationZ(float angle);
	void addScaling(float x, float y, float z);
	void addTranslation(float x, float y, float z);

};

#endif