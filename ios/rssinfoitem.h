//
//  rssinfoitem.h
//  blogrsssdk-ios
//
//  Created by 罗 日健 on 5/8/14.
//
//

#import <Foundation/Foundation.h>

@interface RSSInfoItem : NSObject

@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSDate *pubDate;
@property (nonatomic, strong) NSString *link;

@end
