# COP3530 - Project 2 

## Project Overview 

This project implements Breadth-First Search (BFS) and Dijkstra's Algorithm to find routes between two addresses using OpenStreetMap road data. The program builds a graph from the provided CSV files, compares both algorithms, and exports the resulting route to a CSV file for visualization.

## Requirements

* C++17 compatible compiler (g++)
* MSYS2 UCRT64 (or another environment with g++)
* Visual Studio Code (recommended)

## Project Structure

```text
project_2b/
├── data/
│   ├── road_addresses.csv
│   ├── road_edges.csv
│   ├── road_nodes.csv
│   └── algorithm_results.csv
├── src/
│   └── main.cpp
└── README.md
```
## How to Compile
In the project directory. 

```bash
cd src
g++ main.cpp -o ../project.exe
```


##  How to Run
While inside the `src` directory, run:

```bash
../project.exe
```

The program will prompt for:

Starting Home/Business Number
Starting Street Name
Starting City
Destination Home/Business Number
Destination Street Name
Destination City

## Program Output

The program will:

- Build the road graph
- Find the starting and destination nodes
- Execute BFS
- Execute Dijkstra's Algorithm
- Display:
    - Path
    - Runtime
    - Total distance
- Export the route to: data/algorithm_results.csv


## Visualization

To visualize the routes, the exported CSV can be imported into **uMap**, an open-source web mapping application built on OpenStreetMap. uMap is used only for displaying the generated route data; all graph construction, pathfinding algorithms, and CSV generation are implemented in this project. The exported algorithm_results.csv was imported into uMap to demonstrate the BFS and Dijkstra routes during the project presentation

### Issues:

The program reports an error if:

- The starting address cannot be found.
- The destination address cannot be found.
- A path does not exist between the selected locations.

## Authors
* Kenneth Griffin
* Mariana Velasco

## References

- **uMap:** https://umap.openstreetmap.fr/
- **OpenStreetMap:** https://www.openstreetmap.org/
