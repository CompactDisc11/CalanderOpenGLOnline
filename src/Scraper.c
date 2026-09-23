#include "Scraper.h"



size_t WriteHTMLCallBack(void *contents, size_t size, size_t nmeb, void *userp)
{
        size_t realsize = size  *nmeb;
        CurlResponse *mem = (CurlResponse*)userp;
        char *ptr  = realloc(mem->html, mem->size+realsize+1);
        if (!ptr)
        {
            return 0;
        }
        mem->html = ptr;
        memcpy(&(mem->html[mem->size]), contents, realsize);
        mem->size += realsize;
        mem->html[mem->size] = 0;
        return realsize;
}

CurlResponse getHTML(char *url)
{
    CURL *curl = curl_easy_init();
    CurlResponse res = {.html = malloc(1), .size = 0};
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteHTMLCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&res);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res;


}

htmlDocPtr ParseHTML(char *html, size_t size)
{   
    // printf("%s\n", html);
    return htmlReadMemory(html, size, NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
}

xmlXPathObjectPtr GetNodesByXPath(htmlDocPtr doc, char *xpathExpr)
{
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    return xmlXPathEvalExpression((xmlChar *)xpathExpr, context);
}

int getHeadlines(htmlDocPtr doc, char stringHeadlines[25][999])
{   
    printf("Scraping\n");
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr items = xmlXPathEvalExpression((xmlChar *)"//div[contains(@class,'columns large-12 article-container')]", context);
    int count = 0;
    printf("Number of items %d\n", items->nodesetval->nodeNr);
    for (int i = 0; i < items->nodesetval->nodeNr; ++i)

    {

        xmlNodePtr node = items->nodesetval->nodeTab[i];
        xmlXPathSetContextNode(node, context);
        char *headline  = (char *)xmlGetProp(xmlXPathEvalExpression((xmlChar *)".//article/article/a/div/h2/span", context)->nodesetval->nodeTab[0], (xmlChar *)"title");
        // printf("Headline name: %s\n", headline); 
        memcpy(stringHeadlines[i], headline, 999);
    }
    xmlXPathFreeContext(context);
    xmlXPathFreeObject(items);
    return 0;
}

int getMostRead(htmlDocPtr doc, char mostPopular[8][999])
{
    printf("Scraping\n");
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr items = xmlXPathEvalExpression((xmlChar *)"//li[contains(@class,'most-popular-page-list-item')]", context);
    int count = 0;
    printf("Number of items %d\n", items->nodesetval->nodeNr);
    for (int i = 0; i < items->nodesetval->nodeNr; ++i)

    {

        xmlNodePtr node = items->nodesetval->nodeTab[i];
        xmlXPathSetContextNode(node, context);
        char *headline  = (char *)xmlNodeGetContent(xmlXPathEvalExpression((xmlChar *)".//article/div/a/div/h3/span", context)->nodesetval->nodeTab[0]);
        printf("%d: Most Popular: %s\n", i, headline); 
        memcpy(mostPopular[i], headline, 999);
    }
    xmlXPathFreeContext(context);
    xmlXPathFreeObject(items);
    return 0;
}
