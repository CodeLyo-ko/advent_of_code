#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    char* name;
    int visited;
} node_t;

typedef struct 
{
    node_t* nodeA;
    char* name_nodeB; //temporary stock the name to find the node after
    node_t* nodeB;
} edge_t;

node_t* find_node(node_t** nodes, int n_nodes, char* name_node)
{
    for (int i = 0; i < n_nodes; i++)
    {
        if (!strcmp(nodes[i]->name, name_node))
        {
            return nodes[i];
        }
    }
    return NULL;
}

void DFS(node_t* node, edge_t* edges, int n_edges, int edge1, int edge2, int edge3)
{
    node->visited = 1;
    for (int i = 0; i < n_edges; i++)
    {
        if (i == edge1 || i == edge2 || i == edge3)
        {
            continue;
        }

        if (edges[i].nodeA == node && !edges[i].nodeB->visited)
        {
            DFS(edges[i].nodeB, edges, n_edges, edge1, edge2, edge3);
        }

        else if (edges[i].nodeB == node && !edges[i].nodeA->visited)
        {
            DFS(edges[i].nodeA, edges, n_edges, edge1, edge2, edge3);
        }
    }
}

int* kargerMinCut(int n_nodes, edge_t* edges, int n_edges, int* n_edges_to_cut)
// return the index of edges to cut
{
    //copy graph
    int copy_n_nodes = n_nodes;
    int copy_n_edges = n_edges;
    edge_t* copy_edges = malloc(n_edges * sizeof(edge_t));
    for (int i = 0; i < n_edges; i++)
    {
        copy_edges[i].nodeA = edges[i].nodeA;
        copy_edges[i].nodeB = edges[i].nodeB;
    }

    while (copy_n_nodes > 2)
    {
        //choose a random edge to cut
        int edge_to_cut = rand() % copy_n_edges;
        node_t* nodeA = copy_edges[edge_to_cut].nodeA;
        node_t* nodeB = copy_edges[edge_to_cut].nodeB;
        if (nodeA == nodeB)
        {
            continue;
        }

        //merge the two nodes : nodeB will become nodeA
        for (int i = 0; i < copy_n_edges; i++)
        {
            if (copy_edges[i].nodeA->name == nodeB->name)
            {
                copy_edges[i].nodeA = nodeA;
            }
            if (copy_edges[i].nodeB->name == nodeB->name)
            {
                copy_edges[i].nodeB = nodeA;
            }
        }


        copy_n_nodes--;

    }

    int* index = malloc(100 * sizeof(int));
    int n = 0;
    for (int i = 0; i < copy_n_edges; i++)
    {
        if (copy_edges[i].nodeA != copy_edges[i].nodeB)
        {
            index[n++] = i; 
        }
    }

    free(copy_edges);

    *n_edges_to_cut = n;
    return index;

}

int n_node_in_group(node_t** nodes, int n_nodes, edge_t* edges, int n_edges, int edge1, int edge2, int edge3)
/* Return number of nodes in the group of a random node
 * with edge1, edge2, edge3 removed
 * 
 */
{
    DFS(nodes[0], edges, n_edges, edge1, edge2, edge3);

    int ans = 0;
    for (int i = 0; i < n_nodes; i++)
    {
        if (nodes[i]->visited)
        {
            ans++;
            nodes[i]->visited = 0;
        }
    }

    return ans;

}


int main()
{
    srand(time(NULL));

    node_t** graph = malloc(2000 * sizeof(node_t*));
    int n_nodes = 0;

    edge_t* edges = malloc(4000 * sizeof(edge_t));
    int n_edges = 0;

    char c = getchar();
    int tmp;
    while (c != EOF)
    {
        graph[n_nodes] = malloc(sizeof(node_t));
        graph[n_nodes]->name = calloc(5, sizeof(char));
        graph[n_nodes]->visited = 0;

        tmp = 0;
        while(c != ':')
        {
            graph[n_nodes]->name[tmp++] = c;
            c = getchar();
        }

        getchar(); c = getchar();

        while (c != '\n')
        {
            edges[n_edges].nodeA = graph[n_nodes];
            edges[n_edges].name_nodeB = calloc(5, sizeof(char));
            tmp = 0;
            while (c != ' ' && c != '\n')
            {
                edges[n_edges].name_nodeB[tmp++] = c;
                c = getchar();
            }

            n_edges++;

            if (c == '\n')
            {
                break;
            }

            c = getchar();
        }

        n_nodes++;
        c = getchar();
    }

    for (int i = 0; i < n_edges; i++)
    {
        edges[i].nodeB = find_node(graph, n_nodes, edges[i].name_nodeB);
        if (!edges[i].nodeB)
        //not existing node
        {
            graph[n_nodes] = malloc(sizeof(node_t));
            graph[n_nodes]->name = strdup(edges[i].name_nodeB);
            graph[n_nodes]->visited = 0;
            edges[i].nodeB = graph[n_nodes];
            n_nodes++;
        }
        free(edges[i].name_nodeB);
    }

    int n_edges_to_cut;
    int* edges_to_cut = NULL;
    do
    {
        free(edges_to_cut);
        edges_to_cut = kargerMinCut(n_nodes, edges, n_edges, &n_edges_to_cut);
    } while (n_edges_to_cut != 3);

    int ans = n_node_in_group(graph, n_nodes, edges, n_edges, edges_to_cut[0], edges_to_cut[1], edges_to_cut[2]);
    printf("%d\n", (n_nodes - ans) * ans);

    free(edges_to_cut);
    for (int i = 0; i < n_nodes; i++)
    {
        free(graph[i]->name);
        free(graph[i]);
    }
    free(graph);
    free(edges);
    return 0;
}