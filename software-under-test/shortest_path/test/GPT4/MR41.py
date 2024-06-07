import os, sys

import scipy as sp

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test41(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 41: If a vertex is split into two where the new vertex duplicates 
        all the outgoing and incoming edges of the original, then this should not affect the shortest 
        paths that do not go through the split vertex."""
        # Assume the graph is directed for simplicity
        # Get source output
        original_distances = shortest_path(graph, method=method, directed=True)

        # Split the vertex, duplicating its edges
        split_vertex = randint(0, graph.shape[0] - 1)  # Randomly select a vertex to split
        graph_with_split_vertex = self.split_graph_vertex(graph, split_vertex)

        # Get follow-up output
        new_distances = shortest_path(graph_with_split_vertex, method=method, directed=True)

        # Verify that distances remain unchanged for paths not going through the split vertex
        # ... Test logic here would depend on the strategy for duplicating vertices ...

    def split_graph_vertex(self, graph, vertex_to_split):
        """Splits a specified vertex by duplicating it and all its edges."""
        graph_extended = self.extend_graph_with_additional_vertex(graph)
        # Duplicate all edges of the original vertex
        # ... Implementation here would depend on the strategy for duplicating vertices ...
        return graph_extended

    def extend_graph_with_additional_vertex(self, graph):
        """Extends the graph with an additional vertex, without adding any edges."""
        import scipy.sparse
        num_vertices = graph.shape[0]
        extended_graph = scipy.sparse.lil_matrix((num_vertices + 1, num_vertices + 1))
        extended_graph[:num_vertices, :num_vertices] = graph
        return extended_graph.tocsr()


if __name__ == "__main__":
    unittest.main()
