#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using std::cout;

class Graph
{
public:
    Graph(std::vector<std::vector<double>>& data);
    ~Graph();
    int GetVertexesCount();
    int GetEdgeCount();

    double& operator()(int row, int col);
    double operator()(int row, int col) const;
private:
    std::vector<std::vector<double>> m_data;
    int vertex_count, edge_count;
    void calculateEdgeCount();
};

double& Graph::operator()(int row, int col)
{
    assert(col >= 0 && col < vertex_count);
    assert(row >= 0 && row < vertex_count);

    return m_data[row][col];
}

double Graph::operator()(int row, int col) const
{
    assert(col >= 0 && col < vertex_count);
    assert(row >= 0 && row < vertex_count);

    return m_data[row][col];
}
void Graph::calculateEdgeCount() {
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            double cur = m_data[i][j];
            if (cur) {
                edge_count += 1;
            }
        }
    }
    edge_count /= 2;
}

int Graph::GetVertexesCount() {
    return vertex_count;
}
int Graph::GetEdgeCount() {
    return edge_count;
}

Graph::Graph(std::vector<std::vector<double>>& data)
{
    vertex_count = data.size();
    m_data = data;
    calculateEdgeCount();
}

Graph::~Graph()
{
}


std::vector<int> BreadthFirstSearch(Graph& graph, int start_vertex) {
    if (start_vertex > graph.GetVertexesCount() or start_vertex < 0)
        return {};

    std::vector<int> enter_order;
    std::vector<short> visited(graph.GetVertexesCount());
    std::queue<int> q;

    // Функция принимает вершину, нумерация которой начинается с 1
    // Для удобства уменьшаем ее значение на 1, чтобы нумерация начиналась с 0
    visited[start_vertex] = true;
    q.push(start_vertex);
    enter_order.emplace_back(start_vertex);

    while (!q.empty()) {
        auto from = q.front();
        q.pop();

        for (int to = 0, size = graph.GetVertexesCount(); to != size; ++to) {
            if (!visited[to] and graph(from, to) != 0) {
                visited[to] = true;
                q.push(to);
                enter_order.emplace_back(to);
            }
        }
    }
    return enter_order;
}


int main()
{
    std::vector<std::vector<double>> data = { {0, 1, 5, 7}, {3, 0, 4, 0}, {5, 4, 0, 7}, {7, 0, 7, 0} };
    Graph graph(data);

    std::vector<int> rezBFS = BreadthFirstSearch(graph, 1);
    for (auto t : rezBFS) {
        cout << t << ' ';
    }
    cout << '\n';
}

