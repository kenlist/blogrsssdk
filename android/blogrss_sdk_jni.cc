#include "./blogrss_sdk_jni.h"

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/android/scoped_java_ref.h"
#include "jni/BlogRSSSDK_jni.h"

using namespace base;

namespace blogrss {

static jlong NewInstance(JNIEnv* env, jobject jcaller) {
  return (jlong)new BlogRSSSDKJni();
}

BlogRSSSDKJni::BlogRSSSDKJni() {
  blogrss_sdk_ = new BlogRSSSDK();
}

BlogRSSSDKJni::~BlogRSSSDKJni() {

}

void BlogRSSSDKJni::Destroy(JNIEnv* env, jobject obj) {
  delete this;
}

jboolean BlogRSSSDKJni::Start(JNIEnv* env, jobject obj) {
  if (exit_manager)
    return false;

  exit_manager.reset(new base::AtExitManager);
  return blogrss_sdk_->Start(0, NULL);
}

jboolean BlogRSSSDKJni::Stop(JNIEnv* env, jobject obj) {
  if (!exit_manager) {
    return false;
  }
  exit_manager.reset();
  return true;
}

jboolean BlogRSSSDKJni::FetchRSS(JNIEnv* env, jobject obj) {
  return blogrss_sdk_->FetchRSS();
}

bool BlogRSSSDKJni::DoRegisterNativesImpl(JNIEnv* env) {
    return RegisterNativesImpl(env);
}

}