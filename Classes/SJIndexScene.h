//
//  SJIndexScene.h
//  bounceBall
//
//  Created by 陈少杰 on 15/6/20.
//
//

#ifndef __bounceBall__SJIndexScene__
#define __bounceBall__SJIndexScene__

#include "cocos2d.h"
//#include "GUI/CCControlExtension/CCControlExtensions.h"


class SJIndex : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    bool start(cocos2d::Touch*touch
               , cocos2d::Event  *event);
    
    bool cancel(cocos2d::Touch*touch
               , cocos2d::Event  *event);
    
    bool ok(cocos2d::Touch*touch
            , cocos2d::Event  *event);
    
    bool commentUs(cocos2d::Touch*touch
            , cocos2d::Event  *event);
    
    cocos2d::Sprite* alertBox;
    cocos2d::Label* coinLabel;
    // implement the "static create()" method manually
    CREATE_FUNC(SJIndex);
};

void alert(const std::string &text);
#endif /* defined(__bounceBall__SJIndexScene__) */
