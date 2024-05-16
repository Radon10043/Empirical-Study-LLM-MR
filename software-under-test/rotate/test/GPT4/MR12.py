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
    def test_rotate_cumulative_angles(self, img: np.array, angle1: float):  # Fixed
        """Metamorphic Relation 12: Cumulative rotation of image by angles A, B, C should be equal to the direct rotation by A+B+C."""
        angle2 = 2 * angle1
        angle3 = 3 * angle1

        # Rotate image by angle1
        rotate_by_a = ndimage.rotate(img, angle1)
        # Rotate the result by angle2
        rotate_by_b = ndimage.rotate(rotate_by_a, angle2)
        # Rotate the result by angle3
        rotate_by_c = ndimage.rotate(rotate_by_b, angle3)

        # Direct rotation by angle A+B+C
        combined_angle = angle1 + angle2 + angle3
        direct_rotation = ndimage.rotate(img, combined_angle)

        # Verification
        np.testing.assert_array_almost_equal(rotate_by_c, direct_rotation)


if __name__ == "__main__":
    unittest.main()
