//
//  blogrsssdk+trigger.mm
//  blogrsssdk-ios
//
//  Created by 罗 日健 on 5/8/14.
//
//

#import "blogrsssdk+trigger.h"

@implementation BlogRSSSDK (Trigger)

- (void)TriggerRSSFetchedWithRetCode:(int)ret_code andRSSInfo:(NSArray *)rss_info {
  if (self.delegate) {
    [self.delegate onRSSFetchedWithRetCode:ret_code andRSSInfo:rss_info];
  }
}

@end
