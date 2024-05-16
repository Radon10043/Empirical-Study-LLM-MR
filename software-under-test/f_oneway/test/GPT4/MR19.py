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
    def test_arbitrary_group_extension(self, *groups):
        """MR19: Extending the sample size of a group by adding randomly generated data with similar mean and variance should not significantly change the F-statistic or the p-value."""
        # Select a group to extend
        group_index = np.random.choice(len(groups))
        group_to_extend = groups[group_index]
        mean, var = np.mean(group_to_extend), np.var(group_to_extend)

        # Generate new samples with similar mean and variance
        new_samples = np.random.normal(mean, np.sqrt(var), size=len(group_to_extend))

        # Create the extended group
        extended_group = np.concatenate([group_to_extend, new_samples])

        # Create the new groups list with the extended group replacing the original one
        modified_groups = list(groups)
        modified_groups[group_index] = extended_group

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*modified_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertAlmostEqual(source_pvalue, follow_pvalue, delta=0.05)


if __name__ == "__main__":
    unittest.main()
