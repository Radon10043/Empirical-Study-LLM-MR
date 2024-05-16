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
    def test3(self, img: np.array, angle: float):
        """Metamorphic Relation 3: Rotating the image by 360-degree multiples of a specific angle will result in the same output."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        # follow_angle = angle * n  # where n is an integer
        follow_angle = angle + 360 * 2  # where n is an integer

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.any(follow_out - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
