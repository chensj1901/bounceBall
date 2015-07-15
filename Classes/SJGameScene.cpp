//
//  SJGameScene.cpp
//  bounceBall
//
//  Created by 陈少杰 on 15/6/21.
//
//

#include "SJGameScene.h"
#include "config.h"
#include "CCShake.h"
#include "SJResultScene.h"

typedef enum {
    SJObjectTagTypeCoin=50,
    SJObjectTagTypeObstacles=40
}SJObjectTagType;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//iOS代码
#include "SJMogoForIos.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Android代码
#include "SJMogo.h"
#endif

USING_NS_CC;

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define FLOOR_OFFSET_Y 120
//#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#define FLOOR_OFFSET_Y 50*Director::getInstance()->getContentScaleFactor()+20
//#else
//#define FLOOR_OFFSET_Y 0
//#endif

//using namespace cocos2d::extension;

Scene *SJGame::createScene(){
    auto scene = Scene::create();
    auto layer=SJGame::create();
    layer->setTag(88);
    scene->addChild(layer);
    
    
    return scene;
}

void SJGame::update(float delta) {
    for (int j=0; j<things->count(); j++) {
        Sprite* obstacles=(Sprite*)things->getObjectAtIndex(j);
        obstacles->setPosition(obstacles->getPosition().x-10, obstacles->getPosition().y);
        if (obstacles->getPositionX()<100&&obstacles->getPositionX()>=90&&obstacles->getTag()==SJObjectTagTypeObstacles) {
            this->mark++;
            String *s=String::createWithFormat("当前分数：%d",this->mark);
            this->markLabel->setString(s->getCString());

            auto topMarkStr=String::createWithFormat("topMark_%d",count);
            int topMark=UserDefault::getInstance()->getIntegerForKey(topMarkStr->getCString());
            String *ss=String::createWithFormat("zui高分：%d",this->mark>topMark?this->mark:topMark);
            this->topLabel->setString(ss->getCString());
        }

        if(obstacles->getPosition().x<-10){
            obstacles->removeFromParent();
            things->removeObject(obstacles);
            j--;
        }

    }


    for (int j=0; j<floors->count(); j++) {
        Sprite*floor=(Sprite*)floors->getObjectAtIndex(j);
        floor->setPosition(Vec2(floor->getPositionX()-10,floor->getPositionY()));

        if (floor->boundingBox().getMaxX()<=0) {
            floor->setPosition(Vec2(floor->getPositionX()+floor->boundingBox().size.width*4,floor->getPositionY()));
        }
    }

    for (int ballIndex=0; ballIndex<this->count; ballIndex++) {

    Sprite *ball=(Sprite*)this->balls->getObjectAtIndex(ballIndex);

    float padding=(HEIGHT-100)/count;

    bool shouldShowCoin=false;
    for (int shoundTime=3; shoundTime<10; shoundTime++) {
        if (timeStep==nextPlayStep[ballIndex]-5*shoundTime) {
            shouldShowCoin=true;
        }
    }

    if (shouldShowCoin&& CCRANDOM_0_1()<0.3) {
        //金币
        auto obstacles=Sprite::create("coin.png");
        this->addChild(obstacles,5);
        cocos2d::Size size = obstacles->getBoundingBox().size;
        obstacles->setPosition(Vec2(WIDTH,FLOOR_OFFSET_Y+ballIndex*padding+size.height/2+40));
        obstacles->setTag(SJObjectTagTypeCoin);
        things->addObject(obstacles);
    }

    if (timeStep==nextPlayStep[ballIndex]) {//障碍物
        nextPlayStep[ballIndex]+=70+CCRANDOM_0_1()*80*(CCRANDOM_0_1()<0.5?1:2);
        auto obstacles=Sprite::createWithTexture(thingsBatch->getTexture());
        thingsBatch->addChild(obstacles);
        obstacles->setScale(1+0.5*CCRANDOM_0_1(), 3.5+2.5*CCRANDOM_0_1());
        cocos2d::Size size = obstacles->getBoundingBox().size;
        obstacles->setPosition(Vec2(WIDTH,FLOOR_OFFSET_Y+ballIndex*padding+size.height/2));
        obstacles->setTag(SJObjectTagTypeObstacles);
        things->addObject(obstacles);
    }


        for (int j=0; j<things->count(); j++) {
            Sprite* obstacles=(Sprite*)things->getObjectAtIndex(j);

            if(obstacles->getBoundingBox().intersectsRect(ball->getBoundingBox())){

                if (obstacles->getTag()==SJObjectTagTypeObstacles) {
                    this->unscheduleUpdate();
                    CCShake *shake=CCShake::create(count*0.5+2, 20);
                    CallFunc *func=CallFunc::create(this, callfunc_selector(SJGame::gameOver));
                    Sequence *seq=Sequence::create(shake,func, NULL);
                    this->runAction(seq);

                    for (int ballI=0; ballI<balls->count(); ballI++) {
                        Sprite *ballSpriteI=(Sprite*)this->balls->getObjectAtIndex(ballI);
                        CCActionInterval *moveTo=MoveTo::create(1, Vec2(CCRANDOM_0_1()*200,-100));
                        CCActionInterval * easeExponentialIn= CCEaseExponentialIn::create(moveTo);
                        CCActionInterval * deyal=CCDelayTime::create(ballI*1);
                        Sequence *seqI=Sequence::create(deyal,easeExponentialIn, NULL);
                        ballSpriteI->runAction(seqI);
                    }
                }else{
                    things->removeObject(obstacles);
                    j--;

//                    auto moveTo=MoveTo::create(0.5, this->coinLabel->getPosition());
//                    auto easeExponentialIn= CCEaseExponentialIn::create(moveTo);
//                    auto func=CallFunc::create([&]{
                        obstacles->removeFromParent();
                        coin++;
                        String *s=String::createWithFormat("金币：%d",this->coin);
                        this->coinLabel->setString(s->getCString());
//                    });


//                    Sequence *seqI=Sequence::create(easeExponentialIn,func,NULL);
//                    obstacles->runAction(seqI);


                }

            }
        }

        CCFloat *vy0=(CCFloat*)this->balls_Vy0->getObjectAtIndex(ballIndex);
        float ball_Vy0=vy0->getValue();

        if (ball_Vy0!=0||ball->getPosition().y!=FLOOR_OFFSET_Y+ballIndex*padding+ball->getBoundingBox().size.height/2) {
            ball->setPosition(ball->getPosition().x,ball->getPosition().y+ball_Vy0);
            ball_Vy0-=0.5;
            //        CCLog("%f",this->ball->getPosition().y);
            if (ball_Vy0<0&&ball->getPosition().y<=FLOOR_OFFSET_Y+ballIndex*padding+ball->getBoundingBox().size.height/2) {
                ball_Vy0=0;
                ball->setPosition(ball->getPosition().x,FLOOR_OFFSET_Y+ballIndex*padding+ball->getBoundingBox().size.height/2);
            }
            this->balls_Vy0->setObject(CCFloat::create(ball_Vy0), ballIndex);
        }
    }
    timeStep++;
}

void SJGame::gameOver(){
    auto resultVC=SJResult::createScene();

    TransitionScene *reScene=NULL;
    reScene=CCTransitionJumpZoom::create(0.5, resultVC);
    //    gameVC:;
    auto topMarkStr=String::createWithFormat("topMark_%d",count);

    if (this->mark>UserDefault::getInstance()->getIntegerForKey(topMarkStr->getCString())) {
        UserDefault::getInstance()->setIntegerForKey(topMarkStr->getCString(), this->mark);
    }

    int coinHistory=UserDefault::getInstance()->getIntegerForKey("coinCount");
    UserDefault::getInstance()->setIntegerForKey("coinCount", this->coin+coinHistory);

    SJResult *result=(SJResult*)resultVC->getChildByTag(88);
    result->top=UserDefault::getInstance()->getIntegerForKey(topMarkStr->getCString());
    result->mark=this->mark;
    result->ballCount=this->count;
    Director::getInstance()->replaceScene(reScene);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    MOGOAdForIos::hideBanner();
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android代码
    MOGOAd::hideBanner();
#endif
}

bool SJGame::init(){
    if (!Layer::init()) {
        return false;
    }
    this->count=1;
    
    timeStep=0;
    auto layer=LayerColor::create(Color4B(239, 241, 224, 255));
    this->addChild(layer,0);
    
    return true;
}

void SJGame::onEnterTransitionDidFinish(){
    
    for (int i=0; i<200; i++) {
        nextPlayStep[i]=50+CCRANDOM_0_1()*100;
    }

    things=new Array;
    things->init();

    balls=new Array;
    balls->init();

    balls_Vy0=new Array;
    balls_Vy0->init();

    floors=new Array;
    floors->init();

    thingsBatch=SpriteBatchNode::create("blackBlock.png");

    this->addChild(thingsBatch);

    auto listener1 = EventListenerTouchAllAtOnce::create();//创建一个触摸监听
    listener1->onTouchesBegan =CC_CALLBACK_2(SJGame::onTouchesBegan,this);

    auto dispatcher=Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    for (int i=0; i<this->count; i++) {
        float padding=(HEIGHT-100)/count;

        Sprite* ball=Sprite::create("ball.png");
        ball->setPosition(100, FLOOR_OFFSET_Y+i*padding+ball->getBoundingBox().size.height/2);

        this->addChild(ball);

        this->balls->addObject(ball);
        this->balls_Vy0->addObject(CCFloat::create(0));

        Sprite* floor=NULL;

        for (int floorCount=0; floorCount<4; floorCount++)
        {
                float maxX=floor!=NULL?floor->getBoundingBox().getMaxX():0;
                floor=Sprite::create("floor.png");
                floor->setPosition(maxX+floor->getBoundingBox().size.width/2, FLOOR_OFFSET_Y+i*padding-floor->getBoundingBox().size.height/2);
                this->addChild(floor);

                floors->addObject(floor);
        }
    }

    markLabel=Label::createWithTTF("当前分数：0", "fonts/hyz.ttf", 28);
    markLabel->setPosition(WIDTH/5, HEIGHT-20);
    markLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(markLabel,5);

    auto topMarkStr=String::createWithFormat("topMark_%d",count);
    int topMark=UserDefault::getInstance()->getIntegerForKey(topMarkStr->getCString());
    String *s=String::createWithFormat("zui高分：%d",topMark);
    topLabel=Label::createWithTTF(s->getCString(), "fonts/hyz.ttf", 28);
    topLabel->setPosition(WIDTH/2, HEIGHT-20);
    topLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(topLabel,5);


    coinLabel=Label::createWithTTF("金币：0", "fonts/hyz.ttf", 28);
    coinLabel->setPosition(WIDTH/5*4, HEIGHT-20);
    coinLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(coinLabel,5);

    this->scheduleUpdate();
//    ;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    MOGOAdForIos::showBanner();
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android代码
    MOGOAd::showBanner();
#endif
    
}

//void SJGame::onEnterTransitionDidFinish(){
//}

void SJGame::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    float padding=(HEIGHT-100)/count;
    for ( auto &item: touches )
    {
        auto touch = item;
        cocos2d::Point touchPoint=touch->getLocation();
        int ballIndex= (touchPoint.y-FLOOR_OFFSET_Y)/((HEIGHT-100)/count);

        Sprite *ball=(Sprite*)this->balls->getObjectAtIndex(ballIndex);

        CCFloat *ballVy0=(CCFloat*)this->balls_Vy0->getObjectAtIndex(ballIndex);
        float canResY=FLOOR_OFFSET_Y+10+ballIndex*padding+ball->getBoundingBox().size.height/2;
        if (ballVy0->getValue()<FLOOR_OFFSET_Y&&ball->getPosition().y<canResY)
        {
            this->balls_Vy0->setObject(CCFloat::create(11), ballIndex);
        }
    }
}
