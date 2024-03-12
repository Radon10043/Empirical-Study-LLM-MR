import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):
    def multiply_by_scalar(self, graph: list, scalar: int) -> list:
        """Multiply the entire matrix by a scalar.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        scalar : int
            The scalar to multiply the matrix by

        Returns
        -------
        list
            The new graph after multiplying the entire matrix by the scalar
        """
        n = len(graph)
        new_graph = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                new_graph[i][j] = graph[i][j] * scalar
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 9: Multiplying the entire matrix by a scalar should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Multiply the entire matrix by a scalar
        follow_graph = self.multiply_by_scalar(graph, 2)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()