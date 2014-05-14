#ifndef BLOG_RSS_RESPONSER_H_
#define BLOG_RSS_RESPONSER_H_

#include "../blogrss_sdk_delegate.h"

class BlogRSSResponser
    : public blogrss::BlogRSSSDKDelegate,
      public base::SupportsWeakPtr<BlogRSSResponser> {

public:
  BlogRSSResponser();
  ~BlogRSSResponser();
  
  void OnRSSFetched(int ret_code, blogrss::RSSItemList rss_item_list);

};

#endif
