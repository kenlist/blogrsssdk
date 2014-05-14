#import "blogrss_responser.h"
#import "blogrsssdk.h"
#import "sdktrigger.h"
#import "rssinfoitem.h"

using namespace base;

BlogRSSResponser::BlogRSSResponser() {

}

BlogRSSResponser::~BlogRSSResponser() {

}
  
void BlogRSSResponser::OnRSSFetched(int ret_code, blogrss::RSSItemList rss_item_list) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_UI);
  
  NSMutableArray* rss_items = [NSMutableArray array];
  
  for (blogrss::RSSItemList::iterator iter = rss_item_list.begin(); iter != rss_item_list.end(); ++iter) {
    RSSInfoItem* objc_rss_item = [[RSSInfoItem alloc] init];
    blogrss::RSSItem* rss_item = *iter;
    
    objc_rss_item.title = [NSString stringWithUTF8String:rss_item->title.c_str()];
    objc_rss_item.pubDate = [NSDate dateWithTimeIntervalSince1970:mktime(&rss_item->pub_date)];
    objc_rss_item.link = [NSString stringWithUTF8String:rss_item->link.c_str()];
    
    [rss_items addObject:objc_rss_item];
  }
  
  [SDKTrigger TriggerRSSFetchedWithRetCode:ret_code andRSSItems:rss_items];
}
