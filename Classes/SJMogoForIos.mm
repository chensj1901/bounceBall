//
//  SJMogoForIos.cpp
//  bounceBall
//
//  Created by 陈少杰 on 15/7/15.
//
//

#include "SJMogoForIos.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "SJAdsController.h"
#import <UIKit/UIKit.h>
#endif

MOGOAdForIos::MOGOAdForIos(){}
MOGOAdForIos::~MOGOAdForIos(){}

void MOGOAdForIos::showBanner(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) //􏱜􏱝􏱞􏱟􏰤􏰥􏰌 Android 􏱠􏰵
    [SJAdsController showAdsBanner];
#endif
}

void MOGOAdForIos::hideBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) //􏱜􏱝􏱞􏱟􏰤􏰥􏰌 Android 􏱠􏰵
    [SJAdsController removeAdsBanner];
#endif
}



void MOGOAdForIos::rankApp()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) //􏱜􏱝􏱞􏱟􏰤􏰥􏰌 Android 􏱠􏰵
//    [MobClick event:@"02-01"];
    NSString *str;
    if (([[[UIDevice currentDevice]systemVersion]doubleValue])>=7.0) {
        str=[NSString stringWithFormat: @"http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?id=%@&pageNumber=0&sortOrdering=2&type=Purple+Software&mt=8", @"1013794378"];
    }else{
        str = [NSString stringWithFormat: @"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@", @"1013794378"];
    }
    
    [[UIApplication sharedApplication]openURL:[NSURL URLWithString:str]];
#endif
}