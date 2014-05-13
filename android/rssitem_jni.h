#ifndef RSSITEM_JNI_H_
#define RSSITEM_JNI_H_

#include <jni.h>
#include <map>
#include <string>

#include "base/android/jni_android.h"
#include "base/basictypes.h"

#include "../rss_item.h"

namespace blogrss {

class RSSItemJni {
  public:
    static base::android::ScopedJavaLocalRef<jobject> CreateJavaRSSItem(RSSItem* rss_item);

    static bool RegisterBindings(JNIEnv* env);

  private:

    DISALLOW_COPY_AND_ASSIGN(RSSItemJni);
};

}

#endif