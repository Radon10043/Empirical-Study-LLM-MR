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
    def test40(self, img: np.array, angle: float):
        """Metamorphic Relation 40: Rotating an image by angle and then rotating the result with a negative angle should yield the same output as the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = -angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        self.assertTrue(np.any(follow_out - img) == 0)


if __name__ == "__main__":
    unittest.main()
