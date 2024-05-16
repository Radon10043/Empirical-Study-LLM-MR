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
    def test_addition_of_group_with_identical_values(self, *groups):
        """MR41: Adding a new group with identical values to an existing group should not change the F-statistic and should increase the p-value since it doesn't add new information."""
        # Choose an existing group and replicate it to form a new group
        replicated_group = np.array(groups[0])

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*(groups + (replicated_group,)))

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertGreaterEqual(follow_pvalue, source_pvalue)


if __name__ == "__main__":
    unittest.main()
