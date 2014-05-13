package org.blogrsssdk;

import android.graphics.Rect;

import org.chromium.base.AccessedByNative;
import org.chromium.base.CalledByNative;
import org.chromium.base.CalledByNativeUnchecked;
import org.chromium.base.JNINamespace;
import org.chromium.base.NativeClassQualifiedName;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Date;

class RSSItem {
    private final String title;
    private final Date pubDate;
    private final String link;
}

interface BlogRSSSDKDelegate {
    void onRSSFetchedWithRetCode(int retCode, List<RSSItem> rssItem);
}

@JNINamespace("blogrss")
class BlogRSSSDK {
    private static BlogRSSSDK instance;
    private long mNativeSDKObject;

    public static BlogRSSSDK getInstance() {
        if (instance == null) {
            instance = new BlogRSSSDK();
        }
        return instance;
    }

    private BlogRSSSDK() {
        mNativeSDKObject = nativeNewInstance();
    }

    protected void finalize() {
        nativeDestroy(mNativeSDKObject);
    }
  
    private native long nativeNewInstance();
    private native void nativeDestroy(long nativeBlogRSSSDKJni);
    private native boolean nativeStart(long nativeBlogRSSSDKJni);
    private native boolean nativeStop(long nativeBlogRSSSDKJni);
    private native boolean nativeFetchRSS(long nativeBlogRSSSDKJni);
}