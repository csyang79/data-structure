O(v^2)
void Graph::topsort1()
{
	for (int count = 0; count < numberOfVertex; ++count)
	{
		Vertex v = findNewVertexOfIndegreeZero();
		if (v == NOT_A_VERTEX)
			throw CycleFound();
		v.topNum = count;
		for each Vertex w adjacent to v
			--w.indegree;
	}
}

O(V+E)
void Graph::topsort2()
{
	queue<Vertex> q;
	int count = 0;
	for (each Vertex v)
		if (v.indegree == 0)
			q.push(v);
	
	while (!q.empty())
	{
		Vertex v = q.top();
		q.pop();
		v.topNum = ++count;
		for each Vertex w adjacent to v 
			if (--w.indegree == 0)
				q.push(w)
	}
	if (count != numberOfVertex)	
		throw CycleFound();
}
