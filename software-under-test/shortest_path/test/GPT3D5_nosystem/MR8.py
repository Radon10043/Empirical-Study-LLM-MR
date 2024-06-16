import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 8: Given the same graph and the same source and destination vertices, 
        but with overwrite=True, the output should be the same as when overwrite=False."""
        # Get source output with overwrite=False
        source_out_false = shortest_path(graph, method=method, overwrite=False)

        # Get source output with overwrite=True
        source_out_true = shortest_path(graph, method=method, overwrite=True)

        # Verification
        self.assertTrue(np.array_equal(source_out_false, source_out_true))


if __name__ == "__main__":
    unittest.main()
