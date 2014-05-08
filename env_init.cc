#include "env_init.h"

namespace blogrss {
  
bool EnvInit::InitializeEnvironment(int argc, char** argv) {
  base::CommandLine::Init(argc, argv);

#if defined(OS_ANDROID)
  InitAndroidTest();
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
  
}
