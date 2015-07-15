//
//  SJMogo.cpp
//  bounceBall
//
//  Created by 陈少杰 on 15/7/14.
//
//

#include "SJMogo.h"

MOGOAd::MOGOAd(){}
MOGOAd::~MOGOAd(){}

void MOGOAd::showBanner(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //􏱜􏱝􏱞􏱟􏰤􏰥􏰌 Android 􏱠􏰵
    JniMethodInfo showBanner;
    bool isHave = JniHelper::getStaticMethodInfo(showBanner,"org/cocos2dx/cpp/AppActivity","showBannerStatic","()V");
    if (!isHave) {
        
    }else{
        showBanner.env->CallStaticVoidMethod(showBanner.classID, showBanner.methodID);
    }
    #endif
}

void MOGOAd::hideBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //􏱜􏱝􏱞􏱟􏰤􏰥􏰌 Android 􏱠􏰵
    JniMethodInfo hideBanner;

    bool isHave = JniHelper::getStaticMethodInfo(hideBanner,"org/cocos2dx/cpp/AppActivity","hideBannerStatic","()V");
    if (!isHave) {
    }else{
        hideBanner.env->CallStaticVoidMethod(hideBanner.classID, hideBanner.methodID);
    }
#endif
}
