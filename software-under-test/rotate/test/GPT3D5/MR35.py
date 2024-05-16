import os
import sys
import unittest

import numpy as np
from scipy import ndimage, datasets
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, img: np.array, angle: float):
        """Metamorphic Relation 35: Rotating the image by positive angle and then rotating the negative angling by the same positive angle should result in the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = -angle  # Negative of the original angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, -follow_angle)  # Rotate the negative angle by the same positive angle

        # Verification
        self.assertTrue(np.any(follow_out - img) == 0)  # Fixed


if __name__ == "__main__":
    unittest.main()
