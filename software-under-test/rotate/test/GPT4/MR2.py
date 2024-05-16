import os
import sys
import unittest

import numpy as np
from scipy import ndimage, datasets
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test_rotate_sum_360(self, img: np.array, angle1: float, angle2: float):
        """Metamorphic Relation 2: Rotating an image by angle X and then by angle Y, such that X+Y = 360, should yield the same result as the original."""
        # Get source output
        source_out = ndimage.rotate(img, angle1)

        # Construct follow-up input
        follow_angle = 360 - angle1

        # Get follow-up output
        second_rotate_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        np.testing.assert_array_almost_equal(second_rotate_out, img)


if __name__ == "__main__":
    unittest.main()
