//
//  blogrsssdk.h
//  blogrsssdk-ios
//
//  Created by 罗 日健 on 5/4/14.
//  Copyright (c) 2014 kenlist. All rights reserved.
//

#import "blogrsssdk.h"
#import "blogrss_responser.h"
#import "blogrsssdk/blogrss_sdk.h"
#import "blogrsssdk/blogrss_sdk_delegate.h"

@interface BlogRSSSDK() {
  scoped_ptr<base::AtExitManager> exit_manager;
  scoped_ptr<BlogRSSResponser> responser;
}
@end

@implementation BlogRSSSDK

+ (BlogRSSSDK *)sharedSDK {
  static BlogRSSSDK *sdk = nil;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    sdk = [[self alloc] init];
  });
  return sdk;
}

- (BOOL)start {
  if (exit_manager) {
    return NO;
  }
  exit_manager.reset(new base::AtExitManager);
  responser.reset(new BlogRSSResponser);
  blogrss::BlogRSSSDK::GetInstance()->set_delegate(responser->AsWeakPtr());
  return blogrss::BlogRSSSDK::GetInstance()->Start();
}

- (BOOL)stop {
  if (!exit_manager) {
    return NO;
  }
  exit_manager.reset();
  return YES;
}

- (BOOL)fetchRSS {
  return blogrss::BlogRSSSDK::GetInstance()->FetchRSS();
}

@end
