#include "../blogrss_sdk.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "base/synchronization/condition_variable.h"
#include "base/synchronization/lock.h"

using namespace base;

namespace blogrss {

class BlogRSSSessionTest :public testing::Test {
};

TEST_F(BlogRSSSessionTest, FetchRSS) {
  scoped_refptr<blogrss::BlogRSSSDK> blogrss_sdk = new blogrss::BlogRSSSDK;
  blogrss_sdk->StartWithoutEnvInit();
  blogrss_sdk->FetchRSS();
  
  //CFRunLoopStop([[NSRunLoop currentRunLoop] getCFRunLoop]);
  [[NSRunLoop currentRunLoop] run];
}

}
