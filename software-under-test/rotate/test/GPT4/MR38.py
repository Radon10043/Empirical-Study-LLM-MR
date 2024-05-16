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
    def test_rotate_full_circle_variation(self, img: np.array, step: float):
        """Metamorphic Relation 38: Completing a full circle rotation in discrete steps should result in the original image."""
        num_steps = int(360 / step)
        rotated_img = img.copy()
        for _ in range(num_steps):
            # Rotate the image incrementally by 'step' degrees
            rotated_img = ndimage.rotate(rotated_img, step, reshape=False)

        # Verification
        np.testing.assert_array_almost_equal(rotated_img, img)


if __name__ == "__main__":
    unittest.main()
