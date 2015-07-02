//
//  SJIndexScene.cpp
//  bounceBall
//
//  Created by 陈少杰 on 15/6/20.
//
//

#include "SJIndexScene.h"
#include "SJGameScene.h"
#include "config.h"

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

    auto titleLabel=Label::createWithTTF("谁能不碰壁", "fonts/hyz.ttf", 48);
    titleLabel->setPosition(size.width/2,size.height/4*3);
    titleLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(titleLabel,1);
    
    auto startBtn=Sprite::create("startBtn.png");
    startBtn->setPosition(Vec2(size.width/2, size.height/4));
    this->addChild(startBtn,1);
    
    int coinCount = UserDefault::getInstance()->getIntegerForKey("coinCount");
    String *s=String ::createWithFormat("金币：%d",coinCount);
    auto coinLabel=Label::createWithTTF(s->getCString(), "fonts/hyz.ttf", 28);
    coinLabel->setPosition(WIDTH/2, HEIGHT/2);
    coinLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(coinLabel,5);
    
    auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener1->onTouchBegan =CC_CALLBACK_2(SJIndex::start,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, startBtn);

    return true;
}


bool SJIndex::start(Touch*touch
                    , cocos2d::Event  *event)
{auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
    auto gameVC=SJGame::createScene();
    SJGame *g=(SJGame*)gameVC->getChildByTag(88);
    g->count=2;
    
    TransitionScene *reScene=NULL;
    reScene=CCTransitionJumpZoom::create(0.5, gameVC);
//    gameVC:;
    Director::getInstance()->replaceScene(reScene);
        return true;
    }
    return false;
}