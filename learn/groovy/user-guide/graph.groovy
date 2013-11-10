// adjcent list represented graph
class Graph
{
    public void addVertex(v)
    {
        assert ! adjList.containsKey(v)
        adjList[v] = []
    }
    public void addEdge(v1, v2)
    {
        assert adjList.containsKey(v1)
        assert adjList.containsKey(v2)
        
        adjList[v1].add(v2)
    }
    
    public void dump()
    {
        adjList.each {
            println it
        }
    }
    
    public void BFS() {}
    public void DFS() {}
    public shortestpath() {}
    public void traverse() {}
    
    private adjList = [:]
}

Graph graph = new Graph()
graph.addVertex('a')
graph.addVertex('b')
graph.addVertex('c')
graph.addEdge('a', 'b')
graph.addEdge('a', 'c')
graph.addEdge('b', 'c')
graph.dump()