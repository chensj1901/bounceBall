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
    msgLabel->setPosition(WIDTH/2, HEIGHT/5);
    msgLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(msgLabel,5);
    
    String *topStr=String::createWithFormat("zui高分：%d",this->top);
    topLabel=Label::createWithTTF(topStr->getCString(), "fonts/hyz.ttf", 28);
    topLabel->setPosition(WIDTH/2, HEIGHT/5*2);
    topLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(topLabel,5);
    
    String *markStr=String::createWithFormat("本局得数：%d",this->mark);
    resultLabel=Label::createWithTTF(markStr->getCString(), "fonts/hyz.ttf", 28);
    resultLabel->setPosition(WIDTH/2, HEIGHT/5*3);
    resultLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(resultLabel,5);
    
    
    
    auto startBtn=Sprite::create("startBtn.png");
    startBtn->setPosition(Vec2(WIDTH/2, HEIGHT/5*4));
    this->addChild(startBtn,1);
    
    
    auto listener1 = EventListenerTouchAllAtOnce::create();//创建一个触摸监听
    listener1->onTouchesBegan =CC_CALLBACK_2(SJResult::start,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, startBtn);
    
}

void SJResult::start(const std::vector<Touch*>& touches, Event  *event)
{
    auto gameVC=SJGame::createScene();
    SJGame *g=(SJGame*)gameVC->getChildByTag(88);
    g->count=this->ballCount;
    
    TransitionScene *reScene=NULL;
    reScene=CCTransitionJumpZoom::create(0.5, gameVC);
    //    gameVC:;
    Director::getInstance()->replaceScene(reScene);
}