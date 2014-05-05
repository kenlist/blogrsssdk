#include "blogrss_session.h"
#include "thread_manager.h"

using namespace base;

namespace blogrss {
    
BlogRSSSession *BlogRSSSession::GetInstance() {
    return Singleton<BlogRSSSession>::get();
}

BlogRSSSession::BlogRSSSession() {

}

BlogRSSSession::~BlogRSSSession() {
    
}
    
bool BlogRSSSession::Start() {
    return ThreadManager::GetInstance()->InitalizeThreads();
}

}
