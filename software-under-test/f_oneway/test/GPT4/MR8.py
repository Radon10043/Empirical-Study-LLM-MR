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
    def test_removal_of_outliers(self, *groups):
        """MR8: Removal of outliers should not significantly affect the F-statistic and p-value if they are not substantial in number."""

        # Define a function to remove outliers
        def remove_outliers(data, threshold=1.5):
            q1, q3 = np.percentile(data, [25, 75])
            iqr = q3 - q1
            lower_bound = q1 - (iqr * threshold)
            upper_bound = q3 + (iqr * threshold)
            return data[(data >= lower_bound) & (data <= upper_bound)]

        # Get source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Remove outliers from groups
        cleaned_groups = [remove_outliers(np.array(group)) for group in groups]

        # Get follow-up output
        follow_stat, follow_pvalue = f_oneway(*cleaned_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
