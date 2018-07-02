#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;


struct Tag {
    string name;
    map<string, string> atts;
    vector<Tag *> children;
    int depth;
};

void read_tag(const string& str, Tag *tag) {
    int nos = count_if(str.begin(), str.end(), [](const char& c) {
        return c==' '; }); // nos: number of substrings in string
    vector<string> los(nos+1); // los: list of substrings in string
    istringstream iss(str);
    for (auto& s : los)
        iss >> s;
    if (los.size() == 1) { // no attributes single tag
        tag->name = los[0].substr(1, los[0].size()-2);
    } else {
        tag->name = los[0].substr(1);
        int noa = (los.size()-1)/3; // number of attributes
        for (int ai = 0; ai < noa; ++ai) {
            string attn = los[1+ai*3+0];
            string attv = los[1+ai*3+2];
            string::size_type q1 = attv.find('"');
            string::size_type q2 = attv.rfind('"');
            attv = attv.substr(q1+1, q2-q1-1);
            tag->atts[attn] = attv;
        }
    }
}

int main() {
    int n, q;
    string header;
    getline(cin, header);
    istringstream(header) >> n >> q;
    vector<string> lines(n), queries(q);
    for (auto& line : lines)
        getline(cin, line);
    for (auto& query : queries)
        getline(cin, query);
    int noc = count_if(lines.begin(), lines.end(), [](const string& s) {
        return s[1]=='/'; }); // number of closing tags
    vector<Tag> tags(noc); // repository of tags
    int tci = 0; // tag current index
    map<string, Tag*> name_tag; // name-tag map
    vector<Tag*> open_tags;
    for (const auto& line : lines) {
        if (line[1] != '/') { // opening tag
            Tag *tag = &tags[tci];
            tag->depth = open_tags.size();
            read_tag(line, tag);
            name_tag[tag->name] = tag;
            if (tag->depth > 0)
                open_tags.back()->children.push_back(tag);
            open_tags.push_back(tag);
            tci += 1;
        } else if (line[1] == '/') { // closing tag
            string tag_name = line.substr(2, line.size()-3);
            for (auto it = open_tags.begin(); it != open_tags.end(); ) {
                if ((*it)->name == tag_name)
                    it = open_tags.erase(it);
                else
                    ++it;
            }
        }
    }
    /*
    cout << '>' << open_tags.size() << '\n';
    cout << "Tags:\n";
    for (const auto& t : tags) {
        cout << ' ' << t.name << ' ' << t.depth << flush;
        cout << " (" << flush;
        for (const auto& a : t.atts)
            cout << ' ' << a.first << ' ' << a.second << flush;
        cout << " ) (" << flush;
        for (const auto& c : t.children)
            cout << ' ' << c->name << flush;
        cout << " )\n";
    }
    */
    for (const auto& query : queries) {
        int nod = count_if(query.begin(), query.end(), [](const char& c) {
            return c=='.'; }); // number of dot punctuations
        vector<string> query_tags(nod+1);
        string att_name = query.substr(query.find('~')+1);
        istringstream iss(query);
        for (auto& tag : query_tags) {
            getline(iss, tag, '.');
            if (tag.find('~') != string::npos)
                tag = tag.substr(0, tag.find('~'));
        }
        int m = 0; // number of tags in the sequence
        string prev = "";
        for (const auto& tag_name : query_tags) {
            if (prev != "") {
                bool child_found = false;
                if (name_tag.find(prev) != name_tag.end()) {
                    for (const auto& c : name_tag[prev]->children) {
                        if (c->name == tag_name) {
                            child_found = true;
                            break;
                        }
                    }
                }
                if (!child_found)
                    break;
            }
            prev = tag_name;
            m += 1;
        }
        if (m != nod+1) {
            cout << "Not Found!\n";
        } else {
            string tag_name = query_tags.back();
            if (name_tag.find(tag_name) == name_tag.end()) {
                cout << "Not Found!\n";
            } else {
                Tag *tag = name_tag[tag_name];
                if (tag->depth != m-1) {
                    cout << "Not Found!\n";
                } else {
                    if (tag->atts.find(att_name) == tag->atts.end())
                        cout << "Not Found!\n";
                    else
                        cout << tag->atts[att_name] << "\n";
                }
            }
        }
    }
    return 0;
}
