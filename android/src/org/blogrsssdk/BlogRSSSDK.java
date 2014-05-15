package org.blogrsssdk;

import android.content.Context;

import org.chromium.base.CalledByNative;
import org.chromium.base.JNINamespace;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.blogrsssdk.RSSItem;
import org.blogrsssdk.BlogRSSSDKDelegate;

@JNINamespace("blogrss")
public class BlogRSSSDK {
    private static BlogRSSSDK sInstance = null;
    private long mNativeSDKObject = 0;
    private BlogRSSSDKDelegate mDelegate = null;

    public static BlogRSSSDK getInstance() {
        if (sInstance == null) {
            sInstance = new BlogRSSSDK();
        }
        return sInstance;
    }

    private BlogRSSSDK() {
        System.loadLibrary("blogrsssdk");
        mNativeSDKObject = nativeNewInstance(this);
    }

    protected void finalize() {
        nativeDestroy(mNativeSDKObject);
    }

    public void start(Context context) {
        nativeStart(mNativeSDKObject, context);
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
    private native boolean nativeStart(long nativeBlogRSSSDKJni, Context context);
    private native boolean nativeStop(long nativeBlogRSSSDKJni);
    private native boolean nativeFetchRSS(long nativeBlogRSSSDKJni);
}