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
    def test_group_addition(self, *groups):
        """MR22: Adding a new group with the overall same mean should not significantly change the F-statistic and might increase the p-value."""
        # Compute the overall mean
        all_values = np.concatenate(groups)
        overall_mean = np.mean(all_values)

        # Create a new group with values around the overall mean
        new_group_size = np.random.choice([len(g) for g in groups])
        new_group = np.random.normal(overall_mean, 0.1, size=new_group_size)  # Low standard deviation

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*(groups + (new_group,)))

        # Verification - F-statistic might slightly change, p-value expected to increase
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertGreaterEqual(follow_pvalue, source_pvalue)


if __name__ == "__main__":
    unittest.main()
