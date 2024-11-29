#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;
class MenuItem {
public:
    string name;
    vector<MenuItem> submenus;
    MenuItem(const string& name) : name(name) {}
    void addSubmenu(const MenuItem& submenu) {
        submenus.push_back(submenu);
    }
    void display(int level = 0) const {
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << name << endl;
        for (const auto& submenu : submenus) {
            submenu.display(level + 1);
        }
    }
    void displayMenuOptions(int level = 0) const {
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << name << endl;
        int i = 1;
        for (const auto& submenu : submenus) {
            cout << "  " << i++ << ". " << submenu.name << endl;
        }
    }
    MenuItem* getSubmenu(int choice) {
        if (choice >= 1 && choice <= submenus.size()) {
            return &submenus[choice - 1];
        }
        return nullptr;
    }
};
int main() {
    MenuItem mainMenu("Main Menu");
    MenuItem settingsMenu("Settings");
    MenuItem displaySettingsMenu("Display Settings");
    MenuItem audioSettingsMenu("Audio Settings");
    settingsMenu.addSubmenu(displaySettingsMenu);
    settingsMenu.addSubmenu(audioSettingsMenu);
    MenuItem mediaMenu("Media");
    MenuItem radioMenu("Radio");
    MenuItem bluetoothAudioMenu("Bluetooth Audio");
    mediaMenu.addSubmenu(radioMenu);
    mediaMenu.addSubmenu(bluetoothAudioMenu);
    mainMenu.addSubmenu(settingsMenu);
    mainMenu.addSubmenu(mediaMenu);
    MenuItem* currentMenu = &mainMenu;
    MenuItem* prevMenu = nullptr;
    int choice;
    bool running = true;
    while (running) {
        currentMenu->displayMenuOptions();
        cout << "Enter a choice (1-" << currentMenu->submenus.size() << " to go down, 0 to go back, -1 to exit): ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (choice == -1) {
            running = false;  // Exit the program
        }
        else if (choice == 0) {
            if (prevMenu != nullptr) {
                currentMenu = prevMenu;
                prevMenu = nullptr;
            }
            else {
                cout << "You are already at the main menu.\n";
            }
        }
        else {
            MenuItem* submenu = currentMenu->getSubmenu(choice);
            if (submenu != nullptr) {
                prevMenu = currentMenu;
                currentMenu = submenu;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    return 0;
}
