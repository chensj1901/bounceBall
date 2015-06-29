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

USING_NS_CC;

#define FLOOR_OFFSET_Y 60

using namespace cocos2d::extension;

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
        
        if (obstacles->getPositionX()<100&&obstacles->getPositionX()>=90) {
            this->mark++;
            String *s=String::createWithFormat("当前分数：%d",this->mark);
            this->markLabel->setString(s->getCString());
            
            int topMark=UserDefault::getInstance()->getIntegerForKey("topMark");
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
        
    float padding=HEIGHT/count;
    if (timeStep==nextPlayStep[ballIndex]) {
        nextPlayStep[ballIndex]+=70+CCRANDOM_0_1()*80*(CCRANDOM_0_1()<0.5?1:2);
        auto obstacles=Sprite::createWithTexture(thingsBatch->getTexture());
        thingsBatch->addChild(obstacles);
        obstacles->setScale(1+1*CCRANDOM_0_1(), 5+5*CCRANDOM_0_1());
        Size size = obstacles->getBoundingBox().size;
        obstacles->setPosition(Vec2(WIDTH,FLOOR_OFFSET_Y+ballIndex*padding+size.height/2));
        things->addObject(obstacles);
    }
        
        
        for (int j=0; j<things->count(); j++) {
            Sprite* obstacles=(Sprite*)things->getObjectAtIndex(j);
            
            if(obstacles->getBoundingBox().intersectsRect(ball->getBoundingBox())){
//                obstacles->removeFromParent();
//                things->removeObject(obstacles);
//                j--;
                
                this->unscheduleUpdate();
                
                CCShake *shake=CCShake::create(count*0.5+2, 20);
                CallFunc *func=CallFunc::create(this, callfunc_selector(SJGame::gameOver));
                Sequence *seq=Sequence::create(shake,func, NULL);
                this->runAction(seq);
                
                
//                obstacles->runAction(moveTo);
                for (int ballI=0; ballI<balls->count(); ballI++) {
                    Sprite *ballSpriteI=(Sprite*)this->balls->getObjectAtIndex(ballI);
                    CCActionInterval *moveTo=MoveTo::create(1, Vec2(CCRANDOM_0_1()*200,-100));
                    CCActionInterval * easeExponentialIn= CCEaseExponentialIn::create(moveTo);
                    CCActionInterval * deyal=CCDelayTime::create(ballI*1);
                    Sequence *seqI=Sequence::create(deyal,easeExponentialIn, NULL);
                    ballSpriteI->runAction(seqI);
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
    if (this->mark>UserDefault::getInstance()->getIntegerForKey("topMark")) {
        UserDefault::getInstance()->setIntegerForKey("topMark", this->mark);
    }
    SJResult *result=(SJResult*)resultVC->getChildByTag(88);
    result->top=UserDefault::getInstance()->getIntegerForKey("topMark");
    result->mark=this->mark;
    result->ballCount=this->count;
    Director::getInstance()->replaceScene(reScene);
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
        nextPlayStep[i]=100+CCRANDOM_0_1()*100;
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
        float padding=HEIGHT/count;
        
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
    markLabel->setPosition(WIDTH/2, HEIGHT-100);
    markLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(markLabel,5);
    
    int topMark=UserDefault::getInstance()->getIntegerForKey("topMark");
    String *s=String::createWithFormat("zui高分：%d",topMark);
    
    topLabel=Label::createWithTTF(s->getCString(), "fonts/hyz.ttf", 28);
    topLabel->setPosition(100, HEIGHT-100);
    topLabel->setTextColor(ccc4(0, 0, 0, 255));
    this->addChild(topLabel,5);
    
    this->scheduleUpdate();
    
}

//void SJGame::onEnterTransitionDidFinish(){
//}

void SJGame::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    float padding=HEIGHT/count;
    for ( auto &item: touches )
    {
        auto touch = item;
        Point touchPoint=touch->getLocation();
        int ballIndex=touchPoint.y/(HEIGHT/count);
        
        Sprite *ball=(Sprite*)this->balls->getObjectAtIndex(ballIndex);
        
        CCFloat *ballVy0=(CCFloat*)this->balls_Vy0->getObjectAtIndex(ballIndex);
        if (ballVy0->getValue()<FLOOR_OFFSET_Y&&ball->getPosition().y<FLOOR_OFFSET_Y+10+ballIndex*padding+ball->getBoundingBox().size.height/2) {
            this->balls_Vy0->setObject(CCFloat::create(13), ballIndex);
        }
    }
}