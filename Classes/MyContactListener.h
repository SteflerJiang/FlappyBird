#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
using namespace std;

class MyContactListener : public b2ContactListener {
public:
	b2World* _world;
	Layer* _layer;
	MyContactListener();
	MyContactListener(b2World* w, Layer* c);
	~MyContactListener();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2ManifoldPoint* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};