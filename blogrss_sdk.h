#ifndef BLOGRSS_SDK_H_
#define BLOGRSS_SDK_H_

#include "blogrss_sdk_delegate.h"

namespace blogrss {

class HttpRequest;
class RSSXMLAnalyzer;
class BlogRSSSDK : public base::RefCountedThreadSafe<BlogRSSSDK> {
  public:    
    BlogRSSSDK();
    ~BlogRSSSDK();
  
    bool StartWithoutEnvInit();
    bool Start(int argc, char** argv);
    bool FetchRSS();
  
    void set_delegate(base::WeakPtr<BlogRSSSDKDelegate> delegate) {
      delegate_ = delegate;
    }
  
  private:
    void OnFetchRSS(int ret_code, const std::string& response_data);
    void FireRSSFetchedOnUI();
  
  private:
    base::WeakPtr<BlogRSSSDKDelegate> delegate_;
    scoped_refptr<HttpRequest> request_;
    scoped_ptr<RSSXMLAnalyzer> analyzer_;
  
    int ret_code_;
    RSSItemList rss_item_list_;
  
    DISALLOW_COPY_AND_ASSIGN(BlogRSSSDK);
};
  
}

#endif
