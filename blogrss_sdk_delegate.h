#ifndef BLOGRSS_SDK_DELEGATE_H_
#define BLOGRSS_SDK_DELEGATE_H_

#include "rss_item.h"

namespace blogrss {

class BlogRSSSDKDelegate {
  public:
    virtual void OnRSSFetched(int ret_code, RSSItemList rss_item_list) = 0;
};

}

#endif
