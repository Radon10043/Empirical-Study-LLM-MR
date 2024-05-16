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
    def test_constant_value_within_group(self, *groups):
        """MR16: Replacing all values within a group with a constant value should lead to an undefined F-statistic or a p-value of 1 since variance in that group becomes 0."""
        source_stat, source_pvalue = f_oneway(*groups)

        # Choose a group to replace with a constant value
        group_index = np.random.choice(len(groups))
        constant_value = np.random.uniform(-10, 10)

        group_to_replace = np.full_like(groups[group_index], constant_value)

        modified_groups = list(groups)
        modified_groups[group_index] = group_to_replace

        # Skip calculation if all groups are already homogeneous with the same constant value
        if all(np.all(group_to_replace == g) for g in modified_groups):
            self.skipTest("All groups are already replaced with the constant.")

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*modified_groups)

        # Verification - F-statistic becomes undefined or large, p-value approaches 1
        self.assertTrue(np.isnan(follow_stat) or follow_stat >= source_stat)
        self.assertAlmostEqual(follow_pvalue, 1.0, delta=0.05)


if __name__ == "__main__":
    unittest.main()
