{
  'includes': [
    'blogrsssdk-ios.gypi',
  ],
  'targets': [
    {
      'target_name': 'blogrsssdk',
      'type': 'loadable_module',
      'mac_bundle': 1,
      'variables': {
        'sdk': 1,
      },
      'mac_framework_headers': [
        'ios/blogrsssdk.h',
        'ios/rssinfoitem.h',
      ],
      'sources': [
        'ios/blogrsssdk.h',
        'ios/blogrsssdk.mm',
        'ios/blogrss_responser.h',
        'ios/blogrss_responser.mm',
        'ios/sdktrigger.h',
        'ios/sdktrigger.mm',
        'ios/rssinfoitem.h',
        'ios/rssinfoitem.mm',
      ],
    },
    {
      'target_name': 'blogrsssdk-unittest',
      'type': '<(gtest_target_type)',
      'dependencies': [
        '../base/base.gyp:test_support_base',
        '../testing/gmock.gyp:gmock',
        '../testing/gtest.gyp:gtest',
      ],
      'link_settings': {
        'libraries': [
          '$(SDKROOT)/usr/lib/libstdc++.dylib',
          '$(SDKROOT)/usr/lib/libSystem.dylib',
          '$(SDKROOT)/usr/lib/libxml2.dylib',
        ],
      },
      'sources': [
        'sdk_unittest/blogrss_session_unittest.mm',
        'sdk_unittest/run_unittest.cc',
      ],
    }
  ],
}