"""
Author: Radon
Date: 2023-12-05 10:21:39
LastEditors: Radon
LastEditTime: 2024-01-18 17:49:41
Description: Hi, say something
"""
import unittest

import numpy as np

from scipy.stats import f_oneway
from parameterized import parameterized

from utils import gen_tcs_randomly


def load_test_cases() -> list:
    """加载测试用例

    Returns
    -------
    list
        存有测试用例的列表

    Notes
    -----
    _description_
    """
    return gen_tcs_randomly()


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test1(self, g1: list, g2: list):
        """MR1: Changing the order of the samples, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.permutation(g1)
        follow_g2 = np.random.permutation(g2)

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
