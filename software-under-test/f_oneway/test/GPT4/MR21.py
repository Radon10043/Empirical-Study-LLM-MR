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
    def test_group_sign_flip(self, *groups):    # Fixed
        """MR21: Flipping the sign of all values in a group should not affect the F-statistic or the p-value."""
        # Flip sign of the values in one randomly chosen group
        flip_index = np.random.choice(len(groups))
        flipped_groups = list(groups)
        flipped_groups[flip_index] = [-val for val in flipped_groups[flip_index]]

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*flipped_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
