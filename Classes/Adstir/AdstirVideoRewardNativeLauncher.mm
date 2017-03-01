//
//  AdStirVideoRewardNativeLauncher.m
//  AdstirIncentivizedAdSample
//
//  Created by 森田 裕司 on 2016/12/26.
//
//

#import <Foundation/Foundation.h>
#include "AppController.h"
#include "AdStirVideoRewardNativeLauncher.h"
#include "HelloWorldScene.h"
#import <AdstirAds/AdstirVideoReward.h>
#import <AdstirAds/AdstirConfig.h>

@interface AdstirVideoRewardDelegateImpl : NSObject<AdstirVideoRewardDelegate>
@property (copy) NSNumber *spot;
@property AdstirVideoRewardNativeDelegate *nativeDelegate;
@end

@implementation AdstirVideoRewardDelegateImpl

#pragma mark -
#pragma mark AdstirVideoRewardDelegate

/** 動画の読み込み完了イベントを受け取ります */
- (void)adstirVideoRewardDidLoad:(AdstirVideoReward *)videoReward
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnLoad([self.spot intValue]);
    }
}

/**
 動画の再生準備に失敗した際に呼び出されます
 */
- (void)adstirVideoReward:(AdstirVideoReward *)videoReward didFailToLoadWithError:(NSError *)error
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnFailToLoad([self.spot intValue]);
    }
}

/** 動画の再生開始イベントを受け取ります */
- (void)adstirVideoRewardDidStart:(AdstirVideoReward *)videoReward
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnStart([self.spot intValue]);
    }
}

/** 動画の再生に失敗した際に呼び出されます */
- (void)adstirVideoReward:(AdstirVideoReward *)videoReward didFailToPlaybackWithError:(NSError *) error
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnFailToStart([self.spot intValue]);
    }
}

/** 動画のインセンティブ付与の完了イベントを受け取ります */
- (void)adstirVideoRewardDidComplete:(AdstirVideoReward *)videoReward
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnComplete([self.spot intValue]);
    }
}

/** 動画再生のキャンセルイベントを受け取ります */
- (void)adstirVideoRewardDidCancel:(AdstirVideoReward *)videoReward
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnCancel([self.spot intValue]);
    }
}

/** 動画の再生が完了した際に呼び出されます */
- (void)adstirVideoRewardDidFinishPlayback:(AdstirVideoReward *)videoReward
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnFinish([self.spot intValue]);
    }
}


/** 動画再生ビューが閉じられたことを受け取ります */
- (void)adstirVideoRewardDidClose:(AdstirVideoReward *)videoReward
{
    if(self.nativeDelegate != NULL){
        self.nativeDelegate->OnClose([self.spot intValue]);
    }
}

@end


static BOOL videoRewardInitialized = NO;
static NSString *videoRewardMedia = nil;
static NSMutableDictionary *videoRewardInstances = nil;
static NSMutableDictionary *videoRewardDelegates = nil;
static NSMutableArray *videoRewardSpots = nil;

void AdstirVideoRewardNativeLauncher::setMediaUserID(const char* aMediaUserID)
{
    NSString *mediaUserID = [NSString stringWithUTF8String:aMediaUserID];
    [AdstirVideoReward setMediaUserID:mediaUserID];
}

void AdstirVideoRewardNativeLauncher::init(const char *aMedia, int *aSpots, int numberOfSpots)
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (videoRewardInstances != nil) {
            [videoRewardInstances release];
        }
        videoRewardInstances = [[NSMutableDictionary alloc] init];
        
        if (videoRewardDelegates != nil) {
            [videoRewardDelegates release];
        }
        videoRewardDelegates = [[NSMutableDictionary alloc] init];
        
        if (videoRewardMedia != nil) {
            [videoRewardMedia release];
        }
        videoRewardMedia = [[NSString stringWithUTF8String:aMedia] retain];
        
        if (videoRewardSpots != nil) {
            [videoRewardSpots release];
        }
        videoRewardSpots = [[NSMutableArray alloc] initWithCapacity:numberOfSpots];
        for (int i = 0; i < numberOfSpots; i++) {
            [videoRewardSpots addObject:@(aSpots[i])];
        }
        
        [AdstirVideoReward prepareWithMedia:videoRewardMedia spots:videoRewardSpots];
        videoRewardInitialized = YES;
    });
}

void AdstirVideoRewardNativeLauncher::load(int aSpot)
{
    if (videoRewardInitialized) {
        NSNumber *spot = @(aSpot);
        if (![videoRewardSpots containsObject:spot]) {
            return;
        }
        
        AdstirVideoReward *instance = videoRewardInstances[spot];
        if (instance == nil) {
            instance = [[[AdstirVideoReward alloc] initWithMedia:videoRewardMedia spot:aSpot] autorelease];
            videoRewardInstances[spot] = instance;
        }
        
        [instance load];
    }
}

void AdstirVideoRewardNativeLauncher::show(int aSpot)
{
    if (videoRewardInitialized) {
        NSNumber *spot = @(aSpot);
        if (![videoRewardSpots containsObject:spot]) {
            return;
        }
        
        AdstirVideoReward *instance = videoRewardInstances[spot];
        if (instance == nil) {
            return;
        }
        
        [instance show];
    }
}

bool AdstirVideoRewardNativeLauncher::canShow(int aSpot)
{
    if (videoRewardInitialized) {
        NSNumber *spot = @(aSpot);
        if (![videoRewardSpots containsObject:spot]) {
            return false;
        }
        AdstirVideoReward *instance = videoRewardInstances[spot];
        if (instance == nil) {
            return false;
        }
        return [instance canShow];
    }
    return false;
}

void AdstirVideoRewardNativeLauncher::setDelegate(AdstirVideoRewardNativeDelegate* aDelegate, int aSpot){
    if (videoRewardInitialized) {
        NSNumber *spot = @(aSpot);
        if (![videoRewardSpots containsObject:spot]) {
            return;
        }
        
        AdstirVideoReward *instance = videoRewardInstances[spot];
        if (instance == nil) {
            instance = [[[AdstirVideoReward alloc] initWithMedia:videoRewardMedia spot:aSpot] autorelease];
            videoRewardInstances[spot] = instance;
            
            AdstirVideoRewardDelegateImpl *delegate = [[[AdstirVideoRewardDelegateImpl alloc] init] autorelease];
            delegate.spot = spot;
            delegate.nativeDelegate = aDelegate;
            videoRewardDelegates[spot] = delegate;
            instance.delegate = delegate;
        }
    }
}


