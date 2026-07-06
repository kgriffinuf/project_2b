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
    // initialize destination address as UF computer science building
    std::string dest_home_num = "432";
    std::string dest_street_name = "Newell Drive";
    std::string dest_city = "Gainesville";


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

    // future functions
    // search in node_addresses vector, match address to nearest_to_node or nearest_from_node

    // road_edges vector
    // from_node = start_node
    // algorithms to use to_node to solve paths.
    // need to sum length_m as the path is solved


    return 0;

}



