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
    def test_merge_and_resplit_groups(self, *groups):
        """MR18: Merging two groups and then resplitting them into two new groups should not significantly affect the F-statistic or the p-value."""
        if len(groups) < 2:
            self.skipTest("Not enough groups to merge and resplit.")

        # Merge two groups
        merged_group = np.concatenate(groups[:2])

        # Resplit the merged group at a different point than the original group sizes
        split_index = np.random.randint(1, len(merged_group) - 1)
        new_group1 = merged_group[:split_index]
        new_group2 = merged_group[split_index:]

        new_groups = [new_group1, new_group2] + list(groups[2:])

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*new_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
