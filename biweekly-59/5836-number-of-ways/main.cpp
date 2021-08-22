#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <queue>
/**
 * url:
 * problem:
 */
 /**
  * function Dijkstra(Graph, source):
  *     dist[source] ← 0                           // Initialization
  *
  *     create vertex priority queue Q
  *
  *     for each vertex v in Graph:
  *         if v ≠ source
  *             dist[v] ← INFINITY                 // Unknown distance from source to v
  *             prev[v] ← UNDEFINED                // Predecessor of v
  *
  *         Q.add_with_priority(v, dist[v])
  *
  *
  *     while Q is not empty:                      // The main loop
  *         u ← Q.extract_min()                    // Remove and return best vertex
  *         for each neighbor v of u:              // only v that are still in Q
  *             alt ← dist[u] + length(u, v)
  *             if alt < dist[v]
  *                 dist[v] ← alt
  *                 prev[v] ← u
  *                 Q.decrease_priority(v, alt)
  *
  *     return dist, prev
  */
// class Solution {
// public:
//     int countPaths(int n, vector<vector<int>>& roads) {
//         int mod = 1e9+7;
//         vector<vector<pair<int, int>>> graph(n);
//         for(auto &road: roads) {
//             graph[road[0]].push_back({road[1], road[2]});
//             graph[road[1]].push_back({road[0], road[2]});
//         }
//
//         vector<long long> distance(n, LONG_MAX);
//         vector<int> path(n, 0);
//
//         priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
//         pq.push({0, 0});
//         distance[0] = 0;
//         path[0] = 1;
//
//         while(!pq.empty()) {
//             pair<long long, int> t = pq.top();
//             pq.pop();
//
//             for(auto &nbr: graph[t.second]) {
//                 long long vert = nbr.first;
//                 long long edge = nbr.second;
//
//                 if(distance[vert] > distance[t.second] + edge) {
//                     distance[vert] = distance[t.second] + edge;
//                     pq.push({distance[vert], vert});
//                     path[vert] = path[t.second] %mod;
//                 }
//                 else if(distance[vert] == t.first + edge) {
//                     path[vert] += path[t.second];
//                     path[vert] %= mod;
//                 }
//             }
//         }
//
//         return path[n-1];
//     }
// };
class Solution
{
public:
    int countPaths(int n, std::vector<std::vector<int>>& roads)
    {
        std::priority_queue<int, std::greater<>>
        for ()
    }
};
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace