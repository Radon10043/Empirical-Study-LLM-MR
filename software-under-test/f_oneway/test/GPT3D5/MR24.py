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
    def test24(self, *groups):
        """MR24: Rounding all values in all groups to the nearest integer should not change the result."""
        from random import randint
        for i in range(len(groups)):
            for j in range(len(groups[i])):
                groups[i][j] /= randint(1, 10)

        # Get source output
        source_out = f_oneway(*groups).pvalue

        # Construct follow-up input
        follow_groups = [np.round(group) for group in groups]

        # Get follow-up output
        follow_out = f_oneway(*follow_groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
