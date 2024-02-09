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
    def test15(self, *groups):
        """MR15: Adding a Gaussian noise with mean 0 and variance 1 to all values should not change the result."""
        # Get source output
        source_out = f_oneway(*groups).pvalue

        # Construct follow-up input
        follow_groups = [group + np.random.normal(0, 1, len(group)) for group in groups]

        # Get follow-up output
        follow_out = f_oneway(*follow_groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
