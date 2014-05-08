#import "blogrss_responser.h"
#import "blogrsssdk.h"
#import "sdktrigger.h"
#import "rssinfoitem.h"

using namespace base;

BlogRSSResponser::BlogRSSResponser() {

}

BlogRSSResponser::~BlogRSSResponser() {

}
  
void BlogRSSResponser::OnRSSFetched(int ret_code, blogrss::RSSInfo* rss_info) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_UI);
  
  RSSInfoItem* objc_rss_info = [[RSSInfoItem alloc] init];
  
  [SDKTrigger TriggerRSSFetchedWithRetCode:ret_code andRSSInfo:nil];
}
