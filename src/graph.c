#include "./graph.h"
#include "./heap.h"
#include "./edge.h"
#include "./node.h"
#include <float.h>

#include <stdlib.h>

struct graph {
    Node** nodes;
    int n;
    int* csm[3];
};

Graph* init_graph(Node** nodes, int n, int* servers, int* monitors, int* clients) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));

    graph->n = n;
    graph->nodes = nodes;
    graph->csm[0] = servers;
    graph->csm[1] = monitors;
    graph->csm[2] = clients;
    return graph;
}

void destroy_graph(Graph* g) {
    destroy_node_vector(g->nodes, g->n);
    free(g->csm[0]);
    free(g->csm[1]);
    free(g->csm[2]);
    free(g);
}

/*
1) Initialize distances of all vertices as infinite.

2) Create an empty priority_queue pq.  Every item
   of pq is a pair (weight, vertex). Weight (or 
   distance) is used used as first item  of pair
   as first item is by default used to compare
   two pairs

3) Insert source vertex into pq and make its
   distance as 0.

4) While pq doesn't become empty
    a) Extract minimum distance vertex from pq. 
       Let the extracted vertex be u.
    b) Loop through all adjacent of u and do 
       following for every vertex v.

           // If there is a shorter path to v
           // through u. 
           If dist[v] > dist[u] + weight(u, v)

               (i) Update distance of v, i.e., do
                     dist[v] = dist[u] + weight(u, v)
               (ii) Insert v into the pq (Even if v is
                    already there)
               
5) Print distance array dist[] to print all shortest
   paths. 

*/ 

double dijkstra(Graph* graph, int src, int dest, int n_edges){
    Heap* heap = heap_init(n_edges, graph->n, src);
    double distance;
    heap_insert(heap, src, 0);  

    while(!heap_is_empty(heap)){
        int u = heap_min(heap); // remove
  
        Node* node = graph->nodes[src];

        for(Edge* edge = get_w(node); edge != NULL; edge = get_next(edge))
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = get_dest(edge);
            int weight = get_weight(edge);

            double dist_u = get_heap_dist(heap, u);
            double dist_v = get_heap_dist(heap, v);
            
            //  If there is shorted path to v through u.
            if (dist_v > dist_u + weight) {
                // Updating distance of v
                heap_insert(heap, v, dist_v); 
            }
        }
    }

    distance = get_heap_dist(heap, dest);

    heap_destroy(heap);

    return distance;
}

/*
void Graph::shortestPath(int src)
{
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
  
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(V, INF);
  
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;
  
    //  Looping till priority queue becomes empty (or all
    //  distances are not finalized) 
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();
  
        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;
  
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
  
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

*/