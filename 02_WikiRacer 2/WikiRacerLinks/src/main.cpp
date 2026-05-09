#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;

string getFile(string filename);
template <typename T>
void print_unordered_set(const unordered_set<T> &myUnorder_set);
/*
 * Note that you have to pass in the file as a single string
 * into the findWikiLinks function!
 * So we have to turn the passed-in file into a single string...
 * does that sound familiar at all?
 */
unordered_set<string> findWikiLinks(const string& page_html) {
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
        result.insert(str_portion);
    }

    return result;
}

int main() {
    /* Note if your file reading isn't working, please go to the
     * projects tab on the panel on the left, and in the run section,
     * uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */

    cout << "Enter a file name: ";
    string filename;
    getline(std::cin, filename);
    string page_html;

    // TODO: Create a filestream from the filename, and convert it into
    //       a single string of data called page_html (declared above)

    // Write code here
    page_html = getFile(filename);

    unordered_set<string> validLinks = findWikiLinks(page_html);

    // TODO: Print out the validLinks set above.
    //       You can print it out in any format; this is just for you
    //       to be able to compare your results with the [output] results
    //       under the /res folder.

    // Write code here
    print_unordered_set(validLinks);

    return 0;
}


string getFile(string filename){
    std::ifstream file(filename);
    string page_html;
    string line;
    while(getline(file, line)){
        page_html += line;
    }
    return page_html;
}



template <typename T>
void print_unordered_set(const unordered_set<T> &myUnorder_set){
    for(auto element : myUnorder_set){
        cout << element << endl;
    }
}
