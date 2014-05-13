#ifndef RSS_XML_ANALYZER_H_
#define RSS_XML_ANALYZER_H_

#include "rss_item.h"

namespace blogrss {

class RSSXMLAnalyzer {
  public:
    RSSXMLAnalyzer();
    ~RSSXMLAnalyzer();
  
    RSSItemList AnaylzeRSSInfo(const std::string& xml_string);
};

}

#endif
