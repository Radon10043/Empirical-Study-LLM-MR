import unittest
import sys
import os

import numpy as np

from scipy.stats import f_oneway, boxcox
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, *groups):
        """MR32: Applying a box-cox transformation to all groups should not change the result."""
        for i in range(len(groups)):
            for j in range(len(groups[i])):
                if groups[i][j] <= 0:
                    groups[i][j] = 1

        # Get source output
        source_out = f_oneway(*groups).pvalue

        # Construct follow-up input
        follow_groups = list(groups)
        for i in range(len(follow_groups)):
            follow_groups[i] = boxcox(follow_groups[i], lmbda=None)[0]

        # Get follow-up output
        follow_out = f_oneway(*follow_groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
