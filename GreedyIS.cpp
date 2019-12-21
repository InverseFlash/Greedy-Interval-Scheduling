/*
Description
    A greedy interval scheduling example of hotel bookings.
    Input
        A file with the following lines.  Note: columns between Line 1 and 2 are pairs of (start time, end time).
        Line 1: # of rooms
        Line 2: Start time of booking
        Line 3: End time of booking
    
*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// helper method to sort int pairs
bool sorter(const pair<int, int> &one, const pair<int, int> &two){
    return one.second < two.second;
}

int main(int argc, char* argv[]){
    ifstream fileIn(argv[1]);
    ofstream fileOut;
    fileOut.open("booking confirmations.txt");
    int numRooms;
    vector<pair<int, int>> roomTimes;
    string line1, line2, line3;

    getline(fileIn, line1); // read 3 lines in of the bookings.txt file
    getline(fileIn, line2);
    getline(fileIn, line3); 
    istringstream read1(line1), read2(line2), read3(line3);
    read1 >> numRooms; //store number of rooms

    //input booking times into vector via pairs
    int num2, num3;
    while (read2 >> num2){
        read3 >> num3;
        roomTimes.push_back(make_pair(num2, num3));
    }

    //sort vector by end times
    sort(roomTimes.begin(), roomTimes.end(), sorter);
    
    //Greedy Algorithm
    int end;
    int room = 1;
    vector<int> take; //to track room bookings that have been taken
    while (room <= numRooms && roomTimes.size() != 0){
        fileOut << "Room " << room << " ";
        end = roomTimes[0].second;
        take.push_back(0);
        fileOut << "(" << roomTimes[0].first << ", " << roomTimes[0].second << ") ";
        if (roomTimes.size() > 1){
            for (int i = 1; i < roomTimes.size(); i++){
                if(roomTimes[i].first >= end){
                    end = roomTimes[i].second;
                    take.push_back(i);
                    fileOut << "(" << roomTimes[i].first << ", " << roomTimes[i].second << ") ";
                }
            }
        }
        //remove tracked room bookings from original vector for next loop
        for(int i = take.size() - 1; i >= 0; i--){
            roomTimes.erase(roomTimes.begin() + take[i]);
        }
        fileOut << endl;
        take.clear(); //clear take vector for next loop
        room++;
    }

    //print remaining booking times not assigned to a room
    if (!roomTimes.empty()){
        for (int i = 0; i < roomTimes.size(); i++){
            fileOut << "(" << roomTimes[i].first << ", " << roomTimes[i].second << ") ";
        }
    }
}