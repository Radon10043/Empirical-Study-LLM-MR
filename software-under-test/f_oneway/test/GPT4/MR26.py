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
    def test_doubling_groups(self, *groups):
        """MR26: Doubling the data by appending a group to itself should maintain the same F-statistic and p-value due to unchanged group means and variances."""

        if not all(len(group) > 0 for group in groups):
            self.skipTest("Some groups have no data to double.")

        # Double each group by appending it to itself
        doubled_groups = [np.concatenate([group, group]) for group in groups]

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*doubled_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
