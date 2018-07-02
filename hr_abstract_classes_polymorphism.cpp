#include <map>
#include <string>
#include <iostream>

struct Node {
    int key, value;
    Node *next, *prev;
    Node(const int& _key, const int& _value) : key(_key), value(_value),
        next(), prev() { }
};

class Cache { 
protected:
   std::map<int, Node*> mp; // map the key to the node in the linked list
   int cp;  // capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0;
   virtual int get(int) = 0;
};

class LRUCache : public Cache {
public:
    LRUCache(const int& _cp) : Cache() { cp = _cp; }
    void set(int _key, int _value) override {
        if (mp.find(_key) != mp.end()) {
            mp[_key]->value = _value;
        } else {
            Node *nn = new Node(_key, _value); // new node
            if (head) {
                nn->next = head;
                head->prev = nn;
            }
            head = nn;
            if (!tail)
                tail = head;
            if (mp.size() == cp) { // capacity exhausted
                mp.erase(tail->key);
                tail = tail->prev;
            }
            mp[_key] = nn;
        }
    }
    int get(int _key) override {
        if (mp.find(_key) == mp.end())
            return -1;
        return mp[_key]->value;
    }
};

int main() {
    int n, capacity;
    std::cin >> n >> capacity;
    LRUCache l(capacity);
    for (int i = 0; i < n; ++i) {
        std::string command;
        std::cin >> command;
        if (command == "get") {
            int key;
            std::cin >> key;
            std::cout << l.get(key) << std::endl;
        } else if (command == "set") {
            int key, value;
            std::cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}
