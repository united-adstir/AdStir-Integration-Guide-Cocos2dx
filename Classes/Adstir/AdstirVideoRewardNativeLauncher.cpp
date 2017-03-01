//
//  AdstirVideoRewardNativeLauncher.cpp
//  AdstirIncentivizedAdSample
//
//  Created by 森田 裕司 on 2016/12/26.
//
//

#include <stdio.h>

#include "AdstirVideoRewardNativeLauncher.h"
#include <unordered_map>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define CLASS_NAME "com/ad_stir/videoreward/cocos2dx/AdstirVideoRewardNativeLauncher"


std::unordered_map<int, AdstirVideoRewardNativeDelegate*> delegateMap;

extern "C"
{
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnLoad(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnLoad(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnFailToLoad(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnFailToLoad(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnStart(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnStart(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnFailToStart(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnFailToStart(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnComplete(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnComplete(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnCancel(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnCancel(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnFinish(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnFinish(spot);
        }
        
        return;
    }
    
    JNIEXPORT void JNICALL Java_com_ad_1stir_videoreward_cocos2dx_AdstirVideoRewardListenerImpl_OnClose(JNIEnv* env, jobject thiz, jint spot) {
        if(delegateMap[spot]) {
            delegateMap[spot]->OnClose(spot);
        }
        
        return;
    }
}


void AdstirVideoRewardNativeLauncher::setMediaUserID(const char* aMediaUserID)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setMediaUserID", "(Ljava/lang/String;)V")) {
        jstring str = t.env->NewStringUTF(aMediaUserID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, str);
        t.env->DeleteLocalRef(str);
        t.env->DeleteLocalRef(t.classID);
    }
}

void AdstirVideoRewardNativeLauncher::init(const char *aMedia, int *aSpots, int numberOfSpots)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "init", "(Ljava/lang/String;[I)V")) {
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

void AdstirVideoRewardNativeLauncher::load(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "load", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}

void AdstirVideoRewardNativeLauncher::show(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "show", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool AdstirVideoRewardNativeLauncher::canShow(int aSpot)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "canShow", "(I)Z")) {
        jboolean canShow = (jboolean) t.env->CallStaticBooleanMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
        return (bool)canShow;
    }
    
    return false;
}


void AdstirVideoRewardNativeLauncher::setDelegate(AdstirVideoRewardNativeDelegate* delegate, int aSpot)
{
    delegateMap[aSpot] = delegate;
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setDelegate", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aSpot);
        t.env->DeleteLocalRef(t.classID);
    }
}
