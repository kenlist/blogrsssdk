#include "rssitem_jni.h"
#include "java_singleton.h"
#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "jni/RSSItem_jni.h"

using namespace base;
using namespace base::android;

namespace blogrss {

ScopedJavaLocalRef<jobject> RSSItemJni::CreateJavaRSSItem(RSSItem* rss_item) {
  JNIEnv* env = JavaSingleton::GetInstance()->env();
  if (!env) {
    ScopedJavaLocalRef<jobject> null_obj(env, NULL);
    return null_obj;
  }

  //title
  ScopedJavaLocalRef<jstring> title = 
      ConvertUTF8ToJavaString(env, rss_item->title);
  //pub_date
  jlong date_time = mktime(&rss_item->pub_date);
  //link
  ScopedJavaLocalRef<jstring> link = 
      ConvertUTF8ToJavaString(env, rss_item->link);

  ScopedJavaLocalRef<jobject> java_rss_item = 
      Java_RSSItem_create(env, title.obj(), date_time, link.obj());

  return java_rss_item;
}

bool RSSItemJni::RegisterBindings(JNIEnv* env) {
  return RegisterNativesImpl(env);
}

}