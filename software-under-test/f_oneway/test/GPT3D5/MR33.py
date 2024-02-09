import unittest
import sys
import os

import numpy as np

from scipy.stats import f_oneway, kruskal
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, *groups):
        """MR33: Using a different statistical test on the same data should not affect the result."""
        # Get source output
        source_out = f_oneway(*groups).pvalue

        # Using a different statistical test (e.g., Kruskal-Wallis H-test)
        follow_out = kruskal(*groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
