#include "rss_xml_analyzer.h"

using namespace std;
using namespace blogrss;

RSSXMLAnalyzer::RSSXMLAnalyzer() {

}

RSSXMLAnalyzer::~RSSXMLAnalyzer() {

}
  
RSSItemList RSSXMLAnalyzer::AnaylzeRSSInfo(const string& xml_string) {
  RSSItemList rss_item_list;
  
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
      
      scoped_ptr<RSSItem> rss_item(new RSSItem);
      
      xmlNodePtr child_node = node->xmlChildrenNode;
      while (child_node) {
        xmlChar* content = NULL;
        if (xmlStrEqual(child_node->name, BAD_CAST"title")) {
          content = xmlNodeGetContent(child_node);
          rss_item->title = (char*)content;
        } else if (xmlStrEqual(child_node->name, BAD_CAST"pubDate")) {        
          content = xmlNodeGetContent(child_node);
          strptime((const char*)content, "%a, %d %b %Y %H:%M:%S %z", &rss_item->pub_date);
        } else if (xmlStrEqual(child_node->name, BAD_CAST"link")) {
          content = xmlNodeGetContent(child_node);
          rss_item->link = (char*)content;
        }
        
        xmlFree(content);
        child_node = child_node->next;
      }
      
      rss_item_list.push_back(rss_item.release());
    }
  }
  
  xmlXPathFreeObject(xpath_obj);
  xmlXPathFreeContext(xpath_context);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return rss_item_list.Pass();
}
