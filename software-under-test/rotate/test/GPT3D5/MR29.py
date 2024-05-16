import os
import sys
import unittest

import numpy as np
from scipy import ndimage, datasets
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


# fixed
class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, img: np.array, angle: float):
        """Metamorphic Relation 29: Rotating the image by -angle should result in the same output as rotating the horizontally flipped image by -angle."""
        # Get source output
        source_out = ndimage.rotate(img, -angle)

        # Construct follow-up input
        follow_input = np.fliplr(img)  # Horizontal flip of the original input

        # Get follow-up output
        follow_out = ndimage.rotate(follow_input, -angle)  # Rotate the horizontally flipped input by -angle

        # Verification
        self.assertTrue(np.any(follow_out - source_out) == 0)  # Fixed


if __name__ == "__main__":
    unittest.main()
