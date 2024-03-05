from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test16(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 16: Given the same input graph, the same source and destination vertices,
        but with the weights multiplied by -1 and the direction reversed, the distances should not change."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        follow_graph = [[-weight for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
