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
    def test41(self, *groups):
        """MR41: Replacing a group with a constant value should not change the result."""
        # Get source output
        source_out = f_oneway(*groups).pvalue

        # Replacing the second group with a constant value
        follow_groups = list(groups)
        follow_groups[1] = np.full_like(groups[1], 5)

        # Get follow-up output
        follow_out = f_oneway(*follow_groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
