#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include "wikiscraper.h"
#include "error.h"

using std::cout;            using std::endl;
using std::cerr;            using std::string;
using std::unordered_map;   using std::unordered_set;

/*
 * You should delete the code in this function and
 * fill it in with your code from part A of the assignment.
 *
 * If you used any helper functions, just put them above this function.
 */
unordered_set<string> findWikiLinks(const string& page_html) {
    // TODO: Remove all the code in this function and fill
    //       in with your findWikiLinks code from part A
    std::unordered_set<string> result;
    string beginKey = "<a href=\"/wiki/";
    char endKey = '\"'; 
    auto curIt = page_html.begin();
    auto linkStartId = curIt;
    auto linkEndId = curIt;

    while(curIt != page_html.end()){
        linkStartId = std::search(curIt, page_html.end(), beginKey.begin(), beginKey.end());  //返回"<a href=\"/wiki/"的起始位置
        if(linkStartId == page_html.end())  break;
        linkStartId += beginKey.size();      //更改为"<a href=\"/wiki/"的末端位置
        curIt = linkStartId;

        linkEndId = std::find(curIt, page_html.end(), endKey);
        curIt = linkEndId;

        auto str_portion = string(linkStartId, linkEndId);
        auto isAllLegal = [](char c) -> bool {
            return (c == '_') || (c == '%') || (c == '(') || (c == ')') || isalnum(c); // isalnum(c) = isalpha(c) || isdigit(c)
        };  // [capture list] (parameter list) -> return type { function body }
        if(std::all_of(str_portion.begin(), str_portion.end(),isAllLegal))
            result.insert(str_portion);
    }

    return result;
    
    // errorPrint();
    // errorPrint("If you are seeing this message, you haven't implemented");
    // errorPrint("the find_wiki_links method in wikiscraper.cpp.");
    // errorPrint();
    // cout << endl;
    // return {};

}


/*
 * ==================================================================================
 * |                           DON"T EDIT ANYTHING BELOW HERE                       |
 * ==================================================================================
 */
unordered_set<string> WikiScraper::getLinkSet(const string& page_name) {
    if(linkset_cache.find(page_name) == linkset_cache.end()) {
        auto links = findWikiLinks(getPageSource(page_name));
        linkset_cache[page_name] = links;
    }
    return linkset_cache[page_name];
}


WikiScraper::WikiScraper() {
    (void)getPageSource("Main_Page");
#ifdef _WIN32
    // define something for Windows
    system("cls");
#else
    // define it for a Unix machine
    system("clear");
#endif
}


string createPageUrl(const string& page_name) {
    return "https://en.wikipedia.org/wiki/" + page_name;
}

void notFoundError(const string& msg, const string& page_name, const string& url) {
    const string title = "    AN ERROR OCCURED DURING EXECUTION.    ";
    const string border(title.size() + 4, '*');
    cerr << endl;
    errorPrint(border);
    errorPrint("* " + title + " *");
    errorPrint(border);
    errorPrint();
    errorPrint("Reason: " + msg);
    errorPrint();
    errorPrint("Debug Information:");
    errorPrint();
    errorPrint("\t- Input parameter: " + page_name);
    errorPrint("\t- Attempted url: " + url);
    errorPrint();
}

string WikiScraper::getPageSource(const string &page_name) {
    const static string not_found = "Wikipedia does not have an article with this exact name.";
    if(page_cache.find(page_name) == page_cache.end()) {
        QUrl url(createPageUrl(page_name).c_str()); // need c string to convert to QString

        QNetworkRequest request(url);

        QNetworkReply *reply(manager.get(request));

        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()) , &loop, SLOT(quit()));
        loop.exec();

        string ret = reply->readAll().toStdString();
        if(std::search(ret.begin(), ret.end(), not_found.begin(), not_found.end()) != ret.end()){
            notFoundError("Page does not exist!", page_name, url.toString().toStdString());
            return "";
        }
        size_t indx = ret.find("plainlinks hlist navbar mini");
        if(indx != string::npos) {
            return ret.substr(0, indx);
        }
        page_cache[page_name] = ret;
    }
    return page_cache[page_name];
}





