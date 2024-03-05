from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test27(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 27: Given the same graph with the same source and destination vertices, the output should remain the same 
        irrespective of the presence of negative edge weights."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Create a graph with negative edge weights
        negative_graph = [[-weight for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(negative_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
