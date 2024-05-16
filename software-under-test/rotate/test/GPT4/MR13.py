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
    def test_rotate_reflect_axis(self, img: np.array, angle: float):  # Fixed
        """Metamorphic Relation 13: Reflecting an image across an axis and rotating should give the same result as rotating in the opposite direction and then reflecting."""
        axis = np.random.randint(0, 2)

        # Reflect image across the given axis
        reflected_img = np.flip(img, axis=axis)

        # Rotate the reflected image
        rotated_reflected_img = ndimage.rotate(reflected_img, angle)

        # Rotate the original image in the opposite direction
        rotated_img = ndimage.rotate(img, -angle)

        # Reflect the rotated image across the same axis
        reflected_rotated_img = np.flip(rotated_img, axis=axis)

        # Verification
        np.testing.assert_array_almost_equal(rotated_reflected_img, reflected_rotated_img)


if __name__ == "__main__":
    unittest.main()
