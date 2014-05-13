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
        'android/blogrss_sdk_entry.cc',
      ],
    }
  ],
}