{
  'includes': [
    'blogrsssdk.gypi',
  ],
  'target_defaults': {

  },
  'targets': [
    # {
    #   'target_name': 'blogrsssdk_jni_headers',
    #   'type': 'none',
    #   'sources': [

    #   ],
    #   'variables': {
    #     'jni_gen_dir': 'blogrsssdk/android',
    #   },
    #   'includes': [
    #     '../build/jni_generator.gypi'
    #   ],
    # },
    {
      'target_name': 'blogrsssdk',
      'type': 'shared_library',
      'variables': {
        'sdk_target': 1,
      },
    }
  ],
}