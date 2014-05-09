#ifndef RSS_XML_ANALYZER_H_
#define RSS_XML_ANALYZER_H_

#include "rss_info.h"

namespace blogrss {

class RSSXMLAnalyzer {
  public:
    RSSXMLAnalyzer();
    ~RSSXMLAnalyzer();
  
    RSSInfo AnaylzeRSSInfo(const std::string& xml_string);
};

}

#endif
