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
    def test_increasing_variance_within_group(self, *groups):
        """MR15: Increasing the variance within one group by adding a large outlier should typically increase the F-statistic and might affect the p-value significantly."""
        # Choose a group to add an outlier
        group_index = np.random.choice(len(groups))
        group_with_outlier = list(groups[group_index])

        # Add an outlier
        outlier = np.mean(group_with_outlier) + 10 * np.std(group_with_outlier)
        group_with_outlier.append(outlier)

        new_groups = list(groups)
        new_groups[group_index] = np.array(group_with_outlier)

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*new_groups)

        # Verification - F-statistic might increase due to increased variance
        self.assertLessEqual(source_stat, follow_stat)
        # p-value might be significantly different
        self.assertNotEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
