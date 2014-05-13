{
  'includes': [
    'blogrsssdk.gypi' ,
  ],
  'target_defaults': {

  },
  'targets': [
    {
      'target_name': 'blogrsssdk_jni_headers',
      'type': 'none',
      'sources': [
        'android/src/org/blogrsssdk/BlogRSSSDK.java',
        'android/src/org/blogrsssdk/RSSItem.java',
      ],
      'variables': {
        'jni_gen_package': 'blogrsssdk',
        'jni_generator_ptr_type': 'long',
      },
      'includes': [
        '../build/jni_generator.gypi'
      ],
    },
    {
      'target_name': 'blogrsssdk',
      'type': 'shared_library',
      'variables': {
        'sdk_target': 1,
      },
      'include_files': [
        'blogrsssdk-Prefix.pch'
      ],
      'dependencies': [
        'blogrsssdk_jni_headers'
      ],
      'sources': [
        'android/blogrss_sdk_jni.h',
        'android/blogrss_sdk_jni.cc',
        'android/rssitem_jni.h',
        'android/rssitem_jni.cc',
        'android/java_singleton.h',
        'android/java_singleton.cc',
        'android/blogrss_sdk_entry.cc',
      ],
    },
    {
      'target_name': 'blogrsssdk_java',
      'type': 'none',
      'variables': {
        'java_in_dir': 'android',
      },
      'dependencies': [
        '../base/base.gyp:base_java',
      ],
      'includes': [
        '../build/java.gypi',
      ],
    },
  ],
}