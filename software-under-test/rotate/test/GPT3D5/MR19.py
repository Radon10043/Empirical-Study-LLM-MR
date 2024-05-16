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
    def test19(self, img: np.array, angle: float):
        """Metamorphic Relation 19: Rotating the image by a 90-degree multiple should result in the same output as flipping the image axes."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = 90  # 90 degrees

        # Get follow-up output
        follow_out = ndimage.rotate(np.swapaxes(img, 0, 1), follow_angle)  # Swap the axes and then rotate by 90 degrees

        # Verification
        self.assertTrue(np.any(follow_out - source_out) == 0)  # Fixed


if __name__ == "__main__":
    unittest.main()
