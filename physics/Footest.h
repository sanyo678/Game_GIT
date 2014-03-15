#pragma once
#include "Testbed/Tests/Ground.hpp"

class Player {
  public:
    //class member variables
    b2Body* dynamicBody;
	 bool	onFloor;
  
  public:
    Player(b2World* world) {
      ///////box
		b2BodyDef boxBodyDef;
		boxBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		boxBodyDef.position.Set(0, 20); //set the starting position
		boxBodyDef.angle = 0;

		dynamicBody = world->CreateBody(&boxBodyDef);
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
		onFloor=false;
		dynamicBody->SetUserData( this );
    }

	void startContact() {onFloor = true; }
	void endContact() { onFloor = false; }

    ~Player() {}
  
  };


 class MyContactListener : public b2ContactListener
  {
    void BeginContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->startContact();
  
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->startContact();
  
    }
  
    void EndContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->endContact();
  
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->endContact();
  
    }
  };

class FooTest : public Test
{
	public:

	MyContactListener myContactListenerInstance;

	enum _moveState
	{
    MS_STOP,
    MS_LEFT,
    MS_RIGHT,
	};

	_moveState moveState;
	//b2Body* dynamicBody;
	Player* player;
	Ground* ground;

	FooTest()
	{
		
		player = new Player(m_world);

		b2Vec2 a(-20,0);
		b2Vec2 b(-11,4);
		ground = new Ground( a, b, m_world);

		ground->edges.push_back(b2Vec2(-11.0, 4.0));
		ground->edges.push_back(b2Vec2(-9.0, 6.0));
		ground->edges.push_back(b2Vec2(-6.0, 4.0));
		ground->edges.push_back(b2Vec2(-1.0, 6.0));
		ground->edges.push_back(b2Vec2(3.0, 4.0));
		ground->edges.push_back(b2Vec2(7.0, 3.0));
		ground->edges.push_back(b2Vec2(8.0, 4.0));
		ground->edges.push_back(b2Vec2(10.0, 5.0));
		ground->edges.push_back(b2Vec2(12.0, 3.0));
		
		ground->build(m_world);

		ground->makeHole(b2Vec2(3.0,4.0),3.0f);
		ground->makeHole(b2Vec2(8.0,4.0),2.0f);
		ground->makeHole(b2Vec2(6.0,0.0),3.0f);

		ground->build(m_world);

		//////moveState
		moveState = MS_STOP;
		////

		m_world->SetContactListener(&myContactListenerInstance);
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
			if (player->onFloor)
			//to change velocity by 15
			{
				float impulse = player->dynamicBody->GetMass() * 15;
				player->dynamicBody->ApplyLinearImpulse( b2Vec2(0,impulse), player->dynamicBody->GetWorldCenter(), true );
			}
		}
		break;
	    default:
        Test::Keyboard(key);   //run default behaviour
    }
  }

void Step(Settings* settings)
	{
		b2Vec2 vel = player->dynamicBody->GetLinearVelocity();
	    float desiredVel = 0;
	    switch ( moveState )
	    {
	      case MS_LEFT:  desiredVel = -10; break;
	      case MS_STOP:  desiredVel =  0; break;
	      case MS_RIGHT: desiredVel =  10; break;
	    }
	    float velChange = desiredVel - vel.x;
	    float impulse = player->dynamicBody->GetMass() * velChange; //disregard time factor
	    player->dynamicBody->ApplyLinearImpulse( b2Vec2(impulse,0), player->dynamicBody->GetWorldCenter(), true );

		if(player->onFloor)
		{
			m_debugDraw.DrawString(5, m_textLine, "onFloor : true");
            m_textLine += 15;
		}
		else
		{
			m_debugDraw.DrawString(5, m_textLine, "onFloor : false");
            m_textLine += 15;
		}

		

		Test::Step(settings);
	}
	
	static Test* Create()
	{
		return new FooTest;
	}
};
