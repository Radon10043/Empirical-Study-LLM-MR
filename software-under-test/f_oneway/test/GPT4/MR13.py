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
    def test_proportional_sample_sizes(self, *groups):
        """MR13: Increasing the sample size of each group by the same proportion should not significantly affect the test results."""
        increase_factor = np.random.uniform(1.5, 3)
        larger_groups = [np.concatenate((group, np.random.choice(group, int(len(group) * (increase_factor - 1)), replace=True))) for group in groups]

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)
        
        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*larger_groups)
        
        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
