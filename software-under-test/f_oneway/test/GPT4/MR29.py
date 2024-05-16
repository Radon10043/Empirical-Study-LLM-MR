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
    def test_multiplication_by_nonzero_constant(self, *groups): # Fixed
        """MR29: Multiplying all group values by a nonzero constant should not affect the F-statistic since variances will scale but the relative differences stay the same."""
        nonzero_constant = np.random.uniform(0.1, 10)

        # Multiply groups by the nonzero constant
        scaled_groups = [[val * nonzero_constant for val in group] for group in groups]

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*scaled_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
