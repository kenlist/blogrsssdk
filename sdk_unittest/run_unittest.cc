#include "base/at_exit.h"
#include "base/test/launcher/unit_test_launcher.h"
#include "base/test/test_suite.h"

#include "../blogrss_sdk.h"

using namespace base;

class NoAtExitBaseTestSuite : public base::TestSuite {
  public:
    NoAtExitBaseTestSuite(int argc, char** argv)
        : base::TestSuite(argc, argv, false) {
    }
};
  
int RunTestSuite(int argc, char** argv) {
  return NoAtExitBaseTestSuite(argc, argv).Run();
}

int main(int argc, char** argv) {
#if defined(OS_ANDROID)
  JNIENV* env = android::AttachCurrentThread();
  file_util::RegisterCounentUriTestUtils(env);
#else
  AtExitManager at_exit;
  blogrss::BlogRSSSDK::GetInstance()->Start();
#endif
  return LaunchUnitTests(argc,
                         argv,
                         base::Bind(&RunTestSuite, argc, argv));
}
