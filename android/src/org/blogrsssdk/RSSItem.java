package org.blogrsssdk;

import org.chromium.base.JNINamespace;
import org.chromium.base.CalledByNative;

import java.text.SimpleDateFormat;
import java.util.Date;

@JNINamespace("blogrss")
public class RSSItem {
    public final String title;
    public final Date pubDate;
    public final String link;

    private RSSItem(String t, Date d, String l) {
        title = t;
        pubDate = d;
        link = l;
    }

    @CalledByNative
    private static RSSItem create(String t, long dateTimeSine1970, String l) {
        Date dt = new Date(dateTimeSine1970 * 1000);
        return new RSSItem(t, dt, l);
    }
}