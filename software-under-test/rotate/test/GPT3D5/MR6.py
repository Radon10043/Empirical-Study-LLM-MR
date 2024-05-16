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
    def test6(self, img: np.array, angle: float):
        """Metamorphic Relation 6: Rotating the image by 180 degrees twice should result in the same output as rotating the image by 360 degrees."""
        # Get source output
        source_out = ndimage.rotate(img, 180)

        # Construct follow-up input
        follow_angle = 180  # 180 degrees

        # Get follow-up output
        follow_out_temp = ndimage.rotate(source_out, follow_angle)  # Rotate the source output by 180 degrees
        follow_out = ndimage.rotate(img, 360)  # Rotate the original image by 360 degrees

        # Verification
        self.assertTrue(np.array_equal(follow_out, follow_out_temp))


if __name__ == "__main__":
    unittest.main()
