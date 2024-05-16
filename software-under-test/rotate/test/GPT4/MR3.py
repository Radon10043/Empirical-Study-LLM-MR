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
    def test_rotate_double(self, img: np.array, angle: float):
        """Metamorphic Relation 3: Rotating an image by angle N and then by angle 2*N should be the same as rotating initially by angle 3*N."""
        # Get source output
        once_rotated = ndimage.rotate(img, angle)

        # Construct follow-up input
        second_rotate_angle = 2 * angle

        # Get follow-up output
        twice_rotated = ndimage.rotate(once_rotated, second_rotate_angle)

        # Get expected output by rotating N * 3 times directly
        thrice_angle = 3 * angle
        expected_output = ndimage.rotate(img, thrice_angle)

        # Verification
        np.testing.assert_array_almost_equal(twice_rotated, expected_output)


if __name__ == "__main__":
    unittest.main()
