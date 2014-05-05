#include "thread_manager.h"

#define NET_THREAD_NAME "thread_manager_net_thread"

using namespace base;

namespace blogrss {

ThreadManager *ThreadManager::GetInstance() {
  return Singleton<ThreadManager>().get();
}
    
ThreadManager::ThreadManager()
  : ui_loop_(NULL),
    net_thread_(NET_THREAD_NAME)  {
}

ThreadManager::~ThreadManager() {
}

bool ThreadManager::InitalizeThreads() {
  ui_loop_ = new MessageLoopForUI();
#if defined(OS_IOS)
  ui_loop_->Attach();
#elif defined(OS_ANDROID)
  ui_loop_->Start();
#endif

  return true;
}
    
}
