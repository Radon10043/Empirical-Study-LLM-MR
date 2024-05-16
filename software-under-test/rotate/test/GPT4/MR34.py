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
    def test_rotate_inverse_multi_step(self, img: np.array, angle: float):  # Fixed
        """Metamorphic Relation 34: Rotating an image by a sequence of angles and then by the negatives of those angles in reverse order should return the original image."""
        angles = [angle]
        for _ in range(10):
            angles.append(np.random.uniform(-180, 180))

        # Rotate by sequence of angles
        rotated_img = img.copy()
        for angle in angles:
            rotated_img = ndimage.rotate(rotated_img, angle, reshape=False)

        # Rotate back by negatives of angles in reverse order
        for angle in reversed(angles):
            rotated_img = ndimage.rotate(rotated_img, -angle, reshape=False)

        # Verification
        np.testing.assert_array_almost_equal(rotated_img, img)


if __name__ == "__main__":
    unittest.main()
