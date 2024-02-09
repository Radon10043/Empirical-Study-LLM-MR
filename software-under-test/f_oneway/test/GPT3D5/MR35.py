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
    def test35(self, *groups):
        """MR35: Multiplying all values in every group by a constant should not change the result."""
        # Get source output
        source_out = f_oneway(*groups).pvalue

        constant = 2
        # Construct follow-up input
        follow_groups = [np.array(group) * constant for group in groups]

        # Get follow-up output
        follow_out = f_oneway(*follow_groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
