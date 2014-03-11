#pragma once

class FooTest : public Test
{
	public:

	enum _moveState
	{
    MS_STOP,
    MS_LEFT,
    MS_RIGHT,
	};

	_moveState moveState;
	b2Body* dynamicBody;

	FooTest()
	{
		///////box
		b2BodyDef boxBodyDef;
		boxBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		boxBodyDef.position.Set(0, 20); //set the starting position
		boxBodyDef.angle = 0;

		dynamicBody = m_world->CreateBody(&boxBodyDef);
		dynamicBody->SetFixedRotation(true);
		
		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = 1; //radius
  
		b2PolygonShape rectShape;
		b2FixtureDef boxRectFixtureDef;
		boxRectFixtureDef.shape = &rectShape;
		boxRectFixtureDef.density = 1000;
		b2Vec2 pos(0.0f , 2.0f);
		rectShape.SetAsBox(0.5f, 1, pos , 0 );
		dynamicBody->CreateFixture(&boxRectFixtureDef);

		b2FixtureDef boxCircleFixtureDef;
		boxCircleFixtureDef.shape = &circleShape;
		boxCircleFixtureDef.density = 1;
		boxCircleFixtureDef.friction=10;
		dynamicBody->CreateFixture(&boxCircleFixtureDef);
		////
		
		//////edge
		b2BodyDef edgeBodyDef;
		edgeBodyDef.type = b2_staticBody;
  
		b2FixtureDef edgeFixtureDef;
		b2EdgeShape edgeShape;
		edgeShape.Set( b2Vec2(-20,0), b2Vec2(20,10) );
		edgeFixtureDef.shape = &edgeShape;
		b2Body* staticBody = m_world->CreateBody(&edgeBodyDef);
		staticBody->CreateFixture(&edgeFixtureDef); //add a fixture to the body
		////

		//////moveState
		moveState = MS_STOP;
		////
	}
	
void Keyboard(unsigned char key)
 {
    switch (key)
	{
		case 'a': //move left
			moveState = MS_LEFT;
        break;
		case 's': //stop
			moveState = MS_STOP;
        break;
	    case 'd': //move right
			moveState = MS_RIGHT;
        break;
		case 'w':
		{
			//to change velocity by 10
			float impulse = dynamicBody->GetMass() * 15;
			dynamicBody->ApplyLinearImpulse( b2Vec2(0,impulse), dynamicBody->GetWorldCenter(), true );
		}
		break;
	    default:
        Test::Keyboard(key);   //run default behaviour
    }
  }

void Step(Settings* settings)
	{
		b2Vec2 vel = dynamicBody->GetLinearVelocity();
	    float desiredVel = 0;
	    switch ( moveState )
	    {
	      case MS_LEFT:  desiredVel = -10; break;
	      case MS_STOP:  desiredVel =  0; break;
	      case MS_RIGHT: desiredVel =  10; break;
	    }
	    float velChange = desiredVel - vel.x;
	    float impulse = dynamicBody->GetMass() * velChange; //disregard time factor
	    dynamicBody->ApplyLinearImpulse( b2Vec2(impulse,0), dynamicBody->GetWorldCenter(), true );
		Test::Step(settings);
	}
	
	static Test* Create()
	{
		return new FooTest;
	}
};
