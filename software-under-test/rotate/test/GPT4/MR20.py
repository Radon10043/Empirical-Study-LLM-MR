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
    def test_rotate_by_consecutive_angles(self, img: np.array, angle: float):
        """Metamorphic Relation 20: Rotating by angle A, then angle B should be the same as rotating by angle A+B in one step, where A and B are randomly picked angles."""
        angle_a = angle
        angle_b = np.random.uniform(-180, 180)
        angle_sum = angle_a + angle_b

        # Rotate by angle A and then by B
        intermediate_img = ndimage.rotate(img, angle_a, reshape=False)
        consecutive_rotate_img = ndimage.rotate(intermediate_img, angle_b, reshape=False)

        # Rotate by A+B
        combined_rotate_img = ndimage.rotate(img, angle_sum, reshape=False)

        # Verification
        np.testing.assert_array_almost_equal(consecutive_rotate_img, combined_rotate_img)


if __name__ == "__main__":
    unittest.main()
