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
    def test_data_removal(self, *groups):
        """MR23: Removing a random subset of data from a group should not drastically affect the F-statistic or the p-value, assuming the subset is small."""

        if len(groups) == 0 or min([len(g) for g in groups]) <= 2:
            self.skipTest("Not enough data points in one or more groups to remove.")

        # Randomly choose a group and remove a subset of its data points
        removal_index = np.random.choice(len(groups))
        removal_fraction = 0.1  # Remove 10% of its data
        group_to_remove = groups[removal_index]
        size_to_remove = int(len(group_to_remove) * removal_fraction)
        if size_to_remove == 0:
            size_to_remove = 1  # Ensure at least one element is removed
        indices_to_remove = np.random.choice(len(group_to_remove), size_to_remove, replace=False)
        new_group_to_remove = np.delete(group_to_remove, indices_to_remove)

        modified_groups = list(groups)
        modified_groups[removal_index] = new_group_to_remove

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*modified_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.1)


if __name__ == "__main__":
    unittest.main()
