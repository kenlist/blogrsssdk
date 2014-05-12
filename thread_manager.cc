#include "thread_manager.h"

#define NET_THREAD_NAME "thread_manager_net_thread"
#define FILE_THREAD_NAME "thread_manager_file_thread"

using namespace base;

namespace blogrss {
    
ThreadManager::ThreadManager()
  : ui_loop_(NULL),
    net_thread_(NET_THREAD_NAME),
    file_thread_(FILE_THREAD_NAME)  {
}

ThreadManager::~ThreadManager() {
}

ThreadManager* ThreadManager::GetInstance() {
  return Singleton<ThreadManager>().get();
}

bool ThreadManager::InitalizeThreads() {
  ui_loop_ = new MessageLoopForUI();
#if defined(OS_IOS)
  ui_loop_->Attach();
#elif defined(OS_ANDROID)
  ui_loop_->Start();
#endif

  Thread::Options options(MessageLoop::TYPE_IO, 0);
  net_thread_.StartWithOptions(options);
  file_thread_.StartWithOptions(options);
  return true;
}
    
}
