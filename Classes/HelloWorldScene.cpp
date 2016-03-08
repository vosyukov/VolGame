#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	_square = ui::Button::create("square_normal.png", "square_select.png");
	_square->setPosition(Vec2(500, 400));
	addChild(_square);

	_square->addTouchEventListener(CC_CALLBACK_2(HelloWorld::ButtonCallback, this));


	auto listener1 = EventListenerTouchOneByOne::create();

	// trigger when you push down
	listener1->onTouchBegan = [](Touch* touch, Event* event) {
		// your code
		return true; // if you are consuming it
	};

	// trigger when moving touch
	listener1->onTouchMoved = [](Touch* touch, Event* event) {
		// your code
	};

	// trigger when you let up
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		// your code
	};

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	
	//create a sprite
	auto sprite = Sprite::create("box1.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(100, 600);
	this->addChild(sprite);
	Vec2* g = new Vec2[3];
	g[0] = Vec2(50, 50);
	g[1] = Vec2(50, 100);
	g[2] = Vec2(100, 50);




	auto physicsBody = PhysicsBody::createPolygon(g, 3);

		PhysicsMaterial(1.0f, 1.0f, 1.0f);
	physicsBody->setDynamic(true);
	//apply physicsBody to the sprite
	sprite->addComponent(physicsBody);
	//sprite->getPhysicsBody()->setCategoryBitmask(0x02);    // 0010
	sprite->getPhysicsBody()->setCollisionBitmask(1);   // 0001
	sprite->getPhysicsBody()->setContactTestBitmask(true);
	auto sprite3 = Sprite::create("box2.png");
	sprite3->setAnchorPoint(Vec2(0, 0));
	sprite3->setPosition(400, 500);
	sprite3->setColor(Color3B(100, 100, 100));



	this->addChild(sprite3);
	auto physicsBody3 = PhysicsBody::createBox(sprite3->getContentSize());
	PhysicsMaterial(1.0f, 1.0f, 1.0f);
	physicsBody3->setDynamic(true);
	//apply physicsBody to the sprite
	sprite3->addComponent(physicsBody3);




	//create a sprite
	auto sprite2 = Sprite::create("box4.png");
	
	sprite2->setAnchorPoint(Vec2(0, 0));
	sprite2->setPosition(10, 10);
	this->addChild(sprite2);
	auto physicsBody2 = PhysicsBody::createBox(sprite2->getContentSize());

	PhysicsMaterial(1.f, 1.0f, 1.0f);
	physicsBody2->setDynamic(false);
	//apply physicsBody to the sprite
	sprite2->addComponent(physicsBody2);
	//sprite2->getPhysicsBody()->setCategoryBitmask(0x01);    // 0001
	sprite2->getPhysicsBody()->setCollisionBitmask(2);   // 0010
	sprite2->getPhysicsBody()->setContactTestBitmask(true);
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::ButtonCallback(Ref *pSender, ui::Widget::TouchEventType type)
{
	auto button = static_cast<ui::Button*>(pSender);

	switch (type)
	{
		case ui::Widget::TouchEventType::ENDED:
		{
			if (button == _square) 
			{
				AddShape(SelectShape::SQUARE);
			}
		}
		break;

		case ui::Widget::TouchEventType::CANCELED:
		{

		}
		break;

		default:
			break;
	}
}

void  HelloWorld::AddShape(SelectShape shape)
{
	switch (shape)
	{
		case SelectShape::SQUARE:
		{
			auto sprite = Sprite::create("square.png");
			sprite->setAnchorPoint(Vec2(0, 0));
			sprite->setPosition(280, 450);
			sprite->setColor(Color3B(100, 100, 100));
			this->addChild(sprite);
			auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));			
			physicsBody->setDynamic(false);
			sprite->addComponent(physicsBody);
		}
		break;

		case SelectShape::RECTANGLE:
		{
			auto sprite = Sprite::create("square.png");
			sprite->setAnchorPoint(Vec2(0, 0));
			sprite->setPosition(280, 450);
			sprite->setColor(Color3B(100, 100, 100));
			this->addChild(sprite);
			auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));
			physicsBody->setDynamic(true);
			sprite->addComponent(physicsBody);
		}
		break;

		case SelectShape::TRIANGLE:
		{
			auto sprite = Sprite::create("square.png");
			sprite->setAnchorPoint(Vec2(0, 0));
			sprite->setPosition(280, 450);
			sprite->setColor(Color3B(100, 100, 100));
			this->addChild(sprite);
			auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));
			physicsBody->setDynamic(true);
			sprite->addComponent(physicsBody);
		}
		break;	

		default:
			break;
	}
}