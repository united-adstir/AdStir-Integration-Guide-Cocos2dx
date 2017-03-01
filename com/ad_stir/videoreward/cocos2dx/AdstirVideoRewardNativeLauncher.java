package com.ad_stir.videoreward.cocos2dx;

import android.app.Activity;
import android.util.SparseArray;

import com.ad_stir.videoreward.AdstirVideoReward;
import com.ad_stir.videoreward.AdstirVideoRewardListener;
import java.util.ArrayList;

public class AdstirVideoRewardNativeLauncher {
    private static boolean videoRewardInitialized = false;
    private static ArrayList<Integer> videoRewardSpots;
    private static SparseArray<AdstirVideoReward> videoRewardInstances;
    private static SparseArray<AdstirVideoRewardListenerImpl> videoRewardListeners;
    private static String videoRewardMedia;
    private static Activity activity;

    public AdstirVideoRewardNativeLauncher(Activity activity){
        this.activity = activity;
    }

    public static void setMediaUserID(String mediaUserID) {
        AdstirVideoReward.setMediaUserID(mediaUserID);
    }

    public static void init(final String media, final int[] spots){
        if (!videoRewardInitialized) {
            videoRewardMedia = media;

            videoRewardSpots = new ArrayList<Integer>();
            for (int spot : spots) {
                videoRewardSpots.add(spot);
            }

            activity.runOnUiThread(new Runnable(){
                @Override
                public void run() {
                    AdstirVideoReward.init(activity, media, spots);
                    videoRewardInitialized = true;
                }
            });

            videoRewardInstances = new SparseArray<AdstirVideoReward>();
            videoRewardListeners = new SparseArray<AdstirVideoRewardListenerImpl>();
        }
    }

    public static void load(final int spot){
        if (!videoRewardSpots.contains(spot)) {
            return;
        }

        activity.runOnUiThread(new Runnable(){
            @Override
            public void run() {
                AdstirVideoReward instance = videoRewardInstances.get(spot);
                if (instance == null) {
                    instance = new AdstirVideoReward(activity, videoRewardMedia, spot);

                    videoRewardInstances.put(spot, instance);
                }
                instance.load();
            }
        });
    }

    public static void show(final int spot){
        if (!videoRewardSpots.contains(spot)) {
            return;
        }

        activity.runOnUiThread(new Runnable(){
            @Override
            public void run() {
                AdstirVideoReward instance = videoRewardInstances.get(spot);
                if (instance == null) {
                    return;
                }

                instance.showRewardVideo();
            }
        });

    }

    public static boolean canShow(final int spot){
        if (!videoRewardSpots.contains(spot)) {
            return false;
        }
        AdstirVideoReward instance = videoRewardInstances.get(spot);
        if (instance == null) return false;
        return instance.canShow();
    }

    public static void setDelegate(final int spot){
        activity.runOnUiThread(new Runnable(){
            @Override
            public void run() {
                AdstirVideoReward instance = videoRewardInstances.get(spot);
                if (instance == null) {
                    instance = new AdstirVideoReward(activity, videoRewardMedia, spot);

                    videoRewardInstances.put(spot, instance);
                }
                AdstirVideoRewardListenerImpl listener = new AdstirVideoRewardListenerImpl();
                instance.setAdstirVideoRewardListener(listener);
                videoRewardListeners.put(spot, listener);
            }
        });
    }
}

class AdstirVideoRewardListenerImpl implements AdstirVideoRewardListener {
    public static native void OnLoad(int spot);
    public static native void OnFailToLoad(int spot);
    public static native void OnStart(int spot);
    public static native void OnFailToStart(int spot);
    public static native void OnComplete(int spot);
    public static native void OnCancel(int spot);
    public static native void OnFinish(int spot);
    public static native void OnClose(int spot);

    @Override
    public void onLoad(int spot) {
        OnLoad(spot);
    }

    @Override
    public void onFailed(int spot) {
        OnFailToLoad(spot);
    }

    @Override
    public void onStart(int spot) {
        OnStart(spot);
    }

    @Override
    public void onStartFailed(int spot) {
        OnFailToStart(spot);
    }

    @Override
    public void onFinished(int spot) {
        OnFinish(spot);
    }

    @Override
    public void onClose(int spot) {
        OnClose(spot);
    }

    @Override
    public void onReward(int spot) {
        OnComplete(spot);
    }

    @Override
    public void onRewardCanceled(int spot) {
        OnCancel(spot);
    }
}
