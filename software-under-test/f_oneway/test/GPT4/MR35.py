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
    def test_subtraction_of_means_within_groups(self, *groups): # Fixed
        """MR35: Subtracting the mean from all values within each group should not change the resulting F-statistic or p-value."""
        # Subtract the mean from each group to center it at 0
        centered_groups = list()
        for group in groups:
            avg = np.mean(group)
            centered_group = [val - avg for val in group]
            centered_groups.append(centered_group)

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*centered_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
