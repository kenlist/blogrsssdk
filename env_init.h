#ifndef ENV_INIT_H_
#define ENV_INIT_H_

namespace blogrss {

class EnvInit {
  public:
    static bool InitializeEnvironment(int argc, char** argv);

#if defined(OS_ANDROID)
  private:
    static void InitAndroidLogging();
    static void InitAndroidPaths();

    static bool GetProviderPath(int key, base::FilePath* result);
    static void InitPathProvider(int key);
#endif
};
  
}

#endif
