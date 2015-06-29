//
//  CCShake.h
//  bounceBall
//
//  Created by 陈少杰 on 15/6/27.
//
//

#ifndef __bounceBall__CCShake__
#define __bounceBall__CCShake__

/**
 desc:让指定控件抖动
 一个CCNode同时执行多个CCShake动作,或者一个CCShake没有完又执行一个CCShake的话就会出现问题,会出现偏移的现象!
 
 解决方案:
 1).不要同时执行多个CCShake动作.
 2.自己外部记录这个CCNode的位置,执行完成后手动setPosition();
 */

#include "CCActionInterval.h"

/**
 * 按指定频度范围内抖动[-strength_x,strength_x][-strength_y, strength_y]
 */
class CCShake : public cocos2d::ActionInterval
{
public:
    CCShake();
    
    // Create the action with a time and a strength (same in x and y)
    static CCShake* create(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static CCShake* createWithStrength(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );
    
protected:
    
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
    
    // Initial position of the shaked node
    float m_initial_x, m_initial_y;
    // Strength of the action
    float m_strength_x, m_strength_y;
};


/**
 * 线性抖动(剩余时间越短，抖动范围越小)
 */
class CCFallOffShake : public CCShake
{
public:
    CCFallOffShake();
    
    // Create the action with a time and a strength (same in x and y)
    static CCFallOffShake* create(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static CCFallOffShake* createWithStrength(float d, float strength_x, float strength_y );
    
protected:
    virtual void update(float time);
};

#endif /* defined(__bounceBall__CCShake__) */
