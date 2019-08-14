//
//  AdstirPlugin.h
//
//  Created by 森田 裕司 on 2019/07/25.
//  Copyright © 2019 United Inc. All rights reserved.
//

#ifndef AdstirPlugin_h
#define AdstirPlugin_h

namespace Adstir {
    class VideoAds
    {
    public:
        static void setMediaUserID(const char* aMediaUserID);
        static void init(const char *aMedia, int *aSpots, int numberOfSpots);
    };
    
    class VideoRewardDelegate
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
    
    class VideoReward
    {
    public:
        static void load(int aSpot);
        static void show(int aSpot);
        static bool canShow(int aSpot);
        static void setDelegate(VideoRewardDelegate* delegate, int aSpot);
    };
    
    class InterstitialDelegate
    {
    public:
        virtual void OnLoad(int spot){};
        virtual void OnFailToLoad(int spot){};
        virtual void OnStart(int spot){};
        virtual void OnFailToStart(int spot){};
        virtual void OnClose(int spot){};
    };
    
    class Interstitial
    {
    public:
        static void load(int aSpot);
        static void show(int aSpot);
        static bool canShow(int aSpot);
        static void setDelegate(InterstitialDelegate* delegate, int aSpot);
    };
}

#endif /* AdstirVideoAds_h */
