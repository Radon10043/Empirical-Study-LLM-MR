import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 23: If we add a new edge with a very large weight, it should not be 
        part of the shortest path because its weight will make the path significantly longer."""
        # Get source output
        source_distance = shortest_path(graph, method=method)[src][dst]

        # Add a new edge with a very large weight between two non-source and non-destination nodes
        large_weight_graph = graph.copy()
        for i in range(len(graph)):
            for j in range(i, len(graph)):
                if i != j and graph[i][j] == 0:
                    large_weight_graph[i][j] = 1000000
                    break

        follow_distance = shortest_path(large_weight_graph, method=method)[src][dst]

        # Verification: the additional edge with large weight should not affect original shortest path
        self.assertEqual(source_distance, follow_distance)


if __name__ == "__main__":
    unittest.main()
