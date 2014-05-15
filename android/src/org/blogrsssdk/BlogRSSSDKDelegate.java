package org.blogrsssdk;

import org.blogrsssdk.RSSItem;

public interface BlogRSSSDKDelegate {
    void onRSSFetchedWithRetCode(int retCode, RSSItem[] rssItem);
}