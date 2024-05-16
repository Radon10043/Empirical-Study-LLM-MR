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
    def test_splitting_groups(self, *groups):
        """MR7: Splitting one group into two groups, while keeping their combined sample the same, should not affect the F-statistic and p-value."""
        # Choose a group to split, assuming all groups have at least two samples
        group_to_split = np.random.choice(groups)

        if len(group_to_split) < 2:
            self.skipTest("Selected group has less than two samples to split")

        # Randomly split group into two
        np.random.shuffle(group_to_split)
        midpoint = len(group_to_split) // 2
        split_group_1 = group_to_split[:midpoint]
        split_group_2 = group_to_split[midpoint:]

        # Prepare new group list
        new_groups = [g for g in groups if not np.array_equal(g, group_to_split)]
        new_groups.append(split_group_1)
        new_groups.append(split_group_2)

        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*new_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
