#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "curl/curl.h"
#include "libxml2/libxml/HTMLparser.h"
#include "libxml2/libxml/xpath.h"

typedef struct {
    char *html;
    int size;
} CurlResponse;

typedef struct {
    char *headline;
    char *url;
} Headline;


size_t WriteHTMLCallBack(void *contents, size_t size, size_t nmeb, void *userp);
htmlDocPtr ParseHTML(char *html, size_t size);
xmlXPathObjectPtr GetNodesByXPath(htmlDocPtr doc, char *xpathExpr);
CurlResponse getHTML(char *url);
int getHeadlines(htmlDocPtr doc, char stringHeadlines[25][999]);
int getMostRead(htmlDocPtr doc, char mostPopular[8][999]);
