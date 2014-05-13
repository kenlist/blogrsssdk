#include "base/android/jni_android.h"
#include "base/android/jni_registrar.h"
#include "blogrss_sdk_jni.h"
#include "rssitem_jni.h"
#include "java_singleton.h"

#define DEBUG 0

#define TAG "blogrss_android_linker"

#if DEBUG
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#else
#define LOG_INFO(...) ((void)0)
#define LOG_ERROR(...) ((void)0)
#endif

static base::android::RegistrationMethod kBlogRSSSDKRegisteredMethods[] = {
  { "BlogRSSSDKJni", blogrss::BlogRSSSDKJni::RegisterBindings },
  { "RSSItemJi",     blogrss::RSSItemJni::RegisterBindings },
};

JNI_EXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {

  LOG_INFO("%s: Entering", __FUNCTION__);

  // Get new JNIEnv
  JNIEnv* env;
  if (JNI_OK != vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_4)) {
    LOG_ERROR("Could not create JNIEnv");
    return -1;
  }

  base::android::InitVM(vm);
  JavaSingleton::GetInstance()->set_env(env);

  if (!base::android::RegisterNativeMethods(
          env, kBlogRSSSDKRegisteredMethods,
          arraysize(kBlogRSSSDKRegisteredMethods))) {
    LOG_ERROR("RegisterNativeMethods error");
    return -1;
  }

  return JNI_VERSION_1_4;
}