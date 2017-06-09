/*
This file implements the Tranjan's algorithm to find strong connected components
*/
#include <bits/stdc++.h>
#include <graphviz/cgraph.h>

using namespace std;

void strongConnect(Agnode_t*, Agraph_t*);

typedef struct node {
    int idx, lowPoint;
    bool onStack;
} nodeInfo;

unordered_map<string, nodeInfo> info;
int nOfSub, Index;
stack<Agnode_t*>S;

void strongConnect(Agnode_t *v, Agraph_t* G) {
    string name(agnameof(v));
    info[name].idx = Index;
    info[name].lowPoint = Index++;
    S.push(v);
    info[name].onStack = true;

    for (Agedge_t *i = agfstout(G, v); i; i= agnxtout(G, i)) {
        string name2(agnameof(aghead(i)));
        if (info[name2].idx == -1) {
            strongConnect(aghead(i), G);
            info[name].lowPoint = min(info[name].lowPoint,info[name2].lowPoint);
        } else if (info[name2].onStack)
            info[name].lowPoint = min(info[name].lowPoint,info[name2].idx);
    }

    // v isRoot
    if (info[name].idx == info[name].lowPoint) {
        Agraph_t *sub;
        // create new subGraph
        sub = agsubg(G, (char*)(string("cluster")+to_string(nOfSub++)).c_str(), 1);
        Agnode_t * newNode;
        do {
            newNode = S.top();
            S.pop();
            string name2(agnameof(newNode));
            info[name2].onStack = false;
            agsubnode(sub, newNode, 1); 
            cout << "Adding '"<<agnameof(newNode)<<"' to subgraph.\n";
        } while (newNode != v);
    }
}

int main() {
    nOfSub = 1;
    Index = 0;
    
    //clean stack
    while (!S.empty()) S.pop();

    Agraph_t *G = agread(stdin, NULL);

    for (Agnode_t *v = agfstnode(G); v; v=agnxtnode(G, v)) {
        string name(agnameof(v));
        info[name].idx = -1;
        info[name].onStack = false;
    }

    for (Agnode_t *v = agfstnode(G); v; v=agnxtnode(G, v)) {
        string name(agnameof(v));
        if (info[name].idx == -1) 
            strongConnect(v, G);
    }

    agwrite(G, stdout);

    agclose(G);
    return 0;
}
