#import "blogrss_responser.h"
#import "blogrsssdk.h"
#import "sdktrigger.h"
#import "rssinfoitem.h"

using namespace base;

BlogRSSResponser::BlogRSSResponser() {

}

BlogRSSResponser::~BlogRSSResponser() {

}
  
void BlogRSSResponser::OnRSSFetched(int ret_code, blogrss::RSSInfo rss_info) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_UI);
  
  NSMutableArray* rss_items = [NSMutableArray array];
  
  for (blogrss::RSSInfo::iterator iter = rss_info.begin(); iter != rss_info.end(); ++iter) {
    RSSInfoItem* objc_rss_item = [[RSSInfoItem alloc] init];
    blogrss::RSSItemInfo* cpp_rss_item = *iter;
    
    objc_rss_item.title = [NSString stringWithUTF8String:cpp_rss_item->title.c_str()];
    objc_rss_item.pubDate = [NSDate dateWithTimeIntervalSince1970:mktime(&cpp_rss_item->pub_date)];
    objc_rss_item.link = [NSString stringWithUTF8String:cpp_rss_item->link.c_str()];
    
    [rss_items addObject:objc_rss_item];
  }
  
  [SDKTrigger TriggerRSSFetchedWithRetCode:ret_code andRSSItems:rss_items];
}
