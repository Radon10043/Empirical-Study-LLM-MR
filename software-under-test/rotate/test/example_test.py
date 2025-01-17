"""
Author: Radon
Date: 2023-12-20 21:42:37
LastEditors: Radon
LastEditTime: 2024-05-30 15:25:29
Description: Hi, say something
"""
import unittest

import numpy as np

from parameterized import parameterized
from scipy import ndimage, datasets
from utils import *

def load_test_cases() -> list:
    """加载测试用例

    Returns
    -------
    list
        存储测试用例的列表

    Notes
    -----
    _description_
    """
    return [(datasets.ascent(), 45), (datasets.face(), 60)]


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test1(self, img: np.array, angle: float):
        """Metamorphic Relation 1: Rotating the same image by N degree and N+360 degree will output the same result."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = angle + 360

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.any(follow_out - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
