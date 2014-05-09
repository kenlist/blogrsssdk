#ifndef RSS_INFO_H_
#define RSS_INFO_H_

namespace blogrss {

typedef struct tagRSSItemInfo {
  std::string title;
  struct tm pub_date;
  std::string link;
} RSSItemInfo;

typedef ScopedVector<RSSItemInfo> RSSInfo;

}

#endif
