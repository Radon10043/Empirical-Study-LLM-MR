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
    def test_rotate_reshape_dimensions(self, img: np.array, angle: float):
        """Metamorphic Relation 14: When reshape is True, rotating an image by angles other than 0, 90, 180, 270, ... may change the image dimensions."""
        # Rotate with reshape=True
        rotated_reshape_true = ndimage.rotate(img, angle, reshape=True)

        # Predefined angles that typically would not require reshaping
        standard_angles = {0, 90, 180, 270, 360}

        # Check if angle is not in standard angles
        if angle % 360 not in standard_angles:
            # Verification: Expecting a change in dimensions
            assert img.shape != rotated_reshape_true.shape
        else:
            # Verification: Expecting the same dimensions
            assert img.shape == rotated_reshape_true.shape


if __name__ == "__main__":
    unittest.main()
