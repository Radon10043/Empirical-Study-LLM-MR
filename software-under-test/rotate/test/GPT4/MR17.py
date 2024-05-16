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
    def test_rotate_output_dtype(self, img: np.array, angle: float, dtype: np.dtype):
        """Metamorphic Relation 17: Rotating an image and specifying an output dtype should return an image of that dtype."""
        # Rotate the image with the specified dtype for output
        rotated_img = ndimage.rotate(img, angle, output=dtype)

        # Verification that the rotated image has the specified dtype
        assert rotated_img.dtype == dtype


if __name__ == "__main__":
    unittest.main()
