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
    def test_double_rotate_reshape_consistency(self, img: np.array, angle1: float, angle2: float):
        """Metamorphic Relation 16: Rotating an image by angle A and then by angle B with reshape=True should be same as rotating by A+B with reshape=True."""
        # Rotate by A then B
        rotate_by_a_then_b = ndimage.rotate(ndimage.rotate(img, angle1, reshape=True), angle2, reshape=True)

        # Rotate by A+B
        rotate_by_a_plus_b = ndimage.rotate(img, angle1 + angle2, reshape=True)

        # Verification of same results
        np.testing.assert_array_almost_equal(rotate_by_a_then_b, rotate_by_a_plus_b)


if __name__ == "__main__":
    unittest.main()
