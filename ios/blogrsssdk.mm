//
//  blogrsssdk.h
//  blogrsssdk
//
//  Created by 罗 日健 on 5/4/14.
//  Copyright (c) 2014 kenlist. All rights reserved.
//

#import "blogrsssdk.h"
#import "blogrsssdk/blogrss_session.h"

@interface BlogRSSSDK() {
  base::AtExitManager *pExit_manager;
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

- (void)dealloc {
  if (pExit_manager) {
    delete pExit_manager;
    pExit_manager = NULL;
  }
  [super dealloc];
}

- (id)init {
  self = [super init];
  if (self) {
    pExit_manager = NULL;
  }
  return self;
}

- (BOOL)start {
  if (pExit_manager) {
    return NO;
  }
  pExit_manager = new base::AtExitManager();
  return blogrss::BlogRSSSession::GetInstance()->Start();
}

- (BOOL)stop {
  if (!pExit_manager) {
    return NO;
  }
  delete pExit_manager;
  pExit_manager = NULL;
  return YES;
}

- (BOOL)fetchRSS {
  
}

@end
