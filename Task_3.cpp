#include <iostream>
#include <queue>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
class Event {
public:
    string eventType;
    float x;
    float y;
    float xEnd; // End coordinates for Swipe
    float yEnd;
    long timestamp;
    Event(string eventType, float x, float y, long timestamp, float xEnd = 0, float yEnd = 0){
    this->eventType=eventType;
    this->x=x;
    this->y=y;
    this->xEnd=xEnd;
    this->yEnd=yEnd;
    this->timestamp=timestamp;
}
    void display() {
        cout << "Event Type: " << eventType << endl;
        cout << "Coordinates: (" << x << ", " << y << ")" << endl;
        if (eventType == "Swipe") {
            cout << "End Coordinates: (" << xEnd << ", " << yEnd << ")" << endl;
        }
        cout << "Timestamp: " << timestamp << endl;
    }
    void process()  {
        if (eventType == "Tap") {
            cout << "Tapped at position: (" << x << ", " << y << ")" << endl;
        } else if (eventType == "Swipe") {
            string direction = getSwipeDirection();
            cout << "Swipe detected in direction: " << direction << endl;
        }
    }
    private:
    string getSwipeDirection()  {
        float dx = xEnd - x;
        float dy = yEnd - y;
        if (abs(dx) > abs(dy)) {
            return dx > 0 ? "Right" : "Left";
        } else {
            return dy > 0 ? "Up" : "Down";
        }
    }
};
int main() {
    queue<shared_ptr<Event>> eventQueue;
    // Simulate event generation
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 7; ++i) {
        int eventType = rand() % 2; // 0 for Tap, 1 for Swipe
        float x = rand() % 100;
        float y = rand() % 100;
        long timestamp = rand() % 100000 + 1000000;

        if (eventType == 0) { // Tap
            eventQueue.emplace(make_shared<Event>("Tap", x, y, timestamp));
        } else { // Swipe
            float xEnd = rand() % 100;
            float yEnd = rand() % 100;
            eventQueue.emplace(make_shared<Event>("Swipe", x, y, timestamp, xEnd, yEnd));
        }
    }
    // Process the events
    while (!eventQueue.empty()) {
        auto currentEvent = eventQueue.front();
        currentEvent->display();
        currentEvent->process();
        cout << "---------------------------------" << endl;
        eventQueue.pop();
    }
    return 0;
}
