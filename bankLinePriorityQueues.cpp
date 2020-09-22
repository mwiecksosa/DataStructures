/**
 * @file proj4.cc
 * \mainpage
 *
 * CISC 2200, Data Structures<br>
 * Project 4: The Banking Simulation<p>
 *
 * Brief discussion
 *
 * @author Michael Wieck-Sosa
 * @date April 12, 2019
 *
 */

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

struct Event {
        string type;
        unsigned int time;
        unsigned int length;

        bool operator < (const Event& rhs) const {
                return this->time < rhs.time;
        }
};

struct EventList {
public:
        priority_queue<Event> eventListPriorityQueue;
        queue<Event> eventListQueue;
        void fill(istream& is);
        void simulate();
};


int main(int argc, char** argv)
{
        EventList eventList;

        // command-line parameter munging
        // also fills the event list with the input data
        char* progname = argv[0];
        switch (argc) {
        case 1:
                eventList.fill(cin);
                break;
        case 2: {
                ifstream ifs(argv[1]);
                if (!ifs) {
                        cerr << progname << ": couldn't open " << argv[1] << endl;
                        return 1;
                }
                eventList.fill(ifs);
                break;
        }
        default:
                cerr << "Usage: " << progname << " [datafile]\n";
                return 2;
        }

        eventList.simulate();
}




void EventList::fill(istream& is){
        unsigned int data_time; //arrival time from datafile
        unsigned int data_length; //length from datafile
        unsigned int prevTime = 0;
        unsigned int currTime = 0;
        unsigned int currLength = 0;
        unsigned int earliestDepartTime;
        unsigned int latestDepartTime;
        int customerNum = 1;
        Event firstToDepart;
        Event nextArrival;
        Event nextDepart;
        Event backOfQueue;
        queue<Event> departQueue;

        while (is >> data_time >> data_length) {
                currTime = data_time;
                currLength = data_length;

                if (currTime < prevTime) {
                        cerr << "customer #" << customerNum << " out of order (time = "
                                << data_time << ", previous time = " << prevTime << ")" << endl;
                        exit(EXIT_FAILURE);
                }

                if (!departQueue.empty()) {
                        firstToDepart = departQueue.front();
                        earliestDepartTime = firstToDepart.time;
                        while(earliestDepartTime < currTime && !departQueue.empty()) {
                                this->eventListQueue.emplace(firstToDepart);
                                departQueue.pop(); //remove front
                                firstToDepart = departQueue.front();
                                earliestDepartTime = firstToDepart.time;
                        }

                        backOfQueue = departQueue.back();
                        latestDepartTime = backOfQueue.time;

                        if(!departQueue.empty())
                                nextDepart.time = latestDepartTime + currLength;
                        else
                                nextDepart.time = currTime + currLength;

                        nextDepart.length = 0;
                        nextDepart.type = "departure";
                        departQueue.emplace(nextDepart);
                }
                else { //base case, queue empty
                        nextDepart.time = currTime + currLength;
                        nextDepart.length = 0;
                        nextDepart.type = "departure";
                        departQueue.emplace(nextDepart);
                }

                nextArrival.time = currTime;
                nextArrival.length = currLength;
                nextArrival.type = "arrival";
                this->eventListQueue.emplace(nextArrival);

                prevTime = nextArrival.time;
                customerNum++;
        }
        while (!departQueue.empty()) {
                firstToDepart = departQueue.front();
                earliestDepartTime = firstToDepart.time;
                this->eventListQueue.emplace(firstToDepart);
                departQueue.pop();
        }

}

void EventList::simulate(){
        //initialize all variables

        //sums
        unsigned int arrivalTimeSum = 0; //total arrival time sum
        unsigned int departTimeSum = 0; //total departure time sum
        unsigned int processTimeSum = 0; //total process time sum
        unsigned int eventCount = 0; //number of people processed
        unsigned int numerator;

        float avgWaitingTime; //(departTimeSum - processTimeSum - arrivalTimeSum) / eventCount

        //queue of customers
        queue<Event> bankQueue;

        Event newEvent;

        while (!this->eventListQueue.empty()) {
                newEvent = this->eventListQueue.front();

                if (newEvent.type == "arrival") {
                        std::cout << "Processing an arrival event at time:\t" << newEvent.time << endl;
                        eventCount++;
                        arrivalTimeSum += newEvent.time;
                        processTimeSum += newEvent.length;

                }
                else {
                        std::cout << "Processing an departure event at time: \t" << newEvent.time << endl;
                        departTimeSum += newEvent.time;
                }

                this->eventListQueue.pop();
        }


        avgWaitingTime = (static_cast<float>(departTimeSum) - static_cast<float>(processTimeSum) - static_cast<float>(arrivalTimeSum)) / static_cast<float>(eventCount);

        std::cout << "Final statistics:" << endl;
        std::cout << "  Total number of people processed:\t" << eventCount << endl;
        std::cout << "  Average amount of time spent waiting: " << avgWaitingTime << endl;
}

