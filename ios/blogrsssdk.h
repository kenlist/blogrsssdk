//
//  blogrsssdk.h
//  blogrsssdk
//
//  Created by 罗 日健 on 5/4/14.
//  Copyright (c) 2014 kenlist. All rights reserved.
//

#import <Foundation/Foundation.h>

//BlogRSSSDKDelegate
@protocol BlogRSSSDKDelegate <NSObject>
- (void)onRSSFetchedWithData:(NSArray *)rssData andIsSuccess:(BOOL)bSuccess;
@end

//BlogRSSSDK
@interface BlogRSSSDK : NSObject

+ (BlogRSSSDK *)sharedSDK;

- (BOOL)start;
- (BOOL)stop;
- (BOOL)fetchRSS;

@property (nonatomic, strong) id<BlogRSSSDKDelegate> delegate;

@end
