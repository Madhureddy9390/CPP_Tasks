#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;
struct Control {
    int id;
    string type;
    string state;
};
string copyed_vector(const vector<Control>& s) {
    vector<Control> s1;
    copy(s.begin(), s.end(), back_inserter(s1));
    string result;
    cout << "Backup of the control list" << endl;
    for (const auto& d : s1) {
        result += to_string(d.id) + " " + d.type + " " + d.state + "\n";
    }
    return result;
}
void print_controls(const vector<Control>& s, const string& message) {
    cout << "**************************************" << endl;
    cout << message << endl;
    for (const auto& d : s) {
        cout << d.id << " " << d.type << " " << d.state << endl;
    }
}
void fill_disabled(vector<Control>& s) {
    for (auto& d : s) {
        d.state = "disabled";
    }
    print_controls(s, "After setting all states to disabled:");
}
void generate_random_states(vector<Control>& s) {
    vector<string> states = {"visible", "invisible", "disabled"};
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<> dist(0, 2);
    // for (auto& d : s) {
    //     d.state = states[dist(gen)];
    // }
    srand(time(0));
    for (auto& d : s) {
        int random_index = rand() % 3;  // Generate a random index (0, 1, or 2)
        d.state = states[random_index];
    }
    print_controls(s, "After generating random states:");
}
void transform_state(vector<Control>& s) {
    transform(s.begin(), s.end(), s.begin(), [](Control d) {
        if (d.type == "slider") {
            d.state = "invisible";
        }
        return d; 
    });
    print_controls(s, "After changing the state of all sliders to invisible:");
}
void remove_if_invisible(vector<Control>& s) {
    s.erase(remove_if(s.begin(), s.end(), [](const Control& d) {
        return d.state == "invisible";
    }), s.end());
    print_controls(s, "After filtering out invisible controls:");
}
void reverse_order(vector<Control>& s) {
    reverse(s.begin(), s.end());
    print_controls(s, "After reversing the control order:");
}
void partition_visible(vector<Control>& s) {
    partition(s.begin(), s.end(), [](const Control& a) {
        return a.state == "visible";
    });
    print_controls(s, "After grouping visible controls together:");
}
int main() {
    vector<Control> s = {
        {1, "button", "disable"},
        {2, "button", "visible"},
        {3, "slider", "disable"},
        {4, "button", "invisible"},
        {5, "slider", "disable"},
        {6, "button", "disable"},
        {7, "slider", "invisible"},
        {8, "button", "visible"},
        {9, "slider", "visible"},
        {10, "button", "disable"}
    };
    cout << copyed_vector(s);
    fill_disabled(s);
    generate_random_states(s);
    transform_state(s);
    remove_if_invisible(s);
    reverse_order(s);
    partition_visible(s);
    return 0;
}
