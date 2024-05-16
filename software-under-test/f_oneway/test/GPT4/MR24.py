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
    def test_group_expansion_with_external_data(self, *groups):
        """MR24: Expanding a group with external data having the same distribution should not significantly change the F-statistic or p-value."""

        # Select a group to expand
        group_index = np.random.choice(len(groups))
        group_to_expand = groups[group_index]

        # Assuming the group is normally distributed, get its mean and standard deviation
        mean, std_dev = np.mean(group_to_expand), np.std(group_to_expand)

        # Generate new external data with the same distribution
        external_data_size = int(len(group_to_expand) * 0.5)  # Add 50% more values
        external_data = np.random.normal(mean, std_dev, size=external_data_size)

        # Expand the chosen group with external data
        expanded_groups = list(groups)
        expanded_groups[group_index] = np.concatenate([group_to_expand, external_data])

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*expanded_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
