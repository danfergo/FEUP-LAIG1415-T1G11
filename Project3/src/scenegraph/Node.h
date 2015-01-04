#ifndef NODE_F_H_
#define NODE_F_H_

#include "primitives/Primitive.h"
#include "appearances/Appearance.h"
#include "animations/Animation.h"
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
	int currentAnimationIndex;
	int lastEndTime;
	bool touchable;
	bool visible;
	int name;
public:
	Node();
	~Node();
	void processNodeInitialization(Appearance * parentAppearance);
	void processNode(Appearance * parentAppearance, bool parentIsVisible, bool parentIsTouchable, std::vector<Node *> * nodes);
	void addPrimitive(Primitive * primitive);
	void addDescendants(Node * descendant);
	void setAppearance(Appearance * appearance);
	void addAnimation(Animation * animation);
	unsigned getLastAnimationEndTime() const;
	bool hasAppearance() const;
	void setDisplayList();

	virtual void update(unsigned time);

	void resetTransformations();
	bool addRotation(std::string axis, float angle);
	void addRotationX(float angle);
	void addRotationY(float angle);
	void addRotationZ(float angle);
	void addScaling(float x, float y, float z);
	void addTranslation(float x, float y, float z);

	void setTouchable(bool touchable);
	void setVisible(bool visible);

	virtual void animationCallback(){};

	virtual bool clickHandler();
};

#endif