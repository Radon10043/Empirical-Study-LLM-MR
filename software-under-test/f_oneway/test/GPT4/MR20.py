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
    def test_identical_groups(self, group):
        """MR20: If all groups are identical, the F-statistic should be zero and the p-value should be 1.0."""
        identical_group = np.array(group)
        replicated_groups = [identical_group for _ in range(3)]  # Testing with three identical groups

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*replicated_groups)

        # Verification
        self.assertAlmostEqual(follow_stat, 0)
        self.assertAlmostEqual(follow_pvalue, 1.0)


if __name__ == "__main__":
    unittest.main()
