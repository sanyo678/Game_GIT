#pragma once
class ContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact*);
	virtual void EndContact(b2Contact*);
};

