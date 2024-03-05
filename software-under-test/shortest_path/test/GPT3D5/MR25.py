from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test25(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 25: Given the same graph, the same source and destination vertices, and the same algorithm, 
        but with all weights increased by a constant value, the resulting shortest path should remain the same."""
        # Get source output
        predecessors = shortest_path(graph, method=method, return_predecessors=True)[1]
        source_out = get_shortest_path(predecessors, src, dst)

        # Increase all weights in the graph by a constant value
        follow_graph = [[weight + 5 for weight in row] for row in graph]

        # Get follow-up output
        predecessors = shortest_path(follow_graph, method=method, return_predecessors=True)[1]
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
