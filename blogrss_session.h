#ifndef BLOGRSS_SESSION_H_
#define BLOGRSS_SESSION_H_

namespace blogrss {
    
class BlogRSSSession {
  public:
    static BlogRSSSession *GetInstance();
    
    BlogRSSSession();
    ~BlogRSSSession();
    
    bool Start();
  private:
        
    DISALLOW_COPY_AND_ASSIGN(BlogRSSSession);
};
    
}

#endif
