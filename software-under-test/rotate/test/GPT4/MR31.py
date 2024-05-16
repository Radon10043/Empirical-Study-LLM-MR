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
    def test_rotate_then_inverse_multiple(self, img: np.array, angle: float):  # Fixed
        """Metamorphic Relation 31: A sequence of rotations by angles [A, B, ..., N] and their opposites [-A, -B, ..., -N] should return the original image."""
        rotated_img = img.copy()
        angles = [angle]
        for _ in range(1, 10):
            angles.append(np.random.uniform(-180, 180))

        # Apply rotations by angles A, B, ..., N
        for angle in angles:
            rotated_img = ndimage.rotate(rotated_img, angle, reshape=False)

        # Apply rotations by angles -N, ..., -B, -A
        for angle in reversed(angles):
            rotated_img = ndimage.rotate(rotated_img, -angle, reshape=False)

        # Verification that the final image should match the original
        np.testing.assert_array_almost_equal(rotated_img, img)


if __name__ == "__main__":
    unittest.main()
