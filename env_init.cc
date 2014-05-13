#include "env_init.h"

#if defined(OS_ANDROID)
#include "base/android/path_utils.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/path_service.h"

using namespace base;
#endif

namespace blogrss {
  
bool EnvInit::InitializeEnvironment(int argc, char** argv) {
  base::CommandLine::Init(argc, argv);

#if defined(OS_ANDROID)
  InitAndroidLogging();
  InitAndroidPaths();
#else
  // Initialize logging.
  base::FilePath exe;
  PathService::Get(base::FILE_EXE, &exe);
  base::FilePath log_filename = exe.ReplaceExtension(FILE_PATH_LITERAL("log"));
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LOG_TO_ALL;
  settings.log_file = log_filename.value().c_str();
  settings.delete_old = logging::DELETE_OLD_LOG_FILE;
  logging::InitLogging(settings);
  // We want process and thread IDs because we may have multiple processes.
  // Note: temporarily enabled timestamps in an effort to catch bug 6361.
  logging::SetLogItems(true, true, true, true);
#endif  // else defined(OS_ANDROID)

  base::i18n::InitializeICU();
  
  return true;
}

#if defined(OS_ANDROID)
void EnvInit::InitAndroidLogging() {
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;
  logging::InitLogging(settings);
  // To view log output with IDs and timestamps use "adb logcat -v threadtime".
  logging::SetLogItems(false,    // Process ID
                       false,    // Thread ID
                       false,    // Timestamp
                       false);   // Tick count
}

void EnvInit::InitAndroidPaths() {
  InitPathProvider(DIR_MODULE);
  InitPathProvider(DIR_ANDROID_APP_DATA);
}

bool EnvInit::GetProviderPath(int key, base::FilePath* result) {
  switch (key) {
    case base::DIR_MODULE: {
      return base::android::GetExternalStorageDirectory(result);
    }
    case base::DIR_ANDROID_APP_DATA: {
      // For tests, app data is put in external storage.
      return base::android::GetExternalStorageDirectory(result);
    }
    default:
      return false;
  }
}

void EnvInit::InitPathProvider(int key) {
  base::FilePath path;
  // If failed to override the key, that means the way has not been registered.
  if (GetProviderPath(key, &path) && !PathService::Override(key, path))
    PathService::RegisterProvider(&GetProviderPath, key, key + 1);
}
#endif
  
}
