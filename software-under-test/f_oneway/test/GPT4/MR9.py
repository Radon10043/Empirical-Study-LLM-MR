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
    def test_addition_of_common_value(self, *groups):
        """MR9: Adding a common value to all data points should leave the F-statistic unaffected and the p-value the same."""
        common_value = np.random.uniform(-10, 10)

        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Add common value to each group
        modified_groups = [np.array(group) + common_value for group in groups]

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*modified_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
