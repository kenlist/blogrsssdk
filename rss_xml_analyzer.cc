#include "rss_xml_analyzer.h"

using namespace std;
using namespace blogrss;

RSSXMLAnalyzer::RSSXMLAnalyzer() {

}

RSSXMLAnalyzer::~RSSXMLAnalyzer() {

}
  
RSSInfo RSSXMLAnalyzer::AnaylzeRSSInfo(const string& xml_string) {
  RSSInfo rss_info;
  
  xmlKeepBlanksDefault(0);
  xmlDocPtr doc = xmlReadMemory(xml_string.c_str(),
                                xml_string.length(),
                                NULL,
                                "UTF-8",
                                XML_PARSE_RECOVER);
  
  xmlXPathContextPtr xpath_context = xmlXPathNewContext(doc);
  xmlXPathObjectPtr xpath_obj = xmlXPathEvalExpression(BAD_CAST"//item", xpath_context);
  
  if (xpath_obj) {
    xmlNodeSetPtr nodeset = xpath_obj->nodesetval;
    xmlNodePtr node = NULL;
    for (int i = 0; i < nodeset->nodeNr; i++) {
      node = nodeset->nodeTab[i];
      
      scoped_ptr<RSSItemInfo> item_info(new RSSItemInfo);
      
      xmlNodePtr child_node = node->xmlChildrenNode;
      while (child_node) {
        xmlChar* content = NULL;
        if (xmlStrEqual(child_node->name, BAD_CAST"title")) {
          content = xmlNodeGetContent(child_node);
          item_info->title = (char*)content;
        } else if (xmlStrEqual(child_node->name, BAD_CAST"pubDate")) {
          time_t t = time(NULL);
          char buf[100];
          strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S %z", localtime(&t));
        
          content = xmlNodeGetContent(child_node);
          DCHECK(strptime((const char*)content, "%a, %d %b %Y %H:%M:%S %z", &item_info->pub_date));
        } else if (xmlStrEqual(child_node->name, BAD_CAST"link")) {
          content = xmlNodeGetContent(child_node);
          item_info->link = (char*)content;
        }
        
        xmlFree(content);
        child_node = child_node->next;
      }
      
      rss_info.push_back(item_info.release());
    }
  }
  
  xmlXPathFreeObject(xpath_obj);
  xmlXPathFreeContext(xpath_context);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return rss_info.Pass();
}
