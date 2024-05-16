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
    def test_categorical_value_insertion_within_groups(self, *groups):
        """MR39: Inserting the same categorical value into all groups should not affect the ANOVA results if the value is numerically represented the same across all groups."""
        # Insert a random category represented by a constant numerical value
        categorical_value = -999  # Clearly distinguishable value to represent a category
        categorized_groups = [np.append(group, categorical_value) for group in groups]

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*categorized_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat)
        self.assertAlmostEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
