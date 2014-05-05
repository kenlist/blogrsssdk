#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

namespace blogrss {
    
class ThreadManager {
  public:
    static ThreadManager *GetInstance();
    
    ThreadManager();
    ~ThreadManager();
    
    bool InitalizeThreads();
    
    base::MessageLoop *ui_loop() const { return ui_loop_; }
    base::MessageLoop *net_loop() const { return net_thread_.message_loop(); }
    
  private:
    base::MessageLoopForUI *ui_loop_;
    base::Thread net_thread_;
  
    DISALLOW_COPY_AND_ASSIGN(ThreadManager);
};
  
}

#endif
