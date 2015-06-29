//
//  SJIndexScene.cpp
//  bounceBall
//
//  Created by 陈少杰 on 15/6/20.
//
//

#include "SJIndexScene.h"
#include "SJGameScene.h"

USING_NS_CC;
using namespace cocos2d::extension;

Scene *SJIndex::createScene(){
    auto scene = Scene::create();
    auto layer=SJIndex::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool SJIndex::init(){
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    
    auto layer=LayerColor::create(Color4B(239, 241, 224, 255));
    this->addChild(layer,0);
    
//    auto startBtn=ControlButton::create();
//    startBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SJIndex::start), Control::EventType::TOUCH_UP_INSIDE);

    auto startBtn=Sprite::create("startBtn.png");
    startBtn->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(startBtn,1);
    
    
    auto listener1 = EventListenerTouchAllAtOnce::create();//创建一个触摸监听
    listener1->onTouchesBegan =CC_CALLBACK_2(SJIndex::start,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, startBtn);

    return true;
}


void SJIndex::start(const std::vector<Touch*>& touches, Event  *event)
{
    auto gameVC=SJGame::createScene();
    SJGame *g=(SJGame*)gameVC->getChildByTag(88);
    g->count=2;
    
    TransitionScene *reScene=NULL;
    reScene=CCTransitionJumpZoom::create(0.5, gameVC);
//    gameVC:;
    Director::getInstance()->replaceScene(reScene);
}