import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 19: If the shortest path does not go through a particular vertex z,
        then removing z from the graph should not change the shortest path from src to dst."""
        # Get the shortest path from src to dst
        matrix, predcessors = shortest_path(graph, method=method, return_predecessors=True)
        source_cost = matrix[src][dst]
        source_path = get_shortest_path(predcessors, src, dst)

        # Pick a vertex 'z' that is not in the shortest path from src to dst
        for z in range(len(graph)):
            if z not in source_path:
                # Create a graph without vertex 'z'
                graph_without_z = [row[:z] + row[z + 1:] for row in graph[:z] + graph[z + 1:]]
                # Adjust src and dst for removed vertex
                adjusted_src = src - 1 if z < src else src
                adjusted_dst = dst - 1 if z < dst else dst

                # Get the shortest path in the adjusted graph
                matrix, predcessors = shortest_path(graph_without_z, method=method, return_predecessors=True)
                follow_cost = matrix[adjusted_src][adjusted_dst]

                # Verification of path and cost
                self.assertEqual(source_cost, follow_cost)
                break  # Only need to test with one such vertex, so we break after verification


if __name__ == "__main__":
    unittest.main()
