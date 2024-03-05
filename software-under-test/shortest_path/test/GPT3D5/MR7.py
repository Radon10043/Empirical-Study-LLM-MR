from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: Given the same graph, the same source and destination vertices,
        but using unweighted input graph, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, unweighted=False)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method, unweighted=True)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
