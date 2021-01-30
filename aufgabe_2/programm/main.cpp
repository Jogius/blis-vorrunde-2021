#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Kante
{
  int quelle, ziel, gewicht;
};

struct UnionFind
{
  vector<int> knoten;

  UnionFind(int groesse) : knoten(groesse, -1) {}

  bool unite(int index1, int index2) { return root(index1) == root(index2); }

  int root(int index) { return knoten[index] < 0 ? index : knoten[index] = root(knoten[index]); }
};

void solve(vector<Kante> kanten, int index, int summe, vector<Kante> &loesung, vector<int> &grad, UnionFind &uf, int &besteSumme)
{
  if (index == kanten.size())
  {
    if (loesung.size() + 1 < uf.knoten.size())
      summe = numeric_limits<int>::max();
    if (besteSumme > summe)
      besteSumme = summe;
    return;
  }

  if (grad[kanten[index].ziel] == 0 && uf.root(kanten[index].quelle) != uf.root(kanten[index].ziel))
  {
    UnionFind uf2 = uf;
    uf2.unite(kanten[index].quelle, kanten[index].ziel);

    loesung.push_back(kanten[index]);
    grad[kanten[index].ziel]++;

    solve(kanten, index + 1, summe + kanten[index].gewicht, loesung, grad, uf2, besteSumme);

    grad[kanten[index].ziel]--;
    loesung.pop_back();
  }
  solve(kanten, index + 1, summe, loesung, grad, uf, besteSumme);
}

int main()
{
  // Input
  int n, m;
  cin >> n >> m;

  unordered_map<string, int> ids;
  for (int i = 0; i < n; i++)
  {
    string name;
    cin >> name;
    ids[name] = i;
  }

  vector<Kante> graph;
  for (int i = 0; i < m; i++)
  {
    string quelle, ziel;
    int gewicht;
    cin >> quelle >> ziel >> gewicht;

    graph.push_back({ids[quelle], ids[ziel], gewicht});
  }

  // Brute Force Algorithmus
  int besteSumme = numeric_limits<int>::max();
  vector<Kante> loesung;

  vector<int> grad(n);
  grad[0] = 1;

  UnionFind uf(n);

  solve(graph, 0, 0, loesung, grad, uf, besteSumme);

  // Output
  cout << besteSumme << endl;
}
