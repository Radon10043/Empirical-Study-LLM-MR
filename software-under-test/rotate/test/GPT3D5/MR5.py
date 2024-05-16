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
    def test5(self, img: np.array, angle: float):
        """Metamorphic Relation 5: Rotating an image and then rotating the result by the same angle should result in the same output as rotating the original image by 2 times the angle."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out_temp = ndimage.rotate(source_out, angle)  # Rotate the source output by the same angle
        follow_angle = angle * 2

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.array_equal(follow_out, follow_out_temp))


if __name__ == "__main__":
    unittest.main()
