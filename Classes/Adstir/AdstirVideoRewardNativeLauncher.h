//
//  AdstirVideoRewardNativeLauncher.h
//  AdstirIncentivizedAdSample
//
//  Created by 森田 裕司 on 2016/12/26.
//
//

#ifndef AdstirVideoRewardNativeLauncher_h
#define AdstirVideoRewardNativeLauncher_h

class AdstirVideoRewardNativeDelegate
{
public:
    virtual void OnLoad(int spot){};
    virtual void OnFailToLoad(int spot){};
    virtual void OnStart(int spot){};
    virtual void OnFailToStart(int spot){};
    virtual void OnComplete(int spot){};
    virtual void OnCancel(int spot){};
    virtual void OnFinish(int spot){};
    virtual void OnClose(int spot){};
};

class AdstirVideoRewardNativeLauncher
{
public:
    static void setMediaUserID(const char* aMediaUserID);
    static void init(const char *aMedia, int *aSpots, int numberOfSpots);
    static void load(int aSpot);
    static void show(int aSpot);
    static bool canShow(int aSpot);
    static void setDelegate(AdstirVideoRewardNativeDelegate* delegate, int aSpot);
};

#endif /* AdstirVideoRewardNativeLauncher_h */
