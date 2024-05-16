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
    def test_extreme_value_inclusion(self, *groups):
        """MR37: Including an extreme value to all groups should not change the ANOVA results if the value is the same for all groups."""
        extreme_value = np.max(np.concatenate(groups)) * 1000

        # Add an extreme value to all groups
        augmented_groups = [np.append(group, extreme_value) for group in groups]

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*augmented_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
