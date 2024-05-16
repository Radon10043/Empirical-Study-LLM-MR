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
    def test_centering_invariance(self, *groups):
        """MR4: Centering invariance, adding a constant to all values, the F-statistic should remain unchanged and p-value should remain the same."""
        offset = np.random.uniform(-10, 10)

        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Create follow-up input by adding a constant to each group
        centered_groups = [np.array(group) + offset for group in groups]

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*centered_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
