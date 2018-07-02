#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
struct Workshop {
    int start_time, duration, end_time;
};

struct Available_Workshops {
    int n;
    Workshop *workshops;
};

Available_Workshops* initialize(int start_time[], int duration[], int n) {
    Available_Workshops *aw = new Available_Workshops;
    aw->n = n;
    aw->workshops = new Workshop[n];
    for (int i = 0; i < n; ++i) {
        aw->workshops[i].start_time = start_time[i];
        aw->workshops[i].duration = duration[i];
        aw->workshops[i].end_time = start_time[i] + duration[i];        
    }
    return aw;
}

bool Intersects(const Workshop& wi, const Workshop& wj) {
    return ((wj.start_time >= wi.start_time and wj.start_time < wi.end_time)
        or (wj.end_time > wi.start_time and wj.end_time <= wi.end_time)
        or (wi.start_time >= wj.start_time and wi.start_time < wj.end_time));
}

int NodeExpand(const vector<int>& node, const vector<int>& workshops,
    Available_Workshops* ptr) {
    vector<int> poss; // workshop possibilities to include in current node
    for (const auto& i : workshops) {
        const Workshop& wi = ptr->workshops[i];
        bool conflict = false;
        for (const auto& j : node) {
            const Workshop& wj = ptr->workshops[j];
            if (Intersects(wi, wj)) {
                conflict = true;
                break;
            }
        }
        if (not conflict)
            poss.push_back(i);
    }

    if (poss.size() <= 1)
        return node.size() + poss.size();

    vector<int> conflicts(poss.size());
    for (int i = 0; i < poss.size(); ++i) {
        const Workshop& wi = ptr->workshops[poss[i]];
        for (int j = 0; j < poss.size(); ++j) {
            if (i == j)
                continue;
            const Workshop& wj = ptr->workshops[poss[j]];
            if (Intersects(wi, wj))
                conflicts[i]++;
        }
    }

    vector<int> maxs(poss.size());
    for (int i = 0; i < poss.size(); ++i) {
        if (conflicts[i] == 0) {
            maxs[i] = node.size()+1;
        } else {
            vector<int> new_node(node);
            new_node.push_back(poss[i]);
            maxs[i] = NodeExpand(new_node, workshops, ptr);
        }
        if (maxs[i] == node.size()+poss.size())
            return maxs[i]; // maximum depth reached
    }

    return *max_element(maxs.begin(), maxs.end());
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    //clock_t start = clock();

    vector< pair<int, int> > tt(ptr->n);
    for (int i = 0; i < ptr->n; ++i) {
        tt[i].first = ptr->workshops[i].start_time;
        tt[i].second = ptr->workshops[i].end_time;
    }
    vector<int> idx(tt.size());
    iota(idx.begin(), idx.end(), 0);
    stable_sort(idx.begin(), idx.end(), [&](int id0, int id1) {
        return tt[id0] < tt[id1]; } );

    //clock_t end = clock();
    //cout << "build time table -> " << (end - start)/(double)CLOCKS_PER_SEC << " sec.\n";
    //start = end;

    set<int> removed;
    for (int i = 0; i < idx.size(); ++i) {
        const pair<int, int>& pi = tt[idx[i]];
        for (int j = i+1; j < idx.size(); ++j) {
            const pair<int, int>& pj = tt[idx[j]];
            if (pj.first >= pi.second)
                break;
            if (pi.first <= pj.first and pi.second >= pj.second) {
                removed.insert(i);
                break;
            }
        }
    }

    //end = clock();
    //cout << "remove covering -> " << (end - start)/(double)CLOCKS_PER_SEC << " sec.\n";
    //start = end;

    for (int i = 0; i < idx.size(); ++i) {
        if (removed.find(i) != removed.end())
            continue;
        const pair<int, int>& pi = tt[idx[i]];
        bool first_intersection = false, second_intersection = false;
        for (int j = i+1; j < idx.size(); ++j) {
            if (removed.find(j) != removed.end())
                continue;
            const pair<int, int>& pj = tt[idx[j]];
            if (pj.first >= pi.second)
                break;
            first_intersection = true;
            for (int k = j+1; k < idx.size(); ++k) {
                if (removed.find(k) != removed.end())
                    continue;
                const pair<int, int>& pk = tt[idx[k]];
                if (pk.first >= pj.second)
                    break;
                second_intersection = true;
                break;
            }
            break;
        }
        if (first_intersection and not second_intersection)
            removed.insert(i);
    }

    //end = clock();
    //cout << "remove intersecting -> " << (end - start)/(double)CLOCKS_PER_SEC << " sec.\n";
    //start = end;

    vector< vector<int> > conflicts;
    for (int i = 0; i < idx.size(); ++i) {
        if (removed.find(i) != removed.end())
            continue;
        bool already_done = false;
        for (const auto& c : conflicts) {
            for (const auto& e : c) {
                if (i == e) {
                    already_done = true;
                    break;
                }
            }
            if (already_done)
                break;
        }
        if (already_done)
            continue;
        const pair<int, int>& pi = tt[idx[i]];
        vector< int > curr_conflict;
        for (int j = i+1; j < idx.size(); ++j) {
            if (removed.find(j) != removed.end())
                continue;
            const pair<int, int>& pj = tt[idx[j]];
            if (pj.first >= pi.second)
                break;
            curr_conflict.push_back(j);
        }
        if (not curr_conflict.empty()) {
            curr_conflict.push_back(i);
            conflicts.push_back(curr_conflict);
        }
    }

    //end = clock();
    //cout << "find conflicts -> " << (end - start)/(double)CLOCKS_PER_SEC << " sec.\n";
    //start = end;

    int n_wic = 0, n_res = 0; // number of workshops in conflicts and resolved
    vector<int> curr_node;
    for (const auto& c : conflicts) {
        vector<int> wic(c.size()); // workshops in conflict
        n_wic += wic.size();
        for (int i = 0; i < c.size(); ++i)
            wic[i] = idx[c[i]];
        n_res += NodeExpand(curr_node, wic, ptr);
    }

    //end = clock();
    //cout << "remove conflicts -> " << (end - start)/(double)CLOCKS_PER_SEC << " sec.\n";

    return ptr->n - removed.size() - n_wic + n_res;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
