import unittest
import sys
import os

import numpy as np

from scipy.stats import f_oneway
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test_symmetrical_extension_of_groups(self, *groups):    # Fixed
        """MR38: Extending each group symmetrically around its mean should not significantly change the F-statistic or p-value."""
        # Calculate mean of each group and extend symmetrically
        symmetrical_extended_groups = list()
        for group in groups:
            tmp_list = list()
            for val in group:
                tmp_list.append(val + np.random.uniform(-0.1, 0.1))
            for val in group:
                tmp_list.append(val - np.random.uniform(-0.1, 0.1))
            symmetrical_extended_groups.append(tmp_list)

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*symmetrical_extended_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
