#include "rss_xml_analyzer.h"

using namespace std;
using namespace blogrss;

RSSXMLAnalyzer::RSSXMLAnalyzer() {

}

RSSXMLAnalyzer::~RSSXMLAnalyzer() {

}
  
scoped_ptr<RSSInfo> RSSXMLAnalyzer::AnaylzeRSSInfo(const string& xml_string) {
  scoped_ptr<RSSInfo> rss_info(new RSSInfo);
  
  
  
  return rss_info.Pass();
}
