package org.blogrsssdk;

import android.graphics.Rect;

import org.chromium.base.CalledByNative;
import org.chromium.base.JNINamespace;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.blogrsssdk.RSSItem;

interface BlogRSSSDKDelegate {
    void onRSSFetchedWithRetCode(int retCode, RSSItem[] rssItem);
}

@JNINamespace("blogrss")
public class BlogRSSSDK {
    private static BlogRSSSDK sInstance = null;
    private long mNativeSDKObject = 0;
    private BlogRSSSDKDelegate mDelegate = null;

    static {
        System.loadLibrary("blogrsssdk");
    }

    public static BlogRSSSDK getInstance() {
        if (sInstance == null) {
            sInstance = new BlogRSSSDK();
        }
        return sInstance;
    }

    private BlogRSSSDK() {
        mNativeSDKObject = nativeNewInstance(this);
    }

    protected void finalize() {
        nativeDestroy(mNativeSDKObject);
    }

    public void start() {
        nativeStart(mNativeSDKObject);
    }

    public void stop() {
        nativeStop(mNativeSDKObject);
    }

    public void fetchRSS() {
        nativeFetchRSS(mNativeSDKObject);
    }

    public void setDelegate(BlogRSSSDKDelegate delegate) {
        mDelegate = delegate;
    }

    @CalledByNative
    private void onRSSFetched(int retCode, RSSItem[] rssItems) {
        if (mDelegate != null) {
            mDelegate.onRSSFetchedWithRetCode(retCode, rssItems);
        }
    }
  
    private native long nativeNewInstance(Object javaSDKObject);
    private native void nativeDestroy(long nativeBlogRSSSDKJni);
    private native boolean nativeStart(long nativeBlogRSSSDKJni);
    private native boolean nativeStop(long nativeBlogRSSSDKJni);
    private native boolean nativeFetchRSS(long nativeBlogRSSSDKJni);
}