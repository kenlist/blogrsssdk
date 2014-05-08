#ifndef BLOGRSS_SDK_DELEGATE_H_
#define BLOGRSS_SDK_DELEGATE_H_

#include "rss_info.h"

namespace blogrss {

class BlogRSSSDKDelegate {
  public:
    virtual void OnRSSFetched(int ret_code, RSSInfo* rss_info) = 0;
};

}

#endif
