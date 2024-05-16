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
    def test4(self, img: np.array, angle: float):  # Fixed
        """Metamorphic Relation 4: Rotating the image by 90-degree multiples will result in the same output up to a permutation of axes."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = angle + 90  # where 90 is a multiple of 90 degrees

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.any(np.transpose(follow_out) - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
