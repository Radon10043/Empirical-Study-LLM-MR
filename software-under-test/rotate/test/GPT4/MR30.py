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
    def test_rotate_axis_invariance(self, img: np.array, angle: float):
        """Metamorphic Relation 30: Rotating an image around different axes by 360 degrees should result in the original image."""
        axes_options = [(0, 1), (1, 0), (0, 2), (2, 0), (1, 2), (2, 1)]  # Possible axes pairs for a 3D image
        original_img = img.copy()

        for axes_pair in axes_options:
            # Rotate around the specified axis pair by 360 degrees
            rotated_img = ndimage.rotate(img, 360, axes=axes_pair, reshape=False)

            # Verification
            np.testing.assert_array_almost_equal(rotated_img, original_img)


if __name__ == "__main__":
    unittest.main()
