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
    def test_duplicate_groups(self, *groups):
        """MR5: Duplicating one of the groups should not affect the significance (p-value), assuming group sizes are not equal."""
        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Create follow-up input by duplicating one of the groups
        duplicated_groups = list(groups) + [np.random.choice(groups)]

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*duplicated_groups)

        # Verification
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
