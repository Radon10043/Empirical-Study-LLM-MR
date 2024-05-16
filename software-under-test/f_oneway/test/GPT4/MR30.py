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
    def test_interchange_of_groups(self, *groups):  # Fixed
        """MR30: Interchanging entire groups should not change the outputs since the ANOVA test is agnostic to the labels of the groups."""
        if len(groups) < 2:
            self.skipTest("Not enough groups to interchange.")

        # Interchange the groups
        interchanged_groups = list(groups)
        np.random.shuffle(interchanged_groups)

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*interchanged_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
