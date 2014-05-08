#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

namespace blogrss {
  
class HttpRequest
    : public net::URLRequest::Delegate,
      public base::RefCountedThreadSafe<HttpRequest> {
  public:
    typedef base::Callback<void(int ret_code, const std::string& response_data)> CompleteCallback;
    
  public:
    HttpRequest();
    ~HttpRequest();
    
    bool StartWithURL(const std::string& url_string, const CompleteCallback complete_callback);
  
  private:
    void ActualStartOnNetThread();
    
    void ReadBody(net::URLRequest* request);
    bool ConsumeBytesRead(net::URLRequest* request, int num_bytes);
  
    virtual void OnResponseStarted(net::URLRequest* request);
    virtual void OnReadCompleted(net::URLRequest* request, int bytes_read);
    
  private:
    scoped_ptr<net::URLRequest> request_;
    scoped_ptr<net::URLRequestContext> context_;
    net::URLRequestContextBuilder builder_;
        
    GURL url_;
    CompleteCallback complete_callback_;
    
    //for read bytes from request
    enum { kBufSize = 4096 };
    scoped_refptr<net::IOBuffer> buf_;
    std::string bytes_read_so_far_;
        
    DISALLOW_COPY_AND_ASSIGN(HttpRequest);
};
    
}

#endif
