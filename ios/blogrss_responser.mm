#include "blogrss_responser.h"
#include "blogrsssdk.h"
#include "blogrsssdk+trigger.h"
#include "rssinfoitem.h"

using namespace base;

BlogRSSResponser::BlogRSSResponser() {

}

BlogRSSResponser::~BlogRSSResponser() {

}
  
void BlogRSSResponser::OnRSSFetched(int ret_code, blogrss::RSSInfo* rss_info) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_UI);
  
  RSSInfoItem* objc_rss_info = [[RSSInfoItem alloc] init];
  
  [[BlogRSSSDK sharedSDK] TriggerRSSFetchedWithRetCode:ret_code andRSSInfo:nil];
}
