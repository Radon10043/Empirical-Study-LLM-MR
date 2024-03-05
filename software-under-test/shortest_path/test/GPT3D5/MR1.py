from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test1(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 1: Given the same graph, the same source and destination vertices,
        but with reversed direction (directed/undirected), the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
