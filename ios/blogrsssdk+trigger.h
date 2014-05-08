//
//  blogrssdk+trigger.h
//  blogrsssdk-ios
//
//  Created by 罗 日健 on 5/8/14.
//
//

#import "blogrsssdk.h"
#import "blogrss_responser.h"
#import "rssinfoitem.h"

@interface BlogRSSSDK (Trigger)

- (void)TriggerRSSFetchedWithRetCode:(int)ret_code andRSSInfo:(NSArray *)rss_info;

@end
