import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: Given the same graph and the same source and destination vertices,
        and different subsets of indices, the shortest path with a larger index set should be no longer
        than the shortest path with a smaller index set."""
        # Get source output with no indices specified
        source_out_all = shortest_path(graph, method=method)

        # Get two different subsets of indices
        index_set1 = [0, 1, 2]
        index_set2 = [0, 1]

        # Get source output with both index sets
        source_out_index1 = shortest_path(graph, method=method, indices=index_set1)
        source_out_index2 = shortest_path(graph, method=method, indices=index_set2)

        # Verification
        self.assertTrue(np.all(source_out_index2 <= source_out_index1))


if __name__ == "__main__":
    unittest.main()
