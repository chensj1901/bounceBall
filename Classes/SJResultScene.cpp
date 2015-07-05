//
//  SJResultScene.cpp
//  bounceBall
//
//  Created by 陈少杰 on 15/6/27.
//
//

#include "SJResultScene.h"
#include "config.h"
#include "SJGameScene.h"
#include "SJIndexScene.h"

USING_NS_CC;

Scene* SJResult::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SJResult::create();
    
    // add layer as a child to scene
    layer->setTag(88);
    
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SJResult::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto layer=LayerColor::create(Color4B(239, 241, 224, 255));
    this->addChild(layer,0);
    
    return true;
}

void SJResult::onEnterTransitionDidFinish(){
    
    msgLabel=Label::createWithTTF("游戏结束", "fonts/hyz.ttf", 48);
    msgLabel->setPosition(WIDTH/2, HEIGHT/5*4);
    msgLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(msgLabel,5);
    
    String *topStr=String::createWithFormat("zui高纪录：躲过%d面墙",this->top);
    topLabel=Label::createWithTTF(topStr->getCString(), "fonts/hyz.ttf", 28);
    topLabel->setPosition(WIDTH/2, HEIGHT/5*3);
    topLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(topLabel,5);
    
    float precent=(1-1/((float)this->mark/this->ballCount))*100;
    precent=MAX(precent, 1);
    precent=MIN(precent, 99);
    String *markStr=String::createWithFormat("您在当前难度成功躲过了%d面墙壁，超过了%.1f％的人，继续努力噢！😊",this->mark,precent);
    resultLabel=Label::createWithTTF(markStr->getCString(), "fonts/hyz.ttf", 28);
    resultLabel->setPosition(WIDTH/2, HEIGHT/5*2.8);
    resultLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(resultLabel,5);
    
    
    
    auto startBtn=Sprite::create("againBtn.png");
    startBtn->setPosition(Vec2(WIDTH/3*2, HEIGHT/5*1));
    this->addChild(startBtn,1);
    
    auto homeBtn=Sprite::create("homeBtn.png");
    homeBtn->setPosition(Vec2(WIDTH/3, HEIGHT/5*1));
    this->addChild(homeBtn,1);
    
    
    auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(SJResult::start, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, startBtn);
    
    auto listener2 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener2->setSwallowTouches(true);
    listener2->onTouchBegan =CC_CALLBACK_2(SJResult::home,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, homeBtn);
    
}

bool SJResult::start(Touch *touch, Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
    auto gameVC=SJGame::createScene();
    SJGame *g=(SJGame*)gameVC->getChildByTag(88);
    g->count=this->ballCount;
    
    TransitionScene *reScene=NULL;
    reScene=CCTransitionJumpZoom::create(0.5, gameVC);
    //    gameVC:;
    Director::getInstance()->replaceScene(reScene);
    return true;
    }
    return false;
}

bool SJResult::home(cocos2d::Touch* touch, cocos2d::Event  *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
    auto gameVC=SJIndex::createScene();
    
    TransitionScene *reScene=NULL;
    reScene=CCTransitionJumpZoom::create(0.5, gameVC);
    //    gameVC:;
    Director::getInstance()->replaceScene(reScene);
        return true;
    }
    return false;}