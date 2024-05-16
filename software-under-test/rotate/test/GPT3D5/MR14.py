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
    def test14(self, img: np.array, angle: float):
        """Metamorphic Relation 14: Rotating an image and its vertically flipped counterpart by the same angle should yield vertically flipped outputs."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_input = np.flipud(img)  # Vertical flip of the original input

        # Get follow-up output
        follow_out = ndimage.rotate(follow_input, angle)

        # Verification
        self.assertTrue(np.any(np.flipud(follow_out) - source_out) == 0)  # Fixed


if __name__ == "__main__":
    unittest.main()
