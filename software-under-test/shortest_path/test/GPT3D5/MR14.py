from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test14(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 14: Given the same graph, the same source and destination vertices,
        but with the edge weights changed to their absolute values, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = [[abs(weight) for weight in row] for row in graph]

        # Get folllow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
