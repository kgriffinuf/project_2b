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
#include <map>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <limits>

std::vector<std::string> bfs(
    const std::map<std::string, std::vector<std::pair<std::string, double>>>& graph,
    const std::string& start_node,
    const std::string& end_node)
{
    std::queue<std::string> bfs_queue;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> parent;

    bfs_queue.push(start_node);
    visited.insert(start_node);
    parent[start_node] = "";

    while (!bfs_queue.empty()) {
        const std::string current = bfs_queue.front();
        bfs_queue.pop();

        if (current == end_node) {
            std::vector<std::string> path;
            for (std::string node = end_node; !node.empty(); node = parent[node]) {
                path.push_back(node);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        auto it = graph.find(current);
        if (it == graph.end()) {
            continue;
        }

        for (const auto& neighbor_pair : it->second) {
            const std::string& neighbor = neighbor_pair.first;
            if (visited.insert(neighbor).second) {
                parent[neighbor] = current;
                bfs_queue.push(neighbor);
            }
        }
    }

    return {};
}
// helper function to find distance of BFS. BFS solves by hop count
double bfs_distance(
    const std::map<std::string, std::vector<std::pair<std::string, double>>>& graph,
    const std::vector<std::string>& path)
{
    // initialize total_distance as zero
    double total_distance = 0.0;
    // loop through the path to sum total_distance
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        // start and dest paths
        const std::string& start = path[i];
        const std::string& dest = path[i+1];
        // iterate through graph from to the end
        auto iter = graph.find(start);
        if (iter == graph.end()) {
            continue;
        }
        // loop through to add total_distance up
        for (const auto& edge : iter->second) {
            // if it's equal to dest then add
            if (edge.first == dest) {
                // increment total_distance
                total_distance += edge.second;
                // exit
                break;
            }
        }
    }
    // return the total_distance calculated
    return total_distance;
}


std::vector<std::string> dijkstra(
    const std::map<std::string, std::vector<std::pair<std::string, double>>>& graph,
    const std::string& start_node,
    const std::string& end_node,
    double& total_cost)
{
    struct PQItem {
        double distance;
        std::string node;
    };

    struct Compare {
        bool operator()(const PQItem& a, const PQItem& b) const {
            return a.distance > b.distance;
        }
    };

    std::priority_queue<PQItem, std::vector<PQItem>, Compare> pq;
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> parent;
    const double INF = std::numeric_limits<double>::infinity();

    dist[start_node] = 0.0;
    parent[start_node] = "";
    pq.push({0.0, start_node});

    while (!pq.empty()) {
        const PQItem current = pq.top();
        pq.pop();

        if (current.distance > dist[current.node]) {
            continue;
        }

        if (current.node == end_node) {
            break;
        }

        auto it = graph.find(current.node);
        if (it == graph.end()) {
            continue;
        }

        for (const auto& neighbor_pair : it->second) {
            const std::string& neighbor = neighbor_pair.first;
            double weight = neighbor_pair.second;
            double new_distance = current.distance + weight;

            if (dist.find(neighbor) == dist.end() || new_distance < dist[neighbor]) {
                dist[neighbor] = new_distance;
                parent[neighbor] = current.node;
                pq.push({new_distance, neighbor});
            }
        }
    }

    if (dist.find(end_node) == dist.end()) {
        total_cost = INF;
        return {};
    }

    total_cost = dist[end_node];
    std::vector<std::string> path;
    for (std::string node = end_node; !node.empty(); node = parent[node]) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

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

    // read road_nodes.csv for lat/long csv export
    // map of the node lat long to export/plot
    std::map<std::string, std::pair<double,double>> node_latlong;
    // open csv file
    std::ifstream road_nodes("../data/road_nodes.csv");
    // check if file opened
    if (!road_nodes.is_open()) {
        std::cout << "Error while opening road_nodes.csv!" << std::endl;
        return 1;
    }

    // flag to skip first line of csv
    first_line = true;

    // read in each line
    while (std::getline(road_nodes, line)) {
        // skip header line
        if (first_line) {
            // set it to false so other lines are not skipped
            first_line = false;
            continue;
        }

        // read in the line
        std::stringstream ss(line);
        // strings for node_id and latitude/longitude
        std::string node_id;
        std::string lat;
        std::string lon;

        // each value delimited by commas in csv
        std::getline(ss, node_id, ',');
        std::getline(ss, lat, ',');
        std::getline(ss, lon, ',');

        // load data into map with key node_id and latitude and longitude
        node_latlong[node_id] = {
            std::stod(lat),
            std::stod(lon)
        };

    }
    // close edges file
    road_nodes.close();

    // build adjacency list using a map<from, vector<pair<to,weight>>> graph
    std::map<std::string, std::vector<std::pair<std::string, double>>> graph;

    for (const auto& row : road_edges) {
        if (row.size() < 3) {
            continue;
        }

        const std::string& from_node = row[0];
        const std::string& to_node = row[1];
        double length_m = std::stod(row[2]);

        graph[from_node].push_back({to_node, length_m});
    }

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
    std::cout << "Enter Starting Home/Business Number: ";
    std::getline(std::cin, start_home_num);
    std::cout << "Enter Starting Street Name: ";
    std::getline(std::cin, start_street_name);
    std::cout << "Enter Starting City: ";
    std::getline(std::cin, start_city);
    // input destination city
    std::cout << "Enter Destination Home/Business Number: ";
    std::getline(std::cin, dest_home_num);
    std::cout << "Enter Destination Street Name: ";
    std::getline(std::cin, dest_street_name);
    std::cout << "Enter Destination City: ";
    std::getline(std::cin, dest_city);

    // FIND start_node
    // index 4 housenum, index 5 street, index 7 city
    // match address to index 14 nearest_to_node or index 13 nearest_from_node
    for (const auto& row : node_addresses) {
        if (row[4] == start_home_num && row[5] == start_street_name && row[7] == start_city) {
            // set start_node to nearest_to_node in index 14, nearest_from_node index 13
            start_node = row[14];
            // exit loop since found, set start_found flag to true
            std::cout << "Starting Location Node Identified: " << start_node << std::endl;
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
            std::cout << "Destination Location Node Identified: " << end_node << std::endl;
            std::cout << std::endl;
            end_node_found = true;
            break;
        }
    }
    if (!end_node_found) {
        std::cout << "Error finding ending address node!" << std::endl;
    }
    // declare paths for BFS and Dijkstra
    std::vector<std::string> path;
    std::vector<std::string> shortest_path;

    // use BFS to find any path from start_node to end_node
    if (start_node_found && end_node_found) {
        // bfs, get clock time begin
        auto bfs_begin = std::chrono::steady_clock::now();
        // call bfs algorithm
        path = bfs(graph, start_node, end_node);
        // bfs, get clock time end
        auto bfs_end = std::chrono::steady_clock::now();
        // calculate runtime from bfs_end - bfs_begin
        double bfs_time_ms = std::chrono::duration<double, std::milli>(bfs_end - bfs_begin).count();
        if (!path.empty()) {
            // calculate BFS distance in meters
            double bfs_distance_m = bfs_distance(graph, path);
            // output path that BFS solved
            std::cout << "BFS shortest path from " << start_node << " to " << end_node
                      << " found with " << path.size() << " nodes.\n";
            // print time taken to solve
            std::cout << "BFS algorithm solve time: " << bfs_time_ms << " ms" << std::endl;
            std::cout << "BFS path total distance: "
                      << bfs_distance_m << " meters" << std::endl;
            std::cout << "BFS path nodes: ";
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i];
                if (i + 1 < path.size()) {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
        } else {
            std::cout << "No BFS path was found from " << start_node
                      << " to " << end_node << "." << std::endl;
        }
        // break text between algorithm output
        std::cout << std::endl;
        double shortest_distance = 0.0;
        // dijkstra, get clock time begin
        auto dijkstra_begin = std::chrono::steady_clock::now();
        // call the dijkstra algorithm
        shortest_path =
            dijkstra(graph, start_node, end_node, shortest_distance);
        // dijkstra, get clock time end
        auto dijkstra_end = std::chrono::steady_clock::now();
        // calculate runtime from dijkstra_end - dijkstra_begin
        double dijkstra_time_ms = std::chrono::duration<double, std::milli>(dijkstra_end - dijkstra_begin).count();
        if (!shortest_path.empty()) {
            std::cout << "Dijkstra shortest path from " << start_node
                      << " to " << end_node << " found with "
                      << shortest_path.size() << " nodes." << std::endl;
            // print time taken to solve
            std::cout << "Dijkstra algorithm solve time: " << dijkstra_time_ms << " ms" << std::endl;
            std::cout << "Dijkstra path total distance: "
                      << shortest_distance << " meters" << std::endl;
            std::cout << "Dijkstra path nodes: ";
            for (size_t i = 0; i < shortest_path.size(); ++i) {
                std::cout << shortest_path[i];
                if (i + 1 < shortest_path.size()) {
                    std::cout << " -> ";
                }
            }

            std::cout << std::endl;
        } else {
            std::cout << "No Dijkstra path was found from "
                      << start_node << " to " << end_node << "." << std::endl;
        }

        // export data to csv
        std::ofstream out_file("../data/algorithm_results.csv");
        // check if file open
        if (!out_file.is_open()) {
            std::cout << "Error opening algorithm_results.csv file to export!" << std::endl;
        } else {
            out_file << "algorithm,lat,lon\n";

            // loop through BFS nodes
            for (const std::string& node_id : path) {
                // iterate through to find lat long of node_id
                auto iter = node_latlong.find(node_id);
                // if iterate not at end of map
                if (iter != node_latlong.end()) {
                    out_file << "BFS," << iter->second.first << "," << iter->second.second << "\n";
                }
            }

            // loop through Dijkstra nodes
            for (const std::string& node_id : shortest_path) {
                // iterate through to find lat long of node_id
                auto iter = node_latlong.find(node_id);
                // if iterate not at end of map
                if (iter != node_latlong.end()) {
                    out_file << "Dijkstra," << iter->second.first << "," << iter->second.second << "\n";
                }
            }
            // close the export file
            out_file.close();
            std::cout << "Algorithm Results Exported to /data/algorithm_results.csv" << std::endl;
        }
    } else {
        std::cout << "Skipping BFS and Dijkstra because the start or destination nodes could not be found." << std::endl;
    }

    return 0;
}