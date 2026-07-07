// Project 2 - COP3530
// Mariana Velasco and Kenneth Griffin
// main.cpp
// UF Additional provided resources, regex code reference, and the other UF materials provided for the project
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>




int main() {

    // create vectors to hold data in csv files
    std::vector<std::vector<std::string>> node_addresses;
    // read node_addresses.csv
    // open csv file
    std::ifstream file("../data/road_addresses.csv");
    // check if file opened
    if (!file.is_open()) {
        std::cout << "Error while opening road_addresses.csv!" << std::endl;
        return 1;
    }
    // read each line of csv
    std::string line;
    // flag to skip first line of csv
    bool first_line = true;

    // read in each line
    while (std::getline(file, line)) {
        // skip header line
        if (first_line) {
            // set it to false so other lines are not skipped
            first_line = false;
            continue;
        }
        // read in the line
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> row;
        // check if data is in quotes
        bool quotes_check = false;
        // must check if quotes exist
        for (char c : line) {
            if (c == '"') {
                quotes_check = !quotes_check;
            } else if (c == ',' && !quotes_check) {
                // if comma and not quotes_check
                row.push_back(value);
                value.clear();
            } else {
                value += c;
            }
        }
        // push last value
        row.push_back(value);
        // store data in vector
        node_addresses.push_back(row);
        // output for troubleshoot reading in csv
        // for (const auto& val : row) {
        //     std::cout << val << std::endl;
        // }
    }
    // close file
    file.close();

    // read node_edges.csv
    // vector for data
    std::vector<std::vector<std::string>> road_edges;
    // open csv file
    std::ifstream edges_file("../data/road_edges.csv");
    // check if file opened
    if (!edges_file.is_open()) {
        std::cout << "Error while opening road_edges.csv!" << std::endl;
        return 1;
    }

    // flag to skip first line of csv
    first_line = true;

    // read in each line
    while (std::getline(edges_file, line)) {
        // skip header line
        if (first_line) {
            // set it to false so other lines are not skipped
            first_line = false;
            continue;
        }

        // read in the line
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> row;

        // each value delimited by commas in csv
        while (std::getline(ss, value, ',')) {
            // push each value to the vector
            row.push_back(value);
        }
        // store data in vector
        road_edges.push_back(row);

        // output for troubleshoot reading in csv
        // for (const auto& val : row) {
        //     std::cout << val << std::endl;
        // }
    }
    // close edges file
    edges_file.close();


    // initialize starting address as UF football stadium
    std::string start_home_num = "157";
    std::string start_street_name = "Gale Lemerand Drive";
    std::string start_city = "Gainesville";
    std::string start_node = "84836664";
    bool start_node_found = false;

    // initialize destination address as Gainesville Hyatt
    std::string dest_home_num = "212";
    std::string dest_street_name = "Southeast 1st Street";
    std::string dest_city = "Gainesville";
    std::string end_node = "84898697";
    bool end_node_found = false;


    // USER INPUT
    // input starting home number, street name, and city
    std::cout << "Enter Starting Home/Business Number: " << std::endl;
    std::getline(std::cin, start_home_num);
    std::cout << "Enter Starting Street Name: " << std::endl;
    std::getline(std::cin, start_street_name);
    std::cout << "Enter Starting City: " << std::endl;
    std::getline(std::cin, start_city);
    // input destination city
    std::cout << "Enter Destination Home/Business Number: " << std::endl;
    std::getline(std::cin, dest_home_num);
    std::cout << "Enter Destination Street Name: " << std::endl;
    std::getline(std::cin, dest_street_name);
    std::cout << "Enter Destination City: " << std::endl;
    std::getline(std::cin, dest_city);

    // FIND start_node
    // index 4 housenum, index 5 street, index 7 city
    // match address to index 14 nearest_to_node or index 13 nearest_from_node
    for (const auto& row : node_addresses) {
        if (row[4] == start_home_num && row[5] == start_street_name && row[7] == start_city) {
            // set start_node to nearest_to_node in index 14, nearest_from_node index 13
            start_node = row[14];
            // exit loop since found, set start_found flag to true
            std::cout << "Starting Node: " << start_node << std::endl;
            start_node_found = true;
            break;
        }
    }
    if (!start_node_found) {
        std::cout << "Error finding starting address node!" << std::endl;
    }

    // FIND end_node
    // index 4 housenum, index 5 street, index 7 city
    // match address to index 14 nearest_to_node or index 13 nearest_from_node
    for (const auto& row : node_addresses) {
        if (row[4] == dest_home_num && row[5] == dest_street_name && row[7] == dest_city) {
            // set start_node to nearest_to_node in index 14, nearest_from_node index 13
            end_node = row[14];
            // exit loop since found, set start_found flag to true
            std::cout << "Ending Node: " << end_node << std::endl;
            end_node_found = true;
            break;
        }
    }
    if (!end_node_found) {
        std::cout << "Error finding ending address node!" << std::endl;
    }

    // build adjacency list using a map<from, vector<pair<to,weight>>> graph; Module 10 UF notes

    // road_edges vector
    // from_node = start_node
    // algorithms to use to_node to solve paths.
    // need to sum length_m as the path is solved


    return 0;

}



