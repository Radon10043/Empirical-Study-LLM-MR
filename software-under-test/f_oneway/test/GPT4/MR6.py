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
    def test_combining_groups(self, *groups):
        """MR6: Combining two groups should affect the p-value if original groups had different means."""
        # Cannot be tested if there are less than three groups
        if len(groups) < 3:
            self.skipTest("Not enough groups to combine")

        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Create follow-up input by combining first two groups
        combined_groups = [np.concatenate(groups[:2])] + list(groups[2:])

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*combined_groups)

        # Verification that the p-value should change
        self.assertNotEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
