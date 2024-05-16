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
    def test_permutation_invariance(self, *groups):  # Fixed
        """MR2: Permutation invariance of groups, the F-statistic and p-value should remain unchanged."""
        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Create follow-up input by permuting the group order
        tmp_list = list(groups)
        np.random.shuffle(tmp_list)
        follow_groups = tuple(tmp_list)

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*follow_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
