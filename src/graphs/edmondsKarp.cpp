#include "Graph.h"
#include "edmondsKarp.h"

template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<Vertex<T>*> q;
    s->setVisited(true);
    q.push(s);

    while(!q.empty() && !t->isVisited()) {
        Vertex<T>* v = q.front();
        q.pop();

        for(auto e : v->getAdj()) {
            double residual = e->getWeight() - e->getFlow();
            testAndVisit(q, e, e->getDest(), residual);
        }

        for(auto e : v->getIncoming()) {
            double residual = e->getFlow();
            testAndVisit(q, e, e->getOrig(), residual);
        }
    }

    return t->isVisited();
}

template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
    Vertex<T>* v = t;

    while(v != s) {
        Edge<T>* e = v->getPath();

        if(e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }

    return f;
}

template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    Vertex<T>* v = t;

    while(v != s) {
        Edge<T>* e = v->getPath();

        if(e->getDest() == v) {
            e->setFlow(e->getFlow() + f);
            v = e->getOrig();
        } else {
            e->setFlow(e->getFlow() - f);
            v = e->getDest();
        }
    }
}

void edmondsKarp(Graph<int> *g, int source, int target) {
    Vertex<int>* s = g->findVertex(source);
    Vertex<int>* t = g->findVertex(target);

    if(s == nullptr || t == nullptr || s == t) return;

    for(auto v : g->getVertexSet()) {
        for(auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }

    while(findAugmentingPath(g, s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}