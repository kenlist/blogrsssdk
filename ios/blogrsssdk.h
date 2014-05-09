//
//  blogrsssdk.h
//  blogrsssdk-ios
//
//  Created by 罗 日健 on 5/4/14.
//  Copyright (c) 2014 kenlist. All rights reserved.
//

#import <Foundation/Foundation.h>

//BlogRSSSDKDelegate
@protocol BlogRSSSDKDelegate <NSObject>
- (void)onRSSFetchedWithRetCode:(int)retCode andRSSItems:(NSArray *)rssItems;
@end

//BlogRSSSDK
@interface BlogRSSSDK : NSObject

+ (BlogRSSSDK *)sharedSDK;

- (BOOL)startWithArgc:(int)argc andArgv:(char**)argv;
- (BOOL)stop;
- (BOOL)fetchRSS;

@property (nonatomic, strong) id<BlogRSSSDKDelegate> delegate;

@end
