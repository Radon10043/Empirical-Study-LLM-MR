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
    def test_rotate_mode_edge_effects(self, img: np.array, angle: float):
        """Metamorphic Relation 36: Different modes when rotating should affect the edge filling of the image, but not the central region."""
        modes = ["constant", "nearest", "reflect", "wrap"]
        center_slice = slice(img.shape[0] // 4, 3 * img.shape[0] // 4)  # Central portion of the image

        # Original rotation
        original_rotated_img = ndimage.rotate(img, angle, reshape=False, mode=modes[0])
        original_center = original_rotated_img[center_slice, center_slice]

        for mode in modes[1:]:
            # Rotation with different mode
            new_mode_rotated_img = ndimage.rotate(img, angle, reshape=False, mode=mode)
            new_mode_center = new_mode_rotated_img[center_slice, center_slice]

            # Verification: Central region should remain the same
            np.testing.assert_array_almost_equal(original_center, new_mode_center)


if __name__ == "__main__":
    unittest.main()
