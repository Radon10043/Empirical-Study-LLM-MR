from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test18(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 18: Given the same graph, the same source and destination vertices,
        but with the graph having a limit for Dijkstra's algorithm, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, limit=None)[src][dst]

        # Construct follow-up input: applying a limit for Dijkstra's algorithm
        follow_out = shortest_path(graph, method=method, limit=5)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
