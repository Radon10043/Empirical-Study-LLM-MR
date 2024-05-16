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
    def test_exchanging_samples_between_groups(self, *groups):
        """MR14: Exchanging a small number of samples between groups should not significantly affect the F-statistic or the p-value."""
        if len(groups) < 2 or any(len(group) < 2 for group in groups):
            self.skipTest("Not enough groups or not enough samples in groups to exchange.")
        
        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)
        
        # Exchange samples between the first two groups
        group1, group2 = groups[0], groups[1]
        group1_new = np.append(group1[1:], group2[0])
        group2_new = np.append(group2[1:], group1[0])
        
        new_groups = [group1_new, group2_new] + list(groups[2:])
        
        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*new_groups)
        
        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
