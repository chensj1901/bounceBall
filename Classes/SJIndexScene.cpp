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
#include "SJLanguage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "SJMogoForIos.h"
#else
#endif

USING_NS_CC;
//using namespace cocos2d::extension;

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
    
    cocos2d::Size size = Director::getInstance()->getWinSize();

    auto layer=LayerColor::create(Color4B(239, 241, 224, 255));
    this->addChild(layer,0);

//    auto startBtn=ControlButton::create();
//    startBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SJIndex::start), Control::EventType::TOUCH_UP_INSIDE);
    ;
    auto titleLabel=Label::createWithTTF(LocalizedCStringByKey("appName"), "fonts/hyz.ttf", 48);
    titleLabel->setPosition(size.width/2,size.height/4*3);
    titleLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(titleLabel,1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    auto commenUsBtn=Sprite::create("commentUs.png");
    commenUsBtn->setPosition(Vec2(size.width/2, size.height/12*5));
    this->addChild(commenUsBtn,1);


    auto comentListen = EventListenerTouchOneByOne::create();//创建一个触摸监听
    comentListen->onTouchBegan =CC_CALLBACK_2(SJIndex::commentUs,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(comentListen, commenUsBtn);

#else
    //Android代码
#endif


    auto startBtn=Sprite::create("easy.png");
    startBtn->setPosition(Vec2(size.width/5*1, size.height/3));
    startBtn->setTag(2);
    this->addChild(startBtn,1);

    auto startBtn2=Sprite::create("middle.png");
    startBtn2->setPosition(Vec2(size.width/5*4, size.height/3));
    startBtn2->setTag(3);
    this->addChild(startBtn2,1);

    auto startBtn3=Sprite::create("hard.png");
    startBtn3->setPosition(Vec2(size.width/10*3, size.height/6));
    startBtn3->setTag(4);
    this->addChild(startBtn3,1);


    bool  isVeryHardUnLock = UserDefault::getInstance()->getBoolForKey("isVeryHardUnLock");
    auto startBtn4=Sprite::create(isVeryHardUnLock?"veryHard.png":"veryHard_lock.png");
    startBtn4->setPosition(Vec2(size.width/10*7., size.height/6));
    startBtn4->setTag(5);
    this->addChild(startBtn4,1);

    int coinCount = UserDefault::getInstance()->getIntegerForKey("coinCount");
    String *s=String ::createWithFormat("金币：%d",coinCount);

    coinLabel=Label::createWithTTF(s->getCString(), "fonts/hyz.ttf", 28);
    coinLabel->setPosition(WIDTH/2, HEIGHT/8*5);
    coinLabel->setTextColor(ccc4(0, 0, 0, 255));
    coinLabel->setTag(18);

    this->addChild(coinLabel,5);

    alertBox=Sprite::create("alertBox.png");
    alertBox->setPosition(WIDTH/2, HEIGHT+HEIGHT/2);
    this->addChild(alertBox,99);

    auto msgStr=String::createWithFormat("是否使用1000金币解锁关卡？\n你现在拥有金币%d个",coinCount);
    auto msgLabel=Label::createWithTTF(msgStr->getCString(), "fonts/hyz.ttf", 28);
    msgLabel->setPosition(alertBox->getBoundingBox().size.width/2, alertBox->getBoundingBox().size.height-100);
    msgLabel->setTextColor(ccc4(0, 0, 0, 255));
    alertBox->addChild(msgLabel,5);

    auto okBtn=Sprite::create("okBtn.png");
    okBtn->setPosition(120,50);
    alertBox->addChild(okBtn);

    auto cancelBtn=Sprite::create("cancelBtn.png");
    cancelBtn->setPosition(300,50);
    alertBox->addChild(cancelBtn);


    auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener1->onTouchBegan =CC_CALLBACK_2(SJIndex::start,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, startBtn);


    auto listener2 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener2->onTouchBegan =CC_CALLBACK_2(SJIndex::start,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, startBtn2);

    auto listener3 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener3->onTouchBegan =CC_CALLBACK_2(SJIndex::start,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, startBtn3);

    auto listener4 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener4->onTouchBegan =CC_CALLBACK_2(SJIndex::start,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, startBtn4);

    auto okListener = EventListenerTouchOneByOne::create();//创建一个触摸监听
    okListener->onTouchBegan =CC_CALLBACK_2(SJIndex::ok,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(okListener, okBtn);


    auto cancelListen = EventListenerTouchOneByOne::create();//创建一个触摸监听
    cancelListen->onTouchBegan =CC_CALLBACK_2(SJIndex::cancel,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cancelListen, cancelBtn);


//    UserDefault::getInstance()->setBoolForKey("isVeryHardUnLock", true);
    return true;
}


bool SJIndex::start(Touch*touch
                    , cocos2d::Event  *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    cocos2d::Size s = target->getContentSize();
    cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {
    int tag=target->getTag();


    bool  isVeryHardUnLock = UserDefault::getInstance()->getBoolForKey("isVeryHardUnLock");

    if(tag==5&&!isVeryHardUnLock){
        auto move=MoveTo::create(0.3, Vec2(WIDTH/2, HEIGHT/3));
        auto jump=JumpTo::create(0.5, Vec2(WIDTH/2, HEIGHT/2), HEIGHT/6, 1);
        auto t=EaseIn::create(jump, 0.5);
        auto all=Sequence::create(move,t, NULL);
        alertBox->runAction(all);

        return false;
    }

    auto gameVC=SJGame::createScene();
    SJGame *g=(SJGame*)gameVC->getChildByTag(88);
    g->count=tag;

    TransitionScene *reScene=NULL;
    reScene=CCTransitionJumpZoom::create(0.5, gameVC);
//    gameVC:;
    Director::getInstance()->replaceScene(reScene);
        return true;
    }
    return false;
}

bool SJIndex::commentUs(cocos2d::Touch *touch, cocos2d::Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    cocos2d::Size s = target->getContentSize();
    cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //iOS代码
    MOGOAdForIos::rankApp();
    return true;
#else
        //Android代码
#endif

    }
    return false;
}


bool SJIndex::cancel(cocos2d::Touch *touch, cocos2d::Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    cocos2d::Size s = target->getContentSize();
    cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {

        auto move=MoveTo::create(0.3, Vec2(WIDTH/2, HEIGHT+HEIGHT/2));
        auto t=EaseOut::create(move, 0.5);
        alertBox->runAction(t);
    }
    return false;
}


bool SJIndex::ok(cocos2d::Touch *touch, cocos2d::Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    cocos2d::Size s = target->getContentSize();
    cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {

        auto move=MoveTo::create(0.3, Vec2(WIDTH/2, HEIGHT+HEIGHT/2));
        auto t=EaseOut::create(move, 0.5);
        alertBox->runAction(t);

        int coinCount = UserDefault::getInstance()->getIntegerForKey("coinCount");
        if (coinCount>1000) {
            alert("关卡解锁成功");
            coinCount-=1000;
            UserDefault::getInstance()->setIntegerForKey("coinCount", coinCount);
            UserDefault::getInstance()->setBoolForKey("isVeryHardUnLock", true);
            auto cStr=String::createWithFormat("金币：%d",coinCount);
            coinLabel->setString(cStr->getCString());
            Sprite* btn4=(Sprite*)this->getChildByTag(5);
            btn4->setTexture("veryHard.png");

        }else{
            alert("金币不足");
        }

    }
    return false;
}


void alert(const std::string &text){
    
    auto title=Label::create(text,"fonts/hyz.ttf", 28);
    cocos2d::Size titleSize=title->getBoundingBox().size;
    title->setPosition((titleSize.width+40)/2, (titleSize.height+40)/2);

    auto box=Sprite::create();
    box->setTextureRect(cocos2d::Rect(0, 0, titleSize.width+40, titleSize.height+40));
    box->setPosition(WIDTH/2, HEIGHT/8*3+100);
    box->setColor(ccc3(0, 0, 0));
    box->addChild(title);

    title->setScaleX(1./box->getScaleX());
    title->setScaleY(1./box->getScaleY());

    auto scene = Director::getInstance()->getRunningScene();
    scene->addChild(box,100);

    auto fade = FadeIn::create(1);
    auto delay = DelayTime::create(2);
    auto fadeOut = FadeOut::create(1);
    auto seque = Sequence::create(fade,delay,fadeOut,NULL);

    auto fade2 = FadeIn::create(1);
    auto delay2 = DelayTime::create(2);
    auto fadeOut2 = FadeOut::create(1);
    auto seque2 = Sequence::create(fade2,delay2,fadeOut2,NULL);

    box->runAction(seque);
    title->runAction(seque2);
    
    
}
