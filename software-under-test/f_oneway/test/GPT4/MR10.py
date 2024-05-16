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
    def test_random_sampling_of_groups(self, *groups):
        """MR10: Random sampling (with replacement) from each group should not significantly change the F-statistic and p-value, given a large enough sample."""
        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Sample (with replacement) from each group
        sample_groups = [np.random.choice(group, size=len(group), replace=True) for group in groups]

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*sample_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
