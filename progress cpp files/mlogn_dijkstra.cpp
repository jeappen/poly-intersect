#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
// #include <cstdint>
#include <set>

//const int INT_MAX=32000;
using namespace std;
struct edge { int to, length; };
    
float dijkstra(const vector< vector<edge> > &graph, int source, int target) {
    vector<float> min_distance( graph.size(), INT_MAX );
    min_distance[ source ] = 0;
    set< pair<int,int> > active_vertices;
    active_vertices.insert( {0,source} );
    vector<edge>::const_iterator i;
    edge e;
   // / vector<edge> edge = graph[active_vertices.begin()->second];
    while (!active_vertices.empty()) {
        int where = active_vertices.begin()->second;
        if (where == target) return min_distance[where];
        active_vertices.erase( active_vertices.begin() );

        for (i=graph[where].begin();i!=graph[where].end();i++) {
            e=(*i);
            if (min_distance[e.to] > min_distance[where] + e.length) {
                active_vertices.erase( { min_distance[e.to], e.to } );
                min_distance[e.to] = min_distance[where] + e.length;
                active_vertices.insert( { min_distance[e.to], e.to } );
            }
        }
    }
    return INT_MAX;
}
int main(int argc, char const *argv[])
{   cout<<"hello";
    vector< vector<edge> > graph=vector< vector<edge> >();
    vector<edge> e;
    int i,l=100;
    for(i=0;i<l;i++){
    e.clear();
    e.push_back(edge());
    if(i!=l-1){
    e[0].to=i+1;
    e[0].length=1e5;}
    if(i==2){
        e.push_back(edge());
        e[1].to=4;
        e[1].length=1;
    }
    if(i==8){
        e.push_back(edge());
        e[1].to=60;
        e[1].length=1;
    }
    if(i==60){
        e.push_back(edge());
        e[1].to=59;
        e[1].length=1;
    }
    graph.push_back(e);
    }
    printf("%.2f\n",dijkstra(graph,0,59) );
    return 0;
}