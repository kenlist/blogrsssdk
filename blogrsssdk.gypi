{
  'target_defaults': {
    'dependencies': [
      '../net/net.gyp:net',
    ],
    'include_dirs': [
      '/usr/include/libxml2'
    ],
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
  },
}