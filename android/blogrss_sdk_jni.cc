#include "./blogrss_sdk_jni.h"

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/android/scoped_java_ref.h"
#include "jni/BlogRSSSDK_jni.h"

#include "java_singleton.h"
#include "rssitem_jni.h"

using namespace base;
using namespace base::android;

namespace blogrss {

jlong NewInstance(JNIEnv* env, jobject jcaller,
    jobject javaSDKObject) {

  JavaObjectWeakGlobalRef weak_java_ref = 
      JavaObjectWeakGlobalRef(env, javaSDKObject);
  BlogRSSSDKJni *sdk_jni = new BlogRSSSDKJni(weak_java_ref);

  //use singleton after BlogRSSSDKJni initialized.
  JavaSingleton::GetInstance()->set_env(env);

  return reinterpret_cast<jlong>(sdk_jni);
}

BlogRSSSDKJni::BlogRSSSDKJni(JavaObjectWeakGlobalRef weak_java_ref) {
  weak_java_ref_ = weak_java_ref;
  blogrss_sdk_ = new BlogRSSSDK();
  blogrss_sdk_->set_delegate(this->AsWeakPtr());
  exit_manager_.reset(new AtExitManager);
}

BlogRSSSDKJni::~BlogRSSSDKJni() {
}

void BlogRSSSDKJni::Destroy(JNIEnv* env, jobject obj) {
  delete this;
}

jboolean BlogRSSSDKJni::Start(JNIEnv* env, jobject obj, jobject jcontext) {
  ScopedJavaLocalRef<jobject> scoped_context(env, jcontext);
  InitApplicationContext(env, scoped_context);
  return blogrss_sdk_->Start(0, NULL);
}

jboolean BlogRSSSDKJni::Stop(JNIEnv* env, jobject obj) {
  if (!exit_manager_) {
    return false;
  }
  exit_manager_.reset();
  return true;
}

jboolean BlogRSSSDKJni::FetchRSS(JNIEnv* env, jobject obj) {
  return blogrss_sdk_->FetchRSS();
}

bool BlogRSSSDKJni::RegisterBindings(JNIEnv* env) {
    return RegisterNativesImpl(env);
}

void BlogRSSSDKJni::OnRSSFetched(int ret_code, RSSItemList rss_item_list) {
  JNIEnv* env = JavaSingleton::GetInstance()->env();

  if (!env || weak_java_ref_.get(env).is_null()) return;

  ScopedJavaLocalRef<jclass> rss_item_clazz = GetClass(env, "org/blogrsssdk/RSSItem");
  ScopedJavaLocalRef<jobjectArray> java_array(env, 
                                              env->NewObjectArray(rss_item_list.size(),
                                                                  rss_item_clazz.obj(),
                                                                  NULL));
  CheckException(env);

  for (size_t i = 0; i < rss_item_list.size(); ++i) {
    RSSItem* rss_item = rss_item_list[i];
    ScopedJavaLocalRef<jobject> java_rss_item = 
        RSSItemJni::CreateJavaRSSItem(rss_item);

    env->SetObjectArrayElement(java_array.obj(), i, java_rss_item.obj());
  }

  Java_BlogRSSSDK_onRSSFetched(env, 
                               weak_java_ref_.get(env).obj(), 
                               static_cast<jint>(ret_code),
                               java_array.obj());
}

}