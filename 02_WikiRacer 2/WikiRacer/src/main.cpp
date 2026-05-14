#include <iostream>     // for cout, cin
#include <fstream>      // for ifstream
#include <sstream>      // for stringstream
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"

using std::cout;            using std::endl;
using std::ifstream;        using std::stringstream;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;   using std::cin;

/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */

int similarity(const unordered_set<string>& v1, const unordered_set<string>& v_end){
    int count = 0;
    for(string str : v_end){
        if(v1.find(str) != v1.end())
            count++;
    }
    return count;
}


vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: 1. Once your file reading is working, replace the below
    //          return statement with "return {};".
    //       2. Make sure that you've copied over your findWikiLinks method
    //          from Part A into wikiscraper.cpp.
    //       3. Finally, implement this function per Part B in the handout!
    //
    //                Best of luck!

    // creates WikiScraper object
    WikiScraper scraper;

    // gets the set of links on page specified by end_page
    // variable and stores in target_set variable
    auto target_set = scraper.getLinkSet(end_page);

    // ... rest of implementation

    // Comparison function for priority_queue
    // auto cmpFn = /* declare lambda comparator function */;
    // [capture list] (parameter list) -> return type { function body }
    auto cmpFn = [&scraper, &target_set](vector<string> v1, vector<string> v2) ->bool {
        auto v1_linkSet = scraper.getLinkSet(v1.back());
        auto v2_linkSet = scraper.getLinkSet(v2.back());
        return similarity(v1_linkSet, target_set) < similarity(v2_linkSet, target_set);
    };

    // creates a priority_queue names ladderQueue
    std::priority_queue<vector<string>, vector<vector<string>>,
                        decltype(cmpFn)> ladderQueue(cmpFn);

    // ... rest of implementation

    ladderQueue.push({start_page});
    while(!ladderQueue.empty()){
        vector<string> cur_ladder = ladderQueue.top();
        ladderQueue.pop();
        unordered_set<string> cur_page_links = scraper.getLinkSet(cur_ladder.back());
        for(const string& link : cur_page_links){
            if(link == end_page){
                cur_ladder.push_back(link);
                return cur_ladder;
            }
            else if(find(cur_ladder.begin(), cur_ladder.end(), link) == cur_ladder.end()){
                cur_ladder.push_back(link);
                ladderQueue.push(cur_ladder);
            }
        }
    }

    return {};
    // return {"File reading works!", start_page, end_page};
}

// //PartA中我自己自定义的函数，为了缩减main函数内容
// string getFile(string filename){
//     std::ifstream file(filename);
//     string page_html;
//     string line;
//     while(getline(file, line)){
//         page_html += line;
//     }
//     return page_html;
// }

int main() {
    /* Container to store the found ladders in */
    vector<vector<string>> outputLadders;

    cout << "Enter a file name: ";
    string filename;
    getline(cin, filename);

    // TODO: Create a filestream from the filename.
    //       For each pair {start_page, end_page} in the input file,
    //       retrieve the result of findWikiLadder(start_page, end_page)
    //       and append that vector to outputLadders.

    // Write code here

    ifstream file(filename);
    string start_page;
    string end_page;
    file >> start_page >> end_page;

    outputLadders.push_back(findWikiLadder(start_page, end_page));

    /*
     * Print out all ladders in outputLadders.
     * We've already implemented this for you!
     */
    for (auto& ladder : outputLadders) {
        if(ladder.empty()) {
            cout << "No ladder found!" << endl;
        } else {
            cout << "Ladder found:" << endl;
            cout << "\t" << "{";

            std::copy(ladder.begin(), ladder.end() - 1,
                      std::ostream_iterator<string>(cout, ", "));
            /*
             * The above is an alternate way to print to cout using the
             * STL algorithms library and iterators. This is equivalent to:
             *    for (size_t i = 0; i < ladder.size() - 1; ++i) {
             *        cout << ladder[i] << ", ";
             *    }
             */
            cout << ladder.back() << "}" << endl;
        }
    }
    return 0;
}




