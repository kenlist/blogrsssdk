#include <jni.h>
#include <map>
#include <string>

#include "base/android/jni_android.h"
#include "base/basictypes.h"

#include "../blogrss_sdk.h"

namespace blogrss {

class BlogRSSSDKJni {
  public:
    BlogRSSSDKJni();
    ~BlogRSSSDKJni();

    void Destroy(JNIEnv* env, jobject obj);
    jboolean Start(JNIEnv* env, jobject obj);
    jboolean Stop(JNIEnv* env, jobject obj);
    jboolean FetchRSS(JNIEnv* env, jobject obj);

    static bool DoRegisterNativesImpl(JNIEnv* env);
  private:
    scoped_refptr<BlogRSSSDK> blogrss_sdk_;
    scoped_ptr<base::AtExitManager> exit_manager;

    DISALLOW_COPY_AND_ASSIGN(BlogRSSSDKJni);
};

}
