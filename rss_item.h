#ifndef RSS_ITEM_H_
#define RSS_ITEM_H_

namespace blogrss {

typedef struct tagRSSItem {
  std::string title;
  struct tm pub_date;
  std::string link;
} RSSItem;

typedef ScopedVector<RSSItem> RSSItemList;

}

#endif
