#pragma once

class QueryCallback : public b2QueryCallback
{
public:
	bool ReportFixture(b2Fixture*);
};

