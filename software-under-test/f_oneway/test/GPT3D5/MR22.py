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
    def test22(self, *groups):
        """MR22: Multiplying all values in one group by a constant while dividing all values in another group by the same constant should not change the result."""
        # Get source output
        source_out = f_oneway(*groups).pvalue

        # Construct follow-up input
        follow_groups = [np.array(groups[0]) * 2, np.array(groups[1]) / 2]

        # Get follow-up output
        follow_out = f_oneway(*follow_groups).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
