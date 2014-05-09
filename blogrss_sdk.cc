#include "blogrss_sdk.h"
#include "http_request.h"
#include "thread_manager.h"
#include "rss_xml_analyzer.h"
#include "env_init.h"

#define RSS_URL "http://geekluo.com/feed.xml"

using namespace base;
using namespace net;

namespace blogrss {
  
BlogRSSSDK* BlogRSSSDK::GetInstance() {
  return Singleton<BlogRSSSDK>::get();
}

BlogRSSSDK::BlogRSSSDK()
    : analyzer_(new RSSXMLAnalyzer) {
  this->AddRef(); //never release by refptr
  request_ = scoped_refptr<HttpRequest>(new HttpRequest);
}

BlogRSSSDK::~BlogRSSSDK() {

}

bool BlogRSSSDK::StartWithoutEnvInit() {
  return ThreadManager::GetInstance()->InitalizeThreads();
}
    
bool BlogRSSSDK::Start(int argc, char** argv) {
  EnvInit::InitializeEnvironment(argc, argv);
  return StartWithoutEnvInit();
}

bool BlogRSSSDK::FetchRSS() {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_UI);
  return request_->StartWithURL(RSS_URL, Bind(&BlogRSSSDK::OnFetchRSS, this));
}

void BlogRSSSDK::OnFetchRSS(int ret_code, const std::string& response_data) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_IO);
 
  ret_code_ = ret_code;
  if (ret_code == 200) {
    rss_info_ = analyzer_->AnaylzeRSSInfo(response_data);
  }
  
  //fire delegate on ui_thread
  ThreadManager::GetInstance()->ui_loop()->PostTask(FROM_HERE,
                                                    Bind(&BlogRSSSDK::FireRSSFetchedOnUI,
                                                    this));
}

void BlogRSSSDK::FireRSSFetchedOnUI() {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_UI);
  if (delegate_) {
    delegate_->OnRSSFetched(ret_code_, rss_info_.Pass());
  }
  ret_code_ = 0;
}

}
