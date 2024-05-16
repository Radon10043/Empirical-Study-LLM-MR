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
    def test_combination_with_congruent_group(self, *groups):
        """MR28: Combining each group with another congruent group (a group with identical statistical properties) should not significantly affect the F-statistic and might slightly increase the p-value due to increased degrees of freedom."""

        congruent_groups = []
        for group in groups:
            # Generate a congruent group with the same mean and standard deviation
            congruent_group = np.random.normal(np.mean(group), np.std(group), size=len(group))
            congruent_groups.append(congruent_group)

        # Combine each original group with its congruent group
        combined_groups = [np.concatenate((group, congruent_group)) for group, congruent_group in zip(groups, congruent_groups)]

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*combined_groups)

        # Verification
        self.assertAlmostEqual(source_stat, follow_stat, delta=0.1)
        self.assertGreaterEqual(follow_pvalue, source_pvalue)


if __name__ == "__main__":
    unittest.main()
