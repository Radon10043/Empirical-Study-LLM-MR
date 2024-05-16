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
    def test_shifting_means(self, *groups):
        """MR11: Shifting the mean of one group by a large margin should result in a lower p-value."""
        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Select a group to shift
        group_to_shift = np.random.choice(range(len(groups)))

        # Shift its mean by a significant amount (e.g., by multiple times its standard deviation)
        shift = 5 * np.std(groups[group_to_shift])
        new_group = groups[group_to_shift] + shift
        modified_groups = list(groups)
        modified_groups[group_to_shift] = new_group

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*modified_groups)

        # Verification - expect lower p-value if the shift is large enough
        self.assertLess(follow_pvalue, source_pvalue)


if __name__ == "__main__":
    unittest.main()
