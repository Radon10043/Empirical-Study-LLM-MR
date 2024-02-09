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
    def test2(self, *groups):
        """MR2: Adding a constant to all values in a group should not change the result."""
        # Get source output
        source_out = f_oneway(*groups).pvalue

        # Construct follow-up input
        follow_groups = [np.array(group) + 1 for group in groups]

        # Get follow-up output
        follow_out = f_oneway(*follow_groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
