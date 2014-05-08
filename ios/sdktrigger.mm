//
//  blogrsssdk+trigger.mm
//  blogrsssdk-ios
//
//  Created by 罗 日健 on 5/8/14.
//
//

#import "sdktrigger.h"
#import "blogrsssdk.h"

@implementation SDKTrigger

+ (void)TriggerRSSFetchedWithRetCode:(int)ret_code andRSSInfo:(NSArray *)rss_info {
  id<BlogRSSSDKDelegate> delegate = [BlogRSSSDK sharedSDK].delegate;
  if (delegate) {
    [delegate onRSSFetchedWithRetCode:ret_code andRSSInfo:rss_info];
  }
}

@end
