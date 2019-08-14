//
//  AdstirPlugin.cpp
//
//  Created by 森田 裕司 on 2019/07/25.
//  Copyright © 2019 United Inc. All rights reserved.
//

#include <stdio.h>

#include "AdstirPlugin.h"
#include <unordered_map>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define VIDEO_ADS_CLASS_NAME    "com/ad_stir/cocos2dx/AdstirVideoAdsPlugin"
#define VIDEO_REWARD_CLASS_NAME "com/ad_stir/cocos2dx/AdstirVideoRewardPlugin"
#define INTERSTITIAL_CLASS_NAME "com/ad_stir/cocos2dx/AdstirInterstitialPlugin"

std::unordered_map<int, Adstir::VideoRewardDelegate*> rewardDelegateMap;
std::unordered_map<int, Adstir::InterstitialDelegate*> interstitialDelegateMap;

extern "C"
{
    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnLoad(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnLoad(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnFailToLoad(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnFailToLoad(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnStart(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnStart(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnFailToStart(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnFailToStart(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnComplete(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnComplete(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnCancel(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnCancel(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnFinish(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnFinish(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirVideoRewardListenerImpl_OnClose(JNIEnv* env, jobject thiz, jint spot) {
        if(rewardDelegateMap[spot]) {
            rewardDelegateMap[spot]->OnClose(spot);
        }

        return;
    }

    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirInterstitialListenerImpl_OnLoad(JNIEnv* env, jobject thiz, jint spot) {
        if(interstitialDelegateMap[spot]) {
            interstitialDelegateMap[spot]->OnLoad(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirInterstitialListenerImpl_OnFailToLoad(JNIEnv* env, jobject thiz, jint spot) {
        if(interstitialDelegateMap[spot]) {
            interstitialDelegateMap[spot]->OnFailToLoad(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirInterstitialListenerImpl_OnStart(JNIEnv* env, jobject thiz, jint spot) {
        if(interstitialDelegateMap[spot]) {
            interstitialDelegateMap[spot]->OnStart(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirInterstitialListenerImpl_OnFailToStart(JNIEnv* env, jobject thiz, jint spot) {
        if(interstitialDelegateMap[spot]) {
            interstitialDelegateMap[spot]->OnFailToStart(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_cocos2dx_AdstirInterstitialListenerImpl_OnClose(JNIEnv* env, jobject thiz, jint spot) {
        if(interstitialDelegateMap[spot]) {
            interstitialDelegateMap[spot]->OnClose(spot);
        }
        
        return;
    }
}


void Adstir::VideoAds::setMediaUserID(const char* aMediaUserID)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, VIDEO_ADS_CLASS_NAME, "setMediaUserID", "(Ljava/lang/String;)V")) {
        jstring str = t.env->NewStringUTF(aMediaUserID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, str);
        t.env->DeleteLocalRef(str);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Adstir::VideoAds::init(const char *aMedia, int *aSpots, int numberOfSpots)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, VIDEO_ADS_CLASS_NAME, "init", "(Ljava/lang/String;[I)V")) {
        jstring str = t.env->NewStringUTF(aMedia);
        
        jintArray spots = t.env->NewIntArray(numberOfSpots);
        if (spots == NULL) {
            return;
        }
        t.env->SetIntArrayRegion(spots, 0, numberOfSpots, aSpots);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, str, spots);

        t.env->DeleteLocalRef(spots);
        t.env->DeleteLocalRef(str);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Adstir::VideoReward::load(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, VIDEO_REWARD_CLASS_NAME, "load", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Adstir::VideoReward::show(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, VIDEO_REWARD_CLASS_NAME, "show", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool Adstir::VideoReward::canShow(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, VIDEO_REWARD_CLASS_NAME, "canShow", "(I)Z")) {
        jboolean canShow = (jboolean) t.env->CallStaticBooleanMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
        return (bool)canShow;
    }
    
    return false;
}


void Adstir::VideoReward::setDelegate(Adstir::VideoRewardDelegate* delegate, int aSpot)
{
    rewardDelegateMap[aSpot] = delegate;
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, VIDEO_REWARD_CLASS_NAME, "setDelegate", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}


void Adstir::Interstitial::load(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, INTERSTITIAL_CLASS_NAME, "load", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Adstir::Interstitial::show(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, INTERSTITIAL_CLASS_NAME, "show", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool Adstir::Interstitial::canShow(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, INTERSTITIAL_CLASS_NAME, "canShow", "(I)Z")) {
        jboolean canShow = (jboolean) t.env->CallStaticBooleanMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
        return (bool)canShow;
    }

    return false;
}


void Adstir::Interstitial::setDelegate(Adstir::InterstitialDelegate* delegate, int aSpot)
{
    interstitialDelegateMap[aSpot] = delegate;
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, INTERSTITIAL_CLASS_NAME, "setDelegate", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}
