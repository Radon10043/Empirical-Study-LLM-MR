import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 4: If we select a subset of indices, the distances to those indices from any node
        should be the same as when we calculate them without any indices specified."""
        indices = [0, 1]
        csgraph = csr_matrix(graph)

        # Get source output for all pairs
        full_dist_matrix = shortest_path(csgraph)

        # Get follow-up output for selected indices only
        subset_dist_matrix = shortest_path(csgraph, indices=indices)

        # Verification
        for index in indices:
            for other_index in range(len(full_dist_matrix)):
                source_out = full_dist_matrix[other_index][index]
                follow_out = subset_dist_matrix[other_index]
                self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
