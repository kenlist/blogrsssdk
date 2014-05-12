{
  'target_defaults': {
    'variables': {
      'sdk_target': 0,
    },
    'dependencies': [
      '../net/net.gyp:net',
      '../third_party/libxml/libxml.gyp:libxml',
    ],
    'target_conditions': [
      ['sdk_target==1', {
        'sources': [
          'blogrsssdk-Prefix.pch',
          'blogrss_sdk.h',
          'blogrss_sdk.cc',
          'blogrss_sdk_delegate.h',
          'rss_info.h',
          'rss_xml_analyzer.h',
          'rss_xml_analyzer.cc',
          'http_request.h',
          'http_request.cc',
          'thread_manager.h',
          'thread_manager.cc',
          'env_init.h',
          'env_init.cc',
        ],
      },],
    ],
  },
}