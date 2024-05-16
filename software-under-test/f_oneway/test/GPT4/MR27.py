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
    def test_group_reduction_by_averaging_pairs(self, *groups):
        """MR27: Reducing the size of the groups by averaging pairs of data points should not significantly affect the F-statistic or the p-value."""
        # Reduce the size of each group by averaging each pair of elements
        reduced_groups = []
        for group in groups:
            if len(group) % 2 != 0:
                # If the group has an odd number of elements, temporarily add a copy of the last element
                group = np.append(group, group[-1])
            # Reshape the group into pairs and take the mean of each pair
            reduced_group = group.reshape(-1, 2).mean(axis=1)
            reduced_groups.append(reduced_group)

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*reduced_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
