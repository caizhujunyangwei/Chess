#include "Head.h"


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	auto delay = DelayTime::create(2);
	auto call = CallFunc::create([]() {
		Director::getInstance()->replaceScene(
			TransitionFade::create(1.0f,GameScene::createScene()));
	});


	runAction(Sequence::create(delay, call, nullptr));

    return true;
}
