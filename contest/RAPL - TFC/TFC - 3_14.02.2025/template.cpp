#include <bits/stdc++.h>
using namespace std;

// Graph Representation
const int MAXN = 1e5 + 5; // Adjust the size as needed
vector<int> adj[MAXN];    // Adjacency list for unweighted graph
vector<pair<int, int>> adjWeighted[MAXN]; // Adjacency list for weighted graph

// Depth-First Search (DFS)
void dfs(int node, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, visited);
        }
    }
}

// Breadth-First Search (BFS)
void bfs(int start, int n) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Dijkstra's Algorithm (Single Source Shortest Path - Non-negative weights)
void dijkstra(int start, int n) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int node = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[node]) continue;

        for (auto& edge : adjWeighted[node]) {
            int neighbor = edge.first;
            int weight = edge.second;
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }
}

// Bellman-Ford Algorithm (Single Source Shortest Path - Negative weights allowed)
void bellmanFord(int start, int n) {
    vector<int> dist(n + 1, INT_MAX);
    dist[start] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (int u = 1; u <= n; u++) {
            for (auto& edge : adjWeighted[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 1; u <= n; u++) {
        for (auto& edge : adjWeighted[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative weight cycle\n";
                return;
            }
        }
    }
}

// Floyd-Warshall Algorithm (All Pairs Shortest Path)
void floydWarshall(int n) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    // Initialize distances with direct edges
    for (int u = 1; u <= n; u++) {
        for (auto& edge : adjWeighted[u]) {
            int v = edge.first;
            int weight = edge.second;
            dist[u][v] = min(dist[u][v], weight);
        }
    }

    // Relax all edges
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

// Kruskal's Algorithm (Minimum Spanning Tree)
struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<Edge> edges;
vector<int> parent, rank;

void makeSet(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findSet(int v) {
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v]);
}

void unionSets(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
    }
}

int kruskal(int n) {
    makeSet(n);
    sort(edges.begin(), edges.end());
    int cost = 0;
    for (Edge e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            cost += e.weight;
            unionSets(e.u, e.v);
        }
    }
    return cost;
}

// Topological Sort (DFS-based)
vector<int> topologicalOrder;
void topologicalSort(int node, vector<bool>& visited, vector<int>& order) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            topologicalSort(neighbor, visited, order);
        }
    }
    order.push_back(node);
}

// Strongly Connected Components (Kosaraju's Algorithm)
void kosaraju(int n) {
    vector<bool> visited(n + 1, false);
    vector<int> order;

    // Step 1: Perform topological sort
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            topologicalSort(i, visited, order);
        }
    }

    // Step 2: Reverse the graph
    vector<int> reversedAdj[MAXN];
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            reversedAdj[v].push_back(u);
        }
    }

    // Step 3: Perform DFS on the reversed graph in the order of the topological sort
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> components;
    for (int i = order.size() - 1; i >= 0; i--) {
        int node = order[i];
        if (!visited[node]) {
            vector<int> component;
            topologicalSort(node, visited, component);
            components.push_back(component);
        }
    }
}

// Articulation Points and Bridges
vector<int> discoveryTime(MAXN, -1), lowTime(MAXN, -1);
vector<bool> isArticulationPoint(MAXN, false);
vector<pair<int, int>> bridges;
int timer = 0;

void findArticulationPointsAndBridges(int node, int parent = -1) {
    discoveryTime[node] = lowTime[node] = timer++;
    int children = 0;

    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        if (discoveryTime[neighbor] == -1) {
            children++;
            findArticulationPointsAndBridges(neighbor, node);
            lowTime[node] = min(lowTime[node], lowTime[neighbor]);

            // Articulation point condition
            if (lowTime[neighbor] >= discoveryTime[node] && parent != -1) {
                isArticulationPoint[node] = true;
            }

            // Bridge condition
            if (lowTime[neighbor] > discoveryTime[node]) {
                bridges.push_back({node, neighbor});
            }
        } else {
            lowTime[node] = min(lowTime[node], discoveryTime[neighbor]);
        }
    }

    // Root node condition for articulation point
    if (parent == -1 && children > 1) {
        isArticulationPoint[node] = true;
    }
}

// Bipartite Graph Check
bool isBipartite(int n) {
    vector<int> color(n + 1, -1);
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = color[node] ^ 1;
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Eulerian Path and Circuit
bool hasEulerianPath(int n) {
    vector<int> inDegree(n + 1, 0), outDegree(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            outDegree[u]++;
            inDegree[v]++;
        }
    }

    int startNodes = 0, endNodes = 0;
    for (int i = 1; i <= n; i++) {
        if (abs(inDegree[i] - outDegree[i]) > 1) return false;
        if (outDegree[i] - inDegree[i] == 1) startNodes++;
        if (inDegree[i] - outDegree[i] == 1) endNodes++;
    }

    return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
}

int main() {
    // Example usage
    int n, m; // Number of nodes and edges
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adjWeighted[u].push_back({v, w});
        edges.push_back({u, v, w});
    }

    // Call any algorithm as needed
    dijkstra(1, n);
    bellmanFord(1, n);
    floydWarshall(n);
    kruskal(n);
    kosaraju(n);
    findArticulationPointsAndBridges(1);
    isBipartite(n);
    hasEulerianPath(n);

    return 0;
}


vector<int> topological_sort(int n, vector<vector<int>> &graph, vector<int> &ind) {
    set<int> st;  // Stores nodes with in-degree = 0
    vector<int> ans;  // Stores topological order

    for (int i = 1; i <= n; i++)
        if (ind[i] == 0) st.insert(i);

    while (!st.empty()) {
        int par = *st.begin();
        st.erase(st.begin());
        ans.push_back(par);

        for (int child : graph[par]) {
            ind[child]--;
            if (ind[child] == 0) st.insert(child);
        }
    }

    return (ans.size() == n) ? ans : vector<int>{-1};
}


#include <bits/stdc++.h>
using namespace std;

// Graph Representation
const int MAXN = 1e5 + 5; // Adjust the size as needed
vector<int> adj[MAXN];    // Adjacency list for unweighted graph
vector<pair<int, int>> adjWeighted[MAXN]; // Adjacency list for weighted graph

// Depth-First Search (DFS)
void dfs(int node, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, visited);
        }
    }
}

// Breadth-First Search (BFS)
void bfs(int start, int n) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Dijkstra's Algorithm (Single Source Shortest Path - Non-negative weights)
void dijkstra(int start, int n) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int node = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[node]) continue;

        for (auto& edge : adjWeighted[node]) {
            int neighbor = edge.first;
            int weight = edge.second;
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }
}

// Bellman-Ford Algorithm (Single Source Shortest Path - Negative weights allowed)
void bellmanFord(int start, int n) {
    vector<int> dist(n + 1, INT_MAX);
    dist[start] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (int u = 1; u <= n; u++) {
            for (auto& edge : adjWeighted[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 1; u <= n; u++) {
        for (auto& edge : adjWeighted[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative weight cycle\n";
                return;
            }
        }
    }
}

// Floyd-Warshall Algorithm (All Pairs Shortest Path)
void floydWarshall(int n) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    // Initialize distances with direct edges
    for (int u = 1; u <= n; u++) {
        for (auto& edge : adjWeighted[u]) {
            int v = edge.first;
            int weight = edge.second;
            dist[u][v] = min(dist[u][v], weight);
        }
    }

    // Relax all edges
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

// Kruskal's Algorithm (Minimum Spanning Tree)
struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<Edge> edges;
vector<int> parent, rank;

void makeSet(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findSet(int v) {
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v]);
}

void unionSets(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
    }
}

int kruskal(int n) {
    makeSet(n);
    sort(edges.begin(), edges.end());
    int cost = 0;
    for (Edge e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            cost += e.weight;
            unionSets(e.u, e.v);
        }
    }
    return cost;
}

// Prim's Algorithm (Minimum Spanning Tree)
int prim(int start, int n) {
    vector<bool> inMST(n + 1, false);
    vector<int> key(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[start] = 0;
    pq.push({0, start});

    int cost = 0;
    while (!pq.empty()) {
        int node = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (inMST[node]) continue;
        inMST[node] = true;
        cost += weight;

        for (auto& edge : adjWeighted[node]) {
            int neighbor = edge.first;
            int w = edge.second;
            if (!inMST[neighbor] && w < key[neighbor]) {
                key[neighbor] = w;
                pq.push({w, neighbor});
            }
        }
    }
    return cost;
}

// Topological Sort (DFS-based)
vector<int> topologicalOrder;
void topologicalSortDFS(int node, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            topologicalSortDFS(neighbor, visited);
        }
    }
    topologicalOrder.push_back(node);
}

// Topological Sort (BFS-based - Kahn's Algorithm)
vector<int> topologicalSortBFS(int n) {
    vector<int> inDegree(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (order.size() != n) {
        cout << "Graph contains a cycle!\n";
        return {};
    }
    return order;
}

// Strongly Connected Components (Kosaraju's Algorithm)
void kosaraju(int n) {
    vector<bool> visited(n + 1, false);
    vector<int> order;

    // Step 1: Perform topological sort
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            topologicalSortDFS(i, visited);
        }
    }

    // Step 2: Reverse the graph
    vector<int> reversedAdj[MAXN];
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            reversedAdj[v].push_back(u);
        }
    }

    // Step 3: Perform DFS on the reversed graph in the order of the topological sort
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> components;
    for (int i = order.size() - 1; i >= 0; i--) {
        int node = order[i];
        if (!visited[node]) {
            vector<int> component;
            topologicalSortDFS(node, visited, component);
            components.push_back(component);
        }
    }
}

// Articulation Points and Bridges
vector<int> discoveryTime(MAXN, -1), lowTime(MAXN, -1);
vector<bool> isArticulationPoint(MAXN, false);
vector<pair<int, int>> bridges;
int timer = 0;

void findArticulationPointsAndBridges(int node, int parent = -1) {
    discoveryTime[node] = lowTime[node] = timer++;
    int children = 0;

    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        if (discoveryTime[neighbor] == -1) {
            children++;
            findArticulationPointsAndBridges(neighbor, node);
            lowTime[node] = min(lowTime[node], lowTime[neighbor]);

            // Articulation point condition
            if (lowTime[neighbor] >= discoveryTime[node] && parent != -1) {
                isArticulationPoint[node] = true;
            }

            // Bridge condition
            if (lowTime[neighbor] > discoveryTime[node]) {
                bridges.push_back({node, neighbor});
            }
        } else {
            lowTime[node] = min(lowTime[node], discoveryTime[neighbor]);
        }
    }

    // Root node condition for articulation point
    if (parent == -1 && children > 1) {
        isArticulationPoint[node] = true;
    }
}

// Bipartite Graph Check
bool isBipartite(int n) {
    vector<int> color(n + 1, -1);
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = color[node] ^ 1;
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Eulerian Path and Circuit
bool hasEulerianPath(int n) {
    vector<int> inDegree(n + 1, 0), outDegree(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            outDegree[u]++;
            inDegree[v]++;
        }
    }

    int startNodes = 0, endNodes = 0;
    for (int i = 1; i <= n; i++) {
        if (abs(inDegree[i] - outDegree[i]) > 1) return false;
        if (outDegree[i] - inDegree[i] == 1) startNodes++;
        if (inDegree[i] - outDegree[i] == 1) endNodes++;
    }

    return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
}

int main() {
    // Example usage
    int n, m; // Number of nodes and edges
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adjWeighted[u].push_back({v, w});
        edges.push_back({u, v, w});
    }

    // Call any algorithm as needed
    dijkstra(1, n);
    bellmanFord(1, n);
    floydWarshall(n);
    kruskal(n);
    prim(1, n);
    topologicalSortBFS(n);
    kosaraju(n);
    findArticulationPointsAndBridges(1);
    isBipartite(n);
    hasEulerianPath(n);

    return 0;
}





#include <bits/stdc++.h>
using namespace std;

// Fast I/O
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// Prime Sieve (Sieve of Eratosthenes)
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Prime Factorization
vector<pair<int, int>> prime_factors(int n) {
    vector<pair<int, int>> factors;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            factors.push_back({i, cnt});
        }
    }
    if (n > 1) {
        factors.push_back({n, 1});
    }
    return factors;
}

// Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm
int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Modular Inverse
int mod_inverse(int a, int m) {
    int x, y;
    int g = extended_gcd(a, m, x, y);
    if (g != 1) {
        return -1; // No inverse exists
    } else {
        return (x % m + m) % m;
    }
}

// Fast Exponentiation (Binary Exponentiation)
long long binpow(long long a, long long b, long long mod = LLONG_MAX) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Euler's Totient Function
int euler_totient(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

// Chinese Remainder Theorem
int chinese_remainder_theorem(vector<int> &a, vector<int> &m) {
    int n = a.size();
    long long M = 1;
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }
    long long result = 0;
    for (int i = 0; i < n; i++) {
        long long Mi = M / m[i];
        result += a[i] * Mi * mod_inverse(Mi, m[i]);
    }
    return result % M;
}

// Miller-Rabin Primality Test
bool miller_rabin(int n, int k = 5) {
    if (n < 2) return false;
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
        if (n % p == 0) return n == p;
    }
    int d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (int i = 0; i < k; i++) {
        int a = rand() % (n - 4) + 2;
        int x = binpow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        for (int r = 0; r < s - 1; r++) {
            x = binpow(x, 2, n);
            if (x == n - 1) break;
        }
        if (x != n - 1) return false;
    }
    return true;
}

// Lucas-Lehmer Test for Mersenne Primes
bool lucas_lehmer(int p) {
    if (p == 2) return true;
    long long s = 4;
    long long M = (1LL << p) - 1;
    for (int i = 0; i < p - 2; i++) {
        s = (s * s - 2) % M;
    }
    return s == 0;
}

// Pollard's Rho Algorithm for Factorization
long long pollards_rho(long long n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    if (n % 5 == 0) return 5;
    while (true) {
        long long x = rand() % (n - 2) + 2;
        long long y = x;
        long long c = rand() % (n - 1) + 1;
        long long d = 1;
        while (d == 1) {
            x = (binpow(x, 2, n) + c) % n;
            y = (binpow(y, 2, n) + c) % n;
            y = (binpow(y, 2, n) + c) % n;
            d = gcd(abs(x - y), n);
        }
        if (d != n) return d;
    }
}

// Factorization using Pollard's Rho
vector<long long> factorize(long long n) {
    vector<long long> factors;
    if (n == 1) return factors;
    if (miller_rabin(n)) {
        factors.push_back(n);
        return factors;
    }
    long long d = pollards_rho(n);
    vector<long long> left = factorize(d);
    vector<long long> right = factorize(n / d);
    factors.insert(factors.end(), left.begin(), left.end());
    factors.insert(factors.end(), right.begin(), right.end());
    return factors;
}

// Main Function
int main() {
    fastio;

    // Example usage of the functions
    int n = 100;
    vector<bool> primes = sieve(n);
    cout << "Primes up to " << n << ":\n";
    for (int i = 2; i <= n; i++) {
        if (primes[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";

    int num = 56;
    vector<pair<int, int>> factors = prime_factors(num);
    cout << "Prime factors of " << num << ":\n";
    for (auto &p : factors) {
        cout << p.first << "^" << p.second << " ";
    }
    cout << "\n";

    int a = 56, b = 98;
    cout << "GCD of " << a << " and " << b << " is " << gcd(a, b) << "\n";

    int x, y;
    int g = extended_gcd(a, b, x, y);
    cout << "Extended GCD: " << g << " = " << a << "*" << x << " + " << b << "*" << y << "\n";

    int mod_inv = mod_inverse(3, 11);
    cout << "Modular inverse of 3 mod 11 is " << mod_inv << "\n";

    long long pow_result = binpow(2, 10);
    cout << "2^10 = " << pow_result << "\n";

    int totient = euler_totient(30);
    cout << "Euler's Totient of 30 is " << totient << "\n";

    vector<int> remainders = {2, 3, 2};
    vector<int> mods = {3, 5, 7};
    int crt_result = chinese_remainder_theorem(remainders, mods);
    cout << "Chinese Remainder Theorem result: " << crt_result << "\n";

    bool is_prime = miller_rabin(101);
    cout << "Is 101 prime? " << (is_prime ? "Yes" : "No") << "\n";

    bool is_mersenne_prime = lucas_lehmer(7);
    cout << "Is 2^7 - 1 prime? " << (is_mersenne_prime ? "Yes" : "No") << "\n";

    long long factor_num = 123456789;
    vector<long long> factor_list = factorize(factor_num);
    cout << "Factors of " << factor_num << ":\n";
    for (long long f : factor_list) {
        cout << f << " ";
    }
    cout << "\n";

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union (DSU) / Union-Find
struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rank[u] < rank[v]) swap(u, v);
        parent[v] = u;
        rank[u] += rank[v];
    }
};

// Segment Tree
struct SegmentTree {
    int n;
    vector<int> tree;
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
        } else {
            int mid = (l + r) / 2;
            build(arr, 2 * node, l, mid);
            build(arr, 2 * node + 1, mid + 1, r);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
    }
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
        } else {
            int mid = (l + r) / 2;
            if (idx <= mid) update(2 * node, l, mid, idx, val);
            else update(2 * node + 1, mid + 1, r, idx, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
};

// Fenwick Tree / Binary Indexed Tree
struct FenwickTree {
    int n;
    vector<int> tree;
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx) tree[idx] += delta;
    }
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) sum += tree[idx];
        return sum;
    }
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// Trie
struct Trie {
    struct Node {
        map<char, Node*> children;
        bool isEndOfWord;
        Node() : isEndOfWord(false) {}
    };
    Node* root;
    Trie() { root = new Node(); }
    void insert(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new Node();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }
    bool search(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) return false;
            current = current->children[ch];
        }
        return current->isEndOfWord;
    }
};

// Sparse Table (for Range Minimum Query)
struct SparseTable {
    vector<vector<int>> table;
    SparseTable(const vector<int>& arr) {
        int n = arr.size();
        int logn = log2(n) + 1;
        table.resize(n, vector<int>(logn));
        for (int i = 0; i < n; i++) table[i][0] = arr[i];
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int query(int l, int r) {
        int k = log2(r - l + 1);
        return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

// Heavy-Light Decomposition (HLD)
struct HLD {
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;
    HLD(vector<vector<int>>& adj, int root) {
        int n = adj.size();
        parent.resize(n); depth.resize(n); heavy.resize(n, -1);
        head.resize(n); pos.resize(n);
        cur_pos = 0;
        dfs(root, adj);
        decompose(root, root, adj);
    }
    int dfs(int u, vector<vector<int>>& adj) {
        int size = 1, max_c_size = 0;
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                int c_size = dfs(v, adj);
                size += c_size;
                if (c_size > max_c_size) max_c_size = c_size, heavy[u] = v;
            }
        }
        return size;
    }
    void decompose(int u, int h, vector<vector<int>>& adj) {
        head[u] = h;
        pos[u] = cur_pos++;
        if (heavy[u] != -1) decompose(heavy[u], h, adj);
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u]) decompose(v, v, adj);
        }
    }
    int query(int u, int v, SegmentTree& st) {
        int res = 0;
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            res += st.query(1, 0, st.n - 1, pos[head[v]], pos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        res += st.query(1, 0, st.n - 1, pos[u], pos[v]);
        return res;
    }
};

// Main Function
int main() {
    // Example usage of the data structures
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);
    cout << "Segment Tree Query: " << st.query(1, 0, arr.size() - 1, 1, 3) << endl;

    FenwickTree ft(arr.size());
    for (int i = 0; i < arr.size(); i++) ft.update(i + 1, arr[i]);
    cout << "Fenwick Tree Query: " << ft.range_query(2, 4) << endl;

    Trie trie;
    trie.insert("hello");
    cout << "Trie Search: " << trie.search("hello") << endl;

    SparseTable sparse(arr);
    cout << "Sparse Table Query: " << sparse.query(1, 4) << endl;

    return 0;
}


#include <bits/stdc++.h>
using namespace std;

// ========================
// Knuth-Morris-Pratt (KMP) Algorithm
// ========================
vector<int> computeLPS(const string& pattern) {
    int n = pattern.size();
    vector<int> lps(n, 0);
    for (int i = 1, len = 0; i < n;) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
    }
    return lps;
}

vector<int> KMP(const string& text, const string& pattern) {
    vector<int> lps = computeLPS(pattern);
    vector<int> matches;
    int n = text.size(), m = pattern.size();
    for (int i = 0, j = 0; i < n;) {
        if (text[i] == pattern[j]) {
            i++, j++;
            if (j == m) {
                matches.push_back(i - m);
                j = lps[j - 1];
            }
        } else {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return matches;
}

// ========================
// Z-Algorithm
// ========================
vector<int> computeZ(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<int> ZSearch(const string& text, const string& pattern) {
    string concat = pattern + "$" + text;
    vector<int> z = computeZ(concat);
    vector<int> matches;
    int m = pattern.size();
    for (int i = m + 1; i < z.size(); i++) {
        if (z[i] == m) matches.push_back(i - m - 1);
    }
    return matches;
}

// ========================
// Rabin-Karp Algorithm (Rolling Hash)
// ========================
const int BASE = 911382629, MOD = 1e9 + 7;

vector<int> RabinKarp(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    if (n < m) return {};

    // Precompute powers of BASE
    vector<long long> power(n + 1, 1);
    for (int i = 1; i <= n; i++) power[i] = (power[i - 1] * BASE) % MOD;

    // Compute hash of pattern
    long long patternHash = 0;
    for (char ch : pattern) patternHash = (patternHash * BASE + ch) % MOD;

    // Compute hash of all prefixes of text
    vector<long long> textHash(n + 1, 0);
    for (int i = 0; i < n; i++) textHash[i + 1] = (textHash[i] * BASE + text[i]) % MOD;

    // Find matches
    vector<int> matches;
    for (int i = 0; i <= n - m; i++) {
        long long currHash = (textHash[i + m] - textHash[i] * power[m] % MOD + MOD) % MOD;
        if (currHash == patternHash) matches.push_back(i);
    }
    return matches;
}

// ========================
// Manacher's Algorithm (Longest Palindromic Substring)
// ========================
string longestPalindrome(const string& s) {
    string t = "#";
    for (char ch : s) t += ch, t += '#';
    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    for (int i = 0; i < n; i++) {
        if (i < right) p[i] = min(right - i, p[2 * center - i]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1]) p[i]++;
        if (i + p[i] > right) center = i, right = i + p[i];
    }
    int maxLen = 0, start = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] > maxLen) maxLen = p[i], start = (i - p[i]) / 2;
    }
    return s.substr(start, maxLen);
}

// ========================
// Suffix Array and LCP Array
// ========================
vector<int> buildSuffixArray(const string& s) {
    int n = s.size();
    vector<int> p(n), c(n), cnt(max(256, n), 0);
    for (char ch : s) cnt[ch]++;
    for (int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> curr = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (curr != prev) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> buildLCP(const string& s, const vector<int>& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[p[i]] = i;
    vector<int> lcp(n - 1, 0);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k > 0) k--;
    }
    return lcp;
}

// ========================
// Aho-Corasick Algorithm (Multiple Pattern Matching)
// ========================
struct AhoCorasick {
    struct Node {
        map<char, int> children;
        int fail = 0;
        vector<int> output;
    };
    vector<Node> trie;
    AhoCorasick() { trie.emplace_back(); }
    void insert(const string& word, int id) {
        int node = 0;
        for (char ch : word) {
            if (!trie[node].children.count(ch)) {
                trie[node].children[ch] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].children[ch];
        }
        trie[node].output.push_back(id);
    }
    void build() {
        queue<int> q;
        for (auto& [ch, child] : trie[0].children) q.push(child);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (auto& [ch, child] : trie[node].children) {
                int fail = trie[node].fail;
                while (fail && !trie[fail].children.count(ch)) fail = trie[fail].fail;
                if (trie[fail].children.count(ch)) fail = trie[fail].children[ch];
                trie[child].fail = fail;
                trie[child].output.insert(trie[child].output.end(), trie[fail].output.begin(), trie[fail].output.end());
                q.push(child);
            }
        }
    }
    vector<int> search(const string& text) {
        vector<int> matches;
        int node = 0;
        for (int i = 0; i < text.size(); i++) {
            while (node && !trie[node].children.count(text[i])) node = trie[node].fail;
            if (trie[node].children.count(text[i])) node = trie[node].children[text[i]];
            for (int id : trie[node].output) matches.push_back(id);
        }
        return matches;
    }
};

// ========================
// Main Function
// ========================
int main() {
    // Example usage of the string algorithms
    string text = "ababcababcabc";
    string pattern = "abc";

    // KMP
    vector<int> kmpMatches = KMP(text, pattern);
    cout << "KMP Matches: ";
    for (int pos : kmpMatches) cout << pos << " ";
    cout << endl;

    // Z-Algorithm
    vector<int> zMatches = ZSearch(text, pattern);
    cout << "Z-Algorithm Matches: ";
    for (int pos : zMatches) cout << pos << " ";
    cout << endl;

    // Rabin-Karp
    vector<int> rkMatches = RabinKarp(text, pattern);
    cout << "Rabin-Karp Matches: ";
    for (int pos : rkMatches) cout << pos << " ";
    cout << endl;

    // Manacher's Algorithm
    string longestPal = longestPalindrome("babad");
    cout << "Longest Palindromic Substring: " << longestPal << endl;

    // Suffix Array and LCP
    string s = "banana";
    vector<int> suffixArray = buildSuffixArray(s);
    vector<int> lcpArray = buildLCP(s, suffixArray);
    cout << "Suffix Array: ";
    for (int pos : suffixArray) cout << pos << " ";
    cout << endl;
    cout << "LCP Array: ";
    for (int len : lcpArray) cout << len << " ";
    cout << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

// Define common macros for faster I/O and loops
#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define PI 3.1415926535897932384626
#define deb(x) cout << #x << " = " << x << endl;
#define deb2(x, y) cout << #x << " = " << x << ", " << #y << " = " << y << endl;
#define debv(v) cout << #v << ":"; for (auto x : v) cout << x << " "; cout << endl;
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sortall(x) sort(all(x))
#define tr(it, x) for (auto it = x.begin(); it != x.end(); it++)
#define trr(it, x) for (auto it = x.rbegin(); it != x.rend(); it++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define endl '\n'

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

const int mod = 1e9 + 7;
const int INF = 1e9;

// Function to add two numbers modulo mod
int add(int a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

// Function to subtract two numbers modulo mod
int sub(int a, int b) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}

// Function to multiply two numbers modulo mod
int mul(int a, int b) {
    return (a * 1LL * b) % mod;
}

// Function to compute power under modulo mod
int power(int x, int y) {
    int res = 1;
    x = x % mod;
    while (y > 0) {
        if (y & 1) res = mul(res, x);
        y = y >> 1;
        x = mul(x, x);
    }
    return res;
}

// Function to compute inverse under modulo mod
int inv(int x) {
    return power(x, mod - 2);
}

// Function to compute factorial and inverse factorial
vector<int> fact, inv_fact;
void precompute_factorials(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    inv_fact[n] = inv(fact[n]);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = mul(inv_fact[i + 1], i + 1);
    }
}

// Function to compute binomial coefficient C(n, k) modulo mod
int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return mul(fact[n], mul(inv_fact[k], inv_fact[n - k]));
}

// 1D DP Example: Fibonacci Sequence
int fib(int n) {
    if (n <= 1) return n;
    vi dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// 2D DP Example: Longest Common Subsequence (LCS)
int lcs(string &s1, string &s2) {
    int n = s1.size(), m = s2.size();
    vvi dp(n + 1, vi(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// DP with Bitmask Example: Traveling Salesman Problem (TSP)
int tsp(int n, vvi &dist) {
    vvi dp(1 << n, vi(n, INF));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + dist[u][v]);
            }
        }
    }
    int ans = INF;
    for (int u = 1; u < n; u++) {
        ans = min(ans, dp[(1 << n) - 1][u] + dist[u][0]);
    }
    return ans;
}

// DP with Segment Trees or Fenwick Trees (Optional for advanced problems)
// Example: Range Maximum Query with DP
struct SegmentTree {
    int size;
    vi tree;

    SegmentTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size, 0);
    }

    void update(int idx, int val) {
        idx += size;
        tree[idx] = val;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    int query(int l, int r) {
        int res = 0;
        l += size;
        r += size;
        while (l <= r) {
            if (l % 2 == 1) res = max(res, tree[l++]);
            if (r % 2 == 0) res = max(res, tree[r--]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

// DP with Matrix Exponentiation (Optional for advanced problems)
// Example: Fibonacci with Matrix Exponentiation
struct Matrix {
    vvi mat;
    int n;

    Matrix(int sz) {
        n = sz;
        mat.assign(n, vi(n, 0));
    }

    Matrix operator*(const Matrix &other) {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res.mat[i][j] = add(res.mat[i][j], mul(mat[i][k], other.mat[k][j]));
                }
            }
        }
        return res;
    }
};

Matrix matrix_power(Matrix x, int y) {
    Matrix res(x.n);
    for (int i = 0; i < x.n; i++) res.mat[i][i] = 1;
    while (y > 0) {
        if (y & 1) res = res * x;
        x = x * x;
        y >>= 1;
    }
    return res;
}

int fib_matrix(int n) {
    if (n <= 1) return n;
    Matrix mat(2);
    mat.mat = {{1, 1}, {1, 0}};
    mat = matrix_power(mat, n - 1);
    return mat.mat[0][0];
}

// Main function
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Example usage of DP functions
    int n = 10;
    cout << "Fibonacci(" << n << ") = " << fib(n) << endl;

    string s1 = "abcde", s2 = "ace";
    cout << "LCS of " << s1 << " and " << s2 << " = " << lcs(s1, s2) << endl;

    int nodes = 4;
    vvi dist = {{0, 10, 15, 20},
                {10, 0, 35, 25},
                {15, 35, 0, 30},
                {20, 25, 30, 0}};
    cout << "TSP minimum cost = " << tsp(nodes, dist) << endl;

    return 0;
}