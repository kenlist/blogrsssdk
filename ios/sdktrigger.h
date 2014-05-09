//
//  sdktrigger.h
//  blogrsssdk-ios
//
//  Created by 罗 日健 on 5/8/14.
//
//

#import "blogrsssdk.h"
#import "blogrss_responser.h"
#import "rssinfoitem.h"

@interface SDKTrigger

+ (void)TriggerRSSFetchedWithRetCode:(int)ret_code andRSSItems:(NSArray *)rss_items;

@end
