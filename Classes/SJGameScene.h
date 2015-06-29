//
//  SJGameScene.h
//  bounceBall
//
//  Created by 陈少杰 on 15/6/21.
//
//

#ifndef __bounceBall__SJGameScene__
#define __bounceBall__SJGameScene__

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlExtensions.h"


class SJGame : public cocos2d::Layer
{
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float delta);
    void onEnterTransitionDidFinish();
//    void onEnter();
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void gameOver();
    long count;
protected:
    int mark;
    int timeStep;
    int nextPlayStep[200];
    cocos2d::Array *things;
    cocos2d::Array *balls;
    cocos2d::Array *balls_Vy0;
    cocos2d::Array *floors;
    cocos2d::SpriteBatchNode *thingsBatch;
    cocos2d::Label *markLabel;
    cocos2d::Label *topLabel;
    // implement the "static create()" method manually

    CREATE_FUNC(SJGame);
};

#endif /* defined(__bounceBall__SJGameScene__) */
