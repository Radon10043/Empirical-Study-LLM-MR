from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test5(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 5: Given the same graph, the same source and destination vertices,
        but using the Bellman-Ford algorithm, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method='BF')[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
