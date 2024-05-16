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
    def test_rotate_incremental_angles_sum(self, img: np.array, base_angle: float):
        """Metamorphic Relation 28: Incrementally rotating an image by an angle and sum of increments should result in the same image as a single rotation of that sum."""
        increments = [np.random.uniform(-30, 30) for _ in range(3)]  # Generate random increments
        sum_of_increments = sum(increments)
        angle_sum = base_angle + sum_of_increments

        rotated_image_sum = ndimage.rotate(img, angle_sum, reshape=False)
        incremental_rotated_img = img.copy()

        # Apply incremental rotations
        for increment in increments:
            incremental_rotated_img = ndimage.rotate(incremental_rotated_img, base_angle + increment, reshape=False)

        # Verification
        np.testing.assert_array_almost_equal(rotated_image_sum, incremental_rotated_img)


if __name__ == "__main__":
    unittest.main()
