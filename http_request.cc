#include "http_request.h"
#include "thread_manager.h"

using namespace std;
using namespace base;
using namespace net;

namespace blogrss {

const int kDefaultMaxResponseBytes = 1048576;   // 1 megabyte
  
HttpRequest::HttpRequest()
    : buf_(new IOBuffer(kBufSize)) {

}

HttpRequest::~HttpRequest() {
    
}

bool HttpRequest::StartWithURL(const std::string& url_string, const CompleteCallback complete_callback) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_UI);

  if (url_string.empty()) {
    return false;
  }
  
  url_ = GURL(url_string);
  if (!url_.is_valid()) {
    return false;
  }
  
  complete_callback_ = complete_callback;
  
  ThreadManager::GetInstance()->net_loop()->PostTask(FROM_HERE,
                                                     base::Bind(&HttpRequest::ActualStartOnNetThread,
                                                                this));
  return true;
}

void HttpRequest::ActualStartOnNetThread() {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_IO);
  
  if (request_) {
    //must clear request first
    request_.reset();
  }
  
  context_.reset(builder_.Build());
  request_.reset(new URLRequest(url_, DEFAULT_PRIORITY, this, context_.get()));
  request_->set_method("GET");
  request_->Start();
}

void HttpRequest::ReadBody(net::URLRequest* request) {
  while (true) {
    int num_bytes;
    if (!request->Read(buf_.get(), kBufSize, &num_bytes)) {
      //Check whether the read failed synchronously
      if (!request->status().is_io_pending())
        complete_callback_.Run(request->GetResponseCode(), bytes_read_so_far_);
      return;
    }
    if (!ConsumeBytesRead(request, num_bytes)) {
      return;
    }
  }
}

bool HttpRequest::ConsumeBytesRead(net::URLRequest* request, int num_bytes) {
  if (num_bytes <= 0) {
    // Error while reading, or EOF.
    complete_callback_.Run(request->GetResponseCode(), bytes_read_so_far_);
    return false;
  }
  
  if (num_bytes + bytes_read_so_far_.size() > kDefaultMaxResponseBytes) {
    request->Cancel();
    complete_callback_.Run(0, "too big");
    return false;
  }
  
  bytes_read_so_far_.append(buf_->data(), num_bytes);
  return true;
}

void HttpRequest::OnResponseStarted(URLRequest* request) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_IO);

  bytes_read_so_far_.clear();
  if (request->GetResponseCode() != 200) {
    complete_callback_.Run(request->GetResponseCode(), "response code error");
    return;
  }
  
  ReadBody(request);
}

void HttpRequest::OnReadCompleted(net::URLRequest* request, int bytes_read) {
  DCHECK(MessageLoop::current()->type() == MessageLoop::TYPE_IO);
  
  if (ConsumeBytesRead(request, bytes_read)) {
    // Keep reading.
    ReadBody(request);
  }
}

}
