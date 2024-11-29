#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Control {
    int id;
    string type;
    string state;
};
void print_controls(const vector<Control>& controls) {
    for (const auto& d : controls) {
        cout << d.id << " " << d.type << " " << d.state << endl;
    }
}
void sort_controls_by_id(vector<Control>& controls) {
    stable_sort(controls.begin(), controls.end(), [](Control s1, Control s2) {
        return s1.id < s2.id;  // Sort only by id
    });
}
void search_using_lower_bound(const vector<int>& ids) {
    int option;
    cout << "Enter which ID you want to find using lower_bound: ";
    cin >> option;
    auto m = lower_bound(ids.begin(), ids.end(), option);
    if (m != ids.end() && *m == option) {
        cout << "Element found with ID " << option << " using lower_bound." << endl;
    } else {
        cout << "Element not found with ID " << option << " using lower_bound." << endl;
    }
}
void search_using_upper_bound(const vector<int>& ids) {
    int option1;
    cout << "Enter which ID you want to find using upper_bound: ";
    cin >> option1;
    auto m1 = upper_bound(ids.begin(), ids.end(), option1);
    if (m1 != ids.end() && *m1 == option1) {
        cout << "Element found with ID " << option1 << " using upper_bound." << endl;
    } else {
        cout << "Element not found with ID " << option1 << " using upper_bound." << endl;
    }
}
void merge_controls(const vector<Control>& s, const vector<Control>& s1) {
    vector<Control> s2(s.size() + s1.size());
    merge(s.begin(), s.end(), s1.begin(), s1.end(), s2.begin(), [](Control s, Control s1) {
        return s.id < s1.id;  // Compare only by id
    });
    cout << "Merged elements by ID:" << endl;
    print_controls(s2);
}
void union_controls(const vector<Control>& s, const vector<Control>& s1) {
    vector<Control> s3;
    set_union(s.begin(), s.end(), s1.begin(), s1.end(), back_inserter(s3), [](Control s, Control s1) {
        return s.id < s1.id;  // Compare only by id
    });
    cout << "Union elements of set s and set s1:" << endl;
    print_controls(s3);
}
void intersection_controls(const vector<Control>& s, const vector<Control>& s1) {
    vector<Control> s5;
    set_intersection(s.begin(), s.end(), s1.begin(), s1.end(), back_inserter(s5), [](Control s, Control s1) {
        return s.id == s1.id;  // Compare only by id
    });
    cout << "Intersection elements of set s and set s1 by id:" << endl;
    print_controls(s5);
}
int main() {
    vector<Control> s;
    s.push_back({5, "button", "disable"});
    s.push_back({3, "button", "visible"});
    s.push_back({1, "slider", "disable"});
    s.push_back({4, "button", "invisiable"});
    s.push_back({5, "slider", "disable"});
    s.push_back({9, "button", "disable"});
    s.push_back({4, "slider", "invisiable"});
    s.push_back({8, "button", "visible"});
    s.push_back({7, "slider", "visible"});
    s.push_back({1, "button", "disable"});
    sort_controls_by_id(s);
    cout << "Sorted elements by ID:" << endl;
    print_controls(s);
    vector<int> s4;
    for (auto& s2 : s) {
        s4.push_back(s2.id);
    }
    search_using_lower_bound(s4);
    search_using_upper_bound(s4);
    vector<Control> s1;
    s1.push_back({3, "slider", "invisiable"});
    s1.push_back({5, "button", "visible"});
    s1.push_back({7, "slider", "visible"});
    s1.push_back({9, "button", "disable"});
    merge_controls(s, s1);
    union_controls(s, s1);
    intersection_controls(s, s1);
    return 0;
}
