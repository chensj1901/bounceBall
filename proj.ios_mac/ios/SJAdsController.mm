//
//  SJAdsController.m
//  bounceBall
//
//  Created by 陈少杰 on 15/6/29.
//
//

#import "SJAdsController.h"
#import "config.h"
#import <AdMoGoView.h>
#import <MobClick.h>

static SJAdsController *_adsController;

@interface SJAdsController ()<AdMoGoDelegate>

@end

@implementation SJAdsController
@synthesize adMoGoView=_adMoGoView;

+(SJAdsController *)shareController{
    if(!_adsController){
        _adsController=[[SJAdsController alloc]init];
    }
    return _adsController;
}

+(void)showAdsBanner{
    SJAdsController *ads=[self shareController];
    [ads showAdsBanner];
}

+(void)removeAdsBanner{
    [[self shareController]removeAdsBanner];
}

-(AdMoGoView *)adMoGoView{
    if (!_adMoGoView) {
        _adMoGoView=[[AdMoGoView alloc]initWithAppKey:ADS_MOGO_APPKEY adType:AdViewTypeNormalBanner adMoGoViewDelegate:self adViewPointType:AdMoGoViewPointTypeDown_middle];
    }
    return _adMoGoView;
}


-(void)showAdsBanner{
    UIWindow *mainWindow=[[[UIApplication sharedApplication]windows]objectAtIndex:0];
    [mainWindow addSubview:self.adMoGoView];
}

-(void)removeAdsBanner{
    [self.adMoGoView removeFromSuperview];
    self.adMoGoView=nil;
}


#pragma mark -
#pragma mark AdMoGoDelegate delegate

- (UIViewController *)viewControllerForPresentingModalView{
    UIWindow *mainWindow=[[[UIApplication sharedApplication]windows]objectAtIndex:0];
    return mainWindow.rootViewController;
}


- (void)adMoGoDidStartAd:(AdMoGoView *)adMoGoView{
    NSLog(@"广告开始请求回调");}


- (void)adMoGoDidReceiveAd:(AdMoGoView *)adMoGoView{
    [MobClick event:@"01-01"];

    NSLog(@"%@",NSStringFromCGRect(adMoGoView.frame));
    CGRect frame=adMoGoView.frame;
    frame.origin.y=[UIScreen mainScreen].bounds.size.height-50;
    frame.origin.x=([UIScreen mainScreen].bounds.size.width-frame.size.width)/2;
    adMoGoView.frame=frame;
    NSLog(@"广告接收成功回调");
}


- (void)adMoGoDidFailToReceiveAd:(AdMoGoView *)adMoGoView didFailWithError:(NSError *)error{
    NSLog(@"广告接收失败回调");
    
}
 
- (void)adMoGoClickAd:(AdMoGoView *)adMoGoView{
    [MobClick event:@"01-02"];
    NSLog(@"点击广告回调");
}

- (void)adMoGoDeleteAd:(AdMoGoView *)adMoGoView{
    NSLog(@"广告关闭回调");
}

#pragma mark -
#pragma mark AdMoGoWebBrowserControllerUserDelegate delegate


- (void)webBrowserWillAppear{
    NSLog(@"浏览器将要展示");
}

- (void)webBrowserDidAppear{
    NSLog(@"浏览器已经展示");
}

- (void)webBrowserWillClosed{
    NSLog(@"浏览器将要关闭");
}

- (void)webBrowserDidClosed{
    NSLog(@"浏览器已经关闭");
}

-(BOOL)shouldAlertQAView:(UIAlertView *)alertView{
    return NO;
}

- (void)webBrowserShare:(NSString *)url{
    
}

@end
