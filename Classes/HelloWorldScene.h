#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;
enum class SelectShape {
	SQUARE = 0,
	TRIANGLE = 1,
	RECTANGLE = 2
};

class HelloWorld : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();
	
    virtual bool init();
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
	//extension::PhysicsDebugNode* _debugLayer; // weak ref
#endif
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onContactBegin(PhysicsContact& contact);


	void ButtonCallback(Ref *pSender, ui::Widget::TouchEventType type);
	void AddShape(SelectShape shape);

	ui::Button* _square;
	ui::Button* _triangle;
	ui::Button* _rectangle;

	SelectShape _selectShape;

};

#endif // __HELLOWORLD_SCENE_H__
