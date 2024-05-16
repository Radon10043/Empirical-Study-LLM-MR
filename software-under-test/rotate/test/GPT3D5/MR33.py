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
    def test33(self, img: np.array, angle: float):
        """Metamorphic Relation 33: Rotating the image using different order parameters will guarantee consistency if the order parameters are swapped."""
        # Get source output with the original order
        source_out = ndimage.rotate(img, angle, order=3)

        # Construct follow-up input with swapped order parameters
        follow_out = ndimage.rotate(img, angle, order=0)  # Use a different order parameter

        # Verification
        self.assertTrue(np.any(follow_out - source_out) == 0)  # Fixed


if __name__ == "__main__":
    unittest.main()
