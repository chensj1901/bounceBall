//
//  SJResultScene.h
//  bounceBall
//
//  Created by 陈少杰 on 15/6/27.
//
//

#ifndef __bounceBall__SJResultScene__
#define __bounceBall__SJResultScene__

#include "cocos2d.h"

class SJResult : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    cocos2d::Label *resultLabel;
    cocos2d::Label *topLabel;
    cocos2d::Label *msgLabel;
    
    void onEnterTransitionDidFinish();
    
    void start(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    int top;
    int mark;
    int ballCount;
    // implement the "static create()" method manually
    CREATE_FUNC(SJResult);
};
#endif /* defined(__bounceBall__SJResultScene__) */
