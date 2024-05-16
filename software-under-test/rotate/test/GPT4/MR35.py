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
    def test_rotate_scale_invariance(self, img: np.array, angle: float, scale: float):
        """Metamorphic Relation 35: Scaling an image up or down before rotating should have the same effect as first rotating and then scaling."""
        # Scale then rotate
        scaled_img = ndimage.zoom(img, scale)
        scaled_rotated_img = ndimage.rotate(scaled_img, angle, reshape=True)

        # Rotate then scale
        rotated_img = ndimage.rotate(img, angle, reshape=True)
        rotated_scaled_img = ndimage.zoom(rotated_img, scale)

        # Verification
        np.testing.assert_array_almost_equal(scaled_rotated_img, rotated_scaled_img)


if __name__ == "__main__":
    unittest.main()
