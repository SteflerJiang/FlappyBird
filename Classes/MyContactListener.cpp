#include "MyContactListener.h"
#include "PhysicalSprite.h"

MyContactListener::MyContactListener()
{
}

MyContactListener::MyContactListener(b2World* w, Layer* c)
{
	_world = w;
	_layer = c;
}

MyContactListener::~MyContactListener() {}

void MyContactListener::BeginContact(b2Contact* contact) {}

void MyContactListener::EndContact(b2Contact* contact) {}

void MyContactListener::PreSolve(b2Contact* contact, const b2ManifoldPoint* oldManifold) {}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	float force = impulse->normalImpulses[0];
	if (force > 2) {
		PhysicalSprite* spriteA = (PhysicalSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
		PhysicalSprite* spriteB = (PhysicalSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
		if (spriteA && spriteB) {
			spriteA->hp--;
			spriteB->hp--;
		}
	}
}