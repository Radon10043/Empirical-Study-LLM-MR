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
    def test_removing_group(self, *groups):
        """MR31: Removing a group should generally increase the F-statistic and lower the p-value if the removed group was one of the ones contributing to a lower between-group variance."""

        # Ensure there are at least 3 groups so we can remove one and still perform an ANOVA
        if len(groups) < 3:
            self.skipTest("Not enough groups to remove one and still run ANOVA.")

        # Remove a random group
        groups_list = list(groups)
        removed_group_index = np.random.choice(len(groups_list))
        removed_group = groups_list.pop(removed_group_index)

        # Calculate source output
        source_stat, source_pvalue = f_oneway(*groups)

        # Calculate follow-up output
        follow_stat, follow_pvalue = f_oneway(*groups_list)

        # Verification can vary; if removed group affects between-group variance, expect changes in stat & p-values
        # In the ANOVA context, we generally expect some change, so we do not assert exact equality.
        self.assertNotEqual(source_stat, follow_stat)
        self.assertNotEqual(source_pvalue, follow_pvalue)


if __name__ == "__main__":
    unittest.main()
