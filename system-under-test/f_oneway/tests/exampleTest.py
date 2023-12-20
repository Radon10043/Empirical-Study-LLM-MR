"""
Author: Radon
Date: 2023-12-05 10:21:39
LastEditors: Radon
LastEditTime: 2023-12-20 17:36:46
Description: Hi, say something
"""
import unittest

import numpy as np

from scipy.stats import f_oneway
from parameterized import parameterized


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
    # fmt:off
    test_cases = [
        ([1, 2, 3, 4, 5], [2, 3, 4, 5, 6]),
        ([1, 3, 5, 7, 9], [1, 3, 5, 7, 9])
    ]
    # fmt:on
    return test_cases


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test1(self, g1, g2):
        """MR1: Changing the order of the samples, the result should not change.

        Notes
        -----
        _description_
        """
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.permutation(g1)
        follow_g2 = np.random.permutation(g2)

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
