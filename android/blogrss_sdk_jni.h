#ifndef BLOGRSS_SDK_JNI_H_
#define BLOGRSS_SDK_JNI_H_

#include <jni.h>
#include <map>
#include <string>

#include "base/android/jni_android.h"
#include "base/android/jni_weak_ref.h"
#include "base/basictypes.h"

#include "../blogrss_sdk.h"
#include "../blogrss_sdk_delegate.h"

namespace blogrss {

class BlogRSSSDKJni 
    : public BlogRSSSDKDelegate,
      public base::SupportsWeakPtr<BlogRSSSDKJni> {
  public:
    BlogRSSSDKJni(JavaObjectWeakGlobalRef weak_java_ref);
    ~BlogRSSSDKJni();

    void Destroy(JNIEnv* env, jobject obj);
    jboolean Start(JNIEnv* env, jobject obj, jobject jcontext);
    jboolean Stop(JNIEnv* env, jobject obj);
    jboolean FetchRSS(JNIEnv* env, jobject obj);

    static bool RegisterBindings(JNIEnv* env);

  private:
    void OnRSSFetched(int ret_code, RSSItemList rss_item_list);

  private:
    scoped_refptr<BlogRSSSDK> blogrss_sdk_;
    scoped_ptr<base::AtExitManager> exit_manager_;
    JavaObjectWeakGlobalRef weak_java_ref_;

    DISALLOW_COPY_AND_ASSIGN(BlogRSSSDKJni);
};

}

#endif