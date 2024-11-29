#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Control {
    int id;
    string type;
    string state;
};
void print_controls(vector<Control> s) {
    cout << "Iterating through elements in vector by using for_each method" << endl;
    for_each(s.begin(), s.end(), [](Control a) {
        cout << a.id << " " << a.type << " " << a.state << endl;
    });
}
void find_control_by_id(vector<Control> s, int id) {
    vector<int> k1;
    for(auto s1:s){
        k1.push_back(s1.id);
    }
    auto it2=find(k1.begin(),k1.end(),id);
    for(auto s4:s){
        if(s4.id==*it2){
            cout<<"control with a specific ID."<<*it2<<" "<<s4.type<<endl;
        }
    }
}
void find_first_invisible_control(vector<Control> s) {
    auto it = find_if(s.begin(), s.end(), [](Control a) { return a.state == "invisiable"; });
    if (it != s.end()) {
        cout << "First invisible control is " << it->type << endl;
    } else {
        cout << "No invisible controls found" << endl;
    }
}
void find_consecutive_controls_with_same_state(vector<Control> s) {
    auto it = adjacent_find(s.begin(), s.end(), [](Control a, Control b) { return a.state == b.state; });
    if (it != s.end()) {
        cout << "Found consecutive controls with the same state at id " << it->id << " and " << (it + 1)->id << endl;
    } else {
        cout << "Not found consecutive controls with the same state." << endl;
    }
}
int count_state(vector<Control> s, string state) {
    vector<string> k;
    for (const auto& s1 : s) {
        k.push_back(s1.state);
    }
    return count(k.begin(), k.end(), state);
}
int count_disabled_sliders(vector<Control> s) {
    return count_if(s.begin(), s.end(), [](Control a) { return a.type == "slider" && a.state == "disable"; });
}
void check_subranges_equal(vector<Control> s) {
    bool flag = equal(s.begin(), s.begin() + 3, s.begin() + 7, [](Control a, Control b) {
        return a.state == b.state && a.type == b.type;
    });
    if (flag) {
        cout << "Both subranges are equal" << endl;
    } else {
        cout << "Both subranges are not equal" << endl;
    }
}
int main() {
    vector<Control> s;
    s.push_back({1, "button", "disable"});
    s.push_back({2, "button", "visible"});
    s.push_back({3, "slider", "disable"});
    s.push_back({4, "button", "invisiable"});
    s.push_back({5, "slider", "disable"});
    s.push_back({6, "button", "disable"});
    s.push_back({7, "slider", "invisiable"});
    s.push_back({8, "button", "visible"});
    s.push_back({9, "slider", "visible"});
    s.push_back({10, "button", "disable"});
    print_controls(s);
    find_control_by_id(s, 6);
    find_first_invisible_control(s);
    find_consecutive_controls_with_same_state(s);
    int visible_count = count_state(s, "visible");
    cout << "Number of visible states: " << visible_count << endl;
    int disabled_slider_count = count_disabled_sliders(s);
    cout << "Number of sliders that are disabled: " << disabled_slider_count << endl;
    check_subranges_equal(s);
    return 0;
}
